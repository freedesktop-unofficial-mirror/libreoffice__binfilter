#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: aw $ $Date: 2003-10-09 14:13:52 $
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
BFPRJ=..$/..


PRJNAME=binfilter
TARGET=sfx2_bastyp
ENABLE_EXCEPTIONS=TRUE
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
AUTOSEG=true

# --- Settings -----------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
INC+= -I$(PRJ)$/inc$/bf_sfx2

# --- Files --------------------------------------------------------

SLOFILES =\
        $(SLO)$/sfx2_plugwin.obj				\
        $(SLO)$/sfx2_propset.obj				\
        $(SLO)$/sfx2_itmfac.obj				\
        $(SLO)$/sfx2_sfxhtml.obj				\
        $(SLO)$/sfx2_frmhtml.obj				\
        $(SLO)$/sfx2_frmhtmlw.obj			\
        $(SLO)$/sfx2_misc.obj				\
        $(SLO)$/sfx2_idpool.obj				\
        $(SLO)$/sfx2_progress.obj			\
        $(SLO)$/sfx2_sfxresid.obj			\
        $(SLO)$/sfx2_newhdl.obj				\
        $(SLO)$/sfx2_bitset.obj				\
        $(SLO)$/sfx2_minarray.obj			\
        $(SLO)$/sfx2_fltfnc.obj				\
        $(SLO)$/sfx2_mieclip.obj				\
        $(SLO)$/sfx2_fltdlg.obj				\
        $(SLO)$/sfx2_fltlst.obj				\
        $(SLO)$/sfx2_helper.obj

SRS1NAME=$(TARGET)
SRC1FILES =\
        sfx2_fltdlg.src	\
        sfx2_fltfnc.src	\
        sfx2_bastyp.src	\
        sfx2_newhdl.src

EXCEPTIONSFILES =\
    $(SLO)$/sfx2_propset.obj		\
    $(SLO)$/sfx2_helper.obj

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

