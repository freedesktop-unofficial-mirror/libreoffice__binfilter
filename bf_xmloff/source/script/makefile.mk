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

PRJ=..$/..$/..

PRJNAME=binfilter
TARGET=xmloff_script

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_xmloff
# --- Files --------------------------------------------------------

SLOFILES =	\
        $(SLO)$/xmloff_XMLEventExport.obj \
        $(SLO)$/xmloff_XMLEventImportHelper.obj \
        $(SLO)$/xmloff_XMLEventsImportContext.obj \
        $(SLO)$/xmloff_XMLScriptContextFactory.obj \
        $(SLO)$/xmloff_XMLScriptExportHandler.obj \
        $(SLO)$/xmloff_XMLStarBasicContextFactory.obj \
        $(SLO)$/xmloff_XMLStarBasicExportHandler.obj \
        $(SLO)$/xmloff_xmlscripti.obj \
        $(SLO)$/xmloff_xmlbasici.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

