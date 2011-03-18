/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/



#ifdef _MSC_VER
#pragma hdrstop
#endif


#define _SVSTDARR_STRINGS

#include <rsc/rscsfx.hxx>

#include <comphelper/processfactory.hxx>
#include <com/sun/star/xml/sax/InputSource.hpp>
#include <com/sun/star/xml/sax/XParser.hpp>
#include <com/sun/star/io/XActiveDataControl.hpp>
#include <com/sun/star/text/XTextRange.hpp>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/beans/PropertyAttribute.hpp>
#include <com/sun/star/task/XStatusIndicatorFactory.hpp>
#include <com/sun/star/io/XActiveDataSource.hpp>
#include <com/sun/star/packages/zip/ZipIOException.hpp>
#include <bf_svtools/svstdarr.hxx>

#include <bf_sfx2/appuno.hxx>

#include <bf_sfx2/docfile.hxx>
#include <bf_svtools/sfxecode.hxx>
#include <unotools/streamwrap.hxx>
#include <bf_svx/xmlgrhlp.hxx>
#include <bf_svx/xmleohlp.hxx>
#include <comphelper/genericpropertyset.hxx>
#include <rtl/logfile.hxx>

#include <swerror.h>
#include <osl/diagnose.h>

#include "swtypes.hxx"

#include <fltini.hxx>

#include <horiornt.hxx>

#include <doc.hxx>
#include <docsh.hxx>
#include <unoobj.hxx>
#include <swmodule.hxx>
#include <SwXMLSectionList.hxx>
#include <xmlimp.hxx>

#include <statstr.hrc>
#include <legacysmgr/legacy_binfilters_smgr.hxx>
#define LOGFILE_AUTHOR "mb93740"
namespace binfilter {


using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::lang;

using rtl::OUString;


void lcl_EnsureValidPam( SwPaM& rPam )
{
    if( rPam.GetCntntNode() != NULL )
    {
        // set proper point content
        if( rPam.GetCntntNode() != rPam.GetPoint()->nContent.GetIdxReg() )
        {
            rPam.GetPoint()->nContent.Assign( rPam.GetCntntNode(), 0 );
        }
        // else: point was already valid

        // if mark is invalid, we delete it
        if( ( rPam.GetCntntNode( FALSE ) == NULL ) ||
            ( rPam.GetCntntNode( FALSE ) != rPam.GetMark()->nContent.GetIdxReg() ) )
        {
            rPam.DeleteMark();
        }
    }
    else
    {
        // point is not valid, so move it into the first content
        rPam.DeleteMark();
        rPam.GetPoint()->nNode =
            *rPam.GetDoc()->GetNodes().GetEndOfContent().StartOfSectionNode();
        ++ rPam.GetPoint()->nNode;
        rPam.Move( fnMoveForward, fnGoCntnt ); // go into content
    }
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
