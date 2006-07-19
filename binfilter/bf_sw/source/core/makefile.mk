#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: kz $ $Date: 2006-07-19 13:40:20 $
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
TARGET=sw_core

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

#.INCLUDE :  $(PRJ)$/inc$/swpre.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
#.INCLUDE :  $(PRJ)$/inc$/sw.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk

INC+= -I$(PRJ)$/inc$/bf_sw
.IF "$(CALLTARGETS)"=="core"
RC_SUBDIRS=
.ENDIF

# --- Files --------------------------------------------------------


#SUBLIBS1= \
#		$(SLB)$/access.lib \
#		$(SLB)$/graphic.lib \
#		$(SLB)$/para.lib \
#		$(SLB)$/attr.lib \
#		$(SLB)$/edit.lib \
#		$(SLB)$/crsr.lib \
#		$(SLB)$/view.lib \
#		$(SLB)$/frmedt.lib \
#		$(SLB)$/ole.lib \
#		$(SLB)$/fields.lib \
#		$(SLB)$/tox.lib \
#		$(SLB)$/undo.lib \
#		$(SLB)$/bastyp.lib

SUBLIBS1= \
        $(SLB)$/sw_graphic.lib \
        $(SLB)$/sw_para.lib \
        $(SLB)$/sw_attr.lib \
        $(SLB)$/sw_edit.lib \
        $(SLB)$/sw_crsr.lib \
        $(SLB)$/sw_view.lib \
        $(SLB)$/sw_frmedt.lib \
        $(SLB)$/sw_ole.lib \
        $(SLB)$/sw_fields.lib \
        $(SLB)$/sw_tox.lib \
        $(SLB)$/sw_undo.lib \
        $(SLB)$/sw_bastyp.lib

SUBLIBS2= \
        $(SLB)$/sw_draw.lib \
        $(SLB)$/sw_sw3io.lib \
        $(SLB)$/sw_swg.lib \
        $(SLB)$/sw_layout.lib \
        $(SLB)$/sw_text.lib \
        $(SLB)$/sw_txtnode.lib \
        $(SLB)$/sw_doc.lib \
        $(SLB)$/sw_docnode.lib \
        $(SLB)$/sw_unocore.lib

.IF "$(PRODUCT)" == ""
SUBLIBS2+= \
        $(SLB)$/sw_except.lib
.ENDIF

#-------------------------------------------------------------------------

################################################################

LIB1TARGET=$(SLB)$/sw_core1.lib
LIB1FILES= \
        $(SUBLIBS1)

LIB2TARGET=$(SLB)$/sw_core2.lib
LIB2FILES= \
        $(SUBLIBS2)

.INCLUDE :  target.mk

################################################################

#-------------------------------------------------------------------------


