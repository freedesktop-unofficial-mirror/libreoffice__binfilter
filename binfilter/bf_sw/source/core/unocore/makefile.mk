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
TARGET=sw_unocore

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
EXCEPTIONSFILES=	\
        $(SLO)$/sw_swunohelper.obj\
        $(SLO)$/sw_SwXTextDefaults.obj\
    $(SLO)$/sw_unobkm.obj\
    $(SLO)$/sw_unoevent.obj\
    $(SLO)$/sw_unocrsrhelper.obj\
    $(SLO)$/sw_unoevtlstnr.obj\
    $(SLO)$/sw_unoftn.obj\
    $(SLO)$/sw_unorefmk.obj\
    $(SLO)$/sw_unosect.obj\
    $(SLO)$/sw_unosett.obj\
    $(SLO)$/sw_unocoll.obj\
    $(SLO)$/sw_unodraw.obj\
    $(SLO)$/sw_unofield.obj\
    $(SLO)$/sw_unoframe.obj\
    $(SLO)$/sw_unoidx.obj\
    $(SLO)$/sw_unoobj.obj\
    $(SLO)$/sw_unoobj2.obj\
    $(SLO)$/sw_unoparagraph.obj\
    $(SLO)$/sw_unoport.obj\
    $(SLO)$/sw_unoredline.obj\
    $(SLO)$/sw_unoredlines.obj\
    $(SLO)$/sw_unosrch.obj\
    $(SLO)$/sw_unostyle.obj\
    $(SLO)$/sw_unotbl.obj \
    $(SLO)$/sw_TextCursorHelper.obj \
    $(SLO)$/sw_unotext.obj

.IF "$(GUI)$(COM)$(CPU)" == "WNTMSCI"
EXCEPTIONSNOOPTFILES =$(SLO)$/sw_unoportenum.obj
.ELSE
EXCEPTIONSFILES +=$(SLO)$/sw_unoportenum.obj
.ENDIF


SLOFILES =	\
        $(SLO)$/sw_swunohelper.obj\
        $(SLO)$/sw_SwXTextDefaults.obj\
        $(SLO)$/sw_unoportenum.obj\
    $(SLO)$/sw_unobkm.obj\
    $(SLO)$/sw_unoevent.obj\
    $(SLO)$/sw_unocrsrhelper.obj\
    $(SLO)$/sw_unoevtlstnr.obj\
    $(SLO)$/sw_unoftn.obj\
    $(SLO)$/sw_unorefmk.obj\
    $(SLO)$/sw_unosect.obj\
    $(SLO)$/sw_unosett.obj\
    $(SLO)$/sw_unocoll.obj\
    $(SLO)$/sw_unodraw.obj\
    $(SLO)$/sw_unofield.obj\
    $(SLO)$/sw_unoframe.obj\
    $(SLO)$/sw_unoidx.obj\
    $(SLO)$/sw_unoobj.obj\
    $(SLO)$/sw_unoobj2.obj\
    $(SLO)$/sw_unoparagraph.obj\
    $(SLO)$/sw_unoport.obj\
    $(SLO)$/sw_unoredline.obj\
    $(SLO)$/sw_unoredlines.obj\
    $(SLO)$/sw_unosrch.obj\
    $(SLO)$/sw_unostyle.obj\
    $(SLO)$/sw_unotbl.obj \
    $(SLO)$/sw_TextCursorHelper.obj \
    $(SLO)$/sw_unotext.obj\
        $(SLO)$/sw_unoclbck.obj\
        $(SLO)$/sw_unomap.obj\
        $(SLO)$/sw_unoprnms.obj



# --- Targets -------------------------------------------------------


.INCLUDE :	target.mk

