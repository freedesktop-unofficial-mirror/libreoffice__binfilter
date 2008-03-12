/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: undotab.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 07:12:05 $
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

#ifndef SC_UNDOTAB_HXX
#define SC_UNDOTAB_HXX

#ifndef SC_UNDOBASE_HXX
#include "undobase.hxx"
#endif
#ifndef SC_MARKDATA_HXX
#include "markdata.hxx"
#endif

#ifndef _SVSTDARR_USHORTS

#define _SVSTDARR_USHORTS
#include <bf_svtools/svstdarr.hxx>

#endif

#ifndef _SVSTDARR_STRINGS

#define _SVSTDARR_STRINGS
#include <bf_svtools/svstdarr.hxx>

#endif
namespace binfilter {
class ScDocShell;
class ScDocument;
class SdrUndoAction;
class ScPrintRangeSaver;
class SdrObject;

//----------------------------------------------------------------------------

class ScUndoInsertTab : public ScSimpleUndo
{
public:
                    ScUndoInsertTab(
                            ScDocShell* pNewDocShell,
                            USHORT nTabNum,
                            BOOL bApp,
                            const String& rNewName);
    virtual         ~ScUndoInsertTab();

    virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;

    virtual String  GetComment() const;

private:
    String          sNewName;
    SdrUndoAction*  pDrawUndo;
    ULONG           nEndChangeAction;
    USHORT          nTab;
    BOOL            bAppend;

    void            SetChangeTrack();
};





class ScUndoRenameTab: public ScSimpleUndo
{
public:
                    ScUndoRenameTab(
                            ScDocShell* pNewDocShell,
                            USHORT nT,
                            const String& rOldName,
                            const String& rNewName);
    virtual         ~ScUndoRenameTab();

    virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;

    virtual String  GetComment() const;

private:
    USHORT  nTab;
    String  sOldName;
    String  sNewName;

};












class ScUndoShowHideTab : public ScSimpleUndo
{
public:
                    ScUndoShowHideTab(
                            ScDocShell* pShell,
                            USHORT nNewTab, BOOL bNewShow );
    virtual         ~ScUndoShowHideTab();

    virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;

    virtual String  GetComment() const;

private:
    USHORT  nTab;
    BOOL    bShow;

};




class ScUndoPrintRange : public ScSimpleUndo
{
public:
                    ScUndoPrintRange( ScDocShell* pShell, USHORT nNewTab,
                                        ScPrintRangeSaver* pOld, ScPrintRangeSaver* pNew );
    virtual         ~ScUndoPrintRange();

private:
    USHORT              nTab;
    ScPrintRangeSaver*  pOldRanges;
    ScPrintRangeSaver*  pNewRanges;

};







} //namespace binfilter
#endif

