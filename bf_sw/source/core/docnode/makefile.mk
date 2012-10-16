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
TARGET=sw_docnode

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :	$(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :	settings.mk
.INCLUDE :	$(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw
.IF "$(GUI)$(COM)" == "WINMSC"
LIBFLAGS=/NOI /NOE /PAGE:512
.ENDIF


# --- Files --------------------------------------------------------

CXXFILES = \
        sw_ndindex.cxx \
        sw_ndcopy.cxx \
        sw_ndnotxt.cxx \
        sw_ndnum.cxx \
        sw_ndsect.cxx \
        sw_ndtbl.cxx \
        sw_ndtbl1.cxx \
        sw_node.cxx \
        sw_node2lay.cxx \
        sw_nodes.cxx \
        sw_section.cxx \
        sw_swbaslnk.cxx



SLOFILES =	\
        $(SLO)$/sw_ndindex.obj \
        $(SLO)$/sw_ndcopy.obj \
        $(SLO)$/sw_ndnotxt.obj \
        $(SLO)$/sw_ndnum.obj \
        $(SLO)$/sw_ndsect.obj \
        $(SLO)$/sw_ndtbl.obj \
        $(SLO)$/sw_ndtbl1.obj \
        $(SLO)$/sw_node.obj \
        $(SLO)$/sw_node2lay.obj \
        $(SLO)$/sw_nodes.obj \
        $(SLO)$/sw_section.obj \
        $(SLO)$/sw_swbaslnk.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :	target.mk

