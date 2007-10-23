#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: vg $ $Date: 2007-10-23 13:50:33 $
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
SUBPRJ=..$/..

PRJINC=$(SUBPRJ)

PRJNAME=binfilter
TARGET=so3_ole

# --- Settings -----------------------------------------------------
.INCLUDE :  settings.mk
.INCLUDE :  $(SUBPRJ)$/util$/makefile.pmk


# --- Files --------------------------------------------------------

CXXFILES=   \
             sosink.cxx                                \
            socli.cxx                                \
            socont.cxx									\
            ansi.cxx									\
            helpers.cxx									\
            uieffect.cxx								\

.IF "$(GUI)" == "WNT"
SLOFILES=   \
            $(SLO)$/sosink.obj                        \
            $(SLO)$/socli.obj						\
            $(SLO)$/socont.obj							\
            $(SLO)$/ansi.obj							\
            $(SLO)$/helpers.obj							\
            $(SLO)$/uieffect.obj
.ENDIF


# --- Tagets -------------------------------------------------------


.INCLUDE :  target.mk

.INCLUDE :  $(SUBPRJ)$/util$/target.pmk

