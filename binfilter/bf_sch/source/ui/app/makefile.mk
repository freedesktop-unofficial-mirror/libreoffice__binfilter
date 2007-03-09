#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.9 $
#
#   last change: $Author: obo $ $Date: 2007-03-09 14:30:34 $
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

PROJECTPCH=sch
PROJECTPCHSOURCE=$(BFPRJ)$/util$/sch_sch

PRJNAME=binfilter
TARGET=sch_app

NO_HIDS=TRUE

BMP_OUT=$(RES)
BMP_IN =$(BFPRJ)$/res

# --- Settings -----------------------------------------------------
.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_sch
# --- Files --------------------------------------------------------

#IMGLST_SRS=$(SRS)$/app.srs

SRS1NAME=$(TARGET)
SRC1FILES =	sch_app.src		\
        sch_strings.src

DEPOBJFILES =	\
        $(SLO)$/sch_schlib.obj

SLOFILES =	\
        $(SLO)$/sch_schdll.obj	\
        $(SLO)$/sch_schmod.obj      \
        $(SLO)$/sch_schresid.obj	\
        $(SLO)$/sch_typemap.obj	\
        $(SLO)$/sch_schopt.obj	\
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
    echo \#define DLL_NAME \"libbf_sch$(UPD)$(DLLPOSTFIX)$(DLLPOST)\" >$@
.ELSE
    echo $(EMQ)#define DLL_NAME $(EMQ)"bf_sch$(UPD)$(DLLPOSTFIX)$(DLLPOST)$(EMQ)" >$@
.ENDIF

$(SRS)$/sch_app.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc

$(SLO)$/sch_schlib.obj : $(INCCOM)$/schlib.hxx


