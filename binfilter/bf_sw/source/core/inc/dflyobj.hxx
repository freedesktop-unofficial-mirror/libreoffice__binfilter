/*************************************************************************
 *
 *  $RCSfile: dflyobj.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:23:11 $
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
#ifndef _DFLYOBJ_HXX
#define _DFLYOBJ_HXX

#ifndef _SVDOVIRT_HXX //autogen
#include <bf_svx/svdovirt.hxx>
#endif
#ifndef _SVDOBJ_HXX //autogen
#include <bf_svx/svdobj.hxx>
#endif

class SwFlyFrm;
class SwFrmFmt;
class SdrObjMacroHitRec;

const UINT32 SWGInventor =  UINT32('S')*0x00000001+
                            UINT32('W')*0x00000100+
                            UINT32('G')*0x00010000;

const UINT16 SwFlyDrawObjIdentifier = 0x0001;
const UINT16 SwDrawFirst            = 0x0001;

//---------------------------------------
//SwFlyDrawObj, Die DrawObjekte fuer Flys.

class SwFlyDrawObj : public SdrObject
{
    SfxItemSet*                 mpLocalItemSet;

public:
    TYPEINFO();

    SwFlyDrawObj();
    ~SwFlyDrawObj();

//STRIP001  virtual FASTBOOL Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;

    // ItemSet access
//STRIP001  virtual const SfxItemSet& GetItemSet() const;
//STRIP001  virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);

    //Damit eine Instanz dieser Klasse beim laden erzeugt werden kann
    //(per Factory).
    virtual UINT32 GetObjInventor()     const;
    virtual UINT16 GetObjIdentifier()   const;
//STRIP001  virtual UINT16 GetObjVersion()      const;
};

//---------------------------------------
//SwVirtFlyDrawObj, die virtuellen Objekte fuer Flys.
//Flys werden immer mit virtuellen Objekten angezeigt. Nur so koennen sie
//ggf. mehrfach angezeigt werden (Kopf-/Fusszeilen).

class SwVirtFlyDrawObj : public SdrVirtObj
{
    SwFlyFrm *pFlyFrm;

public:
    TYPEINFO();

    SwVirtFlyDrawObj(SdrObject& rNew, SwFlyFrm* pFly);
    ~SwVirtFlyDrawObj();

    //Ueberladene Methoden der Basisklasse SdrVirtObj
//STRIP001  virtual SdrObject* CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;
//STRIP001  virtual FASTBOOL Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;
//STRIP001  virtual void     TakeObjInfo( SdrObjTransformInfoRec& rInfo ) const;

    //Wir nehemen die Groessenbehandlung vollstaendig selbst in die Hand.
    virtual const Rectangle& GetBoundRect() const;
//STRIP001  virtual       void       RecalcBoundRect();
//STRIP001  virtual       void       RecalcSnapRect();
    virtual const Rectangle& GetSnapRect()  const;
//STRIP001  virtual       void       SetSnapRect(const Rectangle& rRect);
//STRIP001  virtual       void       NbcSetSnapRect(const Rectangle& rRect);
//STRIP001  virtual const Rectangle& GetLogicRect() const;
//STRIP001  virtual       void       SetLogicRect(const Rectangle& rRect);
//STRIP001  virtual       void       NbcSetLogicRect(const Rectangle& rRect);
//STRIP001  virtual       void       TakeXorPoly(XPolyPolygon& rPoly, FASTBOOL) const;
//STRIP001  virtual       void       NbcMove  (const Size& rSiz);
//STRIP001  virtual       void       NbcResize(const Point& rRef, const Fraction& xFact,
//STRIP001                                     const Fraction& yFact);
//STRIP001  virtual       void       Move  (const Size& rSiz);
//STRIP001  virtual       void       Resize(const Point& rRef, const Fraction& xFact,
//STRIP001                                  const Fraction& yFact);

//STRIP001  const SwFrmFmt *GetFmt() const;
          SwFrmFmt *GetFmt();

    // Get Methoden fuer die Fly Verpointerung
          SwFlyFrm* GetFlyFrm()         { return pFlyFrm; }
    const SwFlyFrm* GetFlyFrm() const   { return pFlyFrm; }

    void SetRect() const;
    void _SetRectsDirty()               { SetRectsDirty(); }

    // ist eine URL an einer Grafik gesetzt, dann ist das ein Makro-Object
//STRIP001  virtual FASTBOOL HasMacro() const;
//STRIP001  virtual SdrObject* CheckMacroHit       (const SdrObjMacroHitRec& rRec) const;
//STRIP001  virtual Pointer    GetMacroPointer     (const SdrObjMacroHitRec& rRec) const;
};


#endif
