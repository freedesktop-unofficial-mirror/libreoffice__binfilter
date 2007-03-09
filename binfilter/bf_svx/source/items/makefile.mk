#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.9 $
#
#   last change: $Author: obo $ $Date: 2007-03-09 16:11:16 $
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

PRJ=..$/..$/..
BFPRJ=..$/..

PROJECTPCH4DLL=TRUE
PROJECTPCH=svxpch
PROJECTPCHSOURCE=$(BFPRJ)$/util$/svx_svxpch

PRJNAME=binfilter
TARGET=svx_items

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :	settings.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Files --------------------------------------------------------

SRS1NAME=svx_svxitems
SRC1FILES =  \
        svx_svxerr.src		\
        svx_svxitems.src

SLOFILES=	\
        $(SLO)$/svx_writingmodeitem.obj \
        $(SLO)$/svx_frmitems.obj \
        $(SLO)$/svx_paraitem.obj \
        $(SLO)$/svx_textitem.obj \
        $(SLO)$/svx_postattr.obj	\
        $(SLO)$/svx_flditem.obj \
        $(SLO)$/svx_hlnkitem.obj \
        $(SLO)$/svx_svxfont.obj \
        $(SLO)$/svx_pageitem.obj	\
        $(SLO)$/svx_paperinf.obj	\
        $(SLO)$/svx_drawitem.obj	\
        $(SLO)$/svx_algitem.obj \
        $(SLO)$/svx_rotmodit.obj \
        $(SLO)$/svx_svxerr.obj	\
        $(SLO)$/svx_zoomitem.obj \
        $(SLO)$/svx_chrtitem.obj	\
        $(SLO)$/svx_bulitem.obj \
        $(SLO)$/svx_e3ditem.obj \
        $(SLO)$/svx_numitem.obj \
        $(SLO)$/svx_grfitem.obj \
        $(SLO)$/svx_clipfmtitem.obj \
        $(SLO)$/svx_xmlcnitm.obj

EXCEPTIONSFILES= \
        $(SLO)$/svx_paraitem.obj \
        $(SLO)$/svx_frmitems.obj \
        $(SLO)$/svx_numitem.obj\
        $(SLO)$/svx_xmlcnitm.obj

.INCLUDE :	target.mk

