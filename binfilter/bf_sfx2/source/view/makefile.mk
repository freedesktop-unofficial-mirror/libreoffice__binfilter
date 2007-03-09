#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.9 $
#
#   last change: $Author: obo $ $Date: 2007-03-09 15:05:48 $
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

PRJNAME=			binfilter
TARGET=				sfx2_view

NO_HIDS=TRUE

ENABLE_EXCEPTIONS=	TRUE

.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_sfx2

# --- Files --------------------------------------------------------

SRS1NAME=$(TARGET)
SRC1FILES = \
        sfx2_view.src \
        sfx2_fsetview.src

SLOFILES =	\
        $(SLO)$/sfx2_frmload.obj \
        $(SLO)$/sfx2_fsetvwsh.obj \
        $(SLO)$/sfx2_frame.obj \
        $(SLO)$/sfx2_urlframe.obj \
        $(SLO)$/sfx2_contenv.obj \
        $(SLO)$/sfx2_printer.obj \
        $(SLO)$/sfx2_viewsh.obj \
        $(SLO)$/sfx2_viewprn.obj \
        $(SLO)$/sfx2_ipfrm.obj \
        $(SLO)$/sfx2_viewfac.obj \
        $(SLO)$/sfx2_intfrm.obj \
        $(SLO)$/sfx2_viewfrm.obj \
        $(SLO)$/sfx2_impframe.obj \
        $(SLO)$/sfx2_topfrm.obj \
        $(SLO)$/sfx2_sfxbasecontroller.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

