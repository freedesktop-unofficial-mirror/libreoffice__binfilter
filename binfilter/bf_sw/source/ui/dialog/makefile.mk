#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.4 $
#
#   last change: $Author: rt $ $Date: 2005-09-09 04:33:24 $
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
TARGET=sw_dialog

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

AUTOSEG=true

#IMGLST_SRS=$(SRS)$/dialog.srs
#BMP_IN=$(PRJ)$/win/imglst

# future: DEMO\dialog.srs

# --- Settings -----------------------------------------------------

#.INCLUDE :  $(PRJ)$/inc$/swpre.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
#.INCLUDE :  $(PRJ)$/inc$/sw.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk

INC+= -I$(PRJ)$/inc$/bf_sw
# --- Files --------------------------------------------------------

CXXFILES = \
        sw_addrdlg.cxx \
        sw_abstract.cxx \
        sw_ascfldlg.cxx \
        sw_docstdlg.cxx \
        sw_macassgn.cxx \
        sw_regionsw.cxx

SRS1NAME=$(TARGET)
SRC1FILES =  \
        sw_abstract.src \
        sw_ascfldlg.src \
        sw_dialog.src \
        sw_docstdlg.src \
        sw_regionsw.src

SLOFILES =  \
        $(SLO)$/sw_abstract.obj \
        $(SLO)$/sw_addrdlg.obj \
        $(SLO)$/sw_ascfldlg.obj \
        $(SLO)$/sw_docstdlg.obj \
        $(SLO)$/sw_macassgn.obj \
        $(SLO)$/sw_regionsw.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

