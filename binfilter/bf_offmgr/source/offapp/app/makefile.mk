#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.9 $
#
#   last change: $Author: vg $ $Date: 2007-02-06 12:39:10 $
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



PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PRJNAME=binfilter
TARGET=offmgr_app

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

PROJECTPCH=offmgr_ofapch
PDBTARGET=offmgr_ofapch
PROJECTPCHSOURCE=$(BFPRJ)$/util\offmgr_ofapch

# --- Settings ------------------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_offmgr


.IF "$(prjpch)" != ""
CDEFS=$(CDEFS) -DPRECOMPILED
.ENDIF

.IF "$(GUI)"=="UNX"
    CDEFS+=-DDLL_NAME=libbf_ofa$(UPD)$(DLLPOSTFIX)$(DLLPOST)
.ELSE
    CDEFS+=-DDLL_NAME=bf_ofa$(UPD)$(DLLPOSTFIX)$(DLLPOST)
.ENDIF

RSCUPDVER=$(RSCREVISION)(SV$(UPD)$(UPDMINOR))

#IMGLST_SRS=$(SRS)$/offmgr_app.srs

# --- Allgemein -----------------------------------------------------------

CINTERNAME=bf_ofa

SRS1NAME= offmgr_app
SRC1FILES=	\
    offmgr_app.src

EXCEPTIONSFILES=	\
    $(SLO)$/offmgr_optuno.obj	\
    $(SLO)$/offmgr_apearcfg.obj	\
    $(SLO)$/offmgr_app.obj		\
    $(SLO)$/offmgr_appctor.obj     \
    $(SLO)$/offmgr_appimp.obj	\
    $(SLO)$/offmgr_appstat.obj	\
    $(SLO)$/offmgr_osplcfg.obj	\
    $(SLO)$/offmgr_app2.obj	\
    $(SLO)$/offmgr_app3.obj

SLOFILES=\
    $(SLO)$/offmgr_appctor.obj     \
    $(SLO)$/offmgr_optuno.obj	\
    $(SLO)$/offmgr_apearcfg.obj	\
    $(SLO)$/offmgr_app.obj		\
    $(SLO)$/offmgr_app2.obj	\
    $(SLO)$/offmgr_appimp.obj	\
    $(SLO)$/offmgr_appstat.obj	\
    $(SLO)$/offmgr_fltrcfg.obj	\
    $(SLO)$/offmgr_htmlcfg.obj	\
    $(SLO)$/offmgr_ofaaccfg.obj	\
    $(SLO)$/offmgr_osplcfg.obj	\
    $(SLO)$/offmgr_resid.obj	\
    $(SLO)$/offmgr_app3.obj	\
    $(SLO)$/offmgr_appbas.obj \
    $(SLO)$/offmgr_fontsubstconfig.obj

.INCLUDE :  target.mk

$(SRS)$/offmgr_app.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc

