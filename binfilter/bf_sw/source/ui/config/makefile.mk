#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: aw $ $Date: 2003-10-09 14:15:07 $
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
TARGET=sw_config

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
        sw_barcfg.cxx \
        sw_caption.cxx \
        sw_cfgitems.cxx \
        sw_dbconfig.cxx \
        sw_fontcfg.cxx \
        sw_modcfg.cxx \
        sw_optload.cxx \
        sw_optpage.cxx \
        sw_prtopt.cxx \
        sw_uinums.cxx \
        sw_usrpref.cxx \
        sw_viewopt.cxx \
        sw_swlinguconfig.cxx

SRS1NAME=$(TARGET)
SRC1FILES =	\
        sw_optdlg.src \
        sw_optload.src \
        sw_redlopt.src

SLOFILES =	\
        $(SLO)$/sw_barcfg.obj \
        $(SLO)$/sw_caption.obj \
        $(SLO)$/sw_cfgitems.obj \
        $(SLO)$/sw_dbconfig.obj \
        $(SLO)$/sw_fontcfg.obj \
        $(SLO)$/sw_modcfg.obj \
        $(SLO)$/sw_optload.obj \
        $(SLO)$/sw_optpage.obj \
        $(SLO)$/sw_prtopt.obj \
        $(SLO)$/sw_uinums.obj \
        $(SLO)$/sw_usrpref.obj \
        $(SLO)$/sw_viewopt.obj \
        $(SLO)$/sw_swlinguconfig.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

