/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: undocell.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 16:31:21 $
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

#ifndef SC_UNDOCELL_HXX
#define SC_UNDOCELL_HXX

#ifndef SC_UNDOBASE_HXX
#include "undobase.hxx"
#endif
namespace binfilter {

class ScDocShell;
class ScBaseCell;
class ScPatternAttr;
class EditTextObject;
class SdrUndoAction;
class ScDetOpList;
class ScDetOpData;
class ScRangeName;

//----------------------------------------------------------------------------







class ScUndoPutCell: public ScSimpleUndo
{
public:
                    ScUndoPutCell( ScDocShell* pNewDocShell,
                            const ScAddress& rNewPos,
                            ScBaseCell* pUndoCell, ScBaseCell* pRedoCell, BOOL bHeight );
    virtual         ~ScUndoPutCell();

    virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;

    virtual String  GetComment() const;

private:
    ScAddress       aPos;
    ScBaseCell*     pOldCell;
    ScBaseCell*     pEnteredCell;
    ULONG           nEndChangeAction;
    BOOL            bNeedHeight;

    void            SetChangeTrack();
};






class ScUndoNote: public ScSimpleUndo
{
public:
                    ScUndoNote( ScDocShell* pNewDocShell,
                                BOOL bShow, const ScAddress& rNewPos,
                                SdrUndoAction* pDraw );
    virtual         ~ScUndoNote();



private:
    BOOL            bIsShow;
    ScAddress       aPos;
    SdrUndoAction*  pDrawUndo;
};






class ScUndoRangeNames: public ScSimpleUndo
{
public:
                    ScUndoRangeNames( ScDocShell* pNewDocShell,
                                        ScRangeName* pOld, ScRangeName* pNew );
    virtual         ~ScUndoRangeNames();

    virtual BOOL    CanRepeat(SfxRepeatTarget& rTarget) const;

    virtual String  GetComment() const;

private:
    ScRangeName*    pOldRanges;
    ScRangeName*    pNewRanges;

};



} //namespace binfilter
#endif

