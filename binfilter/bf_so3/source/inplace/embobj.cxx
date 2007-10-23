/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: embobj.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 13:46:19 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#include <stdio.h>



#include <bf_so3/embobj.hxx>

#include <vcl/cvtgrf.hxx>
#include <vcl/gdimtf.hxx>
#include <vcl/wrkwin.hxx>
#include <vcl/svapp.hxx>
#include <vcl/virdev.hxx>
#include <sot/storinfo.hxx>
#include <sot/absdev.hxx>
#include <tools/debug.hxx>
#include <sot/exchange.hxx>

#include <soimpl.hxx>
#include "bf_so3/outplace.hxx"
#include <bf_so3/client.hxx>
#include <bf_so3/svstor.hxx>
#include <bf_so3/so2dll.hxx>
#include "bf_so3/soerr.hxx"
#include <svuidlg.hrc>

#include <svtools/filter.hxx>
#include <svtools/transfer.hxx>
#include <viscache.hxx>
#include <sot/formats.hxx>

// ----------------------
// - SvEmbeddedTransfer -
// ----------------------

class SvEmbeddedTransfer : public TransferableHelper
{
private:

    SvEmbeddedObjectRef mxObj;

protected:

    virtual void        AddSupportedFormats();
    virtual sal_Bool    GetData( const ::com::sun::star::datatransfer::DataFlavor& rFlavor );
    virtual void        ObjectReleased();

public:

                        SvEmbeddedTransfer( const SvEmbeddedObjectRef& rxObj );
                        ~SvEmbeddedTransfer();
};

// -----------------------------------------------------------------------------

SvEmbeddedTransfer::SvEmbeddedTransfer( const SvEmbeddedObjectRef& rxObj ) :
    mxObj( rxObj )
{
}

// -----------------------------------------------------------------------------

SvEmbeddedTransfer::~SvEmbeddedTransfer()
{
}

// -----------------------------------------------------------------------------

void SvEmbeddedTransfer::AddSupportedFormats()
{
    AddFormat( SOT_FORMATSTR_ID_EMBED_SOURCE );
    AddFormat( SOT_FORMATSTR_ID_OBJECTDESCRIPTOR );
    AddFormat( FORMAT_GDIMETAFILE );
}

// -----------------------------------------------------------------------------

sal_Bool SvEmbeddedTransfer::GetData( const ::com::sun::star::datatransfer::DataFlavor& rFlavor )
{
    sal_Bool bRet = sal_False;

    if( mxObj.Is() )
    {
        sal_uInt32 nFormat = SotExchange::GetFormat( rFlavor );

        if( HasFormat( nFormat ) )
        {
            if( nFormat == SOT_FORMATSTR_ID_OBJECTDESCRIPTOR )
            {
                TransferableObjectDescriptor aDesc;

                mxObj->FillTransferableObjectDescriptor( aDesc );
                bRet = SetTransferableObjectDescriptor( aDesc, rFlavor );
            }
            else if( nFormat == SOT_FORMATSTR_ID_EMBED_SOURCE )
            {
                BOOL bWriteOLEStg;
                {
                    // JP 29.3.2001: ist this the right identification?
                    SvOutPlaceObjectRef xOutRef( mxObj );
                    bWriteOLEStg = xOutRef.Is();
                    SvPseudoObjectRef xPO( mxObj );
                    if ( xPO.Is() && ( xPO->GetMiscStatus() & SVOBJ_MISCSTATUS_SPECIALOBJECT ) )
                        bWriteOLEStg = TRUE;
                }

                SotStorageStreamRef xDataStm( new SotStorageStream( String() ) );
                SvStorageRef xStore = new SvStorage( !bWriteOLEStg, *xDataStm );

                xDataStm->SetBufferSize( 0xff00 );

                if( xStore->GetVersion() <= SOFFICE_FILEFORMAT_40 )
                    xStore->SetVersion( SOFFICE_FILEFORMAT_40 +1 );

                mxObj->SetupStorage( xStore );
                bRet = mxObj->DoSaveAs( xStore );
                mxObj->DoSaveCompleted();

                xStore->Commit();
                xDataStm->Commit();
                bRet = ( xDataStm->GetError() == ERRCODE_NONE );

                if( bRet )
                {
                    ::com::sun::star::uno::Any                  aAny;
                    const sal_uInt32                            nLen = xDataStm->Seek( STREAM_SEEK_TO_END );
                    ::com::sun::star::uno::Sequence< sal_Int8 > aSeq( nLen );

                    xDataStm->Seek( STREAM_SEEK_TO_BEGIN );
                    xDataStm->Read( aSeq.getArray(),  nLen );

                    if( ( bRet = ( aSeq.getLength() > 0 ) ) == sal_True )
                    {
                        aAny <<= aSeq;
                        SetAny( aAny, rFlavor );
                    }
                }
            }
            else if( nFormat == FORMAT_GDIMETAFILE )
            {
                GDIMetaFile     aMtf;
                VirtualDevice   aVDev;
                MapMode         aMapMode( mxObj->GetMapUnit() );
                Rectangle       aVisArea( mxObj->GetVisArea( ASPECT_CONTENT ) );

                aVDev.EnableOutput( FALSE );
                aVDev.SetMapMode( aMapMode );
                aMtf.SetPrefSize( aVisArea.GetSize() );
                aMtf.SetPrefMapMode( aMapMode );
                aMtf.Record( &aVDev );

                mxObj->DoDraw( &aVDev, Point(), aVisArea.GetSize(), JobSetup(), ASPECT_CONTENT );

                aMtf.Stop();
                aMtf.WindStart();

                bRet = SetGDIMetaFile( aMtf, rFlavor );
            }
        }
    }

    return bRet;
}

// -----------------------------------------------------------------------------

void SvEmbeddedTransfer::ObjectReleased()
{
    mxObj.Clear();
}

/************** class SvEmbeddedInfoObject ***************************************/
/*************************************************************************/
SV_IMPL_PERSIST1(SvEmbeddedInfoObject,SvInfoObject)

/************************************************************************
|*    SvEmbeddedInfoObject::SvEmbeddedInfoObject()
|*    SvEmbeddedInfoObject::~SvEmbeddedInfoObject()
|*
|*    Beschreibung
*************************************************************************/
SvEmbeddedInfoObject::SvEmbeddedInfoObject() :
    nViewAspect( ASPECT_CONTENT )
{
}

SvEmbeddedInfoObject::SvEmbeddedInfoObject( SvEmbeddedObject * pObj )
    : SvInfoObject( pObj ),
    nViewAspect( ASPECT_CONTENT )
{
}

SvEmbeddedInfoObject::SvEmbeddedInfoObject( SvEmbeddedObject * pObj,
                                            const String & rName )
    : SvInfoObject( pObj, rName ),
    nViewAspect( ASPECT_CONTENT )

{
}

SvEmbeddedInfoObject::SvEmbeddedInfoObject( const String& rObjName,
                                     const SvGlobalName& rClassName )
    : SvInfoObject( rObjName, rClassName ),
    nViewAspect( ASPECT_CONTENT )

{
}

SvEmbeddedInfoObject::~SvEmbeddedInfoObject()
{
}

/************************************************************************
|*    SvEmbeddedInfoObject::MakeCopy()
|*
|*    Beschreibung
*************************************************************************/
void SvEmbeddedInfoObject::Assign( const SvInfoObject * pObj )
{
    SvInfoObject::Assign( pObj );
    SvEmbeddedInfoObject * pI = PTR_CAST(SvEmbeddedInfoObject, pObj );
    if( pI )
    {
        aVisArea = pI->aVisArea;
    }
}

/************************************************************************
|*    SvEmbeddedInfoObject::Load()
|*    SvEmbeddedInfoObject::Save()
|*
|*    Beschreibung
*************************************************************************/
#define INFO_VERSION    (BYTE)2
void SvEmbeddedInfoObject::Load( SvPersistStream & rStm )
{
    SvInfoObject::Load( rStm );
    BYTE nVers = 0;
    rStm >> nVers;
    DBG_ASSERT( nVers == INFO_VERSION, "SvInfoObject version conflict" )
    if( nVers != INFO_VERSION )
        rStm.SetError( SVSTREAM_WRONGVERSION );
    else
    {
        BOOL bIsLink;
        rStm >> bIsLink;
        rStm >> aVisArea;
    }
}

void SvEmbeddedInfoObject::Save( SvPersistStream & rStm )
{
    SvInfoObject::Save( rStm );
    rStm << (BYTE)INFO_VERSION;
    BOOL bIsLink = FALSE;
    rStm << bIsLink;
    rStm << GetVisArea();
}

/************************************************************************
|*    SvEmbeddedInfoObject::SetObj()
|*
|*    Beschreibung
*************************************************************************/
void SvEmbeddedInfoObject::SetObj( SvPersist * pObjP )
{
    SvInfoObject::SetObj( pObjP );
    SvEmbeddedObject * pObj = GetEmbed();
    if( pObj && !pObj->Owner() )
        pObj->SvEmbeddedObject::SetVisArea( aVisArea );
}

/************************************************************************
|*    SvEmbeddedInfoObject::IsLink()
|*
|*    Beschreibung
*************************************************************************/
BOOL SvEmbeddedInfoObject::IsLink() const
{
    return FALSE;
}

/************************************************************************
|*    SvEmbeddedInfoObject::GetVisArea()
|*
|*    Beschreibung
*************************************************************************/
const Rectangle & SvEmbeddedInfoObject::GetVisArea() const
{
    SvEmbeddedObject * pObj = GetEmbed();
    if( pObj )
        ((SvEmbeddedInfoObject *)this)->aVisArea = pObj->GetVisArea();
    return aVisArea;
}

UINT32 SvEmbeddedInfoObject::GetViewAspect() const
{
    SvEmbeddedObject * pObj = GetEmbed();
    if( pObj )
        ((SvEmbeddedInfoObject *)this)->nViewAspect = pObj->GetViewAspect();
    return nViewAspect;
}

/********************** SvFilterList **************************************
**************************************************************************/

/************** class SvObjectDescriptor ********************************
**************************************************************************/




/*************************************************************************
|*
|*    SvEmbeddedObject::Factory()
|*
*************************************************************************/
SO2_IMPL_CLASS2_DLL(SvEmbeddedObject,SvFactory,SvPersist,SvPseudoObject,
                    SvGlobalName( 0xBB0D2800L, 0x73EE, 0x101B,
                                  0x80,0x4C,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD) )

IUnknown * SvEmbeddedObject::GetMemberInterface( const SvGlobalName & )
{
    return NULL;
}

void SvEmbeddedObject::TestMemberObjRef( BOOL /*bFree*/ )
{
#ifdef DBG_UTIL
    if( GetClient() )
    {
        ByteString aTest = "\t\tGetClient() == ";
        aTest.Append( ByteString::CreateFromInt32( (ULONG)(SvObject *)GetClient() ) );
        DBG_TRACE( aTest.GetBuffer() );
    }
#endif
}

#ifdef TEST_INVARIANT
void SvEmbeddedObject::TestMemberInvariant( BOOL bPrint )
{
    (void)bPrint;
}
#endif

/************************************************************************
|*    SvEmbeddedObject::SvEmbeddedObject()
|*
|*    Beschreibung
*************************************************************************/
SvEmbeddedObject::SvEmbeddedObject()
    : bAutoSave       ( TRUE )
    , bAutoHatch      ( TRUE )
    , nMapUnit        ( MAP_100TH_MM )
{
}


SvEmbeddedObject::~SvEmbeddedObject()
{
}

//=========================================================================
USHORT SvEmbeddedObject::FuzzyLock
(
    BOOL bLock,     /* TRUE, lock. FALSE, unlock. */
    BOOL bIntern,   /* TRUE, es handelt sich um einen internen Lock.
                       FALSE, der Lock kam von aussen (Ole2, Ipc2) */
    BOOL bClose     /* TRUE, Close aufrufen wenn letzte Lock */
)
/*  [Beschreibung]

    Ruft FuzzyLock von <SvPseudoObject> und nicht von <SvPersist>.

    [Querverweise]

    <SvPseudoObject::FuzzyLock>
*/
{
    return SvPseudoObject::FuzzyLock( bLock, bIntern, bClose );
}


/// Direct sent, when ViewChange is called. So nothing to do
void SvEmbeddedObject::SendViewChanged()
{
}

void SvEmbeddedObject::ViewChanged( USHORT nAspect)
{
    SvEmbeddedClient * pCl = GetClient();
    if( pCl )
        pCl->ViewChanged( nAspect );
}


/*************************************************************************
|*    SvEmbeddedObject::CreateTransferableSnapshot()
|*
|*    Beschreibung
*************************************************************************/

::com::sun::star::uno::Reference<
                            ::com::sun::star::datatransfer::XTransferable >
    SvEmbeddedObject::CreateTransferableSnapshot()
{
    return( new SvEmbeddedTransfer( this ) );
}

/*************************************************************************
|*    SvEmbeddedObject::GetGDIMetaFile()
|*
|*    Beschreibung
*************************************************************************/

GDIMetaFile& SvEmbeddedObject::GetGDIMetaFile( GDIMetaFile& rMTF )
{
    TransferableDataHelper aDataHelper( new SvEmbeddedTransfer( this ) );
    if( !aDataHelper.GetTransferable().is() ||
        !aDataHelper.GetGDIMetaFile( FORMAT_GDIMETAFILE, rMTF ) )
        rMTF.Clear();
    return rMTF;
}

BOOL SvEmbeddedObject::SetData( const String& )
{
    return FALSE;
}




/*************************************************************************
|*    SvEmbeddedObject::Load()
|*
|*    Beschreibung
*************************************************************************/
BOOL SvEmbeddedObject::Load( SvStorage * pStor )
{
    SvGlobalName aClassName = pStor->GetClassName();

    SvGlobalName aActualClassName =
        SvFactory::GetAutoConvertTo( aClassName );

    if( aActualClassName == *GetSvFactory() )
        return SvPersist::Load( pStor );
    else
    { // Ich bin es nicht selbst
        return SvPersist::Load( pStor );
    }
}

/*************************************************************************
|*    SvEmbeddedObject::Save()
|*
|*    Beschreibung
*************************************************************************/
BOOL SvEmbeddedObject::Save()
{
    return SvPersist::Save();
}

BOOL SvEmbeddedObject::SaveAs( SvStorage * pNewStor )
{
    BOOL bRet = FALSE;
    if( SvPersist::SaveAs( pNewStor ) )
    {
        bRet = TRUE;
        if( bRet && Owner() && GetParent()
          && SOFFICE_FILEFORMAT_31 == pNewStor->GetVersion() )
        {
            ULONG n = pNewStor->GetFormat();
            if( n == SOT_FORMATSTR_ID_STARWRITER_30 || n == SOT_FORMATSTR_ID_STARDRAW
              || n == SOT_FORMATSTR_ID_STARCALC )
            {
                // empty MTF for 3.1 formats
                GDIMetaFile aMtf;
                MakeContentStream( pNewStor, aMtf );
            }
        }
    }
    return bRet;
}

/*************************************************************************
|*    SvEmbeddedObject::LoadContent()
|*
|*    Beschreibung
*************************************************************************/
#define EMBEDDED_OBJECT_VERSION (BYTE)0
void SvEmbeddedObject::LoadContent( SvStream & rStm, BOOL bOwner_ )
{
    SvPersist::LoadContent( rStm, bOwner_ );
    if( rStm.GetError() != SVSTREAM_OK )
        return;

    if( bOwner_ )
    {
        BYTE nVers;
        rStm >> nVers;
        DBG_ASSERT( nVers == EMBEDDED_OBJECT_VERSION, "version conflict" )

        if( nVers != EMBEDDED_OBJECT_VERSION )
            rStm.SetError( SVSTREAM_WRONGVERSION );
        else
        {
            // Sichtbaren Bereich setzten
            rStm >> aVisArea;
            USHORT nUnit;
            rStm >> nUnit;
            SetMapUnit( (MapUnit)nUnit );
        }
    }
}

/*************************************************************************
|*    SvEmbeddedObject::SaveContent()
|*
|*    Beschreibung
*************************************************************************/

static void WriteExtContent( SvStream & rStm, const GDIMetaFile & rMtf,
                             USHORT nAspect, ULONG nAdviseModes )
{
    Impl_OlePres aEle( FORMAT_GDIMETAFILE );
    // Die Groesse in 1/100 mm umrechnen
    // Falls eine nicht anwendbare MapUnit (Device abhaengig) verwendet wird,
    // versucht SV einen BestMatchden richtigen Wert zu raten.
    Size aSize = rMtf.GetPrefSize();
    MapMode aMMSrc = rMtf.GetPrefMapMode();
    MapMode aMMDst( MAP_100TH_MM );
    aSize = OutputDevice::LogicToLogic( aSize, aMMSrc, aMMDst );
    aEle.SetSize( aSize );
     aEle.SetAspect( nAspect );
    aEle.SetAdviseFlags( nAdviseModes );
    aEle.SetMtf( rMtf );
    aEle.Write( rStm );
}


void SvEmbeddedObject::SaveContent( SvStream & rStm, BOOL bOwner_ )
{
    SvPersist::SaveContent( rStm, bOwner_ );
    if( bOwner_ )
    {
        rStm << (BYTE)EMBEDDED_OBJECT_VERSION;
        rStm << GetVisArea();
        rStm << (USHORT)GetMapUnit();
    }
}


BOOL SvEmbeddedObject::MakeContentStream( SotStorage * pStor,
                                          const GDIMetaFile & rMtf )
{
    // MAC MPW mag's sonst nicht ...
    String aPersistStream( String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( SVEXT_PERSIST_STREAM ) ) );
    SotStorageStreamRef xStm = pStor->OpenSotStream( aPersistStream );
    xStm->SetVersion( pStor->GetVersion() );

    xStm->SetBufferSize( 8192 );
    WriteExtContent( *xStm, rMtf, ASPECT_CONTENT, 2 );
    xStm->SetBufferSize( 0 );
    return xStm->GetError() == SVSTREAM_OK;
}

BOOL SvEmbeddedObject::MakeContentStream( SvStorage * pStor,
                                          const GDIMetaFile & rMtf )
{
    return MakeContentStream( (SotStorage *)pStor, rMtf );
}

//=========================================================================
void SvEmbeddedObject::FillClass
(
    SvGlobalName * pClassName,  /* Der Typ der Klasse */
    ULONG * pFormat,            /* Das Dateiformat in dem geschrieben wird */
    String * pAppName,          /* Der Applikationsname */
    String * pFullTypeName,     /* Der genaue Name des Typs */
    String * pShortTypeName,    /* Der kurze Name des Typs  */
    long nFileFormat            /* Fuer dieses Office-Format sollen die
                                   Parameter gefuellt werden */
) const
/*  [Beschreibung]

    Die Methoden <SvPersist::FillClass> und <SvPseudoObject::FillClass>
    setzen nicht alle Parameter. <SvPersist::FillClass> setzt die
    Parameter pClassName und pFormat. <SvPseudoObject::FillClass> setzt
    die restlichen Parmeter.
*/
{
    SvGlobalName    aName;
    ULONG           nFormat;

    SvPersist::FillClass( pClassName, pFormat, pAppName, pFullTypeName,
                            pShortTypeName, nFileFormat );
    SvPseudoObject::FillClass( &aName, &nFormat, pAppName, pFullTypeName,
                                pShortTypeName, nFileFormat );
}

/*************************************************************************
|*    SvEmbeddedObject::FillTransferableObjectDescriptor()
|*
|*    Beschreibung
*************************************************************************/

void SvEmbeddedObject::FillTransferableObjectDescriptor( TransferableObjectDescriptor& rDesc ) const
{
    String aAppName, aShortName;
    ULONG  nClipFormat;

    FillClass( &rDesc.maClassName, &nClipFormat, &aAppName, &rDesc.maTypeName, &aShortName );
    rDesc.mnViewAspect = ASPECT_CONTENT;
    rDesc.mnOle2Misc = GetMiscStatus();
    rDesc.maSize = OutputDevice::LogicToLogic( GetVisArea().GetSize(), GetMapUnit(), MAP_100TH_MM );
    rDesc.maDragStartPos = Point();
    rDesc.maDisplayName = String();
    rDesc.mbCanLink = FALSE;
}

/*************************************************************************
|*    SvEmbeddedObject::SetModified()
|*
|*    Beschreibung
*************************************************************************/
void SvEmbeddedObject::SetModified( BOOL bModifiedP )
{
    ASSERT_INIT()
    SvPersist::SetModified( bModifiedP );

    if( IsEnableSetModified() )
    {
        SvEmbeddedObjectRef xPar = this;

        while( xPar.Is() )
        {
            xPar->SetModifyTime( GetModifyTime() );

            SvPersist * pP = xPar->GetParent();
            xPar = pP;

            // Fuer diesen Fall muss der gesammte Ablauf noch
            // einmal geprueft werden
            DBG_ASSERT( xPar.Is() && pP || !pP && !xPar.Is(),
                        "Persist-Parent ist kein EmbeddedObject" )
        }
    }
}


/*************************************************************************
|*    SvEmbeddedObject::GetMiscStatus()
|*
|*    Beschreibung
*************************************************************************/
ULONG SvEmbeddedObject::GetMiscStatus() const
{
    return SvPseudoObject::GetMiscStatus();
}

//=========================================================================
ErrCode SvEmbeddedObject::DoConnect
(
    SvEmbeddedClient * pClient_ /* Der Client, mit das Objekt verbunden
                                   wird. Darf nicht NULL sein. */
)
/*  [Beschreibung]

    Das Objekt wird mit dem uebergebenen Client verbunden. Die Verbindung
    des Objektes und des Clients wird vorher abgebrochen. Ist der
    uebergebene Client gleich dem Client, der mit dem Objekt verbunden
    ist passiert nichts.

    [Rueckgabewert]

    BOOL        TRUE, Objekt und Client konnten verbunden werden.
                FALSE, beim verbinden wurde DoClose gerufen.

    [Querverweise]

    <SvPseudoObject::DoClose>
*/
{
    DBG_ASSERT( pClient_, "DoConnect( NULL ) not allowed" )

    if( aProt.GetClient() == pClient_ )
        return ERRCODE_NONE;

    SvObjectRef xHoldAlive( this );
    SvObjectRef xHoldAlive1( pClient_ );
    // Client freigeben
    pClient_->aProt.Reset();
    aProt.Reset();

    aProt = SvEditObjectProtocol( this, pClient_ );
    pClient_->aProt = aProt;
    aProt.Connected( TRUE );
    return aProt.IsConnect() ? ERRCODE_NONE : ERRCODE_SO_GENERALERROR;
}

/*************************************************************************
|*    SvEmbeddedObject::DoOpen()
|*
|*    Beschreibung
*************************************************************************/
ErrCode SvEmbeddedObject::DoOpen( BOOL bOpen )
{
    if( !aProt.IsConnect() )
        return ERRCODE_SO_GENERALERROR;
    if( aProt.IsOpen() == bOpen )
        return ERRCODE_NONE;

    SvEmbeddedObjectRef xHoldAliveDuringCall( this );

    if( !bOpen )
        aProt.Reset2Open();


    // Ein Open kommt nicht von Ole2
    // loest eventuell ein Close aus
    // Saved, wenn AutoSave
    aProt.Opened( bOpen );

    return (aProt.IsOpen() == bOpen) ? ERRCODE_NONE : ERRCODE_SO_GENERALERROR;
}

/*************************************************************************
|*    SvEmbeddedObject::DoEmbed()
|*
|*    Beschreibung
*************************************************************************/
ErrCode SvEmbeddedObject::DoEmbed( BOOL bEmbed )
{
    if( aProt.IsEmbed() == bEmbed )
        return ERRCODE_NONE;

    if( !bEmbed )
        aProt.Reset2Embed();

    ErrCode nRet = ERRCODE_NONE;
    if( Owner() )
    {
        if( bEmbed )
            // falls IP-Active
            aProt.Reset2Open();
        aProt.Embedded( bEmbed );
    }

    if( aProt.IsEmbed() != bEmbed && !ERRCODE_TOERROR( nRet ) )
        nRet = ERRCODE_SO_GENERALERROR;
    return nRet;
}

/*************************************************************************
|*    SvEmbeddedObject::Embed()
|*
|*    Beschreibung
*************************************************************************/
#ifdef DBG_UTIL_PROT
void SvEmbeddedObject::Embed( BOOL bEmbed )
#else
void SvEmbeddedObject::Embed( BOOL )
#endif
{
#ifdef DBG_UTIL_PROT
    String aTest( "Object---Embed---" );
    aTest += Owner() ? "Intern" : "Extern: ";
    aTest += bEmbed ? "TRUE" : "FALSE";
    DBG_TRACE( aTest )
#endif
}

//=========================================================================
ErrCode SvEmbeddedObject::DoPlugIn( BOOL bPlugIn )
/*  [Beschreibung]

    [Rueckgabewert]

    BOOL        TRUE, das Objekt ist im PlugIn-Zustand.
                FALSE, das Objekt ist nicht im PlugIn-Zustand.


    [Querverweise]
*/
{
    if( aProt.IsPlugIn() == bPlugIn )
        return ERRCODE_NONE;

    ErrCode nRet = ERRCODE_NONE;
    if( !bPlugIn )
        aProt.Reset2PlugIn();

    if( Owner() )
    {
        if( bPlugIn )
            // falls IP-Active
            aProt.Reset2Open();
        aProt.PlugIn( bPlugIn );
    }

    if( aProt.IsPlugIn() != bPlugIn && !ERRCODE_TOERROR( nRet ) )
        nRet = ERRCODE_SO_GENERALERROR;
    return nRet;
}

//=========================================================================
#ifdef DBG_UTIL_PROT
void SvEmbeddedObject::PlugIn( BOOL bPlugIn )
#else
void SvEmbeddedObject::PlugIn( BOOL )
#endif
{
#ifdef DBG_UTIL_PROT
    String aTest( "Object---PlugIn---" );
    aTest += Owner() ? "Intern" : "Extern: ";
    aTest += bPlugIn ? "TRUE" : "FALSE";
    DBG_TRACE( aTest )
#endif
}

/*************************************************************************
|*    SvEmbeddedObject::DoVerb()
|*
|*    Beschreibung
*************************************************************************/
ErrCode SvEmbeddedObject::DoVerb( long nVerb )
{
    SvEmbeddedClient * pCl = GetClient();
    if( !pCl )
        return DoVerb( nVerb, NULL, NULL, NULL );
    else
    {
        Rectangle aRect, * pRect = NULL;
        SvClientData * pData = pCl->GetClientData();
        Window * pWin = NULL;
        if( pData )
        {
            aRect = pData->GetObjAreaPixel();
            pWin = pData->GetEditWin();
        }
        // nur bei sinnvollen Groessen TRUE
        if( aRect.GetWidth() > 0 && aRect.GetHeight() > 0 )
            pRect = &aRect;

        return DoVerb( nVerb, pCl, pWin, pRect );
    }
}

ErrCode SvEmbeddedObject::DoVerb
(
    long nVerb,
    SvEmbeddedClient * pCallerClient,
    Window * pWin,
    const Rectangle * pWorkRectPixel
)
{
    return SvPseudoObject::DoVerb( nVerb, pCallerClient,
                                    pWin, pWorkRectPixel );
}

/*************************************************************************
|*    SvEmbeddedObject::Verb()
|*
|*    Beschreibung
*************************************************************************/
ErrCode SvEmbeddedObject::Verb
(
    long nVerb,
    SvEmbeddedClient * pCl,
    Window * pWin,
    const Rectangle * pWorkRectPixel
)
{
    ErrCode nRet = ERRCODE_NONE;
    if( Owner() )
    {
        if( nVerb == SVVERB_OPEN )
            nRet = GetProtocol().EmbedProtocol();
        else
            nRet = GetProtocol().PlugInProtocol();
    }
    else
    {
        nRet = SvPseudoObject::Verb( nVerb, pCl, pWin, pWorkRectPixel );
    }
    return nRet;
}

/*************************************************************************
|*    SvEmbeddedObject::SetDocumentName()
|*
|*    Beschreibung
*************************************************************************/
void SvEmbeddedObject::SetDocumentName( const String & rName )
{
    aDocName = rName;
    GetProtocol().DocNameChanged( rName );
}

/*************************************************************************
|*    SvEmbeddedObject::DocumentNameChanged()
|*
|*    Beschreibung
*************************************************************************/
void SvEmbeddedObject::DocumentNameChanged( const String & /*rDocName*/ )
{
}

//=========================================================================
// locker die Struktur von Windows kopiert
struct MY_GUID
{
    UINT32 Data1;
    UINT16 Data2;
    UINT16 Data3;
    BYTE   Data4[8];
};

void SvEmbeddedObject::Connect
(
    BOOL bConnect   /* TRUE, connect. FALSE, disconnect */
)
/*  [Beschreibung]

    Ist bConnect == TRUE, dann wurde das Objekt mit einem
    <SvEmbeddedClient> verbunden. Diesen kann man mit
    <SvEmbeddedObject::GetClient> erfragen.
    Ist bConnect == TRUE, dann wurde das Objekt von dem Client getrennt,
    mit dem es vorher verbunden war.

    [Querverweise]

    <SvPseudoObject::DoClose>, <SvEmbeddedObject::DoConnect>
*/
{
    if( Owner() )
    {
        SvEmbeddedObjectRef xCont = GetClient()->GetContainer();
        // Owner muss abgefragt werden, da Ole2 sonst streikt
        if( xCont.Is() && xCont->Owner() )
            xCont->Lock( bConnect );
    }
}

/*************************************************************************
|*    SvEmbeddedObject::Close()
|*
|*    Beschreibung: Close darf mehrmals gerufen werden
*************************************************************************/
BOOL SvEmbeddedObject::Close()
{
    const SvInfoObjectMemberList * pChildList_ = GetObjectList();
    if( pChildList_ )
    {
        ULONG nCount = pChildList_->Count();
        for( ULONG i = 0; i < nCount; i++ )
        {
            SvInfoObject * pIO = pChildList_->GetObject( i );
            SvPersist * pPer = pIO->GetPersist();
            SvEmbeddedObjectRef xEO( pPer );
            if( xEO.Is() )
                xEO->DoClose();
        }
    }

    // Unter Ole2 muss Close() vor SetClientSite( NULL ) gerufen werden.
    aProt.Reset2Connect();
    SvPseudoObject::Close();
    // Jetzt SetClientSite( NULL ).
    aProt.Reset();
    return TRUE;
}

/*************************************************************************
|*    SvEmbeddedObject::Open()
|*
|*    Beschreibung
*************************************************************************/
void SvEmbeddedObject::Open( BOOL bOpen )
{
#ifdef DBG_UTIL_PROT
    String aTest( "Object---Open---" );
    aTest += Owner() ? "Intern" : "Extern: ";
    aTest += bOpen ? "TRUE" : "FALSE";
    DBG_TRACE( aTest )
#endif

    SendViewChanged();
    // kein Autosave im HandsOff State
    if( bAutoSave && !bOpen && !IsHandsOff())
    {
        SvEmbeddedClient * pCl = GetClient();
        if( pCl )
            pCl->SaveObject();
    }

}





/*************************************************************************
|*    SvEmbeddedObject::SetGetVisArea()
|*
|*    Beschreibung
*************************************************************************/
const Rectangle & SvEmbeddedObject::SetGetVisArea( const Rectangle & rArea )
{
    // nicht auf Gleichheit optimieren, da der Server sie jederzeit
    // modifizieren darf
    if( Owner() )
        // muss, weil SetVisArea ist virtuell ist
        SetVisArea( rArea );
    return aVisArea;
}

/*************************************************************************
|*    SvEmbeddedObject::SetVisArea()
|*    SvEmbeddedObject::GetVisArea()
|*
|*    Beschreibung
*************************************************************************/
void SvEmbeddedObject::SetVisArea( const Rectangle & rArea )
{
    if( Owner() )
        aVisArea = rArea;
    else
        SetGetVisArea( rArea );
}

void SvEmbeddedObject::SetVisAreaSize( const Size & rSize )
{
    SetVisArea( Rectangle( GetVisArea().TopLeft(), rSize ) );
}

Rectangle SvEmbeddedObject::GetVisArea( USHORT nAspect ) const
{
    if( nAspect == ASPECT_CONTENT )
        return aVisArea;
    else if( nAspect == ASPECT_THUMBNAIL )
    {
        Rectangle aRect;
        aRect.SetSize( OutputDevice::LogicToLogic( Size( 5000, 5000 ),
                                         MAP_100TH_MM, GetMapUnit() ) );
        return aRect;
    }
    return Rectangle();
}

const Rectangle & SvEmbeddedObject::GetVisArea() const
{
    ((SvEmbeddedObject *)this)->aVisArea = GetVisArea( ASPECT_CONTENT );
    return aVisArea;
}

UINT32 SvEmbeddedObject::GetViewAspect() const
{
    return ASPECT_CONTENT;
}

/*************************************************************************
|*    SvEmbeddedObject::DrawHatch()
|*
|*    Beschreibung
*************************************************************************/
void SvEmbeddedObject::DrawHatch( OutputDevice * pDev, const Point & rViewPos,
                               const Size &rSize )
{
    GDIMetaFile * pMtf = pDev->GetConnectMetaFile();
    if( pMtf && pMtf->IsRecord() )
        return;

    SvEmbeddedClient * pCl = GetClient();
    if( pCl && pCl->Owner() && bAutoHatch
      && pDev->GetOutDevType() == OUTDEV_WINDOW
      && GetProtocol().IsEmbed() )
    {
        pDev->Push();
        pDev->SetLineColor( Color( COL_BLACK ) );

        Size aPixSize = pDev->LogicToPixel( rSize );
        aPixSize.Width() -= 1;
        aPixSize.Height() -= 1;
        Point aPixViewPos = pDev->LogicToPixel( rViewPos );
        INT32 nMax = aPixSize.Width() + aPixSize.Height();
        for( INT32 i = 5; i < nMax; i += 5 )
        {
            Point a1( aPixViewPos ), a2( aPixViewPos );
            if( i > aPixSize.Width() )
                a1 += Point( aPixSize.Width(), i - aPixSize.Width() );
            else
                a1 += Point( i, 0 );
            if( i > aPixSize.Height() )
                a2 += Point( i - aPixSize.Height(), aPixSize.Height() );
            else
                a2 += Point( 0, i );

            pDev->DrawLine( pDev->PixelToLogic( a1 ), pDev->PixelToLogic( a2 ) );
        }
        pDev->Pop();
    }
}


/*************************************************************************
|*    SvEmbeddedObject::DoDraw()
|*
|*    Beschreibung
*************************************************************************/
void SvEmbeddedObject::DoDraw( OutputDevice * pDev, const Point & rViewPos,
                               const Size &rSize,
                               const JobSetup & rSetup, USHORT nAspect )
{
    if( Owner() )
    {
        MapMode aMod = pDev->GetMapMode();
        Size aSize = GetVisArea( nAspect ).GetSize();
        MapMode aWilliMode( GetMapUnit() );
        aSize = pDev->LogicToLogic( aSize, &aWilliMode, &aMod );
        if( aSize.Width() && aSize.Height() )
        {
            Fraction aXF( rSize.Width(), aSize.Width() );
            Fraction aYF( rSize.Height(), aSize.Height() );

            Point aOrg = rViewPos;
            aMod.SetMapUnit( MAP_100TH_MM );
            aSize = pDev->LogicToLogic( GetVisArea( nAspect ).GetSize(), &aMod, &aWilliMode );
            DoDraw( pDev, aOrg, aXF, aYF, rSetup, aSize, nAspect );
        }
    }
}

/*************************************************************************
|*    SvEmbeddedObject::DoDraw()
|*
|*    Beschreibung
*************************************************************************/
void SvEmbeddedObject::DoDraw( OutputDevice * pDev, const Point & rViewPos,
                               const Fraction & rScaleX,
                               const Fraction & rScaleY,
                               const JobSetup & rSetup, const Size& rSize,
                               USHORT nAspect )
{
    Rectangle aVisArea_  = GetVisArea( nAspect );
    // MapUnit des Ziels
    MapMode aMapMode( GetMapUnit() );
    aMapMode.SetScaleX( rScaleX );
    aMapMode.SetScaleY( rScaleY );

    if( Owner() )
    {
        // Ziel in Pixel
        Point aOrg   = pDev->LogicToLogic( rViewPos, NULL, &aMapMode );
        Point aDelta = aOrg - aVisArea_.TopLeft();

        // Origin entsprechend zum sichtbaren Bereich verschieben
        // Origin mit Scale setzen
        aMapMode.SetOrigin( aDelta );

        // Deviceeinstellungen sichern
        pDev->Push();

        Region aRegion;
        if( pDev->IsClipRegion() && pDev->GetOutDevType() != OUTDEV_PRINTER )
        {
            aRegion = pDev->GetClipRegion();
            aRegion = pDev->LogicToPixel( aRegion );
        }
        pDev->SetRelativeMapMode( aMapMode );

        GDIMetaFile * pMtf = pDev->GetConnectMetaFile();
        if( pMtf )
            if( pMtf->IsRecord() && pDev->GetOutDevType() != OUTDEV_PRINTER )
                pMtf->Stop();
            else
                pMtf = NULL;
// #ifndef UNX
        if( pDev->IsClipRegion() && pDev->GetOutDevType() != OUTDEV_PRINTER )
// #endif
        {
            aRegion = pDev->PixelToLogic( aRegion );
            pDev->SetClipRegion( aRegion );
        }
        if( pMtf )
            pMtf->Record( pDev );

        SvOutPlaceObjectRef xOutRef( this );
        if ( xOutRef.Is() )
            xOutRef->DrawObject( pDev, rSetup, rSize, nAspect );
        else
            Draw( pDev, rSetup, nAspect );
        DrawHatch( pDev, aVisArea_.TopLeft(), aVisArea_.GetSize() );

        // Deviceeinstellungen wieder herstellen
        pDev->Pop();
    }
    else
    {
        Size aSize = aVisArea_.GetSize();
        pDev->LogicToLogic( rViewPos, NULL, &aMapMode );
        DoDraw( pDev, rViewPos, aSize, rSetup, nAspect );
    }
}

/*************************************************************************
|*    SvEmbeddedObject::Draw()
|*
|*    Beschreibung
*************************************************************************/
void SvEmbeddedObject::Draw( OutputDevice * /*pDev*/,
                             const JobSetup & /*rSetup*/, USHORT /*nAspect*/ )
{
}

/*************************************************************************
|*    SvEmbeddedObject::GetDocumentPrinter()
|*
|*    Beschreibung:
*************************************************************************/
Printer *   SvEmbeddedObject::GetDocumentPrinter()
{
    SvEmbeddedObjectRef xParent( GetParent() );
    if( xParent.Is() )
        return xParent->GetDocumentPrinter();
    return NULL;
}

/*************************************************************************
|*    SvEmbeddedObject::GetDocumentRefDev()
|*
|*    Beschreibung:
*************************************************************************/
OutputDevice*   SvEmbeddedObject::GetDocumentRefDev()
{
    SvEmbeddedObjectRef xParent( GetParent() );
    if( xParent.Is() )
        return xParent->GetDocumentRefDev();
    return NULL;
}

/*************************************************************************
|*    SvEmbeddedObject::ConvertToOle1()
|*
|*    Beschreibung:
*************************************************************************/
struct ClsIDs {
    UINT32      nId;
    const sal_Char* pSvrName;
    const sal_Char* pDspName;
};
static ClsIDs aClsIDs[] = {

    { 0x000212F0, "MSWordArt",          "Microsoft Word Art"            },
    { 0x000212F0, "MSWordArt.2",        "Microsoft Word Art 2.0"        },

    // MS Apps
    { 0x00030000, "ExcelWorksheet",     "Microsoft Excel Worksheet"     },
    { 0x00030001, "ExcelChart",         "Microsoft Excel Chart"         },
    { 0x00030002, "ExcelMacrosheet",    "Microsoft Excel Macro"         },
    { 0x00030003, "WordDocument",       "Microsoft Word Document"       },
    { 0x00030004, "MSPowerPoint",       "Microsoft PowerPoint"          },
    { 0x00030005, "MSPowerPointSho",    "Microsoft PowerPoint Slide Show"},
    { 0x00030006, "MSGraph",            "Microsoft Graph"               },
    { 0x00030007, "MSDraw",             "Microsoft Draw"                },
    { 0x00030008, "Note-It",            "Microsoft Note-It"             },
    { 0x00030009, "WordArt",            "Microsoft Word Art"            },
    { 0x0003000a, "PBrush",             "Microsoft PaintBrush Picture"  },
    { 0x0003000b, "Equation",           "Microsoft Equation Editor"     },
    { 0x0003000c, "Package",            "Package"                       },
    { 0x0003000d, "SoundRec",           "Sound"                         },
    { 0x0003000e, "MPlayer",            "Media Player"                  },
    // MS Demos
    { 0x0003000f, "ServerDemo",         "OLE 1.0 Server Demo"           },
    { 0x00030010, "Srtest",             "OLE 1.0 Test Demo"             },
    { 0x00030011, "SrtInv",             "OLE 1.0 Inv Demo"              },
    { 0x00030012, "OleDemo",            "OLE 1.0 Demo"                  },

    // Coromandel / Dorai Swamy / 718-793-7963
    { 0x00030013, "CoromandelIntegra",  "Coromandel Integra"            },
    { 0x00030014, "CoromandelObjServer","Coromandel Object Server"      },

    // 3-d Visions Corp / Peter Hirsch / 310-325-1339
    { 0x00030015, "StanfordGraphics",   "Stanford Graphics"             },

    // Deltapoint / Nigel Hearne / 408-648-4000
    { 0x00030016, "DGraphCHART",        "DeltaPoint Graph Chart"        },
    { 0x00030017, "DGraphDATA",         "DeltaPoint Graph Data"         },

    // Corel / Richard V. Woodend / 613-728-8200 x1153
    { 0x00030018, "PhotoPaint",         "Corel PhotoPaint"              },
    { 0x00030019, "CShow",              "Corel Show"                    },
    { 0x0003001a, "CorelChart",         "Corel Chart"                   },
    { 0x0003001b, "CDraw",              "Corel Draw"                    },

    // Inset Systems / Mark Skiba / 203-740-2400
    { 0x0003001c, "HJWIN1.0",           "Inset Systems"                 },

    // Mark V Systems / Mark McGraw / 818-995-7671
    { 0x0003001d, "ObjMakerOLE",        "MarkV Systems Object Maker"    },

    // IdentiTech / Mike Gilger / 407-951-9503
    { 0x0003001e, "FYI",                "IdentiTech FYI"                },
    { 0x0003001f, "FYIView",            "IdentiTech FYI Viewer"         },

    // Inventa Corporation / Balaji Varadarajan / 408-987-0220
    { 0x00030020, "Stickynote",         "Inventa Sticky Note"           },

    // ShapeWare Corp. / Lori Pearce / 206-467-6723
    { 0x00030021, "ShapewareVISIO10",   "Shapeware Visio 1.0"           },
    { 0x00030022, "ImportServer",       "Spaheware Import Server"       },

    // test app SrTest
    { 0x00030023, "SrvrTest",           "OLE 1.0 Server Test"           },

    // test app ClTest.  Doesn't really work as a server but is in reg db
    { 0x00030025, "Cltest",             "OLE 1.0 Client Test"           },

    // Microsoft ClipArt Gallery   Sherry Larsen-Holmes
    { 0x00030026, "MS_ClipArt_Gallery", "Microsoft ClipArt Gallery"     },
    // Microsoft Project  Cory Reina
    { 0x00030027, "MSProject",          "Microsoft Project"             },

    // Microsoft Works Chart
    { 0x00030028, "MSWorksChart",       "Microsoft Works Chart"         },

    // Microsoft Works Spreadsheet
    { 0x00030029, "MSWorksSpreadsheet", "Microsoft Works Spreadsheet"   },

    // AFX apps - Dean McCrory
    { 0x0003002A, "MinSvr",             "AFX Mini Server"               },
    { 0x0003002B, "HierarchyList",      "AFX Hierarchy List"            },
    { 0x0003002C, "BibRef",             "AFX BibRef"                    },
    { 0x0003002D, "MinSvrMI",           "AFX Mini Server MI"            },
    { 0x0003002E, "TestServ",           "AFX Test Server"               },

    // Ami Pro
    { 0x0003002F, "AmiProDocument",     "Ami Pro Document"              },

    // WordPerfect Presentations For Windows
    { 0x00030030, "WPGraphics",         "WordPerfect Presentation"      },
    { 0x00030031, "WPCharts",           "WordPerfect Chart"             },

    // MicroGrafx Charisma
    { 0x00030032, "Charisma",           "MicroGrafx Charisma"           },
    { 0x00030033, "Charisma_30",        "MicroGrafx Charisma 3.0"       },
    { 0x00030034, "CharPres_30",        "MicroGrafx Charisma 3.0 Pres"  },
    // MicroGrafx Draw
    { 0x00030035, "Draw",               "MicroGrafx Draw"               },
    // MicroGrafx Designer
    { 0x00030036, "Designer_40",        "MicroGrafx Designer 4.0"       },

    // STAR DIVISION
//  { 0x000424CA, "StarMath",           "StarMath 1.0"                  },
    { 0x00043AD2, "FontWork",           "Star FontWork"                 },
//  { 0x000456EE, "StarMath2",          "StarMath 2.0"                  },

    { 0, "", "" } };

/*
class Ole1Convert
{
    virtual DWORD FAR PASCAL Ole1_Get( void * pBuf, DWORD nSize );
    virtual DWORD FAR PASCAL Ole1_Put( const void * pBuf, DWORD nSize );
    SvStream &  rStm;
public:
    Ole1Convert( SvStream & rStmPar )
        : rStm( rStmPar )
    {
    }
};

DWORD Ole1Convert::Ole1_Get( void * pBuf, DWORD nSize )
{
    return rStm.Read( pBuf, nSize );
}

DWORD Ole1Convert::Ole1_Put( const void * pBuf, DWORD nSize )
{
    return rStm.Write( pBuf, nSize );
}
*/
BOOL SvEmbeddedObject::ConvertToOle2( SvStream& rStm, UINT32 nReadLen,
                    const GDIMetaFile * pMtf, const SotStorageRef& rDest )
{
    BOOL bMtfRead = FALSE;
    SotStorageStreamRef xOle10Stm = rDest->OpenSotStream( String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "\1Ole10Native" ) ),
                                                    STREAM_WRITE| STREAM_SHARE_DENYALL );
    if( xOle10Stm->GetError() )
        return FALSE;

    UINT32 nType;
    UINT32 nRecType;
    UINT32 nStrLen;
    String aSvrName;
    UINT32 nDummy0;
    UINT32 nDummy1;
    UINT32 nDataLen;
    BYTE*  pData;
    UINT32 nBytesRead = 0;
    do
    {
        rStm >> nType;
        rStm >> nRecType;
        rStm >> nStrLen;
        if( nStrLen )
        {
            if( 0x10000L > nStrLen )
            {
                sal_Char * pBuf = new sal_Char[ nStrLen ];
                rStm.Read( pBuf, nStrLen );
                aSvrName.Assign( String( pBuf, sal::static_int_cast< xub_StrLen >(nStrLen-1), gsl_getSystemTextEncoding() ) );
                delete[] pBuf;
            }
            else
                break;
        }
        rStm >> nDummy0;
        rStm >> nDummy1;
        rStm >> nDataLen;

        nBytesRead += 6 * sizeof( UINT32 ) + nStrLen + nDataLen;

        if( !rStm.IsEof() && nReadLen > nBytesRead && nDataLen )
        {
            if( xOle10Stm.Is() )
            {
                pData = new BYTE[ nDataLen ];
                if( !pData )
                    return FALSE;

                rStm.Read( pData, nDataLen );

                // write to ole10 stream
                *xOle10Stm << nDataLen;
                xOle10Stm->Write( pData, nDataLen );
                xOle10Stm = SotStorageStreamRef();

                // set the compobj stream
                ClsIDs* pIds;
                for( pIds = aClsIDs; pIds->nId; pIds++ )
                {
                    if( COMPARE_EQUAL == aSvrName.CompareToAscii( pIds->pSvrName ) )
                        break;
                }
                String aShort, aFull;
                if( pIds->nId )
                {
                    // gefunden!
                    ULONG nCbFmt = SotExchange::RegisterFormatName( aSvrName );
                    rDest->SetClass( SvGlobalName( pIds->nId, 0, 0, 0xc0,0,0,0,0,0,0,0x46 ), nCbFmt,
                                    String( pIds->pDspName, RTL_TEXTENCODING_ASCII_US ) );
                }
                else
                {
                    ULONG nCbFmt = SotExchange::RegisterFormatName( aSvrName );
                    rDest->SetClass( SvGlobalName(), nCbFmt, aSvrName );
                }

                delete[] pData;
            }
            else if( nRecType == 5 && !pMtf )
            {
                ULONG nPos = rStm.Tell();
                UINT16 sz[4];
                rStm.Read( sz, 8 );
                //rStm.SeekRel( 8 );
                Graphic aGraphic;
                if( ERRCODE_NONE == GraphicConverter::Import( rStm, aGraphic ) && aGraphic.GetType() )
                {
                    const GDIMetaFile& rMtf = aGraphic.GetGDIMetaFile();
                    MakeContentStream( rDest, rMtf );
                    bMtfRead = TRUE;
                }
                // set behind the data
                rStm.Seek( nPos + nDataLen );
            }
            else
                rStm.SeekRel( nDataLen );
        }
    } while( !rStm.IsEof() && nReadLen >= nBytesRead );

    if( !bMtfRead && pMtf )
    {
        MakeContentStream( rDest, *pMtf );
        return TRUE;
    }
    return FALSE;
}

/*************************************************************************
|*    SvEmbeddedObject::OnDocumentPrinterChanged()
|*
|*    Beschreibung: An allen Child-Objekten sollte diese Methode gerufen
                    werden, wenn im Dokument der Drucker gewechselt wird und
                    sie das Flag SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE ueber die
                    Methode GetMiscStatus() liefern.
                    Bevor der Container am Child diese Methode ruft,
                    muss er einen Client angemeldet und geoeffnet haben.
                    Dies tut er mit dem folgenden Codefragment.

                    if( xChildObj->GetMiscStatus() & SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE )
                    {
                        // Client erzeugen
                        SvEmbeddedClientRef xClient = new MyClient( ... );
                        // Client und ChildObj verbinden
                        xChildObj->DoConnect( xClient );
                        // Verbindung oeffnen, es wird ein ViewAdvise angemeldet
                        xChildObj->DoOpen( TRUE );
                        // Die Druckeraenderung melden
                        xChildObj->OnDocumentPrinterChanged( pNewPrinter );
                        ...

                    Wenn die VisArea aufgrund der Printer-Aenderung
                    angepasst wird, dann muss das ChildObj diese Aenderung melden. Da
                    sich sowohl seine Daten (VisArea), als auch seine Darstellung
                    geaendert hat, muessen folgen Methoden gerufen werden.

                    SvData aData;
                    // Alle anliegenden Aenderungen der Daten werden sofort (synchron) abgeschickt
                    SendDataChanged( aData );
                    // Alle Aenderungen der View werden synchron an den Client gemeldet.
                    SendViewChanged();

                    Auf der Client-Seite ist die ViewChanged-Benachrichtigung ueberladen,
                    sodass die Groesse angepasst wird.

|*      Anmerkung:  SendDataChanged und SendViewChanged senden nur, wenn vorher die Methoden
|*                  ViewChanged und DataChanged Aenderungen angemeldet haben. Dies sollte aber
|*                  durch umsetzen der VisArea und den dadurch notwendigen Aenderungen
|*                  automatisch passieren. In so3 passiert in dieser Hinsicht nichts
|*                  automatisch!!!
|*
*************************************************************************/
void SvEmbeddedObject::OnDocumentPrinterChanged( Printer * )
{
    /*
    const SvInfoObjectMemberList * pChildList = GetObjectList();
    if( pChildList )
    {
        ULONG nCount = pChildList->Count();
        for( ULONG i = 0; i < nCount; i++ )
        {
            SvInfoObject * pIO = pChildList->GetObject( i );
            SvEmbeddedObjectRef xEO( pIO->GetPersist() );
            if( xEO.Is() && (xEO->GetMiscStatus() & SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE) )
                xEO->OnDocumentPrinterChanged( pPrt );
        }
    }
    */
}

