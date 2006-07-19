#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: kz $ $Date: 2006-07-19 13:31:55 $
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

PRJ=..$/..$/..
BFPRJ=..$/..

PRJNAME=binfilter
TARGET=sfx2_control

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
AUTOSEG=true


# --- Settings -----------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
INC+= -I$(PRJ)$/inc$/bf_sfx2

# w.g. compilerbugs
.IF "$(GUI)"=="WNT"
CFLAGS+=-Od
.ENDIF

# --- Files --------------------------------------------------------

CXXFILES = \
    sfx2_unoctitm.cxx \
    sfx2_macro.cxx \
    sfx2_request.cxx \
    sfx2_dispatch.cxx \
        sfx2_ctrlitem.cxx \
    sfx2_statcach.cxx \
    sfx2_msgpool.cxx \
    sfx2_shell.cxx \
    sfx2_objface.cxx \
    sfx2_msg.cxx \
    sfx2_bindings.cxx \
    sfx2_macrconf.cxx \
        sfx2_macro.cxx \
    sfx2_minfitem.cxx \
    sfx2_srchitem.cxx \
    $(PROJECTPCHSOURCE).cxx

SLOFILES = \
    $(SLO)$/sfx2_unoctitm.obj \
    $(SLO)$/sfx2_request.obj \
    $(SLO)$/sfx2_dispatch.obj \
       $(SLO)$/sfx2_msgpool.obj \
       $(SLO)$/sfx2_objface.obj \
    $(SLO)$/sfx2_ctrlitem.obj \
    $(SLO)$/sfx2_statcach.obj \
    $(SLO)$/sfx2_shell.obj \
    $(SLO)$/sfx2_msg.obj \
    $(SLO)$/sfx2_bindings.obj \
    $(SLO)$/sfx2_minfitem.obj \
    $(SLO)$/sfx2_srchitem.obj \
        $(SLO)$/sfx2_macro.obj \
    $(SLO)$/sfx2_macrconf.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

