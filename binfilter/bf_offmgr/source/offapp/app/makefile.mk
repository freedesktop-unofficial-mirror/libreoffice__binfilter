#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.1.1.1 $
#
#   last change: $Author: hjs $ $Date: 2003-10-01 12:17:33 $
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

PRJNAME=bf_offmgr
TARGET=offmgr_app

PROJECTPCH=offmgr_ofapch
PDBTARGET=offmgr_ofapch
PROJECTPCHSOURCE=$(BFPRJ)$/util\offmgr_ofapch

# --- Settings ------------------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_offmgr


.IF "$(prjpch)" != ""
CDEFS=$(CDEFS) -DPRECOMPILED
.ENDIF

.IF "$(GUI)"=="UNX"
    CDEFS+=-DDLL_NAME=libbf_ofa$(UPD)$(DLLPOSTFIX)$(DLLPOST)
.ELSE
    CDEFS+=-DDLL_NAME=bf_ofa$(UPD)$(DLLPOSTFIX)$(DLLPOST)
.ENDIF

.INCLUDE :  $(UPD)minor.mk
RSCUPDVER=$(RSCREVISION)(SV$(UPD)$(UPDMINOR))

#IMGLST_SRS=$(SRS)$/offmgr_app.srs

# --- Allgemein -----------------------------------------------------------

CINTERNAME=bf_ofa

SRS1NAME= offmgr_app
SRC1FILES=	\
    offmgr_app.src

EXCEPTIONSFILES=	\
    $(SLO)$/offmgr_sdbcdriverenum.obj	\
    $(SLO)$/offmgr_optuno.obj	\
    $(SLO)$/offmgr_apearcfg.obj	\
    $(SLO)$/offmgr_app.obj		\
    $(SLO)$/offmgr_appctor.obj     \
    $(SLO)$/offmgr_appimp.obj	\
    $(SLO)$/offmgr_appstat.obj	\
    $(SLO)$/offmgr_osplcfg.obj	\
    $(SLO)$/offmgr_app2.obj	\
    $(SLO)$/offmgr_app3.obj	\
    $(SLO)$/offmgr_connpoolconfig.obj

SLOFILES=\
    $(SLO)$/offmgr_sdbcdriverenum.obj     \
    $(SLO)$/offmgr_connpoolconfig.obj     \
    $(SLO)$/offmgr_connpoolsettings.obj     \
    $(SLO)$/offmgr_appctor.obj     \
    $(SLO)$/offmgr_optuno.obj	\
    $(SLO)$/offmgr_apearcfg.obj	\
    $(SLO)$/offmgr_app.obj		\
    $(SLO)$/offmgr_app2.obj	\
    $(SLO)$/offmgr_appimp.obj	\
    $(SLO)$/offmgr_appstat.obj	\
    $(SLO)$/offmgr_fltrcfg.obj	\
    $(SLO)$/offmgr_htmlcfg.obj	\
    $(SLO)$/offmgr_ofaaccfg.obj	\
    $(SLO)$/offmgr_ofaitem.obj	\
    $(SLO)$/offmgr_dbcoll.obj	\
    $(SLO)$/offmgr_osplcfg.obj	\
    $(SLO)$/offmgr_resid.obj	\
    $(SLO)$/offmgr_app3.obj	\
    $(SLO)$/offmgr_appbas.obj \
    $(SLO)$/offmgr_fontsubstconfig.obj

.INCLUDE :  target.mk

$(SRS)$/offmgr_app.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc

