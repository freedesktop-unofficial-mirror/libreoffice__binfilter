#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: aw $ $Date: 2003-10-09 14:14:43 $
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

PRJNAME=binfilter
TARGET=sw_sw3io

AUTOSEG=true

# --- Settings -----------------------------------------------------

#.INCLUDE :  $(PRJ)$/inc$/swpre.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :  settings.mk
#.INCLUDE :  $(PRJ)$/inc$/sw.mk
.INCLUDE :  $(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw

.IF "$(GUI)$(COM)" == "WINMSC"
LIBFLAGS=/NOI /NOE /PAGE:512
.ENDIF

# --- Files --------------------------------------------------------

CXXFILES = \
    sw_sw3io.cxx		\
    sw_sw3attr.cxx 	\
    sw_swacorr.cxx 	\
    sw_sw3block.cxx	\
    sw_sw3doc.cxx		\
    sw_sw3field.cxx	\
    sw_sw3fmts.cxx 	\
    sw_sw3imp.cxx		\
    sw_sw3misc.cxx 	\
    sw_sw3nodes.cxx	\
    sw_sw3npool.cxx	\
    sw_sw3num.cxx		\
    sw_sw3page.cxx 	\
    sw_sw3redln.cxx 	\
    sw_sw3sectn.cxx	\
    sw_sw3style.cxx	\
    sw_sw3table.cxx	\
    sw_sw3gsect.cxx	\
    sw_swacorr.cxx 	\
    sw_crypter.cxx

SLOFILES = \
    $(SLO)$/sw_sw3io.obj	\
    $(SLO)$/sw_sw3attr.obj	\
    $(SLO)$/sw_sw3block.obj \
    $(SLO)$/sw_sw3doc.obj	\
    $(SLO)$/sw_sw3field.obj \
    $(SLO)$/sw_sw3fmts.obj	\
    $(SLO)$/sw_sw3imp.obj	\
    $(SLO)$/sw_sw3misc.obj	\
    $(SLO)$/sw_sw3nodes.obj \
    $(SLO)$/sw_sw3npool.obj \
    $(SLO)$/sw_sw3num.obj	\
    $(SLO)$/sw_sw3page.obj	\
    $(SLO)$/sw_sw3redln.obj	\
    $(SLO)$/sw_sw3sectn.obj \
    $(SLO)$/sw_sw3style.obj \
    $(SLO)$/sw_sw3table.obj \
    $(SLO)$/sw_sw3gsect.obj \
    $(SLO)$/sw_swacorr.obj	\
    $(SLO)$/sw_crypter.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

