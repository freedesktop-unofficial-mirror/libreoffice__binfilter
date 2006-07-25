#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.6 $
#
#   last change: $Author: rt $ $Date: 2006-07-25 08:49:42 $
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

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
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
        $(SLO)$/sw_viewdraw.obj \
        $(SLO)$/sw_viewmdi.obj \
        $(SLO)$/sw_pview.obj \
        $(SLO)$/sw_viewport.obj \
        $(SLO)$/sw_viewstat.obj \
        $(SLO)$/sw_viewtab.obj \
        $(SLO)$/sw_viewprt.obj \
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

