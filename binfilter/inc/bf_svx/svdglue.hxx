/*************************************************************************
 *
 *  $RCSfile: svdglue.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:49 $
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

#ifndef _SVDGLUE_HXX
#define _SVDGLUE_HXX
class Window;
class OutputDevice;
class SvStream;
namespace binfilter {
class SdrObject;
}//end of namespace binfilter
#ifndef _CONTNR_HXX //autogen
#include <tools/contnr.hxx>
#endif
#ifndef _GEN_HXX //autogen
#include <tools/gen.hxx>
#endif
namespace binfilter {
////////////////////////////////////////////////////////////////////////////////////////////////////

#define SDRESC_SMART  0x0000
#define SDRESC_LEFT   0x0001
#define SDRESC_RIGHT  0x0002
#define SDRESC_TOP    0x0004
#define SDRESC_BOTTOM 0x0008
#define SDRESC_LO    0x0010 /* ni */
#define SDRESC_LU    0x0020 /* ni */
#define SDRESC_RO    0x0040 /* ni */
#define SDRESC_RU    0x0080 /* ni */
#define SDRESC_HORZ  (SDRESC_LEFT|SDRESC_RIGHT)
#define SDRESC_VERT  (SDRESC_TOP|SDRESC_BOTTOM)
#define SDRESC_ALL   0x00FF

#define SDRHORZALIGN_CENTER   0x0000
#define SDRHORZALIGN_LEFT     0x0001
#define SDRHORZALIGN_RIGHT    0x0002
#define SDRHORZALIGN_DONTCARE 0x0010
#define SDRVERTALIGN_CENTER   0x0000
#define SDRVERTALIGN_TOP      0x0100
#define SDRVERTALIGN_BOTTOM   0x0200
#define SDRVERTALIGN_DONTCARE 0x1000

class SdrGluePoint {
    // Bezugspunkt ist SdrObject::GetSnapRect().Center()
    // bNoPercent=FALSE: Position ist -5000..5000 (1/100)% bzw. 0..10000 (je nach Align)
    // bNoPercent=TRUE : Position ist in log Einh, rel zum Bezugspunkt
    Point    aPos;
    USHORT   nEscDir;
    USHORT   nId;
    USHORT   nAlign;
    FASTBOOL bNoPercent:1;
    FASTBOOL bReallyAbsolute:1; // Temporaer zu setzen fuer Transformationen am Bezugsobjekt
public:
    SdrGluePoint(): nEscDir(SDRESC_SMART),nId(0),nAlign(0) { bNoPercent=FALSE; bReallyAbsolute=FALSE; }
    SdrGluePoint(const Point& rNewPos, FASTBOOL bNewPercent=TRUE, USHORT nNewAlign=0): aPos(rNewPos),nEscDir(SDRESC_SMART),nId(0),nAlign(nNewAlign) { bNoPercent=!bNewPercent; bReallyAbsolute=FALSE; }
    FASTBOOL operator==(const SdrGluePoint& rCmpGP) const   { return aPos==rCmpGP.aPos && nEscDir==rCmpGP.nEscDir && nId==rCmpGP.nId && nAlign==rCmpGP.nAlign && bNoPercent==rCmpGP.bNoPercent && bReallyAbsolute==rCmpGP.bReallyAbsolute; }
    FASTBOOL operator!=(const SdrGluePoint& rCmpGP) const   { return !operator==(rCmpGP); }
    const Point& GetPos() const                             { return aPos; }
    void         SetPos(const Point& rNewPos)               { aPos=rNewPos; }
    USHORT       GetEscDir() const                          { return nEscDir; }
    void         SetEscDir(USHORT nNewEsc)                  { nEscDir=nNewEsc; }
    /*FASTBOOL   IsEscapeSmart() const                      { return nEscDir==SDRESC_SMART; }
    void         SetEscapeSmart()                           { nEscDir=SDRESC_SMART; }
    FASTBOOL     IsEscapeLeft() const                       { return (nEscDir&SDRESC_LEFT)!=0; }
    void         SetEscapeLeft(FASTBOOL bOn)                { nEscDir=bOn ? (nEscDir|SDRESC_LEFT) : (nEscDir&~SDRESC_LEFT); }
    FASTBOOL     IsEscapeRight() const                      { return (nEscDir&SDRESC_RIGHT)!=0; }
    void         SetEscapeRight(FASTBOOL bOn)               { nEscDir=bOn ? (nEscDir|SDRESC_RIGHT) : (nEscDir&~SDRESC_RIGHT); }
    FASTBOOL     IsEscapeTop() const                        { return (nEscDir&SDRESC_TOP)!=0; }
    void         SetEscapeTop(FASTBOOL bOn)                 { nEscDir=bOn ? (nEscDir|SDRESC_TOP) : (nEscDir&~SDRESC_TOP); }
    FASTBOOL     IsEscapeBottom() const                     { return (nEscDir&SDRESC_BOTTOM)!=0; }
    void         SetEscapeBottom(FASTBOOL bOn)              { nEscDir=bOn ? (nEscDir|SDRESC_BOTTOM) : (nEscDir&~SDRESC_BOTTOM); }*/
    USHORT       GetId() const                              { return nId; }
    void         SetId(USHORT nNewId)                       { nId=nNewId; }
    FASTBOOL     IsPercent() const                          { return !bNoPercent; }
    void         SetPercent(FASTBOOL bOn)                   { bNoPercent=!bOn; }
    // Temporaer zu setzen fuer Transformationen am Bezugsobjekt
    FASTBOOL     IsReallyAbsolute() const                   { return bReallyAbsolute; }
//STRIP001  void         SetReallyAbsolute(FASTBOOL bOn, const SdrObject& rObj);
    USHORT       GetAlign() const                           { return nAlign; }
    void         SetAlign(USHORT nAlg)                      { nAlign=nAlg; }
    USHORT       GetHorzAlign() const                       { return nAlign&0x00FF; }
    void         SetHorzAlign(USHORT nAlg)                  { nAlign=(nAlign&0xFF00)|(nAlg&0x00FF); }
    USHORT       GetVertAlign() const                       { return nAlign&0xFF00; }
    void         SetVertAlign(USHORT nAlg)                  { nAlign=(nAlign&0x00FF)|(nAlg&0xFF00); }
//STRIP001  void         Draw(OutputDevice& rOut, const SdrObject* pObj) const;
//STRIP001  FASTBOOL     IsHit(const Point& rPnt, const OutputDevice& rOut, const SdrObject* pObj) const;
//STRIP001  void         Invalidate(Window& rWin, const SdrObject* pObj) const;
    Point        GetAbsolutePos(const SdrObject& rObj) const;
//STRIP001  void         SetAbsolutePos(const Point& rNewPos, const SdrObject& rObj);
//STRIP001  long         GetAlignAngle() const;
//STRIP001  void         SetAlignAngle(long nWink);
//STRIP001  long         EscDirToAngle(USHORT nEsc) const;
//STRIP001  USHORT       EscAngleToDir(long nWink) const;
//STRIP001  void         Rotate(const Point& rRef, long nWink, double sn, double cs, const SdrObject* pObj);
//STRIP001  void         Mirror(const Point& rRef1, const Point& rRef2, const SdrObject* pObj);
//STRIP001  void         Mirror(const Point& rRef1, const Point& rRef2, long nWink, const SdrObject* pObj);
//STRIP001  void         Shear (const Point& rRef, long nWink, double tn, FASTBOOL bVShear, const SdrObject* pObj);
    friend SvStream& operator<<(SvStream& rOut, const SdrGluePoint& rGP);
    friend SvStream& operator>>(SvStream& rIn, SdrGluePoint& rGP);
};

#define SDRGLUEPOINT_NOTFOUND 0xFFFF

class SdrGluePointList {
    Container aList;
#if SUPD > 322
//    FASTBOOL bSorted; // Muss noch implementiert werden oder?
    // Eigentlich sollte die GluePointList stets sortiert sein (solange die
    // Id's ausreichen)
#endif
protected:
    SdrGluePoint* GetObject(USHORT i) const { return (SdrGluePoint*)(aList.GetObject(i)); }
public:
    SdrGluePointList(): aList(1024,4,4) {}
    SdrGluePointList(const SdrGluePointList& rSrcList): aList(1024,4,4)     { *this=rSrcList; }
    ~SdrGluePointList()                                                     { Clear(); }
    void                Clear();
//STRIP001  void                operator=(const SdrGluePointList& rSrcList);
    USHORT              GetCount() const                                    { return USHORT(aList.Count()); }
    // Beim Insert wird dem Objekt (also dem GluePoint) automatisch eine Id zugewiesen.
    // ReturnCode ist der Index des neuen GluePoints in der Liste
    USHORT              Insert(const SdrGluePoint& rGP);
    void                Delete(USHORT nPos)                                 { delete (SdrGluePoint*)aList.Remove(nPos); }
    SdrGluePoint&       operator[](USHORT nPos)                             { return *GetObject(nPos); }
    const SdrGluePoint& operator[](USHORT nPos) const                       { return *GetObject(nPos); }
    USHORT              FindGluePoint(USHORT nId) const;
//STRIP001  USHORT              HitTest(const Point& rPnt, const OutputDevice& rOut, const SdrObject* pObj, FASTBOOL bBack=FALSE, FASTBOOL bNext=FALSE, USHORT nId0=0) const;
//STRIP001  void                DrawAll(OutputDevice& rOut, const SdrObject* pObj) const;
//STRIP001  void                Invalidate(Window& rWin, const SdrObject* pObj) const;
    // Temporaer zu setzen fuer Transformationen am Bezugsobjekt
//STRIP001  void                SetReallyAbsolute(FASTBOOL bOn, const SdrObject& rObj);
//STRIP001  void                Rotate(const Point& rRef, long nWink, double sn, double cs, const SdrObject* pObj);
//STRIP001  void                Mirror(const Point& rRef1, const Point& rRef2, const SdrObject* pObj);
//STRIP001  void                Mirror(const Point& rRef1, const Point& rRef2, long nWink, const SdrObject* pObj);
//STRIP001  void                Shear (const Point& rRef, long nWink, double tn, FASTBOOL bVShear, const SdrObject* pObj);
    friend SvStream& operator<<(SvStream& rOut, const SdrGluePointList& rGPL);
    friend SvStream& operator>>(SvStream& rIn, SdrGluePointList& rGPL);
};

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDGLUE_HXX

