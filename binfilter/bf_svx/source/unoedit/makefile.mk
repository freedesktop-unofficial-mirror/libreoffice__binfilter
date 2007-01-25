#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.6 $
#
#   last change: $Author: obo $ $Date: 2007-01-25 12:02:23 $
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
TARGET=svx_unoedit

NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Files --------------------------------------------------------

SLOFILES =	\
        $(SLO)$/svx_UnoForbiddenCharsTable.obj \
        $(SLO)$/svx_unoedsrc.obj	\
        $(SLO)$/svx_unoedhlp.obj	\
        $(SLO)$/svx_unopracc.obj	\
        $(SLO)$/svx_unoedprx.obj	\
        $(SLO)$/svx_unoviwed.obj	\
        $(SLO)$/svx_unoviwou.obj	\
        $(SLO)$/svx_unofored.obj	\
        $(SLO)$/svx_unoforou.obj	\
        $(SLO)$/svx_unotext.obj		\
        $(SLO)$/svx_unotext2.obj	\
        $(SLO)$/svx_unofield.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

