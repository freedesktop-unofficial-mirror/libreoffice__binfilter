#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.8 $
#
#   last change: $Author: hr $ $Date: 2007-01-02 17:14:59 $
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
TARGET=sfx2_doc

NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk

# --- Settings -----------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
INC+= -I$(PRJ)$/inc$/bf_sfx2

# --- Files --------------------------------------------------------

SRS1NAME=$(TARGET)
SRC1FILES = \
        sfx2_doc.src sfx2_doctempl.src sfx2_sfxbasemodel.src

SLOFILES =	\
        $(SLO)$/sfx2_docfile.obj \
        $(SLO)$/sfx2_objuno.obj \
        $(SLO)$/sfx2_frmdescr.obj \
        $(SLO)$/sfx2_fsetobsh.obj \
        $(SLO)$/sfx2_docinf.obj \
        $(SLO)$/sfx2_interno.obj \
        $(SLO)$/sfx2_objxtor.obj \
        $(SLO)$/sfx2_objmisc.obj \
        $(SLO)$/sfx2_objstor.obj \
        $(SLO)$/sfx2_objsys.obj \
        $(SLO)$/sfx2_objcont.obj \
        $(SLO)$/sfx2_objserv.obj \
        $(SLO)$/sfx2_objitem.obj \
        $(SLO)$/sfx2_clientsh.obj \
        $(SLO)$/sfx2_docfac.obj \
        $(SLO)$/sfx2_docfilt.obj \
        $(SLO)$/sfx2_doctempl.obj \
        $(SLO)$/sfx2_doctemplates.obj \
        $(SLO)$/sfx2_frameobj.obj \
        $(SLO)$/sfx2_sfxbasemodel.obj \
        $(SLO)$/sfx2_xmlversion.obj

EXCEPTIONSFILES=$(SLO)$/sfx2_objuno.obj \
                $(SLO)$/sfx2_objcont.obj \
        $(SLO)$/sfx2_docfac.obj \
        $(SLO)$/sfx2_docfile.obj \
        $(SLO)$/sfx2_doctempl.obj \
        $(SLO)$/sfx2_doctemplates.obj \
        $(SLO)$/sfx2_sfxbasemodel.obj \
        $(SLO)$/sfx2_objxtor.obj \
        $(SLO)$/sfx2_objstor.obj \
        $(SLO)$/sfx2_xmlversion.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk







