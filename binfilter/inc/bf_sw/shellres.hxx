/*************************************************************************
 *
 *  $RCSfile: shellres.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:34:08 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef _SHELLRES_HXX
#define _SHELLRES_HXX


#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif

#ifndef _BITMAP_HXX //autogen
#include <vcl/bitmap.hxx>
#endif

#ifndef _SVSTDARR_HXX
#define _SVSTDARR_STRINGSDTOR
#include <svtools/svstdarr.hxx>
#endif
namespace binfilter {

struct ShellResource : public Resource
{
    String          aPostItAuthor;
    String          aPostItPage;
    String          aPostItLine;

    // Calc Fehlerstrings
    String          aCalc_Syntax;
    String          aCalc_ZeroDiv;
    String          aCalc_Brack;
    String          aCalc_Pow;
    String          aCalc_VarNFnd;
    String          aCalc_Overflow;
    String          aCalc_WrongTime;
    String          aCalc_Default;
    String          aCalc_Error;

    // fuers GetRefFeld - oben/unten
    String          aGetRefFld_Up, aGetRefFld_Down;
    // fuer dynamisches Menu - String "alle"
    String          aStrAllPageHeadFoot;
    // fuer einige Listboxen - String "keine"
    String          aStrNone;
    // fuer Felder, die Fixiert sind
    String          aFixedStr;

    //names of TOXs
    String          aTOXIndexName;
    String          aTOXUserName;
    String          aTOXContentName;
    String          aTOXIllustrationsName;
    String          aTOXObjectsName;
    String          aTOXTablesName;
    String          aTOXAuthoritiesName;

    SvStringsDtor   aDocInfoLst;

    // Fly-Anker Bmps
//  Bitmap          aAnchorBmp;
//  Bitmap          aDragAnchorBmp;

    // die AutoFormat-Redline-Kommentare
    inline const SvStringsDtor& GetAutoFmtNameLst() const;

    // returns for the specific filter the new names of pagedescs
    // This method is for the old code of the specific filters with
    // now localized names
//STRIP001  String GetPageDescName( USHORT nNo, BOOL bFirst = FALSE,
//STRIP001                                      BOOL bFollow = FALSE );

    ShellResource();
    ~ShellResource();

private:
    void _GetAutoFmtNameLst() const;
    SvStringsDtor   *pAutoFmtNameLst;
    String          sPageDescFirstName, sPageDescFollowName, sPageDescName;
};

inline const SvStringsDtor& ShellResource::GetAutoFmtNameLst() const
{
    if( !pAutoFmtNameLst )
        _GetAutoFmtNameLst();
    return *pAutoFmtNameLst;
}


} //namespace binfilter
#endif //_SHELLRES_HXX
