#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.8 $
#
#   last change: $Author: obo $ $Date: 2007-07-17 09:16:47 $
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
TARGET=sc_dbgui

NO_HIDS=TRUE

PROJECTPCH4DLL=TRUE
PROJECTPCH=ui_pch
PDBTARGET=ui_pch
PROJECTPCHSOURCE=..\pch\sc_ui_pch

# --- Settings -----------------------------------------------------

.INCLUDE :  scpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sc.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sc
# --- Files --------------------------------------------------------

SLOFILES =	\
    $(SLO)$/sc_imoptdlg.obj	\
    $(SLO)$/sc_asciiopt.obj

SRS1NAME=$(TARGET)
SRC1FILES =  \
        sc_pivot.src		\
        sc_imoptdlg.src    \
        sc_asciiopt.src    \
        sc_outline.src

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk


