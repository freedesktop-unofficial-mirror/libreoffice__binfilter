#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.7 $
#
#   last change: $Author: kz $ $Date: 2006-11-08 13:00:15 $
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
TARGET=sw_unoidl

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE
ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

#.INCLUDE :  $(PRJ)$/inc$/swpre.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
#.INCLUDE :  $(PRJ)$/inc$/sw.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw
# --- Files --------------------------------------------------------

SLOFILES =  \
        $(SLO)$/sw_dlelstnr.obj \
        $(SLO)$/sw_RefreshListenerContainer.obj \
        $(SLO)$/sw_SwXDocumentSettings.obj \
        $(SLO)$/sw_SwXFilterOptions.obj\
        $(SLO)$/sw_SwXPrintPreviewSettings.obj \
        $(SLO)$/sw_unoatxt.obj \
        $(SLO)$/sw_unodefaults.obj\
        $(SLO)$/sw_unodoc.obj     \
        $(SLO)$/sw_unofreg.obj \
        $(SLO)$/sw_unomod.obj \
        $(SLO)$/sw_unotxdoc.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

