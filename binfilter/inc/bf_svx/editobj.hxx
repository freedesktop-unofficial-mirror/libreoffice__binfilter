/*************************************************************************
 *
 *  $RCSfile: editobj.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:34 $
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

#ifndef _EDITOBJ_HXX
#define _EDITOBJ_HXX

#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _RSCSFX_HXX
#include <rsc/rscsfx.hxx>
#endif
#ifndef _SFXITEMSET_HXX
#include <svtools/itemset.hxx>
#endif
#ifndef _EEITEM_HXX
#include <bf_svx/eeitem.hxx>
#endif

DBG_NAMEEX( EE_EditTextObject );

class SfxItemPool;
class SfxStyleSheetPool;
class SvxFieldItem;
class EECharAttribArray;

#define EDTOBJ_SETTINGS_ULITEMSUMMATION     0x00000001
#define EDTOBJ_SETTINGS_ULITEMFIRSTPARA     0x00000002

class EditTextObject
{
private:
    USHORT              nWhich;
//STRIP001  EditTextObject&     operator=( const EditTextObject& );

protected:
                        EditTextObject( USHORT nWhich );
                        EditTextObject( const EditTextObject& r );

    virtual void        StoreData( SvStream& rOStream ) const;
    virtual void        CreateData( SvStream& rIStream );

public:
    virtual             ~EditTextObject();

    USHORT              Which() const { return nWhich; }

    virtual USHORT      GetUserType() const;    // Fuer OutlinerMode, der kann das aber nicht kompatibel speichern
    virtual void        SetUserType( USHORT n );

//STRIP001  virtual ULONG       GetObjectSettings() const;
//STRIP001  virtual void        SetObjectSettings( ULONG n );

    virtual BOOL        IsVertical() const;
#if SUPD >= 615
    virtual
#endif
    void                SetVertical( BOOL bVertical );

#if SUPD >= 615
//STRIP001  virtual
#endif
//STRIP001  USHORT              GetScriptType() const;

    virtual USHORT      GetVersion() const; // Solange der Outliner keine Recordlaenge speichert

    virtual EditTextObject* Clone() const = 0;

    BOOL                    Store( SvStream& rOStream ) const;
    static EditTextObject*  Create( SvStream& rIStream,
                                SfxItemPool* pGlobalTextObjectPool = 0 );
//STRIP001  void                    Skip( SvStream& rIStream );

    // Zur 5.1 hat sich die Bedeutung des LRSpaceItems fuer den Outliner geaendert...
//STRIP001  virtual void            SetLRSpaceItemFlags( BOOL bOutlineMode );
    virtual void            AdjustImportedLRSpaceItems( BOOL bTurnOfBullets );
    virtual void            PrepareStore( SfxStyleSheetPool* pStyleSheetPool );
    virtual void            FinishStore();
    virtual void            FinishLoad( SfxStyleSheetPool* pStyleSheetPool );

    virtual USHORT      GetParagraphCount() const;

    virtual XubString   GetText( USHORT nParagraph ) const;
    virtual void        Insert( const EditTextObject& rObj, USHORT nPara );
//STRIP001  virtual void        RemoveParagraph( USHORT nPara );
//STRIP001  virtual EditTextObject* CreateTextObject( USHORT nPara, USHORT nParas = 1 ) const;

//STRIP001  virtual BOOL        HasPortionInfo() const;
    virtual void        ClearPortionInfo();

//STRIP001  virtual BOOL        HasOnlineSpellErrors() const;

//STRIP001  virtual BOOL        HasCharAttribs( USHORT nWhich = 0 ) const;
//STRIP001  virtual void        GetCharAttribs( USHORT nPara, EECharAttribArray& rLst ) const;

//STRIP001  virtual BOOL        RemoveCharAttribs( USHORT nWhich = 0 );
//STRIP001  virtual BOOL        RemoveParaAttribs( USHORT nWhich = 0 );

    virtual void        MergeParaAttribs( const SfxItemSet& rAttribs, USHORT nStart = EE_CHAR_START, USHORT nEnd = EE_CHAR_END );

//STRIP001  virtual BOOL        IsFieldObject() const;
//STRIP001  virtual const SvxFieldItem* GetField() const;
    virtual BOOL        HasField( TypeId aType = NULL ) const;

    virtual SfxItemSet  GetParaAttribs( USHORT nPara ) const;
//STRIP001  virtual void        SetParaAttribs( USHORT nPara, const SfxItemSet& rAttribs );

//STRIP001  virtual BOOL        HasStyleSheet( const XubString& rName, SfxStyleFamily eFamily ) const;
    virtual void        GetStyleSheet( USHORT nPara, XubString& rName, SfxStyleFamily& eFamily ) const;
    virtual void        SetStyleSheet( USHORT nPara, const XubString& rName, const SfxStyleFamily& eFamily );
    virtual BOOL        ChangeStyleSheets(  const XubString& rOldName, SfxStyleFamily eOldFamily,
                                            const XubString& rNewName, SfxStyleFamily eNewFamily );
    virtual void        ChangeStyleSheetName( SfxStyleFamily eFamily, const XubString& rOldName, const XubString& rNewName );
};

#endif  // _EDITOBJ_HXX
