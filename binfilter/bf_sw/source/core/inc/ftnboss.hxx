/*************************************************************************
 *
 *  $RCSfile: ftnboss.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:49:54 $
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
#ifndef _FTNBOSS_HXX
#define _FTNBOSS_HXX

#include "layfrm.hxx"
namespace binfilter {

class SwFtnBossFrm;
class SwFtnContFrm;
class SwFtnFrm;
class SwTxtFtn;


//Setzen des maximalen Fussnotenbereiches. Restaurieren des alten Wertes im DTor.
//Implementierung im ftnfrm.cxx
class SwSaveFtnHeight
{
    SwFtnBossFrm *pBoss;
    const SwTwips nOldHeight;
    SwTwips nNewHeight;
public:
    SwSaveFtnHeight( SwFtnBossFrm *pBs, const SwTwips nDeadLine );
    ~SwSaveFtnHeight();
};

#define NA_ONLY_ADJUST 0
#define NA_GROW_SHRINK 1
#define NA_GROW_ADJUST 2
#define NA_ADJUST_GROW 3

class SwFtnBossFrm: public SwLayoutFrm
{
    //Fuer die privaten Fussnotenoperationen
    friend class SwFrm;
    friend class SwSaveFtnHeight;
    friend class SwPageFrm; // fuer das Setzen der MaxFtnHeight

    //Maximale Hoehe des Fussnotencontainers fuer diese Seite.
    SwTwips nMaxFtnHeight;

    SwFtnContFrm *MakeFtnCont();
    SwFtnFrm     *FindFirstFtn();
    BYTE _NeighbourhoodAdjustment( const SwFrm* pFrm ) const;
protected:

    void          InsertFtn( SwFtnFrm * );
    static void   ResetFtn( const SwFtnFrm *pAssumed );
public:
    inline SwFtnBossFrm( SwFrmFmt* pFmt) : SwLayoutFrm( pFmt ) {}

                 SwLayoutFrm *FindBodyCont();
    inline const SwLayoutFrm *FindBodyCont() const;
    inline void SetMaxFtnHeight( const SwTwips nNewMax ) { nMaxFtnHeight = nNewMax; }

    //Fussnotenschnittstelle
    void AppendFtn( SwCntntFrm *, SwTxtFtn * );
    void RemoveFtn( const SwCntntFrm *, const SwTxtFtn *, BOOL bPrep = TRUE );
    static       SwFtnFrm     *FindFtn( const SwCntntFrm *, const SwTxtFtn * );
                 SwFtnContFrm *FindFtnCont();
    inline const SwFtnContFrm *FindFtnCont() const;
           const SwFtnFrm     *FindFirstFtn( SwCntntFrm* ) const;
                 SwFtnContFrm *FindNearestFtnCont( BOOL bDontLeave = FALSE );

//STRIP001  void ChangeFtnRef( const SwCntntFrm *pOld, const SwTxtFtn *,
//STRIP001                     SwCntntFrm *pNew );
    void RearrangeFtns( const SwTwips nDeadLine, const BOOL bLock = FALSE,
                        const SwTxtFtn *pAttr = 0 );

    //SS damit der Textformatierer Temporaer die Fussnotenhoehe begrenzen
    //kann. DeadLine in Dokumentkoordinaten.
    void    SetFtnDeadLine( const SwTwips nDeadLine );
    SwTwips GetMaxFtnHeight() const { return nMaxFtnHeight; }

    //Liefert den Wert, der noch uebrig ist, bis der Body seine minimale
    //Hoehe erreicht hat.
    SwTwips GetVarSpace() const;

        //Layoutseitig benoetigte Methoden
    /// OD 03.04.2003 #108446# - add parameters <_bCollectOnlyPreviousFtns> and
    /// <_pRefFtnBossFrm> in order to control, if only footnotes, which are positioned
    /// before the given reference footnote boss frame have to be collected.
    /// Note: if parameter <_bCollectOnlyPreviousFtns> is true, then parameter
    /// <_pRefFtnBossFrm> have to be referenced to an object.
//STRIP001     static void _CollectFtns( const SwCntntFrm*   _pRef,
//STRIP001                               SwFtnFrm*           _pFtn,
//STRIP001                               SvPtrarr&           _rFtnArr,
//STRIP001                               const sal_Bool      _bCollectOnlyPreviousFtns = sal_False,
//STRIP001                               const SwFtnBossFrm* _pRefFtnBossFrm = NULL);
    /// OD 03.04.2003 #108446# - add parameter <_bCollectOnlyPreviousFtns> in
    /// order to control, if only footnotes, which are positioned before the
    /// footnote boss frame <this> have to be collected.
//STRIP001     void    CollectFtns( const SwCntntFrm* _pRef,
//STRIP001                          SwFtnBossFrm*     _pOld,
//STRIP001                          SvPtrarr&         _rFtnArr,
//STRIP001                          const sal_Bool    _bCollectOnlyPreviousFtns = sal_False );
//STRIP001  void    _MoveFtns( SvPtrarr &rFtnArr, BOOL bCalc = FALSE );
//STRIP001  void    MoveFtns( const SwCntntFrm *pSrc, SwCntntFrm *pDest,
//STRIP001                    SwTxtFtn *pAttr );
    // Sollte AdjustNeighbourhood gerufen werden (oder Grow/Shrink)?
    BYTE NeighbourhoodAdjustment( const SwFrm* pFrm ) const
        { return IsPageFrm() ? NA_ONLY_ADJUST : _NeighbourhoodAdjustment( pFrm ); }
};

inline const SwLayoutFrm *SwFtnBossFrm::FindBodyCont() const
{
    return ((SwFtnBossFrm*)this)->FindBodyCont();
}
inline const SwFtnContFrm *SwFtnBossFrm::FindFtnCont() const
{
    return ((SwFtnBossFrm*)this)->FindFtnCont();
}

} //namespace binfilter
#endif  //_FTNBOSS_HXX
