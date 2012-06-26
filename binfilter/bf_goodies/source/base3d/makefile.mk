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
TARGET=goodies_base3d

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
