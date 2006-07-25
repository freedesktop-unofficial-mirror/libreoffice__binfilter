#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.6 $
#
#   last change: $Author: rt $ $Date: 2006-07-25 08:51:20 $
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
TARGET=sw_utlui

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk

INC+= -I$(PRJ)$/inc$/bf_sw

# --- Files --------------------------------------------------------

CXXFILES = \
        sw_bookctrl.cxx \
        sw_content.cxx \
        sw_gloslst.cxx \
        sw_initui.cxx \
        sw_navipi.cxx \
        sw_prcntfld.cxx \
        sw_tmplctrl.cxx \
        sw_uitool.cxx \
        sw_uiitems.cxx \
        sw_attrdesc.cxx \
        sw_swstbctl.cxx \
        sw_zoomctrl.cxx

SRS1NAME=$(TARGET)
SRC1FILES =  \
        sw_initui.src \
        sw_gloslst.src \
        sw_navipi.src \
        sw_poolfmt.src \
        sw_attrdesc.src \
        sw_utlui.src

SLOFILES =  \
        $(SLO)$/sw_bookctrl.obj \
        $(SLO)$/sw_content.obj \
        $(SLO)$/sw_gloslst.obj \
        $(SLO)$/sw_initui.obj \
        $(SLO)$/sw_navipi.obj \
        $(SLO)$/sw_prcntfld.obj \
        $(SLO)$/sw_tmplctrl.obj \
        $(SLO)$/sw_uitool.obj \
        $(SLO)$/sw_uiitems.obj \
        $(SLO)$/sw_attrdesc.obj \
        $(SLO)$/sw_swstbctl.obj \
        $(SLO)$/sw_zoomctrl.obj


# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

