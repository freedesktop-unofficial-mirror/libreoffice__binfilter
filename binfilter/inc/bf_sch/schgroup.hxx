/*************************************************************************
 *
 *  $RCSfile: schgroup.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:25:33 $
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

#ifndef _SCH_SCHGROUP_HXX
#define _SCH_SCHGROUP_HXX

#ifndef _SVDOGRP_HXX //autogen
#include <bf_svx/svdogrp.hxx>
#endif

#include "chtmodel.hxx"
namespace binfilter {

/************************************************************************/

class SchObjGroup : public SdrObjGroup
{
 public:
    enum ChartGroupTypeNames {LEGEND, DIAGRAM, NOTHING};

 private:
    SdrObjTransformInfoRec aInfo;
    ChartGroupTypeNames eChartGroupType;  // FG: 11.3.97 Wird einfach auf TRUE gesetzt falls es
                                   //     das Chart selbst ist. Das muss beim Resize anders
                                   //     behandelt werden
    ChartModel *pChartmodel;       // Auch das ist nur fuer das Resize wichtig, um dort
                                   // CreateChart() aufzurufen;

    BOOL bAskForLogicRect;         // Da die Groesse eines Gruppenobjektes durch die
                                   // Mitlgieder berechnet wird, hilft ein Resize der Gruppe nichts.
                                   // Bei BuildChart muss eine Neuberechnung bisweilen verhindert
                                   // werden. (z.B falls der Benutzer die Gruppe selbst resized hat)
    bool mbUseChartInventor;

public:

    TYPEINFO();

    SchObjGroup(ChartModel *pChmodel = NULL);
    virtual ~SchObjGroup();

    virtual UINT32 GetObjInventor() const;
    virtual UINT16 GetObjIdentifier() const;

//STRIP001  virtual USHORT GetHdlCount() const;
//STRIP001  virtual SdrHdl* GetHdl(USHORT nHdlNum) const;
//STRIP001  virtual void AddToHdlList(SdrHdlList& rHdlList) const;

//STRIP001  virtual FASTBOOL HasSpecialDrag() const;

    // FG: Damit soll ermöglicht werden dass man Objektgruppen im Chart resizen kann
//STRIP001  virtual void    TakeObjInfo(SdrObjTransformInfoRec& rInfo) const;
    void    SetObjInfo(SdrObjTransformInfoRec aMyInfo);

    // FG: Um das Verhalten bei einem Resize zu aendern muessen beide Routinen
    //     überladen werden.
//STRIP001  virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
//STRIP001  virtual void Resize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);

    // FG: 9.3.1997 Methode von Joe, die Überladen wird um zu Kennzeichnen
    //              ob die Gruppe jemals verschoben worden ist.
    virtual void Move  (const Size& rSiz);

    void SetGroupType (ChartGroupTypeNames value) {eChartGroupType = value;}
    ChartGroupTypeNames GetGroupType() {return eChartGroupType;}
    void SetGroupIsChart() {eChartGroupType = DIAGRAM;}
    BOOL GetGroupIsChart() {return (eChartGroupType == DIAGRAM);}

//STRIP001  void SetGroupMoved(BOOL value);

    void SetModel (ChartModel *pChModel) {pChartmodel = pChModel; SdrObjGroup::SetModel( (SdrModel*) pChModel ); }

    void SetAskForLogicRect(BOOL value) {bAskForLogicRect = value;}
    BOOL GetAskForLogicRect() {return bAskForLogicRect;}

    void SetUseChartInventor( bool bUseChartInventor );
};

} //namespace binfilter
#endif  // _SCH_SCHGROUP_HXX


