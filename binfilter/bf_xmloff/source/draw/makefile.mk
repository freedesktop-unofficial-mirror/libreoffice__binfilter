#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.1 $
#
#   last change: $Author: aw $ $Date: 2003-12-05 09:33:03 $
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
TARGET=xmloff_draw
AUTOSEG=true
ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE : svpre.mk
.INCLUDE : settings.mk
.INCLUDE : sv.mk

INC+= -I$(PRJ)$/inc$/bf_xmloff

# --- Files --------------------------------------------------------

SLOFILES =	\
        $(SLO)$/xmloff_XMLNumberStyles.obj\
        $(SLO)$/xmloff_XMLGraphicsDefaultStyle.obj\
        $(SLO)$/xmloff_viewcontext.obj\
        $(SLO)$/xmloff_eventimp.obj\
        $(SLO)$/xmloff_layerexp.obj\
        $(SLO)$/xmloff_layerimp.obj\
        $(SLO)$/xmloff_ximpshow.obj\
        $(SLO)$/xmloff_animimp.obj\
        $(SLO)$/xmloff_animexp.obj\
        $(SLO)$/xmloff_numithdl.obj\
        $(SLO)$/xmloff_sdxmlimp.obj \
        $(SLO)$/xmloff_sdxmlexp.obj \
        $(SLO)$/xmloff_ximpstyl.obj \
        $(SLO)$/xmloff_ximpbody.obj \
        $(SLO)$/xmloff_ximpshap.obj \
        $(SLO)$/xmloff_ximpgrp.obj \
        $(SLO)$/xmloff_ximp3dscene.obj \
        $(SLO)$/xmloff_ximp3dobject.obj \
        $(SLO)$/xmloff_ximpnote.obj \
        $(SLO)$/xmloff_sdpropls.obj \
        $(SLO)$/xmloff_propimp0.obj \
        $(SLO)$/xmloff_xexptran.obj \
        $(SLO)$/xmloff_shapeexport.obj \
        $(SLO)$/xmloff_shapeexport2.obj \
        $(SLO)$/xmloff_shapeexport3.obj \
        $(SLO)$/xmloff_shapeimport.obj \
        $(SLO)$/xmloff_XMLImageMapExport.obj \
        $(SLO)$/xmloff_XMLImageMapContext.obj \
        $(SLO)$/xmloff_XMLShapePropertySetContext.obj \
        $(SLO)$/xmloff_XMLShapeStyleContext.obj \
        $(SLO)$/xmloff_ximppage.obj

SVXLIGHTOBJFILES =	\
        $(OBJ)$/xmloff_XMLNumberStyles.obj\
        $(OBJ)$/xmloff_XMLGraphicsDefaultStyle.obj\
        $(OBJ)$/xmloff_viewcontext.obj\
        $(OBJ)$/xmloff_eventimp.obj\
        $(OBJ)$/xmloff_layerimp.obj\
        $(OBJ)$/xmloff_ximpshow.obj\
        $(OBJ)$/xmloff_animimp.obj\
        $(OBJ)$/xmloff_numithdl.obj\
        $(OBJ)$/xmloff_sdxmlimp.obj \
        $(OBJ)$/xmloff_ximpstyl.obj \
        $(OBJ)$/xmloff_ximpbody.obj \
        $(OBJ)$/xmloff_ximpshap.obj \
        $(OBJ)$/xmloff_ximpgrp.obj \
        $(OBJ)$/xmloff_ximp3dscene.obj \
        $(OBJ)$/xmloff_ximp3dobject.obj \
        $(OBJ)$/xmloff_ximpnote.obj \
        $(OBJ)$/xmloff_sdpropls.obj \
        $(OBJ)$/xmloff_propimp0.obj \
        $(OBJ)$/xmloff_xexptran.obj \
        $(OBJ)$/xmloff_shapeimport.obj \
        $(OBJ)$/xmloff_XMLImageMapContext.obj \
        $(OBJ)$/xmloff_XMLShapePropertySetContext.obj \
        $(OBJ)$/xmloff_XMLShapeStyleContext.obj \
        $(OBJ)$/xmloff_ximppage.obj

# --- Targets --------------------------------------------------------------

.INCLUDE : target.mk

