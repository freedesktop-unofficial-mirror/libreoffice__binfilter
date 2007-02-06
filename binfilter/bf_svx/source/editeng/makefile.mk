#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.9 $
#
#   last change: $Author: vg $ $Date: 2007-02-06 12:48:46 $
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
TARGET=svx_editeng

NO_HIDS=TRUE

PROJECTPCH4DLL=TRUE
PROJECTPCH=eeng_pch
PROJECTPCHSOURCE=svx_eeng_pch

ENABLE_EXCEPTIONS=TRUE


# --- Settings -----------------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Allgemein ----------------------------------------------------------

.IF "$(editdebug)" != "" || "$(EDITDEBUG)" != ""
CDEFS+=-DEDITDEBUG
.ENDIF

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

SRS1NAME=$(TARGET)
SRC1FILES=	svx_editeng.src

EXCEPTIONSFILES= \
    $(SLO)$/svx_unolingu.obj

.INCLUDE :  target.mk

