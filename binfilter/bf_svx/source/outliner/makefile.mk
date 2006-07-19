#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: kz $ $Date: 2006-07-19 13:37:27 $
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
TARGET=svx_outliner

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

AUTOSEG=true

PROJECTPCH4DLL=TRUE
PROJECTPCH=outl_pch
PROJECTPCHSOURCE=svx_outl_pch


# --- Settings -----------------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Allgemein ----------------------------------------------------------

.IF "$(header)" == ""

#CXXFILES=	\
#			outlundo.cxx	\
#			outliner.cxx	\
#			outlin2.cxx		\
#			paralist.cxx	\
#			outlobj.cxx 	\
#			outlvw.cxx		\
#			outleeng.cxx	\
#			outl_pch.cxx

CXXFILES=	\
            svx_outliner.cxx	\
            svx_outlin2.cxx		\
            svx_paralist.cxx	\
            svx_outlobj.cxx 	\
            svx_outlvw.cxx		\
            svx_outleeng.cxx	\
            svx_outl_pch.cxx
            
#SLOFILES=	\
#			$(SLO)$/svx_outlundo.obj	\
#			$(SLO)$/svx_outliner.obj 	\
#			$(SLO)$/svx_outlin2.obj		\
#			$(SLO)$/svx_paralist.obj 	\
#			$(SLO)$/svx_outlvw.obj 		\
#			$(SLO)$/svx_outleeng.obj 	\
#			$(SLO)$/svx_outlobj.obj

SLOFILES=	\
            $(SLO)$/svx_outliner.obj 	\
            $(SLO)$/svx_outlin2.obj		\
            $(SLO)$/svx_paralist.obj 	\
            $(SLO)$/svx_outlvw.obj 		\
            $(SLO)$/svx_outleeng.obj 	\
            $(SLO)$/svx_outlobj.obj
            
SVXLIGHTOBJFILES= \
            $(OBJ)$/svx_outliner.obj 	\
            $(OBJ)$/svx_outlin2.obj		\
            $(OBJ)$/svx_paralist.obj 	\
            $(OBJ)$/svx_outlvw.obj 		\
            $(OBJ)$/svx_outleeng.obj 	\
            $(OBJ)$/svx_outlobj.obj

.ENDIF

SRS1NAME=$(TARGET)
SRC1FILES=	svx_outliner.src

.INCLUDE :  target.mk
