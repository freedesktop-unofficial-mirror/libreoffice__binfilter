#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.4 $
#
#   last change: $Author: aw $ $Date: 2003-12-05 15:11:17 $
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
TARGET=bf_sw

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

.IF "$(CPU)"=="i386"
USE_LDUMP2=TRUE
.ENDIF


# --- Settings ------------------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
INC+= -I$(PRJ)$/inc$/bf_sw
#	nmake		 	-	swdll

DESK=T

.IF "$(GUI)" == "WIN"
RESLIBSPLIT1NAME=bf_sw
.ELSE
RESLIB1NAME=bf_sw
.ENDIF
MYRESLIBNAME=sw

#RSCLOCINC=$(RSCLOCINC);$(PRJ)$/RES

# --- Allgemein -----------------------------------------------------------
.IF "$(GUI)"=="WIN"
LIBFLAGS=/PAGE:128 /NOE /NOI
#OPTLINKS=YES
MAPSYM=tmapsym
.IF "$(debug)" != ""
LINKFLAGS= /F /PACKCODE:65520 /PACKDATA /NOD /NOE /MAP /COD /NOCV
.ELSE
LINKFLAGS= /F /PACKCODE:65520 /PACKDATA /NOD /NOE /MAP
.ENDIF
.ENDIF

.IF "$(COM)"=="ICC"
LINKFLAGS+=/SEGMENTS:1024 /PACKD:32768
.ENDIF
.IF "$(OS)"=="IRIX"
LINKFLAGS+=-Wl,-LD_LAYOUT:lgot_buffer=40
.ENDIF

.IF "$(header)" == ""

#sw_res_files= \
#    $(SRS)$/app.srs          \
#    $(SRS)$/dialog.srs       \
#    $(SRS)$/chrdlg.srs       \
#    $(SRS)$/config.srs       \
#    $(SRS)$/dbui.srs	    \
#    $(SRS)$/dochdl.srs       \
#    $(SRS)$/docvw.srs        \
#    $(SRS)$/envelp.srs       \
#    $(SRS)$/fldui.srs        \
#    $(SRS)$/fmtui.srs        \
#    $(SRS)$/frmdlg.srs       \
#    $(SRS)$/globdoc.srs      \
#    $(SRS)$/index.srs        \
#    $(SRS)$/lingu.srs        \
#    $(SRS)$/misc.srs         \
#    $(SRS)$/ribbar.srs       \
#    $(SRS)$/shells.srs       \
#    $(SRS)$/swslots.srs     \
#    $(SRS)$/table.srs        \
#    $(SRS)$/uiview.srs       \
#    $(SRS)$/utlui.srs        \
#    $(SRS)$/web.srs          \
#    $(SRS)$/wizard.srs       \
#    $(SRS)$/wrtsh.srs        \
#    $(SOLARRESDIR)$/bf_sfx.srs

sw_res_files= \
    $(SRS)$/sw_app.srs          \
    $(SRS)$/sw_dialog.srs       \
    $(SRS)$/sw_config.srs       \
    $(SRS)$/sw_dbui.srs	    \
    $(SRS)$/sw_dochdl.srs       \
    $(SRS)$/sw_docvw.srs        \
    $(SRS)$/sw_envelp.srs       \
    $(SRS)$/sw_fldui.srs        \
    $(SRS)$/sw_globdoc.srs      \
    $(SRS)$/sw_index.srs        \
    $(SRS)$/sw_misc.srs         \
    $(SRS)$/sw_ribbar.srs       \
    $(SRS)$/sw_shells.srs       \
    $(SRS)$/sw_swslots.srs     \
    $(SRS)$/sw_table.srs        \
    $(SRS)$/sw_uiview.srs       \
    $(SRS)$/sw_utlui.srs        \
    $(SRS)$/sw_web.srs          \
    $(SRS)$/sw_wrtsh.srs        \
    $(SRS)$/sfx2_sfx.srs
.IF "$(GUI)" == "WIN"
RESLIBSPLIT1SRSFILES= \
    $(sw_res_files)
.ELSE
RESLIB1SRSFILES= \
    $(sw_res_files)
.ENDIF

LIB1TARGET=$(LB)$/bf_swlib.lib
LIB1ARCHIV=$(LB)$/libbf_swlib.a
LIB1OBJFILES= \
        $(OUT)$/obj$/sw_swlib.obj \
        $(OUT)$/obj$/sw_swcomlib.obj \
        $(OUT)$/obj$/sw_w4wflt.obj




SHL2TARGET= $(TARGET)$(UPD)$(DLLPOSTFIX)
SHL2VERSIONMAP= $(TARGET).map
SHL2IMPLIB= _$(TARGET)
SHL2LIBS= \
    $(SLB)$/sw_core1.lib\
    $(SLB)$/sw_core2.lib\
    $(SLB)$/sw_filter.lib\
    $(SLB)$/sw_ui1.lib\
    $(SLB)$/sw_ui2.lib

# static libraries
SHL2STDLIBS+= $(BFSCHLIB) $(BFSMLIB)

# dynamic libraries
SHL2STDLIBS+= \
    $(BFOFALIB) \
    $(BFSVXLIB) \
    $(LEGACYSMGRLIB)	\
    $(BFXMLOFFLIB) \
    $(BASICLIB) \
    $(GOODIESLIB) \
    $(SO2LIB) \
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

.IF "$(GUI)" == "UNX"
SHL2STDLIBS+= \
                        $(BFSFXLIB)
.ENDIF     

.IF "$(GUI)"=="WNT"
SHL2STDLIBS+= advapi32.lib
.ENDIF # WNT

#			uno.lib usr.lib sj.lib aofa.lib
#			ysch.lib  ysim.lib ysm.lib basic.lib ich.lib

SHL2DEPN=   \
    $(SLB)$/sw_core1.lib\
    $(SLB)$/sw_core2.lib\
    $(SLB)$/sw_filter.lib\
    $(SLB)$/sw_ui1.lib\
    $(SLB)$/sw_ui2.lib


SHL2OBJS= \
    $(OUT)$/slo$/sw_swmodule.obj \
    $(OUT)$/slo$/sw_swdll.obj
#	$(SLO)$/sw_.obj		  ^ \ nicht vergessen!


SHL2DEF=    $(MISC)$/$(SHL2TARGET).def
SHL2BASE=	0x1e000000


.IF "$(GUI)"=="WNT"
do_build+= \
    $(MISC)$/linkinc.ls
.ENDIF

do_build+= \
    $(SHL2TARGETN)

.IF "$(depend)"==""
ALL:\
    $(do_build) \
    $(INC)$/sw.lst	\
    ALLTAR
.ENDIF
.ENDIF

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
    @echo DESCRIPTION 'SWriter4 DLL'                                 >>$@
    @echo DATA        READ WRITE NONSHARED                          >>$@
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

$(INC)$/sw.lst:
.IF "$(GUI)" =="WNT"
    +-@echo clook missed!!!!
#clook -o $@ -p 1 -i ..\inc;..\source\ui\inc;..\source\core\inc;..\source\filter\inc;. dummy.cxx
.ELSE
    @echo wnt only
.ENDIF

