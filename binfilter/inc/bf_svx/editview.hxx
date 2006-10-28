/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: editview.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:30:20 $
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

// MyEDITVIEW, wegen exportiertem EditView
#ifndef _MyEDITVIEW_HXX
#define _MyEDITVIEW_HXX

#ifndef _RSCSFX_HXX //autogen
#include <rsc/rscsfx.hxx>
#endif

#ifndef _TOOLS_COLOR_HXX
#include <tools/color.hxx>
#endif
class Window;
class Pointer;
class Cursor;
class KeyEvent;
class MouseEvent;
class Rectangle;
class Link;
class Pair;
class Point;
class Range;
class SvStream;
class SvKeyValueIterator;
class SfxStyleSheet;
namespace binfilter {

class EditEngine;
class ImpEditEngine;
class ImpEditView;
class SvxSearchItem;
class SvxFieldItem;
class DropEvent;
class CommandEvent;
}//end of namespace binfilter //namespace binfilter
#ifndef _EDITDATA_HXX
#include <bf_svx/editdata.hxx>
#endif

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_
#include <com/sun/star/uno/Reference.h>
#endif

namespace com {
namespace sun {
namespace star {
namespace datatransfer {
    class XTransferable;
}}}}

namespace binfilter {
class EditView
{
    friend class EditEngine;
    friend class ImpEditEngine;
    friend class EditSelFunctionSet;

public: // brauche ich fuer Undo
    ImpEditView*    GetImpEditView() const      { return pImpEditView; }

private:
    ImpEditView*    pImpEditView;

                    EditView( const EditView& );

public:
                    EditView( EditEngine* pEng, Window* pWindow );
    virtual         ~EditView();

    EditEngine*     GetEditEngine() const;

    Window*         GetWindow() const;


    void            ShowCursor( BOOL bGotoCursor = TRUE, BOOL bForceVisCursor = TRUE );
    void            HideCursor();

    void            SetSelectionMode( EESelectionMode eMode );

    BOOL            IsReadOnly() const;

    BOOL            HasSelection() const;
    ESelection      GetSelection() const;
    void            SetSelection( const ESelection& rNewSel );


    BOOL            IsInsertMode() const;



                        // Position der VisArea im Ausgabefenster.
                        // Eine Groessenaenderung betrifft auch die VisArea
    void                SetOutputArea( const Rectangle& rRec );
    const Rectangle&    GetOutputArea() const;

                        // Dokumentposition.
                        // Eine Groessenaenderung betrifft auch die VisArea
    void                SetVisArea( const Rectangle& rRec );
    const Rectangle&    GetVisArea() const;

    const Pointer&  GetPointer() const;



    BOOL            PostKeyEvent( const KeyEvent& rKeyEvent );



    void            Cut();
    void            Copy();
    void            Paste();



    // speziell fuer Olli






    // An EditView, damit bei TRUE flackerfreies Update:

    void            SetStyleSheet( SfxStyleSheet* pStyle );







    const SvxFieldItem* GetField( const Point& rPos, USHORT* pnPara = NULL, xub_StrLen* pnPos = NULL ) const;



};

}//end of namespace binfilter
#endif // _MyEDITVIEW_HXX
