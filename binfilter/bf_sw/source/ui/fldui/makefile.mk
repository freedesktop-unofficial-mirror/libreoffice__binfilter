#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.1.1.1 $
#
#   last change: $Author: hjs $ $Date: 2003-10-01 12:20:06 $
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

PRJNAME=bf_sw
TARGET=sw_fldui

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
        sw_changedb.cxx \
        sw_DropDownFieldDialog.cxx\
        sw_flddb.cxx \
        sw_flddinf.cxx \
        sw_flddok.cxx \
        sw_fldedt.cxx \
        sw_fldfunc.cxx \
        sw_fldmgr.cxx \
        sw_fldpage.cxx \
        sw_fldref.cxx \
        sw_fldtdlg.cxx \
        sw_fldvar.cxx \
        sw_javaedit.cxx \
        sw_inpdlg.cxx \
        sw_xfldui.cxx

SRS1NAME=$(TARGET)
SRC1FILES =  \
        sw_changedb.src \
        sw_DropDownFieldDialog.src\
        sw_flddb.src \
        sw_flddinf.src \
        sw_flddok.src \
        sw_fldfunc.src \
        sw_fldref.src \
        sw_fldtdlg.src \
        sw_fldui.src \
        sw_fldvar.src \
        sw_javaedit.src \
        sw_inpdlg.src

SLOFILES =  \
        $(SLO)$/sw_changedb.obj \
        $(SLO)$/sw_DropDownFieldDialog.obj \
        $(SLO)$/sw_flddb.obj \
        $(SLO)$/sw_flddinf.obj \
        $(SLO)$/sw_flddok.obj \
        $(SLO)$/sw_fldedt.obj \
        $(SLO)$/sw_fldfunc.obj \
        $(SLO)$/sw_fldmgr.obj \
        $(SLO)$/sw_fldpage.obj \
        $(SLO)$/sw_fldref.obj \
        $(SLO)$/sw_fldtdlg.obj \
        $(SLO)$/sw_fldvar.obj \
        $(SLO)$/sw_javaedit.obj \
        $(SLO)$/sw_inpdlg.obj \
        $(SLO)$/sw_xfldui.obj

EXCEPTIONSFILES =  \
        $(SLO)$/sw_xfldui.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

