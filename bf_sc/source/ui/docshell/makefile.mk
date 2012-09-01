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
TARGET=sc_docshell

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sc
# --- Files --------------------------------------------------------

SLOFILES =  \
        $(SLO)$/sc_docsh.obj	\
        $(SLO)$/sc_docsh2.obj	\
        $(SLO)$/sc_docsh3.obj	\
        $(SLO)$/sc_docsh4.obj   	\
        $(SLO)$/sc_docsh5.obj   	\
        $(SLO)$/sc_docsh6.obj   	\
        $(SLO)$/sc_tablink.obj   	\
        $(SLO)$/sc_arealink.obj   	\
        $(SLO)$/sc_dbdocfun.obj 	\
        $(SLO)$/sc_dbdocimp.obj 	\
        $(SLO)$/sc_docfunc.obj	\
        $(SLO)$/sc_pntlock.obj \
        $(SLO)$/sc_sizedev.obj \
        $(SLO)$/sc_editable.obj


EXCEPTIONSFILES= \
        $(SLO)$/sc_dbdocimp.obj


# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

