#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.1.1.1 $
#
#   last change: $Author: hjs $ $Date: 2003-10-01 12:22:32 $
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

PRJNAME=bf_svx
TARGET=svx_svdraw
AUTOSEG=true

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Files --------------------------------------------------------

SLOFILES=\
         $(SLO)$/svx_svdoutlinercache.obj \
         $(SLO)$/svx_dialdll.obj         \
         $(SLO)$/svx_gradtrns.obj         \
         $(SLO)$/svx_svdattr.obj         \
         $(SLO)$/svx_svdcrtmt.obj        \
         $(SLO)$/svx_svdcrtv.obj         \
         $(SLO)$/svx_svddrag.obj         \
         $(SLO)$/svx_svddrgmt.obj        \
         $(SLO)$/svx_svddrgv.obj         \
         $(SLO)$/svx_svdedtv.obj         \
         $(SLO)$/svx_svdedtv1.obj        \
         $(SLO)$/svx_svdedtv2.obj        \
         $(SLO)$/svx_svdedxv.obj         \
         $(SLO)$/svx_svdetc.obj          \
         $(SLO)$/svx_svdfmtf.obj		\
         $(SLO)$/svx_svdfppt.obj         \
         $(SLO)$/svx_svdglev.obj         \
         $(SLO)$/svx_svdglue.obj         \
         $(SLO)$/svx_svdhdl.obj          \
         $(SLO)$/svx_svdhlpln.obj        \
         $(SLO)$/svx_svdibrow.obj        \
         $(SLO)$/svx_svdio.obj           \
         $(SLO)$/svx_svditer.obj         \
         $(SLO)$/svx_svdlayer.obj        \
         $(SLO)$/svx_svdmark.obj         \
         $(SLO)$/svx_svdmodel.obj        \
         $(SLO)$/svx_svdmrkv.obj         \
         $(SLO)$/svx_svdmrkv1.obj        \
         $(SLO)$/svx_svdoattr.obj        \
         $(SLO)$/svx_svdobj.obj          \
         $(SLO)$/svx_impgrfll.obj        \
         $(SLO)$/svx_svdocapt.obj        \
         $(SLO)$/svx_svdocirc.obj        \
         $(SLO)$/svx_svdoedge.obj        \
         $(SLO)$/svx_svdograf.obj        \
         $(SLO)$/svx_svdogrp.obj         \
         $(SLO)$/svx_svdomeas.obj        \
         $(SLO)$/svx_svdoole2.obj        \
         $(SLO)$/svx_svdopage.obj        \
         $(SLO)$/svx_svdopath.obj        \
         $(SLO)$/svx_svdorect.obj        \
         $(SLO)$/svx_svdotext.obj        \
         $(SLO)$/svx_svdotxat.obj        \
         $(SLO)$/svx_svdotxdr.obj        \
         $(SLO)$/svx_svdotxed.obj        \
         $(SLO)$/svx_svdotxfl.obj        \
         $(SLO)$/svx_svdotxln.obj        \
         $(SLO)$/svx_svdotxtr.obj        \
         $(SLO)$/svx_svdouno.obj         \
         $(SLO)$/svx_svdoutl.obj         \
         $(SLO)$/svx_svdovirt.obj        \
         $(SLO)$/svx_svdpage.obj         \
         $(SLO)$/svx_svdpagv.obj         \
         $(SLO)$/svx_svdpntv.obj         \
         $(SLO)$/svx_svdpoev.obj         \
         $(SLO)$/svx_svdscrol.obj        \
         $(SLO)$/svx_svdsnpv.obj         \
         $(SLO)$/svx_svdsuro.obj         \
         $(SLO)$/svx_svdtouch.obj        \
         $(SLO)$/svx_svdtrans.obj        \
         $(SLO)$/svx_svdtxhdl.obj        \
         $(SLO)$/svx_svdundo.obj         \
         $(SLO)$/svx_svdview.obj         \
         $(SLO)$/svx_svdviter.obj        \
         $(SLO)$/svx_svdvmark.obj        \
         $(SLO)$/svx_svdxcgv.obj		 \
         $(SLO)$/svx_clonelist.obj

SVXLIGHTOBJFILES=\
         $(OBJ)$/svx_svdoutlinercache.obj \
         $(OBJ)$/svx_dialdll.obj        \
         $(OBJ)$/svx_gradtrns.obj        \
         $(OBJ)$/svx_svdattr.obj         \
         $(OBJ)$/svx_svdcrtmt.obj        \
         $(OBJ)$/svx_svdcrtv.obj         \
         $(OBJ)$/svx_svddrag.obj         \
         $(OBJ)$/svx_svddrgmt.obj        \
         $(OBJ)$/svx_svddrgv.obj         \
         $(OBJ)$/svx_svdedtv.obj         \
         $(OBJ)$/svx_svdedtv1.obj        \
         $(OBJ)$/svx_svdedtv2.obj        \
         $(OBJ)$/svx_svdedxv.obj         \
         $(OBJ)$/svx_svdetc.obj          \
         $(OBJ)$/svx_svdfmtf.obj		\
         $(OBJ)$/svx_svdfppt.obj         \
         $(OBJ)$/svx_svdglev.obj         \
         $(OBJ)$/svx_svdglue.obj         \
         $(OBJ)$/svx_svdhdl.obj          \
         $(OBJ)$/svx_svdhlpln.obj        \
         $(OBJ)$/svx_svdio.obj           \
         $(OBJ)$/svx_svditer.obj         \
         $(OBJ)$/svx_svdlayer.obj        \
         $(OBJ)$/svx_svdmark.obj         \
         $(OBJ)$/svx_svdmodel.obj        \
         $(OBJ)$/svx_svdmrkv.obj         \
         $(OBJ)$/svx_svdmrkv1.obj        \
         $(OBJ)$/svx_svdoattr.obj        \
         $(OBJ)$/svx_svdobj.obj          \
         $(OBJ)$/svx_impgrfll.obj        \
         $(OBJ)$/svx_svdocapt.obj        \
         $(OBJ)$/svx_svdocirc.obj        \
         $(OBJ)$/svx_svdoedge.obj        \
         $(OBJ)$/svx_svdograf.obj        \
         $(OBJ)$/svx_svdogrp.obj         \
         $(OBJ)$/svx_svdomeas.obj        \
         $(OBJ)$/svx_svdoole2.obj        \
         $(OBJ)$/svx_svdopage.obj        \
         $(OBJ)$/svx_svdopath.obj        \
         $(OBJ)$/svx_svdorect.obj        \
         $(OBJ)$/svx_svdotext.obj        \
         $(OBJ)$/svx_svdotxat.obj        \
         $(OBJ)$/svx_svdotxdr.obj        \
         $(OBJ)$/svx_svdotxed.obj        \
         $(OBJ)$/svx_svdotxfl.obj        \
         $(OBJ)$/svx_svdotxln.obj        \
         $(OBJ)$/svx_svdotxtr.obj        \
         $(OBJ)$/svx_svdouno.obj         \
         $(OBJ)$/svx_svdoutl.obj         \
         $(OBJ)$/svx_svdovirt.obj        \
         $(OBJ)$/svx_svdpage.obj         \
         $(OBJ)$/svx_svdpagv.obj         \
         $(OBJ)$/svx_svdpntv.obj         \
         $(OBJ)$/svx_svdpoev.obj         \
         $(OBJ)$/svx_svdscrol.obj        \
         $(OBJ)$/svx_svdsnpv.obj         \
         $(OBJ)$/svx_svdsuro.obj         \
         $(OBJ)$/svx_svdtouch.obj        \
         $(OBJ)$/svx_svdtrans.obj        \
         $(OBJ)$/svx_svdtxhdl.obj        \
         $(OBJ)$/svx_svdundo.obj         \
         $(OBJ)$/svx_svdview.obj         \
         $(OBJ)$/svx_svdviter.obj        \
         $(OBJ)$/svx_svdvmark.obj        \
         $(OBJ)$/svx_svdxcgv.obj

EXCEPTIONSFILES= \
         $(SLO)$/svx_svdhdl.obj          \
         $(SLO)$/svx_svdmrkv.obj         \
         $(SLO)$/svx_svdogrp.obj         \
         $(SLO)$/svx_svdotxln.obj        \
         $(SLO)$/svx_svdouno.obj         \
         $(SLO)$/svx_svdfppt.obj         \
         $(SLO)$/svx_svdpagv.obj

.IF "$(SVXLIGHT)"!=""
EXCEPTIONSFILES+= \
         $(OBJ)$/svx_sxl_svdogrp.obj         \
         $(OBJ)$/svx_sxl_svdotxln.obj
.ENDIF          # "$(SVXLIGHT)"!=""

SRS1NAME=svx_svdstr
SRC1FILES=  \
            svx_svdstr.src

.INCLUDE :  target.mk

