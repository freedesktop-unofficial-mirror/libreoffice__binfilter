#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: obo $ $Date: 2008-02-25 15:18:21 $
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

BFPRJ=..
PRJ=..$/..

PRJNAME=binfilter
TARGET=bf_sb

# --- Settings ---------------------------------------------------

.INCLUDE :  settings.mk

# --- Allgemein ---------------------------------------------------

LIB1TARGET=$(SLB)$/$(TARGET).lib
LIB1FILES=      \
    $(SLB)$/basic_basicmgr.lib \
    $(SLB)$/basic_sbx.lib \
    $(SLB)$/basic_classes.lib \
    $(SLB)$/basic_comp.lib \
    $(SLB)$/basic_runtime.lib

SHL1TARGET=$(TARGET)$(DLLPOSTFIX)
SHL1IMPLIB=$(TARGET)

SHL1STDLIBS= \
            $(CPPULIB) \
            $(CPPUHELPERLIB) \
            $(TOOLSLIB) \
            $(SVTOOLLIB) \
            $(SVLLIB)   \
            $(SVLIB) \
            $(VOSLIB) \
            $(SALLIB) \
            $(COMPHELPERLIB) \
            $(UNOTOOLSLIB) \
            $(SOTLIB) \
            $(VOSLIB) \
            $(VCLLIB) \
            $(XMLSCRIPTLIB)

.IF "$(GUI)"=="WNT"
SHL1STDLIBS+=   \
    $(UWINAPILIB)	\
    $(OLEAUT32LIB)
.ENDIF # WNT

SHL1DEF=    $(MISC)$/$(SHL1TARGET).def
SHL1LIBS=   $(SLB)$/$(TARGET).lib

DEF1NAME    =$(SHL1TARGET)
DEF1DEPN    =   \
    $(MISC)$/$(SHL1TARGET).flt

DEFLIB1NAME =$(TARGET)

# --- Targets -----------------------------------------------------------

.INCLUDE :  target.mk
 
# --- Basic-Filter-Datei ---

$(MISC)$/$(SHL1TARGET).flt: makefile.mk
    @echo ------------------------------
    @echo Making: $@
    @echo __CT >> $@


