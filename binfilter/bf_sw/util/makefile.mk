#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.18 $
#
#   last change: $Author: obo $ $Date: 2008-02-25 15:24:26 $
#
#   The Contents of this file are made available subject to
#   the terms of GNU Lesser General Public License Version 2.1.
#
#
#     GNU Lesser General Public License Version 2.1
#     =============================================
#     Copyright 2005 by Sun Microsystems, Inc.
#     901 San Antonio Road, Palo Alto, CA 94303, USA
#
#     This library is free software; you can redistribute it and/or
#     modify it under the terms of the GNU Lesser General Public
#     License version 2.1, as published by the Free Software Foundation.
#
#     This library is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#     Lesser General Public License for more details.
#
#     You should have received a copy of the GNU Lesser General Public
#     License along with this library; if not, write to the Free Software
#     Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#     MA  02111-1307  USA
#
#*************************************************************************

EXTERNAL_WARNINGS_NOT_ERRORS := TRUE

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
INC+= -I$(PRJ)$/inc$/bf_sw

DESK=T

RESLIB1NAME=bf_sw
MYRESLIBNAME=sw

# --- Allgemein -----------------------------------------------------------
.IF "$(OS)"=="IRIX"
LINKFLAGS+=-Wl,-LD_LAYOUT:lgot_buffer=40
.ENDIF

sw_res_files= \
    $(SRS)$/sw_app.srs          \
    $(SRS)$/sw_config.srs       \
    $(SRS)$/sw_dochdl.srs       \
    $(SRS)$/sw_fldui.srs        \
    $(SRS)$/sw_globdoc.srs      \
    $(SRS)$/sw_index.srs        \
    $(SRS)$/sw_misc.srs         \
    $(SRS)$/sw_shells.srs       \
    $(SRS)$/sw_utlui.srs        \
    $(SRS)$/sw_wrtsh.srs        

RESLIB1SRSFILES= \
    $(sw_res_files)

LIB1TARGET=$(LB)$/bf_swlib.lib
LIB1ARCHIV=$(LB)$/libbf_swlib.a
LIB1OBJFILES= \
        $(SLO)$/sw_w4wflt.obj \
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
    $(BFSO3LIB) \
    $(SVTOOLLIB) \
    $(TKLIB) \
    $(VCLLIB) \
    $(SVLLIB)	\
    $(SOTLIB) \
    $(UNOTOOLSLIB) \
    $(TOOLSLIB) \
    $(COMPHELPERLIB) \
    $(UCBHELPERLIB) \
    $(CPPUHELPERLIB) \
    $(CPPULIB) \
    $(VOSLIB) \
    $(SALLIB) \
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


#SHL2OBJS= \
#	$(OUT)$/slo$/sw_swmodule.obj \
#	$(OUT)$/slo$/sw_swdll.obj
#	$(SLO)$/sw_.obj		  ^ \ nicht vergessen!


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
    @echo   component_getImplementationEnvironment @50				>>$@
    @echo   component_writeInfo @51									>>$@
    @echo   component_getFactory @52								>>$@

.ENDIF

