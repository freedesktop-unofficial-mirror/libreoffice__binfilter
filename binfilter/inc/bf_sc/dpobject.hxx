/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: dpobject.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:34:04 $
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

#ifndef SC_DPOBJECT_HXX
#define SC_DPOBJECT_HXX

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif

#ifndef SC_COLLECT_HXX
#include "collect.hxx"
#endif

#ifndef _COM_SUN_STAR_SHEET_XDIMENSIONSSUPPLIER_HPP_
#include <com/sun/star/sheet/XDimensionsSupplier.hpp>
#endif
class Rectangle;
class SvStream;
namespace binfilter {


//------------------------------------------------------------------


class ScDPSaveData;
class ScDPOutput;
struct ScDPPositionData;
class ScMultipleReadHeader;
class ScMultipleWriteHeader;
class ScPivot;
class ScPivotCollection;
struct ScPivotParam;
struct ScImportSourceDesc;
struct ScSheetSourceDesc;


struct ScDPServiceDesc
{
    String  aServiceName;
    String  aParSource;
    String  aParName;
    String  aParUser;
    String  aParPass;

    ScDPServiceDesc( const String& rServ, const String& rSrc, const String& rNam,
                        const String& rUser, const String& rPass ) :
        aServiceName( rServ ), aParSource( rSrc ), aParName( rNam ),
        aParUser( rUser ), aParPass( rPass ) {  }

    BOOL operator== ( const ScDPServiceDesc& rOther ) const
        { return aServiceName == rOther.aServiceName &&
                 aParSource   == rOther.aParSource &&
                 aParName     == rOther.aParName &&
                 aParUser     == rOther.aParUser &&
                 aParPass     == rOther.aParPass; }
};


class ScDPObject : public DataObject
{
private:
    ScDocument*             pDoc;
                                            // settings
    ScDPSaveData*           pSaveData;
    String                  aTableName;
    String                  aTableTag;
    ScRange                 aOutRange;
    ScSheetSourceDesc*      pSheetDesc;     //  for sheet data
    ScImportSourceDesc*     pImpDesc;       //  for database data
    ScDPServiceDesc*        pServDesc;      //  for external service
                                            // cached data
    ::com::sun::star::uno::Reference< ::com::sun::star::sheet::XDimensionsSupplier> xSource;
    ScDPOutput*             pOutput;
    BOOL                    bSettingsChanged;
    BOOL                    bAlive;         // FALSE if only used to hold settings


    void                CreateObjects();

public:
                ScDPObject( ScDocument* pD );
                ScDPObject(const ScDPObject& r);
    virtual     ~ScDPObject();

    virtual DataObject* Clone() const;

    void                SetAlive(BOOL bSet);

    void                InvalidateData();
    void                InvalidateSource();


    void                SetSaveData(const ScDPSaveData& rData);
    ScDPSaveData*       GetSaveData() const     { return pSaveData; }

    void                SetOutRange(const ScRange& rRange);
    const ScRange&      GetOutRange() const     { return aOutRange; }

    void                SetSheetDesc(const ScSheetSourceDesc& rDesc);
    void                SetImportDesc(const ScImportSourceDesc& rDesc);
    void                SetServiceData(const ScDPServiceDesc& rDesc);


    const ScSheetSourceDesc* GetSheetDesc() const   { return pSheetDesc; }
    const ScImportSourceDesc* GetImportSourceDesc() const   { return pImpDesc; }
    const ScDPServiceDesc* GetDPServiceDesc() const { return pServDesc; }


    BOOL                IsSheetData() const;
    BOOL                IsImportData() const { return(pImpDesc != NULL); }
    BOOL                IsServiceData() const { return(pServDesc != NULL); }

    void                SetName(const String& rNew);
    const String&       GetName() const                 { return aTableName; }
    void                SetTag(const String& rNew);
    const String&       GetTag() const                  { return aTableTag; }



    BOOL                StoreOld(SvStream& rStream, ScMultipleWriteHeader& rHdr ) const;
    BOOL                StoreNew(SvStream& rStream, ScMultipleWriteHeader& rHdr ) const;
    BOOL                LoadNew(SvStream& rStream, ScMultipleReadHeader& rHdr );
    BOOL                FillOldParam(ScPivotParam& rParam, BOOL bForFile) const;
    void                InitFromOldPivot(const ScPivot& rOld, ScDocument* pDoc, BOOL bSetSource);

    void                UpdateReference( UpdateRefMode eUpdateRefMode,
                                          const ScRange& r, short nDx, short nDy, short nDz );
    BOOL                RefsEqual( const ScDPObject& r ) const;
    void                WriteRefsTo( ScDPObject& r ) const;


    static void         ConvertOrientation( ScDPSaveData& rSaveData,
                            PivotField* pFields, USHORT nCount, USHORT nOrient,
                            ScDocument* pDoc, USHORT nRow, USHORT nTab,
                            const ::com::sun::star::uno::Reference<
                                ::com::sun::star::sheet::XDimensionsSupplier>& xSource,
                            BOOL bOldDefaults,
                            PivotField* pRefColFields = NULL, USHORT nRefColCount = 0,
                            PivotField* pRefRowFields = NULL, USHORT nRefRowCount = 0 );
};


class ScDPCollection : public Collection
{
private:
    ScDocument* pDoc;

public:
                ScDPCollection(ScDocument* pDocument);
                ScDPCollection(const ScDPCollection& r);
    virtual     ~ScDPCollection();

    virtual DataObject* Clone() const;

    ScDPObject* operator[](USHORT nIndex) const {return (ScDPObject*)At(nIndex);}

    BOOL        StoreOld( SvStream& rStream ) const;
    BOOL        StoreNew( SvStream& rStream ) const;
    BOOL        LoadNew( SvStream& rStream );

    void        ConvertOldTables( ScPivotCollection& rOldColl );

    void        UpdateReference( UpdateRefMode eUpdateRefMode,
                                 const ScRange& r, short nDx, short nDy, short nDz );

    BOOL        RefsEqual( const ScDPCollection& r ) const;
    void        WriteRefsTo( ScDPCollection& r ) const;

    String      CreateNewName( USHORT nMin = 1 ) const;
    void        EnsureNames();
};


} //namespace binfilter
#endif

