#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.1.1.1 $
#
#   last change: $Author: hjs $ $Date: 2003-10-01 12:21:31 $
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

PROJECTPCH4DLL=TRUE
PROJECTPCH=svxpch
PROJECTPCHSOURCE=$(BFPRJ)$/util$/svx_svxpch

PRJNAME=bf_svx
TARGET=svx_dialogs
AUTOSEG=true
VERSION=$(UPD)

.IF "$(debug)" != ""
LINK=n:\bin\optlinks\optlinks
.ELSE
OPTLINKS=YES
.ENDIF

# --- Settings -----------------------------------------------------

.INCLUDE :  svpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sv.mk
.INCLUDE :  $(BFPRJ)$/util$/makefile.pmk
INC+= -I$(PRJ)$/inc$/bf_svx

.IF "$(GUI)" != "MAC"
CFLAGS+=-DDG_DLL
.ELSE
CFLAGS+=-D DG_DLL
.ENDIF

# --- Files --------------------------------------------------------

HXX2TARGET= drawdlgs
HXX2EXT=    hxx
HXX2EXCL=   -E:*include*
HXX2DEPN=\
        $(INC)$/dlgctrl.hxx \
        $(INC)$/dlgname.hxx \
        $(INC)$/tabarea.hxx \
        $(INC)$/tabline.hxx \
        $(INC)$/labdlg.hxx \
        $(INC)$/transfrm.hxx

.IF "$(header)" == ""

#IMGLST_SRS=$(SRS)$/dialogs.srs
BMP_IN=$(BFPRJ)$/win/res

CXXFILES = \
        svx__contdlg.cxx \
        svx__bmpmask.cxx \
        svx_charmap.cxx \
        svx_dlgutil.cxx \
        svx_fontwork.cxx \
        svx_hyperdlg.cxx \
        svx_imapdlg.cxx \
        svx_impgrf.cxx \
        svx_rlrcitem.cxx \
        svx_rulritem.cxx \
        svx_rubydialog.cxx \
        svx_srchdlg.cxx \
        svx_svxruler.cxx \
         svx_txencbox.cxx \
       $(PROJECTPCHSOURCE).cxx

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
        svx_dlgctrl.src \
        svx_grfflt.src \
        svx_langbox.src \
        svx_frmdirlbox.src \
        svx_hangulhanjadlg.src \
        svx_commonlingui.src

SRS2NAME=svx_drawdlgs
SRC2FILES =  \
    svx_dlgname.src \
        svx_sdstring.src \
        svx_tabarea.src \
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

.ENDIF

# --- Targets -------------------------------------------------------

.INCLUDE :  target.mk

