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
TARGET=svdde

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_svtools

# --- Files --------------------------------------------------------

.IF "$(GUIBASE)"=="WIN"

SLOFILES=	$(SLO)$/svt_ddecli.obj	\
            $(SLO)$/svt_ddesvr.obj	\
            $(SLO)$/svt_ddedata.obj	\
            $(SLO)$/svt_ddestrg.obj	\
            $(SLO)$/svt_ddewrap.obj \
            $(SLO)$/svt_ddeinf.obj
.ELSE

SLOFILES=	$(SLO)$/svt_ddedummy.obj	\

.ENDIF

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk


