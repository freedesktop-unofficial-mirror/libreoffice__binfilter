/*************************************************************************
 *
 *  $RCSfile: dpobject.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:59:44 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
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
//STRIP001  void                CreateOutput();

public:
                ScDPObject( ScDocument* pD );
                ScDPObject(const ScDPObject& r);
    virtual     ~ScDPObject();

    virtual DataObject* Clone() const;

    void                SetAlive(BOOL bSet);

    void                InvalidateData();
    void                InvalidateSource();

//STRIP001  void                Output();
//STRIP001  ScRange             GetNewOutputRange( BOOL& rOverflow );

    void                SetSaveData(const ScDPSaveData& rData);
    ScDPSaveData*       GetSaveData() const     { return pSaveData; }

    void                SetOutRange(const ScRange& rRange);
    const ScRange&      GetOutRange() const     { return aOutRange; }

    void                SetSheetDesc(const ScSheetSourceDesc& rDesc);
    void                SetImportDesc(const ScImportSourceDesc& rDesc);
    void                SetServiceData(const ScDPServiceDesc& rDesc);

//STRIP001  void                WriteSourceDataTo( ScDPObject& rDest ) const;

    const ScSheetSourceDesc* GetSheetDesc() const   { return pSheetDesc; }
    const ScImportSourceDesc* GetImportSourceDesc() const   { return pImpDesc; }
    const ScDPServiceDesc* GetDPServiceDesc() const { return pServDesc; }

//STRIP001  ::com::sun::star::uno::Reference< ::com::sun::star::sheet::XDimensionsSupplier> GetSource();

    BOOL                IsSheetData() const;
    BOOL                IsImportData() const { return(pImpDesc != NULL); }
    BOOL                IsServiceData() const { return(pServDesc != NULL); }

    void                SetName(const String& rNew);
    const String&       GetName() const                 { return aTableName; }
    void                SetTag(const String& rNew);
    const String&       GetTag() const                  { return aTableTag; }

//STRIP001  String              GetDimName( long nDim, BOOL& rIsDataLayout );
//STRIP001  void                GetPositionData( ScDPPositionData& rData, const ScAddress& rPos );
//STRIP001  long                GetHeaderDim( const ScAddress& rPos );
//STRIP001  BOOL                GetHeaderDrag( const ScAddress& rPos, BOOL bMouseLeft, BOOL bMouseTop,
//STRIP001                                      long nDragDim,
//STRIP001                                      Rectangle& rPosRect, USHORT& rOrient, long& rDimPos );
//STRIP001  BOOL                IsFilterButton( const ScAddress& rPos );

//STRIP001  void                ToggleDetails( ScDPPositionData& rElemDesc, ScDPObject* pDestObj );

    BOOL                StoreOld(SvStream& rStream, ScMultipleWriteHeader& rHdr ) const;
    BOOL                StoreNew(SvStream& rStream, ScMultipleWriteHeader& rHdr ) const;
    BOOL                LoadNew(SvStream& rStream, ScMultipleReadHeader& rHdr );
    BOOL                FillOldParam(ScPivotParam& rParam, BOOL bForFile) const;
//STRIP001  BOOL                FillLabelData(ScPivotParam& rParam, BOOL* pShowAll, USHORT nShowAllMax) const;
    void                InitFromOldPivot(const ScPivot& rOld, ScDocument* pDoc, BOOL bSetSource);

    void                UpdateReference( UpdateRefMode eUpdateRefMode,
                                          const ScRange& r, short nDx, short nDy, short nDz );
    BOOL                RefsEqual( const ScDPObject& r ) const;
    void                WriteRefsTo( ScDPObject& r ) const;

//STRIP001  static BOOL         HasRegisteredSources();
//STRIP001  static ::com::sun::star::uno::Sequence<rtl::OUString> GetRegisteredSources();
//STRIP001  static ::com::sun::star::uno::Reference< ::com::sun::star::sheet::XDimensionsSupplier>
//STRIP001                      CreateSource( const ScDPServiceDesc& rDesc );

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

