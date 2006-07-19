#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: kz $ $Date: 2006-07-19 14:59:53 $
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
TARGET=sw_config

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
        sw_barcfg.cxx \
        sw_caption.cxx \
        sw_cfgitems.cxx \
        sw_dbconfig.cxx \
        sw_fontcfg.cxx \
        sw_modcfg.cxx \
        sw_optload.cxx \
        sw_optpage.cxx \
        sw_prtopt.cxx \
        sw_uinums.cxx \
        sw_usrpref.cxx \
        sw_viewopt.cxx \
        sw_swlinguconfig.cxx

SRS1NAME=$(TARGET)
SRC1FILES =	\
        sw_optdlg.src \
        sw_optload.src \
        sw_redlopt.src

SLOFILES =	\
        $(SLO)$/sw_barcfg.obj \
        $(SLO)$/sw_caption.obj \
        $(SLO)$/sw_cfgitems.obj \
        $(SLO)$/sw_dbconfig.obj \
        $(SLO)$/sw_fontcfg.obj \
        $(SLO)$/sw_modcfg.obj \
        $(SLO)$/sw_optload.obj \
        $(SLO)$/sw_optpage.obj \
        $(SLO)$/sw_prtopt.obj \
        $(SLO)$/sw_uinums.obj \
        $(SLO)$/sw_usrpref.obj \
        $(SLO)$/sw_viewopt.obj \
        $(SLO)$/sw_swlinguconfig.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

