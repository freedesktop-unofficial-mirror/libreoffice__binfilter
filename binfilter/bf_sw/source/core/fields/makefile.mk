#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.7 $
#
#   last change: $Author: obo $ $Date: 2007-03-09 16:37:25 $
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
TARGET=sw_fields

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw
# --- Files --------------------------------------------------------

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
        $(SLO)$/sw_scrptfld.obj \
        $(SLO)$/sw_macrofld.obj \
        $(SLO)$/sw_reffld.obj \
        $(SLO)$/sw_tblcalc.obj \
        $(SLO)$/sw_usrfld.obj


# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

