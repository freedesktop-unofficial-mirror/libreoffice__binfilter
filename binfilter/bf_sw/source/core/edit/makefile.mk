#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.7 $
#
#   last change: $Author: hr $ $Date: 2007-01-02 17:47:31 $
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
TARGET=sw_edit

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :	$(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :	settings.mk
.INCLUDE :	$(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw
# --- Files --------------------------------------------------------

CXXFILES = \
        sw_acorrect.cxx \
        sw_autofmt.cxx \
        sw_edatmisc.cxx \
        sw_edattr.cxx \
        sw_eddel.cxx \
        sw_edfcol.cxx \
        sw_edfld.cxx \
        sw_edfmt.cxx \
        sw_edglbldc.cxx \
        sw_edglss.cxx \
        sw_editsh.cxx \
        sw_ednumber.cxx \
        sw_edredln.cxx \
        sw_edtab.cxx \
        sw_edtox.cxx \
        sw_edundo.cxx \
        sw_edws.cxx \
        sw_edsect.cxx



SLOFILES =	\
        $(SLO)$/sw_acorrect.obj \
        $(SLO)$/sw_autofmt.obj \
        $(SLO)$/sw_edatmisc.obj \
        $(SLO)$/sw_edattr.obj \
        $(SLO)$/sw_eddel.obj \
        $(SLO)$/sw_edfcol.obj \
        $(SLO)$/sw_edfld.obj \
        $(SLO)$/sw_edfmt.obj \
        $(SLO)$/sw_edglbldc.obj \
        $(SLO)$/sw_edglss.obj \
        $(SLO)$/sw_editsh.obj \
        $(SLO)$/sw_ednumber.obj \
        $(SLO)$/sw_edredln.obj \
        $(SLO)$/sw_edtab.obj \
        $(SLO)$/sw_edtox.obj \
        $(SLO)$/sw_edundo.obj \
        $(SLO)$/sw_edws.obj \
        $(SLO)$/sw_edsect.obj

# --- Targets -------------------------------------------------------

.INCLUDE :	target.mk

