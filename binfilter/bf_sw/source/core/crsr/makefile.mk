#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.7 $
#
#   last change: $Author: hr $ $Date: 2007-01-02 17:41:58 $
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
TARGET=sw_crsr

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :	$(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :	settings.mk
.INCLUDE :	$(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw
.IF "$(mydebug)" != ""
CDEFS+=-Dmydebug
.ENDIF

# --- Files --------------------------------------------------------

CXXFILES = \
        sw_bookmrk.cxx \
        sw_callnk.cxx \
        sw_crbm.cxx \
        sw_crsrsh.cxx \
        sw_crstrvl1.cxx \
        sw_findattr.cxx \
        sw_findcoll.cxx \
        sw_findtxt.cxx \
        sw_pam.cxx \
        sw_paminit.cxx \
        sw_swcrsr.cxx \
        sw_trvlcol.cxx \
        sw_trvlfnfl.cxx \
        sw_trvlreg.cxx \
        sw_trvltbl.cxx \
        sw_unocrsr.cxx \
        sw_viscrs.cxx

.IF "$(GUI)"=="MAC"
CXXFILES += \
        sw_crsrsh1.cxx
.ENDIF
.IF "$(mydebug)" != ""
CXXFILES += \
        sw_pamio.cxx
.ENDIF

SLOFILES =	\
        $(SLO)$/sw_bookmrk.obj \
        $(SLO)$/sw_callnk.obj \
        $(SLO)$/sw_crbm.obj \
        $(SLO)$/sw_crsrsh.obj \
        $(SLO)$/sw_crstrvl1.obj \
        $(SLO)$/sw_findattr.obj \
        $(SLO)$/sw_findcoll.obj \
        $(SLO)$/sw_findtxt.obj \
        $(SLO)$/sw_pam.obj \
        $(SLO)$/sw_paminit.obj \
        $(SLO)$/sw_swcrsr.obj \
        $(SLO)$/sw_trvlcol.obj \
        $(SLO)$/sw_trvlfnfl.obj \
        $(SLO)$/sw_trvlreg.obj \
        $(SLO)$/sw_trvltbl.obj \
        $(SLO)$/sw_unocrsr.obj \
        $(SLO)$/sw_viscrs.obj

.IF "$(GUI)"=="MAC"
SLOFILES +=  \
        $(SLO)$/sw_crsrsh1.obj
.ENDIF
.IF "$(mydebug)" != ""
SLOFILES +=  \
        $(SLO)$/sw_pamio.obj
.ENDIF

# --- Tagets -------------------------------------------------------

.INCLUDE :	target.mk
