#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: kz $ $Date: 2006-07-19 15:00:58 $
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
TARGET=sw_envelp

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
        sw_envfmt.cxx \
    sw_envimg.cxx \
        sw_envlop1.cxx \
        sw_envprt.cxx \
        sw_labelcfg.cxx \
        sw_label1.cxx \
        sw_labelexp.cxx \
        sw_labfmt.cxx \
        sw_labprt.cxx \
        sw_labimg.cxx \
        sw_mailmrge.cxx \
        sw_syncbtn.cxx

SRS1NAME=$(TARGET)
SRC1FILES =\
        sw_envelp.src \
        sw_envfmt.src \
        sw_envlop.src \
        sw_envprt.src \
        sw_label.src  \
        sw_labfmt.src \
        sw_labprt.src \
        sw_mailmrge.src

SLOFILES =  \
        $(SLO)$/sw_envfmt.obj  \
        $(SLO)$/sw_envimg.obj  \
        $(SLO)$/sw_envlop1.obj \
        $(SLO)$/sw_envprt.obj  \
        $(SLO)$/sw_labelcfg.obj  \
        $(SLO)$/sw_label1.obj  \
        $(SLO)$/sw_labelexp.obj \
        $(SLO)$/sw_labfmt.obj  \
        $(SLO)$/sw_labprt.obj  \
        $(SLO)$/sw_labimg.obj  \
        $(SLO)$/sw_mailmrge.obj \
        $(SLO)$/sw_syncbtn.obj

EXCEPTIONSFILES= \
        $(SLO)$/sw_labelexp.obj      \
        $(SLO)$/sw_mailmrge.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

