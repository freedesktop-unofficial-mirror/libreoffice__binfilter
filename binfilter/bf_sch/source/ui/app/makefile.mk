#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: aw $ $Date: 2003-10-09 14:13:26 $
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

PROJECTPCH=sch
PROJECTPCHSOURCE=$(BFPRJ)$/util$/sch_sch
PRJNAME=binfilter
TARGET=sch_app

AUTOSEG=true

BMP_OUT=$(RES)
BMP_IN =$(BFPRJ)$/res

# --- Settings -----------------------------------------------------
.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_sch
# --- Files --------------------------------------------------------

#IMGLST_SRS=$(SRS)$/app.srs

SRS1NAME=$(TARGET)
SRC1FILES =	sch_app.src		\
        sch_strings.src		\
        sch_res_bmp.src		\
        sch_res_hc_bmp.src

DEPOBJFILES =	\
        $(SLO)$/sch_schlib.obj

SLOFILES =	\
        $(SLO)$/sch_schdll.obj	\
        $(SLO)$/sch_schmod.obj      \
        $(SLO)$/sch_schresid.obj	\
        $(SLO)$/sch_typemap.obj	\
        $(SLO)$/sch_schopt.obj	\
        $(SLO)$/sch_appopt.obj \
        $(SLO)$/sch_globopt.obj

LIB2TARGET =	$(SLB)$/bf_ysch.lib
LIB2ARCHIV =	$(LB)$/libbf_ysch.a
LIB2OBJFILES  =	$(SLO)$/sch_schlib.obj


.IF "$(GUI)" == "WNT"
NOOPTFILES=\
    $(SLO)$/sch_schdll.obj
.ENDIF



# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

$(INCCOM)$/schlib.hxx: makefile.mk
.IF "$(GUI)"=="UNX"
    $(RM) $@
    +echo \#define DLL_NAME \"libbf_sch$(UPD)$(DLLPOSTFIX)$(DLLPOST)\" >$@
.ELSE
.IF "$(USE_SHELL)"!="4nt"
    +echo \#define DLL_NAME \"bf_sch$(UPD)$(DLLPOSTFIX)$(DLLPOST)\" >$@
.ELSE          # "$(USE_SHELL)"!="4nt"
    +echo #define DLL_NAME "bf_sch$(UPD)$(DLLPOSTFIX)$(DLLPOST)" >$@
.ENDIF          # "$(USE_SHELL)"!="4nt"
.ENDIF

$(SRS)$/sch_app.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc

$(SLO)$/sch_schlib.obj : $(INCCOM)$/schlib.hxx


