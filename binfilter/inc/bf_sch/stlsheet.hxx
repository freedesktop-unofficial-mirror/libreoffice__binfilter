/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: stlsheet.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:53:37 $
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

#ifndef _SCH_STLSHEET_HXX
#define _SCH_STLSHEET_HXX

// auto strip #ifndef _SFXITEMSET_HXX //autogen
// auto strip #include <svtools/itemset.hxx>
// auto strip #endif
#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif
// auto strip #ifndef _STREAM_HXX //autogen
// auto strip #include <tools/stream.hxx>
// auto strip #endif
namespace binfilter {




class SchStyleSheet : public SfxStyleSheet
{
protected:
    virtual void Load (SvStream& rIn, USHORT nVersion);
    virtual void Store(SvStream& rOut);

public:
    TYPEINFO();
    SchStyleSheet(const String& rName, SfxStyleSheetBasePool& rPool,
                  SfxStyleFamily eFamily, USHORT nMask);
    virtual ~SchStyleSheet();

    virtual BOOL SetParent (const String& rParentName);
    virtual SfxItemSet& GetItemSet();
//STRIP001  virtual BOOL IsUsed() const;
//STRIP001  virtual BOOL HasFollowSupport() const;
//STRIP001  virtual BOOL HasParentSupport() const;
};

} //namespace binfilter
#endif     // _SCH_STLSHEET_HXX

