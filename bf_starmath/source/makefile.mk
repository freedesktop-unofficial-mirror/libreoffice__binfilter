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
TARGET=bf_starmath

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
alllangiso=en-US
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_starmath
# --- Files --------------------------------------------------------

SMDLL=TRUE

SRS2NAME =starmath_smres
SRC2FILES = starmath_smres.src   \
            starmath_symbol.src	\
            starmath_commands.src

SLOFILES =  \
        $(SLO)$/starmath_register.obj \
        $(SLO)$/starmath_symbol.obj \
        $(SLO)$/starmath_cfgitem.obj \
        $(SLO)$/starmath_config.obj \
        $(SLO)$/starmath_document.obj \
        $(SLO)$/starmath_mathml.obj \
        $(SLO)$/starmath_format.obj \
        $(SLO)$/starmath_node.obj \
        $(SLO)$/starmath_parse.obj \
        $(SLO)$/starmath_utility.obj \
        $(SLO)$/starmath_smdll.obj \
        $(SLO)$/starmath_smmod.obj \
        $(SLO)$/starmath_rect.obj \
        $(SLO)$/starmath_unomodel.obj \
        $(SLO)$/starmath_unodoc.obj

EXCEPTIONSFILES =   \
        $(SLO)$/starmath_register.obj  \
        $(SLO)$/starmath_mathml.obj \
        $(SLO)$/starmath_viewhdl.obj \
        $(SLO)$/starmath_unomodel.obj \
        $(SLO)$/starmath_unodoc.obj


LIB2TARGET =    $(SLB)$/bf_ysm.lib
LIB2ARCHIV =    $(LB)$/libbf_ysm.a
LIB2OBJFILES  =    $(SLO)$/starmath_smlib.obj

DEPOBJFILES = $(SLO)$/starmath_smlib.obj

# --- Targets -------------------------------------------------------

.IF "$(GUI)"=="UNX" || "$(GUI)"=="MAC"
CDEFS+=-DUSE_POLYGON
.ENDIF

.INCLUDE :  target.mk

$(SLO)$/starmath_smlib.obj : $(INCCOM)$/dllname.hxx

$(INCCOM)$/dllname.hxx: makefile.mk
.IF "$(GUI)"=="UNX"
    $(RM) $@
    echo \#define DLL_NAME \"$(DLLPRE)bf_sm$(DLLPOSTFIX)$(DLLPOST)\" >$@
.ELSE
    echo $(EMQ)#define DLL_NAME $(EMQ)"$(DLLPRE)bf_sm$(DLLPOSTFIX)$(DLLPOST)$(EMQ)" >$@
.ENDIF

$(SRS)$/starmath_smres.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc
