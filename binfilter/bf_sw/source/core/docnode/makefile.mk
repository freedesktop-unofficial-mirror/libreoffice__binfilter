#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.6 $
#
#   last change: $Author: rt $ $Date: 2006-07-25 08:24:47 $
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
TARGET=sw_docnode

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :	$(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :	settings.mk
.INCLUDE :	$(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw
.IF "$(GUI)$(COM)" == "WINMSC"
LIBFLAGS=/NOI /NOE /PAGE:512
.ENDIF


# --- Files --------------------------------------------------------

CXXFILES = \
        sw_ndindex.cxx \
        sw_ndcopy.cxx \
        sw_ndnotxt.cxx \
        sw_ndnum.cxx \
        sw_ndsect.cxx \
        sw_ndtbl.cxx \
        sw_ndtbl1.cxx \
        sw_node.cxx \
        sw_node2lay.cxx \
        sw_nodes.cxx \
        sw_section.cxx \
        sw_swbaslnk.cxx



SLOFILES =	\
        $(SLO)$/sw_ndindex.obj \
        $(SLO)$/sw_ndcopy.obj \
        $(SLO)$/sw_ndnotxt.obj \
        $(SLO)$/sw_ndnum.obj \
        $(SLO)$/sw_ndsect.obj \
        $(SLO)$/sw_ndtbl.obj \
        $(SLO)$/sw_ndtbl1.obj \
        $(SLO)$/sw_node.obj \
        $(SLO)$/sw_node2lay.obj \
        $(SLO)$/sw_nodes.obj \
        $(SLO)$/sw_section.obj \
        $(SLO)$/sw_swbaslnk.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :	target.mk

