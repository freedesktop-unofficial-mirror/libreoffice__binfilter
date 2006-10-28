/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: drwlayer.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:35:33 $
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

#ifndef SC_DRWLAYER_HXX
#define SC_DRWLAYER_HXX

#ifndef _SV_GRAPH_HXX //autogen
#include <vcl/graph.hxx>
#endif
#ifndef _FM_FMMODEL_HXX
#include <bf_svx/fmmodel.hxx>
#endif
#ifndef _SVSTOR_HXX
#include <so3/svstor.hxx>
#endif
#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
namespace binfilter {

class ScDocument;
class SfxViewShell;
class ScDrawObjData;
class ScIMapInfo;
class IMapObject;
class ScMarkData;
class SdrOle2Obj;

// -----------------------------------------------------------------------

class ScTabDeletedHint : public SfxHint
{
private:
    USHORT  nTab;
public:
            TYPEINFO();
            ScTabDeletedHint( USHORT nTabNo = USHRT_MAX );
    virtual ~ScTabDeletedHint();

    USHORT  GetTab()    { return nTab; }
};

class ScTabSizeChangedHint : public SfxHint
{
private:
    USHORT  nTab;
public:
            TYPEINFO();
            ScTabSizeChangedHint( USHORT nTabNo = USHRT_MAX );
    virtual ~ScTabSizeChangedHint();

    USHORT  GetTab()    { return nTab; }
};

// -----------------------------------------------------------------------


class ScDrawLayer: public FmFormModel
{
private:
    SvStorageRef    xPictureStorage;
    String          aName;
    ScDocument*     pDoc;
    SdrUndoGroup*   pUndoGroup;
    BOOL            bRecording;
    BOOL            bAdjustEnabled;
    BOOL            bHyphenatorSet;

private:
    void            MoveAreaTwips( USHORT nTab, const Rectangle& rArea, const Point& rMove,
                                const Point& rTopLeft );

public:
                    ScDrawLayer( ScDocument* pDocument, const String& rName );
    virtual         ~ScDrawLayer();

    virtual SdrPage*  AllocPage(FASTBOOL bMasterPage);
    virtual void    SetChanged( FASTBOOL bFlg = TRUE );

    virtual SvStream* GetDocumentStream(SdrDocumentStreamInfo& rStreamInfo) const;


    void            ReleasePictureStorage();


    void            ScAddPage( USHORT nTab );
    void            ScRenamePage( USHORT nTab, const String& rNewName );
                    // inkl. Inhalt, bAlloc=FALSE -> nur Inhalt

    ScDocument*     GetDocument() const { return pDoc; }

    void            UpdateBasic();              // DocShell-Basic in DrawPages setzen

    void            Load( SvStream& rStream );
    void            Store( SvStream& rStream ) const;

    BOOL            GetPrintArea( ScRange& rRange, BOOL bSetHor, BOOL bSetVer ) const;

                    //      automatische Anpassungen

    void            EnableAdjust( BOOL bSet = TRUE )    { bAdjustEnabled = bSet; }

    void            BeginCalcUndo();
    SdrUndoGroup*   GetCalcUndo();
    BOOL            IsRecording()           { return bRecording; }
    void            AddCalcUndo( SdrUndoAction* pUndo );

    void            WidthChanged( USHORT nTab, USHORT nCol, long nDifTwips );
    void            HeightChanged( USHORT nTab, USHORT nRow, long nDifTwips );

    BOOL            HasObjectsInRows( USHORT nTab, USHORT nStartRow, USHORT nEndRow );



    void            SetPageSize( USHORT nPageNo, const Size& rSize );

                    //  GetVisibleName: name for navigator etc: GetPersistName or GetName
                    //  (ChartListenerCollection etc. must use GetPersistName directly)

    SdrObject*      GetNamedObject( const String& rName, USHORT nId, USHORT& rFoundTab ) const;
                    // if pnCounter != NULL, the search for a name starts with this index + 1,
                    // and the index really used is returned.

    // Verankerung setzen und ermitteln
    static void     SetAnchor( SdrObject*, ScAnchorType );
    static ScAnchorType GetAnchor( const SdrObject* );

    // Positionen fuer Detektivlinien
    static ScDrawObjData* GetObjData( SdrObject* pObj, BOOL bCreate=FALSE );

    // Image-Map
    static ScIMapInfo* GetIMapInfo( SdrObject* pObj );


private:
    static SvPersist* pGlobalDrawPersist;           // fuer AllocModel
public:
};


} //namespace binfilter
#endif


