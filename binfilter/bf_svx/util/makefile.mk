#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.9 $
#
#   last change: $Author: ihi $ $Date: 2006-11-14 12:06:32 $
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
TARGET=bf_svx

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

USE_LDUMP2=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk

.IF "$(OS)"=="IRIX"
LINKFLAGS+=-Wl,-LD_LAYOUT:lgot_buffer=30
.ENDIF
RSCLOCINC+=-I$(BFPRJ)$/source$/svdraw

INC+= -I$(PRJ)$/inc$/bf_svx

# --- Svx - DLL ----------

#HELPIDFILES=    ..$/inc$/helpid.hrc

SHL1TARGET= bf_svx$(UPD)$(DLLPOSTFIX)
SHL1IMPLIB= bf_svx
SVXLOKAL=	$(LB)$/bf_svx.lib
SHL1BASE  = 0x1d800000

SHL1STDLIBS= \
    $(BFXMLOFFLIB) \
            $(BFGOODIESLIB) \
            $(BASICLIB) \
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
            $(UCBHELPERLIB)	\
            $(CPPUHELPERLIB)	\
            $(CPPULIB) \
            $(VOSLIB) \
            $(SALLIB) \
            $(ICUUCLIB)\
            $(FWELIB)	\
    $(LEGACYSMGRLIB)	\
    $(SALHELPERLIB)	\
    $(XMLSCRIPTLIB)	\
    $(SYSSHELLLIB)

.IF "$(GUI)"=="UNX"
SHL1STDLIBS+=\
                    $(BFSFXLIB)	\
                    $(SYSSHELLLIB)
.ENDIF

.IF "$(GUI)"=="WNT"

SHL1STDLIBS+=\
        uwinapi.lib \
        advapi32.lib \
        shell32.lib \
        gdi32.lib \
        ole32.lib \
        uuid.lib

.ENDIF


.IF "$(GUI)"=="WNT"
SHL1STDLIBS+=\
            $(SHELLLIB)
.ENDIF # WNT

#.IF "$(BIG_SVX)"==""
#SHL1STDLIBS+=\
#			$(LB)$/dl.lib
#.ENDIF

.IF "$(GUI)"=="WNT"
SHL1DEPN=       $(SLB)$/svx_svx.lib #$(LB)$/dl.lib
.ENDIF # WNT

SHL1LIBS=       $(SLB)$/svx_svx.lib

SHL1DEF=        $(MISC)$/$(SHL1TARGET).def
DEF1NAME        =$(SHL1TARGET)
DEF1DEPN        =$(MISC)$/$(SHL1TARGET).flt
DEFLIB1NAME=svx_svx
DEF1DES		= Rtf, Edt, Outliner, SvDraw, Form, Fmcomp, Engine3D, MSFilter
# THB: exports list svx checked for 6.0 Final 6.12.2001
DEF1EXPORTFILE	= svx.dxp

#.IF "$(BIG_SVX)"==""
#
#SHL2TARGET= dl$(UPD)$(DLLPOSTFIX)
#SHL2IMPLIB= dl
#SVXLOKAL+=	$(LB)$/dl.lib
#SHL2BASE  = 0x1db00000
#SHL2STDLIBS= \
#            $(LB)$/svx.lib \
#            $(SALLIB) \
#            $(VOSLIB) \
#            $(TOOLSLIB) \
#            $(SVTOOLLIB) \
#			$(SVLLIB)	\
#            $(SVLIB) \
#            $(SO2LIB) \
#            $(SOTLIB) \
#			$(XMLOFFLIB) \
#            $(SFX2LIB) \
#            $(GOODIESLIB) \
#            $(BASICLIB) \
#            $(SVMEMLIB) \
#            $(TKLIB) \
#			$(CPPULIB) \
#			$(CPPUHELPERLIB) \
#			$(UNOTOOLSLIB) \
#			$(UCBHELPERLIB) \
#            $(COMPHELPERLIB)
#
#.IF "$(GUI)"=="WNT"
#SHL2STDLIBS+=\
#            $(SHELLLIB)
#.ENDIF

#.IF "$(SOLAR_JAVA)" != ""
#SHL2STDLIBS+=\
#        $(SJLIB)
#.ENDIF


#SHL2DEPN=       $(SLB)$/dl.lib $(LB)$/svx.lib
#SHL2LIBS=       $(SLB)$/dl.lib
#SHL2OBJS+=      $(SLO)$/svx_svxempty.obj
#
#SHL2DEF=        $(MISC)$/$(SHL2TARGET).def
#DEF2NAME        =$(SHL2TARGET)
#DEF2DEPN        =$(MISC)$/$(SHL2TARGET).flt
#DEFLIB2NAME=dl
#DEF2DES     =SvDraw, Form, Fmcomp, Engine3D, XOutDev, MSFilter
#
#.ENDIF

LIBEXTRAFILES=\
        $(LIBPRE) $(SLB)$/svx_svdraw.lib \
        $(LIBPRE) $(SLB)$/svx_form.lib \
        $(LIBPRE) $(SLB)$/svx_engine3d.lib \
        $(LIBPRE) $(SLB)$/svx_msfilter.lib \
        $(LIBPRE) $(SLB)$/svx_xout.lib \
        $(LIBPRE) $(SLB)$/svx_xml.lib
#        $(LIBPRE) $(SLB)$/svx_fmcomp.lib \

LIB1TARGET      =$(SLB)$/svx_svx.lib
LIB1FILES       = \
            $(LIBPRE) $(SLB)$/svx_items.lib     \
            $(LIBPRE) $(SLB)$/svx_svxlink.lib   \
            $(LIBPRE) $(SLB)$/svx_editeng.lib   \
            $(LIBPRE) $(SLB)$/svx_outliner.lib \
            $(LIBPRE) $(SLB)$/svx_dialogs.lib\
            $(LIBPRE) $(SLB)$/svx_mnuctrls.lib  \
            $(LIBPRE) $(SLB)$/svx_options.lib   \
            $(LIBPRE) $(SLB)$/svx_stbctrls.lib  \
            $(LIBPRE) $(SLB)$/svx_tbxctrls.lib  \
            $(LIBPRE) $(SLB)$/svx_unoedit.lib   \
            $(LIBPRE) $(SLB)$/svx_unodraw.lib	\
            $(LIBPRE) $(SLB)$/svx_gal.lib		
#            $(LIBPRE) $(SLB)$/svx_accessibility.lib
#            $(LIBPRE) $(SLB)$/svx_svxrtf.lib    \

.IF "$(GUI)"=="WNT"
LIB1FILES  += \
                        $(LIBPRE) $(LB)$/bf_sfx.lib #$(LIBPRE) $(LIB)$/bf_sfx.lib
.ENDIF					


.IF "$(SVXLIGHT)" != ""
LIB3TARGET= $(LB)$/svx_svxl.lib
LIB3ARCHIV= $(LB)$/libsvx_svxl.a
LIB3FILES=  \
            $(LB)$/sxl_editeng.lib \
            $(LB)$/sxl_engine3d.lib \
            $(LB)$/sxl_form.lib \
            $(LB)$/sxl_items.lib \
            $(LB)$/sxl_outliner.lib \
            $(LB)$/sxl_svdraw.lib \
            $(LB)$/sxl_xout.lib \
            $(LB)$/sxl_options.lib \
            $(LB)$/sxl_xml.lib \
            $(LB)$/sxl_unoedit.lib \
            $(LB)$/sxl_unodraw.lib
.ENDIF

#.IF "$(BIG_SVX)"==""
#LIB2TARGET      =$(SLB)$/dl.lib
#LIB2FILES       = $(LIBEXTRAFILES)
#.ELSE
LIB1FILES+=$(LIBEXTRAFILES)
#.ENDIF

.IF "$(GUI)" == "OS2" || "(GUIBASE)" == "WIN"
LIB1FILES  += \
            $(LIBPRE) $(SLB)$/ibrwimp.lib
.ENDIF


SRS1FILELIST=\
                $(SRS)$/svx_svdstr.srs      \
                $(SRS)$/svx_editeng.srs     \
                $(SRS)$/svx_outliner.srs \
                $(SRS)$/svx_dialogs.srs     \
                $(SRS)$/svx_drawdlgs.srs \
                $(SRS)$/svx_mnuctrls.srs \
                $(SRS)$/svx_stbctrls.srs \
                $(SRS)$/svx_tbxctrls.srs \
                $(SRS)$/svx_options.srs     \
                $(SRS)$/svx_svxitems.srs \
                $(SRS)$/svx_form.srs \
                $(SRS)$/svx_engine3d.srs \
                $(SRS)$/svx_svxlink.srs

#				$(SRS)$/svx_unodraw.srs \

#SRSFILELIST=\
#                $(SRS)$/svdstr.srs      \
#                $(SRS)$/editeng.srs     \
#                $(SRS)$/outliner.srs \
#                $(SRS)$/dialogs.srs     \
#                $(SRS)$/drawdlgs.srs \
#                $(SRS)$/mnuctrls.srs \
#                $(SRS)$/stbctrls.srs \
#                $(SRS)$/tbxctrls.srs \
#                $(SRS)$/options.srs     \
#                $(SRS)$/svxitems.srs \
#				$(SRS)$/form.srs \
#				$(SRS)$/fmcomp.srs \
#				$(SRS)$/engine3d.srs \
#				$(SRS)$/unodraw.srs \
#                $(SRS)$/svxlink.srs \
#                $(SRS)$/accessibility.srs


#.IF "$(GUI)" != "MAC"
#SRS1FILELIST+=   $(SRS)$/sfx2_sfx.srs
#.ELSE
#.IF "$(UPDMINOR)" != ""
#SRS1FILELIST+=   $(SRS)$/sfx2_sfx.srs
#.ELSE
#SRS1FILELIST+=   $(SRS)$/sfx2_sfx.srs
#.ENDIF
#.ENDIF

RESLIB1NAME=bf_svx
RESLIB1SRSFILES= $(SRS1FILELIST)

.IF "$(depend)" != ""

ALL:
    @echo nothing to depend on

.ELSE
.IF "$(GUI)"=="WNT"


#.IF "$(BIG_SVX)"==""
#ALL:      \
#        $(MAKELANGDIR)  \
#            $(SLB)$/dl.lib  $(SLB)$/svx.lib \
#            $(LB)$/dl.lib   $(LB)$/svx.lib \
#          $(MISC)$/linkinc.ls                   \
#          ALLTAR
#.ELSE
ALL:\
        $(MAKELANGDIR)  \
         $(SLB)$/svx_svx.lib \
         $(LB)$/bf_svx.lib \
         $(MISC)$/linkinc.ls \
         ALLTAR

     

    
                   
                    
#.ENDIF

.ENDIF			# "$(GUI)"=="WNT"

.IF "$(GUI)"=="UNX" || "$(GUI)"=="MAC"
ALL: \
        $(MAKELANGDIR)  \
        ALLTAR
.ENDIF
.ENDIF			#F "$(depend)" != ""

# --- Targets -------------------------------------------------------


$(MISC)$/$(SHL1TARGET).flt: makefile.mk
    @echo ------------------------------
    @echo Making: $@
    +$(TYPE) bf_svx.flt >$@
    +$(TYPE) bf_sfxwin.flt > $@


#$(MISC)$/$(SHL2TARGET).flt: makefile.mk
#    @echo ------------------------------
#    @echo Making: $@
#	+$(TYPE) dl.flt >$@

.INCLUDE :  target.mk


implib1: $(MISC)\svx1.def
    implib /noi $(LB)\svx1.lib $(MISC)\svx1.def

implib2: $(MISC)\svx2.def
    implib /noi $(LB)\svx2.lib $(MISC)\svx2.def

implib3: $(MISC)\dl1.def
    implib /noi $(LB)\dl1.lib $(MISC)\dl1.def

implib4: $(MISC)\dl2.def
    implib /noi $(LB)\dl2.lib $(MISC)\dl2.def

implib_defs: $(SHL1DEF) $(SHL2DEF)
    +-$(RM) $(MISC)$/svx1.def
    +-$(RM) $(MISC)$/svx2.def
    +-$(RM) $(MISC)$/dl1.def
    +-$(RM) $(MISC)$/dl2.def
    splitdef $(SHL1DEF) $(MISC)$/svx1.def $(MISC)$/svx2.def
    splitdef $(SHL2DEF) $(MISC)$/dl1.def $(MISC)$/dl2.def
    
    
