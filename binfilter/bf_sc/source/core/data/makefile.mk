#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.9 $
#
#   last change: $Author: obo $ $Date: 2007-07-17 09:11:11 $
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
TARGET=sc_data

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  scpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sc.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sc
# --- Files --------------------------------------------------------

SLOFILES =  \
    $(SLO)$/sc_bclist.obj \
    $(SLO)$/sc_bcaslot.obj \
    $(SLO)$/sc_docpool.obj \
    $(SLO)$/sc_poolhelp.obj \
    $(SLO)$/sc_column.obj \
    $(SLO)$/sc_column2.obj \
    $(SLO)$/sc_column3.obj \
    $(SLO)$/sc_document.obj \
    $(SLO)$/sc_documen2.obj \
    $(SLO)$/sc_documen3.obj \
    $(SLO)$/sc_documen4.obj \
    $(SLO)$/sc_documen5.obj \
    $(SLO)$/sc_documen6.obj \
    $(SLO)$/sc_documen7.obj \
    $(SLO)$/sc_documen8.obj \
    $(SLO)$/sc_documen9.obj \
    $(SLO)$/sc_fillinfo.obj \
    $(SLO)$/sc_table1.obj \
    $(SLO)$/sc_table2.obj \
    $(SLO)$/sc_table3.obj \
    $(SLO)$/sc_table4.obj \
    $(SLO)$/sc_table5.obj \
    $(SLO)$/sc_olinetab.obj \
    $(SLO)$/sc_patattr.obj \
    $(SLO)$/sc_cell.obj \
    $(SLO)$/sc_cell2.obj \
    $(SLO)$/sc_attarray.obj \
    $(SLO)$/sc_attrib.obj \
    $(SLO)$/sc_global.obj \
    $(SLO)$/sc_global2.obj \
    $(SLO)$/sc_globalx.obj \
    $(SLO)$/sc_markarr.obj \
    $(SLO)$/sc_markdata.obj \
    $(SLO)$/sc_dociter.obj \
    $(SLO)$/sc_drwlayer.obj \
    $(SLO)$/sc_userdat.obj \
    $(SLO)$/sc_drawpage.obj \
    $(SLO)$/sc_stlsheet.obj \
    $(SLO)$/sc_stlpool.obj \
    $(SLO)$/sc_dptabsrc.obj \
    $(SLO)$/sc_dptabdat.obj \
    $(SLO)$/sc_dpshttab.obj \
    $(SLO)$/sc_dpoutput.obj \
    $(SLO)$/sc_dpobject.obj \
    $(SLO)$/sc_dpsave.obj \
    $(SLO)$/sc_pivot.obj \
    $(SLO)$/sc_pivot2.obj \
    $(SLO)$/sc_dbdocutl.obj \
    $(SLO)$/sc_pagepar.obj \
    $(SLO)$/sc_conditio.obj \
    $(SLO)$/sc_validat.obj \
    $(SLO)$/sc_sortparam.obj

EXCEPTIONSFILES= \
    $(SLO)$/sc_documen6.obj \
    $(SLO)$/sc_dpobject.obj \
    $(SLO)$/sc_dpoutput.obj \
    $(SLO)$/sc_dpsave.obj	\
    $(SLO)$/sc_dbdocutl.obj \
    $(SLO)$/sc_dptabsrc.obj \
    $(SLO)$/sc_globalx.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

