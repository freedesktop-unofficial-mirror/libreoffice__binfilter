/*************************************************************************
 *
 *  $RCSfile: unoforou.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:29:22 $
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

#ifndef _SVX_UNOFOROU_HXX
#define _SVX_UNOFOROU_HXX

#ifndef _SVX_UNOEDSRC_HXX
#include <bf_svx/unoedsrc.hxx>
#endif

#include <bf_svx/editdata.hxx>
namespace binfilter {

class Outliner;
class SdrObject;

//  SvxOutlinerForwarder - SvxTextForwarder fuer Outliner

class SvxOutlinerForwarder : public SvxTextForwarder
{
private:
    Outliner&           rOutliner;
    SdrObject*          pSdrObject;

    /** this pointer may be null or point to an item set for the attribs of
        the selection maAttribsSelection */
    mutable SfxItemSet* mpAttribsCache;

    /** if we have a chached attribute item set, this is the selection of it */
    mutable ESelection  maAttribCacheSelection;

    /** this pointer may be null or point to an item set for the paragraph
        mnParaAttribsCache */
    mutable SfxItemSet* mpParaAttribsCache;

    /** if we have a cached para attribute item set, this is the paragraph of it */
    mutable USHORT      mnParaAttribsCache;

public:
                        SvxOutlinerForwarder( Outliner& rOutl, SdrObject* pSdrObj );
    virtual             ~SvxOutlinerForwarder();

    virtual USHORT      GetParagraphCount() const;
    virtual USHORT      GetTextLen( USHORT nParagraph ) const;
    virtual String      GetText( const ESelection& rSel ) const;
    virtual SfxItemSet  GetAttribs( const ESelection& rSel, BOOL bOnlyHardAttrib = 0 ) const;
    virtual SfxItemSet  GetParaAttribs( USHORT nPara ) const;
    virtual void        SetParaAttribs( USHORT nPara, const SfxItemSet& rSet );
    virtual void        GetPortions( USHORT nPara, SvUShorts& rList ) const;

    virtual USHORT      GetItemState( const ESelection& rSel, USHORT nWhich ) const;
    virtual USHORT      GetItemState( USHORT nPara, USHORT nWhich ) const;

    virtual void        QuickInsertText( const String& rText, const ESelection& rSel );
    virtual void        QuickInsertField( const SvxFieldItem& rFld, const ESelection& rSel );
    virtual void        QuickSetAttribs( const SfxItemSet& rSet, const ESelection& rSel );
    virtual void        QuickInsertLineBreak( const ESelection& rSel );

    virtual SfxItemPool* GetPool() const;

    virtual XubString    CalcFieldValue( const SvxFieldItem& rField, USHORT nPara, USHORT nPos, Color*& rpTxtColor, Color*& rpFldColor );
    virtual BOOL        IsValid() const;

    Outliner&           GetOutliner() const { return rOutliner; }

    virtual LanguageType    GetLanguage( USHORT, USHORT ) const;
    virtual USHORT          GetFieldCount( USHORT nPara ) const;
    virtual EFieldInfo      GetFieldInfo( USHORT nPara, USHORT nField ) const;
    virtual EBulletInfo     GetBulletInfo( USHORT nPara ) const;
    virtual Rectangle       GetCharBounds( USHORT nPara, USHORT nIndex ) const;
    virtual Rectangle       GetParaBounds( USHORT nPara ) const;
    virtual MapMode         GetMapMode() const;
    virtual OutputDevice*   GetRefDevice() const;
    virtual sal_Bool        GetIndexAtPoint( const Point&, USHORT& nPara, USHORT& nIndex ) const;
    virtual sal_Bool        GetWordIndices( USHORT nPara, USHORT nIndex, USHORT& nStart, USHORT& nEnd ) const;
    virtual sal_Bool        GetAttributeRun( USHORT& nStartIndex, USHORT& nEndIndex, USHORT nPara, USHORT nIndex ) const;
    virtual USHORT          GetLineCount( USHORT nPara ) const;
    virtual USHORT          GetLineLen( USHORT nPara, USHORT nLine ) const;
    virtual sal_Bool        Delete( const ESelection& );
    virtual sal_Bool        InsertText( const String&, const ESelection& );
    virtual sal_Bool        QuickFormatDoc( BOOL bFull=FALSE );
    virtual USHORT          GetDepth( USHORT nPara ) const;
    virtual sal_Bool        SetDepth( USHORT nPara, USHORT nNewDepth );

    /* this method flushes internal caches for this forwarder */
    void                flushCache();
};

}//end of namespace binfilter
#endif

