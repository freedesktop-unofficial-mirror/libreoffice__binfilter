#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.1 $
#
#   last change: $Author: aw $ $Date: 2003-12-05 09:34:07 $
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

PRJNAME=binfilter
TARGET=xmloff_forms

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
INC+= -I$(PRJ)$/inc$/bf_xmloff

# --- Files --------------------------------------------------------

# UNO header files
UNOUCROUT=$(OUT)$/inc
INCPRE+=$(UNOUCROUT)

UNOTYPES=\
    drafts.com.sun.star.form.XBindableValue \
    drafts.com.sun.star.form.XListEntrySource \
    drafts.com.sun.star.form.XListEntrySink

SLOFILES =	\
        $(SLO)$/xmloff_formstyles.obj \
        $(SLO)$/xmloff_officeforms.obj \
        $(SLO)$/xmloff_formevents.obj \
        $(SLO)$/xmloff_eventimport.obj \
        $(SLO)$/xmloff_eventexport.obj \
        $(SLO)$/xmloff_controlpropertyhdl.obj \
        $(SLO)$/xmloff_controlpropertymap.obj \
        $(SLO)$/xmloff_valueproperties.obj \
        $(SLO)$/xmloff_attriblistmerge.obj \
        $(SLO)$/xmloff_controlelement.obj \
        $(SLO)$/xmloff_formlayerexport.obj \
        $(SLO)$/xmloff_layerexport.obj \
        $(SLO)$/xmloff_elementexport.obj \
        $(SLO)$/xmloff_propertyexport.obj \
        $(SLO)$/xmloff_elementimport.obj \
        $(SLO)$/xmloff_layerimport.obj \
        $(SLO)$/xmloff_propertyimport.obj \
        $(SLO)$/xmloff_formlayerimport.obj \
        $(SLO)$/xmloff_formattributes.obj \
        $(SLO)$/xmloff_formenums.obj \
        $(SLO)$/xmloff_formsimp.obj \
        $(SLO)$/xmloff_strings.obj \
        $(SLO)$/xmloff_logging.obj \
        $(SLO)$/xmloff_formcellbinding.obj \

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk
