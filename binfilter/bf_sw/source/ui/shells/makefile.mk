#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: aw $ $Date: 2003-10-09 14:15:19 $
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
TARGET=sw_shells

AUTOSEG=true

# --- Settings -----------------------------------------------------

#.INCLUDE :  $(PRJ)$/inc$/swpre.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
#.INCLUDE :  $(PRJ)$/inc$/sw.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw
# --- Files --------------------------------------------------------

SRS1NAME=$(TARGET)
SRC1FILES =  \
        sw_shells.src \
        sw_pseudo.src

SLOFILES =  \
        $(SLO)$/sw_basesh.obj \
        $(SLO)$/sw_beziersh.obj \
        $(SLO)$/sw_drawdlg.obj \
        $(SLO)$/sw_drawsh.obj \
        $(SLO)$/sw_drformsh.obj \
        $(SLO)$/sw_drwbassh.obj \
        $(SLO)$/sw_drwtxtex.obj \
        $(SLO)$/sw_drwtxtsh.obj \
        $(SLO)$/sw_frmsh.obj \
        $(SLO)$/sw_grfsh.obj \
        $(SLO)$/sw_grfshex.obj \
        $(SLO)$/sw_listsh.obj \
        $(SLO)$/sw_olesh.obj \
        $(SLO)$/sw_slotadd.obj \
        $(SLO)$/sw_tabsh.obj \
        $(SLO)$/sw_textdrw.obj \
        $(SLO)$/sw_textfld.obj \
        $(SLO)$/sw_textglos.obj \
        $(SLO)$/sw_textidx.obj \
        $(SLO)$/sw_textsh.obj \
        $(SLO)$/sw_textsh1.obj \
        $(SLO)$/sw_textsh2.obj \
        $(SLO)$/sw_txtattr.obj \
        $(SLO)$/sw_txtcrsr.obj \
        $(SLO)$/sw_txtnum.obj

EXCEPTIONSFILES =  \
        $(SLO)$/sw_textsh2.obj \
        $(SLO)$/sw_grfshex.obj	\
        $(SLO)$/sw_textsh1.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

$(SRS)$/sw_shells.srs: $(PRJ)$/inc$/bf_svx$/globlmn.hrc

