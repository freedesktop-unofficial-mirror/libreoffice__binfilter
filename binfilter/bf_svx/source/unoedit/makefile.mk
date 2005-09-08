#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.4 $
#
#   last change: $Author: rt $ $Date: 2005-09-08 07:31:01 $
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

PRJ=..$/..$/..
BFPRJ=..$/..

PRJNAME=binfilter
TARGET=svx_unoedit

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
        svx_UnoForbiddenCharsTable.cxx \
        svx_unoedsrc.cxx	\
        svx_unoedhlp.cxx	\
        svx_unopracc.cxx	\
        svx_unoedprx.cxx	\
        svx_unoviwed.cxx	\
        svx_unoviwou.cxx	\
        svx_unofored.cxx	\
        svx_unoforou.cxx	\
        svx_unotext.cxx		\
        svx_unotext2.cxx	\
        svx_unofield.cxx	

SVXLIGHTOBJFILES=\
        $(OBJ)$/svx_UnoForbiddenCharsTable.obj \
        $(OBJ)$/svx_unoedsrc.obj	\
        $(OBJ)$/svx_unoedhlp.obj	\
        $(OBJ)$/svx_unopracc.obj	\
        $(OBJ)$/svx_unoedprx.obj	\
        $(OBJ)$/svx_unoviwed.obj	\
        $(OBJ)$/svx_unoviwou.obj	\
        $(OBJ)$/svx_unofored.obj	\
        $(OBJ)$/svx_unoforou.obj	\
        $(OBJ)$/svx_unotext.obj		\
        $(OBJ)$/svx_unotext2.obj	\
        $(OBJ)$/svx_unofield.obj

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

