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
TARGET=smath3

NO_HIDS=TRUE

LIBTARGET=NO

# --- Settings -----------------------------------------------------------

.INCLUDE :  settings.mk
alllangiso=en-US
INC+= -I$(PRJ)$/inc$/bf_starmath

# --- Files --------------------------------------------------------

RESLIB1NAME=bf_sm
RESLIB1SRSFILES=\
    $(SRS)$/starmath_smres.srs 

SHL1TARGET= bf_sm$(DLLPOSTFIX)
SHL1IMPLIB= bf_smimp

SHL1VERSIONMAP= bf_sm.map
SHL1DEF=$(MISC)$/$(SHL1TARGET).def
DEF1NAME=		$(SHL1TARGET)

SHL1STDLIBS= \
            $(BFSVXLIB) \
            $(LEGACYSMGRLIB)	\
            $(BFSO3LIB) \
            $(BFXMLOFFLIB) \
            $(BFSVTOOLLIB) \
            $(TKLIB) \
            $(VCLLIB) \
            $(SOTLIB) \
            $(UNOTOOLSLIB) \
            $(TOOLSLIB) \
            $(COMPHELPERLIB) \
            $(CPPUHELPERLIB) \
            $(CPPULIB) \
            $(SALLIB)

SHL1DEPN=	makefile.mk
SHL1LIBS=   $(SLB)$/bf_starmath.lib

.IF "$(GUI)" != "UNX"
.IF "$(GUI)$(COM)" != "WNTGCC"
SHL1OBJS=   $(SLO)$/starmath_smdll.obj
.ENDIF
.ENDIF # ! UNX

.IF "$(GUI)" == "WNT"
SHL1RES=	$(RCTARGET)
.ENDIF # WNT

# --- Targets -------------------------------------------------------------

.INCLUDE :  target.mk

ALLTAR : $(MISC)/bf_sm.component

$(MISC)/bf_sm.component .ERRREMOVE : $(SOLARENV)/bin/createcomponent.xslt \
        bf_sm.component
    $(XSLTPROC) --nonet --stringparam uri \
        '$(COMPONENTPREFIX_BASIS_NATIVE)$(SHL1TARGETN:f)' -o $@ \
        $(SOLARENV)/bin/createcomponent.xslt bf_sm.component
