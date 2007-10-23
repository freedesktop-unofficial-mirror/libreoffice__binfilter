#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.9 $
#
#   last change: $Author: vg $ $Date: 2007-10-23 14:16:34 $
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

PRJNAME=binfilter
TARGET=bf_xo

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk

# --- Allgemein ----------------------------------------------------
NO_BSYMBOLIC=TRUE
ENABLE_EXCEPTIONS=TRUE

LIB1TARGET= $(SLB)$/bf_xo.lib
LIB1FILES=	\
    $(SLB)$/xmloff_core.lib \
    $(SLB)$/xmloff_meta.lib \
    $(SLB)$/xmloff_script.lib \
    $(SLB)$/xmloff_style.lib \
    $(SLB)$/xmloff_text.lib \
    $(SLB)$/xmloff_draw.lib \
    $(SLB)$/xmloff_chart.lib \
    $(SLB)$/xmloff_forms.lib

# --- Shared-Library -----------------------------------------------

.IF "$(GUI)"!="UNX"
LIB4TARGET= $(LB)$/ibf_xo.lib
LIB4FILES=	$(LB)$/_ibf_xo.lib
LIB4OBJFILES=\
    $(OBJ)$/xmloff_xmlkywd.obj
.ENDIF

SHL1TARGET= bf_xo$(UPD)$(DLLPOSTFIX)
SHL1IMPLIB= _ibf_xo

SHL1STDLIBS= \
        $(SVTOOLLIB)	\
        $(TOOLSLIB)		\
        $(I18NISOLANGLIB) \
        $(VOSLIB)		\
        $(CPPULIB)		\
        $(CPPUHELPERLIB)\
        $(COMPHELPERLIB)\
        $(VCLLIB)		\
        $(TKLIB)		\
        $(SVLLIB)		\
        $(SALLIB)		\
        $(UNOTOOLSLIB)	\
        $(BFGOODIESLIB) \
        $(BFSO3LIB)

# SCO: the linker does know about weak symbols, but we can't ignore multiple defined symbols
.IF "(OS)"=="SCO" || "$(OS)$(COM)"=="OS2GCC"
SHL1STDLIBS+=-licg617mxp
.ENDIF

SHL1DEF=    $(MISC)$/$(SHL1TARGET).def
SHL1LIBS=   $(LIB1TARGET)

# --- Def-File ---------------------------------------------------------

DEF1NAME    =$(SHL1TARGET)
DEF1DEPN    =$(MISC)$/$(SHL1TARGET).flt
DEFLIB1NAME =bf_xo
DEF1DES     =XML Office Lib
DEF1EXPORTFILE=	exports.dxp
# --- Targets ----------------------------------------------------------

.INCLUDE :  target.mk

# --- Filter -----------------------------------------------------------

$(MISC)$/$(SHL1TARGET).flt: makefile.mk
    $(TYPE) bf_xo.flt > $@

