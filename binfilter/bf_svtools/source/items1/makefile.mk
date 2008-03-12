#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: rt $ $Date: 2008-03-12 08:49:25 $
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
TARGET=items1
ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_svtools

# --- Files --------------------------------------------------------

SLOFILES=\
    $(SLO)$/svt_bintitem.obj	\
    $(SLO)$/svt_cenumitm.obj	\
    $(SLO)$/svt_cintitem.obj	\
    $(SLO)$/svt_cntwall.obj	\
    $(SLO)$/svt_cstitem.obj	\
    $(SLO)$/svt_ctypeitm.obj	\
    $(SLO)$/svt_custritm.obj	\
    $(SLO)$/svt_dateitem.obj	\
    $(SLO)$/svt_dtritem.obj	\
    $(SLO)$/svt_frqitem.obj	\
    $(SLO)$/svt_ilstitem.obj    \
    $(SLO)$/svt_itemiter.obj	\
    $(SLO)$/svt_itempool.obj	\
    $(SLO)$/svt_itemprop.obj	\
    $(SLO)$/svt_itemset.obj	\
    $(SLO)$/svt_lckbitem.obj	\
    $(SLO)$/svt_poolio.obj	\
    $(SLO)$/svt_stylepool.obj	\
    $(SLO)$/svt_poolitem.obj	\
    $(SLO)$/svt_sfontitm.obj	\
    $(SLO)$/svt_sitem.obj	    \
    $(SLO)$/svt_slstitm.obj	\
    $(SLO)$/svt_tfrmitem.obj	\
    $(SLO)$/svt_tresitem.obj	\
    $(SLO)$/svt_whiter.obj \
    $(SLO)$/svt_visitem.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

