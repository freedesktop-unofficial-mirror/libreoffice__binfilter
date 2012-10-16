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

PRJ=..$/..
BFPRJ=..

PRJNAME=binfilter
TARGET=bf_ofa

NO_HIDS=TRUE

# --- Settings ------------------------------------------------------------

.INCLUDE :	settings.mk
alllangiso=en-US

RSCLOCINC!:=$(RSCLOCINC);$(PRJ)$/RES
SOLARLIB+=-L$(LB)

# --- Allgemein -----------------------------------------------------------

RESLIB1LIST=\
    $(SRS)$/so3_src.srs 	

RESLIB1NAME=$(TARGET)
RESLIB1SRSFILES=$(RESLIB1LIST)

# -------------------------------------------------------------------------
LIB3TARGET= $(SLB)$/$(TARGET).lib
LIB3FILES=	$(SLB)$/offmgr_app.lib 

SHL2TARGET= $(TARGET)$(DLLPOSTFIX)
SHL2IMPLIB= $(TARGET)
SHL2LIBS=	$(SLB)$/$(TARGET).lib

# dynamic libraries
SHL2STDLIBS+= \
    $(BFSVTOOLLIB) \
    $(BFSVXLIB) \
    $(LEGACYSMGRLIB)	\
    $(BFBASICLIB) \
    $(TOOLSLIB) \
    $(CPPUHELPERLIB) \
    $(CPPULIB) \
    $(SALLIB)

.IF "$(GUI)"=="WNT"
SHL2STDLIBS += $(ADVAPI32LIB)
.ENDIF # WNT

SHL2DEF=	$(MISC)$/$(SHL2TARGET).def
SHL2BASE=	0x1de00000

DEF2NAME=	$(SHL2TARGET)
DEF2DEPN=	$(MISC)$/$(SHL2TARGET).flt
DEFLIB2NAME =$(TARGET)
DEF2DES 	=offmgr app-interface

# -------------------------------------------------------------------------

.IF "$(GUI)"=="WNT"
LIB4TARGET= $(LB)$/a$(TARGET).lib
LIB4FILES=	$(LB)$/$(TARGET).lib
.ENDIF

.IF "$(L10N_framework)"==""
.IF "$(BUILD_SOSL)"==""
.IF "$(depend)" == ""
ALL:\
    $(LIB3TARGET)			\
    $(INCCOM)$/class.lst	\
    ALLTAR

.ENDIF # "$(depend)" == ""
.ENDIF # "$(BUILD_SOSL)" == ""
.ENDIF

.INCLUDE :	target.mk

$(MISC)$/$(SHL2TARGET).flt: makefile.mk
    @echo ------------------------------
    @echo Making: $@
    @echo WEP>$@
    @echo PlugInApplication>>$@
    @echo __dt__17OfficeApplication>>$@
    @echo LibMain>>$@
    @echo _Impl>>$@
    @echo _Imp>>$@
    @echo solver>>$@
    @echo bad_alloc>>$@
    @echo exception12>>$@
.IF "$(GUI)"=="WNT"
    @echo __CT>>$@
.ENDIF

# ------------------------------------------------------------------
# Windows NT
# ------------------------------------------------------------------

$(INCCOM)$/class.lst:
.IF "$(BUILD_SOSL)"==""
.IF "$(GUI)$(CPU)$(UPDATER)"=="WNTIYES"
    -$(COPY) class.lst $@
.ELSE
    @echo nix
.ENDIF
.ENDIF			# "$(BUILD_SOSL)"==""
