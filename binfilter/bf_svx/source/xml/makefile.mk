#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: kz $ $Date: 2006-07-19 13:39:17 $
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
TARGET=svx_xml

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE : settings.mk
INC+= -I$(PRJ)$/inc$/bf_svx


# --- Files --------------------------------------------------------
SLOFILES = \
        $(SLO)$/svx_xmlexport.obj		\
        $(SLO)$/svx_xmltxtimp.obj		\
        $(SLO)$/svx_xmltxtexp.obj		\
        $(SLO)$/svx_xmlxtimp.obj		\
        $(SLO)$/svx_xmlxtexp.obj		\
        $(SLO)$/svx_xmlgrhlp.obj		\
        $(SLO)$/svx_xmleohlp.obj		

SVXLIGHTOBJFILES=\
        $(OBJ)$/svx_xmlxtimp.obj		\
        $(OBJ)$/svx_xmlxtexp.obj		\
        $(OBJ)$/svx_xmlgrhlp.obj		\
        $(OBJ)$/svx_xmleohlp.obj		

# --- Targets --------------------------------------------------------------

.INCLUDE : target.mk
