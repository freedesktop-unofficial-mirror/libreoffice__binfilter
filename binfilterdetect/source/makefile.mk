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
TARGET=binfilterdetect

NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE
LIBTARGET=NO
DLLTARGET=bindet

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk

# --- Files --------------------------------------------------------

SLOFILES =      \
        $(SLO)$/bindetect.obj

SHL1DEPN=makefile.mk
SHL1OBJS=$(SLOFILES)
SHL1TARGET=$(DLLTARGET)$(DLLPOSTFIX)
SHL1IMPLIB=i$(DLLTARGET)
SHL1DEF=$(MISC)$/$(SHL1TARGET).def
DEF1NAME=$(SHL1TARGET)
SHL1VERSIONMAP=$(SOLARENV)/src/component.map

SHL1STDLIBS= \
    $(BFSVTOOLLIB)	\
    $(SOTLIB)	\
    $(VCLLIB)	\
    $(TOOLSLIB)	\
    $(CPPUHELPERLIB)\
    $(CPPULIB)	\
    $(COMPHELPERLIB) \
    $(UNOTOOLSLIB) \
    $(SALLIB)

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

ALLTAR : $(MISC)/bindet.component

$(MISC)/bindet.component .ERRREMOVE : $(SOLARENV)/bin/createcomponent.xslt \
        bindet.component
    $(XSLTPROC) --nonet --stringparam uri \
        '$(COMPONENTPREFIX_BASIS_NATIVE)$(SHL1TARGETN:f)' -o $@ \
        $(SOLARENV)/bin/createcomponent.xslt bindet.component
