/*************************************************************************
 *
 *  $RCSfile: uinums.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:20:00 $
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
#ifndef _UINUMS_HXX
#define _UINUMS_HXX

#ifndef _SVARRAY_HXX //autogen
#include <svtools/svarray.hxx>
#endif

#ifndef _NUMRULE_HXX
#include <numrule.hxx>
#endif

//STRIP001 class SfxPoolItem;
//STRIP001 class SwWrtShell;
//STRIP001 class SvStream;

//STRIP001 #define MAX_NUM_RULES 9

//STRIP001 typedef SfxPoolItem* SfxPoolItemPtr;
//STRIP001 SV_DECL_PTRARR_DEL( _SwNumFmtsAttrs, SfxPoolItemPtr, 5,0 )

//------------------------------------------------------------------------
//STRIP001 class SwNumRulesWithName
//STRIP001 {
//STRIP001  String aName;
//STRIP001  // die Formate der NumRule muessen! unabhaengig von einem Document sein
//STRIP001  // (Sie sollen immer vorhanden sein!)
//STRIP001  class _SwNumFmtGlobal
//STRIP001  {
//STRIP001      SwNumFmt aFmt;
//STRIP001      String sCharFmtName;
//STRIP001      USHORT nCharPoolId;
//STRIP001      _SwNumFmtsAttrs aItems;
//STRIP001
//STRIP001      _SwNumFmtGlobal& operator=( const _SwNumFmtGlobal& );
//STRIP001
//STRIP001  public:
//STRIP001      _SwNumFmtGlobal( const SwNumFmt& rFmt );
//STRIP001      _SwNumFmtGlobal( const _SwNumFmtGlobal& );
//STRIP001      _SwNumFmtGlobal( SvStream&, USHORT nVersion );
//STRIP001      ~_SwNumFmtGlobal();
//STRIP001
//STRIP001      void Store( SvStream& );
//STRIP001      void ChgNumFmt( SwWrtShell& rSh, SwNumFmt& rChg ) const;
//STRIP001  };
//STRIP001
//STRIP001  _SwNumFmtGlobal* aFmts[ MAXLEVEL ];
//STRIP001 protected:
//STRIP001  void SetName(const String& rSet) {aName = rSet;}
//STRIP001
//STRIP001 public:
//STRIP001  SwNumRulesWithName(const SwNumRule &, const String &);
//STRIP001  SwNumRulesWithName( const SwNumRulesWithName & );
//STRIP001  SwNumRulesWithName(SvStream &, USHORT nVersion);
//STRIP001  ~SwNumRulesWithName();
//STRIP001
//STRIP001  const SwNumRulesWithName &operator=(const SwNumRulesWithName &);
//STRIP001
//STRIP001  const String& GetName() const               { return aName; }
//STRIP001  void MakeNumRule( SwWrtShell& rSh, SwNumRule& rChg ) const;
//STRIP001
//STRIP001  void Store( SvStream& );
//STRIP001 };
/********************************************************************

********************************************************************/
//STRIP001 class SwBaseNumRules
//STRIP001 {
//STRIP001 public:
//STRIP001  enum { nMaxRules = MAX_NUM_RULES };         // zur Zeit 9 definierte Forms
//STRIP001 protected:
//STRIP001  SwNumRulesWithName  *pNumRules[ MAX_NUM_RULES ];
//STRIP001  String              sFileName;
//STRIP001  USHORT              nVersion;
//STRIP001      BOOL                bModified;
//STRIP001
//STRIP001  virtual int         Load(SvStream&);
//STRIP001  virtual BOOL        Store(SvStream&);
//STRIP001
//STRIP001  void                Init();
//STRIP001
//STRIP001 public:
//STRIP001  SwBaseNumRules(const String& rFileName);
//STRIP001  virtual ~SwBaseNumRules();
//STRIP001
//STRIP001  inline const SwNumRulesWithName*    GetRules(USHORT nIdx) const;
//STRIP001  const SwNumRulesWithName*           GetRules(const String &rName) const;
//STRIP001  virtual void                        ApplyNumRules(
//STRIP001                                              const SwNumRulesWithName &rCopy,
//STRIP001                                              USHORT nIdx);
//STRIP001
//STRIP001 };

/********************************************************************

********************************************************************/
class SwChapterNumRules //STRIP001 : public SwBaseNumRules
{

public:
    SwChapterNumRules(){DBG_ASSERT(0, "STRIP");} //STRIP001 SwChapterNumRules();
    virtual ~SwChapterNumRules(){DBG_ASSERT(0, "STRIP");} //STRIP001 virtual ~SwChapterNumRules();

//STRIP001  virtual void        ApplyNumRules(  const SwNumRulesWithName &rCopy,
//STRIP001                                          USHORT nIdx);
};

// INLINE METHODE --------------------------------------------------------
//STRIP001 inline const SwNumRulesWithName *SwBaseNumRules::GetRules(USHORT nIdx) const
//STRIP001 {
//STRIP001  ASSERT(nIdx < nMaxRules, Array der NumRules ueberindiziert.);
//STRIP001  return pNumRules[nIdx];
//STRIP001 }

#endif
