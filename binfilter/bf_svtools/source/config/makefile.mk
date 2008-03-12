#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: rt $ $Date: 2008-03-12 08:27:27 $
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
PRJ=..$/..$/..

PRJNAME=binfilter
TARGET=config
ENABLE_EXCEPTIONS := TRUE

# --- Settings -----------------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_svtools

# --- Files --------------------------------------------------------

SLOFILES = \
    $(SLO)$/svt_fltrcfg.obj				\
    $(SLO)$/svt_moduleoptions.obj           \
    $(SLO)$/svt_pathoptions.obj             \
    $(SLO)$/svt_saveopt.obj					\
    $(SLO)$/svt_lingucfg.obj                \
    $(SLO)$/svt_javaoptions.obj             \
    $(SLO)$/svt_securityoptions.obj			\
    $(SLO)$/svt_localisationoptions.obj		\
    $(SLO)$/svt_workingsetoptions.obj		\
    $(SLO)$/svt_viewoptions.obj				\
    $(SLO)$/svt_internaloptions.obj			\
    $(SLO)$/svt_startoptions.obj			\
    $(SLO)$/svt_historyoptions.obj			\
    $(SLO)$/svt_inetoptions.obj				\
    $(SLO)$/svt_menuoptions.obj				\
    $(SLO)$/svt_dynamicmenuoptions.obj		\
    $(SLO)$/svt_options3d.obj				\
    $(SLO)$/svt_optionsdrawinglayer.obj		\
    $(SLO)$/svt_fontoptions.obj				\
    $(SLO)$/svt_addxmltostorageoptions.obj	\
    $(SLO)$/svt_defaultoptions.obj			\
    $(SLO)$/svt_searchopt.obj				\
    $(SLO)$/svt_printwarningoptions.obj		\
    $(SLO)$/svt_cacheoptions.obj            \
    $(SLO)$/svt_regoptions.obj				\
    $(SLO)$/svt_cmdoptions.obj				\
    $(SLO)$/svt_extendedsecurityoptions.obj \
    $(SLO)$/svt_sourceviewconfig.obj		\
    $(SLO)$/svt_compatibility.obj           \
    $(SLO)$/svt_eventcfg.obj                \
    $(SLO)$/svt_optionsdlg.obj              \
    $(SLO)$/svt_itemholder1.obj \
    $(SLO)$/svt_options.obj \
    $(SLO)$/svt_fontsubstconfig.obj				\
    $(SLO)$/svt_misccfg.obj				\
    $(SLO)$/svt_apearcfg.obj				\
    $(SLO)$/svt_helpopt.obj                 \
    $(SLO)$/svt_printoptions.obj			\
    $(SLO)$/svt_languageoptions.obj     \
    $(SLO)$/svt_ctloptions.obj          \
    $(SLO)$/svt_cjkoptions.obj          \
    $(SLO)$/svt_colorcfg.obj            \
    $(SLO)$/svt_extcolorcfg.obj            \
    $(SLO)$/svt_undoopt.obj                 \
    $(SLO)$/svt_useroptions.obj      \
    $(SLO)$/svt_syslocaleoptions.obj \
    $(SLO)$/svt_itemholder2.obj \
    $(SLO)$/svt_miscopt.obj

# --- Targets ------------------------------------------------------

.INCLUDE :  target.mk

