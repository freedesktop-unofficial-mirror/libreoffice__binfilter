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
BFPRJ=..$/..

PRJNAME=binfilter
TARGET=sfx2_doc

NO_HIDS=TRUE

ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_sfx2

# --- Files --------------------------------------------------------

SLOFILES =	\
        $(SLO)$/timestamp.obj \
        $(SLO)$/sfx2_docfile.obj \
        $(SLO)$/sfx2_objuno.obj \
        $(SLO)$/sfx2_frmdescr.obj \
        $(SLO)$/sfx2_docinf.obj \
        $(SLO)$/sfx2_interno.obj \
        $(SLO)$/sfx2_objxtor.obj \
        $(SLO)$/sfx2_objmisc.obj \
        $(SLO)$/sfx2_objstor.obj \
        $(SLO)$/sfx2_objcont.obj \
        $(SLO)$/sfx2_objserv.obj \
        $(SLO)$/sfx2_objitem.obj \
        $(SLO)$/sfx2_docfac.obj \
        $(SLO)$/sfx2_docfilt.obj \
        $(SLO)$/sfx2_frameobj.obj \
        $(SLO)$/sfx2_sfxbasemodel.obj \
        $(SLO)$/sfx2_xmlversion.obj

EXCEPTIONSFILES=\
        $(SLO)$/sfx2_objuno.obj \
        $(SLO)$/sfx2_objcont.obj \
        $(SLO)$/sfx2_docfac.obj \
        $(SLO)$/sfx2_docfile.obj \
        $(SLO)$/sfx2_doctempl.obj \
        $(SLO)$/sfx2_doctemplates.obj \
        $(SLO)$/sfx2_sfxbasemodel.obj \
        $(SLO)$/sfx2_objxtor.obj \
        $(SLO)$/sfx2_objstor.obj \
        $(SLO)$/sfx2_xmlversion.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk
