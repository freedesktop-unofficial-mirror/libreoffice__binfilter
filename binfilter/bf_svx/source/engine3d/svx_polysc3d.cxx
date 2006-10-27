/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_polysc3d.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 20:51:09 $
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


#ifndef _XDEF_HXX //autogen
#include "xdef.hxx"
#endif












#ifndef _E3D_GLOBL3D_HXX
#include "globl3d.hxx"
#endif

#ifndef _E3D_POLYSC3D_HXX
#include "polysc3d.hxx"
#endif








namespace binfilter {

#define ITEMVALUE(ItemSet,Id,Cast)  ((const Cast&)(ItemSet).Get(Id)).GetValue()

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*N*/ TYPEINIT1(E3dPolyScene, E3dScene);

/*N*/ E3dPolyScene::E3dPolyScene()
/*N*/ : E3dScene()
/*N*/ {
/*N*/ }

/*?*/ E3dPolyScene::E3dPolyScene(E3dDefaultAttributes& rDefault)
/*?*/ : E3dScene(rDefault)
/*?*/ {
/*?*/ }

/*************************************************************************
|*
|* Identifier zurueckgeben
|*
\************************************************************************/

/*N*/ UINT16 E3dPolyScene::GetObjIdentifier() const
/*N*/ {
/*N*/   return E3D_POLYSCENE_ID;
/*N*/ }

/*************************************************************************
|*
|* Die Kontur fuer TextToContour
|*
\************************************************************************/


/*************************************************************************
|*
|* Objekt als Kontur in das Polygon einfuegen
|*
\************************************************************************/


/*************************************************************************
|*
|* Paint
|*
\************************************************************************/

/*N*/ FASTBOOL E3dPolyScene::Paint(ExtOutputDevice& rOut,
/*N*/   const SdrPaintInfoRec& rInfoRec) const
/*N*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001
/*N*/ }


/*************************************************************************
|*
|* Geometrie zeichnen mit clipping Beruecksichtigung
|*
\************************************************************************/


/*************************************************************************
|*
|* Zeichenroutine fuer 3D
|*
\************************************************************************/


/*************************************************************************
|*
|* Schatten aller Objekte zeichnen
|*
\************************************************************************/


/*************************************************************************
|*
|* Verminderte Darstellungsqualitaet, zeichne als WireFrame OHNE renderer
|*
\************************************************************************/



}
