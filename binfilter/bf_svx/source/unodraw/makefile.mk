#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.7 $
#
#   last change: $Author: obo $ $Date: 2007-07-17 11:48:14 $
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
TARGET=svx_unodraw

NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Files --------------------------------------------------------

SLOFILES =	\
        $(SLO)$/svx_UnoNamespaceMap.obj \
        $(SLO)$/svx_unopool.obj \
        $(SLO)$/svx_XPropertyTable.obj \
        $(SLO)$/svx_UnoNameItemTable.obj \
        $(SLO)$/svx_unoshape.obj	\
        $(SLO)$/svx_unoipset.obj	\
        $(SLO)$/svx_unoctabl.obj	\
        $(SLO)$/svx_unoshap2.obj	\
        $(SLO)$/svx_unoshap3.obj	\
        $(SLO)$/svx_unoshap4.obj	\
        $(SLO)$/svx_unopage.obj		\
        $(SLO)$/svx_unoshtxt.obj	\
        $(SLO)$/svx_unoshcol.obj	\
        $(SLO)$/svx_unoprov.obj		\
        $(SLO)$/svx_unomod.obj      \
        $(SLO)$/svx_unonrule.obj	\
        $(SLO)$/svx_unofdesc.obj	\
        $(SLO)$/svx_unomlstr.obj	\
        $(SLO)$/svx_unogtabl.obj	\
        $(SLO)$/svx_unohtabl.obj	\
        $(SLO)$/svx_unobtabl.obj	\
        $(SLO)$/svx_unottabl.obj	\
        $(SLO)$/svx_unomtabl.obj	\
        $(SLO)$/svx_unodtabl.obj	\
        $(SLO)$/svx_gluepts.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

