/*************************************************************************
 *
 *  $RCSfile: sw_txtinit.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:35:31 $
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


#pragma hdrstop

#include "errhdl.hxx"
#include "txtcfg.hxx"
#include "swcache.hxx"
#include "fntcache.hxx"     // pFntCache  ( SwFont/ScrFont-PrtFont Cache )
#include "swfntcch.hxx"     // pSwFontCache  ( SwAttrSet/SwFont Cache )
#include "txtfrm.hxx"
#include "txtcache.hxx"
#include "porlay.hxx"
#include "porglue.hxx"
#include "porexp.hxx"
#include "porrst.hxx"
#include "portab.hxx"
#include "porfly.hxx"
#include "portox.hxx"
#include "porref.hxx"
#include "porftn.hxx"
#include "porhyph.hxx"
#include "pordrop.hxx"
#include "tempauto.hxx" // Temporaere Autokorrekturliste
#include "blink.hxx"    // Blink-Manager
#include "init.hxx"   // Deklarationen fuer _TextInit() und _TextFinit()
#include "txtfly.hxx"   // SwContourCache
#include "dbg_lay.hxx"  // Layout Debug Fileausgabe

/*N*/ SwCache *SwTxtFrm::pTxtCache = 0;
/*N*/ long SwTxtFrm::nMinPrtLine = 0;
/*N*/ SwContourCache *pContourCache = 0;
/*N*/ SwDropCapCache *pDropCapCache = 0;

#ifndef PROFILE
// Code zum Initialisieren von Statics im eigenen Code-Segment
#pragma code_seg( "SWSTATICS" )
#endif

/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( SwTxtLine,    50,  50 )
/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( SwParaPortion,  50,  50 )   //Absaetze
/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( SwLineLayout,  150, 150 )   //Zeilen
/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( SwHolePortion, 150, 150 )   //z.B. Blanks am Zeilenende
/*N*/ IMPL_FIXEDMEMPOOL_NEWDEL( SwTxtPortion,  200, 100 )   //Attributwechsel

#ifndef PROFILE
#pragma code_seg()
#endif

/*************************************************************************
 *                  _TextInit(), _TextFinit()
 *************************************************************************/

// Werden _nur_ in init.cxx verwendet, dort stehen extern void _TextFinit()
// und extern void _TextInit(...)

/*N*/ void _TextInit()
/*N*/ {
/*N*/   pFntCache = new SwFntCache;
/*N*/   pSwFontCache = new SwFontCache;
/*N*/   pWaveCol = new Color( COL_GRAY );
/*N*/
/*N*/   //Pauschale groesse 250, plus 100 pro Shell
/*N*/   SwCache *pTxtCache = new SwCache( 250, 100
/*N*/ #ifndef PRODUCT
/*N*/   , "static SwTxtFrm::pTxtCache"
/*N*/ #endif
/*N*/   );
/*N*/   SwTxtFrm::SetTxtCache( pTxtCache );
/*N*/   PROTOCOL_INIT
/*N*/ }

/*N*/ void _TextFinit()
/*N*/ {
/*N*/   PROTOCOL_STOP
/*N*/   delete SwTxtFrm::GetTxtCache();
/*N*/   delete pSwFontCache;
/*N*/   delete pFntCache;
//STRIP001  delete pTempAuto;
/*N*/   delete pBlink;
/*N*/   delete pWaveCol;
/*N*/   delete pContourCache;
/*N*/   SwDropPortion::DeleteDropCapCache();
/*N*/ }



