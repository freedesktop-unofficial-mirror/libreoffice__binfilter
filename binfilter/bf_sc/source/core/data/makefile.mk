#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.4 $
#
#   last change: $Author: rt $ $Date: 2005-09-07 16:38:05 $
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

PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PRJNAME=binfilter
TARGET=sc_data

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

PROJECTPCH4DLL=TRUE
PROJECTPCH=core_pch
PROJECTPCHSOURCE=..\pch\sc_core_pch

AUTOSEG=true

# --- Settings -----------------------------------------------------

.INCLUDE :  scpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sc.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sc
# --- Files --------------------------------------------------------

CXXFILES = \
    sc_bclist.cxx \
    sc_bcaslot.cxx \
    sc_docpool.cxx \
    sc_poolhelp.cxx \
    sc_column.cxx \
    sc_column2.cxx \
    sc_column3.cxx \
    sc_document.cxx \
    sc_documen2.cxx \
    sc_documen3.cxx \
    sc_documen4.cxx \
    sc_documen5.cxx \
    sc_documen6.cxx \
    sc_documen7.cxx \
    sc_documen8.cxx \
    sc_documen9.cxx \
    sc_fillinfo.cxx \
    sc_table1.cxx \
    sc_table2.cxx \
    sc_table3.cxx \
    sc_table4.cxx \
    sc_table5.cxx \
    sc_table6.cxx \
    sc_olinetab.cxx \
    sc_patattr.cxx \
    sc_cell.cxx \
    sc_cell2.cxx \
    sc_attarray.cxx \
    sc_attrib.cxx \
    sc_global.cxx \
    sc_global2.cxx \
    sc_globalx.cxx \
    sc_markarr.cxx \
    sc_markdata.cxx \
    sc_dociter.cxx \
    sc_drwlayer.cxx \
    sc_userdat.cxx \
    sc_drawpage.cxx \
    sc_stlsheet.cxx \
    sc_stlpool.cxx \
    sc_dptabsrc.cxx \
    sc_dptabres.cxx \
    sc_dptabdat.cxx \
    sc_dpshttab.cxx \
    sc_dpsdbtab.cxx \
    sc_dpoutput.cxx \
    sc_dpobject.cxx \
    sc_dpsave.cxx \
    sc_pivot.cxx \
    sc_pivot2.cxx \
    sc_dbdocutl.cxx \
    sc_pagepar.cxx \
    sc_conditio.cxx \
    sc_validat.cxx \
    sc_scimpexpmsg.cxx \
    sc_sortparam.cxx

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
    $(SLO)$/sc_table6.obj \
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
    $(SLO)$/sc_dptabres.obj \
    $(SLO)$/sc_dptabdat.obj \
    $(SLO)$/sc_dpshttab.obj \
    $(SLO)$/sc_dpsdbtab.obj \
    $(SLO)$/sc_dpoutput.obj \
    $(SLO)$/sc_dpobject.obj \
    $(SLO)$/sc_dpsave.obj \
    $(SLO)$/sc_pivot.obj \
    $(SLO)$/sc_pivot2.obj \
    $(SLO)$/sc_dbdocutl.obj \
    $(SLO)$/sc_pagepar.obj \
    $(SLO)$/sc_conditio.obj \
    $(SLO)$/sc_validat.obj \
    $(SLO)$/sc_scimpexpmsg.obj \
    $(SLO)$/sc_sortparam.obj

EXCEPTIONSFILES= \
    $(SLO)$/sc_documen6.obj \
    $(SLO)$/sc_dpsdbtab.obj \
    $(SLO)$/sc_dpobject.obj \
    $(SLO)$/sc_dpoutput.obj \
    $(SLO)$/sc_dpsave.obj	\
    $(SLO)$/sc_dbdocutl.obj \
        $(SLO)$/sc_dptabsrc.obj \
    $(SLO)$/sc_globalx.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

