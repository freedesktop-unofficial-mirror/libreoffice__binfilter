#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.1.1.1 $
#
#   last change: $Author: hjs $ $Date: 2003-10-01 12:19:45 $
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

PROJECTPCH=sd
PROJECTPCHSOURCE=$(BFPRJ)$/util$/sd_sd
PRJNAME=bf_sd
TARGET=sd_view

AUTOSEG=true

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_sd
# --- Files --------------------------------------------------------

CXXFILES = $(BFPRJ)$/util$/sd_sd.cxx \
        sd_sdview.cxx		\
        sd_sdview2.cxx 	\
        sd_sdview3.cxx 	\
        sd_sdview4.cxx 	\
        sd_sdview5.cxx 	\
        sd_viewshel.cxx	\
        sd_viewshe2.cxx	\
        sd_viewshe3.cxx	\
        sd_sdwindow.cxx	\
        sd_drviewsh.cxx	\
        sd_drviews1.cxx	\
        sd_drviews2.cxx	\
        sd_drviews3.cxx	\
        sd_drviews4.cxx	\
        sd_drviews5.cxx	\
        sd_drviews6.cxx	\
        sd_drviews7.cxx	\
        sd_drviews8.cxx	\
        sd_drviews9.cxx	\
        sd_drviewsa.cxx	\
        sd_drviewsb.cxx	\
        sd_drviewsc.cxx	\
        sd_drviewsd.cxx	\
        sd_drviewse.cxx	\
        sd_drviewsf.cxx	\
        sd_drviewsg.cxx	\
        sd_drviewsi.cxx	\
        sd_drviewsj.cxx	\
        sd_drvwshrg.cxx	\
        sd_drawview.cxx	\
        sd_grviewsh.cxx	\
        sd_slidvish.cxx	\
        sd_slidview.cxx	\
        sd_outlnvsh.cxx	\
        sd_outlnvs2.cxx	\
        sd_presvish.cxx	\
        sd_prvwshll.cxx	\
        sd_outlview.cxx	\
        sd_tabcontr.cxx	\
        sd_layertab.cxx	\
        sd_showview.cxx	\
        sd_showwin.cxx 	\
        sd_bmcache.cxx 	\
        sd_drstdob.cxx 	\
        sd_grstdob.cxx 	\
        sd_drbezob.cxx 	\
        sd_drglueob.cxx 	\
        sd_drtxtob.cxx 	\
        sd_drtxtob1.cxx 	\
        sd_sdruler.cxx 	\
        sd_sdoutl.cxx		\
        sd_SdOutlinerIterator.cxx \
        sd_frmview.cxx 	\
        sd_clview.cxx		\
        sd_zoomlist.cxx	\
        sd_unmodpg.cxx		\
        sd_drgrfob.cxx		\
        sd_WindowUpdater.cxx

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
        $(SLO)$/sd_sdview3.obj	\
        $(SLO)$/sd_sdview4.obj	\
        $(SLO)$/sd_sdview5.obj	\
        $(SLO)$/sd_viewshel.obj \
        $(SLO)$/sd_viewshe2.obj \
        $(SLO)$/sd_viewshe3.obj \
        $(SLO)$/sd_sdwindow.obj \
        $(SLO)$/sd_drviewsh.obj \
        $(SLO)$/sd_drviews1.obj \
        $(SLO)$/sd_drviews2.obj \
        $(SLO)$/sd_drviews3.obj \
        $(SLO)$/sd_drviews4.obj \
        $(SLO)$/sd_drviews5.obj \
        $(SLO)$/sd_drviews6.obj \
        $(SLO)$/sd_drviews7.obj \
        $(SLO)$/sd_drviews8.obj \
        $(SLO)$/sd_drviews9.obj \
        $(SLO)$/sd_drviewsa.obj \
        $(SLO)$/sd_drviewsb.obj \
        $(SLO)$/sd_drviewsc.obj \
        $(SLO)$/sd_drviewsd.obj \
        $(SLO)$/sd_drviewse.obj \
        $(SLO)$/sd_drviewsf.obj \
        $(SLO)$/sd_drviewsg.obj \
        $(SLO)$/sd_drviewsi.obj \
        $(SLO)$/sd_drviewsj.obj \
        $(SLO)$/sd_drvwshrg.obj \
        $(SLO)$/sd_drawview.obj \
        $(SLO)$/sd_grviewsh.obj \
        $(SLO)$/sd_slidvish.obj \
        $(SLO)$/sd_slidview.obj \
        $(SLO)$/sd_outlnvsh.obj \
        $(SLO)$/sd_outlnvs2.obj \
        $(SLO)$/sd_presvish.obj \
        $(SLO)$/sd_prvwshll.obj \
        $(SLO)$/sd_outlview.obj \
        $(SLO)$/sd_tabcontr.obj \
        $(SLO)$/sd_layertab.obj \
        $(SLO)$/sd_showview.obj \
        $(SLO)$/sd_showwin.obj	\
        $(SLO)$/sd_bmcache.obj	\
        $(SLO)$/sd_drstdob.obj	\
        $(SLO)$/sd_grstdob.obj	\
        $(SLO)$/sd_drbezob.obj	\
        $(SLO)$/sd_drglueob.obj	\
        $(SLO)$/sd_drtxtob.obj	\
        $(SLO)$/sd_drtxtob1.obj	\
        $(SLO)$/sd_sdruler.obj	\
        $(SLO)$/sd_sdoutl.obj  \
        $(SLO)$/sd_SdOutlinerIterator.obj \
        $(SLO)$/sd_frmview.obj	\
        $(SLO)$/sd_clview.obj  \
        $(SLO)$/sd_zoomlist.obj	\
        $(SLO)$/sd_unmodpg.obj	\
        $(SLO)$/sd_drgrfob.obj \
        $(SLO)$/sd_WindowUpdater.obj


# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

