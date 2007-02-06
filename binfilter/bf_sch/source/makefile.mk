#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.6 $
#
#   last change: $Author: vg $ $Date: 2007-02-06 12:40:14 $
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

PRJ=..$/..
BFPRJ=..

PROJECTPCH=sch
PROJECTPCHSOURCE=$(BFPRJ)$/util\sch_sch

PRJNAME=binfilter
TARGET=sch

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

LIBTARGET=NO

# --- Settings -----------------------------------------------------
.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_sch
.IF "$(GUI)$(COM)" == "WINMSC"
LIBFLAGS+=/PAGE:128
.ENDIF


# --- Files --------------------------------------------------------

# --- ui Lib

LIB1TARGET= $(SLB)$/ui.lib
LIB1FILES= \
    $(SLB)$/app.lib \
    $(SLB)$/dlg.lib \
    $(SLB)$/docshell.lib \
    $(SLB)$/func.lib \
    $(SLB)$/view.lib \
    $(SLB)$/chxchart.lib 


# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk
