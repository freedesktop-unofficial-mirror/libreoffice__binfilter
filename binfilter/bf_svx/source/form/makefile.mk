#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.3 $
#
#   last change: $Author: aw $ $Date: 2003-11-18 19:23:57 $
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

PRJ=..$/..$/..
BFPRJ=..$/..

PRJNAME=binfilter
TARGET=svx_form

#GEN_HID=TRUE
#GEN_HID_OTHER=TRUE
NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Files --------------------------------------------------------

#IMGLST_SRS=$(SRS)$/form.srs
BMP_IN=$(BFPRJ)$/win$/res

SRS1NAME=svx_form
SRC1FILES= \
    svx_fmexpl.src 		\
    svx_filtnav.src		\
    svx_taborder.src 	\
    svx_fmstring.src 	\
    svx_tbxform.src		\
    svx_fmsearch.src


SLOFILES = \
    $(SLO)$/svx_dbcharsethelper.obj			\
    $(SLO)$/svx_ParseContext.obj			\
    $(SLO)$/svx_typeconversionclient.obj    \
    $(SLO)$/svx_confirmdelete.obj      \
    $(SLO)$/svx_dbtoolsclient.obj      \
    $(SLO)$/svx_sqlparserclient.obj      \
    $(SLO)$/svx_dataaccessdescriptor.obj      \
    $(SLO)$/svx_fmpage.obj      \
    $(SLO)$/svx_fmPropBrw.obj			\
    $(SLO)$/svx_fmundo.obj  	\
    $(SLO)$/svx_fmprop.obj      \
    $(SLO)$/svx_fmmodel.obj		\
    $(SLO)$/svx_navigatortree.obj      \
    $(SLO)$/svx_navigatortreemodel.obj      \
    $(SLO)$/svx_fmexpl.obj      \
    $(SLO)$/svx_fmctrler.obj    \
    $(SLO)$/svx_fmpgeimp.obj	\
    $(SLO)$/svx_fmvwimp.obj     \
    $(SLO)$/svx_taborder.obj    \
    $(SLO)$/svx_fmdpage.obj		\
    $(SLO)$/svx_fmitems.obj  	\
    $(SLO)$/svx_tbxform.obj     \
    $(SLO)$/svx_fmobj.obj      	\
    $(SLO)$/svx_fmdmod.obj		\
    $(SLO)$/svx_fmobjfac.obj	\
    $(SLO)$/svx_fmsrccfg.obj	\
    $(SLO)$/svx_fmservs.obj     \
    $(SLO)$/svx_typemap.obj		\
    $(SLO)$/svx_fmexch.obj      \
    $(SLO)$/svx_tabwin.obj      \
    $(SLO)$/svx_multipro.obj	\
    $(SLO)$/svx_fmurl.obj		\
    $(SLO)$/svx_filtnav.obj		\
    $(SLO)$/svx_fmimplids.obj   \
    $(SLO)$/svx_fmtools.obj     \
    $(SLO)$/svx_fmshimp.obj     \
    $(SLO)$/svx_fmshell.obj     \
    $(SLO)$/svx_fmsearch.obj	\
    $(SLO)$/svx_fmsrcimp.obj	\
    $(SLO)$/svx_fmview.obj		\
    $(SLO)$/svx_siimport.obj	\
    $(SLO)$/svx_sdbdatacolumn.obj

.IF "$(OS)$(CPU)"=="SOLARISI" 
NOOPTFILES=$(SLO)$/svx_fmprop.obj
.ENDIF

SVXLIGHTOBJFILES= \
    $(OBJ)$/svx_fmpage.obj      \
    $(OBJ)$/svx_fmmodel.obj

.INCLUDE :  target.mk
