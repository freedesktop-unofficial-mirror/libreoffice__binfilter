#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: aw $ $Date: 2003-10-09 14:14:05 $
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

#MKDEPENDSOLVER=YES
PROJECTPCH4DLL=TRUE

PRJ=..$/..
BFPRJ=..
PRJNAME=binfilter
TARGET=bf_starmath

PROJECTPCH=math_pch
PDBTARGET=math_pch
PROJECTPCHSOURCE=starmath_math_pch


# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
#.INCLUDE :  $(PRJ)$/util$/makefile.pmk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
#IMGLST_SRS=$(SRS)$/smres.srs
INC+= -I$(PRJ)$/inc$/bf_starmath
# --- Files --------------------------------------------------------

SMDLL=TRUE

SRS2NAME =starmath_smres
SRC2FILES = starmath_smres.src   \
            starmath_symbol.src	\
            starmath_commands.src

SLOFILES =  \
        $(SLO)$/starmath_register.obj \
        $(SLO)$/starmath_typemap.obj \
        $(SLO)$/starmath_symbol.obj \
        $(SLO)$/starmath_toolbox.obj \
        $(SLO)$/starmath_action.obj \
        $(SLO)$/starmath_accessibility.obj \
        $(SLO)$/starmath_cfgitem.obj \
        $(SLO)$/starmath_config.obj \
        $(SLO)$/starmath_dialog.obj \
        $(SLO)$/starmath_document.obj \
        $(SLO)$/starmath_mathtype.obj \
        $(SLO)$/starmath_mathml.obj \
        $(SLO)$/starmath_format.obj \
        $(SLO)$/starmath_node.obj \
        $(SLO)$/starmath_parse.obj \
        $(SLO)$/starmath_utility.obj \
        $(SLO)$/starmath_smdll.obj \
        $(SLO)$/starmath_smmod.obj \
        $(SLO)$/starmath_view.obj \
        $(SLO)$/starmath_viewhdl.obj \
        $(SLO)$/starmath_edit.obj \
        $(SLO)$/starmath_rect.obj \
        $(SLO)$/starmath_unomodel.obj \
        $(SLO)$/starmath_unodoc.obj

EXCEPTIONSFILES =   \
        $(SLO)$/starmath_accessibility.obj \
        $(SLO)$/starmath_register.obj  \
        $(SLO)$/starmath_mathml.obj \
        $(SLO)$/starmath_viewhdl.obj \
        $(SLO)$/starmath_unomodel.obj \
        $(SLO)$/starmath_unodoc.obj


LIB2TARGET =    $(SLB)$/bf_ysm.lib
LIB2ARCHIV =    $(LB)$/libbf_ysm.a
LIB2OBJFILES  =    $(SLO)$/starmath_smlib.obj

DEPOBJFILES = $(SLO)$/starmath_smlib.obj

# --- Targets -------------------------------------------------------

.IF "$(GUI)"=="UNX" || "$(GUI)"=="MAC"
CDEFS+=-DUSE_POLYGON
.ENDIF

.INCLUDE :  target.mk

$(SLO)$/starmath_smlib.obj : $(INCCOM)$/dllname.hxx

$(INCCOM)$/dllname.hxx: makefile.mk
.IF "$(GUI)"=="UNX"
    $(RM) $@
    +echo \#define DLL_NAME \"$(DLLPRE)bf_sm$(UPD)$(DLLPOSTFIX)$(DLLPOST)\" >$@
.ELSE
.IF "$(USE_SHELL)"!="4nt"
        +echo \#define DLL_NAME \"$(DLLPRE)bf_sm$(UPD)$(DLLPOSTFIX)$(DLLPOST)\" >$@
.ELSE          # "$(USE_SHELL)"!="4nt"
    +echo #define DLL_NAME "bf_sm$(UPD)$(DLLPOSTFIX)$(DLLPOST)" >$@
.ENDIF          # "$(USE_SHELL)"!="4nt"
.ENDIF

$(SRS)$/starmath_smres.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc
