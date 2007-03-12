#*************************************************************************#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.10 $
#
#   last change: $Author: obo $ $Date: 2007-03-12 09:25:21 $
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

EXTERNAL_WARNINGS_NOT_ERRORS := TRUE

PRJ=..$/..$/..
BFPRJ=..$/..

PRJNAME=binfilter
TARGET=svx_svdraw

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

# --- Files --------------------------------------------------------

SLOFILES=\
         $(SLO)$/svx_svdoutlinercache.obj \
         $(SLO)$/svx_dialdll.obj         \
         $(SLO)$/svx_svdattr.obj         \
         $(SLO)$/svx_svdcrtv.obj         \
         $(SLO)$/svx_svddrag.obj         \
         $(SLO)$/svx_svddrgv.obj         \
         $(SLO)$/svx_svdedtv.obj         \
         $(SLO)$/svx_svdedtv2.obj        \
         $(SLO)$/svx_svdedxv.obj         \
         $(SLO)$/svx_svdetc.obj          \
         $(SLO)$/svx_svdglev.obj         \
         $(SLO)$/svx_svdglue.obj         \
         $(SLO)$/svx_svdhdl.obj          \
         $(SLO)$/svx_svdhlpln.obj        \
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

.IF "$(OS)$(CPU)"=="LINUXI"
NOOPTFILES=$(SLO)$/svx_svdattr.obj
.ENDIF

EXCEPTIONSFILES= \
         $(SLO)$/svx_svdhdl.obj          \
         $(SLO)$/svx_svdmrkv.obj         \
         $(SLO)$/svx_svdogrp.obj         \
         $(SLO)$/svx_svdotxln.obj        \
         $(SLO)$/svx_svdouno.obj         \
         $(SLO)$/svx_svdfppt.obj         \
         $(SLO)$/svx_svdpagv.obj

SRS1NAME=svx_svdstr
SRC1FILES=  \
            svx_svdstr.src

.INCLUDE :  target.mk

