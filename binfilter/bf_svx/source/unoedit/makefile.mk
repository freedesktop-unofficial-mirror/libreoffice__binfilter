#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: aw $ $Date: 2003-10-09 14:14:26 $
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

PRJNAME=binfilter
TARGET=svx_unoedit
ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Files --------------------------------------------------------

CXXFILES =				\
        svx_UnoForbiddenCharsTable.cxx \
        svx_unoedsrc.cxx	\
        svx_unoedhlp.cxx	\
        svx_unopracc.cxx	\
        svx_unoedprx.cxx	\
        svx_unoviwed.cxx	\
        svx_unoviwou.cxx	\
        svx_unofored.cxx	\
        svx_unoforou.cxx	\
        svx_unotext.cxx		\
        svx_unotext2.cxx	\
        svx_unofield.cxx	

SVXLIGHTOBJFILES=\
        $(OBJ)$/svx_UnoForbiddenCharsTable.obj \
        $(OBJ)$/svx_unoedsrc.obj	\
        $(OBJ)$/svx_unoedhlp.obj	\
        $(OBJ)$/svx_unopracc.obj	\
        $(OBJ)$/svx_unoedprx.obj	\
        $(OBJ)$/svx_unoviwed.obj	\
        $(OBJ)$/svx_unoviwou.obj	\
        $(OBJ)$/svx_unofored.obj	\
        $(OBJ)$/svx_unoforou.obj	\
        $(OBJ)$/svx_unotext.obj		\
        $(OBJ)$/svx_unotext2.obj	\
        $(OBJ)$/svx_unofield.obj

SLOFILES =	\
        $(SLO)$/svx_UnoForbiddenCharsTable.obj \
        $(SLO)$/svx_unoedsrc.obj	\
        $(SLO)$/svx_unoedhlp.obj	\
        $(SLO)$/svx_unopracc.obj	\
        $(SLO)$/svx_unoedprx.obj	\
        $(SLO)$/svx_unoviwed.obj	\
        $(SLO)$/svx_unoviwou.obj	\
        $(SLO)$/svx_unofored.obj	\
        $(SLO)$/svx_unoforou.obj	\
        $(SLO)$/svx_unotext.obj		\
        $(SLO)$/svx_unotext2.obj	\
        $(SLO)$/svx_unofield.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

