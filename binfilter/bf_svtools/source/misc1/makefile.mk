#*************************************************************************
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
# 
# Copyright 2008 by Sun Microsystems, Inc.
#
# OpenOffice.org - a multi-platform office productivity suite
#
# $RCSfile: makefile.mk,v $
#
# $Revision: 1.5 $
#
# This file is part of OpenOffice.org.
#
# OpenOffice.org is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License version 3
# only, as published by the Free Software Foundation.
#
# OpenOffice.org is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License version 3 for more details
# (a copy is included in the LICENSE file that accompanied this code).
#
# You should have received a copy of the GNU Lesser General Public License
# version 3 along with OpenOffice.org.  If not, see
# <http://www.openoffice.org/license.html>
# for a copy of the LGPLv3 License.
#
#*************************************************************************

EXTERNAL_WARNINGS_NOT_ERRORS := TRUE

PRJ=..$/..$/..

PRJNAME=binfilter
TARGET=misc1

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_svtools

# --- Files --------------------------------------------------------

EXCEPTIONSFILES=\
    $(SLO)$/svt_fstathelper.obj \
    $(SLO)$/svt_strmadpt.obj \
    $(SLO)$/svt_svtdata.obj

SLOFILES=\
    $(EXCEPTIONSFILES) \
    $(SLO)$/svt_adrparse.obj \
    $(SLO)$/svt_docpasswdrequest.obj \
    $(SLO)$/svt_inethist.obj \
    $(SLO)$/svt_inettype.obj \
    $(SLO)$/svt_loginerr.obj \
    $(SLO)$/svt_PasswordHelper.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk




