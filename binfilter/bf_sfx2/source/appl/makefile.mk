#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.3 $
#
#   last change: $Author: aw $ $Date: 2003-11-18 19:23:12 $
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

PRJ=..$/..$/..
BFPRJ=..$/..

PRJNAME=binfilter
TARGET=sfx2_appl

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk

# --- Settings -----------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk

IMGLST_SRS=$(SRS)$/sfx2_appl.srs
BMP_IN=$(BFPRJ)$/win/res
INC+= -I$(PRJ)$/inc$/bf_sfx2

# w.g. compilerbugs
.IF "$(GUI)"=="WNT"
CFLAGS+=-Od
.ENDIF

# --- Files --------------------------------------------------------

SRS1NAME=sfx2_appl
SRC1FILES =  \
        sfx2_app.src sfx2_sfx.src sfx2_image.src sfx2_newhelp.src

SRS2NAME=sfx2_sfx
SRC2FILES =  \
        sfx2_sfx.src

SLOFILES =  \
    $(SLO)$/sfx2_imagemgr.obj\
    $(SLO)$/sfx2_appuno.obj \
    $(SLO)$/sfx2_appmail.obj \
    $(SLO)$/sfx2_appmain.obj \
    $(SLO)$/sfx2_appopen.obj \
    $(SLO)$/sfx2_appinit.obj \
    $(SLO)$/sfx2_appmisc.obj \
    $(SLO)$/sfx2_appdemo.obj \
    $(SLO)$/sfx2_appreg.obj \
    $(SLO)$/sfx2_appcfg.obj \
    $(SLO)$/sfx2_appquit.obj \
    $(SLO)$/sfx2_appchild.obj \
    $(SLO)$/sfx2_appserv.obj \
    $(SLO)$/sfx2_appdata.obj \
    $(SLO)$/sfx2_app.obj \
    $(SLO)$/sfx2_appbas.obj \
    $(SLO)$/sfx2_appdde.obj \
    $(SLO)$/sfx2_workwin.obj \
    $(SLO)$/sfx2_sfxhelp.obj \
    $(SLO)$/sfx2_childwin.obj \
    $(SLO)$/sfx2_sfxdll.obj \
    $(SLO)$/sfx2_module.obj \
    $(SLO)$/sfx2_appsys.obj \
    $(SLO)$/sfx2_loadenv.obj \
    $(SLO)$/sfx2_dlgcont.obj \
    $(SLO)$/sfx2_namecont.obj \
    $(SLO)$/sfx2_scriptcont.obj \
    $(SLO)$/sfx2_newhelp.obj \
    $(SLO)$/sfx2_helpinterceptor.obj \
    $(SLO)$/sfx2_shutdownicon.obj \
    $(SLO)$/sfx2_shutdowniconw32.obj \
    $(SLO)$/sfx2_sfxpicklist.obj \
    $(SLO)$/sfx2_helpdispatch.obj \
    $(SLO)$/sfx2_imestatuswindow.obj \
    $(SLO)$/sfx2_accelinfo.obj

EXCEPTIONSFILES=\
    $(SLO)$/sfx2_imagemgr.obj		\
    $(SLO)$/sfx2_appopen.obj \
    $(SLO)$/sfx2_appmain.obj			\
    $(SLO)$/sfx2_appmisc.obj			\
    $(SLO)$/sfx2_frstinit.obj		\
    $(SLO)$/sfx2_appinit.obj			\
    $(SLO)$/sfx2_appcfg.obj			\
    $(SLO)$/sfx2_helpinterceptor.obj	\
    $(SLO)$/sfx2_newhelp.obj			\
    $(SLO)$/sfx2_sfxhelp.obj			\
    $(SLO)$/sfx2_shutdownicon.obj	\
    $(SLO)$/sfx2_shutdowniconw32.obj \
    $(SLO)$/sfx2_sfxpicklist.obj		\
    $(SLO)$/sfx2_helpdispatch.obj

.IF "$(GUI)" == "MAC"
SLOFILES +=\
        $(SLO)$/sfx2_appmac.obj
.ENDIF

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

