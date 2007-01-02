/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: asciiopt.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:04:07 $
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

// ============================================================================

#ifndef SC_ASCIIOPT_HXX
#define SC_ASCIIOPT_HXX

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _DIALOG_HXX //autogen
#include <vcl/dialog.hxx>
#endif
#ifndef _BUTTON_HXX //autogen
#include <vcl/button.hxx>
#endif
#ifndef _FIXED_HXX //autogen
#include <vcl/fixed.hxx>
#endif
#ifndef _LSTBOX_HXX //autogen
#include <vcl/lstbox.hxx>
#endif
#ifndef _COMBOBOX_HXX //autogen
#include <vcl/combobox.hxx>
#endif
#ifndef _FIELD_HXX //autogen
#include <vcl/field.hxx>
#endif
#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif
#ifndef _SVX_TXENCBOX_HXX
#include <bf_svx/txencbox.hxx>
#endif

#ifndef _SC_CSVTABLEBOX_HXX
#include "csvtablebox.hxx"
#endif
namespace binfilter {


// ============================================================================

class ScAsciiOptions
{
private:
    BOOL        bFixedLen;
    String      aFieldSeps;
    BOOL        bMergeFieldSeps;
    sal_Unicode cTextSep;
    CharSet     eCharSet;
    BOOL        bCharSetSystem;
    long        nStartRow;
    USHORT      nInfoCount;
    xub_StrLen* pColStart;  //! TODO replace with vector
    BYTE*       pColFormat; //! TODO replace with vector

public:
                    ScAsciiOptions();
                    ScAsciiOptions(const ScAsciiOptions& rOpt);
                    ~ScAsciiOptions();



    void            ReadFromString( const String& rString );


    CharSet             GetCharSet() const      { return eCharSet; }
    BOOL                GetCharSetSystem() const    { return bCharSetSystem; }
    const String&       GetFieldSeps() const    { return aFieldSeps; }
    BOOL                IsMergeSeps() const     { return bMergeFieldSeps; }
    sal_Unicode         GetTextSep() const      { return cTextSep; }
    BOOL                IsFixedLen() const      { return bFixedLen; }
    USHORT              GetInfoCount() const    { return nInfoCount; }
    const xub_StrLen*   GetColStart() const     { return pColStart; }
    const BYTE*         GetColFormat() const    { return pColFormat; }
    long                GetStartRow() const     { return nStartRow; }

    void    SetCharSet( CharSet eNew )          { eCharSet = eNew; }
    void    SetCharSetSystem( BOOL bSet )       { bCharSetSystem = bSet; }
    void    SetFixedLen( BOOL bSet )            { bFixedLen = bSet; }
    void    SetFieldSeps( const String& rStr )  { aFieldSeps = rStr; }
    void    SetMergeSeps( BOOL bSet )           { bMergeFieldSeps = bSet; }
    void    SetTextSep( sal_Unicode c )         { cTextSep = c; }
    void    SetStartRow( long nRow)             { nStartRow= nRow; }

};


// ============================================================================



// ============================================================================

} //namespace binfilter
#endif

