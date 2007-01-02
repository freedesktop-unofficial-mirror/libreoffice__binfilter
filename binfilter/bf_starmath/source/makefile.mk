#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.8 $
#
#   last change: $Author: hr $ $Date: 2007-01-02 17:17:26 $
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

PROJECTPCH4DLL=TRUE

PRJ=..$/..
BFPRJ=..

PRJNAME=binfilter
TARGET=bf_starmath

NO_HIDS=TRUE

PROJECTPCH=math_pch
PDBTARGET=math_pch
PROJECTPCHSOURCE=starmath_math_pch


# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
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
        $(SLO)$/starmath_cfgitem.obj \
        $(SLO)$/starmath_config.obj \
        $(SLO)$/starmath_document.obj \
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
    echo \#define DLL_NAME \"$(DLLPRE)bf_sm$(UPD)$(DLLPOSTFIX)$(DLLPOST)\" >$@
.ELSE
    echo $(EMQ)#define DLL_NAME $(EMQ)"$(DLLPRE)bf_sm$(UPD)$(DLLPOSTFIX)$(DLLPOST)$(EMQ)" >$@
.ENDIF

$(SRS)$/starmath_smres.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc
