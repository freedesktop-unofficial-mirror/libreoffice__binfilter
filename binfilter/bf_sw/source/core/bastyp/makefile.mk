#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: kz $ $Date: 2006-07-19 13:41:02 $
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
TARGET=sw_bastyp

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
        sw_bparr.cxx \
        sw_breakit.cxx \
        sw_calc.cxx \
                sw_checkit.cxx \
        sw_index.cxx \
        sw_init.cxx \
        sw_ring.cxx \
        sw_swcache.cxx \
        sw_swrect.cxx \
        sw_swregion.cxx \
        sw_swtypes.cxx \
        sw_tabcol.cxx

SLOFILES =  \
        $(SLO)$/sw_bparr.obj \
        $(SLO)$/sw_breakit.obj \
        $(SLO)$/sw_calc.obj \
                $(SLO)$/sw_checkit.obj \
        $(SLO)$/sw_index.obj \
        $(SLO)$/sw_init.obj \
        $(SLO)$/sw_ring.obj \
        $(SLO)$/sw_swcache.obj \
        $(SLO)$/sw_swrect.obj \
        $(SLO)$/sw_swregion.obj \
        $(SLO)$/sw_swtypes.obj \
        $(SLO)$/sw_tabcol.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

