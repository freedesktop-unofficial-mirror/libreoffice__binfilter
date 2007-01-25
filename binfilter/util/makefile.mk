#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.8 $
#
#   last change: $Author: obo $ $Date: 2007-01-25 12:05:30 $
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

PRJ=..

PRJNAME=binfilter
TARGET=bf_util

# --- Settings ----------------------------------

.INCLUDE :  	settings.mk

# --- Files -------------------------------------

.IF "$(GUI)"=="UNX"
LOCALLIBDIR=$(LB)
.ELSE          # "$(GUI)"=="UNX"
LOCALLIBDIR=$(BIN)
.ENDIF          # "$(GUI)"=="UNX"

RDBNAMES=		\
    bf_xo		\
    bf_sw		\
    bf_sc		\
    bf_sd		\
    bf_sm		\
    bf_sch		\
    bf_frm		\
    bf_lng		\
    bf_svx		\
    bf_wrapper

RDBLIBS=$(foreach,i,$(strip $(RDBNAMES)) $(LOCALLIBDIR)$/$(DLLPRE)$i$(UPD)$(DLLPOSTFIX)$(DLLPOST))

# --- Targets ----------------------------------

.INCLUDE : target.mk

ALLTAR : $(BIN)$/legacy_binfilters.rdb

$(BIN)$/legacy_binfilters.rdb : $(RDBLIBS)
    @-$(RM) $@ >& $(NULLDEV)
    cd $(LOCALLIBDIR) && $(REGCOMP) -register -r ..$/bin$/$(@:f) -wop $(foreach,i,$(RDBLIBS) -c $(subst,$(LOCALLIBDIR)$/,./ $i))

