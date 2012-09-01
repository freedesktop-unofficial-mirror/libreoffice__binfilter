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
PRJNAME=binfilter
TARGET=misc

ENABLE_EXCEPTIONS := TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
alllangiso=en-US
INC+= -I$(PRJ)$/inc$/bf_svtools

# --- Files --------------------------------------------------------

SRS1NAME=ehdl
SRC1FILES=\
    ctrltool.src\
    errtxt.src

SLOFILES=\
    $(SLO)$/svt_asynclink.obj			\
    $(SLO)$/svt_ctrltool.obj			\
    $(SLO)$/svt_imageresourceaccess.obj \
    $(SLO)$/svt_templatefoldercache.obj \
    $(SLO)$/svt_urihelper.obj           \
    $(SLO)$/svt_ehdl.obj                \
    $(SLO)$/svt_flbytes.obj             \
    $(SLO)$/svt_imap.obj                \
    $(SLO)$/svt_imap2.obj               \
    $(SLO)$/svt_imap3.obj               \
    $(SLO)$/svt_ownlist.obj             \
    $(SLO)$/svt_vcldata.obj             \
    $(SLO)$/svt_restrictedpaths.obj	\
    $(SLO)$/tl_tstring.obj		\
    $(SLO)$/tl_tustring.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

