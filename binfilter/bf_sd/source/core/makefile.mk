#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.7 $
#
#   last change: $Author: hr $ $Date: 2006-08-14 14:18:37 $
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

PROJECTPCH=sd
PROJECTPCHSOURCE=$(BFPRJ)$/util$/sd_sd

PRJNAME=binfilter
TARGET=sd_core

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sd
IENV+=-I..\ui\inc

# --- Files --------------------------------------------------------


SRS1NAME=$(TARGET)
SRC1FILES = sd_glob.src

SLOFILES = $(SLO)$/sd_stlsheet.obj  \
           $(SLO)$/sd_stlpool.obj	\
           $(SLO)$/sd_drawdoc.obj \
           $(SLO)$/sd_drawdoc2.obj \
           $(SLO)$/sd_drawdoc3.obj \
           $(SLO)$/sd_drawdoc4.obj \
           $(SLO)$/sd_sdpage.obj \
           $(SLO)$/sd_sdattr.obj \
           $(SLO)$/sd_sdobjfac.obj \
           $(SLO)$/sd_anminfo.obj	\
           $(SLO)$/sd_sdiocmpt.obj	\
           $(SLO)$/sd_sdpage2.obj	\
           $(SLO)$/sd_typemap.obj	\
           $(SLO)$/sd_cusshow.obj

EXCEPTIONSFILES= \
           $(SLO)$/sd_drawdoc.obj

.IF "$(SVXLIGHT)"!=""
EXCEPTIONSFILES+= \
           $(OBJ)$/sd_sxl_drawdoc.obj
.ENDIF          # "$(SVXLIGHT)"!=""

SVXLIGHTOBJFILES = \
           $(OBJ)$/sd_stlsheet.obj  \
           $(OBJ)$/sd_stlpool.obj	\
           $(OBJ)$/sd_drawdoc.obj \
           $(OBJ)$/sd_drawdoc2.obj \
           $(OBJ)$/sd_drawdoc3.obj \
           $(OBJ)$/sd_drawdoc4.obj \
           $(OBJ)$/sd_sdpage.obj \
           $(OBJ)$/sd_sdattr.obj \
           $(OBJ)$/sd_sdobjfac.obj \
           $(OBJ)$/sd_anminfo.obj	\
           $(OBJ)$/sd_sdiocmpt.obj	\
           $(OBJ)$/sd_sdpage2.obj	\
           $(OBJ)$/sd_typemap.obj	\
           $(OBJ)$/sd_cusshow.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

