#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.1 $
#
#   last change: $Author: aw $ $Date: 2003-10-02 14:42:35 $
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

PRJNAME=bf_sc
TARGET=sc_tool

PROJECTPCH4DLL=TRUE
PROJECTPCH=core_pch
PROJECTPCHSOURCE=..\pch\sc_core_pch

AUTOSEG=true

# --- Settings -----------------------------------------------------

.INCLUDE :  scpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sc.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sc
# --- Files --------------------------------------------------------

SLOFILES =  \
        $(SLO)$/sc_adiasync.obj \
        $(SLO)$/sc_appoptio.obj \
        $(SLO)$/sc_autoform.obj \
        $(SLO)$/sc_callform.obj \
        $(SLO)$/sc_cellform.obj \
        $(SLO)$/sc_chartarr.obj \
        $(SLO)$/sc_chartlis.obj \
        $(SLO)$/sc_chgtrack.obj \
        $(SLO)$/sc_chgviset.obj \
        $(SLO)$/sc_collect.obj  \
        $(SLO)$/sc_compiler.obj \
        $(SLO)$/sc_consoli.obj  \
        $(SLO)$/sc_dbcolect.obj \
        $(SLO)$/sc_ddelink.obj \
        $(SLO)$/sc_detfunc.obj  \
        $(SLO)$/sc_detdata.obj  \
        $(SLO)$/sc_docoptio.obj \
        $(SLO)$/sc_editutil.obj \
        $(SLO)$/sc_indexmap.obj \
        $(SLO)$/sc_interpr1.obj \
        $(SLO)$/sc_interpr2.obj \
        $(SLO)$/sc_interpr3.obj \
        $(SLO)$/sc_interpr4.obj \
        $(SLO)$/sc_interpr5.obj \
        $(SLO)$/sc_interpr6.obj \
        $(SLO)$/sc_linelink.obj \
        $(SLO)$/sc_progress.obj \
        $(SLO)$/sc_rangenam.obj \
        $(SLO)$/sc_rangelst.obj \
        $(SLO)$/sc_rangeutl.obj \
        $(SLO)$/sc_rechead.obj  \
        $(SLO)$/sc_refupdat.obj \
        $(SLO)$/sc_refdata.obj \
        $(SLO)$/sc_reffind.obj \
        $(SLO)$/sc_scdebug.obj \
        $(SLO)$/sc_scmatrix.obj \
        $(SLO)$/sc_sctictac.obj \
        $(SLO)$/sc_subtotal.obj \
        $(SLO)$/sc_token.obj \
        $(SLO)$/sc_unitconv.obj \
        $(SLO)$/sc_userlist.obj \
        $(SLO)$/sc_viewopti.obj \
        $(SLO)$/sc_inputopt.obj \
        $(SLO)$/sc_filtopt.obj \
        $(SLO)$/sc_printopt.obj \
        $(SLO)$/sc_optutil.obj \
        $(SLO)$/sc_zforauto.obj \
        $(SLO)$/sc_hints.obj \
        $(SLO)$/sc_prnsave.obj \
        $(SLO)$/sc_navicfg.obj \
        $(SLO)$/sc_addincol.obj \
        $(SLO)$/sc_addinlis.obj \
        $(SLO)$/sc_addinhelpid.obj \
        $(SLO)$/sc_rangeseq.obj \
        $(SLO)$/sc_refreshtimer.obj

EXCEPTIONSFILES= \
        $(SLO)$/sc_addincol.obj

# [kh] POWERPC compiler problem
.IF "$(OS)$(COM)$(CPUNAME)"=="LINUXGCCPOWERPC"
NOOPTFILES= \
                $(SLO)$/sc_subtotal.obj
.ENDIF

.IF "$(GUI)"=="OS2"
NOOPTFILES= \
        $(SLO)$/sc_interpr6.obj
.ENDIF

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

