/*************************************************************************
 *
 *  $RCSfile: symbol.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: kz $ $Date: 2005-07-14 14:39:29 $
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
#ifndef SYMBOL_HXX
#define SYMBOL_HXX

#ifndef _VOS_REFERNCE_HXX_
#include <vos/refernce.hxx>
#endif
#ifndef _FONT_HXX //autogen
#include <vcl/font.hxx>
#endif
#ifndef _LIST_HXX //autogen
#include <tools/list.hxx>
#endif
#ifndef _TOOLS_DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif
#ifndef _DYNARY_HXX
#include <tools/dynary.hxx>
#endif
#ifndef _SFXLSTNER_HXX //autogen
#include <svtools/lstner.hxx>
#endif
#ifndef _SVARRAY_HXX
#include <svtools/svarray.hxx>
#endif

#ifndef UTILITY_HXX
#include "utility.hxx"
#endif
#ifndef _SMMOD_HXX
#include <smmod.hxx>
#endif
namespace binfilter {

#define SS_ATTR_ACCESS      0x80

#define SYMBOLSET_NONE  0xFFFF
#define SYMBOL_NONE     0xFFFF

class SmSymSetManager;

////////////////////////////////////////////////////////////////////////////////

//STRIP001 inline const String GetExportSymbolName( const String &rUiSymbolName )
//STRIP001 {
//STRIP001     return SM_MOD1()->GetLocSymbolData().GetExportSymbolName( rUiSymbolName );
//STRIP001 }


/*N*/ inline const String GetUiSymbolName( const String &rExportSymbolName )
/*N*/ {
/*N*/     return SM_MOD1()->GetLocSymbolData().GetUiSymbolName( rExportSymbolName );
/*N*/ }

//STRIP001 inline const String GetExportSymbolSetName( const String &rUiSymbolSetName )
//STRIP001 {
//STRIP001     return SM_MOD1()->GetLocSymbolData().GetExportSymbolSetName( rUiSymbolSetName );
//STRIP001 }


/*N*/ inline const String GetUiSymbolSetName( const String &rExportSymbolSetName )
/*N*/ {
/*N*/     return SM_MOD1()->GetLocSymbolData().GetUiSymbolSetName( rExportSymbolSetName );
/*N*/ }

////////////////////////////////////////////////////////////////////////////////

class SmSym
{
    friend class SmSymSetManager;

//STRIP001     friend SvStream& operator << (SvStream& rStream, const SmSym& rSymbol);
//STRIP001     friend SvStream& operator >> (SvStream& rStream, SmSym& rSymbol);

    SmFace               Face;
    String               Name;
    String               aExportName;
    String               aSetName;
    SmSym               *pHashNext;
    SmSymSetManager     *pSymSetManager;
    sal_Unicode          Character;
    BYTE                 Attribut;
    BOOL                 bPredefined;
    BOOL                 bDocSymbol;

public:
    SmSym();
    SmSym(const SmSym& rSymbol);
    SmSym(const String& rName, const Font& rFont, sal_Unicode cChar,
          const String& rSet, BOOL bIsPredefined = FALSE);

    SmSym&      operator = (const SmSym& rSymbol);

//STRIP001     void            SetSymbolName(const String& rName);

    const Font&     GetFace() const { return Face; }
    sal_Unicode     GetCharacter() const { return Character; }
    const String&   GetName() const { return Name; }

    void            SetFace( const Font& rFont )        { Face = rFont; }
    void            SetCharacter( sal_Unicode cChar )   { Character = cChar; }
    void            SetName( const String &rTxt )       { Name = rTxt; }

    BOOL            IsPredefined() const    { return bPredefined; }
    const String &  GetSetName() const      { return aSetName; }
    void            SetSetName( const String &rName )    { aSetName = rName; }
    const String &  GetExportName() const   { return aExportName; }
    void            SetExportName( const String &rName )    { aExportName = rName; }

    BOOL            IsDocSymbol() const         { return bDocSymbol; }
    void            SetDocSymbol( BOOL bVal )   { bDocSymbol = bVal; }
};

DECLARE_LIST(SmListSym, SmSym *)//STRIP008 DECLARE_LIST(SmListSym, SmSym *);
SV_DECL_PTRARR( SymbolArray, SmSym *, 32, 32 )//STRIP008 ;

/**************************************************************************/

class SmSymSet
{
    friend class SmSymSetManager;

//STRIP001     friend SvStream& operator << (SvStream& rStream, const SmSymSet& rSymbolSet);
//STRIP001     friend SvStream& operator >> (SvStream& rStream, SmSymSet& rSymbolSet);

    SmListSym            SymbolList;
    String               Name;
    SmSymSetManager     *pSymSetManager;

public:
//STRIP001     SmSymSet();
//STRIP001     SmSymSet(const SmSymSet& rSymbolSet);
    SmSymSet(const String& rName);
//STRIP001     ~SmSymSet();

//STRIP001  SmSymSet&   operator = (const SmSymSet& rSymbolSet);

    const String&   GetName() const { return Name; }
//STRIP001  void            SetName(String& rName);
    USHORT          GetCount() const { return (USHORT) SymbolList.Count(); }

    const SmSym&    GetSymbol(USHORT SymbolNo) const
    {
        DBG_ASSERT(SymbolList.GetObject(SymbolNo), "Symbol nicht vorhanden");
        return *SymbolList.GetObject(SymbolNo);
    }

    USHORT      AddSymbol(SmSym* pSymbol);
//STRIP001     void        DeleteSymbol(USHORT SymbolNo);
//STRIP001     SmSym *     RemoveSymbol(USHORT SymbolNo);
//STRIP001     USHORT      GetSymbolPos(const String& rName);
};

DECLARE_DYNARRAY(SmArraySymSet, SmSymSet *)

/**************************************************************************/

//STRIP001 class SmSymbolDialog;


struct SmSymSetManager_Impl
{
    SmArraySymSet       SymbolSets;
    SmSymSetManager &   rSymSetMgr;
    SmSym**             HashEntries;
    USHORT              NoSymbolSets;
    USHORT              NoHashEntries;
    BOOL                Modified;

    SmSymSetManager_Impl( SmSymSetManager &rMgr, USHORT HashTableSize );
//STRIP001     ~SmSymSetManager_Impl();

//STRIP001     SmSymSetManager_Impl & operator = ( const SmSymSetManager_Impl &rImpl );
};


class SmSymSetManager : public SfxListener
{
    friend struct SmSymSetManager_Impl;

    SmSymSetManager_Impl *pImpl;

//STRIP001  virtual void SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType,
//STRIP001                      const SfxHint& rHint, const TypeId& rHintType);

    UINT32      GetHashIndex(const String& rSymbolName);
    void        EnterHashTable(SmSym& rSymbol);
    void        EnterHashTable(SmSymSet& rSymbolSet);
    void        FillHashTable();
//STRIP001  void        Init();
//STRIP001  void        Exit();

public:
    SmSymSetManager(USHORT HashTableSize = 137);
//STRIP001     SmSymSetManager(const SmSymSetManager& rSymbolSetManager);
//STRIP001     ~SmSymSetManager();

//STRIP001  SmSymSetManager&   operator = (const SmSymSetManager& rSymbolSetManager);


    USHORT      AddSymbolSet(SmSymSet* pSymbolSet);
    void        ChangeSymbolSet(SmSymSet* pSymbolSet);
//STRIP001  void        DeleteSymbolSet(USHORT SymbolSetNo);
    USHORT      GetSymbolSetPos(const String& rSymbolSetName) const;
        USHORT      GetSymbolSetCount() const { return pImpl->NoSymbolSets; }
    SmSymSet   *GetSymbolSet(USHORT SymbolSetNo) const
    {
        return pImpl->SymbolSets.Get(SymbolSetNo);
    }

    SmSym       *   GetSymbolByName(const String& rSymbolName);
    const SmSym *   GetSymbolByName(const String& rSymbolName) const
    {
        return ((SmSymSetManager *) this)->GetSymbolByName(rSymbolName);
    }

        void            AddReplaceSymbol( const SmSym & rSymbol );
        USHORT          GetSymbolCount() const;
        const SmSym *   GetSymbolByPos( USHORT nPos ) const;

    BOOL        IsModified() const { return pImpl->Modified; }
    void        SetModified(BOOL Modify) { pImpl->Modified = Modify; }

        void            Load();
//STRIP001  void            Save();
};

} //namespace binfilter
#endif

