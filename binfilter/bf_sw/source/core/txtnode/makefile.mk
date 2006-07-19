#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.6 $
#
#   last change: $Author: kz $ $Date: 2006-07-19 14:54:29 $
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
TARGET=sw_txtnode

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
INCEXT=s:$/solar$/inc$/hm

.IF "$(mydebug)" != ""
CDEFS+=-Dmydebug
.ENDIF

.IF "$(GUI)$(COM)" == "WINMSC"
LIBFLAGS=/NOI /NOE /PAGE:512
.ENDIF

# --- Files --------------------------------------------------------

CXXFILES = \
        sw_atrfld.cxx \
        sw_atrflyin.cxx \
        sw_atrftn.cxx \
        sw_atrref.cxx \
        sw_atrtox.cxx \
        sw_chrfmt.cxx \
        sw_fmtatr1.cxx \
        sw_fmtatr2.cxx \
        sw_fntcap.cxx \
        sw_fntcache.cxx \
        sw_swfntcch.cxx \
        sw_ndhints.cxx \
        sw_ndtxt.cxx \
        sw_swfont.cxx \
        sw_thints.cxx \
        sw_txatbase.cxx \
        sw_txatritr.cxx \
        sw_txtatr2.cxx \
        sw_txtedt.cxx



SLOFILES =  \
        $(SLO)$/sw_atrfld.obj \
        $(SLO)$/sw_atrflyin.obj \
        $(SLO)$/sw_atrftn.obj \
        $(SLO)$/sw_atrref.obj \
        $(SLO)$/sw_atrtox.obj \
        $(SLO)$/sw_chrfmt.obj \
        $(SLO)$/sw_fmtatr1.obj \
        $(SLO)$/sw_fmtatr2.obj \
        $(SLO)$/sw_fntcap.obj \
        $(SLO)$/sw_fntcache.obj \
        $(SLO)$/sw_swfntcch.obj \
        $(SLO)$/sw_ndhints.obj \
        $(SLO)$/sw_ndtxt.obj \
        $(SLO)$/sw_swfont.obj \
        $(SLO)$/sw_thints.obj \
        $(SLO)$/sw_txatbase.obj \
        $(SLO)$/sw_txatritr.obj \
        $(SLO)$/sw_txtatr2.obj \
        $(SLO)$/sw_txtedt.obj

.IF "$(dbutil)" != ""
OFILES+=$(SLO)$/sw_dbchratr.$(QBJX)
.ENDIF

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

