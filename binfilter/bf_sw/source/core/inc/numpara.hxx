/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: numpara.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 09:34:42 $
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
#ifndef _NUMPARA_HXX
#define _NUMPARA_HXX

#include "numrule.hxx"
#ifndef _NDARR_HXX //autogen
#include "ndarr.hxx"
#endif
#include "ndindex.hxx"
namespace binfilter {

class SwTxtNode;
class SwDoc;
class SwNumSection;
class SwNodes;

class _NumPara
{
    const SwNumSection& rNumSection;

    void _Init();

public:
    SwNodeIndex aNdIdx;
    ULONG nCnt;
    SwNum aNum;
    char nDiff;             // +1, 0, -1 !! dafuer reicht ein char !!
    BYTE nOldLevel;
    BOOL bInitNum : 1;
    BOOL bWasUndo : 1;
    BOOL bOverTbl : 1;      // Flag fuer ForEach-Methoden, Tabelle ueberspr.

    _NumPara( char nOffset, const SwNodeIndex& rNdIdx,
                const SwNumSection& rSect, ULONG nCntNodes );
    _NumPara( const SwNodeIndex& rNdIdx, const SwNumSection& rSect );
    ~_NumPara();

    void UpdateNum( SwTxtNode& rTxtNd );
};

// Funktion fuer ForEach am Nodes-Array
BOOL _NumUpDown( const SwNodePtr& rpNode, void* pPara );


} //namespace binfilter
#endif  // _NUMPARA_HXX
