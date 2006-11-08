#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.7 $
#
#   last change: $Author: kz $ $Date: 2006-11-08 12:37:32 $
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
TARGET=sw_filter

NO_HIDS=TRUE

.IF "$(CALLTARGETS)"=="filter"
RC_SUBDIRS=
.ENDIF

# --- Settings -----------------------------------------------------

.INCLUDE :	$(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :	settings.mk
.INCLUDE :	$(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw
# --- Files --------------------------------------------------------


SUBLIBS= \
    $(SLB)$/sw_ascii.lib \
    $(SLB)$/sw_basflt.lib \
    $(SLB)$/sw_writer.lib \
    $(SLB)$/sw_excel.lib \
    $(SLB)$/sw_lotus.lib \
    $(SLB)$/sw_w4w.lib \
    $(SLB)$/sw_xml.lib \
    $(SLB)$/sw_sw6.lib

################################################################

LIB1TARGET=$(SLB)$/sw_filter.lib
LIB1FILES= \
        $(SUBLIBS)

.INCLUDE :	target.mk

################################################################


