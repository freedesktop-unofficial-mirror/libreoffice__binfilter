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
TARGET=bf_go

NO_HIDS=TRUE

LIBTARGET=NO

# --- Settings -----------------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_go

# --- Files --------------------------------------------------------

LIB1TARGET=$(SLB)$/bf_go.lib
LIB1FILES=\
   $(SLB)$/goodies_base2d.lib	\
   $(SLB)$/goodies_base3d.lib

SHL1TARGET= bf_go$(DLLPOSTFIX)
SHL1IMPLIB= bf_go
SHL1DEF=$(MISC)$/$(SHL1TARGET).def
SHL1LIBS=	$(SLB)$/bf_go.lib

DEF1NAME	=$(SHL1TARGET)
DEF1DEPN	=$(MISC)$/$(SHL1TARGET).flt \
        $(LIB1TARGET)

DEF1DES		=Bf_Goodies
DEFLIB1NAME	=bf_go

SHL1STDLIBS= \
            $(BFSVTOOLLIB) \
            $(SVTOOLLIB)		\
            $(TOOLSLIB)			\
            $(SALLIB)

# --- Targets -------------------------------------------------------------

.INCLUDE :  target.mk

# --- Goodies-Filter-Datei ---

$(MISC)$/$(SHL1TARGET).flt: makefile.mk
    @echo ------------------------------
    @echo Making: $@
        @echo _Impl>$@
    @echo WEP>>$@
        @echo m_pLoader>$@
    @echo LIBMAIN>>$@
    @echo LibMain>>$@
        @echo CT>>$@
