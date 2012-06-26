#
# This file is part of the LibreOffice project.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# This file incorporates work covered by the following license notice:
#
#   Licensed to the Apache Software Foundation (ASF) under one or more
#   contributor license agreements. See the NOTICE file distributed
#   with this work for additional information regarding copyright
#   ownership. The ASF licenses this file to you under the Apache
#   License, Version 2.0 (the "License"); you may not use this file
#   except in compliance with the License. You may obtain a copy of
#   the License at http://www.apache.org/licenses/LICENSE-2.0 .
#

PRJ					= ..$/..$/..
PRJNAME				= binfilter
TARGET				= xmloff_chart
ENABLE_EXCEPTIONS	= TRUE

# --- Settings -----------------------------------------------------

.INCLUDE : settings.mk

INC+= -I$(PRJ)$/inc$/bf_xmloff

# --- Files --------------------------------------------------------

SLOFILES =	$(SLO)$/xmloff_SchXMLExport.obj \
            $(SLO)$/xmloff_SchXMLImport.obj \
            $(SLO)$/xmloff_contexts.obj \
            $(SLO)$/xmloff_SchXMLTableContext.obj \
            $(SLO)$/xmloff_SchXMLChartContext.obj \
            $(SLO)$/xmloff_SchXMLPlotAreaContext.obj \
            $(SLO)$/xmloff_SchXMLParagraphContext.obj \
            $(SLO)$/xmloff_PropertyMaps.obj \
            $(SLO)$/xmloff_XMLChartStyleContext.obj \
            $(SLO)$/xmloff_XMLErrorIndicatorPropertyHdl.obj \
            $(SLO)$/xmloff_SchXMLAutoStylePoolP.obj \
            $(SLO)$/xmloff_XMLChartPropertyContext.obj \
            $(SLO)$/xmloff_XMLSymbolImageContext.obj \
            $(SLO)$/xmloff_XMLTextOrientationHdl.obj

# --- Targets --------------------------------------------------------------

.INCLUDE : target.mk

