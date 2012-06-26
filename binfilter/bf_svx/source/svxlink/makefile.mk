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
TARGET=svx_svxlink

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
alllangiso=en-US
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Files --------------------------------------------------------

.IF "$(header)" == ""

CXXFILES=\
    svx_linkmgr.cxx		\
    svx_fileobj.cxx

SLOFILES=\
        $(SLO)$/svx_linkmgr.obj	\
        $(SLO)$/svx_fileobj.obj

SRS1NAME=$(TARGET)
SRC1FILES=	\
        svx_linkmgr.src

.IF "$(GUI)" == "WNT"
NOOPTFILES=\
    $(SLO)$/svx_fileobj.obj
.ENDIF

.ENDIF

# ==========================================================================

.INCLUDE :  target.mk


