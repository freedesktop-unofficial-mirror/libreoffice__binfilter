#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: aw $ $Date: 2003-10-09 14:12:28 $
#
#   The Contents of this file are made available subject to the terms of
#   either of the following licenses
#
#          - GNU Lesser General Public License Version 2.1
#          - Sun Industry Standards Source License Version 1.1
#
#   Sun Microsystems Inc., October, 2000
#
#   GNU Lesser General Public License Version 2.1
#   =============================================
#   Copyright 2000 by Sun Microsystems, Inc.
#   901 San Antonio Road, Palo Alto, CA 94303, USA
#
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU Lesser General Public
#   License version 2.1, as published by the Free Software Foundation.
#
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with this library; if not, write to the Free Software
#   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#   MA  02111-1307  USA
#
#
#   Sun Industry Standards Source License Version 1.1
#   =================================================
#   The contents of this file are subject to the Sun Industry Standards
#   Source License Version 1.1 (the "License"); You may not use this file
#   except in compliance with the License. You may obtain a copy of the
#   License at http://www.openoffice.org/license.html.
#
#   Software provided under this License is provided on an "AS IS" basis,
#   WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
#   WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
#   MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
#   See the License for the specific provisions governing your rights and
#   obligations concerning the Software.
#
#   The Initial Developer of the Original Code is: Sun Microsystems, Inc.
#
#   Copyright: 2000 by Sun Microsystems, Inc.
#
#   All Rights Reserved.
#
#   Contributor(s): _______________________________________
#
#
#
#*************************************************************************

PRJ=..$/..
BFPRJ=..

PRJNAME=binfilter
TARGET=bf_ofa
#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
.IF "$(CPU)"=="i386"
USE_LDUMP2=TRUE
.ENDIF

PROJECTPCH=offmgr_ofapch
PDBTARGET=offmgr_ofapch
PROJECTPCHSOURCE=$(BFPRJ)$/util$/offmgr_ofapch

# --- Settings ------------------------------------------------------------

.INCLUDE :	settings.mk
INC+= -I$(PRJ)$/inc$/bf_offmgr

.IF "$(prjpch)" != ""
CDEFS+=-DPRECOMPILED
.ENDIF

RSCLOCINC!:=$(RSCLOCINC);$(PRJ)$/RES
SOLARLIB+=-L$(LB)

# --- Allgemein -----------------------------------------------------------

RES1FILELIST=\
    $(SRS)$/offmgr_ofaslots.srs \
    $(SRS)$/offmgr_dialog.srs \
    $(SRS)$/offmgr_app.srs \
    $(SOLARRESDIR)$/svtools.srs \
    $(SOLARRESDIR)$/so2.srs 	

RESLIB1NAME=$(TARGET)
RESLIB1SRSFILES=$(RES1FILELIST)

# -------------------------------------------------------------------------

LIB3TARGET= $(SLB)$/$(TARGET).lib
LIB3FILES=	$(SLB)$/offmgr_app.lib 		\
            $(SLB)$/offmgr_dialog.lib

#.IF "$(GUI)"!="UNX"
#LIB3FILES+= \
#	$(LIBPRE) $(SOLARLIBDIR)$/ysch.lib	\
#	$(LIBPRE) $(SOLARLIBDIR)$/ysm.lib
#.ENDIF # "$(GUI)"!="UNX"

SHL2TARGET= $(TARGET)$(UPD)$(DLLPOSTFIX)
SHL2IMPLIB= $(TARGET)
SHL2LIBS=	$(SLB)$/$(TARGET).lib

# static libraries
SHL2STDLIBS= $(BASICIDELIB)

#.IF "$(GUI)"=="UNX"
#SHL2STDLIBS+= \
#	$(SCHLIB) \
#	$(SMLIB)
#.ENDIF # "$(GUI)" == "UNX"

# dynamic libraries
SHL2STDLIBS+= \
    $(BFSVXLIB) \
    $(LEGACYSMGRLIB)	\
    $(BASICLIB) \
    $(GOODIESLIB) \
    $(SVTOOLLIB) \
    $(SVLLIB)	\
    $(VCLLIB) \
    $(TOOLSLIB) \
    $(UNOTOOLSLIB) \
    $(COMPHELPERLIB) \
    $(CPPUHELPERLIB) \
    $(CPPULIB) \
    $(VOSLIB) \
    $(SALLIB)

.IF "$(GUI)" == "UNX"
SHL2STDLIBS+= \
            $(BFSFXLIB)
.ENDIF                 

.IF "$(GUI)"=="WNT"
SHL2STDLIBS += $(LIBPRE) advapi32.lib
.ENDIF # WNT

SHL2DEF=	$(MISC)$/$(SHL2TARGET).def
SHL2BASE=	0x1de00000

DEF2NAME=	$(SHL2TARGET)
DEF2DEPN=	$(MISC)$/$(SHL2TARGET).flt
DEFLIB2NAME =$(TARGET)
DEF2DES 	=offmgr app-interface

# -------------------------------------------------------------------------

.IF "$(GUI)"=="WNT"
LIB4TARGET= $(LB)$/a$(TARGET).lib
LIB4FILES=	$(LB)$/$(TARGET).lib
.ENDIF


.IF "$(BUILD_SOSL)"==""
.IF "$(depend)" == ""
ALL:\
    $(INCCOM)$/sba.hrc		\
    $(LIB3TARGET)			\
    $(INCCOM)$/class.lst	\
    ALLTAR

.ENDIF # "$(depend)" == ""
.ENDIF # "$(BUILD_SOSL)" == ""

.INCLUDE :	target.mk

$(MISCX)$/$(SHL2TARGET).flt: makefile.mk
    @echo ------------------------------
    @echo Making: $@
    @echo WEP>$@
    @echo PlugInApplication>>$@
    @echo __dt__17OfficeApplication>>$@
    @echo LibMain>>$@
    @echo _Impl>>$@
    @echo _Imp>>$@
    @echo solver>>$@
    @echo bad_alloc>>$@
    @echo exception12>>$@
.IF "$(GUI)"=="WNT"
    @echo __CT>>$@
.ENDIF

# ------------------------------------------------------------------
# Windows NT
# ------------------------------------------------------------------

$(INCCOM)$/class.lst:
.IF "$(BUILD_SOSL)"==""
.IF "$(GUI)$(CPU)$(UPDATER)"=="WNTIYES"
    +-$(COPY) class.lst $@
.ELSE
    @+echo nix
.ENDIF
.ENDIF			# "$(BUILD_SOSL)"==""

#$(INCCOM)$/sba.hrc: $(INC)$/sbasltid.hrc
$(INCCOM)$/sba.hrc: $(PRJ)$/inc$/bf_offmgr/sbasltid.hrc
    @+-$(COPY) $(INC)$/sbasltid.hrc $(INCCOM)$/sba.hrc
    @+-$(COPY) $(INC)$/sbasltid.hrc $(INC)$/sba,hrc
