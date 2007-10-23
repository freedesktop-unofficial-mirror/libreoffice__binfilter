#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.11 $
#
#   last change: $Author: vg $ $Date: 2007-10-23 13:58:09 $
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
TARGET=smath3

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

LIBTARGET=NO

# --- Settings -----------------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_starmath
# --- Files --------------------------------------------------------

RESLIB1NAME=bf_sm
RESLIB1SRSFILES=\
    $(SRS)$/starmath_smres.srs 

SHL1TARGET= bf_sm$(UPD)$(DLLPOSTFIX)
SHL1IMPLIB= bf_smimp

SHL1VERSIONMAP= bf_sm.map
SHL1DEF=$(MISC)$/$(SHL1TARGET).def
DEF1NAME=		$(SHL1TARGET)

SHL1STDLIBS= \
            $(BFSVXLIB) \
            $(LEGACYSMGRLIB)	\
            $(BFSO3LIB) \
            $(BFXMLOFFLIB) \
            $(SVTOOLLIB) \
            $(TKLIB) \
            $(VCLLIB) \
            $(SVLLIB)	\
            $(SOTLIB) \
            $(UNOTOOLSLIB) \
            $(TOOLSLIB) \
            $(COMPHELPERLIB) \
            $(CPPUHELPERLIB) \
            $(CPPULIB) \
            $(SALLIB)

SHL1DEPN=	makefile.mk
SHL1LIBS=   $(SLB)$/bf_starmath.lib

.IF "$(GUI)" != "UNX"
.IF "$(GUI)$(COM)" != "WNTGCC"
SHL1OBJS=   $(SLO)$/starmath_smdll.obj
.ENDIF
.ENDIF # ! UNX

.IF "$(GUI)" == "WNT"
SHL1RES=	$(RCTARGET)
.ENDIF # WNT

# --- Targets -------------------------------------------------------------

.INCLUDE :  target.mk

