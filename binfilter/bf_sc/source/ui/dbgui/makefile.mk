#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: aw $ $Date: 2003-10-09 14:12:56 $
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

PRJNAME=binfilter
TARGET=sc_dbgui

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


