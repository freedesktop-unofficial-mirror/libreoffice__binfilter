#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.10 $
#
#   last change: $Author: obo $ $Date: 2007-03-12 09:32:48 $
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

NO_HIDS=TRUE
TARGET=svx_xout
ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Files --------------------------------------------------------

SLOFILES= \
        $(SLO)$/svx_xout.obj   		\
        $(SLO)$/svx_xout1.obj  		\
        $(SLO)$/svx_xattr.obj  		\
        $(SLO)$/svx_xattr2.obj  	\
        $(SLO)$/svx_xattrbmp.obj	\
        $(SLO)$/svx_xline.obj   	\
        $(SLO)$/svx_xpool.obj  		\
        $(SLO)$/svx_xtable.obj 		\
        $(SLO)$/svx_xtabcolr.obj	\
        $(SLO)$/svx_xtablend.obj	\
        $(SLO)$/svx_xtabdash.obj	\
        $(SLO)$/svx_xtabhtch.obj	\
        $(SLO)$/svx_xtabgrdt.obj	\
        $(SLO)$/svx_xtabbtmp.obj	\
        $(SLO)$/svx_xiocomp.obj		\
        $(SLO)$/svx__xpoly.obj  	\
        $(SLO)$/svx__ximp.obj   	\
        $(SLO)$/svx__xoutbmp.obj	\
        $(SLO)$/svx__xfont.obj

HXXCOPYFILES=\
     $(PRJ)$/inc$/bf_svx$/xenum.hxx


.INCLUDE :  target.mk
