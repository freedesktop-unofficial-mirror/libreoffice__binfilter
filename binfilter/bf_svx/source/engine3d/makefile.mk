#
# This file is part of the LibreOffice project.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# This file incorporates work covered by the following license notice:
#
#   Licensed to the Apache Software Foundation (ASF) under one or more
#   contributor license agreements. See the NOTICE file distributed
#   with this work for additional information regarding copyright
#   ownership. The ASF licenses this file to you under the Apache
#   License, Version 2.0 (the "License"); you may not use this file
#   except in compliance with the License. You may obtain a copy of
#   the License at http://www.apache.org/licenses/LICENSE-2.0 .
#

PRJ=..$/..$/..
BFPRJ=..$/..

PRJNAME=binfilter
TARGET=svx_engine3d

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
alllangiso=en-US
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Files --------------------------------------------------------

SRS1NAME=svx_engine3d
SRC1FILES=\
        svx_float3d.src

SLOFILES= \
        $(SLO)$/svx_svx3ditems.obj	\
        $(SLO)$/svx_deflt3d.obj		\
        $(SLO)$/svx_class3d.obj		\
        $(SLO)$/svx_volume3d.obj		\
        $(SLO)$/svx_viewpt3d.obj		\
        $(SLO)$/svx_camera3d.obj		\
        $(SLO)$/svx_poly3d.obj 		\
        $(SLO)$/svx_polygn3d.obj 		\
        $(SLO)$/svx_objfac3d.obj 	\
        $(SLO)$/svx_obj3d.obj 		\
        $(SLO)$/svx_light3d.obj 		\
        $(SLO)$/svx_dlight3d.obj 	\
        $(SLO)$/svx_plight3d.obj 	\
        $(SLO)$/svx_pntobj3d.obj     \
        $(SLO)$/svx_polyob3d.obj		\
        $(SLO)$/svx_scene3d.obj		\
        $(SLO)$/svx_polysc3d.obj		\
        $(SLO)$/svx_cube3d.obj		\
        $(SLO)$/svx_sphere3d.obj		\
        $(SLO)$/svx_extrud3d.obj     \
        $(SLO)$/svx_lathe3d.obj		\
        $(SLO)$/svx_label3d.obj		\
        $(SLO)$/svx_view3d.obj		\
        $(SLO)$/svx_e3dcmpt.obj       

.INCLUDE :  target.mk

