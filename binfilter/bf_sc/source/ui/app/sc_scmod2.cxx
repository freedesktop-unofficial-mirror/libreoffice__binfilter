/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_scmod2.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 07:03:04 $
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

#ifdef PCH
#include "ui_pch.hxx"
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

//------------------------------------------------------------------

#include <bf_svx/unolingu.hxx>
#include <bf_svtools/lingucfg.hxx>

#include <com/sun/star/linguistic2/XThesaurus.hpp>
#include <com/sun/star/lang/Locale.hpp>

using namespace ::com::sun::star;

#include "scmod.hxx"
namespace binfilter {

//------------------------------------------------------------------

//#define LINGUPROP_DEFLOCALE           "DefaultLocale"
//#define LINGUPROP_CJKLOCALE           "DefaultLocale_CJK"
//#define LINGUPROP_CTLLOCALE           "DefaultLocale_CTL"
#define LINGUPROP_AUTOSPELL         "IsSpellAuto"
#define LINGUPROP_HIDEAUTO          "IsSpellHide"

//------------------------------------------------------------------

// static
/*N*/ void ScModule::GetSpellSettings( USHORT& rDefLang, USHORT& rCjkLang, USHORT& rCtlLang,
/*N*/                                   BOOL& rAutoSpell, BOOL& rHideAuto )
/*N*/ {
/*N*/   //  use SvtLinguConfig instead of service LinguProperties to avoid
/*N*/   //  loading the linguistic component
/*N*/   SvtLinguConfig aConfig;
/*N*/
/*N*/   SvtLinguOptions aOptions;
/*N*/   aConfig.GetOptions( aOptions );
/*N*/
/*N*/   rDefLang = aOptions.nDefaultLanguage;
/*N*/   rCjkLang = aOptions.nDefaultLanguage_CJK;
/*N*/   rCtlLang = aOptions.nDefaultLanguage_CTL;
/*N*/   rAutoSpell = aOptions.bIsSpellAuto;
/*N*/   rHideAuto = aOptions.bIsSpellHideMarkings;
/*N*/ }

// static

// static


// static


}
