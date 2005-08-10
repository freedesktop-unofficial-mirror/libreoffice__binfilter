#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.9 $
#
#   last change: $Author: obo $ $Date: 2005-08-10 11:24:52 $
#
#   The Contents of this file are made available subject to the terms of
#   either of the following licenses
#
#          - GNU Lesser General Public License Version 2.1
#          - Sun Industry Standards Source License Version 1.1
#
#   Sun Microsystems Inc., October, 2000
#
#   GNU Lesser General Public License Version 2.1
#   =============================================
#   Copyright 2000 by Sun Microsystems, Inc.
#   901 San Antonio Road, Palo Alto, CA 94303, USA
#
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU Lesser General Public
#   License version 2.1, as published by the Free Software Foundation.
#
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with this library; if not, write to the Free Software
#   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#   MA  02111-1307  USA
#
#
#   Sun Industry Standards Source License Version 1.1
#   =================================================
#   The contents of this file are subject to the Sun Industry Standards
#   Source License Version 1.1 (the "License"); You may not use this file
#   except in compliance with the License. You may obtain a copy of the
#   License at http://www.openoffice.org/license.html.
#
#   Software provided under this License is provided on an "AS IS" basis,
#   WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
#   WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
#   MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
#   See the License for the specific provisions governing your rights and
#   obligations concerning the Software.
#
#   The Initial Developer of the Original Code is: Sun Microsystems, Inc.
#
#   Copyright: 2000 by Sun Microsystems, Inc.
#
#   All Rights Reserved.
#
#   Contributor(s): _______________________________________
#
#
#
#*************************************************************************
PRJ=..$/..
BFPRJ=..

PRJNAME=binfilter
TARGET=scalc3

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

# --- Settings -----------------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  connectivity/version.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
INC+= -I$(PRJ)$/inc$/bf_sc
IENV!:=$(IENV);..$/res

.IF "$(COM)"=="ICC"
LINKFLAGS+=/SEGMENTS:512 /PACKD:32768
.ENDIF
.IF "$(OS)"=="IRIX"
LINKFLAGS+=-Wl,-LD_LAYOUT:lgot_buffer=30
.ENDIF

# --- Resourcen ----------------------------------------------------

#RESLIB1LIST=\
#	$(SRS)$/miscdlgs.srs	\
#	$(SRS)$/docshell.srs	\
#	$(SRS)$/ui.srs		\
#	$(SRS)$/dbgui.srs	\
#	$(SRS)$/drawfunc.srs \
#	$(SRS)$/core.srs 	\
#	$(SRS)$/styleui.srs	\
#	$(SRS)$/scslots.srs	\
#	$(SRS)$/formdlgs.srs \
#	$(SRS)$/pagedlg.srs	\
#	$(SRS)$/navipi.srs	\
#	$(SOLARVERSION)$/$(INPATH)$/res$(EXT_UPDMINOR)$/sfx.srs

RESLIB1LIST=\
    $(SRS)$/sc_docshell.srs	\
    $(SRS)$/sc_ui.srs		\
    $(SRS)$/sc_dbgui.srs	\
    $(SRS)$/sc_drawfunc.srs \
    $(SRS)$/sc_core.srs 	\
    $(SRS)$/sc_scslots.srs	\
    $(SRS)$/sc_formdlgs.srs \
    $(SRS)$/sc_navipi.srs	\
    $(SRS)$/sfx2_sfx.srs

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
    $(BASICLIB)		\
       $(LEGACYSMGRLIB)	\
    $(SO2LIB)		\
    $(SVTOOLLIB)	\
    $(SVLLIB)		\
    $(BFSVXLIB)		\
    $(GOODIESLIB)	\
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
    $(UNOTOOLSLIB)  \
    $(SOTLIB)		\
    $(BFXMLOFFLIB)	\
    $(DBTOOLSLIB)


.IF "$(OS)" == "MACOSX"
# static libraries must come at the end of list on MacOSX
SHL1STDLIBS+= $(BFSCHLIB)
.ENDIF


SHL1DEPN=   $(L)$/itools.lib
SHL1LIBS=   $(LIB3TARGET) $(LIB4TARGET)

.IF "$(GUI)"!="UNX"
SHL1OBJS=   $(SLO)$/sc_scdll.obj
.ENDIF

.IF "$(GUI)" == "UNX"
SHL1STDLIBS+= \
            $(BFSFXLIB)
.ENDIF

SHL1DEF=    $(MISC)$/$(SHL1TARGET).def

.IF "$(GUI)" == "WNT" || "$(GUI)" == "WNT"
SHL1RES=    $(RCTARGET)
.ENDIF

# --- Linken der Applikation ---------------------------------------

LIB2TARGET=$(SLB)$/scmod.lib
LIB2OBJFILES=	\
            $(SLO)$/sc_scmod.obj

LIB3TARGET=$(SLB)$/scalc3.lib
#LIB3FILES=	\
#	$(SLB)$/app.lib \
#	$(SLB)$/docshell.lib \
#	$(SLB)$/view.lib \
#	$(SLB)$/undo.lib \
#	$(SLB)$/attrdlg.lib \
#	$(SLB)$/namedlg.lib \
#	$(SLB)$/styleui.lib \
#	$(SLB)$/miscdlgs.lib \
#	$(SLB)$/formdlgs.lib \
#	$(SLB)$/cctrl.lib \
#	$(SLB)$/dbgui.lib \
#	$(SLB)$/optdlg.lib \
#	$(SLB)$/pagedlg.lib \
#	$(SLB)$/drawfunc.lib \
#	$(SLB)$/navipi.lib

LIB3FILES=	\
    $(SLB)$/sc_app.lib \
    $(SLB)$/sc_docshell.lib \
    $(SLB)$/sc_view.lib \
    $(SLB)$/sc_undo.lib \
    $(SLB)$/sc_formdlgs.lib \
    $(SLB)$/sc_cctrl.lib \
    $(SLB)$/sc_dbgui.lib \
    $(SLB)$/sc_drawfunc.lib \
    $(SLB)$/sc_navipi.lib
    
LIB3FILES+= \
            $(SLB)$/sc_unoobj.lib

.IF "$(linkinc)" != ""
#SHL1STDLIBS+= \
#			$(SLB)$/stardiv_sc.lib
.ELSE
#SHL1STDLIBS+= \
#			$(L)$/offsmart.lib \
#			$(L)$/svtsmart.lib \
#			$(L)$/svxsmrt1.lib
.ENDIF

LIB4TARGET=$(SLB)$/scalc3c.lib
#LIB4FILES=	\
#	$(SLB)$/data.lib \
#	$(SLB)$/tool.lib \
#	$(SLB)$/dif.lib \
#	$(SLB)$/excel.lib \
#	$(SLB)$/xcl97.lib \
#	$(SLB)$/html.lib \
#	$(SLB)$/lotus.lib \
#	$(SLB)$/rtf.lib \
#	$(SLB)$/xml.lib \
#	$(SLB)$/accessibility.lib \
#	$(SLB)$/ftools.lib \
#	$(SLB)$/scflt.lib

LIB4FILES=	\
    $(SLB)$/sc_data.lib \
    $(SLB)$/sc_tool.lib \
    $(SLB)$/sc_xml.lib
    
LIB5TARGET=$(LB)$/bf_sclib.lib
LIB5ARCHIV=$(LB)$/libbf_sclib.a

#.IF "$(GUI)"=="UNX"
LIB5OBJFILES=$(SLO)$/sc_sclib.obj
#.ELSE
#LIB5OBJFILES=$(OBJ)$/sc_sclib.obj
#.ENDIF

# --- Targets -------------------------------------------------------------

.INCLUDE :  target.mk

ALLTAR:	\
    $(MISC)$/linkinc.ls

.IF "$(depend)" == ""

.IF "$(GUI)" == "WNT"

$(MISC)$/$(SHL1TARGET).def:  makefile.mk
    @echo ------------------------------
    @echo Making: $@
    @echo LIBRARY     $(SHL1TARGET)                                  >$@
    @echo DESCRIPTION 'SCALC3 DLL'                                 >>$@
    @echo DATA        READ WRITE NONSHARED                          >>$@
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

.ENDIF



$(MISCX)$/$(SHL1TARGET).flt:
    @echo ------------------------------
    @echo Making: $@
    @echo WEP>$@
    @echo LIBMAIN>>$@
    @echo LibMain>>$@


