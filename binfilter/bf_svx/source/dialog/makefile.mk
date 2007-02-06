#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.8 $
#
#   last change: $Author: vg $ $Date: 2007-02-06 12:48:32 $
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
TARGET=svx_dialogs

NO_HIDS=TRUE

VERSION=$(UPD)

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

.IF "$(GUI)" != "MAC"
CFLAGS+=-DDG_DLL
.ELSE
CFLAGS+=-D DG_DLL
.ENDIF

# --- Files --------------------------------------------------------

BMP_IN=$(BFPRJ)$/win/res

SRS1NAME=svx_dialogs
SRC1FILES =  \
        svx_connect.src \
        svx_contdlg.src \
        svx_ctredlin.src \
        svx_measure.src \
        svx_dstribut.src \
        svx_passwd.src	\
        svx_align.src \
        svx_backgrnd.src \
        svx_bbdlg.src \
        svx_bmpmask.src \
        svx_border.src \
        svx_chardlg.src \
        svx_charmap.src \
        svx_checklbx.src \
        svx_fontwork.src \
        svx_frmsel.src \
        svx_grfpage.src \
        svx_hdft.src \
        svx_hyperdlg.src \
        svx_hlmarkwn.src\
        svx_hyphen.src \
        svx_iconcdlg.src \
        svx_imapdlg.src \
        svx_impgrf.src \
        svx_langtab.src \
        svx_language.src \
        svx_lingu.src \
        svx_numfmt.src \
        svx_numpages.src \
        svx_page.src \
        svx_paragrph.src \
        svx_postdlg.src \
        svx_prtqry.src \
        svx_ruler.src \
        svx_rubydialog.src\
        svx_spldlg.src \
        svx_srchdlg.src \
        svx_srchxtra.src \
        svx_tabstpge.src \
        svx_textanim.src \
        svx_textattr.src \
        svx_thesdlg.src \
        svx_txenctab.src \
        svx_zoom.src	\
        svx_grfflt.src \
        svx_langbox.src \
        svx_frmdirlbox.src \
        svx_hangulhanjadlg.src \
        svx_commonlingui.src

SRS2NAME=svx_drawdlgs
SRC2FILES =  \
    svx_dlgname.src \
        svx_sdstring.src \
        svx_tabline.src \
        svx_labdlg.src \
        svx_transfrm.src


EXCEPTIONSFILES=\
        $(SLO)$/svx_charmap.obj		\
        $(SLO)$/svx__bmpmask.obj	\
        $(SLO)$/svx_rubydialog.obj 	

SLOFILES=\
        $(SLO)$/svx__bmpmask.obj\
        $(SLO)$/svx__contdlg.obj\
        $(SLO)$/svx_charmap.obj  \
        $(SLO)$/svx_hyperdlg.obj \
        $(SLO)$/svx_imapdlg.obj \
        $(SLO)$/svx_dlgutil.obj  \
        $(SLO)$/svx_fontwork.obj \
        $(SLO)$/svx_impgrf.obj   \
        $(SLO)$/svx_rlrcitem.obj \
        $(SLO)$/svx_rulritem.obj \
        $(SLO)$/svx_rubydialog.obj \
        $(SLO)$/svx_srchdlg.obj  \
        $(SLO)$/svx_svxruler.obj	\
         $(SLO)$/svx_txencbox.obj 



.IF "$(COM)" == "C50"
EXCEPTIONSNOOPTFILES=$(SLO)$/svx_impgrf.obj
.ELSE
EXCEPTIONSFILES+=$(SLO)$/svx_impgrf.obj
.ENDIF

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

