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
TARGET=svx_items

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :	settings.mk
alllangiso=en-US
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Files --------------------------------------------------------

SRS1NAME=svx_svxitems
SRC1FILES =  \
        svx_svxerr.src		\
        svx_svxitems.src

SLOFILES=	\
        $(SLO)$/svx_writingmodeitem.obj \
        $(SLO)$/svx_frmitems.obj \
        $(SLO)$/svx_paraitem.obj \
        $(SLO)$/svx_textitem.obj \
        $(SLO)$/svx_postattr.obj	\
        $(SLO)$/svx_flditem.obj \
        $(SLO)$/svx_svxfont.obj \
        $(SLO)$/svx_pageitem.obj	\
        $(SLO)$/svx_paperinf.obj	\
        $(SLO)$/svx_drawitem.obj	\
        $(SLO)$/svx_algitem.obj \
        $(SLO)$/svx_rotmodit.obj \
        $(SLO)$/svx_svxerr.obj	\
        $(SLO)$/svx_zoomitem.obj \
        $(SLO)$/svx_chrtitem.obj	\
        $(SLO)$/svx_bulitem.obj \
        $(SLO)$/svx_e3ditem.obj \
        $(SLO)$/svx_numitem.obj \
        $(SLO)$/svx_grfitem.obj \
        $(SLO)$/svx_clipfmtitem.obj \
        $(SLO)$/svx_xmlcnitm.obj

EXCEPTIONSFILES= \
        $(SLO)$/svx_paraitem.obj \
        $(SLO)$/svx_frmitems.obj \
        $(SLO)$/svx_numitem.obj\
        $(SLO)$/svx_xmlcnitm.obj

.INCLUDE :	target.mk

