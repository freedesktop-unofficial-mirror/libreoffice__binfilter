/*************************************************************************
 *
 *  $RCSfile: asciiopt.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:18:29 $
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

//STRIP001  ScAsciiOptions& operator=( const ScAsciiOptions& rCpy );

//STRIP001  BOOL            operator==( const ScAsciiOptions& rCmp ) const;

    void            ReadFromString( const String& rString );
    String          WriteToString() const;

//STRIP001  void            InterpretColumnList( const String& rString );

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

//STRIP001  void    SetColInfo( USHORT nCount, const xub_StrLen* pStart, const BYTE* pFormat );
//STRIP001     void    SetColumnInfo( const ScCsvExpDataVec& rDataVec );
};


// ============================================================================

//STRIP001 class ScImportAsciiDlg : public ModalDialog
//STRIP001 {
//STRIP001     SvStream*                   pDatStream;
//STRIP001     ULONG*                      pRowPosArray;
//STRIP001     ULONG*                      pRowPosArrayUnicode;
//STRIP001     USHORT                      nArrayEndPos;
//STRIP001     USHORT                      nArrayEndPosUnicode;
//STRIP001     ULONG                       nStreamPos;
//STRIP001     ULONG                       nStreamPosUnicode;
//STRIP001     BOOL                        bVFlag;
//STRIP001
//STRIP001     FixedLine                   aFlFieldOpt;
//STRIP001     FixedText                   aFtCharSet;
//STRIP001 //STRIP001     SvxTextEncodingBox          aLbCharSet;
//STRIP001
//STRIP001     FixedText                   aFtRow;
//STRIP001     NumericField                aNfRow;
//STRIP001
//STRIP001     FixedLine                   aFlSepOpt;
//STRIP001     RadioButton                 aRbFixed;
//STRIP001     RadioButton                 aRbSeparated;
//STRIP001
//STRIP001     CheckBox                    aCkbTab;
//STRIP001     CheckBox                    aCkbSemicolon;
//STRIP001     CheckBox                    aCkbComma;
//STRIP001     CheckBox                    aCkbSpace;
//STRIP001     CheckBox                    aCkbOther;
//STRIP001     Edit                        aEdOther;
//STRIP001     CheckBox                    aCkbAsOnce;
//STRIP001     FixedText                   aFtTextSep;
//STRIP001     ComboBox                    aCbTextSep;
//STRIP001
//STRIP001     FixedLine                   aFlWidth;
//STRIP001     FixedText                   aFtType;
//STRIP001     ListBox                     aLbType;
//STRIP001
//STRIP001     ScCsvTableBox               maTableBox;
//STRIP001
//STRIP001     OKButton                    aBtnOk;
//STRIP001     CancelButton                aBtnCancel;
//STRIP001     HelpButton                  aBtnHelp;
//STRIP001
//STRIP001     String                      aCharSetUser;
//STRIP001     String                      aColumnUser;
//STRIP001     String                      aFldSepList;
//STRIP001     String                      aTextSepList;
//STRIP001
//STRIP001  // aPreviewLine contains the byte string as read from the file
//STRIP001     ByteString                  aPreviewLine[ CSV_PREVIEW_LINES ];
//STRIP001  // same for Unicode
//STRIP001     String                      aPreviewLineUnicode[ CSV_PREVIEW_LINES ];
//STRIP001
//STRIP001     CharSet                     meCharSet;          /// Selected char set.
//STRIP001     bool                        mbCharSetSystem;    /// Is System char set selected?
//STRIP001
//STRIP001 public:
//STRIP001                                 ScImportAsciiDlg(
//STRIP001                                     Window* pParent, String aDatName,
//STRIP001                                  SvStream* pInStream, sal_Unicode cSep = '\t' );
//STRIP001                                 ~ScImportAsciiDlg();
//STRIP001
//STRIP001     void                        GetOptions( ScAsciiOptions& rOpt );
//STRIP001
//STRIP001 private:
//STRIP001     /** Sets the selected char set data to meCharSet and mbCharSetSystem. */
//STRIP001  void                        SetSelectedCharSet();
//STRIP001     /** Returns all separator characters in a string. */
//STRIP001     String                      GetSeparators() const;
//STRIP001
//STRIP001     /** Enables or disables all separator checkboxes and edit fields. */
//STRIP001     void                        SetupSeparatorCtrls();
//STRIP001
//STRIP001 //STRIP001     void                        UpdateVertical( bool bSwitchToFromUnicode = false );
//STRIP001
//STRIP001                                 DECL_LINK( CharSetHdl, SvxTextEncodingBox* );
//STRIP001                                 DECL_LINK( FirstRowHdl, NumericField* );
//STRIP001                                 DECL_LINK( RbSepFixHdl, RadioButton* );
//STRIP001                                 DECL_LINK( SeparatorHdl, Control* );
//STRIP001                                 DECL_LINK( LbColTypeHdl, ListBox* );
//STRIP001                                 DECL_LINK( UpdateTextHdl, ScCsvTableBox* );
//STRIP001                                 DECL_LINK( ColTypeHdl, ScCsvTableBox* );
//STRIP001 };


// ============================================================================

#endif

