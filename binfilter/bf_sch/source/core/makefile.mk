#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.3 $
#
#   last change: $Author: aw $ $Date: 2003-11-18 19:22:54 $
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

PROJECTPCH=sch
PROJECTPCHSOURCE=$(BFPRJ)$/util$/sch_sch

PRJNAME=binfilter
TARGET=sch_core

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

AUTOSEG=true

# --- Settings -----------------------------------------------------
.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
INC+= -I$(PRJ)$/inc$/bf_sch
# --- Files --------------------------------------------------------

CXXFILES = $(BFPRJ)$/util$/sch_sch.cxx	\
    sch_chtscene.cxx	sch_stlsheet.cxx 	\
    sch_globfunc.cxx	sch_stlpool.cxx		\
    sch_chtmodel.cxx	sch_chtmode1.cxx	\
    sch_chtmode2.cxx	sch_chtmode3.cxx	\
    sch_chtmode4.cxx	sch_chtmode5.cxx	\
    sch_chtmode6.cxx	sch_chtmode7.cxx	\
    sch_chtmode8.cxx	sch_charttyp.cxx	\
    sch_chtmod2a.cxx	sch_chtmod3d.cxx	\
    sch_chtm3d2.cxx		sch_chartdoc.cxx 	\
    sch_schgroup.cxx	sch_objfac.cxx		\
    sch_axisid.cxx		sch_objid.cxx		\
    sch_objadj.cxx		sch_datarow.cxx		\
    sch_datapoin.cxx	sch_lightfac.cxx	\
    sch_schiocmp.cxx	sch_axisobj.cxx		\
    sch_itempool.cxx	sch_datalog.cxx		\
    sch_memchrt.cxx		\
    sch_chdescr.cxx 	sch_chaxis.cxx		\
    sch_chtmode9.cxx	sch_chartbar.cxx	\
    sch_calculat.cxx	\
    sch_SchAddInCollection.cxx			\
    sch_SchRangeChecker.cxx				\
    sch_SchPersistentObjectPointer.cxx  \
    sch_ReBuildHint.cxx \
    sch_PropertyChangeHint.cxx \
    sch_modeldata.cxx

SRS1NAME=$(TARGET)
SRC1FILES = sch_glob.src

SLOFILES =  \
    $(SLO)$/sch_chtscene.obj	\
    $(SLO)$/sch_globfunc.obj	\
    $(SLO)$/sch_chtmodel.obj	\
    $(SLO)$/sch_chtmode1.obj	\
    $(SLO)$/sch_chtmode2.obj	\
    $(SLO)$/sch_chtmode3.obj	\
    $(SLO)$/sch_chtmode4.obj	\
    $(SLO)$/sch_chtmode5.obj	\
    $(SLO)$/sch_chtmode6.obj	\
    $(SLO)$/sch_chtmode7.obj	\
    $(SLO)$/sch_chtmode8.obj	\
    $(SLO)$/sch_charttyp.obj	\
    $(SLO)$/sch_chtmode9.obj	\
    $(SLO)$/sch_chartbar.obj	\
    $(SLO)$/sch_chtmod2a.obj	\
    $(SLO)$/sch_chtmod3d.obj	\
    $(SLO)$/sch_chtm3d2.obj		\
    $(SLO)$/sch_chartdoc.obj	\
    $(SLO)$/sch_stlsheet.obj	\
    $(SLO)$/sch_schgroup.obj	\
    $(SLO)$/sch_stlpool.obj		\
    $(SLO)$/sch_objfac.obj		\
    $(SLO)$/sch_axisid.obj		\
    $(SLO)$/sch_objid.obj		\
    $(SLO)$/sch_objadj.obj		\
    $(SLO)$/sch_datarow.obj		\
    $(SLO)$/sch_datapoin.obj	\
    $(SLO)$/sch_lightfac.obj	\
    $(SLO)$/sch_schiocmp.obj	\
    $(SLO)$/sch_itempool.obj	\
    $(SLO)$/sch_datalog.obj		\
    $(SLO)$/sch_memchrt.obj 	\
    $(SLO)$/sch_chdescr.obj 	\
    $(SLO)$/sch_chaxis.obj		\
    $(SLO)$/sch_calculat.obj	\
    $(SLO)$/sch_axisobj.obj		\
    $(SLO)$/sch_SchAddInCollection.obj	\
    $(SLO)$/sch_SchRangeChecker.obj		\
    $(SLO)$/sch_SchPersistentObjectPointer.obj \
    $(SLO)$/sch_ReBuildHint.obj \
    $(SLO)$/sch_PropertyChangeHint.obj \
    $(SLO)$/sch_modeldata.obj

.IF "$(GUI)" == "WIN"
NOOPTFILES=\
    $(OBJ)$/sch_chtmode5.obj
.ENDIF

EXCEPTIONSFILES= \
    $(SLO)$/sch_chtmode4.obj   \
    $(SLO)$/sch_chtmodel.obj   \
    $(SLO)$/sch_SchAddInCollection.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

