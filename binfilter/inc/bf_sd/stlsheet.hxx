/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: stlsheet.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 12:07:05 $
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

#ifndef _SD_STLSHEET_HXX
#define _SD_STLSHEET_HXX


#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif
namespace binfilter {
class SdStyleSheet : public SfxStyleSheet
{
protected:
    virtual void Load (SvStream& rIn, USHORT nVersion);
    virtual void Store(SvStream& rOut);

    virtual void SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType,
                            const SfxHint& rHint, const TypeId& rHintType);

public:
                        TYPEINFO();
                        SdStyleSheet(const String& rName,
                                     SfxStyleSheetBasePool& rPool,
                                     SfxStyleFamily eFamily,
                                     USHORT nMask);
    virtual             ~SdStyleSheet();

    virtual BOOL        SetParent (const String& rParentName);
    virtual SfxItemSet& GetItemSet();
    virtual BOOL        IsUsed() const;
//STRIP001  virtual BOOL        HasFollowSupport() const;
//STRIP001  virtual BOOL        HasParentSupport() const;
//STRIP001  virtual BOOL        HasClearParentSupport() const;

//STRIP001          List*       CreateChildList() const;

//STRIP001          void        AdjustToFontHeight(SfxItemSet& rSet,
//STRIP001                                         BOOL bOnlyMissingItems = TRUE);

    SdStyleSheet* GetRealStyleSheet() const;
//STRIP001  SdStyleSheet* GetPseudoStyleSheet() const;
};

} //namespace binfilter
#endif     // _SD_STLSHEET_HXX



