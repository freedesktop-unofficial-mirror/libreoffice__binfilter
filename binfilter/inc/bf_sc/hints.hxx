/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: hints.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:18:04 $
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

#ifndef SC_HINTS_HXX
#define SC_HINTS_HXX

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif

#ifndef _SFXHINT_HXX //autogen
#include <bf_svtools/hint.hxx>
#endif
#include <tools/debug.hxx>
namespace binfilter {

// ---------------------------------------------------------------------------

class ScPaintHint : public SfxHint
{
    ScRange     aRange;
    USHORT      nParts;
    BOOL        bPrint;     //  Flag, ob auch Druck/Vorschau betroffen ist

public:
                    TYPEINFO();
                    ScPaintHint();
                    ScPaintHint( const ScRange& rRng, USHORT nPaint = PAINT_ALL );
                    ~ScPaintHint();

    void            SetPrintFlag(BOOL bSet) { bPrint = bSet; }

    const ScRange&  GetRange() const        { return aRange; }
    USHORT          GetStartCol() const     { return aRange.aStart.Col(); }
    USHORT          GetStartRow() const     { return aRange.aStart.Row(); }
    USHORT          GetStartTab() const     { return aRange.aStart.Tab(); }
    USHORT          GetEndCol() const       { return aRange.aEnd.Col(); }
    USHORT          GetEndRow() const       { return aRange.aEnd.Row(); }
    USHORT          GetEndTab() const       { return aRange.aEnd.Tab(); }
    USHORT          GetParts() const        { return nParts; }
    BOOL            GetPrintFlag() const    { return bPrint; }
};


class ScUpdateRefHint : public SfxHint
{
    UpdateRefMode   eUpdateRefMode;
    ScRange         aRange;
    short           nDx;
    short           nDy;
    short           nDz;

public:
                    TYPEINFO();

                    ScUpdateRefHint( UpdateRefMode eMode, const ScRange& rR,
                                        short nX, short nY, short nZ );
                    ~ScUpdateRefHint();

    UpdateRefMode   GetMode() const         { return eUpdateRefMode; }
    const ScRange&  GetRange() const        { return aRange; }
    short           GetDx() const           { return nDx; }
    short           GetDy() const           { return nDy; }
    short           GetDz() const           { return nDz; }
};


#define SC_POINTERCHANGED_NUMFMT    1

class ScPointerChangedHint : public SfxHint
{
    USHORT          nFlags;

public:
                    TYPEINFO();

                    ScPointerChangedHint( USHORT nF );
                    ~ScPointerChangedHint();

    USHORT          GetFlags() const            { return nFlags; }
};


//! move ScLinkRefreshedHint to a different file?

#define SC_LINKREFTYPE_NONE     0
#define SC_LINKREFTYPE_SHEET    1
#define SC_LINKREFTYPE_AREA     2
#define SC_LINKREFTYPE_DDE      3

class ScLinkRefreshedHint : public SfxHint
{
    USHORT      nLinkType;  // SC_LINKREFTYPE_...
    String      aUrl;       // used for sheet links
    String      aDdeAppl;   // used for dde links:
    String      aDdeTopic;
    String      aDdeItem;
    BYTE        nDdeMode;
    ScAddress   aDestPos;   // used to identify area links
                            //! also use source data for area links?

public:
                    TYPEINFO();
                    ScLinkRefreshedHint();
                    ~ScLinkRefreshedHint();

    void            SetSheetLink( const String& rSourceUrl );
    void            SetAreaLink( const ScAddress& rPos );

    USHORT              GetLinkType() const { return nLinkType; }
    const String&       GetUrl() const      { return aUrl; }
    const String&       GetDdeAppl() const  { return aDdeAppl; }
    const String&       GetDdeTopic() const { return aDdeTopic; }
    const String&       GetDdeItem() const  { return aDdeItem; }
    BYTE                GetDdeMode() const  { return nDdeMode; }
    const ScAddress&    GetDestPos() const  { return aDestPos; }
};


//! move ScAutoStyleHint to a different file?

class ScAutoStyleHint : public SfxHint
{
public:
                    TYPEINFO();
                    ScAutoStyleHint( const ScRange& rR, const String& rSt1,
                                        ULONG nT, const String& rSt2 ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ULONG nT, const String& rSt2 );

};


} //namespace binfilter
#endif
