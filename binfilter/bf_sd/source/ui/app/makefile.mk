#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.4 $
#
#   last change: $Author: obo $ $Date: 2005-08-10 11:25:05 $
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

PROJECTPCH=sd
PROJECTPCHSOURCE=$(BFPRJ)$/util$/sd_sd

PRJNAME=binfilter
TARGET=sd_app

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

AUTOSEG=true

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sd
NO_HID_FILES=sd_app.src
.EXPORT : NO_HID_FILES

# --- Imagelisten --------------------------------------------------

#IMGLST_SRS=$(SRS)$/sd_app.srs
BMP_IN=$(BFPRJ)$/res/imagelst

# --- Update-Version -----------------------------------------------

RSCUPDVER=$(RSCREVISION)SV$(UPD)$(UPDMINOR)

# --- Files --------------------------------------------------------

SRS1NAME=$(TARGET)
SRC1FILES =	\
        sd_app.src 			\
        sd_toolbox.src			\
        sd_strings.src 		\
        sd_res_bmp.src 		\
        sd_tbx_ww.src			\
        sd_popup.src			\
        sd_sdstring.src		\
        sd_pseudo.src

#OBJFILES = \
#		$(OBJ)$/sd_sdlib.obj	\
#		$(OBJ)$/sd_sdresid.obj

SLOFILES =	\
        $(SLO)$/sd_sdmod.obj		\
        $(SLO)$/sd_sdmod1.obj		\
        $(SLO)$/sd_sdmod2.obj		\
        $(SLO)$/sd_sddll.obj		\
        $(SLO)$/sd_sddll1.obj      \
        $(SLO)$/sd_sddll2.obj      \
        $(SLO)$/sd_tbxww.obj		\
        $(SLO)$/sd_optsitem.obj	\
        $(SLO)$/sd_sdresid.obj		\
        $(SLO)$/sd_sdpopup.obj		\
        $(SLO)$/sd_sdxfer.obj		

EXCEPTIONSFILES= \
        $(SLO)$/sd_sdxfer.obj		\
        $(SLO)$/sd_sdmod1.obj		

#LIB3TARGET=$(SLB)$/bf_ysdlib.lib
#LIB3OBJFILES=

DEPOBJFILES= \
        $(SLO)$/sd_sdlib.obj \
         $(SLO)$/sd_sdresid.obj

.IF "$(GUI)" == "WNT"

NOOPTFILES=\
    $(SLO)$/sd_optsitem.obj

.ENDIF

# --- Tagets -------------------------------------------------------

all: \
    $(INCCOM)$/sddll0.hxx   \
    ALLTAR

$(INCCOM)$/sddll0.hxx: makefile.mk
    +@echo $@
.IF "$(GUI)"=="UNX"
    echo \#define DLL_NAME \"libbf_sd$(UPD)$(DLLPOSTFIX)$(DLLPOST)\" >$@
.ELSE			# "$(GUI)"=="UNX"
.IF "$(USE_SHELL)"!="4nt"
    echo \#define DLL_NAME \"bf_sd$(UPD)$(DLLPOSTFIX).DLL\" >$@
.ELSE			# "$(USE_SHELL)"!="4nt"
    echo #define DLL_NAME "bf_sd$(UPD)$(DLLPOSTFIX).DLL" >$@
.ENDIF			#  "$(USE_SHELL)"!="4nt"
.ENDIF			# "$(GUI)"=="UNX"

.INCLUDE :  target.mk

ALLTAR : $(DEPOBJFILES)

$(SRS)$/sd_app.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc

