#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.1.1.1 $
#
#   last change: $Author: hjs $ $Date: 2003-10-01 12:19:55 $
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
TARGET=sw_misc

AUTOSEG=true

# --- Settings -----------------------------------------------------

#.INCLUDE :	$(PRJ)$/inc$/swpre.mk
.INCLUDE :	$(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :	settings.mk
#.INCLUDE :	$(PRJ)$/inc$/sw.mk
.INCLUDE :	$(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw
# --- Files --------------------------------------------------------

CXXFILES = \
        sw_bookmark.cxx \
        sw_docfnote.cxx \
        sw_glosbib.cxx \
        sw_glosdoc.cxx \
        sw_glossary.cxx \
        sw_glshell.cxx \
        sw_hdftctrl.cxx \
        sw_insfnote.cxx \
        sw_insrule.cxx \
        sw_linenum.cxx \
        sw_num.cxx \
        sw_numberingtypelistbox.cxx \
        sw_outline.cxx \
        sw_pgfnote.cxx \
        sw_pggrid.cxx \
        sw_redlndlg.cxx \
        sw_srtdlg.cxx

SRS1NAME=$(TARGET)
SRC1FILES=\
    sw_bookmark.src \
    sw_docfnote.src \
    sw_glossary.src \
    sw_glosbib.src \
    sw_insfnote.src \
    sw_insrule.src \
    sw_linenum.src \
    sw_num.src \
    sw_numberingtypelistbox.src \
    sw_outline.src \
    sw_pgfnote.src \
    sw_pggrid.src \
    sw_redlndlg.src \
    sw_srtdlg.src

SLOFILES =	\
        $(SLO)$/sw_bookmark.obj \
        $(SLO)$/sw_docfnote.obj \
        $(SLO)$/sw_glosbib.obj \
        $(SLO)$/sw_glosdoc.obj \
        $(SLO)$/sw_glossary.obj \
        $(SLO)$/sw_glshell.obj \
        $(SLO)$/sw_hdftctrl.obj \
        $(SLO)$/sw_insfnote.obj \
        $(SLO)$/sw_insrule.obj \
        $(SLO)$/sw_linenum.obj \
        $(SLO)$/sw_num.obj \
        $(SLO)$/sw_numberingtypelistbox.obj \
        $(SLO)$/sw_outline.obj \
        $(SLO)$/sw_pgfnote.obj \
        $(SLO)$/sw_pggrid.obj \
        $(SLO)$/sw_redlndlg.obj \
        $(SLO)$/sw_srtdlg.obj

EXCEPTIONSFILES = \
        $(SLO)$/sw_glossary.obj \
        $(SLO)$/sw_numberingtypelistbox.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :	target.mk

