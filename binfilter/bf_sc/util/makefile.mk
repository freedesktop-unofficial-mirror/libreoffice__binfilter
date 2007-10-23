#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.20 $
#
#   last change: $Author: vg $ $Date: 2007-10-23 13:33:12 $
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
TARGET=scalc3

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_sc
IENV!:=$(IENV);..$/res

.IF "$(OS)"=="IRIX"
LINKFLAGS+=-Wl,-LD_LAYOUT:lgot_buffer=30
.ENDIF

# --- Resourcen ----------------------------------------------------

RESLIB1LIST=\
    $(SRS)$/sc_ui.srs		\
    $(SRS)$/sc_dbgui.srs	\
    $(SRS)$/sc_core.srs 	\

RESLIB1NAME=bf_sc
RESLIB1SRSFILES=\
    $(RESLIB1LIST)

# --- StarClac DLL

SHL1TARGET= bf_sc$(UPD)$(DLLPOSTFIX)
SHL1VERSIONMAP= bf_sc.map
SHL1IMPLIB= bf_sci

.IF "$(OS)" != "MACOSX"
# static libraries
SHL1STDLIBS+= $(BFSCHLIB)
.ENDIF

# dynamic libraries
SHL1STDLIBS+=       \
    $(BFBASICLIB)		\
       $(LEGACYSMGRLIB)	\
    $(BFSO3LIB)		\
    $(SVTOOLLIB)	\
    $(SVLLIB)		\
    $(BFSVXLIB)		\
    $(BFGOODIESLIB)	\
    $(BFOFALIB)		\
    $(VCLLIB)		\
    $(CPPULIB)		\
    $(CPPUHELPERLIB)	\
    $(COMPHELPERLIB)	\
    $(UCBHELPERLIB)	\
    $(TKLIB)		\
    $(VOSLIB)		\
    $(SALLIB)		\
    $(TOOLSLIB)		\
    $(I18NISOLANGLIB)   \
    $(UNOTOOLSLIB)  \
    $(SOTLIB)		\
    $(BFXMLOFFLIB)	\
    $(DBTOOLSLIB)


.IF "$(OS)" == "MACOSX"
# static libraries must come at the end of list on MacOSX
SHL1STDLIBS+= $(BFSCHLIB)
.ENDIF


SHL1LIBS=   $(LIB3TARGET) $(LIB4TARGET)

.IF "$(GUI)"!="UNX"
.IF "$(GUI)$(COM)" != "WNTGCC"
SHL1OBJS=   $(SLO)$/sc_scdll.obj
.ENDIF
.ENDIF


SHL1DEF=    $(MISC)$/$(SHL1TARGET).def

.IF "$(GUI)"=="WNT"
SHL1RES=    $(RCTARGET)
.ENDIF

# --- Linken der Applikation ---------------------------------------

LIB2TARGET=$(SLB)$/scmod.lib
LIB2OBJFILES=	\
            $(SLO)$/sc_scmod.obj

LIB3TARGET=$(SLB)$/scalc3.lib

LIB3FILES=	\
    $(SLB)$/sc_app.lib \
    $(SLB)$/sc_docshell.lib \
    $(SLB)$/sc_view.lib \
    $(SLB)$/sc_dbgui.lib

LIB3FILES+= \
            $(SLB)$/sc_unoobj.lib

LIB4TARGET=$(SLB)$/scalc3c.lib

LIB4FILES=	\
    $(SLB)$/sc_data.lib \
    $(SLB)$/sc_tool.lib \
    $(SLB)$/sc_xml.lib

LIB5TARGET=$(LB)$/bf_sclib.lib
LIB5ARCHIV=$(LB)$/libbf_sclib.a

LIB5OBJFILES=$(SLO)$/sc_sclib.obj

# --- Targets -------------------------------------------------------------

.INCLUDE :  target.mk

ALLTAR:	\
    $(MISC)$/linkinc.ls

.IF "$(GUI)" == "WNT"

$(MISC)$/$(SHL1TARGET).def:  makefile.mk
    @echo ------------------------------
    @echo Making: $@
    @echo LIBRARY     $(SHL1TARGET)                                  >$@
.IF "$(COM)"!="GCC"
    @echo DESCRIPTION 'SCALC3 DLL'                                 >>$@
    @echo DATA        READ WRITE NONSHARED                          >>$@
.ENDIF
    @echo EXPORTS                                                   >>$@
    @echo   CreateScDocShellDll @20                            >>$@
    @echo   CreateObjScDocShellDll @21                         >>$@
    @echo   InitScDll @22                                          >>$@
    @echo   DeInitScDll @23                                        >>$@
    @echo   component_getImplementationEnvironment @24             >>$@
    @echo   component_writeInfo @25                                >>$@
    @echo   component_getFactory @26                               >>$@
.ENDIF
.IF "$(OPTLINKS)" == "YES"
    echo  RC $(RCFLAGS) $(RES)$/scappi.res                    >>$@
.ENDIF

