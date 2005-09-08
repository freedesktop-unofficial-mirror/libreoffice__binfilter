/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: layouter.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 09:33:04 $
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
#ifndef _LAYOUTER_HXX
#define _LAYOUTER_HXX

#include "swtypes.hxx"
namespace binfilter {

//STRIP001 class SwEndnoter;
class SwDoc;
class SwSectionFrm;
class SwFtnFrm;
class SwPageFrm;
class SwLooping;

#define LOOP_PAGE 1

class SwLayouter
{
//STRIP001  SwEndnoter* pEndnoter;
    SwLooping* pLooping;
//STRIP001  void _CollectEndnotes( SwSectionFrm* pSect );
    BOOL StartLooping( SwPageFrm* pPage );
public:
    SwLayouter();
    ~SwLayouter();
//STRIP001  void InsertEndnotes( SwSectionFrm* pSect );
//STRIP001  void CollectEndnote( SwFtnFrm* pFtn );
//STRIP001  BOOL HasEndnotes() const;

    void LoopControl( SwPageFrm* pPage, BYTE nLoop );
    void EndLoopControl();

//STRIP001  static void CollectEndnotes( SwDoc* pDoc, SwSectionFrm* pSect );
//STRIP001  static BOOL Collecting( SwDoc* pDoc, SwSectionFrm* pSect, SwFtnFrm* pFtn );
    static BOOL StartLoopControl( SwDoc* pDoc, SwPageFrm *pPage );
};

} //namespace binfilter
#endif  //_LAYOUTER_HXX


