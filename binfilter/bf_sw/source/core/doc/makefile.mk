#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.8 $
#
#   last change: $Author: obo $ $Date: 2007-07-17 11:59:39 $
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
TARGET=sw_doc

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

SLOFILES =	\
        $(SLO)$/sw_SwStyleNameMapper.obj \
        $(SLO)$/sw_doc.obj \
        $(SLO)$/sw_docbm.obj \
        $(SLO)$/sw_docchart.obj \
        $(SLO)$/sw_doccorr.obj \
        $(SLO)$/sw_docdde.obj \
        $(SLO)$/sw_docdesc.obj \
        $(SLO)$/sw_docdraw.obj \
        $(SLO)$/sw_docedt.obj \
        $(SLO)$/sw_docfld.obj \
        $(SLO)$/sw_docfly.obj \
        $(SLO)$/sw_docfmt.obj \
        $(SLO)$/sw_docftn.obj \
        $(SLO)$/sw_doclay.obj \
        $(SLO)$/sw_docglos.obj \
        $(SLO)$/sw_docnew.obj \
        $(SLO)$/sw_docnum.obj \
        $(SLO)$/sw_docredln.obj \
        $(SLO)$/sw_docruby.obj \
        $(SLO)$/sw_docsort.obj \
        $(SLO)$/sw_docstat.obj \
        $(SLO)$/sw_doctxm.obj \
        $(SLO)$/sw_extinput.obj \
        $(SLO)$/sw_fmtcol.obj \
        $(SLO)$/sw_ftnidx.obj \
        $(SLO)$/sw_gctable.obj \
        $(SLO)$/sw_lineinfo.obj \
        $(SLO)$/sw_notxtfrm.obj \
        $(SLO)$/sw_number.obj \
        $(SLO)$/sw_poolfmt.obj \
        $(SLO)$/sw_sortopt.obj \
        $(SLO)$/sw_swserv.obj \
        $(SLO)$/sw_swtable.obj \
        $(SLO)$/sw_tblafmt.obj \
        $(SLO)$/sw_tblrwcl.obj \
        $(SLO)$/sw_visiturl.obj \
        $(SLO)$/sw_htmltbl.obj

.IF "$(OS)$(CVER)"=="MACOSXC295"
SLOFILES += $(SLO)$/sw_gcc_outl.obj
.ENDIF

# --- Tagets -------------------------------------------------------

.INCLUDE :	target.mk

