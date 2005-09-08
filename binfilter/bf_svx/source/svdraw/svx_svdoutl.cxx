/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_svdoutl.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 07:03:58 $
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

#ifndef _SVDOUTL_HXX //autogen
#include "svdoutl.hxx"
#endif
// auto strip #ifndef _OUTLINER_HXX //autogen
// auto strip #include "outliner.hxx"
// auto strip #endif
#ifndef _SVDOTEXT_HXX //autogen
#include "svdotext.hxx"
#endif
#ifndef _EDITSTAT_HXX //autogen wg. EE_CNTRL_STRETCHING
#include <editstat.hxx>
#endif
// auto strip #ifndef _SVDMODEL_HXX //autogen wg. SdrModel
// auto strip #include <svdmodel.hxx>
// auto strip #endif
// auto strip #ifndef _EEITEM_HXX //autogen wg. EE_ITEMS_START
// auto strip #include <eeitem.hxx>
// auto strip #endif
// auto strip #ifndef _SFXITEMPOOL_HXX //autogen wg. SfxItemPool
// auto strip #include <svtools/itempool.hxx>
// auto strip #endif
namespace binfilter {


//TYPEINIT1( SdrOutliner, Outliner );

/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/
/*N*/ SdrOutliner::SdrOutliner( SfxItemPool* pItemPool, USHORT nMode ):
/*N*/ Outliner( pItemPool, nMode ),
/*N*/ pTextObj( NULL )
/*N*/ {
/*N*/ }


/*************************************************************************
|*
|* Dtor
|*
\************************************************************************/
/*N*/ SdrOutliner::~SdrOutliner()
/*N*/ {
/*N*/ }


/*************************************************************************
|*
|*
|*
\************************************************************************/
/*N*/ void SdrOutliner::SetTextObj( const SdrTextObj* pObj )
/*N*/ {
/*N*/   if( pObj && pObj != pTextObj )
/*N*/   {
/*N*/       SetUpdateMode(FALSE);
/*N*/       USHORT nOutlinerMode = OUTLINERMODE_OUTLINEOBJECT;
/*N*/       if ( !pObj->IsOutlText() )
/*N*/           nOutlinerMode = OUTLINERMODE_TEXTOBJECT;
/*N*/       Init( nOutlinerMode );
/*N*/
/*N*/       SetGlobalCharStretching(100,100);
/*N*/
/*N*/       ULONG nStat = GetControlWord();
/*N*/       nStat &= ~( EE_CNTRL_STRETCHING | EE_CNTRL_AUTOPAGESIZE );
/*N*/       SetControlWord(nStat);
/*N*/
/*N*/       Size aNullSize;
/*N*/       Size aMaxSize( 100000,100000 );
/*N*/       SetMinAutoPaperSize( aNullSize );
/*N*/       SetMaxAutoPaperSize( aMaxSize );
/*N*/       SetPaperSize( aMaxSize );
/*N*/       ClearPolygon();
/*N*/   }
/*N*/
/*N*/   pTextObj = pObj;
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/
/*N*/ void SdrOutliner::SetTextObjNoInit( const SdrTextObj* pObj )
/*N*/ {
/*N*/   pTextObj = pObj;
/*N*/ }

/*************************************************************************
|*
|*
|*
\************************************************************************/
/*N*/ XubString SdrOutliner::CalcFieldValue(const SvxFieldItem& rField, USHORT nPara, USHORT nPos,
/*N*/                                      Color*& rpTxtColor, Color*& rpFldColor)
/*N*/ {
/*N*/   FASTBOOL bOk = FALSE;
/*N*/   XubString aRet;
/*N*/
/*N*/   if (pTextObj)
/*N*/       bOk = pTextObj->CalcFieldValue(rField, nPara, nPos, FALSE, rpTxtColor, rpFldColor, aRet);
/*N*/
/*N*/   if (!bOk)
/*N*/       aRet = Outliner::CalcFieldValue(rField, nPara, nPos, rpTxtColor, rpFldColor);
/*N*/
/*N*/   return aRet;
/*N*/ }





}
