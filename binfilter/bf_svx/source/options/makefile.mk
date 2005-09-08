#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.4 $
#
#   last change: $Author: rt $ $Date: 2005-09-08 06:28:37 $
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
PRJ=..$/..$/..
BFPRJ=..$/..

PROJECTPCH4DLL=TRUE
PROJECTPCH=svxpch
PROJECTPCHSOURCE=$(BFPRJ)$/util\svx_svxpch

PRJNAME=binfilter
TARGET=svx_options

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

CFLAGS+=-DDG_DLL

# --- Files --------------------------------------------------------

SRS1NAME=$(TARGET)
SRC1FILES=\
    svx_optasian.src		\
    svx_optcolor.src		\
    svx_optjsearch.src		\
    svx_optgenrl.src		\
    svx_optdict.src		\
    svx_optaccessibility.src	\
    svx_optsave.src		\
    svx_optpath.src		\
    svx_optlingu.src		\
    svx_optgrid.src		\
    svx_optinet2.src		\
    svx_multipat.src		\
    svx_optextbr.src		\
    svx_optctl.src

#EXCEPTIONSFILES=\
#	$(SLO)$/svx_multifil.obj		\
#	$(SLO)$/svx_optasian.obj		\
#	$(SLO)$/svx_optdict.obj		\
#	$(SLO)$/svx_optlingu.obj		\
#	$(SLO)$/svx_optaccessibility.obj	\
#	$(SLO)$/svx_optsave.obj		\
#	$(SLO)$/svx_optpath.obj

SLOFILES=\
        $(SLO)$/svx_asiancfg.obj	\
        $(SLO)$/svx_adritem.obj	\
        $(SLO)$/svx_optgrid.obj


SVXLIGHTOBJFILES=\
    $(OBJ)$/svx_adritem.obj

.IF "$(GUI)"=="WIN"
SLOFILES+=\
    $(SLO)$/svx_optdll.obj
.ENDIF

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

