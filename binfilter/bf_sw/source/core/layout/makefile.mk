#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.6 $
#
#   last change: $Author: rt $ $Date: 2006-07-25 08:26:14 $
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

PRJNAME=binfilter
TARGET=sw_layout

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw

.IF "$(mydebug)" != ""
CDEFS+=-Dmydebug
.ENDIF

.IF "$(madebug)" != ""
CDEFS+=-DDEBUG
.ENDIF

#		"Querdarstellung des Dokumentes"
#		CDEFS=$(CDEFS) -DQUER

# 		CDEFS=$(CDEFS) -DPAGE

.IF "$(GUI)$(COM)" == "WINMSC"
LIBFLAGS=/NOI /NOE /PAGE:512
.ENDIF


# --- Files --------------------------------------------------------

CXXFILES = \
        sw_atrfrm.cxx \
        sw_calcmove.cxx \
        sw_colfrm.cxx \
        sw_findfrm.cxx \
        sw_flowfrm.cxx \
        sw_fly.cxx \
        sw_flycnt.cxx \
        sw_flyincnt.cxx \
        sw_flylay.cxx \
        sw_flypos.cxx \
        sw_frmtool.cxx \
        sw_ftnfrm.cxx \
        sw_hffrm.cxx \
        sw_layact.cxx \
                sw_laycache.cxx \
        sw_layouter.cxx \
        sw_newfrm.cxx \
        sw_pagechg.cxx \
        sw_pagedesc.cxx \
        sw_pageiter.cxx \
        sw_paintfrm.cxx \
        sw_sectfrm.cxx \
        sw_ssfrm.cxx \
        sw_tabfrm.cxx \
        sw_trvlfrm.cxx \
        sw_unusedf.cxx \
        sw_wsfrm.cxx



SLOFILES =  \
        $(SLO)$/sw_atrfrm.obj \
        $(SLO)$/sw_calcmove.obj \
        $(SLO)$/sw_colfrm.obj \
        $(SLO)$/sw_findfrm.obj \
        $(SLO)$/sw_flowfrm.obj \
        $(SLO)$/sw_fly.obj \
        $(SLO)$/sw_flycnt.obj \
        $(SLO)$/sw_flyincnt.obj \
        $(SLO)$/sw_flylay.obj \
        $(SLO)$/sw_flypos.obj \
        $(SLO)$/sw_frmtool.obj \
        $(SLO)$/sw_ftnfrm.obj \
        $(SLO)$/sw_hffrm.obj \
        $(SLO)$/sw_layact.obj \
                $(SLO)$/sw_laycache.obj \
        $(SLO)$/sw_layouter.obj \
        $(SLO)$/sw_newfrm.obj \
        $(SLO)$/sw_pagechg.obj \
        $(SLO)$/sw_pagedesc.obj \
        $(SLO)$/sw_pageiter.obj \
        $(SLO)$/sw_paintfrm.obj \
        $(SLO)$/sw_sectfrm.obj \
        $(SLO)$/sw_ssfrm.obj \
        $(SLO)$/sw_tabfrm.obj \
        $(SLO)$/sw_trvlfrm.obj \
        $(SLO)$/sw_unusedf.obj \
        $(SLO)$/sw_wsfrm.obj

.IF "$(product)"==""
.IF "$(cap)"==""
CXXFILES += \
        sw_dbg_lay.cxx
SLOFILES +=  \
        $(SLO)$/sw_dbg_lay.obj
.ENDIF
.ENDIF

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

