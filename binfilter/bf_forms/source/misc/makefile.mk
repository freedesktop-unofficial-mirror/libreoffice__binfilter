#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: kz $ $Date: 2006-07-19 13:13:38 $
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
TARGET=forms_common

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE
#TARGETTYPE=GUI

# --- Settings ----------------------------------

.INCLUDE : settings.mk
INC+= -I$(PRJ)$/inc$/bf_forms
# --- Types -------------------------------------

INCPRE+=$(SOLARINCDIR)$/offuh

# --- Files -------------------------------------

SLOFILES=	$(SLO)$/forms_limitedformats.obj \
            $(SLO)$/forms_property.obj \
            $(SLO)$/forms_services.obj \
            $(SLO)$/forms_InterfaceContainer.obj \
            $(SLO)$/forms_ids.obj	\
            $(SLO)$/forms_formsmodule.obj

# --- Targets ----------------------------------

.INCLUDE : target.mk

