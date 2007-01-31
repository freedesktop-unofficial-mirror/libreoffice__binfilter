#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.6 $
#
#   last change: $Author: rt $ $Date: 2007-01-31 08:37:44 $
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

PRJ = ..$/..$/..
BFPRJ = ..$/..
PRJNAME = binfilter
TARGET = legacy_binfilters
USE_DEFFILE = TRUE
NO_BSYMBOLIC = TRUE
ENABLE_EXCEPTIONS = TRUE
# COMP1TYPELIST = $(TARGET)

# --- Settings -----------------------------------------------------

.INCLUDE : settings.mk
INC+= -I$(PRJ)$/inc$/legacysmgr
# ------------------------------------------------------------------

SLOFILES = \
    $(SLO)$/legacy_binfilters_smgr.obj

SHL1TARGET = $(TARGET)$(UPD)$(DLLPOSTFIX)

SHL1STDLIBS = \
    $(CPPUHELPERLIB)	\
    $(CPPULIB)		\
    $(SALLIB)

.IF "$(COMNAME)"=="msci"
SHL1VERSIONMAP=msci.map
.ELIF "$(COMNAME)"=="sunpro5"
SHL1VERSIONMAP=sols.map
.ELIF "$(OS)$(CPU)$(COMNAME)"=="LINUXIgcc2"
SHL1VERSIONMAP=lngi.map
.ELIF "$(OS)$(CPU)$(COMNAME)"=="LINUXIgcc3"
SHL1VERSIONMAP=gcc3_linux_intel.map
.ELIF "$(OS)$(CPU)$(COMNAME)"=="LINUXSgcc3"
SHL1VERSIONMAP=gcc3_linux_intel.map
.ELIF "$(OS)$(CPU)$(COMNAME)"=="MACOSXIgcc3"
SHL1VERSIONMAP=gcc3_linux_intel.map
.ENDIF

SHL1DEPN =
SHL1IMPLIB = i$(TARGET)
SHL1LIBS = $(SLB)$/$(TARGET).lib
SHL1DEF = $(MISC)$/$(SHL1TARGET).def
DEF1NAME = $(SHL1TARGET)

.IF "$(debug)" != ""

# msvc++: no inlining for debugging
.IF "$(COM)" == "MSC"
CFLAGS += -Ob0
.ENDIF

.ENDIF

# --- Targets ------------------------------------------------------

.INCLUDE :	target.mk

