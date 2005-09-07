#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.4 $
#
#   last change: $Author: rt $ $Date: 2005-09-07 19:05:26 $
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
PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PRJNAME=binfilter
TARGET=sc_docshell

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

PROJECTPCH4DLL=TRUE
PROJECTPCH=ui_pch
PDBTARGET=ui_pch
PROJECTPCHSOURCE=..\pch\sc_ui_pch

AUTOSEG=true

# --- Settings -----------------------------------------------------

.INCLUDE :  scpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sc.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sc
# --- Files --------------------------------------------------------

CXXFILES = \
        sc_docsh.cxx	\
        sc_docsh2.cxx	\
        sc_docsh3.cxx	\
        sc_docsh4.cxx 	\
        sc_docsh5.cxx	\
        sc_docsh6.cxx 	\
        sc_docsh7.cxx 	\
        sc_docsh8.cxx 	\
        sc_tablink.cxx 	\
        sc_arealink.cxx 	\
        sc_dbdocfun.cxx 	\
        sc_dbdocimp.cxx 	\
        sc_impex.cxx	\
        sc_docfunc.cxx	\
        sc_olinefun.cxx	\
        sc_servobj.cxx	\
        sc_tpstat.cxx	\
        sc_autostyl.cxx	\
        sc_pagedata.cxx \
        sc_hiranges.cxx \
        sc_pntlock.cxx \
        sc_sizedev.cxx \
        sc_editable.cxx


SLOFILES =  \
        $(SLO)$/sc_docsh.obj	\
        $(SLO)$/sc_docsh2.obj	\
        $(SLO)$/sc_docsh3.obj	\
        $(SLO)$/sc_docsh4.obj   	\
        $(SLO)$/sc_docsh5.obj   	\
        $(SLO)$/sc_docsh6.obj   	\
        $(SLO)$/sc_docsh7.obj   	\
        $(SLO)$/sc_docsh8.obj   	\
        $(SLO)$/sc_tablink.obj   	\
        $(SLO)$/sc_arealink.obj   	\
        $(SLO)$/sc_dbdocfun.obj 	\
        $(SLO)$/sc_dbdocimp.obj 	\
        $(SLO)$/sc_impex.obj	\
        $(SLO)$/sc_docfunc.obj	\
        $(SLO)$/sc_olinefun.obj	\
        $(SLO)$/sc_servobj.obj	\
        $(SLO)$/sc_tpstat.obj	\
        $(SLO)$/sc_autostyl.obj	\
        $(SLO)$/sc_pagedata.obj \
        $(SLO)$/sc_hiranges.obj \
        $(SLO)$/sc_pntlock.obj \
        $(SLO)$/sc_sizedev.obj \
        $(SLO)$/sc_editable.obj


EXCEPTIONSFILES= \
        $(SLO)$/sc_docsh8.obj \
        $(SLO)$/sc_dbdocimp.obj


SRS1NAME=$(TARGET)
SRC1FILES =  sc_tpstat.src

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

