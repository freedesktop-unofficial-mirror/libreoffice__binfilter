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

BFPRJ=..
PRJ=..$/..

PRJNAME=binfilter
TARGET=bf_sb

# --- Settings ---------------------------------------------------

.INCLUDE :  settings.mk

# --- Allgemein ---------------------------------------------------

LIB1TARGET=$(SLB)$/$(TARGET).lib
LIB1FILES=      \
    $(SLB)$/basic_basicmgr.lib \
    $(SLB)$/basic_sbx.lib \
    $(SLB)$/basic_classes.lib \
    $(SLB)$/basic_comp.lib \
    $(SLB)$/basic_runtime.lib

SHL1TARGET=$(TARGET)$(DLLPOSTFIX)
SHL1IMPLIB=$(TARGET)

SHL1STDLIBS= \
            $(TOOLSLIB) \
            $(CPPULIB) \
            $(CPPUHELPERLIB) \
            $(BFSVTOOLLIB) \
            $(SALLIB) \
            $(COMPHELPERLIB) \
            $(UNOTOOLSLIB) \
            $(SOTLIB) \
            $(VCLLIB)

.IF "$(GUI)"=="WNT"
SHL1STDLIBS+=   \
    $(UWINAPILIB)	\
    $(OLEAUT32LIB)
.ENDIF # WNT

SHL1DEF=    $(MISC)$/$(SHL1TARGET).def
SHL1LIBS=   $(SLB)$/$(TARGET).lib

DEF1NAME    =$(SHL1TARGET)
DEF1DEPN    =   \
    $(MISC)$/$(SHL1TARGET).flt

DEFLIB1NAME =$(TARGET)

# --- Targets -----------------------------------------------------------

.INCLUDE :  target.mk
 
# --- Basic-Filter-Datei ---

$(MISC)$/$(SHL1TARGET).flt: makefile.mk
    @echo ------------------------------
    @echo Making: $@
    @echo __CT >> $@


