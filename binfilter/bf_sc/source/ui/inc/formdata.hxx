/*************************************************************************
 *
 *  $RCSfile: formdata.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:39:43 $
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

#ifndef SC_FORMDATA_HXX
#define SC_FORMDATA_HXX

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif

#ifndef _SV_GEN_HXX //autogen
#include <tools/gen.hxx>
#endif
namespace binfilter {

//STRIP001 class ScInputHandler;
//STRIP001 class ScDocShell;

//============================================================================

class ScFormEditData
{
public:
                        ScFormEditData(){DBG_BF_ASSERT(0, "STRIP");} //STRIP001                         ScFormEditData();
                        ~ScFormEditData(){DBG_BF_ASSERT(0, "STRIP");} //STRIP001                        ~ScFormEditData();
//STRIP001
//STRIP001  void                SaveValues();
//STRIP001  void                RestoreValues();
//STRIP001  BOOL                HasParent() const   { return pParent != NULL; }
//STRIP001
//STRIP001  USHORT              GetMode() const     { return nMode; }
//STRIP001  xub_StrLen          GetFStart() const   { return nFStart; }
//STRIP001  USHORT              GetCatSel() const   { return nCatSel; }
//STRIP001  USHORT              GetFuncSel() const  { return nFuncSel; }
//STRIP001  USHORT              GetOffset() const   { return nOffset; }
//STRIP001  USHORT              GetEdFocus() const  { return nEdFocus; }
//STRIP001  const String&       GetUndoStr() const  { return aUndoStr; }
//STRIP001  BOOL                GetMatrixFlag()const{ return bMatrix;}
//STRIP001  ULONG               GetUniqueId()const  { return nUniqueId;}
//STRIP001  const Selection&    GetSelection()const { return aSelection;}
//STRIP001  ScInputHandler*     GetInputHandler()   { return pInputHandler;}
//STRIP001  ScDocShell*         GetDocShell()       { return pScDocShell;}
//STRIP001
//STRIP001  void                SetMode( USHORT nNew )                  { nMode = nNew; }
//STRIP001  void                SetFStart( xub_StrLen nNew )            { nFStart = nNew; }
//STRIP001  void                SetCatSel( USHORT nNew )                { nCatSel = nNew; }
//STRIP001  void                SetFuncSel( USHORT nNew )               { nFuncSel = nNew; }
//STRIP001  void                SetOffset( USHORT nNew )                { nOffset = nNew; }
//STRIP001  void                SetEdFocus( USHORT nNew )               { nEdFocus = nNew; }
//STRIP001  void                SetUndoStr( const String& rNew )        { aUndoStr = rNew; }
//STRIP001  void                SetMatrixFlag(BOOL bNew)                { bMatrix=bNew;}
//STRIP001  void                SetUniqueId(ULONG nNew)                 { nUniqueId=nNew;}
//STRIP001  void                SetSelection(const Selection& aSel)     { aSelection=aSel;}
//STRIP001  void                SetInputHandler(ScInputHandler* pHdl)   { pInputHandler=pHdl;}
//STRIP001  void                SetDocShell(ScDocShell* pSds)           { pScDocShell=pSds;}
//STRIP001
//STRIP001
//STRIP001
//STRIP001 private:
//STRIP001                      ScFormEditData( const ScFormEditData& );
//STRIP001  const ScFormEditData& operator=( const ScFormEditData& r );
//STRIP001  void                Reset();
//STRIP001
//STRIP001  ScFormEditData*     pParent;            // fuer Verschachtelung
//STRIP001  USHORT              nMode;              // enum ScFormulaDlgMode
//STRIP001  xub_StrLen          nFStart;
//STRIP001  USHORT              nCatSel;
//STRIP001  USHORT              nFuncSel;
//STRIP001  USHORT              nOffset;
//STRIP001  USHORT              nEdFocus;
//STRIP001  String              aUndoStr;
//STRIP001  BOOL                bMatrix;
//STRIP001  ULONG               nUniqueId;
//STRIP001  Selection           aSelection;
//STRIP001  ScInputHandler*     pInputHandler;
//STRIP001  ScDocShell*         pScDocShell;
};



} //namespace binfilter
#endif // SC_CRNRDLG_HXX

