#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.9 $
#
#   last change: $Author: obo $ $Date: 2007-03-09 14:45:21 $
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
PRJ=..$/..$/..$/..
BFPRJ=..$/..$/..

PROJECTPCH=sd
PROJECTPCHSOURCE=$(BFPRJ)$/util$/sd_sd

PRJNAME=binfilter
TARGET=sd_view

NO_HIDS=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sd
# --- Files --------------------------------------------------------

EXCEPTIONSFILES= \
        $(SLO)$/sd_sdoutl.obj  \
        $(SLO)$/sd_drviews1.obj \
        $(SLO)$/sd_drviews8.obj \
        $(SLO)$/sd_drviewsa.obj \
        $(SLO)$/sd_outlnvsh.obj \
        $(SLO)$/sd_slidvish.obj	

EXCEPTIONSNOOPTFILES=\
        $(SLO)$/sd_drviews5.obj\
        $(SLO)$/sd_drviewsb.obj

SLOFILES =	\
        $(SLO)$/sd_sdview.obj	\
        $(SLO)$/sd_sdview2.obj	\
        $(SLO)$/sd_sdview4.obj	\
        $(SLO)$/sd_viewshel.obj \
        $(SLO)$/sd_viewshe2.obj \
        $(SLO)$/sd_viewshe3.obj \
        $(SLO)$/sd_sdwindow.obj \
        $(SLO)$/sd_drviews1.obj \
        $(SLO)$/sd_drviews2.obj \
        $(SLO)$/sd_drviews3.obj \
        $(SLO)$/sd_drviews5.obj \
        $(SLO)$/sd_drviews6.obj \
        $(SLO)$/sd_drviews7.obj \
        $(SLO)$/sd_drviews8.obj \
        $(SLO)$/sd_drviewsa.obj \
        $(SLO)$/sd_drviewsb.obj \
        $(SLO)$/sd_drviewsc.obj \
        $(SLO)$/sd_drviewse.obj \
        $(SLO)$/sd_drviewsf.obj \
        $(SLO)$/sd_drviewsi.obj \
        $(SLO)$/sd_drviewsj.obj \
        $(SLO)$/sd_drvwshrg.obj \
        $(SLO)$/sd_drawview.obj \
        $(SLO)$/sd_grviewsh.obj \
        $(SLO)$/sd_slidvish.obj \
        $(SLO)$/sd_outlnvsh.obj \
        $(SLO)$/sd_presvish.obj \
        $(SLO)$/sd_prvwshll.obj \
        $(SLO)$/sd_tabcontr.obj \
        $(SLO)$/sd_layertab.obj \
        $(SLO)$/sd_drstdob.obj	\
        $(SLO)$/sd_grstdob.obj	\
        $(SLO)$/sd_drbezob.obj	\
        $(SLO)$/sd_drglueob.obj	\
        $(SLO)$/sd_drtxtob.obj	\
        $(SLO)$/sd_sdruler.obj	\
        $(SLO)$/sd_sdoutl.obj  \
        $(SLO)$/sd_SdOutlinerIterator.obj \
        $(SLO)$/sd_frmview.obj	\
        $(SLO)$/sd_zoomlist.obj	\
        $(SLO)$/sd_drgrfob.obj \
        $(SLO)$/sd_WindowUpdater.obj


# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

