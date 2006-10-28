/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: callform.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:28:30 $
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

#ifndef SC_CALLFORM_HXX
#define SC_CALLFORM_HXX

#ifndef SC_COLLECT_HXX
#include "collect.hxx"
#endif
namespace binfilter {

//------------------------------------------------------------------------
#define MAXFUNCPARAM    16
#define MAXARRSIZE      0xfffe

//------------------------------------------------------------------------
#ifndef WIN
#ifndef WNT
#define CALLTYPE
#else
#define CALLTYPE            __cdecl
#endif
#else
#define PASCAL              _pascal
#define FAR                 _far
#define CALLTYPE            FAR PASCAL
#endif

extern "C" {
typedef void (CALLTYPE* AdvData)( double& nHandle, void* pData );
}

//------------------------------------------------------------------------
enum ParamType
{
    PTR_DOUBLE,
    PTR_STRING,
    PTR_DOUBLE_ARR,
    PTR_STRING_ARR,
    PTR_CELL_ARR,
    NONE
};

//------------------------------------------------------------------------
class ModuleData;
class FuncData : public DataObject
{
friend class FuncCollection;
    const ModuleData* pModuleData;
    String      aInternalName;
    String      aFuncName;
    USHORT      nNumber;
    USHORT      nParamCount;
    ParamType   eAsyncType;
    ParamType   eParamType[MAXFUNCPARAM];
private:
    FuncData(const String& rIName);
public:
    FuncData(const FuncData& rData);
    virtual DataObject* Clone() const { return new FuncData(*this); }

    const   String&     GetInternalName() const { return aInternalName; }
    const   String&     GetFuncName() const { return aFuncName; }
            USHORT      GetParamCount() const { return nParamCount; }
            ParamType   GetParamType(USHORT nIndex) const { return eParamType[nIndex]; }
            ParamType   GetReturnType() const { return eParamType[0]; }
            ParamType   GetAsyncType() const { return eAsyncType; }
            BOOL        Call(void** ppParam);

                        // Name und Beschreibung des Parameters nParam.
                        // nParam==0 => Desc := Funktions-Beschreibung,
                        // Name := n/a
};


//------------------------------------------------------------------------
class FuncCollection : public SortedCollection
{
public:
    FuncCollection(USHORT nLim = 4, USHORT nDel = 4, BOOL bDup = FALSE) : SortedCollection ( nLim, nDel, bDup ) {}
    FuncCollection(const FuncCollection& rFuncCollection) : SortedCollection ( rFuncCollection ) {}

    virtual DataObject* Clone() const { return new FuncCollection(*this); }
    virtual short       Compare(DataObject* pKey1, DataObject* pKey2) const;
            BOOL        SearchFunc( const String& rName, USHORT& rIndex ) const;
};


void ExitExternalFunc();

} //namespace binfilter
#endif
