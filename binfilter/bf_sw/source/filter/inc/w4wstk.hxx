/*************************************************************************
 *
 *  $RCSfile: w4wstk.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:52:48 $
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
#ifndef _W4WSTK_HXX
#define _W4WSTK_HXX

#ifndef _SVARRAY_HXX //autogen
#include <svtools/svarray.hxx>
#endif

#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif

#ifndef _NDINDEX_HXX
#include <ndindex.hxx>
#endif
namespace binfilter {

class SwW4WParser;
class SwDoc;
struct SwPosition;
class SwPaM;
class SwFlyFrmFmt;

/* ------ Stack-Eintrag fuer die Attribute -----------
 * Es werden immer Pointer auf neue Attribute uebergeben.
 */

struct W4WStkEntry
{
    SfxPoolItem * pAttr;    // Format Attribute
    SwNodeIndex nMkNode;
    SwNodeIndex nPtNode;
    xub_StrLen nMkCntnt;        // Nachbildung von Mark()
    xub_StrLen nPtCntnt;        // Nachbildung von GetPoint()
    BOOL bLocked : 1;
    BOOL bCopied : 1;
    BOOL bClosed : 1;       // Zeigt ueber Child geschlossenes Attr. an.
    BOOL bNeverIntoDoc : 1; // Dieser Entry soll nichts ins Doc sondern,
                            // nach dem Schliessen geloescht werden.

    W4WStkEntry( const SwPosition & rStartPos,
                    SfxPoolItem* pHt,
                    BOOL bInitCopied = FALSE,
                    BOOL bInitNID    = FALSE );

    ~W4WStkEntry();

    void SetStartPos( const SwPosition & rStartPos );
    void SetEndPos( const SwPosition & rEndPos );
    BOOL MakeRegion( SwPaM & rRegion ) const;

private:
    W4WStkEntry( const W4WStkEntry& rEntry ); // niemals aufrufen, nur Complier-Test
};

// ein Stack fuer die gesamten Text-Attribute
typedef W4WStkEntry* W4WStkEntryPtr;
SV_DECL_PTRARR(W4WCtrlStkEntries,W4WStkEntryPtr,5,10)

class W4WCtrlStack : public W4WCtrlStkEntries
{
    SwW4WParser*  pParser;
    W4WCtrlStack* pParentStack;

public:
    W4WCtrlStack( SwW4WParser& rParser );
    W4WCtrlStack( W4WCtrlStack& rCpy, const SwPosition& rPos );
    ~W4WCtrlStack();

    void NewAttr( const SwPosition& rPos, const SfxPoolItem & rAttr );

    BOOL SetAttr( const SwPosition& rPos, USHORT nAttrId=0,
                    BOOL bTstEnde       = TRUE,
                    BOOL bDoNotSetInDoc = FALSE );
    void SetAttrInDoc( SwPaM& rRegion, const W4WStkEntry& rEntry );
    void SetLockedAttrClosed( USHORT nAttrId );
    void SetEndForClosedEntries( const SwPosition& rPos );
    void StealAttr( const SwPosition& rPos, USHORT nAttrId = 0 );
    void StealWWTabAttr( const SwPosition& rPos );

    SfxPoolItem* GetFmtStkAttr( USHORT nWhich, USHORT * pPos = 0 );
    const SfxPoolItem* GetFmtAttr( const SwPaM& rPaM, USHORT nWhich );
    BOOL IsAttrOpen( USHORT nAttrId );
};


// weitere Teile aus ehemaligem swrtf.hxx
class SwW4WStyle : public SfxPoolItem
{
public:
    USHORT nStyleId;
    SwW4WStyle( USHORT nId );
    SwW4WStyle( const SwW4WStyle & rRTFFld );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* = 0 ) const;

    USHORT GetStyleId() const { return nStyleId; }
};

class SwW4WAnchor : public SfxPoolItem
{
    SwFlyFrmFmt* pFlyFmt;
public:
    SwW4WAnchor( SwFlyFrmFmt* pFlyFmt );
    SwW4WAnchor( const SwW4WAnchor& );

    // "pure virtual Methoden" vom SfxPoolItem
    virtual int             operator==( const SfxPoolItem& ) const;
    virtual SfxPoolItem*    Clone( SfxItemPool* = 0 ) const;

    const SwFlyFrmFmt* GetFlyFmt() const { return pFlyFmt; }
          SwFlyFrmFmt* GetFlyFmt()    { return pFlyFmt; }
};

} //namespace binfilter
#endif
