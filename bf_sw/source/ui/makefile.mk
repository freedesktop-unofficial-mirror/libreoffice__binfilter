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
TARGET=sw_ui

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw

.IF "$(GUI)" != "OS2"
.IF "$(GUI)" != "WNT"
.IF "$(GUI)" != "MAC"
.IF "$(COM)" != "BLC"
.IF "$(COM)" != "WTC"
LIBFLAGS=/NOI /NOE /PAGE:256
.ENDIF
.ENDIF
.ENDIF
.ENDIF
.ENDIF

################################################################

# andere Label als Verzeichnisnamen fuer VC++/NT

LIB1TARGET=$(SLB)$/sw_ui.lib
LIB1FILES= \
        $(SLB)$/sw_app.lib      \
        $(SLB)$/sw_config.lib   \
        $(SLB)$/sw_dbui.lib     \
        $(SLB)$/sw_utlui.lib    \
        $(SLB)$/sw_fldui.lib    \
        $(SLB)$/sw_globdoc.lib  \
        $(SLB)$/sw_index.lib    \
        $(SLB)$/sw_unoidl.lib   \
        $(SLB)$/sw_web.lib

.INCLUDE :  target.mk

################################################################

kill:
    @$(RM) $(SLB)$/ui.lst
    @$(RM) $(SLB)$/ui.lib

