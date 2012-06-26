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
TARGET=bf_sw

NO_HIDS=TRUE

.IF "$(CPU)"=="i386"
USE_LDUMP2=TRUE
.ENDIF


# --- Settings ------------------------------------------------------------

.INCLUDE :  settings.mk
alllangiso=en-US
INC+= -I$(PRJ)$/inc$/bf_sw

DESK=T

RESLIB1NAME=bf_sw
MYRESLIBNAME=sw

# --- Allgemein -----------------------------------------------------------

sw_res_files= \
    $(SRS)$/sw_app.srs          \
    $(SRS)$/sw_config.srs       \
    $(SRS)$/sw_fldui.srs        \
    $(SRS)$/sw_globdoc.srs      \
    $(SRS)$/sw_index.srs        \
    $(SRS)$/sw_misc.srs         \
    $(SRS)$/sw_shells.srs       \
    $(SRS)$/sw_utlui.srs

RESLIB1SRSFILES= \
    $(sw_res_files)

LIB1TARGET=$(LB)$/bf_swlib.lib
LIB1ARCHIV=$(LB)$/libbf_swlib.a
LIB1OBJFILES= \
        $(SLO)$/sw_swlib.obj \
        $(SLO)$/sw_swcomlib.obj

SHL2TARGET= $(TARGET)$(DLLPOSTFIX)
SHL2VERSIONMAP= $(TARGET).map
SHL2IMPLIB= _$(TARGET)
SHL2LIBS= \
    $(SLB)$/sw_core1.lib\
    $(SLB)$/sw_core2.lib\
    $(SLB)$/sw_filter.lib\
        $(SLB)$/sw_ui.lib

.IF "$(OS)" != "MACOSX"
# static libraries
SHL2STDLIBS+= $(BFSCHLIB) $(BFSMLIB)
.ENDIF

# dynamic libraries
SHL2STDLIBS+= \
    $(BFOFALIB) \
    $(BFSVXLIB) \
    $(LEGACYSMGRLIB)	\
    $(BFXMLOFFLIB) \
    $(BFBASICLIB) \
    $(BFGOODIESLIB) \
    $(BFSVTOOLLIB) \
    $(BFSO3LIB) \
    $(TKLIB) \
    $(VCLLIB) \
    $(SOTLIB) \
    $(UNOTOOLSLIB) \
    $(TOOLSLIB) \
        $(COMPHELPERLIB) \
    $(UCBHELPERLIB) \
    $(CPPUHELPERLIB) \
    $(CPPULIB) \
    $(SALLIB) \
    $(SALHELPERLIB) \
        $(SVTOOLLIB) \
    $(ICUUCLIB)


.IF "$(OS)" == "MACOSX"
# static libraries
SHL2STDLIBS+= $(BFSCHLIB) $(BFSMLIB)
.ENDIF

.IF "$(GUI)"=="WNT"
SHL2STDLIBS+= $(ADVAPI32LIB)
.ENDIF # WNT

SHL2DEPN=   \
    $(SLB)$/sw_core1.lib\
    $(SLB)$/sw_core2.lib\
    $(SLB)$/sw_filter.lib\
        $(SLB)$/sw_ui.lib


SHL2DEF=    $(MISC)$/$(SHL2TARGET).def
SHL2BASE=	0x1e000000

.INCLUDE :  target.mk

$(MISCX)$/$(SHL2TARGET).flt:
    @echo ------------------------------
    @echo Making: $@
    @echo WEP>$@
    @echo LIBMAIN>>$@
    @echo LibMain>>$@

# ------------------------------------------------------------------
# Windows NT
# ------------------------------------------------------------------

.IF "$(GUI)" == "WNT"

$(MISC)$/$(SHL2TARGET).def:  makefile.mk
    @echo ------------------------------
    @echo Making: $@
    @echo LIBRARY     $(SHL2TARGET)                                  >$@
.IF "$(COM)"!="GCC"
    @echo DESCRIPTION 'SWriter4 DLL'                                 >>$@
    @echo DATA        READ WRITE NONSHARED                          >>$@
.ENDIF
    @echo EXPORTS                                                   >>$@
    @echo   CreateSwDocShellDll @20                            >>$@
    @echo   CreateSwWebDocShellDll @30                            >>$@
    @echo   CreateSwGlobalDocShellDll @40                            >>$@
    @echo   CreateObjSwDocShellDll @21                         >>$@
    @echo   CreateObjSwWebDocShellDll @22                         >>$@
    @echo   CreateObjSwGlobalDocShellDll @23                         >>$@
    @echo   InitSwDll @24                                          >>$@
    @echo   DeInitSwDll @25                                        >>$@
    @echo   component_getFactory @52								>>$@

.ENDIF


# ------------------------------------------------------------------
# OS/2
# ------------------------------------------------------------------

.IF "$(GUI)" == "OS2"

$(MISC)$/$(SHL2TARGET).def:  makefile.mk
    @echo ------------------------------
    @echo Making: $@
    @echo LIBRARY     $(SHL2TARGET8) INITINSTANCE TERMINSTANCE      >$@
    @echo DESCRIPTION 'SWriter4 DLL'                                >>$@
    @echo DATA        MULTIPLE                                      >>$@
    @echo EXPORTS                                                   >>$@
    @echo   _CreateSwDocShellDll                                    >>$@
    @echo   _CreateSwWebDocShellDll                                 >>$@
    @echo   _CreateSwGlobalDocShellDll                              >>$@
    @echo   _CreateObjSwDocShellDll                                 >>$@
    @echo   _CreateObjSwWebDocShellDll                              >>$@
    @echo   _CreateObjSwGlobalDocShellDll                           >>$@
    @echo   _InitSwDll                                              >>$@
    @echo   _DeInitSwDll                                            >>$@
    @echo   _component_getFactory    			            >>$@

.ENDIF

ALLTAR : $(MISC)/bf_sw.component

$(MISC)/bf_sw.component .ERRREMOVE : $(SOLARENV)/bin/createcomponent.xslt \
        bf_sw.component
    $(XSLTPROC) --nonet --stringparam uri \
        '$(COMPONENTPREFIX_BASIS_NATIVE)$(SHL2TARGETN:f)' -o $@ \
        $(SOLARENV)/bin/createcomponent.xslt bf_sw.component
