#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: aw $ $Date: 2003-10-09 14:14:39 $
#
#   The Contents of this file are made available subject to the terms of
#   either of the following licenses
#
#          - GNU Lesser General Public License Version 2.1
#          - Sun Industry Standards Source License Version 1.1
#
#   Sun Microsystems Inc., October, 2000
#
#   GNU Lesser General Public License Version 2.1
#   =============================================
#   Copyright 2000 by Sun Microsystems, Inc.
#   901 San Antonio Road, Palo Alto, CA 94303, USA
#
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU Lesser General Public
#   License version 2.1, as published by the Free Software Foundation.
#
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with this library; if not, write to the Free Software
#   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#   MA  02111-1307  USA
#
#
#   Sun Industry Standards Source License Version 1.1
#   =================================================
#   The contents of this file are subject to the Sun Industry Standards
#   Source License Version 1.1 (the "License"); You may not use this file
#   except in compliance with the License. You may obtain a copy of the
#   License at http://www.openoffice.org/license.html.
#
#   Software provided under this License is provided on an "AS IS" basis,
#   WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
#   WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
#   MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
#   See the License for the specific provisions governing your rights and
#   obligations concerning the Software.
#
#   The Initial Developer of the Original Code is: Sun Microsystems, Inc.
#
#   Copyright: 2000 by Sun Microsystems, Inc.
#
#   All Rights Reserved.
#
#   Contributor(s): _______________________________________
#
#
#
#*************************************************************************

PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PRJNAME=binfilter
TARGET=sw_fields

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

