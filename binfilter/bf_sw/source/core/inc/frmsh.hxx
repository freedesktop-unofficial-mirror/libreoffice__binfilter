/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: frmsh.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 09:30:19 $
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
#ifndef _FRMSH_HXX
#define _FRMSH_HXX

#include "rootfrm.hxx"
namespace binfilter {

/*************************************************************************
|*
|*  SwFrm::GetShell()
|*
|*  Beschreibung        Liefert die aktuelle Shell, ggf. auch NULL.
|*  Ersterstellung      MA 14. Aug. 92
|*  Letzte Aenderung    MA 18. Feb. 99
|*
|*************************************************************************/

inline ViewShell * SwFrm::GetShell() const
{
    const SwRootFrm *pRoot;
    if ( 0 != (pRoot = FindRootFrm()) )
        return pRoot->GetCurrShell();
    return 0;
}


} //namespace binfilter
#endif
