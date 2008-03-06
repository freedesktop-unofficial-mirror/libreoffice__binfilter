#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.8 $
#
#   last change: $Author: kz $ $Date: 2008-03-06 14:49:57 $
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
PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PRJNAME=binfilter
TARGET=sc_unoobj

NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  scpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sc.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sc
# --- Files --------------------------------------------------------

SLOFILES =  \
        $(SLO)$/sc_docuno.obj \
        $(SLO)$/sc_servuno.obj \
        $(SLO)$/sc_defltuno.obj \
        $(SLO)$/sc_drdefuno.obj \
        $(SLO)$/sc_cellsuno.obj \
        $(SLO)$/sc_textuno.obj \
        $(SLO)$/sc_notesuno.obj \
        $(SLO)$/sc_cursuno.obj \
        $(SLO)$/sc_fielduno.obj \
        $(SLO)$/sc_miscuno.obj \
        $(SLO)$/sc_optuno.obj \
        $(SLO)$/sc_appluno.obj \
        $(SLO)$/sc_funcuno.obj \
        $(SLO)$/sc_nameuno.obj \
        $(SLO)$/sc_datauno.obj \
        $(SLO)$/sc_dapiuno.obj \
        $(SLO)$/sc_chartuno.obj \
        $(SLO)$/sc_shapeuno.obj \
        $(SLO)$/sc_pageuno.obj \
        $(SLO)$/sc_forbiuno.obj \
        $(SLO)$/sc_styleuno.obj \
        $(SLO)$/sc_afmtuno.obj \
        $(SLO)$/sc_fmtuno.obj \
        $(SLO)$/sc_linkuno.obj \
        $(SLO)$/sc_targuno.obj \
        $(SLO)$/sc_convuno.obj \
        $(SLO)$/sc_editsrc.obj \
        $(SLO)$/sc_unoguard.obj \
        $(SLO)$/sc_confuno.obj \
        $(SLO)$/sc_filtuno.obj \
        $(SLO)$/sc_unodoc.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

