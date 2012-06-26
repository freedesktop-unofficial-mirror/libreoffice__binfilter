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
TARGET=sw_swg

NO_HIDS=TRUE

AUTOSEG=true

# --- Settings -----------------------------------------------------

.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw
.IF "$(GUI)$(COM)" == "WINMSC"
LIBFLAGS=/NOI /NOE /PAGE:512
.ENDIF

# --- Files --------------------------------------------------------

SLOFILES =  \
        $(SLO)$/sw_rdcont.obj \
        $(SLO)$/sw_rdflds.obj \
        $(SLO)$/sw_rdfmts.obj \
        $(SLO)$/sw_rdhnt.obj \
        $(SLO)$/sw_rdmisc.obj \
        $(SLO)$/sw_rdnds.obj \
        $(SLO)$/sw_rdnum.obj \
        $(SLO)$/sw_rdpage.obj \
        $(SLO)$/sw_rdswg.obj \
        $(SLO)$/sw_rdtox.obj \
        $(SLO)$/sw_swgpar.obj \
        $(SLO)$/sw_swgstr.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk
