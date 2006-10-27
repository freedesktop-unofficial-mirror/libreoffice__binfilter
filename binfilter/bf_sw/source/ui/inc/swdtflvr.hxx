/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: swdtflvr.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 00:54:33 $
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
#ifndef _SWDTFLVR_HXX
#define _SWDTFLVR_HXX

#ifndef _TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif
#ifndef _EMBOBJ_HXX
#include <so3/embobj.hxx>
#endif
#ifndef _LNKBASE_HXX
#include <so3/lnkbase.hxx>
#endif
class Graphic;
class ImageMap;
namespace binfilter {



class INetBookmark;
class INetImage;
class SwDoc;
class SwDocFac;
class SwNode;
class SwTextBlocks;
class SwWrtShell;
class Reader;
class SvxClipboardFmtItem;
class ViewShell;
class SwView_Impl;

enum TransferBufferType
{
    TRNSFR_NONE             = 0x0000,
    TRNSFR_DOCUMENT         = 0x0001,
    TRNSFR_DOCUMENT_WORD    = 0x0002,
    TRNSFR_GRAPHIC          = 0x0004,
    TRNSFR_TABELLE          = 0x0008,
    TRNSFR_DDELINK          = 0x0010,
    TRNSFR_OLE              = 0x0020,
    TRNSFR_INETFLD          = 0x0040,
    TRNSFR_DRAWING          = 0x0081    //Drawing ist auch intern!
};

#define DATA_FLAVOR     ::com::sun::star::datatransfer::DataFlavor

class SwTransferable : public TransferableHelper
{
    friend class SwView_Impl;
    SvEmbeddedObjectRef             aDocShellRef;
    TransferableDataHelper          aOleData;
    TransferableObjectDescriptor    aObjDesc;
    ::so3::SvBaseLinkRef            refDdeLink;

    SwWrtShell      *pWrtShell;
    /* #96392# Added pCreatorView to distinguish SwFrameShell from
       SwWrtShell. */
    const ViewShell       *pCreatorView;
    SwDocFac        *pClpDocFac;
    Graphic         *pClpGraphic, *pClpBitmap, *pOrigGrf;
    INetBookmark    *pBkmk;     // URL und Beschreibung!
    ImageMap        *pImageMap;
    INetImage       *pTargetURL;

    TransferBufferType eBufferType;

    BOOL bOldIdle   :1; //D&D Idle flag from the viewsettings
    BOOL bCleanUp   :1; //D&D cleanup after Drop (not by internal Drop)

    // helper methods for the copy

    // helper methods for the paste
    static int _TestAllowedFormat( const TransferableDataHelper& rData,
                                        ULONG nFormat, USHORT nDestination );












                                    // not available

protected:

public:

    static USHORT GetSotDestination( const SwWrtShell& rSh, const Point* = 0 );

    // set properties on the document, like PageMargin, VisArea.
    // And set real Size
    static void InitOle( SvEmbeddedObjectRef rRef, SwDoc& rDoc );

    // copy - methods and helper methods for the copy

    // remove the DDE-Link format promise

    // paste - methods and helper methods for the paste
    static BOOL IsPaste( const SwWrtShell&, const TransferableDataHelper& );

    static BOOL IsPasteSpecial( const SwWrtShell& rWrtShell,
                                const TransferableDataHelper& );

    static void FillClipFmtItem( const SwWrtShell& rSh,
                                const TransferableDataHelper& rData,
                                SvxClipboardFmtItem & rToFill );

    // Interfaces for Drag & Drop

    // Interfaces for Selection
    /* #96392# Added pCreator to distinguish SwFrameShell from SwWrtShell. */
    static void ClearSelection( SwWrtShell& rSh,
                                const ViewShell * pCreator = NULL );

    // the related SwView is being closed and the SwTransferable is invalid now
    void    Invalidate() {pWrtShell = 0;}
    static const ::com::sun::star::uno::Sequence< sal_Int8 >& getUnoTunnelId();

    virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& rId ) throw( ::com::sun::star::uno::RuntimeException );
};


} //namespace binfilter
#endif
