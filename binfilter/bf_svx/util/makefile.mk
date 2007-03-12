#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.11 $
#
#   last change: $Author: obo $ $Date: 2007-03-12 09:43:51 $
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

SHL1STDLIBS+=\
            $(SHELLLIB)

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

LIBEXTRAFILES=\
        $(SLB)$/svx_svdraw.lib \
        $(SLB)$/svx_form.lib \
        $(SLB)$/svx_engine3d.lib \
        $(SLB)$/svx_msfilter.lib \
        $(SLB)$/svx_xout.lib \
        $(SLB)$/svx_xml.lib

LIB1TARGET      =$(SLB)$/svx_svx.lib
LIB1FILES       = \
            $(SLB)$/svx_items.lib     \
            $(SLB)$/svx_svxlink.lib   \
            $(SLB)$/svx_editeng.lib   \
            $(SLB)$/svx_outliner.lib \
            $(SLB)$/svx_dialogs.lib\
            $(SLB)$/svx_mnuctrls.lib  \
            $(SLB)$/svx_options.lib   \
            $(SLB)$/svx_stbctrls.lib  \
            $(SLB)$/svx_tbxctrls.lib  \
            $(SLB)$/svx_unoedit.lib   \
            $(SLB)$/svx_unodraw.lib	\
            $(SLB)$/svx_gal.lib

.IF "$(GUI)"=="WNT"
LIB1FILES  += \
                        $(LB)$/bf_sfx.lib #$(LIB)$/bf_sfx.lib
.ENDIF


LIB1FILES+=$(LIBEXTRAFILES)

.IF "$(GUI)" == "OS2" || "(GUIBASE)" == "WIN"
LIB1FILES  += \
            $(SLB)$/ibrwimp.lib
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
                $(SRS)$/svx_svxitems.srs \
                $(SRS)$/svx_form.srs \
                $(SRS)$/svx_engine3d.srs \
                $(SRS)$/svx_svxlink.srs

RESLIB1NAME=bf_svx
RESLIB1SRSFILES= $(SRS1FILELIST)

.IF "$(depend)" != ""

ALL:
    @echo nothing to depend on

.ELSE
.IF "$(GUI)"=="WNT"
ALL:\
        $(MAKELANGDIR)  \
         $(SLB)$/svx_svx.lib \
         $(LB)$/bf_svx.lib \
         $(MISC)$/linkinc.ls \
         ALLTAR

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
    $(TYPE) bf_svx.flt >$@
    $(TYPE) bf_sfxwin.flt > $@

.INCLUDE :  target.mk
