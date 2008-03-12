#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: rt $ $Date: 2008-03-12 09:01:17 $
#
#   The Contents of this file are made available subject to
#   the terms of GNU Lesser General Public License Version 2.1.
#
#
#     GNU Lesser General Public License Version 2.1
#     =============================================
#     Copyright 2005 by Sun Microsystems, Inc.
#     901 San Antonio Road, Palo Alto, CA 94303, USA
#
#     This library is free software; you can redistribute it and/or
#     modify it under the terms of the GNU Lesser General Public
#     License version 2.1, as published by the Free Software Foundation.
#
#     This library is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#     Lesser General Public License for more details.
#
#     You should have received a copy of the GNU Lesser General Public
#     License along with this library; if not, write to the Free Software
#     Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#     MA  02111-1307  USA
#
#*************************************************************************

PRJ=..$/..$/..

PRJNAME=binfilter
TARGET=misc1

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
INC+= -I$(PRJ)$/inc$/bf_svtools

# --- Files --------------------------------------------------------

EXCEPTIONSFILES=\
    $(SLO)$/svt_fstathelper.obj \
    $(SLO)$/svt_folderrestriction.obj \
    $(SLO)$/svt_strmadpt.obj \
    $(SLO)$/svt_svtdata.obj

SLOFILES=\
    $(EXCEPTIONSFILES) \
    $(SLO)$/svt_adrparse.obj \
    $(SLO)$/svt_docpasswdrequest.obj \
    $(SLO)$/svt_filenotation.obj \
    $(SLO)$/svt_inethist.obj \
    $(SLO)$/svt_inettype.obj \
    $(SLO)$/svt_iniadrtk.obj \
    $(SLO)$/svt_lngmisc.obj \
    $(SLO)$/svt_loginerr.obj \
    $(SLO)$/svt_PasswordHelper.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk




