/*************************************************************************
 *
 *  $RCSfile: impex.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-06-24 11:45:27 $
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

#ifndef SC_IMPEX_HXX
#define SC_IMPEX_HXX

#ifndef _SOT_EXCHANGE_HXX //autogen
#include <sot/exchange.hxx>
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
#ifndef _OSL_ENDIAN_H_
#include <osl/endian.h>
#endif
class SvStream;
namespace binfilter {

class ScDocShell;
class ScDocument;
class SfxMedium;
class ScAsciiOptions;

class ScImportExport
{
    ScDocShell* pDocSh;
    ScDocument* pDoc;
    ScDocument* pUndoDoc;
    ScRange     aRange;
    String      aStreamPath;
    String      aNonConvertibleChars;
    ULONG       nSizeLimit;
    sal_Unicode cSep;                   // Separator
    sal_Unicode cStr;                   // String Delimiter
    BOOL        bFormulas;              // Formeln im Text?
    BOOL        bIncludeFiltered;       // include filtered rows? (default true)
    BOOL        bAll;                   // keine Selektion
    BOOL        bSingle;                // Einfachselektion
    BOOL        bUndo;                  // Mit Undo?
    BOOL        bOverflow;              // zuviele Zeilen/Spalten

    ScAsciiOptions* pExtOptions;        // erweiterte Optionen

//STRIP001  BOOL StartPaste();                  // Protect-Check, Undo einrichten
//STRIP001  void EndPaste();                    // Undo/Redo-Aktionen, Repaint
//STRIP001  BOOL Doc2Text( SvStream& );
//STRIP001  BOOL Text2Doc( SvStream& );
//STRIP001  BOOL Doc2Sylk( SvStream& );
//STRIP001  BOOL Sylk2Doc( SvStream& );
//STRIP001  BOOL Doc2HTML( SvStream& );
//STRIP001  BOOL Doc2RTF( SvStream& );
//STRIP001  BOOL Doc2Dif( SvStream& );
//STRIP001  BOOL Dif2Doc( SvStream& );
    BOOL ExtText2Doc( SvStream& );      // mit pExtOptions
//STRIP001  BOOL RTF2Doc( SvStream& );
//STRIP001  BOOL HTML2Doc( SvStream& );

    //! only if stream is only used in own (!) memory
//STRIP001  static  inline  void    SetNoEndianSwap( SvStream& rStrm );

public:
    ScImportExport( ScDocument* );                  // Gesamtdokument
//STRIP001  ScImportExport( ScDocument*, const String& );   // Bereichs/Zellangabe
//STRIP001  ScImportExport( ScDocument*, const ScAddress& );
//STRIP001  ScImportExport( ScDocument*, const ScRange& );
   ~ScImportExport();

    void SetExtOptions( const ScAsciiOptions& rOpt );

    BOOL IsDoubleRef() const { return BOOL( !( bAll || bSingle ) ); }
    BOOL IsSingleRef() const { return bSingle; }
    BOOL IsNoRef() const     { return bAll;    }
    BOOL IsRef() const       { return BOOL( !bAll ); }

    const ScRange& GetRange() const { return aRange; }

    BOOL IsUndo() const      { return bUndo; }
    void SetUndo( BOOL b )   { bUndo = b;    }

//STRIP001  static BOOL  IsFormatSupported( ULONG nFormat );
    static const sal_Unicode* ScanNextFieldFromString( const sal_Unicode* p,
            String& rField, sal_Unicode cStr, const sal_Unicode* pSeps, BOOL bMergeSeps );
//STRIP001  static  void    WriteUnicodeOrByteString( SvStream& rStrm, const String& rString, BOOL bZero = FALSE );
//STRIP001  static  void    WriteUnicodeOrByteEndl( SvStream& rStrm );
    static  inline  BOOL    IsEndianSwap( const SvStream& rStrm );

    sal_Unicode GetSeparator() const { return cSep; }
    void SetSeparator( sal_Unicode c ) { cSep = c; }
    sal_Unicode GetDelimiter() const { return cStr; }
    void SetDelimiter( sal_Unicode c ) { cStr = c; }
    BOOL IsFormulas() const { return bFormulas; }
    void SetFormulas( BOOL b ) { bFormulas = b; }
    BOOL IsIncludeFiltered() const { return bIncludeFiltered; }
    void SetIncludeFiltered( BOOL b ) { bIncludeFiltered = b; }

    void SetSizeLimit( ULONG nNew ) { nSizeLimit = nNew; }  // momentan nur fuer Ascii

    void            SetStreamPath( const String& rPath ) { aStreamPath = rPath; }
    const String&   GetStreamPath() const { return aStreamPath; }

//STRIP001     BOOL ImportString( const ::rtl::OUString&, ULONG=FORMAT_STRING );
//STRIP001  BOOL ExportString( ::rtl::OUString&, ULONG=FORMAT_STRING );
//STRIP001  BOOL ExportByteString( ByteString&, rtl_TextEncoding, ULONG=FORMAT_STRING );

    BOOL ImportStream( SvStream&, ULONG=FORMAT_STRING );
//STRIP001  BOOL ExportStream( SvStream&, ULONG=FORMAT_STRING );

//STRIP001  BOOL ImportData( const String& rMimeType,
//STRIP001                   const ::com::sun::star::uno::Any & rValue );
//STRIP001  BOOL ExportData( const String& rMimeType,
//STRIP001                   ::com::sun::star::uno::Any & rValue  );

    BOOL IsOverflow() const { return bOverflow; }       // nach dem Importieren

    const String& GetNonConvertibleChars() const { return aNonConvertibleChars; }
};


// static
inline BOOL ScImportExport::IsEndianSwap( const SvStream& rStrm )
{
#ifdef OSL_BIGENDIAN
    return rStrm.GetNumberFormatInt() != NUMBERFORMAT_INT_BIGENDIAN;
#else
    return rStrm.GetNumberFormatInt() != NUMBERFORMAT_INT_LITTLEENDIAN;
#endif
}


} //namespace binfilter
#endif

