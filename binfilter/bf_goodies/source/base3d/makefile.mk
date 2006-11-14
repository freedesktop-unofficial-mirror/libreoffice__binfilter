#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: ihi $ $Date: 2006-11-14 11:58:41 $
#
#   The Contents of this file are made available subject to
#   the terms of GNU Lesser General Public License Version 2.1.
#
#
#     GNU Lesser General Public License Version 2.1
#     =============================================
#     Copyright 2005 by Sun Microsystems, Inc.
#     901 San Antonio Road, Palo Alto, CA 94303, USA
#
#     This library is free software; you can redistribute it and/or
#     modify it under the terms of the GNU Lesser General Public
#     License version 2.1, as published by the Free Software Foundation.
#
#     This library is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#     Lesser General Public License for more details.
#
#     You should have received a copy of the GNU Lesser General Public
#     License along with this library; if not, write to the Free Software
#     Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#     MA  02111-1307  USA
#
#*************************************************************************

EXTERNAL_WARNINGS_NOT_ERRORS := TRUE

PRJ=..$/..$/..
BFPRJ=..$/..

PRJNAME=binfilter
TARGET=goodies_base3d

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

AUTOSEG=true

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_goodies

# --- Files --------------------------------------------------------

SLOFILES=\
         $(SLO)$/goodies_b3dvolum.obj	\
         $(SLO)$/goodies_b3dcolor.obj	\
         $(SLO)$/goodies_b3dentty.obj	\
         $(SLO)$/goodies_b3dtrans.obj	\
         $(SLO)$/goodies_b3dlight.obj	\
         $(SLO)$/goodies_matril3d.obj	\
         $(SLO)$/goodies_b3dcompo.obj	\
         $(SLO)$/goodies_b3dgeom.obj	\
         $(SLO)$/goodies_vector3d.obj	\
         $(SLO)$/goodies_point4d.obj	\
         $(SLO)$/goodies_hmatrix.obj

.INCLUDE :  target.mk
