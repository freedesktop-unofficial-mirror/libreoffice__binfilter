#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.4 $
#
#   last change: $Author: hr $ $Date: 2004-08-03 15:32:49 $
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
TARGET=svx_editeng

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

AUTOSEG=true

PROJECTPCH4DLL=TRUE
PROJECTPCH=eeng_pch
PROJECTPCHSOURCE=svx_eeng_pch

ENABLE_EXCEPTIONS=TRUE


# --- Settings -----------------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Allgemein ----------------------------------------------------------

.IF "$(editdebug)" != "" || "$(EDITDEBUG)" != ""
CDEFS+=-DEDITDEBUG
.ENDIF

.IF "$(header)" == ""

#SLOFILES =	\
#			$(SLO)$/svx_txtrange.obj \
#			$(SLO)$/svx_svxacorr.obj \
#			$(SLO)$/svx_SvXMLAutoCorrectImport.obj \
#			$(SLO)$/svx_SvXMLAutoCorrectExport.obj \
#			$(SLO)$/svx_forbiddencharacterstable.obj \
#			$(SLO)$/svx_swafopt.obj \
#			$(SLO)$/svx_editattr.obj \
#			$(SLO)$/svx_editdbg.obj	\
#			$(SLO)$/svx_editdoc.obj	\
#			$(SLO)$/svx_editdoc2.obj \
#			$(SLO)$/svx_editeng.obj	\
#			$(SLO)$/svx_editobj.obj	\
#			$(SLO)$/svx_editsel.obj	\
#			$(SLO)$/svx_editundo.obj \
#			$(SLO)$/svx_editview.obj  \
#			$(SLO)$/svx_edtspell.obj \
#			$(SLO)$/svx_eehtml.obj \
#			$(SLO)$/svx_eerdll.obj	\
#			$(SLO)$/svx_eeobj.obj \
#			$(SLO)$/svx_eertfpar.obj \
#			$(SLO)$/svx_impedit.obj	\
#			$(SLO)$/svx_impedit2.obj \
#			$(SLO)$/svx_impedit3.obj \
#			$(SLO)$/svx_impedit4.obj \
#			$(SLO)$/svx_impedit5.obj \
#			$(SLO)$/svx_unolingu.obj

SLOFILES =	\
            $(SLO)$/svx_txtrange.obj \
            $(SLO)$/svx_svxacorr.obj \
            $(SLO)$/svx_SvXMLAutoCorrectImport.obj \
            $(SLO)$/svx_forbiddencharacterstable.obj \
            $(SLO)$/svx_swafopt.obj \
            $(SLO)$/svx_editattr.obj \
            $(SLO)$/svx_editdbg.obj	\
            $(SLO)$/svx_editdoc.obj	\
            $(SLO)$/svx_editdoc2.obj \
            $(SLO)$/svx_editeng.obj	\
            $(SLO)$/svx_editobj.obj	\
            $(SLO)$/svx_editsel.obj	\
            $(SLO)$/svx_editundo.obj \
            $(SLO)$/svx_edtspell.obj \
            $(SLO)$/svx_editview.obj  \
            $(SLO)$/svx_eerdll.obj	\
            $(SLO)$/svx_impedit.obj	\
            $(SLO)$/svx_impedit2.obj \
            $(SLO)$/svx_impedit3.obj \
            $(SLO)$/svx_impedit4.obj \
            $(SLO)$/svx_impedit5.obj \
            $(SLO)$/svx_unolingu.obj
#SVXLIGHTOBJFILES= \
#			$(OBJ)$/svx_txtrange.obj \
#			$(OBJ)$/svx_swafopt.obj \
#			$(OBJ)$/svx_editattr.obj \
#			$(OBJ)$/svx_editdbg.obj	\
#			$(OBJ)$/svx_editdoc.obj	\
#			$(OBJ)$/svx_editdoc2.obj \
#			$(OBJ)$/svx_editeng.obj	\
#			$(OBJ)$/svx_editobj.obj	\
#			$(OBJ)$/svx_editsel.obj	\
#			$(OBJ)$/svx_editview.obj  \
#			$(OBJ)$/svx_eerdll.obj	\
#			$(OBJ)$/svx_impedit.obj	\
#			$(OBJ)$/svx_impedit2.obj \
#            $(OBJ)$/svx_impedit3.obj \
#			$(OBJ)$/svx_impedit4.obj \
#			$(OBJ)$/svx_impedit5.obj \
#			$(OBJ)$/svx_forbiddencharacterstable.obj \
#			$(OBJ)$/svx_unolingu.obj

SVXLIGHTOBJFILES= \
            $(OBJ)$/svx_txtrange.obj \
            $(OBJ)$/svx_swafopt.obj \
            $(OBJ)$/svx_editattr.obj \
            $(OBJ)$/svx_editdbg.obj	\
            $(OBJ)$/svx_editdoc.obj	\
            $(OBJ)$/svx_editdoc2.obj \
            $(OBJ)$/svx_editeng.obj	\
            $(OBJ)$/svx_editobj.obj	\
            $(OBJ)$/svx_editsel.obj	\
            $(OBJ)$/svx_editview.obj  \
            $(OBJ)$/svx_eerdll.obj	\
            $(OBJ)$/svx_impedit.obj	\
            $(OBJ)$/svx_impedit2.obj \
            $(OBJ)$/svx_impedit3.obj \
            $(OBJ)$/svx_impedit4.obj \
            $(OBJ)$/svx_impedit5.obj \
            $(OBJ)$/svx_forbiddencharacterstable.obj \
            $(OBJ)$/svx_unolingu.obj
.ENDIF

SRS1NAME=$(TARGET)
SRC1FILES=	svx_editeng.src

EXCEPTIONSFILES= \
    $(SLO)$/svx_unolingu.obj

.IF "$(SVXLIGHT)"!=""
EXCEPTIONSFILES+= \
    $(OBJ)$/svx_sxl_unolingu.obj
.ENDIF          # "$(SVXLIGHT)"!=""

.INCLUDE :  target.mk

