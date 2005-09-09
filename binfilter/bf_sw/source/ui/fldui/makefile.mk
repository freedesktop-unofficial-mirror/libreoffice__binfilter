#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.4 $
#
#   last change: $Author: rt $ $Date: 2005-09-09 05:02:11 $
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

PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PRJNAME=binfilter
TARGET=sw_fldui

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

CXXFILES = \
        sw_changedb.cxx \
        sw_DropDownFieldDialog.cxx\
        sw_flddb.cxx \
        sw_flddinf.cxx \
        sw_flddok.cxx \
        sw_fldedt.cxx \
        sw_fldfunc.cxx \
        sw_fldmgr.cxx \
        sw_fldpage.cxx \
        sw_fldref.cxx \
        sw_fldtdlg.cxx \
        sw_fldvar.cxx \
        sw_javaedit.cxx \
        sw_inpdlg.cxx \
        sw_xfldui.cxx

SRS1NAME=$(TARGET)
SRC1FILES =  \
        sw_changedb.src \
        sw_DropDownFieldDialog.src\
        sw_flddb.src \
        sw_flddinf.src \
        sw_flddok.src \
        sw_fldfunc.src \
        sw_fldref.src \
        sw_fldtdlg.src \
        sw_fldui.src \
        sw_fldvar.src \
        sw_javaedit.src \
        sw_inpdlg.src

SLOFILES =  \
        $(SLO)$/sw_changedb.obj \
        $(SLO)$/sw_DropDownFieldDialog.obj \
        $(SLO)$/sw_flddb.obj \
        $(SLO)$/sw_flddinf.obj \
        $(SLO)$/sw_flddok.obj \
        $(SLO)$/sw_fldedt.obj \
        $(SLO)$/sw_fldfunc.obj \
        $(SLO)$/sw_fldmgr.obj \
        $(SLO)$/sw_fldpage.obj \
        $(SLO)$/sw_fldref.obj \
        $(SLO)$/sw_fldtdlg.obj \
        $(SLO)$/sw_fldvar.obj \
        $(SLO)$/sw_javaedit.obj \
        $(SLO)$/sw_inpdlg.obj \
        $(SLO)$/sw_xfldui.obj

EXCEPTIONSFILES =  \
        $(SLO)$/sw_xfldui.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

