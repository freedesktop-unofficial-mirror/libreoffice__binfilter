#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.1.1.1 $
#
#   last change: $Author: hjs $ $Date: 2003-10-01 12:20:27 $
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
TARGET=sw_xml

# --- Settings -----------------------------------------------------

#.INCLUDE :  $(PRJ)$/inc$/swpre.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
#.INCLUDE :  $(PRJ)$/inc$/sw.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw
.IF "$(mydebug)" != ""
CDEFS=$(CDEFS) -Dmydebug
.ENDIF

# --- Files --------------------------------------------------------

CXXFILES = \
        sw_swxml.cxx      \
        sw_xmlimp.cxx      \
        sw_wrtxml.cxx      \
        sw_xmlexp.cxx      \
        sw_xmltext.cxx      \
        sw_xmltexte.cxx      \
        sw_xmltexti.cxx      \
        sw_xmltbli.cxx      \
        sw_xmltble.cxx      \
        sw_xmlfmt.cxx      \
        sw_xmlfmte.cxx      \
        sw_xmlmeta.cxx      \
        sw_xmlitemm.cxx	\
        sw_xmlitemi.cxx	\
        sw_xmliteme.cxx	\
        sw_xmlbrsh.cxx		\
        sw_xmlfonte.cxx	\
        sw_XMLRedlineImportHelper.cxx \
        sw_xmlitem.cxx	\
        sw_xmlithlp.cxx \
        sw_xmlitmpr.cxx	\
        sw_xmlimpit.cxx \
        sw_xmlexpit.cxx 

SLOFILES =  \
        $(SLO)$/sw_swxml.obj \
        $(SLO)$/sw_xmlimp.obj \
        $(SLO)$/sw_wrtxml.obj \
        $(SLO)$/sw_xmlexp.obj \
        $(SLO)$/sw_xmltext.obj \
        $(SLO)$/sw_xmltexte.obj \
        $(SLO)$/sw_xmltexti.obj \
        $(SLO)$/sw_xmltbli.obj \
        $(SLO)$/sw_xmltble.obj \
        $(SLO)$/sw_xmlfmt.obj \
        $(SLO)$/sw_xmlfmte.obj \
        $(SLO)$/sw_xmlmeta.obj \
        $(SLO)$/sw_xmlscript.obj \
        $(SLO)$/sw_xmlitemm.obj \
        $(SLO)$/sw_xmlitemi.obj \
        $(SLO)$/sw_xmliteme.obj \
        $(SLO)$/sw_xmlithlp.obj \
        $(SLO)$/sw_xmlbrsh.obj \
        $(SLO)$/sw_xmlfonte.obj \
        $(SLO)$/sw_XMLRedlineImportHelper.obj \
        $(SLO)$/sw_xmlitem.obj	\
        $(SLO)$/sw_xmlitmpr.obj	\
        $(SLO)$/sw_xmlimpit.obj \
        $(SLO)$/sw_xmlexpit.obj

EXCEPTIONSFILES= \
        $(SLO)$/sw_swxml.obj \
        $(SLO)$/sw_xmlimp.obj \
        $(SLO)$/sw_wrtxml.obj \
        $(SLO)$/sw_xmlexp.obj \
        $(SLO)$/sw_xmltext.obj \
        $(SLO)$/sw_xmltexti.obj \
        $(SLO)$/sw_xmltbli.obj \
        $(SLO)$/sw_xmltble.obj \
        $(SLO)$/sw_xmlfmt.obj \
        $(SLO)$/sw_xmlfmte.obj \
        $(SLO)$/sw_xmlmeta.obj \
        $(SLO)$/sw_xmlscript.obj \
        $(SLO)$/sw_xmlitemi.obj \
        $(SLO)$/sw_xmliteme.obj \
        $(SLO)$/sw_xmlithlp.obj \
        $(SLO)$/sw_xmlbrsh.obj \
        $(SLO)$/sw_xmlfonte.obj \
        $(SLO)$/sw_XMLRedlineImportHelper.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

