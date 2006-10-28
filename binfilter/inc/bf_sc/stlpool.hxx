/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: stlpool.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:42:57 $
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


    void                SetActualStyleSheet ( ::SfxStyleSheetBase* pActStyleSheet )
                                { pActualStyleSheet = pActStyleSheet; }

    ::SfxStyleSheetBase*    GetActualStyleSheet ()
                                { return pActualStyleSheet; }

    void                CreateStandardStyles();
    void                UpdateStdNames();



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

