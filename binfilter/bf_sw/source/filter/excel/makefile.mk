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

# makefile Verteiler

PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PRJNAME=binfilter
TARGET=sw_excel

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw

CXXFILES = \
        sw_fltglbls.cxx \
        sw_exctools.cxx \
        sw_excread.cxx \
        sw_excimpop.cxx \
        sw_exlpar.cxx \


SLOFILES =  \
        $(SLO)$/sw_fltglbls.obj \
        $(SLO)$/sw_exctools.obj \
        $(SLO)$/sw_excread.obj \
        $(SLO)$/sw_excimpop.obj \
        $(SLO)$/sw_exlpar.obj


# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

