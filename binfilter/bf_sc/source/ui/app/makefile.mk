#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.8 $
#
#   last change: $Author: obo $ $Date: 2007-03-09 14:20:38 $
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
TARGET=sc_app

NO_HIDS=TRUE

PROJECTPCH4DLL=TRUE
PROJECTPCH=ui_pch
PDBTARGET=ui_pch
PROJECTPCHSOURCE=..$/pch$/sc_ui_pch

# --- Settings -----------------------------------------------------

.INCLUDE :  scpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sc.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sc
# --- Files --------------------------------------------------------

SLOFILES =  \
    $(SLO)$/sc_scmod.obj  \
    $(SLO)$/sc_scmod2.obj  \
    $(SLO)$/sc_scdll.obj  \
    $(SLO)$/sc_transobj.obj \
    $(SLO)$/sc_drwtrans.obj \
    $(SLO)$/sc_seltrans.obj \
    $(SLO)$/sc_inputhdl.obj \
    $(SLO)$/sc_inputwin.obj \
    $(SLO)$/sc_rfindlst.obj \
    $(SLO)$/sc_uiitems.obj  \
    $(SLO)$/sc_msgpool.obj \
    $(SLO)$/sc_client.obj \
    $(SLO)$/sc_typemap.obj

EXCEPTIONSFILES= \
    $(SLO)$/sc_scmod2.obj \
    $(SLO)$/sc_scmod.obj

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

