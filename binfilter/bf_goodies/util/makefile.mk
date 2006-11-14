#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: ihi $ $Date: 2006-11-14 11:58:50 $
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

PRJ=..$/..
BFPRJ=..

PRJNAME=binfilter
TARGET=bf_go

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

LIBTARGET=NO

# --- Settings -----------------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
INC+= -I$(PRJ)$/inc$/bf_go

# --- Files --------------------------------------------------------

LIB1TARGET=$(SLB)$/bf_go.lib
LIB1FILES=\
   $(SLB)$/goodies_base2d.lib	\
   $(SLB)$/goodies_base3d.lib

SHL1TARGET= bf_go$(UPD)$(DLLPOSTFIX)
SHL1IMPLIB= bf_go
SHL1DEF=$(MISC)$/$(SHL1TARGET).def
SHL1LIBS=	$(SLB)$/bf_go.lib

DEF1NAME	=$(SHL1TARGET)
DEF1DEPN	=$(MISC)$/$(SHL1TARGET).flt \
        $(LIB1TARGET)

DEF1DES		=Bf_Goodies
DEFLIB1NAME	=bf_go
#DEF1EXPORTFILE	=bf_goodies.dxp

SHL1STDLIBS= \
            $(GOODIESLIB)		\
            $(TOOLSLIB)			\
            $(SALLIB)

# --- Targets -------------------------------------------------------------

.INCLUDE :  target.mk

# --- Goodies-Filter-Datei ---

$(MISC)$/$(SHL1TARGET).flt: makefile.mk
    @echo ------------------------------
    @echo Making: $@
        @echo _Impl>$@
    @echo WEP>>$@
        @echo m_pLoader>$@
    @echo LIBMAIN>>$@
    @echo LibMain>>$@
        @echo CT>>$@
