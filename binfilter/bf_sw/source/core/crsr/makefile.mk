#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.3 $
#
#   last change: $Author: aw $ $Date: 2003-11-18 19:24:22 $
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
TARGET=sw_crsr

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

AUTOSEG=true

# --- Settings -----------------------------------------------------

#.INCLUDE :	$(PRJ)$/inc$/swpre.mk
.INCLUDE :	$(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :	settings.mk
#.INCLUDE :	$(PRJ)$/inc$/sw.mk
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
        sw_crstrvl.cxx \
        sw_crstrvl1.cxx \
        sw_findattr.cxx \
        sw_findcoll.cxx \
        sw_findfmt.cxx \
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
        $(SLO)$/sw_crstrvl.obj \
        $(SLO)$/sw_crstrvl1.obj \
        $(SLO)$/sw_findattr.obj \
        $(SLO)$/sw_findcoll.obj \
        $(SLO)$/sw_findfmt.obj \
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
