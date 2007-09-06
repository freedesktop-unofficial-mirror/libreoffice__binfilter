/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_dflyobj.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:08:10 $
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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include "hintids.hxx"

#ifndef _SVX_PROTITEM_HXX //autogen
#include <bf_svx/protitem.hxx>
#endif
#ifndef _SVDPAGE_HXX //autogen
#include <bf_svx/svdpage.hxx>
#endif



#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#include "frmatr.hxx"
#include "dflyobj.hxx"
#include "frmfmt.hxx"
#include "flyfrms.hxx"
namespace binfilter {

static FASTBOOL bInResize = FALSE;

/*N*/ TYPEINIT1( SwFlyDrawObj, SdrObject )
/*N*/ TYPEINIT1( SwVirtFlyDrawObj, SdrVirtObj )

/*************************************************************************
|*
|*  SwFlyDrawObj::Ctor
|*
|*  Ersterstellung      MA 18. Apr. 95
|*  Letzte Aenderung    MA 28. May. 96
|*
*************************************************************************/
/*N*/ SwFlyDrawObj::SwFlyDrawObj()
/*N*/ {
/*N*/   bNotPersistent = TRUE;
/*N*/   mpLocalItemSet = NULL;
/*N*/ }

/*N*/ SwFlyDrawObj::~SwFlyDrawObj()
/*N*/ {
/*N*/   if(mpLocalItemSet)
/*?*/       delete mpLocalItemSet;
/*N*/ }



/*************************************************************************
|*
|*  SwFlyDrawObj::Paint()
|*
|*  Ersterstellung      MA 08. Dec. 94
|*  Letzte Aenderung    MA 20. May. 95
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwFlyDrawObj::Factory-Methoden
|*
|*  Ersterstellung      MA 23. Feb. 95
|*  Letzte Aenderung    MA 23. Feb. 95
|*
*************************************************************************/

/*N*/ UINT32 __EXPORT SwFlyDrawObj::GetObjInventor() const
/*N*/ {
/*N*/   return SWGInventor;
/*N*/ }


/*N*/ UINT16 __EXPORT SwFlyDrawObj::GetObjIdentifier()  const
/*N*/ {
/*N*/   return SwFlyDrawObjIdentifier;
/*N*/ }



/*************************************************************************
|*
|*  SwVirtFlyDrawObj::CToren, Dtor
|*
|*  Ersterstellung      MA 08. Dec. 94
|*  Letzte Aenderung    MA 28. May. 96
|*
*************************************************************************/

/*N*/ SwVirtFlyDrawObj::SwVirtFlyDrawObj(SdrObject& rNew, SwFlyFrm* pFly) :
/*N*/   SdrVirtObj( rNew ),
/*N*/   pFlyFrm( pFly )
/*N*/ {
/*N*/   bNotPersistent = bNeedColorRestore = bWriterFlyFrame = TRUE;
/*N*/   const SvxProtectItem &rP = pFlyFrm->GetFmt()->GetProtect();
/*N*/   bMovProt = rP.IsPosProtected();
/*N*/   bSizProt = rP.IsSizeProtected();
/*N*/ }


/*N*/ __EXPORT SwVirtFlyDrawObj::~SwVirtFlyDrawObj()
/*N*/ {
/*N*/   if ( GetPage() )    //Der SdrPage die Verantwortung entziehen.
/*N*/       GetPage()->RemoveObject( GetOrdNum() );
/*N*/ }

/*************************************************************************
|*
|*  SwVirtFlyDrawObj::GetFmt()
|*
|*  Ersterstellung      MA 08. Dec. 94
|*  Letzte Aenderung    MA 08. Dec. 94
|*
*************************************************************************/



/*N*/ SwFrmFmt *SwVirtFlyDrawObj::GetFmt()
/*N*/ {
/*N*/   return GetFlyFrm()->GetFmt();
/*N*/ }

/*************************************************************************
|*
|*  SwVirtFlyDrawObj::Paint()
|*
|*  Ersterstellung      MA 20. Dec. 94
|*  Letzte Aenderung    MA 18. Dec. 95
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwVirtFlyDrawObj::CheckHit()
|*  Beschreibung        Das Teil ist genau dann getroffen wenn
|*                      1. der Point im Rand des Frm liegt.
|*                      2. der Point im heissen Bereich liegt.
|*                      3. der Point in der Flaeche liegt und es sich um
|*                         einen Rahmen mit NoTxtFrm handelt und dieser
|*                         keine URL traegt.
|*                      3a nicht aber wenn ueber dem Fly noch ein Fly liegt,
|*                         und der Point in dessen Flaeche nicht steht.
|*                      4. der Point in der Flaeche liegt und der Rahmen
|*                         selektiert ist.
|*  Ersterstellung      MA 08. Dec. 94
|*  Letzte Aenderung    JP 25.03.96
|*
*************************************************************************/


/*************************************************************************
|*
|*  SwVirtFlyDrawObj::TakeObjInfo()
|*
|*  Ersterstellung      MA 03. May. 95
|*  Letzte Aenderung    MA 03. May. 95
|*
*************************************************************************/



/*************************************************************************
|*
|*  SwVirtFlyDrawObj::Groessenermittlung
|*
|*  Ersterstellung      MA 12. Jan. 95
|*  Letzte Aenderung    MA 10. Nov. 95
|*
*************************************************************************/

/*N*/ void SwVirtFlyDrawObj::SetRect() const
/*N*/ {
/*N*/   if ( GetFlyFrm()->Frm().HasArea() )
/*N*/       ((SwVirtFlyDrawObj*)this)->aOutRect = GetFlyFrm()->Frm().SVRect();
/*N*/   else
/*?*/       ((SwVirtFlyDrawObj*)this)->aOutRect = Rectangle();
/*N*/ }


/*N*/ const Rectangle& __EXPORT SwVirtFlyDrawObj::GetBoundRect() const
/*N*/ {
/*N*/   SetRect();
/*N*/   return aOutRect;
/*N*/ }






/*N*/ const Rectangle& __EXPORT SwVirtFlyDrawObj::GetSnapRect()  const
/*N*/ {
/*N*/   SetRect();
/*N*/   return aOutRect;
/*N*/ }













/*************************************************************************
|*
|*  SwVirtFlyDrawObj::Move() und Resize()
|*
|*  Ersterstellung      MA 12. Jan. 95
|*  Letzte Aenderung    MA 26. Jul. 96
|*
*************************************************************************/















}
