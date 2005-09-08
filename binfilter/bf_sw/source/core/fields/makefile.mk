#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.4 $
#
#   last change: $Author: rt $ $Date: 2005-09-08 09:05:56 $
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
TARGET=sw_fields

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

AUTOSEG=true

# --- Settings -----------------------------------------------------

#.INCLUDE :  $(PRJ)$/inc$/swpre.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
#.INCLUDE :  $(PRJ)$/inc$/sw.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw
# --- Files --------------------------------------------------------

CXXFILES = \
        sw_authfld.cxx \
        sw_cellfml.cxx \
        sw_chpfld.cxx \
        sw_dbfld.cxx \
        sw_ddefld.cxx \
        sw_ddetbl.cxx \
        sw_docufld.cxx \
        sw_expfld.cxx \
        sw_fldbas.cxx \
        sw_flddat.cxx \
        sw_flddropdown.cxx \
        sw_scrptfld.cxx \
        sw_macrofld.cxx \
        sw_fldlst.cxx \
        sw_reffld.cxx \
        sw_tblcalc.cxx \
        sw_usrfld.cxx



SLOFILES =	\
        $(SLO)$/sw_authfld.obj \
        $(SLO)$/sw_cellfml.obj \
        $(SLO)$/sw_chpfld.obj \
        $(SLO)$/sw_dbfld.obj \
        $(SLO)$/sw_ddefld.obj \
        $(SLO)$/sw_ddetbl.obj \
        $(SLO)$/sw_docufld.obj \
        $(SLO)$/sw_expfld.obj \
        $(SLO)$/sw_fldbas.obj \
        $(SLO)$/sw_flddat.obj \
        $(SLO)$/sw_flddropdown.obj \
        $(SLO)$/sw_fldlst.obj \
        $(SLO)$/sw_scrptfld.obj \
        $(SLO)$/sw_macrofld.obj \
        $(SLO)$/sw_reffld.obj \
        $(SLO)$/sw_tblcalc.obj \
        $(SLO)$/sw_usrfld.obj


# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

