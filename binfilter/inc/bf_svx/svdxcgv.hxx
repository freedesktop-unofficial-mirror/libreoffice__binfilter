/*************************************************************************
 *
 *  $RCSfile: svdxcgv.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:43 $
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

#ifndef _SVDXCGV_HXX
#define _SVDXCGV_HXX

// HACK to avoid too deep includes and to have some
// levels free in svdmark itself (MS compiler include depth limit)
#ifndef _SVDHDL_HXX
#include <bf_svx/svdhdl.hxx>
#endif

#include <bf_svx/svdedxv.hxx>

#ifndef _GDIMTF_HXX //autogen
#include <vcl/gdimtf.hxx>
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @@@@@ @@   @@  @@@@  @@  @@  @@@@  @@  @@  @@@@  @@@@@  @@ @@ @@ @@@@@ @@   @@
//  @@    @@@ @@@ @@  @@ @@  @@ @@  @@ @@@ @@ @@  @@ @@     @@ @@ @@ @@    @@   @@
//  @@     @@@@@  @@     @@  @@ @@  @@ @@@@@@ @@     @@     @@ @@ @@ @@    @@ @ @@
//  @@@@    @@@   @@     @@@@@@ @@@@@@ @@@@@@ @@ @@@ @@@@   @@@@@ @@ @@@@  @@@@@@@
//  @@     @@@@@  @@     @@  @@ @@  @@ @@ @@@ @@  @@ @@      @@@  @@ @@    @@@@@@@
//  @@    @@@ @@@ @@  @@ @@  @@ @@  @@ @@  @@ @@  @@ @@      @@@  @@ @@    @@@ @@@
//  @@@@@ @@   @@  @@@@  @@  @@ @@  @@ @@  @@  @@@@@ @@@@@    @   @@ @@@@@ @@   @@
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

class SdrExchangeView: public SdrObjEditView
{
    friend class SdrPageView;

protected:

 //STRIP001    void                ImpGetPasteObjList(Point& rPos, SdrObjList*& rpLst);
//STRIP001  void                ImpPasteObject(SdrObject* pObj, SdrObjList& rLst, const Point& rCenter, const Size& rSiz, const MapMode& rMap, UINT32 nOptions);
//STRIP001  BOOL                ImpGetPasteLayer(const SdrObjList* pObjList, SdrLayerID& rLayer) const;
//STRIP001  Point               GetPastePos(SdrObjList* pLst, OutputDevice* pOut=NULL);

    // liefert True, wenn rPt geaendert wurde
//STRIP001  BOOL                ImpLimitToWorkArea(Point& rPt, const SdrPageView* pPV=NULL) const;

public:

    SdrExchangeView(SdrModel* pModel1, OutputDevice* pOut=NULL);
    SdrExchangeView(SdrModel* pModel1, ExtOutputDevice* pXOut);

    // Alle markierten Objekte auf dem angegebenen OutputDevice ausgeben.
//STRIP001  virtual void        DrawMarkedObj(OutputDevice& rOut, const Point& rOfs) const;

    // Z.B. fuer's Clipboard, Drag&Drop, ...
    // Alle markierten Objekte in ein Metafile stecken. Z.Zt. noch etwas
    // buggee (Offset..., Fremdgrafikobjekte (SdrGrafObj), Virtuelle
    // Objektkopien (SdrVirtObj) mit Ankerpos<>(0,0)).
    virtual GDIMetaFile GetMarkedObjMetaFile(BOOL bNoVDevIfOneMtfMarked=FALSE) const;

    // Alle markierten Objekte auf eine Bitmap malen. Diese hat die Farbtiefe
    // und Aufloesung des Bildschirms.
//STRIP001  virtual Bitmap      GetMarkedObjBitmap(BOOL bNoVDevIfOneBmpMarked=FALSE) const;

    // Alle markierten Objekte in ein neues Model kopieren. Dieses neue Model
    // hat dann genau eine Page. Das Flag PageNotValid an diesem Model ist
    // gesetzt. Daran ist zu erkennen, dass nur die Objekte der Page Gueltikeit
    // haben, die Page sebst jedoch nicht (Seitengroesse, Raender). Das neue
    // Model wird auf dem Heap erzeugt und wird an den Aufrufer dieser Methode
    // uebergeben. Dieser hat es dann spaeter zu entsorgen.
    // Beim einfuegen der markierten Objekte in die eine Page des neuen Model
    // findet ein Merging der seitenlokalen Layer statt. Sollte kein Platz mehr
    // fuer weitere seitenlokale Layer sein, wird den entsprechenden Objekten
    // der Default-Layer zugewiesen (Layer 0, (dokumentglobaler Standardlayer).
//STRIP001  virtual SdrModel*   GetMarkedObjModel() const;

//STRIP001     void            DrawAllMarked(OutputDevice& rOut, const Point& rOfs) const { DrawMarkedObj(rOut,rOfs); }
    GDIMetaFile     GetAllMarkedMetaFile(BOOL bNoVDevIfOneMtfMarked=FALSE) const { return GetMarkedObjMetaFile(bNoVDevIfOneMtfMarked); }
//STRIP001  Bitmap          GetAllMarkedBitmap(BOOL bNoVDevIfOneBmpMarked=FALSE) const { return GetMarkedObjBitmap(bNoVDevIfOneBmpMarked); }
//STRIP001  Graphic         GetAllMarkedGraphic() const;
//STRIP001  SdrModel*       GetAllMarkedModel() const { return GetMarkedObjModel(); }

//STRIP001     static Graphic  GetObjGraphic( SdrModel* pModel, SdrObject* pObj );

    // Bestimmung des View-Mittelpunktes, z.B. zum Pasten
//STRIP001  Point           GetViewCenter(const OutputDevice* pOut=NULL) const;

    // Bei allen Paste-Methoden werden die neuen Draw-Objekte markiert.
    // Wird der Parameter bAddMark auf TRUE gesetzt, so werden die neuen
    // DrawObjekte zu einer bereits bestehenden Selektion "hinzumarkiert".
    // Dieser Fall ist fuer Drag&Drop mit mehreren Items gedacht.
    // Die Methoden mit Point-Parameter fuegen neue Objekte zentriert an
    // dieser Position ein, die anderen zentriert am 1.OutputDevice der View.
    // Ist der Parameter pPg gesetzt, werden die Objekte and dieser Seite
    // eingefuegt. Die Positionierung (rPos bzw. Zentrierung) bezieht sich
    // dann nichtmehr auf die View sondern auf die Page.
    // Hinweis: SdrObjList ist Basisklasse von SdrPage.
    // Die Methoden liefern TRUE, wenn die Objekte erfolgreich erzeugt und
    // eingefuegt wurden. Bei pLst=FALSE und kein TextEdit aktiv kann man
    // sich dann auch darauf verlassen, dass diese an der View markiert sind.
    // Andernfalls erfolgt die Markierung nur, wenn pLst z.Zt. auch an der
    // View angezeigt wird.
    // Gueltige Werte fuer nOptions sind SDRINSERT_DONTMARK und
    // SDRINSERT_ADDMARK (siehe svdedtv.hxx).
//STRIP001  BOOL            Paste(const GDIMetaFile& rMtf, SdrObjList* pLst=NULL, OutputDevice* pOut=NULL, UINT32 nOptions=0) { return Paste(rMtf,GetPastePos(pLst,pOut),pLst,nOptions); }
//STRIP001  BOOL            Paste(const GDIMetaFile& rMtf, const Point& rPos, SdrObjList* pLst=NULL, UINT32 nOptions=0);
//STRIP001  BOOL            Paste(const Bitmap& rBmp, SdrObjList* pLst=NULL, OutputDevice* pOut=NULL, UINT32 nOptions=0) { return Paste(rBmp,GetPastePos(pLst,pOut),pLst,nOptions); }
//STRIP001  BOOL            Paste(const Bitmap& rBmp, const Point& rPos, SdrObjList* pLst=NULL, UINT32 nOptions=0);
//STRIP001  BOOL            Paste(const SdrModel& rMod, SdrObjList* pLst=NULL, OutputDevice* pOut=NULL, UINT32 nOptions=0) { return Paste(rMod,GetPastePos(pLst,pOut),pLst,nOptions); }
//STRIP001  virtual BOOL    Paste(const SdrModel& rMod, const Point& rPos, SdrObjList* pLst=NULL, UINT32 nOptions=0);
//STRIP001  BOOL            Paste(const String& rStr, SdrObjList* pLst=NULL, OutputDevice* pOut=NULL, UINT32 nOptions=0) { return Paste(rStr,GetPastePos(pLst,pOut),pLst,nOptions); }
//STRIP001  BOOL            Paste(const String& rStr, const Point& rPos, SdrObjList* pLst=NULL, UINT32 nOptions=0);
//STRIP001  // der USHORT eFormat nimmt Werte des enum EETextFormat entgegen
//STRIP001  BOOL            Paste(SvStream& rInput, USHORT eFormat, SdrObjList* pLst=NULL, OutputDevice* pOut=NULL, UINT32 nOptions=0) { return Paste(rInput,eFormat,GetPastePos(pLst,pOut),pLst,nOptions); }
//STRIP001  BOOL            Paste(SvStream& rInput, USHORT eFormat, const Point& rPos, SdrObjList* pLst=NULL, UINT32 nOptions=0);
//STRIP001
//STRIP001  // Feststellen, ob ein bestimmtes Format ueber Drag&Drop bzw. ueber's
//STRIP001  // Clipboard angenommen werden kann.
//STRIP001  BOOL            IsExchangeFormatSupported(ULONG nFormat) const;
//STRIP001
//STRIP001  BOOL            Cut( ULONG nFormat = SDR_ANYFORMAT );
//STRIP001  void            CutMarked( ULONG nFormat=SDR_ANYFORMAT );
//STRIP001
//STRIP001  BOOL            Yank( ULONG nFormat = SDR_ANYFORMAT );
//STRIP001  void            YankMarked( ULONG nFormat=SDR_ANYFORMAT );
//STRIP001
//STRIP001     BOOL            Paste( Window* pWin = NULL, ULONG nFormat = SDR_ANYFORMAT );
//STRIP001  BOOL            PasteClipboard( OutputDevice* pOut = NULL, ULONG nFormat = SDR_ANYFORMAT, UINT32 nOptions = 0 );
};

#endif //_SVDXCGV_HXX
