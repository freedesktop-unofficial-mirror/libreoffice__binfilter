#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.10 $
#
#   last change: $Author: obo $ $Date: 2007-07-17 08:55:37 $
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

EXCEPTIONSFILES=	\
    $(SLO)$/offmgr_app.obj		

SLOFILES=\
    $(SLO)$/offmgr_app.obj		

.INCLUDE :  target.mk

