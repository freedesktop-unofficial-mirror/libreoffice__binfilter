#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: kz $ $Date: 2006-07-19 15:03:12 $
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
TARGET=sw_shells

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
        sw_shells.src \
        sw_pseudo.src

SLOFILES =  \
        $(SLO)$/sw_basesh.obj \
        $(SLO)$/sw_beziersh.obj \
        $(SLO)$/sw_drawdlg.obj \
        $(SLO)$/sw_drawsh.obj \
        $(SLO)$/sw_drformsh.obj \
        $(SLO)$/sw_drwbassh.obj \
        $(SLO)$/sw_drwtxtex.obj \
        $(SLO)$/sw_drwtxtsh.obj \
        $(SLO)$/sw_frmsh.obj \
        $(SLO)$/sw_grfsh.obj \
        $(SLO)$/sw_grfshex.obj \
        $(SLO)$/sw_listsh.obj \
        $(SLO)$/sw_olesh.obj \
        $(SLO)$/sw_slotadd.obj \
        $(SLO)$/sw_tabsh.obj \
        $(SLO)$/sw_textdrw.obj \
        $(SLO)$/sw_textfld.obj \
        $(SLO)$/sw_textglos.obj \
        $(SLO)$/sw_textidx.obj \
        $(SLO)$/sw_textsh.obj \
        $(SLO)$/sw_textsh1.obj \
        $(SLO)$/sw_textsh2.obj \
        $(SLO)$/sw_txtattr.obj \
        $(SLO)$/sw_txtcrsr.obj \
        $(SLO)$/sw_txtnum.obj

EXCEPTIONSFILES =  \
        $(SLO)$/sw_textsh2.obj \
        $(SLO)$/sw_grfshex.obj	\
        $(SLO)$/sw_textsh1.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

$(SRS)$/sw_shells.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc

