#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.11 $
#
#   last change: $Author: obo $ $Date: 2007-07-17 12:17:45 $
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

PRJ=..$/..$/..
BFPRJ=..$/..

PRJNAME=binfilter
TARGET=bf_wrapper

NO_HIDS=TRUE

LIBTARGET=NO
ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
RSCUPDVER=$(RSCREVISION)(SV$(UPD)$(UPDMINOR))

# --- Files --------------------------------------------------------

SLOFILES =	$(SLO)$/bf_wrapper.obj

SHL1OBJS=   $(SLOFILES)
SHL1TARGET= $(TARGET)$(UPD)$(DLLPOSTFIX)

SHL1IMPLIB= ibf_wrp
SHL1STDLIBS=    \
                $(FWELIB)			\
                $(BFBASICLIB) 		\
                $(SO2LIB) 			\
                $(SJLIB) 			\
                $(TKLIB) 			\
                $(SVTOOLLIB) 		\
                $(SVLLIB) 			\
                $(BFOFALIB)			\
                $(VCLLIB) 			\
                $(SOTLIB) 			\
                $(SALLIB)			\
                $(VOSLIB)			\
                $(TOOLSLIB)			\
                $(CPPULIB)			\
                $(CPPUHELPERLIB)	\
                $(BFSCHLIB)         \
                $(BFSMLIB)          \
                $(BFSWLIB)          \
                $(BFSDLIB)          \
                $(BFSCLIB)          \
                $(BFSVXLIB)         \
                $(UNOTOOLSLIB)		\
                $(COMPHELPERLIB)	\
                $(LEGACYSMGRLIB)

SHL1DEPN=       makefile.mk
SHL1DEF=        $(MISC)$/$(SHL1TARGET).def

DEF1NAME=       $(SHL1TARGET)
DEF1EXPORTFILE= exports.dxp

# --- Targets ------------------------------------------------------

.IF "$(depend)" != ""
SRCFILES=$(SRC1FILES)
.ENDIF

.INCLUDE :  target.mk

