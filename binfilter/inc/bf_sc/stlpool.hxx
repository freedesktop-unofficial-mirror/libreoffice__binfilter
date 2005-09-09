/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: stlpool.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:31:10 $
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

#ifndef SC_STLPOOL_HXX
#define SC_STLPOOL_HXX

#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif
namespace binfilter {


class ScStyleSheet;
class ScDocument;

class ScStyleSheetPool : public ::SfxStyleSheetPool
{
public:
                        ScStyleSheetPool( SfxItemPool&  rPool,
                                          ScDocument*   pDocument );
    virtual             ~ScStyleSheetPool();

    void                SetDocument( ScDocument* pDocument );
    ScDocument*         GetDocument() const { return pDoc; }

//STRIP001  virtual void        Erase( ::SfxStyleSheetBase* pStyle );

    void                SetActualStyleSheet ( ::SfxStyleSheetBase* pActStyleSheet )
                                { pActualStyleSheet = pActStyleSheet; }

    ::SfxStyleSheetBase*    GetActualStyleSheet ()
                                { return pActualStyleSheet; }

    void                CreateStandardStyles();
//STRIP001  void                CopyStdStylesFrom( ScStyleSheetPool* pSrcPool );
    void                UpdateStdNames();

//STRIP001  void                CopyStyleFrom( ScStyleSheetPool* pSrcPool,
//STRIP001                                      const String& rName, SfxStyleFamily eFamily );

//STRIP001  ScStyleSheet*       FindCaseIns( const String& rName, SfxStyleFamily eFam );

    void                SetForceStdName( const String* pSet );
    const String*       GetForceStdName() const { return pForceStdName; }

    virtual ::SfxStyleSheetBase& Make( const String&, SfxStyleFamily eFam,
                                     USHORT nMask = 0xffff, USHORT nPos = 0xffff );

    void                ConvertFontsAfterLoad();     // old binary file format

protected:
    virtual ::SfxStyleSheetBase* Create( const String&  rName,
                                       SfxStyleFamily   eFamily,
                                       USHORT           nMask);
    virtual ::SfxStyleSheetBase* Create( const SfxStyleSheetBase& rStyle );

private:
    ::SfxStyleSheetBase*    pActualStyleSheet;
    ScDocument*         pDoc;
    const String*       pForceStdName;
};

} //namespace binfilter
#endif     // SC_STLPOOL_HXX

