/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: codegen.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: obo $ $Date: 2007-03-15 15:08:26 $
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

#ifndef _CODEGEN_HXX
#define _CODEGEN_HXX

/*?*/ // #include "opcodes.hxx"
/*?*/ // #include "buffer.hxx"

namespace binfilter {

class SbiImage;
class SbiParser;
class SbModule;

class SbiCodeGen {              // Code-Erzeugung:
/*?*/ //    SbiParser* pParser;         // fuer Fehlermeldungen, Line, Column etc.
/*?*/ //    SbModule& rMod;             // aktuelles Modul
/*?*/ //    SbiBuffer aCode;                // Code-Puffer
/*?*/ //    short  nLine, nCol;         // Zeile, Spalte fuer Stmnt-Befehl
/*?*/ //    short  nForLevel;           // #29955 for-Schleifen-Ebene
/*?*/ //    BOOL bStmnt;                // TRUE: Statement-Opcode liegt an
public:
/*?*/ //    SbiCodeGen( SbModule&, SbiParser*, short );
/*?*/ //    SbiParser* GetParser() { return pParser; }
/*?*/ //    UINT32 Gen( SbiOpcode );
/*?*/ //    UINT32 Gen( SbiOpcode, UINT32 );
/*?*/ //    UINT32 Gen( SbiOpcode, UINT32, UINT32 );
/*?*/ //    void Patch( UINT32 o, UINT32 v ){ aCode.Patch( o, v ); }
/*?*/ //    void BackChain( UINT32 off )    { aCode.Chain( off );  }
/*?*/ //    void Statement();
/*?*/ //    void GenStmnt();            // evtl. Statement-Opcode erzeugen
/*?*/ //    UINT32 GetPC();
/*?*/ //    UINT32 GetOffset()              { return GetPC() + 1; }
/*?*/ //    void Save();
/*?*/ //
/*?*/ //    // #29955 for-Schleifen-Ebene pflegen
/*?*/ //    void IncForLevel( void ) { nForLevel++; }
/*?*/ //    void DecForLevel( void ) { nForLevel--; }
/*?*/ //
    static UINT32 calcNewOffSet( BYTE* pCode, UINT16 nOffset );
    static UINT16 calcLegacyOffSet( BYTE* pCode, UINT32 nOffset );
/*?*/ //
};

template < class T, class S >
class PCodeBuffConvertor
{
    T m_nSize; //
    BYTE* m_pStart;
    BYTE* m_pCnvtdBuf;
    S m_nCnvtdSize; //

    //  Disable usual copying symantics and bodgy default ctor
    PCodeBuffConvertor();
    PCodeBuffConvertor(const PCodeBuffConvertor& );
    PCodeBuffConvertor& operator = ( const PCodeBuffConvertor& );
public:
    PCodeBuffConvertor( BYTE* pCode, T nSize ): m_nSize( nSize ),  m_pStart( pCode ), m_pCnvtdBuf( NULL ), m_nCnvtdSize( 0 ){ convert(); }
    S GetSize(){ return m_nCnvtdSize; }
    void convert();
    // Caller owns the buffer returned
    BYTE* GetBuffer() { return m_pCnvtdBuf; }
};

// #111897 PARAM_INFO flags start at 0x00010000 to not
// conflict with DefaultId in SbxParamInfo::nUserData
#define PARAM_INFO_PARAMARRAY   0x0010000

}

#endif
