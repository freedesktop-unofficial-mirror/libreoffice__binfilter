#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.8 $
#
#   last change: $Author: vg $ $Date: 2007-02-06 12:40:26 $
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

PROJECTPCH=sch
PROJECTPCHSOURCE=$(BFPRJ)$/util$/sch_sch

PRJNAME=binfilter
TARGET=sch_core

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------
.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_sch
# --- Files --------------------------------------------------------

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
    $(SLO)$/sch_schiocmp.obj	\
    $(SLO)$/sch_itempool.obj	\
    $(SLO)$/sch_datalog.obj		\
    $(SLO)$/sch_memchrt.obj 	\
    $(SLO)$/sch_chdescr.obj 	\
    $(SLO)$/sch_chaxis.obj		\
    $(SLO)$/sch_calculat.obj	\
    $(SLO)$/sch_axisobj.obj		\
    $(SLO)$/sch_SchAddInCollection.obj	\
    $(SLO)$/sch_ReBuildHint.obj

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

