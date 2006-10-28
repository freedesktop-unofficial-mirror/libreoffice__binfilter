/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: detfunc.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:32:56 $
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

#ifndef SC_DETFUNC_HXX
#define SC_DETFUNC_HXX

#ifndef _GEN_HXX //autogen
#include <tools/gen.hxx>
#endif

#ifndef _TOOLS_COLOR_HXX
#include <tools/color.hxx>
#endif
class String;
namespace binfilter {

class SdrObject;
class SdrPage;

class ScCommentData;
class ScDetectiveData;
class ScDocument;
class ScTripel;
class ScAddress;
class ScRange;

#define SC_DET_MAXCIRCLE    1000

enum ScDetectiveDelete { SC_DET_ALL, SC_DET_DETECTIVE, SC_DET_CIRCLES, SC_DET_COMMENTS, SC_DET_ARROWS };

enum ScDetectiveObjType
{
    SC_DETOBJ_NONE,
    SC_DETOBJ_ARROW,
    SC_DETOBJ_FROMOTHERTAB,
    SC_DETOBJ_TOOTHERTAB,
    SC_DETOBJ_CIRCLE
};

class ScDetectiveFunc
{
    static ColorData nArrowColor;
    static ColorData nErrorColor;
    static ColorData nCommentColor;
    static BOOL      bColorsInitialized;

    ScDocument*     pDoc;
    USHORT          nTab;

    Point       GetDrawPos( USHORT nCol, USHORT nRow, BOOL bArrow );
    BOOL        HasArrow( USHORT nStartCol, USHORT nStartRow, USHORT nStartTab,
                            USHORT nEndCol, USHORT nEndRow, USHORT nEndTab );

    void        DeleteArrowsAt( USHORT nCol, USHORT nRow, BOOL bDestPnt );
    void        DeleteBox( USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2 );

    BOOL        HasError( const ScTripel& rStart, const ScTripel& rEnd, ScTripel& rErrPos );

    void        FillAttributes( ScDetectiveData& rData );

                // called from DrawEntry/DrawAlienEntry and InsertObject
    BOOL        InsertArrow( USHORT nCol, USHORT nRow,
                                USHORT nRefStartCol, USHORT nRefStartRow,
                                USHORT nRefEndCol, USHORT nRefEndRow,
                                BOOL bFromOtherTab, BOOL bRed,
                                ScDetectiveData& rData );
    BOOL        InsertToOtherTab( USHORT nStartCol, USHORT nStartRow,
                                USHORT nEndCol, USHORT nEndRow, BOOL bRed,
                                ScDetectiveData& rData );

                // DrawEntry / DrawAlienEntry check for existing arrows and errors
    BOOL        DrawEntry( USHORT nCol, USHORT nRow, const ScTripel& rRefStart, const ScTripel& rRefEnd,
                                ScDetectiveData& rData );
    BOOL        DrawAlienEntry( const ScTripel& rRefStart, const ScTripel& rRefEnd,
                                ScDetectiveData& rData );

    void        DrawCircle( USHORT nCol, USHORT nRow, ScDetectiveData& rData );


    USHORT      InsertPredLevel( USHORT nCol, USHORT nRow, ScDetectiveData& rData, USHORT nLevel );
    USHORT      InsertPredLevelArea( const ScTripel& rRefStart, const ScTripel& rRefEnd,
                                        ScDetectiveData& rData, USHORT nLevel );
    USHORT      FindPredLevel( USHORT nCol, USHORT nRow, USHORT nLevel, USHORT nDeleteLevel );
    USHORT      FindPredLevelArea( const ScTripel& rRefStart, const ScTripel& rRefEnd,
                                    USHORT nLevel, USHORT nDeleteLevel );

    USHORT      InsertErrorLevel( USHORT nCol, USHORT nRow, ScDetectiveData& rData, USHORT nLevel );

    USHORT      InsertSuccLevel( USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2,
                                        ScDetectiveData& rData, USHORT nLevel );
    USHORT      FindSuccLevel( USHORT nCol1, USHORT nRow1, USHORT nCol2, USHORT nRow2,
                                USHORT nLevel, USHORT nDeleteLevel );

/*N*/   BOOL        FindFrameForObject( SdrObject* pObject, ScRange& rRange );


public:
                ScDetectiveFunc(ScDocument* pDocument, USHORT nTable) : pDoc(pDocument),nTab(nTable) {}

    BOOL        ShowSucc( USHORT nCol, USHORT nRow );
    BOOL        ShowPred( USHORT nCol, USHORT nRow );
    BOOL        ShowError( USHORT nCol, USHORT nRow );

    BOOL        DeleteSucc( USHORT nCol, USHORT nRow );
    BOOL        DeletePred( USHORT nCol, USHORT nRow );
    BOOL        DeleteAll( ScDetectiveDelete eWhat );

    BOOL        MarkInvalid(BOOL& rOverflow);

    SdrObject*  ShowComment( USHORT nCol, USHORT nRow, BOOL bForce, SdrPage* pDestPage = NULL );
    SdrObject*  ShowCommentUser( USHORT nCol, USHORT nRow, const String& rUserText,
                                    const Rectangle& rVisible, BOOL bLeft,
                                    BOOL bForce, SdrPage* pDestPage );
    BOOL        HideComment( USHORT nCol, USHORT nRow );

    void        UpdateAllComments();        // on all tables
/*N*/   void        UpdateAllArrowColors();     // on all tables


    ScDetectiveObjType GetDetectiveObjectType( SdrObject* pObject,
                                ScAddress& rPosition, ScRange& rSource, BOOL& rRedLine );
    void        InsertObject( ScDetectiveObjType eType, const ScAddress& rPosition,
                                const ScRange& rSource, BOOL bRedLine );

    static ColorData GetArrowColor();
    static ColorData GetErrorColor();
    static ColorData GetCommentColor();
    static void InitializeColors();
};



} //namespace binfilter
#endif
