#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.3 $
#
#   last change: $Author: aw $ $Date: 2003-11-18 19:24:55 $
#
#   The Contents of this file are made available subject to the terms of
#   either of the following licenses
#
#          - GNU Lesser General Public License Version 2.1
#          - Sun Industry Standards Source License Version 1.1
#
#   Sun Microsystems Inc., October, 2000
#
#   GNU Lesser General Public License Version 2.1
#   =============================================
#   Copyright 2000 by Sun Microsystems, Inc.
#   901 San Antonio Road, Palo Alto, CA 94303, USA
#
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU Lesser General Public
#   License version 2.1, as published by the Free Software Foundation.
#
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with this library; if not, write to the Free Software
#   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#   MA  02111-1307  USA
#
#
#   Sun Industry Standards Source License Version 1.1
#   =================================================
#   The contents of this file are subject to the Sun Industry Standards
#   Source License Version 1.1 (the "License"); You may not use this file
#   except in compliance with the License. You may obtain a copy of the
#   License at http://www.openoffice.org/license.html.
#
#   Software provided under this License is provided on an "AS IS" basis,
#   WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
#   WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
#   MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
#   See the License for the specific provisions governing your rights and
#   obligations concerning the Software.
#
#   The Initial Developer of the Original Code is: Sun Microsystems, Inc.
#
#   Copyright: 2000 by Sun Microsystems, Inc.
#
#   All Rights Reserved.
#
#   Contributor(s): _______________________________________
#
#
#
#*************************************************************************

PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PRJNAME=binfilter
TARGET=sw_utlui

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
#IMGLST_SRS=$(SRS)$/utlui.srs
#BMP_IN=$(PRJ)$/win/imglst

INC+= -I$(PRJ)$/inc$/bf_sw

# --- Files --------------------------------------------------------

CXXFILES = \
        sw_bookctrl.cxx \
        sw_condedit.cxx \
        sw_content.cxx \
        sw_gloslst.cxx \
        sw_glbltree.cxx \
        sw_initui.cxx \
        sw_navipi.cxx \
        sw_navicfg.cxx \
        sw_numfmtlb.cxx \
        sw_prcntfld.cxx \
        sw_tmplctrl.cxx \
        sw_uitool.cxx \
        sw_uiitems.cxx \
        sw_attrdesc.cxx \
        sw_swstbctl.cxx \
        sw_shdwcrsr.cxx \
        sw_unotools.cxx \
        sw_zoomctrl.cxx

SRS1NAME=$(TARGET)
SRC1FILES =  \
        sw_initui.src \
        sw_gloslst.src \
        sw_navipi.src \
        sw_poolfmt.src \
        sw_attrdesc.src \
        sw_unotools.src \
        sw_utlui.src

SLOFILES =  \
        $(SLO)$/sw_bookctrl.obj \
        $(SLO)$/sw_condedit.obj \
        $(SLO)$/sw_content.obj \
        $(SLO)$/sw_gloslst.obj \
        $(SLO)$/sw_glbltree.obj \
        $(SLO)$/sw_initui.obj \
        $(SLO)$/sw_navipi.obj \
        $(SLO)$/sw_navicfg.obj \
        $(SLO)$/sw_numfmtlb.obj \
        $(SLO)$/sw_prcntfld.obj \
        $(SLO)$/sw_tmplctrl.obj \
        $(SLO)$/sw_uitool.obj \
        $(SLO)$/sw_uiitems.obj \
        $(SLO)$/sw_attrdesc.obj \
        $(SLO)$/sw_swstbctl.obj \
        $(SLO)$/sw_shdwcrsr.obj \
        $(SLO)$/sw_unotools.obj \
        $(SLO)$/sw_zoomctrl.obj

EXCEPTIONSFILES= \
        $(SLO)$/sw_unotools.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

