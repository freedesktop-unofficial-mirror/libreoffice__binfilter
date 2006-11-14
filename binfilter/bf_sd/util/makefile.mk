#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.10 $
#
#   last change: $Author: ihi $ $Date: 2006-11-14 12:01:11 $
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
TARGET=sdraw3

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

# --- Settings -----------------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
INC+= -I$(PRJ)$/inc$/bf_sd
#IENV!:=$(IENV);..$/res

.IF "$(GUI)"=="WIN"
LINKFLAGS+=/PACKCODE:65500 /SEG:16000 /NOE /NOD /MAP
MAPSYM=tmapsym
.ENDIF

.IF "$(COM)"=="ICC"
LINKFLAGS+=/SEGMENTS:512 /PACKD:32768
.ENDIF

# --- Resourcen ----------------------------------------------------

.IF "$(GUI)"=="WIN"
RESLIBSPLIT1NAME=sd
RESLIBSPLIT1SRSFILES= \
     $(SRS)$/sd_app.srs $(SRS)$/sd_dlg.srs $(SRS)$/sd_core.srs $(SRS)$/sd_sdslots.srs \
     $(SRS)$/sfx2_sfx.srs
.ELSE
RESLIB1NAME=bf_sd
RESLIB1SRSFILES=\
     $(SRS)$/sd_app.srs $(SRS)$/sd_dlg.srs $(SRS)$/sd_core.srs $(SRS)$/sd_sdslots.srs \
     $(SRS)$/sfx2_sfx.srs
.ENDIF

#.IF "$(GUI)"=="WIN"
#RESLIBSPLIT1NAME=sd
#RESLIBSPLIT1SRSFILES= \
#	 $(SRS)$/app.srs $(SRS)$/dlg.srs $(SRS)$/core.srs $(SRS)$/html.srs $(SRS)$/sdslots.srs \
#	 $(SRS)$/accessibility.srs $(SOLARRESDIR)$/sfx.srs
#.ELSE
#RESLIB1NAME=sd
#RESLIB1SRSFILES=\
#	 $(SRS)$/app.srs $(SRS)$/dlg.srs $(SRS)$/core.srs $(SRS)$/html.srs $(SRS)$/sdslots.srs \
#	 $(SRS)$/accessibility.srs $(SOLARRESDIR)$/sfx.srs
#.ENDIF

#.IF "$(solarlang)" == "deut"
#SRC1FILES=      ..$/source$/ui$/app$/appmain.src
#SRS1NAME =      appmain
#SRS1FILES=$(SRS)$/appmain.srs \
#	 $(SOLARRESDIR)$/sfx.srs
#RES1TARGET= sdappi
#.ENDIF

# --- StarDraw DLL

SHL1TARGET= bf_sd$(UPD)$(DLLPOSTFIX)
SHL1VERSIONMAP= bf_sd.map
SHL1IMPLIB= bf_sdi

# static libraries
SHL1STDLIBS= $(BFSCHLIB) $(BFSCLIB) $(BFSMLIB)

# dynamic libraries
SHL1STDLIBS+= \
    $(BFOFALIB) \
    $(BFSVXLIB) \
    $(LEGACYSMGRLIB)	\
    $(BASICLIB) \
    $(BFGOODIESLIB) \
    $(SO2LIB) \
    $(SVTOOLLIB) \
    $(TKLIB) \
    $(VCLLIB) \
    $(SVLLIB) \
    $(SOTLIB) \
    $(UNOTOOLSLIB) \
    $(TOOLSLIB) \
    $(I18NISOLANGLIB) \
    $(COMPHELPERLIB) \
    $(UCBHELPERLIB) \
    $(CPPUHELPERLIB) \
    $(CPPULIB) \
    $(VOSLIB) \
    $(SALLIB)

.IF "$(GUI)" == "UNX"
SHL1STDLIBS+= \
            $(BFSFXLIB)
.ENDIF     

.IF "$(GUI)" == "MAC"
SHL1STDLIBS += \
            $(SOLARBINDIR)$/SDB$(UPD)$(DLLPOSTFIX).DLL \
            $(SOLARLIBDIR)$/plugctor.lib
.ENDIF

SHL1LIBS=   $(LIB3TARGET)


SHL1DEF=    $(MISC)$/$(SHL1TARGET).def
.IF "$(GUI)" == "WNT" || "$(GUI)" == "WIN"
SHL1RES=    $(RCTARGET)
.ENDIF

# --- Linken der Applikation ---------------------------------------

LIB2TARGET=$(SLB)$/sd_sdmod.lib
LIB2OBJFILES=   \
            $(SLO)$/sd_sdmod2.obj      \
            $(SLO)$/sd_sdmod.obj

LIB3TARGET=$(SLB)$/sd_sdraw3.lib
LIB3FILES=      \
            $(SLB)$/sd_view.lib        \
            $(SLB)$/sd_app.lib			\
            $(SLB)$/sd_func.lib        \
            $(SLB)$/sd_docshell.lib    \
            $(SLB)$/sd_dlg.lib			\
            $(SLB)$/sd_core.lib		\
            $(SLB)$/sd_xml.lib			\
            $(SLB)$/sd_bin.lib			\
            $(SLB)$/sd_filter.lib		\
            $(SLB)$/sd_unoidl.lib		
#			$(SLB)$/sd_html.lib		\
#			$(SLB)$/sd_cgm.lib			\
#			$(SLB)$/sd_grf.lib			\
#			$(SLB)$/sd_accessibility.lib		


LIB4TARGET=$(LB)$/bf_sdlib.lib
LIB4ARCHIV=$(LB)$/libbf_sdlib.a
#.IF "$(GUI)"=="UNX"
LIB4OBJFILES=$(SLO)$/sd_sdlib.obj \
          $(SLO)$/sd_sdresid.obj
#.ELSE
#.IF "$(GUI)"=="MAC"
#LIB4OBJFILES=$(OBJ)$/sd_sdlib.obj \
#		  $(OBJ)$/sd_sdresid.obj
#.ELSE
#LIB4OBJFILES=$(OBJ)$/sd_sdlib.obj \
#		  $(OBJ)$/sd_sdresid.obj
#.ENDIF
#.ENDIF


#.IF "$(depend)" == ""
#ALL:    \
#	ALLTAR
#.ENDIF


.IF "$(SVXLIGHT)" != "" 
LIB5TARGET= $(LB)$/sd_sdl.lib
LIB5ARCHIV= $(LB)$/sd_libsdl.a
LIB5FILES=  \
            $(LB)$/sd_sxl_core.lib\
            $(LB)$/sd_sxl_unoidl.lib
.ENDIF

# --- Targets -------------------------------------------------------------

.INCLUDE :  target.mk

.IF "$(depend)" == ""

# -------------------------------------------------------------------------
# MAC
# -------------------------------------------------------------------------

.IF "$(GUI)" == "MAC"

$(MISCX)$/$(APP1TARGET).def : makefile.mk


$(MISC)$/$(SHL1TARGET).def:  makefile.mk
        delete -i $@.exp
        $(LINK)  $(LINKFLAGS) $(LINKFLAGSSHL) $(SHL1OBJS) $(SHL1LIBS) -f $@.exp · dev:null
        duplicate -y $@.exp $@
.ENDIF

.IF "$(GUI)" == "WNT"

$(MISC)$/$(SHL1TARGET).def:
    @echo ------------------------------
    @echo Making: $@
    @echo LIBRARY     $(SHL1TARGET)                                  >$@
    @echo DESCRIPTION 'SDRAW3 DLL'                                 >>$@
    @echo DATA        READ WRITE NONSHARED                          >>$@
    @echo EXPORTS                                                   >>$@
    @echo   CreateSdDrawDocShellDll @20                            >>$@
    @echo   CreateSdGraphicDocShellDll @21                         >>$@
    @echo   CreateObjSdDrawDocShellDll @22                         >>$@
    @echo   CreateObjSdGraphicDocShellDll @23                      >>$@
    @echo   InitSdDll @24                                          >>$@
    @echo   DeInitSdDll @25                                        >>$@
    @echo component_getImplementationEnvironment 				   >>$@
    @echo component_writeInfo									   >>$@
    @echo component_getFactory									   >>$@
.ENDIF

.ENDIF

$(MISCX)$/$(SHL1TARGET).flt:
    @echo ------------------------------
    @echo Making: $@
    @echo WEP>$@
    @echo LIBMAIN>>$@
    @echo LibMain>>$@
