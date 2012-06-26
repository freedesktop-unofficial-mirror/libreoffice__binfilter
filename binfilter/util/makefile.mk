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

PRJ = ..
PRJNAME = binfilter
TARGET = bf_util

my_components = \
    bf_frm bf_sc bf_sch bf_sd bf_sm bf_svt bf_svx bf_sw bf_wrapper bf_xo

.INCLUDE: settings.mk
.INCLUDE: target.mk

ALLTAR : $(MISC)/legacy_binfilters.rdb

$(MISC)/legacy_binfilters.rdb .ERRREMOVE : $(SOLARENV)/bin/packcomponents.xslt \
        $(MISC)/legacy_binfilters.input \
        $(my_components:^"$(MISC)/":+".component")
    $(XSLTPROC) --nonet --stringparam prefix $(PWD)/$(MISC)/ -o $@ \
        $(SOLARENV)/bin/packcomponents.xslt $(MISC)/legacy_binfilters.input

$(MISC)/legacy_binfilters.input :
    echo \
        '<list>$(my_components:^"<filename>":+".component</filename>")</list>' \
        > $@
