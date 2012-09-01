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

PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PRJNAME=binfilter
TARGET=sw_bastyp

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw
# --- Files --------------------------------------------------------

CXXFILES = \
        sw_bparr.cxx \
        sw_breakit.cxx \
        sw_calc.cxx \
                sw_checkit.cxx \
        sw_index.cxx \
        sw_init.cxx \
        sw_ring.cxx \
        sw_swcache.cxx \
        sw_swrect.cxx \
        sw_swregion.cxx \
        sw_swtypes.cxx

SLOFILES =  \
        $(SLO)$/sw_bparr.obj \
        $(SLO)$/sw_breakit.obj \
        $(SLO)$/sw_calc.obj \
                $(SLO)$/sw_checkit.obj \
        $(SLO)$/sw_index.obj \
        $(SLO)$/sw_init.obj \
        $(SLO)$/sw_ring.obj \
        $(SLO)$/sw_swcache.obj \
        $(SLO)$/sw_swrect.obj \
        $(SLO)$/sw_swregion.obj \
        $(SLO)$/sw_swtypes.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

