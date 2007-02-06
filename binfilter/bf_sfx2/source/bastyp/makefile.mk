#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.8 $
#
#   last change: $Author: vg $ $Date: 2007-02-06 12:45:21 $
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
TARGET=sfx2_bastyp

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_sfx2

# --- Files --------------------------------------------------------

SLOFILES =\
        $(SLO)$/sfx2_misc.obj				\
        $(SLO)$/sfx2_idpool.obj				\
        $(SLO)$/sfx2_progress.obj			\
        $(SLO)$/sfx2_sfxresid.obj			\
        $(SLO)$/sfx2_newhdl.obj				\
        $(SLO)$/sfx2_bitset.obj				\
        $(SLO)$/sfx2_minarray.obj			\
        $(SLO)$/sfx2_fltfnc.obj				\
        $(SLO)$/sfx2_fltlst.obj				\
        $(SLO)$/sfx2_helper.obj

SRS1NAME=$(TARGET)
SRC1FILES =\
        sfx2_bastyp.src	\
        sfx2_newhdl.src

EXCEPTIONSFILES =\
    $(SLO)$/sfx2_helper.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

