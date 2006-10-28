/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: editund2.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:30:08 $
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

#ifndef _EDITUND2_HXX
#define _EDITUND2_HXX

//#include <tools.hxx>

#ifndef _UNDO_HXX
#include <svtools/undo.hxx>
#endif
namespace binfilter {

class ImpEditEngine;

class EditUndoManager : public SfxUndoManager
{
private:
    ImpEditEngine*  pImpEE;
public:
                    EditUndoManager( ImpEditEngine* pImpEE );

};

// -----------------------------------------------------------------------
// EditUndo
// ------------------------------------------------------------------------
class EditUndo : public SfxUndoAction
{
private:
    USHORT          nId;
    ImpEditEngine*  pImpEE;

public:
                    EditUndo( USHORT nI, ImpEditEngine* pImpEE );
    virtual         ~EditUndo();

    ImpEditEngine*  GetImpEditEngine() const    { return pImpEE; }

    virtual void    Undo()      = 0;
    virtual void    Redo()      = 0;
    virtual void    Repeat()    = 0;

    virtual String  GetComment() const;
    virtual USHORT  GetId() const;
};

}//end of namespace binfilter
#endif  // _EDITUND2_HXX

