#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.10 $
#
#   last change: $Author: obo $ $Date: 2007-07-17 10:32:49 $
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
TARGET=sfx2_appl

NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk

INC+= -I$(PRJ)$/inc$/bf_sfx2

# w.g. compilerbugs
.IF "$(GUI)"=="WNT"
.IF "$(COM)"!="GCC"
CFLAGS+=-Od
.ENDIF
.ENDIF

# --- Files --------------------------------------------------------

SLOFILES =  \
    $(SLO)$/sfx2_appuno.obj \
    $(SLO)$/sfx2_appmain.obj \
    $(SLO)$/sfx2_appopen.obj \
    $(SLO)$/sfx2_appinit.obj \
    $(SLO)$/sfx2_appmisc.obj \
    $(SLO)$/sfx2_appcfg.obj \
    $(SLO)$/sfx2_appquit.obj \
    $(SLO)$/sfx2_appdata.obj \
    $(SLO)$/sfx2_app.obj \
    $(SLO)$/sfx2_appbas.obj \
    $(SLO)$/sfx2_appdde.obj \
    $(SLO)$/sfx2_sfxdll.obj \
    $(SLO)$/sfx2_module.obj \
    $(SLO)$/sfx2_dlgcont.obj \
    $(SLO)$/sfx2_namecont.obj \
    $(SLO)$/sfx2_scriptcont.obj \
    $(SLO)$/sfx2_imestatuswindow.obj 

EXCEPTIONSFILES=\
    $(SLO)$/sfx2_appopen.obj \
    $(SLO)$/sfx2_appmain.obj			\
    $(SLO)$/sfx2_appmisc.obj			\
    $(SLO)$/sfx2_appinit.obj			\
    $(SLO)$/sfx2_appcfg.obj			

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

