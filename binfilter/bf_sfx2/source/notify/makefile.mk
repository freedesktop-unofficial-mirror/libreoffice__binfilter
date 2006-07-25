#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.7 $
#
#   last change: $Author: rt $ $Date: 2006-07-25 08:17:17 $
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
TARGET=sfx2_notify

NO_HIDS=TRUE

.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk

# --- Settings -----------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
INC+= -I$(PRJ)$/inc$/bf_sfx2

# --- Files --------------------------------------------------------

CXXFILES = \
        sfx2_eventsupplier.cxx \
        sfx2_hintpost.cxx \
        sfx2_linkhdl.cxx \
        $(PROJECTPCHSOURCE).cxx

SLOFILES =	\
        $(SLO)$/sfx2_eventsupplier.obj \
        $(SLO)$/sfx2_hintpost.obj \
        $(SLO)$/sfx2_linkhdl.obj

EXCEPTIONSFILES =	\
        $(SLO)$/sfx2_eventsupplier.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

