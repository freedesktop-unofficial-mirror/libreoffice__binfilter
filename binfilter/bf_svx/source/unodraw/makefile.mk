#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: kz $ $Date: 2006-07-19 13:38:52 $
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
TARGET=svx_unodraw

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Files --------------------------------------------------------

CXXFILES =				\
        svx_UnoNamespaceMap.cxx \
        svx_UnoGraphicExporter.cxx \
        svx_unopool.cxx \
        svx_XPropertyTable.cxx \
        svx_UnoNameItemTable.cxx \
        svx_unoipset.cxx	\
        svx_unoshape.cxx	\
        svx_unoshap2.cxx	\
        svx_unoshap3.cxx	\
        svx_unoshap4.cxx	\
        svx_unopage.cxx		\
        svx_unoshtxt.cxx	\
        svx_unoshcol.cxx	\
        svx_unoprov.cxx		\
        svx_unomod.cxx      \
        svx_unonrule.cxx	\
        svx_unofdesc.cxx	\
        svx_unoctabl.cxx	\
        svx_unomlstr.cxx	\
        svx_unogtabl.cxx	\
        svx_unohtabl.cxx	\
        svx_unobtabl.cxx	\
        svx_unottabl.cxx	\
        svx_unomtabl.cxx	\
        svx_unodtabl.cxx	\
        svx_gluepts.cxx

SVXLIGHTOBJFILES=\
        $(OBJ)$/svx_unopool.obj \
        $(OBJ)$/svx_XPropertyTable.obj \
        $(OBJ)$/svx_UnoNameItemTable.obj \
        $(OBJ)$/svx_unoshape.obj	\
        $(OBJ)$/svx_unoipset.obj	\
        $(OBJ)$/svx_unoctabl.obj	\
        $(OBJ)$/svx_unoshap2.obj	\
        $(OBJ)$/svx_unoshap3.obj	\
        $(OBJ)$/svx_unoshap4.obj	\
        $(OBJ)$/svx_unopage.obj		\
        $(OBJ)$/svx_unoshtxt.obj	\
        $(OBJ)$/svx_unoshcol.obj	\
        $(OBJ)$/svx_unoprov.obj		\
        $(OBJ)$/svx_unomod.obj      \
        $(OBJ)$/svx_unonrule.obj	\
        $(OBJ)$/svx_unofdesc.obj	\
        $(OBJ)$/svx_unomlstr.obj	\
        $(OBJ)$/svx_unogtabl.obj	\
        $(OBJ)$/svx_unohtabl.obj	\
        $(OBJ)$/svx_unobtabl.obj	\
        $(OBJ)$/svx_unottabl.obj	\
        $(OBJ)$/svx_unomtabl.obj	\
        $(OBJ)$/svx_unodtabl.obj	\
        $(OBJ)$/svx_gluepts.obj

SLOFILES =	\
        $(SLO)$/svx_UnoNamespaceMap.obj \
        $(SLO)$/svx_UnoGraphicExporter.obj \
        $(SLO)$/svx_unopool.obj \
        $(SLO)$/svx_XPropertyTable.obj \
        $(SLO)$/svx_UnoNameItemTable.obj \
        $(SLO)$/svx_unoshape.obj	\
        $(SLO)$/svx_unoipset.obj	\
        $(SLO)$/svx_unoctabl.obj	\
        $(SLO)$/svx_unoshap2.obj	\
        $(SLO)$/svx_unoshap3.obj	\
        $(SLO)$/svx_unoshap4.obj	\
        $(SLO)$/svx_unopage.obj		\
        $(SLO)$/svx_unoshtxt.obj	\
        $(SLO)$/svx_unoshcol.obj	\
        $(SLO)$/svx_unoprov.obj		\
        $(SLO)$/svx_unomod.obj      \
        $(SLO)$/svx_unonrule.obj	\
        $(SLO)$/svx_unofdesc.obj	\
        $(SLO)$/svx_unomlstr.obj	\
        $(SLO)$/svx_unogtabl.obj	\
        $(SLO)$/svx_unohtabl.obj	\
        $(SLO)$/svx_unobtabl.obj	\
        $(SLO)$/svx_unottabl.obj	\
        $(SLO)$/svx_unomtabl.obj	\
        $(SLO)$/svx_unodtabl.obj	\
        $(SLO)$/svx_gluepts.obj

#SRSNAME=unodraw
#SRS1NAME=$(TARGET)
#SRC1FILES =  \
#		svx_unodraw.src

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

