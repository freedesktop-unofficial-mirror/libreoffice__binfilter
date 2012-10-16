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
TARGET=schart3

NO_HIDS=TRUE

LIBTARGET=NO

# --- Settings -----------------------------------------------------------
.INCLUDE :  settings.mk
alllangiso=en-US
INC+= -I$(PRJ)$/inc$/bf_sch
IENV!:=$(IENV);$(RES);..$/res

# --- Files --------------------------------------------------------

RESLIB1LIST=\
    $(SRS)$/sch_app.srs	\
    $(SRS)$/sch_core.srs	

RESLIB1NAME=bf_sch
RESLIB1SRSFILES=\
    $(RESLIB1LIST)

LIB2TARGET= $(SLB)$/sch_schmod.lib
LIB2OBJFILES=	$(SLO)$/sch_schmod.obj

LIB3TARGET= $(SLB)$/bf_sch.lib
LIB3FILES=	$(SLB)$/sch_core.lib \
        $(SLB)$/sch_app.lib \
        $(SLB)$/sch_docshell.lib \
        $(SLB)$/sch_chxchart.lib \
        $(SLB)$/sch_xml.lib 


SHL1TARGET= bf_sch$(DLLPOSTFIX)
SHL1IMPLIB= bf_schi

SHL1VERSIONMAP= bf_sch.map
SHL1DEF=$(MISC)$/$(SHL1TARGET).def
DEF1NAME=$(SHL1TARGET)

SHL1STDLIBS=\
    $(BFSVXLIB)	\
    $(LEGACYSMGRLIB)	\
    $(BFSO3LIB)	\
    $(BFGOODIESLIB)	\
    $(BFSVTOOLLIB)	\
    $(VCLLIB)	\
    $(SOTLIB)	\
    $(UNOTOOLSLIB) \
    $(TOOLSLIB)	\
    $(COMPHELPERLIB) \
    $(CPPUHELPERLIB) \
    $(CPPULIB) \
    $(SALLIB)
    

SHL1BASE=	0x1d100000
SHL1LIBS=   $(LIB3TARGET)

.IF "$(GUI)"!="UNX"
.IF "$(GUI)$(COM)" != "WNTGCC"
SHL1OBJS=   $(SLO)$/sch_schdll.obj
.ENDIF
.ENDIF # ! UNX

.IF "$(GUI)" == "WNT" || "$(GUI)" == "WIN"
SHL1RES=	$(RCTARGET)
.ENDIF # WNT || WIN

# --- Targets -------------------------------------------------------------

.INCLUDE :  target.mk

ALLTAR : $(MISC)/bf_sch.component

$(MISC)/bf_sch.component .ERRREMOVE : $(SOLARENV)/bin/createcomponent.xslt \
        bf_sch.component
    $(XSLTPROC) --nonet --stringparam uri \
        '$(COMPONENTPREFIX_BASIS_NATIVE)$(SHL1TARGETN:f)' -o $@ \
        $(SOLARENV)/bin/createcomponent.xslt bf_sch.component
