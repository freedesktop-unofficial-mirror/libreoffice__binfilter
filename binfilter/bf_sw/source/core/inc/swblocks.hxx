/*************************************************************************
 *
 *  $RCSfile: swblocks.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 15:22:49 $
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
#ifndef _SWBLOCKS_HXX
#define _SWBLOCKS_HXX

#ifndef _DATE_HXX //autogen
#include <tools/date.hxx>
#endif
#ifndef _PERSIST_HXX //autogen
#include <so3/persist.hxx>
#endif
#ifndef _SVARRAY_HXX //autogen
#include <svtools/svarray.hxx>
#endif
/*N*/#include <tools/debug.hxx> //addded for stripping

class SfxMedium;
class SwPaM;
class SwDoc;
class SvxMacroTableDtor;
class SvXMLTextBlocks;
// Name eines Textblocks:

//STRIP001 class SwBlockName
//STRIP001 {
//STRIP001  friend class SwImpBlocks;
//STRIP001  friend class Sw2TextBlocks;
//STRIP001  USHORT nHashS, nHashL;              // Hash-Codes zum Checken
//STRIP001  long   nPos;                        // Dateiposition (SW2-Format)
//STRIP001 public:
//STRIP001  String aShort;                      // Short name
//STRIP001  String aLong;                       // Long name
//STRIP001  String aPackageName;                // Package name
//STRIP001  BOOL bIsOnlyTxtFlagInit : 1;        // ist das Flag gueltig?
//STRIP001  BOOL bIsOnlyTxt : 1;                // unformatted text
//STRIP001  BOOL bInPutMuchBlocks : 1;          // put serveral block entries
//STRIP001
//STRIP001  SwBlockName( const String& rShort, const String& rLong, long n );
//STRIP001  SwBlockName( const String& rShort, const String& rLong, const String& rPackageName );
//STRIP001
//STRIP001  // fuer das Einsortieren in das Array
//STRIP001  int operator==( const SwBlockName& r ) { return aShort == r.aShort; }
//STRIP001  int operator< ( const SwBlockName& r ) { return aShort <  r.aShort; }
//STRIP001 };

//STRIP001 SV_DECL_PTRARR_SORT( SwBlockNames, SwBlockName*, 10, 10 );


class SwImpBlocks
{
    friend class SwTextBlocks;
protected:
    String aFile;                       // physikalischer Dateiname
    String aName;                       // logischer Name der Datei
//STRIP001  String aCur;                        // aktueller Text
//STRIP001  String aShort, aLong;               // Kurz- und Langname (PutDoc)
//STRIP001  SwBlockNames aNames;                // Liste aller Bausteine
//STRIP001  Date aDateModified;                 // fuers abgleichen bei den Aktionen
//STRIP001  Time aTimeModified;
//STRIP001  SwDoc* pDoc;                        // Austauschdokument
//STRIP001  USHORT nCur;                        // aktueller Index
//STRIP001  BOOL bReadOnly : 1;
//STRIP001  BOOL bInPutMuchBlocks : 1;          // put serveral block entries
//STRIP001  BOOL bInfoChanged : 1;              // any Info of TextBlock is changed
//STRIP001
    SwImpBlocks( const String&, BOOL = FALSE ){DBG_ASSERT(0, "STRIP")}; //STRIP001 ;
//STRIP001  virtual ~SwImpBlocks();
//STRIP001
//STRIP001  static short GetFileType( const String& );
//STRIP001  virtual short GetFileType() const = 0;
//STRIP001 #define  SWBLK_NO_FILE   0               // nicht da
//STRIP001 #define  SWBLK_NONE      1               // keine TB-Datei
//STRIP001 #define  SWBLK_SW2       2               // SW2-Datei
//STRIP001 #define  SWBLK_SW3       3               // SW3-Datei
//STRIP001 #define  SWBLK_XML       4               // XML Block List
//STRIP001
//STRIP001  virtual void   ClearDoc();                  // Doc-Inhalt loeschen
//STRIP001  SwPaM* MakePaM();                   // PaM ueber Doc aufspannen
//STRIP001  virtual void   AddName( const String&, const String&, BOOL bOnlyTxt = FALSE );
//STRIP001  BOOL   IsFileChanged() const;
//STRIP001  void   Touch();
//STRIP001
public:
//STRIP001  static USHORT Hash( const String& );        // Hashcode fuer Blocknamen
//STRIP001  USHORT GetCount() const;                    // Anzahl Textbausteine ermitteln
//STRIP001  USHORT GetIndex( const String& ) const;     // Index fuer Kurznamen ermitteln
//STRIP001  USHORT GetLongIndex( const String& ) const; //Index fuer Langnamen ermitteln
//STRIP001  const String& GetShortName( USHORT ) const; // Kurzname fuer Index zurueck
//STRIP001  const String& GetLongName( USHORT ) const;  // Langname fuer Index zurueck
//STRIP001  const String& GetPackageName( USHORT ) const;   // Langname fuer Index zurueck
//STRIP001
    const String& GetFileName() const {return aFile;}   // phys. Dateinamen liefern
//STRIP001  void SetName( const String& rName )                 // logic name
//STRIP001      { aName = rName; bInfoChanged = TRUE; }
//STRIP001  const String & GetName( void )
//STRIP001      { return aName; }
//STRIP001
//STRIP001  virtual ULONG Delete( USHORT ) = 0;
//STRIP001  virtual ULONG Rename( USHORT, const String&, const String& ) = 0;
//STRIP001  virtual ULONG CopyBlock( SwImpBlocks& rImp, String& rShort, const String& rLong) = 0;
//STRIP001  virtual ULONG GetDoc( USHORT ) = 0;
//STRIP001  virtual ULONG GetDocForConversion( USHORT );
//STRIP001  virtual ULONG BeginPutDoc( const String&, const String& ) = 0;
//STRIP001  virtual ULONG PutDoc() = 0;
//STRIP001  virtual ULONG GetText( USHORT, String& ) = 0;
//STRIP001  virtual ULONG PutText( const String&, const String&, const String& ) = 0;
//STRIP001  virtual ULONG MakeBlockList() = 0;
//STRIP001
//STRIP001  virtual ULONG OpenFile( BOOL bReadOnly = TRUE ) = 0;
//STRIP001  virtual void  CloseFile() = 0;
//STRIP001
//STRIP001  virtual BOOL IsOnlyTextBlock( const String& rShort ) const;
//STRIP001
//STRIP001  virtual ULONG GetMacroTable( USHORT nIdx, SvxMacroTableDtor& rMacroTbl,
//STRIP001                               sal_Bool bFileAlreadyOpen = sal_False );
//STRIP001  virtual ULONG SetMacroTable( USHORT nIdx,
//STRIP001                               const SvxMacroTableDtor& rMacroTbl,
//STRIP001                               sal_Bool bFileAlreadyOpen = sal_False );
//STRIP001  virtual BOOL PutMuchEntries( BOOL bOn );
};

//STRIP001 class Sw3Persist : public SvPersist
//STRIP001 {
//STRIP001  virtual void FillClass( SvGlobalName * pClassName,
//STRIP001                          ULONG * pClipFormat,
//STRIP001                          String * pAppName,
//STRIP001                          String * pLongUserName,
//STRIP001                          String * pUserName,
//STRIP001                          long nFileFormat=SOFFICE_FILEFORMAT_CURRENT ) const;
//STRIP001  virtual BOOL Save();
//STRIP001  virtual BOOL SaveCompleted( SvStorage * );
//STRIP001 public:
//STRIP001  Sw3Persist();
//STRIP001 };

//STRIP001 class SwSwgReader;

//STRIP001 class Sw2TextBlocks : public SwImpBlocks
//STRIP001 {
//STRIP001  SvPersistRef refPersist;            // Fuer OLE-Objekte
//STRIP001  SwSwgReader* pRdr;                  // Lese-Routinen
//STRIP001  SfxMedium* pMed;                    // der logische Input-Stream
//STRIP001  String* pText;                      // String fuer GetText()
//STRIP001  long   nDocStart;                   // Beginn des Doc-Records
//STRIP001  long   nDocSize;                    // Laenge des Doc-Records
//STRIP001  long   nStart;                      // Beginn des CONTENTS-Records
//STRIP001  long   nSize;                       // Laenge des CONTENTS-Records
//STRIP001  USHORT nNamedFmts;                  // benannte Formate
//STRIP001  USHORT nColls;                      // Text-Collections
//STRIP001  USHORT nBlks;                       // Anzahl Elemente im CONTENTS-Record
//STRIP001 public:
//STRIP001  Sw2TextBlocks( const String& );
//STRIP001  virtual ~Sw2TextBlocks();
//STRIP001  virtual ULONG Delete( USHORT );
//STRIP001  virtual ULONG Rename( USHORT, const String&, const String& );
//STRIP001  virtual ULONG CopyBlock( SwImpBlocks& rImp, String& rShort, const String& rLong);
//STRIP001  virtual ULONG GetDoc( USHORT );
//STRIP001  virtual ULONG BeginPutDoc( const String&, const String& );
//STRIP001  virtual ULONG PutDoc();
//STRIP001  virtual ULONG GetText( USHORT, String& );
//STRIP001  virtual ULONG PutText( const String&, const String&, const String& );
//STRIP001  virtual ULONG MakeBlockList();
//STRIP001  virtual short GetFileType( ) const;
//STRIP001  ULONG LoadDoc();
//STRIP001
//STRIP001  virtual ULONG OpenFile( BOOL bReadOnly = TRUE );
//STRIP001  virtual void  CloseFile();
//STRIP001
//STRIP001  void StatLineStartPercent();                // zum Anzeigen des Prozessbars
//STRIP001 };

class Sw3Io;
class Sw3IoImp;

class Sw3TextBlocks : public SwImpBlocks
{
//STRIP001  Sw3Io*       pIo3;
//STRIP001  Sw3IoImp*    pImp;
//STRIP001  BOOL         bAutocorrBlock;

public:
    Sw3TextBlocks( const String& rFile): SwImpBlocks( rFile ){DBG_ASSERT(0, "STRIP");} ;//STRIP001  Sw3TextBlocks( const String& );
//STRIP001  Sw3TextBlocks( SvStorage& );
//STRIP001  virtual ~Sw3TextBlocks();
//STRIP001  virtual ULONG Delete( USHORT );
//STRIP001  virtual ULONG Rename( USHORT, const String&, const String& );
//STRIP001  virtual ULONG CopyBlock( SwImpBlocks& rImp, String& rShort, const String& rLong);
//STRIP001  virtual ULONG GetDoc( USHORT );
//STRIP001  virtual ULONG GetDocForConversion( USHORT );
//STRIP001  virtual ULONG BeginPutDoc( const String&, const String& );
//STRIP001  virtual ULONG PutDoc();
//STRIP001  virtual void SetDoc( SwDoc * pNewDoc);
//STRIP001  virtual ULONG GetText( USHORT, String& );
//STRIP001  virtual ULONG PutText( const String&, const String&, const String& );
//STRIP001  virtual ULONG MakeBlockList();
//STRIP001  virtual short GetFileType( ) const;

//STRIP001  virtual ULONG OpenFile( BOOL bReadOnly = TRUE );
//STRIP001  virtual void  CloseFile();

//STRIP001  ULONG SetConvertMode( BOOL );

    // Methoden fuer die neue Autokorrektur
//STRIP001  ULONG GetText( const String& rShort, String& );
//STRIP001  SwDoc* GetDoc() const { return pDoc; }

//STRIP001  virtual BOOL IsOnlyTextBlock( const String& rShort ) const;

//STRIP001  virtual ULONG GetMacroTable( USHORT, SvxMacroTableDtor& rMacroTbl,
//STRIP001                               sal_Bool bFileAlreadyOpen = sal_False );
//STRIP001  virtual ULONG SetMacroTable( USHORT nIdx,
//STRIP001                               const SvxMacroTableDtor& rMacroTbl,
//STRIP001                               sal_Bool bFileAlreadyOpen = sal_False );

//STRIP001  void ReadInfo();
};

#endif
