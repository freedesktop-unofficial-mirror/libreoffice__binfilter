#*************************************************************************
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
# 
# Copyright 2008 by Sun Microsystems, Inc.
#
# OpenOffice.org - a multi-platform office productivity suite
#
# $RCSfile: makefile.mk,v $
#
# $Revision: 1.3 $
#
# This file is part of OpenOffice.org.
#
# OpenOffice.org is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License version 3
# only, as published by the Free Software Foundation.
#
# OpenOffice.org is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License version 3 for more details
# (a copy is included in the LICENSE file that accompanied this code).
#
# You should have received a copy of the GNU Lesser General Public License
# version 3 along with OpenOffice.org.  If not, see
# <http://www.openoffice.org/license.html>
# for a copy of the LGPLv3 License.
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
