#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.10 $
#
#   last change: $Author: rt $ $Date: 2008-03-12 11:04:12 $
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
TARGET=binfilterdetect

NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE
LIBTARGET=NO
DLLTARGET=bindet

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk

# --- Files --------------------------------------------------------

SLOFILES =      \
        $(SLO)$/bindetect.obj

SHL1DEPN=makefile.mk
SHL1OBJS=$(SLOFILES)
SHL1TARGET=$(DLLTARGET)$(DLLPOSTFIX)
SHL1IMPLIB=i$(DLLTARGET)
SHL1DEF=$(MISC)$/$(SHL1TARGET).def
DEF1NAME=$(SHL1TARGET)
SHL1VERSIONMAP=exports.map

SHL1STDLIBS= \
    $(BFSVTOOLLIB)	\
    $(SOTLIB)	\
    $(VCLLIB)	\
    $(TOOLSLIB)	\
    $(CPPUHELPERLIB)\
    $(CPPULIB)	\
    $(COMPHELPERLIB) \
    $(UNOTOOLSLIB) \
    $(SALLIB)

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

