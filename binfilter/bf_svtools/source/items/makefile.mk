#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: rt $ $Date: 2008-03-12 08:45:42 $
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
TARGET=items
ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_svtools

# --- Files --------------------------------------------------------

SLOFILES=\
    $(SLO)$/svt_aeitem.obj	\
    $(SLO)$/svt_eitem.obj	\
    $(SLO)$/svt_flagitem.obj	\
    $(SLO)$/svt_globalnameitem.obj	\
    $(SLO)$/svt_imageitm.obj    \
    $(SLO)$/svt_intitem.obj	\
    $(SLO)$/svt_itemdel.obj	\
    $(SLO)$/svt_macitem.obj	\
    $(SLO)$/svt_poolcach.obj	\
    $(SLO)$/svt_ptitem.obj	\
    $(SLO)$/svt_rectitem.obj	\
    $(SLO)$/svt_rngitem.obj	\
    $(SLO)$/svt_stritem.obj	\
    $(SLO)$/svt_style.obj	\
    $(SLO)$/svt_szitem.obj	\
    $(SLO)$/svt_wallitem.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

