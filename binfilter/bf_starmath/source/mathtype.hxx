/*************************************************************************
 *
 *  $RCSfile: mathtype.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:40:21 $
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
#ifndef MATHTYPE_HXX
#define MATHTYPE_HXX

#ifndef NODE_HXX
#include "node.hxx"
#endif

#ifndef _SVSTOR_HXX
#include <so3/svstor.hxx>
#endif

#include <set>
namespace binfilter {

#define EQNOLEFILEHDR_SIZE 28
class EQNOLEFILEHDR
{
public:
    EQNOLEFILEHDR() {}
    EQNOLEFILEHDR(sal_uInt32 nLenMTEF) : nCBHdr(0x1c),nVersion(0x20000),
        nCf(0xc1c6),nCBObject(nLenMTEF),nReserved1(0),nReserved2(0x0014F690),
        nReserved3(0x0014EBB4), nReserved4(0) {}
    sal_uInt16   nCBHdr;     // length of header, sizeof(EQNOLEFILEHDR) = 28
    sal_uInt32   nVersion;   // hiword = 2, loword = 0
    sal_uInt16   nCf;        // clipboard format ("MathType EF")
    sal_uInt32   nCBObject;  // length of MTEF data following this header
    sal_uInt32   nReserved1; // not used
    sal_uInt32   nReserved2; // not used
    sal_uInt32   nReserved3; // not used
    sal_uInt32   nReserved4; // not used

//STRIP001  void Read(SvStorageStream *pS);
//STRIP001  void Write(SvStorageStream *pS);
};

class MathTypeFont
{
public:
    sal_uInt8 nTface;
    sal_uInt8 nStyle;
    MathTypeFont() : nTface(0),nStyle(0) {}
    MathTypeFont(sal_uInt8 nFace) : nTface(nFace),nStyle(0) {}
//STRIP001  void AppendStyleToText(String &rS);
};

struct LessMathTypeFont
{
    sal_Bool operator() (const MathTypeFont &rValue1,
        const MathTypeFont &rValue2) const
    {
        return rValue1.nTface < rValue2.nTface;
    }
};

typedef ::std::set< MathTypeFont, LessMathTypeFont > MathTypeFontSet;

class MathType
{
public:
    MathType(String &rIn) : bSilent(sal_False),nDefaultSize(12),nLSize(0),
        nDSize(0),nCurSize(0),nLastSize(0),nVAlign(0),nHAlign(0),rRet(rIn)
    {
        DBG_BF_ASSERT(0, "STRIP"); //STRIP001       Init();
    }
    MathType(String &rIn,SmNode *pIn) : bSilent(sal_False),nDefaultSize(12),
        nLSize(0),nDSize(0),nCurSize(0),nLastSize(0),nVAlign(0),nHAlign(2),
        pTree(pIn),rRet(rIn),nInsertion(0),nSpec(0)
    {
        DBG_BF_ASSERT(0, "STRIP"); //STRIP001Init();
    }
//STRIP001  int Parse(SvStorage *pS);
//STRIP001  int ConvertFromStarMath(SvStorage *pStor);
private:
/*Ver 2 Header*/
    sal_uInt8 nVersion;
    sal_uInt8 nPlatform;
    sal_uInt8 nProduct;
    sal_uInt8 nProdVersion;
    sal_uInt8 nProdSubVersion;

    SvStorageStream *pS;

//STRIP001  void Init();

//STRIP001  int HandleRecords(int nLevel=0,sal_uInt8 nSelector=-1,
//STRIP001      sal_uInt8 nVariation=-1,int nRows=0,int nCols=0);
//STRIP001  sal_Bool HandleSize(sal_Int16 nLSize,sal_Int16 nDSize, int &rSetSize);
//STRIP001  void HandleAlign(sal_uInt8 nHAlign,sal_uInt8 nVAlign, int &rSetAlign);
//STRIP001  int HandlePile(int &rSetAlign,int nLevel,sal_uInt8 nSelector,
//STRIP001      sal_uInt8 nVariation);
//STRIP001  int HandleMatrix(int nLevel,sal_uInt8 nSelector,sal_uInt8 nVariarion);
//STRIP001  void HandleMatrixSeperator(int nMatrixRows,int nMatrixCols,int &rCurCol,
//STRIP001      int &rCurRow);
//STRIP001  int HandleTemplate(int nLevel,sal_uInt8 &rSelector,sal_uInt8 &rVariation,
//STRIP001      xub_StrLen &rLastTemplateBracket);
//STRIP001  void HandleEmblishments();
//STRIP001  void HandleSetSize();
//STRIP001  int HandleChar(xub_StrLen &rTextStart,int &rSetSize,int nLevel,
//STRIP001      sal_uInt8 nTag,sal_uInt8 nSelector,sal_uInt8 nVariation,
//STRIP001      sal_Bool bSilent);
    int xfLMOVE(sal_uInt8 nTest) {return nTest&0x80;}
    int xfAUTO(sal_uInt8 nTest) {return nTest&0x10;}
    int xfEMBELL(sal_uInt8 nTest) {return nTest&0x20;}
    int xfNULL(sal_uInt8 nTest) {return nTest&0x10;}
    int xfLSPACE(sal_uInt8 nTest) {return nTest&0x40;}
    int xfRULER(sal_uInt8 nTest) {return nTest&0x20;}

//STRIP001  sal_uInt8 HandleNodes(SmNode *pNode,int nLevel=0);
//STRIP001  int StartTemplate(sal_uInt16 nSelector,sal_uInt16 nVariation=0);
//STRIP001  void EndTemplate(int nOldPendingAttributes);
//STRIP001  void HandleSmMatrix(SmMatrixNode *pMatrix,int nLevel);
//STRIP001  void HandleTable(SmNode *pNode,int nLevel);
//STRIP001  void HandleRoot(SmNode *pNode,int nLevel);
//STRIP001  void HandleSubSupScript(SmNode *pNode,int nLevel);
//STRIP001  sal_uInt8 HandleCScript(SmNode *pNode,SmNode *pContent,int nLevel,
//STRIP001      ULONG *pPos=NULL,sal_Bool bTest=TRUE);
//STRIP001  void HandleFractions(SmNode *pNode,int nLevel);
//STRIP001  void HandleBrace(SmNode *pNode,int nLevel);
//STRIP001  void HandleVerticalBrace(SmNode *pNode,int nLevel);
//STRIP001  void HandleOperator(SmNode *pNode,int nLevel);
//STRIP001  sal_Bool HandleLim(SmNode *pNode,int nLevel);
//STRIP001  void HandleMAlign(SmNode *pNode,int nLevel);
//STRIP001  void HandleMath(SmNode *pNode,int nLevel);
//STRIP001  void HandleText(SmNode *pNode,int nLevel);
//STRIP001  void HandleAttributes(SmNode *pNode,int nLevel);
//STRIP001  void TypeFaceToString(String &rRet,sal_uInt8 nFace);

    String &rRet;
    SmNode *pTree;

    sal_uInt8 nHAlign;
    sal_uInt8 nVAlign;

    int nPendingAttributes;
    ULONG nInsertion;

    sal_Int16 aSizeTable[7];
    sal_Int16 nDefaultSize;
    sal_Int16 nLSize;
    sal_Int16 nDSize;
    sal_Int16 nCurSize;
    sal_Int16 nLastSize;
    sal_uInt8 nSpec;
    sal_Bool bSilent,bReInterpBrace;
    String sPost;
    xub_StrLen nPostSup;
    xub_StrLen nPostlSup;
    sal_uInt8 nTypeFace;
    MathTypeFontSet aUserStyles;

    enum MTOKENS {END,LINE,CHAR,TMPL,PILE,MATRIX,EMBEL,RULER,FONT,SIZE};
    enum MTEMPLATES
    {
        tmANGLE,tmPAREN,tmBRACE,tmBRACK,tmBAR,tmDBAR,tmFLOOR,tmCEILING,
        tmLBLB,tmRBRB,tmRBLB,tmLBRP,tmLPRB,tmROOT,tmFRACT,tmSCRIPT,tmUBAR,
        tmOBAR,tmLARROW,tmRARROW,tmBARROW,tmSINT,tmDINT,tmTINT,tmSSINT,
        tmDSINT,tmTSINT,tmUHBRACE,tmLHBRACE,tmSUM
    };
public:
//STRIP001  static sal_Bool LookupChar(sal_Unicode nChar,String &rRet,
//STRIP001      sal_uInt8 nVersion=3,sal_uInt8 nTypeFace=0);
};


} //namespace binfilter
#endif
