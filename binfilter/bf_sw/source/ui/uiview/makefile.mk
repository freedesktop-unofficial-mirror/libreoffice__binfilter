#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: kz $ $Date: 2006-07-19 15:03:39 $
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
TARGET=sw_uiview

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

AUTOSEG=true

# --- Settings -----------------------------------------------------

#.INCLUDE :  $(PRJ)$/inc$/swpre.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
#.INCLUDE :  $(PRJ)$/inc$/sw.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk

INC+= -I$(PRJ)$/inc$/bf_sw
# --- Files --------------------------------------------------------

SRS1NAME=$(TARGET)
SRC1FILES =  \
        sw_view.src \
        sw_pview.src

SLOFILES =  \
        $(SLO)$/sw_view0.obj \
        $(SLO)$/sw_view.obj \
        $(SLO)$/sw_view1.obj \
        $(SLO)$/sw_view2.obj \
        $(SLO)$/sw_viewcoll.obj \
        $(SLO)$/sw_viewdlg2.obj \
        $(SLO)$/sw_viewdlg.obj \
        $(SLO)$/sw_viewdraw.obj \
        $(SLO)$/sw_viewling.obj \
        $(SLO)$/sw_viewmdi.obj \
        $(SLO)$/sw_pview.obj \
        $(SLO)$/sw_viewport.obj \
        $(SLO)$/sw_viewstat.obj \
        $(SLO)$/sw_viewtab.obj \
        $(SLO)$/sw_viewprt.obj \
        $(SLO)$/sw_viewsrch.obj \
        $(SLO)$/sw_scroll.obj \
        $(SLO)$/sw_swcli.obj  \
        $(SLO)$/sw_srcview.obj \
        $(SLO)$/sw_uivwimp.obj

EXCEPTIONSFILES= \
        $(SLO)$/sw_srcview.obj \
        $(SLO)$/sw_uivwimp.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

$(SRS)$/sw_uiview.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc

