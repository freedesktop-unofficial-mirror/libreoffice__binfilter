#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.4 $
#
#   last change: $Author: obo $ $Date: 2005-08-10 11:24:39 $
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
TARGET=sc_app

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

PROJECTPCH4DLL=TRUE
PROJECTPCH=ui_pch
PDBTARGET=ui_pch
PROJECTPCHSOURCE=..$/pch$/sc_ui_pch

AUTOSEG=true

# --- Settings -----------------------------------------------------

.INCLUDE :  scpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sc.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sc
# --- Files --------------------------------------------------------

#OBJFILES = \
#	$(OBJ)$/sc_sclib.obj

SLOFILES =  \
    $(SLO)$/sc_scmod.obj  \
    $(SLO)$/sc_scmod2.obj  \
    $(SLO)$/sc_scdll.obj  \
    $(SLO)$/sc_typemap.obj  \
    $(SLO)$/sc_transobj.obj \
    $(SLO)$/sc_drwtrans.obj \
    $(SLO)$/sc_lnktrans.obj \
    $(SLO)$/sc_seltrans.obj \
    $(SLO)$/sc_inputhdl.obj \
    $(SLO)$/sc_inputwin.obj \
    $(SLO)$/sc_rfindlst.obj \
    $(SLO)$/sc_uiitems.obj  \
    $(SLO)$/sc_msgpool.obj \
    $(SLO)$/sc_client.obj

EXCEPTIONSFILES= \
    $(SLO)$/sc_scmod2.obj \
    $(SLO)$/sc_scmod.obj

#LIB3TARGET=$(SLB)$/bf_ysclib.lib
#LIB3OBJFILES=$(SLO)$/sc_sclib.obj

DEPOBJFILES=$(SLO)$/sc_sclib.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

ALLTAR : $(DEPOBJFILES)

$(SLO)$/sc_sclib.obj :	$(INCCOM)$/scdll0.hxx
#$(OBJ)$/sc_sclib.obj :	$(INCCOM)$/scdll0.hxx

$(INCCOM)$/scdll0.hxx: makefile.mk
.IF "$(GUI)"=="UNX"
    echo \#define DLL_NAME \"libbf_sc$(UPD)$(DLLPOSTFIX)$(DLLPOST)\" >$@
.ELSE			# "$(GUI)"=="UNX"
.IF "$(USE_SHELL)"!="4nt"
    echo \#define DLL_NAME \"bf_sc$(UPD)$(DLLPOSTFIX).DLL\" >$@
.ELSE			#  "$(USE_SHELL)"!="4nt"
    echo #define DLL_NAME "bf_sc$(UPD)$(DLLPOSTFIX).DLL" >$@
.ENDIF			#  "$(USE_SHELL)"!="4nt"
.ENDIF			# "$(GUI)"=="UNX"

$(SRS)$/sc_app.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc

