#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.8 $
#
#   last change: $Author: obo $ $Date: 2007-07-17 10:07:40 $
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

PROJECTPCH=sd
PROJECTPCHSOURCE=$(BFPRJ)$/util$/sd_sd

PRJNAME=binfilter
TARGET=sd_unoidl

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE
# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sd
# --- Files --------------------------------------------------------

.IF "$(COM)"=="GCC"
NOOPTFILES= $(SLO)$/sd_unowcntr.obj
.ENDIF

SLOFILES =      \
        $(SLO)$/sd_unopool.obj \
        $(SLO)$/sd_UnoDocumentSettings.obj \
        $(SLO)$/sd_facreg.obj \
        $(SLO)$/sd_unomodel.obj    \
        $(SLO)$/sd_unopage.obj     \
        $(SLO)$/sd_unolayer.obj    \
        $(SLO)$/sd_unopres.obj     \
        $(SLO)$/sd_unocpres.obj    \
        $(SLO)$/sd_unoobj.obj		\
        $(SLO)$/sd_unosrch.obj		\
        $(SLO)$/sd_unowcntr.obj	\
        $(SLO)$/sd_unogsfm.obj		\
        $(SLO)$/sd_unogstyl.obj	\
        $(SLO)$/sd_unopsfm.obj		\
        $(SLO)$/sd_unopstyl.obj	\
        $(SLO)$/sd_unokywds.obj	\
        $(SLO)$/sd_unostyls.obj	\
        $(SLO)$/sd_unopback.obj	\
        $(SLO)$/sd_unovwcrs.obj	\
        $(SLO)$/sd_unodoc.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

