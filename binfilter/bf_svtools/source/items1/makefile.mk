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
TARGET=items1
ENABLE_EXCEPTIONS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_svtools

# --- Files --------------------------------------------------------

SLOFILES=\
    $(SLO)$/svt_bintitem.obj	\
    $(SLO)$/svt_cenumitm.obj	\
    $(SLO)$/svt_cintitem.obj	\
    $(SLO)$/svt_cntwall.obj	\
    $(SLO)$/svt_cstitem.obj	\
    $(SLO)$/svt_ctypeitm.obj	\
    $(SLO)$/svt_custritm.obj	\
    $(SLO)$/svt_dateitem.obj	\
    $(SLO)$/svt_dtritem.obj	\
    $(SLO)$/svt_frqitem.obj	\
    $(SLO)$/svt_ilstitem.obj    \
    $(SLO)$/svt_itemiter.obj	\
    $(SLO)$/svt_itempool.obj	\
    $(SLO)$/svt_itemprop.obj	\
    $(SLO)$/svt_itemset.obj	\
    $(SLO)$/svt_lckbitem.obj	\
    $(SLO)$/svt_poolio.obj	\
    $(SLO)$/svt_stylepool.obj	\
    $(SLO)$/svt_poolitem.obj	\
    $(SLO)$/svt_sfontitm.obj	\
    $(SLO)$/svt_sitem.obj	    \
    $(SLO)$/svt_slstitm.obj	\
    $(SLO)$/svt_tfrmitem.obj	\
    $(SLO)$/svt_tresitem.obj	\
    $(SLO)$/svt_whiter.obj \
    $(SLO)$/svt_visitem.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

