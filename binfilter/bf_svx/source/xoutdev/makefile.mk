#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.1.1.1 $
#
#   last change: $Author: hjs $ $Date: 2003-10-01 12:21:11 $
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

PRJ=..$/..$/..
BFPRJ=..$/..

PRJNAME=bf_svx
PROJECTPCH=xout
PROJECTPCHSOURCE=svx_xoutpch
TARGET=svx_xout
AUTOSEG=true
ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Files --------------------------------------------------------

HXX1TARGET	=	xoutx
HXX1EXT		=	hxx
HXX1FILES	=	$(INC)$/xoutx.hxx
HXX1EXCL	= 	-K:*compat.hxx

HXX2TARGET	=	xattr
HXX2EXT		=	hxx
HXX2FILES	=	$(INC)$/xattr.hxx
HXX2EXCL	= 	-K:*compat.hxx

HXX3TARGET	=	xpoly
HXX3EXT		=	hxx
HXX3FILES	=	$(INC)$/xpoly.hxx
HXX3EXCL	= 	-K:*compat.hxx

HXX4TARGET	=	xtable
HXX4EXT		=	hxx
HXX4FILES	=	$(INC)$/xtable.hxx
HXX4EXCL	= 	-K:*compat.hxx

HXX5TARGET	=	xoutbmp
HXX5EXT		=	hxx
HXX5FILES	=	$(INC)$/xoutbmp.hxx
HXX5EXCL	= 	-K:*compat.hxx

HXX6TARGET	=	xpool
HXX6EXT		=	hxx
HXX6FILES	=	$(INC)$/xpool.hxx
HXX6EXCL	= 	-K:*compat.hxx

.IF "$(header)" == ""

CXXFILES= \
        svx_xcpoly.cxx		\
        svx_xoutpch.cxx 	\
        svx_xout.cxx		\
        svx_xout1.cxx		\
        svx_xattr.cxx		\
        svx_xattr2.cxx		\
        svx_xattrbmp.cxx	\
        svx_xline.cxx		\
        svx_xpool.cxx		\
        svx_xtable.cxx		\
        svx_xtabcolr.cxx	\
        svx_xtablend.cxx	\
        svx_xtabdash.cxx	\
        svx_xtabhtch.cxx	\
        svx_xtabgrdt.cxx	\
        svx_xtabbtmp.cxx	\
        svx_xexch.cxx       \
        svx_xiocomp.cxx		\
        svx__xpoly.cxx		\
        svx__ximp.cxx		\
        svx__xoutbmp.cxx	\
        svx__xfont.cxx

SLOFILES= \
        $(SLO)$/svx_xcpoly.obj 		\
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
        $(SLO)$/svx_xexch.obj		\
        $(SLO)$/svx_xiocomp.obj		\
        $(SLO)$/svx__xpoly.obj  	\
        $(SLO)$/svx__ximp.obj   	\
        $(SLO)$/svx__xoutbmp.obj	\
        $(SLO)$/svx__xfont.obj

SVXLIGHTOBJFILES= \
        $(OBJ)$/svx_xcpoly.obj 		\
        $(OBJ)$/svx_xout.obj   		\
        $(OBJ)$/svx_xout1.obj  		\
        $(OBJ)$/svx_xattr.obj  		\
        $(OBJ)$/svx_xattr2.obj  	\
        $(OBJ)$/svx_xattrbmp.obj	\
        $(OBJ)$/svx_xline.obj   	\
        $(OBJ)$/svx_xpool.obj  		\
        $(OBJ)$/svx_xtable.obj 		\
        $(OBJ)$/svx_xtabcolr.obj	\
        $(OBJ)$/svx_xtablend.obj	\
        $(OBJ)$/svx_xtabdash.obj	\
        $(OBJ)$/svx_xtabhtch.obj	\
        $(OBJ)$/svx_xtabgrdt.obj	\
        $(OBJ)$/svx_xtabbtmp.obj	\
        $(OBJ)$/svx_xexch.obj		\
        $(OBJ)$/svx_xiocomp.obj		\
        $(OBJ)$/svx__xpoly.obj  	\
        $(OBJ)$/svx__ximp.obj   	\
        $(OBJ)$/svx__xoutbmp.obj	\
        $(OBJ)$/svx__xfont.obj

.ENDIF

HXXCOPYFILES=\
     $(PRJ)$/inc$/bf_svx$/xenum.hxx


.INCLUDE :  target.mk
