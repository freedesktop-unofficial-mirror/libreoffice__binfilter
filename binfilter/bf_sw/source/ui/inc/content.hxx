/*************************************************************************
 *
 *  $RCSfile: content.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:54:59 $
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
#ifndef _CONTENT_HXX
#define _CONTENT_HXX

#include <limits.h>     // USHRT_MAX
#ifndef _SWCONT_HXX
#include "swcont.hxx"
#endif

#ifndef _MENU_HXX //autogen
#include <vcl/menu.hxx>
#endif
namespace binfilter {

class SwWrtShell;
class SwContentArr;
class SwContentType;
class SwNavigationPI;
class SwFmtFld;
class SwTxtINetFmt;
//STRIP001 class SwNavigationConfig;
class SwDocShell;
class SvDataObject;
class SwTOXBase;

//----------------------------------------------------------------------------
//  Hilfsklassen
//----------------------------------------------------------------------------

class SwPopup : public PopupMenu
{
    USHORT          nCurId;
    virtual void    Select(){nCurId = GetCurItemId();}

public:
    SwPopup() :
        PopupMenu(),
        nCurId(USHRT_MAX){}

    USHORT          GetCurId() const { return nCurId; }

};

//----------------------------------------------------------------------------

class SwOutlineContent : public SwContent
{
    USHORT  nOutlinePos;
    BYTE    nOutlineLevel;
    BOOL    bIsMoveable;
    public:
        SwOutlineContent(   const SwContentType* pCnt,
                            const String& rName,
                            USHORT nArrPos,
                            BYTE nLevel,
                            BOOL bMove,
                            long nYPos) :
            SwContent(pCnt, rName, nYPos), nOutlineLevel(nLevel),
                        nOutlinePos(nArrPos), bIsMoveable(bMove){}

    USHORT  GetPos(){return nOutlinePos;}
    BYTE    GetOutlineLevel(){return nOutlineLevel;}
    BOOL    IsMoveable(){return bIsMoveable;};
};

//----------------------------------------------------------------------------
class SwRegionContent : public SwContent
{

    BYTE    nRegionLevel;

    public:
        SwRegionContent(    const SwContentType* pCnt,
                            const String& rName,
                            BYTE nLevel,
                            long nYPos) :
            SwContent(pCnt, rName, nYPos),
                        nRegionLevel(nLevel){}
    BYTE    GetRegionLevel() const {return nRegionLevel;}
};
//----------------------------------------------------------------------------

//STRIP001 class SwURLFieldContent : public SwContent
//STRIP001 {
//STRIP001  const SwTxtINetFmt* pINetAttr;
//STRIP001  String sURL;

//STRIP001 public:
//STRIP001  SwURLFieldContent(  const SwContentType* pCnt,
//STRIP001                          const String& rName,
//STRIP001                          const String& rURL,
//STRIP001                          const SwTxtINetFmt* pAttr,
//STRIP001                          long nYPos )
//STRIP001      : SwContent( pCnt, rName, nYPos ), sURL( rURL ), pINetAttr( pAttr )
//STRIP001  {}

//STRIP001  virtual BOOL    IsProtect() const;
//STRIP001  const String&   GetURL()                { return sURL; }
//STRIP001  const SwTxtINetFmt* GetINetAttr()       { return pINetAttr; }
//STRIP001 };

//----------------------------------------------------------------------------

//STRIP001 class SwPostItContent : public SwContent
//STRIP001 {
//STRIP001  const SwFmtFld*     pFld;
//STRIP001 public:
//STRIP001  SwPostItContent( const SwContentType* pCnt,
//STRIP001                          const String& rName,
//STRIP001                          const SwFmtFld* pField,
//STRIP001                          long nYPos )
//STRIP001      : SwContent( pCnt, rName, nYPos ), pFld( pField )
//STRIP001  {}

//STRIP001  const SwFmtFld* GetPostIt()     { return pFld; }
//STRIP001  virtual BOOL    IsProtect() const;
//STRIP001 };

//----------------------------------------------------------------------------

//STRIP001 class SwGraphicContent : public SwContent
//STRIP001 {
//STRIP001  String      sLink;
//STRIP001 public:
//STRIP001  SwGraphicContent(const SwContentType* pCnt, const String& rName, const String& rLink, long nYPos)
//STRIP001      : SwContent( pCnt, rName, nYPos ), sLink( rLink )
//STRIP001      {}
//STRIP001  virtual ~SwGraphicContent();

//STRIP001  const String&   GetLink() const {return sLink;}
//STRIP001 };

//----------------------------------------------------------------------------
//STRIP001 class SwTOXBaseContent : public SwContent
//STRIP001 {
//STRIP001  const SwTOXBase* pBase;
//STRIP001 public:
//STRIP001  SwTOXBaseContent(const SwContentType* pCnt, const String& rName, long nYPos, const SwTOXBase& rBase)
//STRIP001      : SwContent( pCnt, rName, nYPos ), pBase(&rBase)
//STRIP001      {}
//STRIP001  virtual ~SwTOXBaseContent();
//STRIP001
//STRIP001  const SwTOXBase* GetTOXBase() const {return pBase;}
//STRIP001 };
/*
    class ContentType enthaelt Informationen zu einer Inhaltsform
    Das MemberArray wird nur gefuellt, wenn der Inhalt mit GetMember
    angefordert wird. Es wird nach Invalidate() nur dann neu geladen,
    wenn der Inhalt erneut ausgelesen werden soll.
*/
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

//STRIP001 class SwContentType : public SwTypeNumber
//STRIP001 {
//STRIP001  SwWrtShell*         pWrtShell;
//STRIP001  SwContentArr*       pMember;            // Array fuer Inhalte
//STRIP001  String              sContentTypeName;   // Name der Inhaltsform
//STRIP001  String              sSingleContentTypeName; // Name der Inhaltsform, Singular
//STRIP001  String              sTypeToken;         // Anhaengsel fuer URL
//STRIP001  USHORT              nMemberCount;       // Inhaltsanzahl
//STRIP001  USHORT              nContentType;       // Id der Inhaltsform
//STRIP001  BYTE                nOutlineLevel;
//STRIP001  BOOL                bMemberFilled : 1;  // wurden die Inhalte bereits eingefuegt?
//STRIP001  BOOL                bIsInternalDrag:1;  // koennen die Inhalte verschoben werden?
//STRIP001  BOOL                bDataValid :    1;  //
//STRIP001  BOOL                bEdit:          1;  // kann diese Type bearbeitet werden ?
//STRIP001  BOOL                bDelete:        1;  // kann diese Type geloescht werden ?
//STRIP001 protected:
//STRIP001      void            RemoveNewline(String&);
//STRIP001 public:
//STRIP001      SwContentType(SwWrtShell* pParent, USHORT nType, BYTE nLevel );
//STRIP001      ~SwContentType();

//STRIP001      void                Init(BOOL* pbInvalidateWindow = 0);
//STRIP001      void                FillMemberList(BOOL* pbLevelChanged = NULL);
//STRIP001      USHORT              GetMemberCount() const
//STRIP001                              {return nMemberCount;};
//STRIP001      USHORT              GetType() const {return nContentType;}
//STRIP001      const SwContent*    GetMember(USHORT nIndex);
//STRIP001      const String&       GetName() {return sContentTypeName;}
//STRIP001      const String&       GetSingleName() const {return sSingleContentTypeName;}
//STRIP001      const String&       GetTypeToken() const{return sTypeToken;}

//STRIP001      void                SetOutlineLevel(BYTE nNew)
//STRIP001                          {
//STRIP001                              nOutlineLevel = nNew;
//STRIP001                              Invalidate();
//STRIP001                          }

//STRIP001      void                Invalidate(); // nur nMemberCount wird neu gelesen

//STRIP001      BOOL                IsEditable() const {return bEdit;}
//STRIP001      BOOL                IsDeletable() const {return bDelete;}
//STRIP001 };

} //namespace binfilter
#endif

