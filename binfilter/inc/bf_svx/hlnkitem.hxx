/*************************************************************************
 *
 *  $RCSfile: hlnkitem.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:39 $
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
#ifndef _SVX_HLNKITEM_HXX
#define _SVX_HLNKITEM_HXX

#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif
#ifndef _SFXPOOLITEM_HXX
#include <svtools/poolitem.hxx>
#endif
#ifndef _SFXSIDS_HRC
#include <bf_sfx2/sfxsids.hrc>
#endif

#ifndef _SFXMACITEM_HXX
#include <svtools/macitem.hxx>
#endif

#define HYPERDLG_EVENT_MOUSEOVER_OBJECT     0x0001
#define HYPERDLG_EVENT_MOUSECLICK_OBJECT    0x0002
#define HYPERDLG_EVENT_MOUSEOUT_OBJECT      0x0004

enum SvxLinkInsertMode
{
    HLINK_DEFAULT,
    HLINK_FIELD,
    HLINK_BUTTON,
    HLINK_HTMLMODE = 0x0080
};

class SvxHyperlinkItem : public SfxPoolItem
{
//STRIP001  String sName;
//STRIP001  String sURL;
//STRIP001  String sTarget;
//STRIP001  SvxLinkInsertMode eType;
//STRIP001
//STRIP001  String sIntName;
//STRIP001  SvxMacroTableDtor*  pMacroTable;
//STRIP001
//STRIP001  USHORT nMacroEvents;
//STRIP001
public:
    TYPEINFO();
//STRIP001
//STRIP001  SvxHyperlinkItem( USHORT nWhich = SID_HYPERLINK_GETLINK ):
//STRIP001              SfxPoolItem(nWhich), pMacroTable(NULL)  { eType = HLINK_DEFAULT; nMacroEvents=0; };
//STRIP001  SvxHyperlinkItem( const SvxHyperlinkItem& rHyperlinkItem );
//STRIP001  SvxHyperlinkItem( USHORT nWhich, String& rName, String& rURL,
//STRIP001                                  String& rTarget, String& rIntName,
//STRIP001                                  SvxLinkInsertMode eTyp = HLINK_FIELD,
//STRIP001                                  USHORT nEvents = 0,
//STRIP001                                  SvxMacroTableDtor *pMacroTbl =NULL );
//STRIP001  virtual ~SvxHyperlinkItem () { delete pMacroTable; }
//STRIP001
//STRIP001  inline SvxHyperlinkItem& operator=( const SvxHyperlinkItem &rItem );
//STRIP001
    virtual int              operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001  virtual BOOL             QueryValue( com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
//STRIP001  virtual BOOL             PutValue( const com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );
//STRIP001
//STRIP001  const   String& GetName() const { return sName; }
//STRIP001  void    SetName(const String& rName) { sName = rName; }
//STRIP001
//STRIP001  const   String& GetURL() const { return sURL; }
//STRIP001  void    SetURL(const String& rURL) { sURL = rURL; }
//STRIP001
//STRIP001  const   String& GetIntName () const { return sIntName; }
//STRIP001  void    SetIntName(const String& rIntName) { sIntName = rIntName; }
//STRIP001
//STRIP001  const   String& GetTargetFrame() const { return sTarget; }
//STRIP001  void    SetTargetFrame(const String& rTarget) { sTarget = rTarget; }
//STRIP001
//STRIP001  SvxLinkInsertMode GetInsertMode() const { return eType; }
//STRIP001  void    SetInsertMode( SvxLinkInsertMode eNew ) { eType = eNew; }
//STRIP001
//STRIP001  void SetMacro( USHORT nEvent, const SvxMacro& rMacro );
//STRIP001
//STRIP001  void SetMacroTable( const SvxMacroTableDtor& rTbl );
//STRIP001  const SvxMacroTableDtor* GetMacroTbl() const    { return pMacroTable; }
//STRIP001
//STRIP001  void SetMacroEvents (const USHORT nEvents) { nMacroEvents = nEvents; }
//STRIP001  const   USHORT GetMacroEvents() const { return nMacroEvents; }
//STRIP001
//STRIP001  virtual SvStream&           Store( SvStream &, USHORT nItemVersion ) const;
//STRIP001  virtual SfxPoolItem*        Create( SvStream &, USHORT nVer ) const;
//STRIP001
};

#endif

