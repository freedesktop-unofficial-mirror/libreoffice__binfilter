/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: dpsdbtab.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:10:34 $
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

#ifndef SC_DPSDBTAB_HXX
#define SC_DPSDBTAB_HXX

// auto strip #ifndef _COM_SUN_STAR_UNO_REFERENCE_HXX_
// auto strip #include <com/sun/star/uno/Reference.hxx>
// auto strip #endif

namespace com { namespace sun { namespace star {
    namespace lang {
        class XMultiServiceFactory;
    }
}}}

#ifndef SC_DPTABDAT_HXX
#include "dptabdat.hxx"
#endif
namespace binfilter {

// --------------------------------------------------------------------
//
//  implementation of ScDPTableData with database data
//

struct ScImportSourceDesc
{
    String  aDBName;
    String  aObject;
    USHORT  nType;          // enum DataImportMode
    BOOL    bNative;

    BOOL operator== ( const ScImportSourceDesc& rOther ) const
        { return aDBName == rOther.aDBName &&
                 aObject == rOther.aObject &&
                 nType   == rOther.nType &&
                 bNative == rOther.bNative; }
};

//STRIP001 class ScDatabaseDPData_Impl;

//STRIP001 class ScDatabaseDPData : public ScDPTableData
//STRIP001 {
//STRIP001 private:
//STRIP001  ScDatabaseDPData_Impl* pImpl;
//STRIP001
//STRIP001  BOOL            OpenDatabase();
//STRIP001  void            InitAllColumnEntries();
//STRIP001
//STRIP001 public:
//STRIP001                  ScDatabaseDPData(
//STRIP001                      ::com::sun::star::uno::Reference<
//STRIP001                          ::com::sun::star::lang::XMultiServiceFactory > xSMgr,
//STRIP001                      const ScImportSourceDesc& rImport );
//STRIP001  virtual         ~ScDatabaseDPData();
//STRIP001
//STRIP001  virtual long                    GetColumnCount();
//STRIP001  virtual const TypedStrCollection&   GetColumnEntries(long nColumn);
//STRIP001  virtual String                  getDimensionName(long nColumn);
//STRIP001  virtual BOOL                    getIsDataLayoutDimension(long nColumn);
//STRIP001  virtual BOOL                    IsDateDimension(long nDim);
//STRIP001  virtual void                    DisposeData();
//STRIP001  virtual void                    SetEmptyFlags( BOOL bIgnoreEmptyRows, BOOL bRepeatIfEmpty );
//STRIP001
//STRIP001  virtual void                    ResetIterator();
//STRIP001  virtual BOOL                    GetNextRow( const ScDPTableIteratorParam& rParam );
//STRIP001 };



} //namespace binfilter
#endif

