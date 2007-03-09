#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.9 $
#
#   last change: $Author: obo $ $Date: 2007-03-09 14:25:39 $
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
TARGET=sc_view

NO_HIDS=TRUE

PROJECTPCH4DLL=TRUE
PROJECTPCH=ui_pch
PDBTARGET=ui_pch
PROJECTPCHSOURCE=..\pch\sc_ui_pch

# --- Settings -----------------------------------------------------

.INCLUDE :  scpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sc.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sc

SLOFILES =  \
        $(SLO)$/sc_tabview.obj \
        $(SLO)$/sc_tabview2.obj \
        $(SLO)$/sc_tabview3.obj \
        $(SLO)$/sc_tabview4.obj \
        $(SLO)$/sc_tabview5.obj \
        $(SLO)$/sc_viewfunc.obj \
        $(SLO)$/sc_viewfun2.obj \
        $(SLO)$/sc_dbfunc.obj \
        $(SLO)$/sc_dbfunc2.obj \
        $(SLO)$/sc_dbfunc3.obj \
        $(SLO)$/sc_tabvwsh.obj \
        $(SLO)$/sc_tabvwsh2.obj \
        $(SLO)$/sc_tabvwsh4.obj \
        $(SLO)$/sc_tabvwsh5.obj \
        $(SLO)$/sc_tabvwsh9.obj \
        $(SLO)$/sc_tabvwsha.obj \
        $(SLO)$/sc_tabvwshf.obj \
        $(SLO)$/sc_tabvwshh.obj \
        $(SLO)$/sc_printfun.obj \
        $(SLO)$/sc_pfuncache.obj \
        $(SLO)$/sc_prevwsh.obj \
        $(SLO)$/sc_editsh.obj \
        $(SLO)$/sc_pivotsh.obj \
        $(SLO)$/sc_auditsh.obj \
        $(SLO)$/sc_gridwin.obj \
        $(SLO)$/sc_gridwin3.obj \
        $(SLO)$/sc_gridwin4.obj \
        $(SLO)$/sc_gridwin5.obj \
        $(SLO)$/sc_drawview.obj \
        $(SLO)$/sc_drawvie2.obj \
        $(SLO)$/sc_drawvie3.obj \
        $(SLO)$/sc_drawutil.obj \
        $(SLO)$/sc_output.obj \
        $(SLO)$/sc_output2.obj \
        $(SLO)$/sc_output3.obj \
        $(SLO)$/sc_gridmerg.obj \
        $(SLO)$/sc_invmerge.obj \
        $(SLO)$/sc_select.obj \
        $(SLO)$/sc_olinewin.obj \
        $(SLO)$/sc_tabcont.obj \
        $(SLO)$/sc_tabsplit.obj \
        $(SLO)$/sc_viewdata.obj \
        $(SLO)$/sc_viewutil.obj \
        $(SLO)$/sc_hdrcont.obj \
        $(SLO)$/sc_colrowba.obj \
        $(SLO)$/sc_reffact.obj \
        $(SLO)$/sc_cellsh.obj \
        $(SLO)$/sc_cellsh2.obj\
        $(SLO)$/sc_formatsh.obj\
        $(SLO)$/sc_pgbrksh.obj

EXCEPTIONSFILES=\
        $(SLO)$/sc_viewdata.obj

NOOPTFILES=\
    $(SLO)$/sc_drawview.obj	\
    $(SLO)$/sc_dbfunc2.obj     \
    $(SLO)$/sc_tabvwsh2.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

