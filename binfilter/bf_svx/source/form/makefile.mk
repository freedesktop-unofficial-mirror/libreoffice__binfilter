#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.7 $
#
#   last change: $Author: obo $ $Date: 2007-01-25 12:01:22 $
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

PRJNAME=binfilter
TARGET=svx_form

NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Files --------------------------------------------------------

BMP_IN=$(BFPRJ)$/win$/res

SRS1NAME=svx_form
SRC1FILES= \
    svx_fmexpl.src 		\
    svx_filtnav.src		\
    svx_taborder.src 	\
    svx_fmstring.src 	\
    svx_tbxform.src		\
    svx_fmsearch.src


SLOFILES = \
    $(SLO)$/svx_ParseContext.obj			\
    $(SLO)$/svx_dbtoolsclient.obj      \
    $(SLO)$/svx_sqlparserclient.obj      \
    $(SLO)$/svx_fmpage.obj      \
    $(SLO)$/svx_fmPropBrw.obj			\
    $(SLO)$/svx_fmundo.obj  	\
    $(SLO)$/svx_fmprop.obj      \
    $(SLO)$/svx_fmmodel.obj		\
    $(SLO)$/svx_navigatortree.obj      \
    $(SLO)$/svx_navigatortreemodel.obj      \
    $(SLO)$/svx_fmexpl.obj      \
    $(SLO)$/svx_fmctrler.obj    \
    $(SLO)$/svx_fmpgeimp.obj	\
    $(SLO)$/svx_fmvwimp.obj     \
    $(SLO)$/svx_taborder.obj    \
    $(SLO)$/svx_fmdpage.obj		\
    $(SLO)$/svx_tbxform.obj     \
    $(SLO)$/svx_fmobj.obj      	\
    $(SLO)$/svx_fmdmod.obj		\
    $(SLO)$/svx_fmobjfac.obj	\
    $(SLO)$/svx_fmservs.obj     \
    $(SLO)$/svx_typemap.obj		\
    $(SLO)$/svx_fmexch.obj      \
    $(SLO)$/svx_tabwin.obj      \
    $(SLO)$/svx_multipro.obj	\
    $(SLO)$/svx_fmurl.obj		\
    $(SLO)$/svx_filtnav.obj		\
    $(SLO)$/svx_fmimplids.obj   \
    $(SLO)$/svx_fmtools.obj     \
    $(SLO)$/svx_fmshimp.obj     \
    $(SLO)$/svx_fmshell.obj     \
    $(SLO)$/svx_fmsearch.obj	\
    $(SLO)$/svx_fmview.obj		\
    $(SLO)$/svx_siimport.obj	\
    $(SLO)$/svx_sdbdatacolumn.obj

.IF "$(OS)$(CPU)"=="SOLARISI" 
NOOPTFILES=$(SLO)$/svx_fmprop.obj
.ENDIF

.INCLUDE :  target.mk
