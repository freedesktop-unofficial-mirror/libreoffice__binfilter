#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: aw $ $Date: 2003-10-09 14:14:48 $
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
TARGET=sw_unocore

AUTOSEG=true

# --- Settings -----------------------------------------------------
#ENABLE_EXCEPTIONS=TRUE

#.INCLUDE :	$(PRJ)$/inc$/swpre.mk
.INCLUDE :	$(PRJ)$/inc$/bf_sw$/swpre.mk
.INCLUDE :	settings.mk
#.INCLUDE :	$(PRJ)$/inc$/sw.mk
.INCLUDE :	$(PRJ)$/inc$/bf_sw$/sw.mk
INC+= -I$(PRJ)$/inc$/bf_sw

.IF "$(GUI)$(COM)" == "WINMSC"
LIBFLAGS=/NOI /NOE /PAGE:512
.ENDIF



# --- Files --------------------------------------------------------
EXCEPTIONSFILES=	\
        $(SLO)$/sw_swunohelper.obj\
        $(SLO)$/sw_SwXTextDefaults.obj\
    $(SLO)$/sw_unobkm.obj\
    $(SLO)$/sw_unoevent.obj\
    $(SLO)$/sw_unocrsrhelper.obj\
    $(SLO)$/sw_unoevtlstnr.obj\
    $(SLO)$/sw_unoftn.obj\
    $(SLO)$/sw_unorefmk.obj\
    $(SLO)$/sw_unosect.obj\
    $(SLO)$/sw_unosett.obj\
    $(SLO)$/sw_unocoll.obj\
    $(SLO)$/sw_unodraw.obj\
    $(SLO)$/sw_unofield.obj\
    $(SLO)$/sw_unoframe.obj\
    $(SLO)$/sw_unoidx.obj\
    $(SLO)$/sw_unoobj.obj\
    $(SLO)$/sw_unoobj2.obj\
    $(SLO)$/sw_unoparagraph.obj\
    $(SLO)$/sw_unoport.obj\
    $(SLO)$/sw_unoredline.obj\
    $(SLO)$/sw_unoredlines.obj\
    $(SLO)$/sw_unosrch.obj\
    $(SLO)$/sw_unostyle.obj\
    $(SLO)$/sw_unotbl.obj \
    $(SLO)$/sw_TextCursorHelper.obj \
    $(SLO)$/sw_unotext.obj

.IF "$(GUI)$(COM)$(CPU)" == "WNTMSCI"
EXCEPTIONSNOOPTFILES =$(SLO)$/sw_unoportenum.obj
.ELSE
EXCEPTIONSFILES +=$(SLO)$/sw_unoportenum.obj
.ENDIF


SLOFILES =	\
        $(SLO)$/sw_swunohelper.obj\
        $(SLO)$/sw_SwXTextDefaults.obj\
        $(SLO)$/sw_unoportenum.obj\
    $(SLO)$/sw_unobkm.obj\
    $(SLO)$/sw_unoevent.obj\
    $(SLO)$/sw_unocrsrhelper.obj\
    $(SLO)$/sw_unoevtlstnr.obj\
    $(SLO)$/sw_unoftn.obj\
    $(SLO)$/sw_unorefmk.obj\
    $(SLO)$/sw_unosect.obj\
    $(SLO)$/sw_unosett.obj\
    $(SLO)$/sw_unocoll.obj\
    $(SLO)$/sw_unodraw.obj\
    $(SLO)$/sw_unofield.obj\
    $(SLO)$/sw_unoframe.obj\
    $(SLO)$/sw_unoidx.obj\
    $(SLO)$/sw_unoobj.obj\
    $(SLO)$/sw_unoobj2.obj\
    $(SLO)$/sw_unoparagraph.obj\
    $(SLO)$/sw_unoport.obj\
    $(SLO)$/sw_unoredline.obj\
    $(SLO)$/sw_unoredlines.obj\
    $(SLO)$/sw_unosrch.obj\
    $(SLO)$/sw_unostyle.obj\
    $(SLO)$/sw_unotbl.obj \
    $(SLO)$/sw_TextCursorHelper.obj \
    $(SLO)$/sw_unotext.obj\
        $(SLO)$/sw_unoclbck.obj\
        $(SLO)$/sw_unomap.obj\
        $(SLO)$/sw_unoprnms.obj



# --- Targets -------------------------------------------------------


.INCLUDE :	target.mk

