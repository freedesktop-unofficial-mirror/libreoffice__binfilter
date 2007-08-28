/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sbintern.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: vg $ $Date: 2007-08-28 11:04:23 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#include "sbintern.hxx"
#include "sbunoobj.hxx"
#include "token.hxx"                // Tokenizer
/*?*/ // #include "symtbl.hxx"              // Symbolverwaltung
/*?*/ // #include "parser.hxx"              // Parser
#include "codegen.hxx"              // Code-Generator
#include "basmgr.hxx"

namespace binfilter {

SV_IMPL_PTRARR(SbErrorStack, SbErrorStackEntry*)

SbiGlobals* GetSbData()
{
    DBG_TESTSOLARMUTEX();
    static SbiGlobals* s_pGlobals = new SbiGlobals;
    return s_pGlobals;
}

SbiGlobals::SbiGlobals()
{
    pInst = NULL;
    pMod  = NULL;
    pSbFac= NULL;
    pUnoFac = NULL;
    pTypeFac = NULL;
    pOLEFac = NULL;
    pCompMod = NULL; // JSM
    nInst = 0;
    nCode = 0;
    nLine = 0;
    nCol1 = nCol2 = 0;
    bCompiler = FALSE;
    bGlobalInitErr = FALSE;
    bRunInit = FALSE;
    eLanguageMode = SB_LANG_BASIC;
    pErrStack = NULL;
    pTransliterationWrapper = NULL;
    bBlockCompilerError = FALSE;
    pAppBasMgr = NULL;
}

SbiGlobals::~SbiGlobals()
{
    delete pErrStack;
    delete pSbFac;
    delete pUnoFac;
    delete pTransliterationWrapper;
}

}
