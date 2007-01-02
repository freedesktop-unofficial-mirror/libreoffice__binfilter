/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: goodies_matril3d.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 16:49:19 $
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

#ifndef _B3D_MATRIL3D_HXX
#include "matril3d.hxx"
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

namespace binfilter {

/*************************************************************************
|*
|* Konstruktor B3dMaterial
|*
\************************************************************************/

B3dMaterial::B3dMaterial()
:   aAmbient(COL_BLACK),            // kein lokales Umgebungslicht
    aDiffuse(0x00, 0xb8, 0xff),     // Blau7
    aSpecular(COL_WHITE),           // Weisser Glanzpunkt
    aEmission(COL_BLACK),           // Keine Selbstleuchtfarbe
    nExponent(15)                   // Glanzpunktbuendelung
{
}

void B3dMaterial::WriteData(SvStream& rOut) const
{
    rOut << aAmbient;
    rOut << aDiffuse;
    rOut << aSpecular;
    rOut << aEmission;
    rOut << nExponent;
}

void B3dMaterial::ReadData(SvStream& rIn)
{
    rIn >> aAmbient;
    rIn >> aDiffuse;
    rIn >> aSpecular;
    rIn >> aEmission;
    rIn >> nExponent;
}

/*************************************************************************
|*
|* Vergleichsoperator
|*
\************************************************************************/

BOOL B3dMaterial::operator==(const B3dMaterial& rMat)
{
     if(aAmbient == rMat.aAmbient
         && aDiffuse == rMat.aDiffuse
         && aSpecular == rMat.aSpecular
         && aEmission == rMat.aEmission
         && nExponent == rMat.nExponent)
         return TRUE;
     return FALSE;
}

/*************************************************************************
|*
|* Bucket fuer geometrische Daten
|*
\************************************************************************/

BASE3D_IMPL_BUCKET(B3dMaterial, Bucket)

}//end of namespace binfilter

// eof
