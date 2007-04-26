#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.9 $
#
#   last change: $Author: rt $ $Date: 2007-04-26 13:50:39 $
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

BFPRJ=..
PRJ=..$/..

ENABLE_EXCEPTIONS=TRUE

PRJNAME=binfilter
TARGET=bf_sfx

NO_HIDS=TRUE

.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk

INC+= -I$(PRJ)$/inc$/bf_sfx2
# --- Allgemein ----------------------------------------------------

LIB1TARGET= $(SLB)$/$(TARGET).lib
LIB1ARCHIV=$(LB)$/lib$(TARGET).a
LIB1FILES=  $(SLB)$/sfx2_appl.lib		\
            $(SLB)$/sfx2_explorer.lib	\
            $(SLB)$/sfx2_doc.lib			\
            $(SLB)$/sfx2_view.lib		\
            $(SLB)$/sfx2_control.lib		\
            $(SLB)$/sfx2_notify.lib		\
            $(SLB)$/sfx2_menu.lib		\
            $(SLB)$/sfx2_inet.lib		\
            $(SLB)$/sfx2_accel.lib		\
            $(SLB)$/sfx2_toolbox.lib		\
            $(SLB)$/sfx2_statbar.lib		\
            $(SLB)$/sfx2_dialog.lib		\
            $(SLB)$/sfx2_bastyp.lib		\
            $(SLB)$/sfx2_config.lib

SFXSRSLIST=\
        $(SRS)$/sfx2_accel.srs \
        $(SRS)$/sfx2_appl.srs \
        $(SRS)$/sfx2_sfx.srs \
        $(SRS)$/sfx2_doc.srs \
        $(SRS)$/sfx2_view.srs \
        $(SRS)$/sfx2_config.srs \
        $(SRS)$/sfx2_menu.srs \
        $(SRS)$/sfx2_statbar.srs \
        $(SRS)$/sfx2_toolbox.srs \
        $(SRS)$/sfx2_dialog.srs \
        $(SRS)$/sfx2_bastyp.srs \
        $(SRS)$/sfx2_explorer.srs

RESLIB1NAME=$(TARGET)
RESLIB1SRSFILES=$(SFXSRSLIST)

# --- Targets ------------------------------------------------------


.INCLUDE :  target.mk


## --- SFX-Filter-Datei ---
#
#$(MISC)$/$(SHL1TARGET).flt: makefile.mk
#    @echo ------------------------------
#    @echo Making: $@
#    @$(TYPE) sfxwin.flt > $@


