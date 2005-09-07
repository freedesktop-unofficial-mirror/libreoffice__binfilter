#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.4 $
#
#   last change: $Author: rt $ $Date: 2005-09-07 18:53:52 $
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
TARGET=sc_dbgui

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

SLOFILES =	\
    $(SLO)$/sc_sortdlg.obj		\
    $(SLO)$/sc_tpsort.obj		\
    $(SLO)$/sc_filtdlg.obj		\
    $(SLO)$/sc_sfiltdlg.obj	\
    $(SLO)$/sc_foptmgr.obj		\
    $(SLO)$/sc_pfiltdlg.obj	\
    $(SLO)$/sc_dbnamdlg.obj	\
    $(SLO)$/sc_expftext.obj	\
    $(SLO)$/sc_subtdlg.obj		\
    $(SLO)$/sc_tpsubt.obj		\
    $(SLO)$/sc_fieldwnd.obj	\
    $(SLO)$/sc_pvlaydlg.obj	\
    $(SLO)$/sc_pvfundlg.obj	\
    $(SLO)$/sc_dapitype.obj	\
    $(SLO)$/sc_dapidata.obj	\
    $(SLO)$/sc_consdlg.obj		\
    $(SLO)$/sc_scendlg.obj		\
    $(SLO)$/sc_imoptdlg.obj	\
    $(SLO)$/sc_validate.obj	\
    $(SLO)$/sc_csvsplits.obj	\
    $(SLO)$/sc_csvcontrol.obj	\
    $(SLO)$/sc_csvruler.obj	\
    $(SLO)$/sc_csvgrid.obj		\
    $(SLO)$/sc_csvtablebox.obj	\
    $(SLO)$/sc_asciiopt.obj

EXCEPTIONSFILES= \
    $(SLO)$/sc_dapidata.obj

SRS1NAME=$(TARGET)
SRC1FILES =  \
        sc_pivot.src		\
        sc_pvfundlg.src	\
        sc_dapitype.src	\
        sc_consdlg.src		\
        sc_scendlg.src     \
        sc_imoptdlg.src    \
        sc_validate.src    \
        sc_asciiopt.src    \
        sc_outline.src

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk


