#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.3 $
#
#   last change: $Author: aw $ $Date: 2003-11-18 19:22:50 $
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
TARGET=sc_view

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
# drawattr.cxx fuer IDL (enums), sollte in den Svx gehen??

SLOFILES =  \
        $(SLO)$/sc_tabview.obj \
        $(SLO)$/sc_tabview2.obj \
        $(SLO)$/sc_tabview3.obj \
        $(SLO)$/sc_tabview4.obj \
        $(SLO)$/sc_tabview5.obj \
        $(SLO)$/sc_viewfunc.obj \
        $(SLO)$/sc_viewfun2.obj \
        $(SLO)$/sc_viewfun3.obj \
        $(SLO)$/sc_viewfun4.obj \
        $(SLO)$/sc_viewfun5.obj \
        $(SLO)$/sc_viewfun6.obj \
        $(SLO)$/sc_viewfun7.obj \
        $(SLO)$/sc_dbfunc.obj \
        $(SLO)$/sc_dbfunc2.obj \
        $(SLO)$/sc_dbfunc3.obj \
        $(SLO)$/sc_dbfunc4.obj \
        $(SLO)$/sc_tabvwsh.obj \
        $(SLO)$/sc_tabvwsh2.obj \
        $(SLO)$/sc_tabvwsh3.obj \
        $(SLO)$/sc_tabvwsh4.obj \
        $(SLO)$/sc_tabvwsh5.obj \
        $(SLO)$/sc_tabvwsh8.obj \
        $(SLO)$/sc_tabvwsh9.obj \
        $(SLO)$/sc_tabvwsha.obj \
        $(SLO)$/sc_tabvwshb.obj \
        $(SLO)$/sc_tabvwshc.obj \
        $(SLO)$/sc_tabvwshd.obj \
        $(SLO)$/sc_tabvwshe.obj \
    $(SLO)$/sc_tabvwshf.obj \
    $(SLO)$/sc_tabvwshg.obj \
        $(SLO)$/sc_tabvwshh.obj \
        $(SLO)$/sc_printfun.obj \
        $(SLO)$/sc_pfuncache.obj \
        $(SLO)$/sc_preview.obj \
        $(SLO)$/sc_prevwsh.obj \
        $(SLO)$/sc_prevwsh2.obj \
        $(SLO)$/sc_prevloc.obj \
        $(SLO)$/sc_editsh.obj \
        $(SLO)$/sc_pivotsh.obj \
        $(SLO)$/sc_auditsh.obj \
        $(SLO)$/sc_gridwin.obj \
        $(SLO)$/sc_gridwin2.obj \
        $(SLO)$/sc_gridwin3.obj \
        $(SLO)$/sc_gridwin4.obj \
        $(SLO)$/sc_gridwin5.obj \
        $(SLO)$/sc_drawview.obj \
        $(SLO)$/sc_drawvie2.obj \
        $(SLO)$/sc_drawvie3.obj \
        $(SLO)$/sc_drawvie4.obj \
        $(SLO)$/sc_drawutil.obj \
        $(SLO)$/sc_output.obj \
        $(SLO)$/sc_output2.obj \
        $(SLO)$/sc_output3.obj \
        $(SLO)$/sc_gridmerg.obj \
        $(SLO)$/sc_invmerge.obj \
        $(SLO)$/sc_select.obj \
        $(SLO)$/sc_olinewin.obj \
        $(SLO)$/sc_hintwin.obj \
        $(SLO)$/sc_notemark.obj \
        $(SLO)$/sc_tabcont.obj \
        $(SLO)$/sc_tabsplit.obj \
        $(SLO)$/sc_viewdata.obj \
        $(SLO)$/sc_viewutil.obj \
        $(SLO)$/sc_hdrcont.obj \
        $(SLO)$/sc_colrowba.obj \
        $(SLO)$/sc_olkact.obj \
        $(SLO)$/sc_galwrap.obj \
        $(SLO)$/sc_imapwrap.obj \
        $(SLO)$/sc_reffact.obj \
        $(SLO)$/sc_spelleng.obj \
        $(SLO)$/sc_waitoff.obj \
        $(SLO)$/sc_cellsh.obj \
        $(SLO)$/sc_cellsh1.obj\
        $(SLO)$/sc_cellsh2.obj\
        $(SLO)$/sc_cellsh3.obj\
        $(SLO)$/sc_cellsh4.obj\
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

