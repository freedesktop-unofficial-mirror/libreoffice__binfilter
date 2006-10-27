/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fntcache.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 22:45:04 $
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
#ifndef _FNTCACHE_HXX
#define _FNTCACHE_HXX


#ifndef _SV_FONT_HXX //autogen
#include <vcl/font.hxx>
#endif
#ifndef _SVMEMPOOL_HXX //autogen
#include <tools/mempool.hxx>
#endif

#include "swtypes.hxx"
#include "swcache.hxx"
/*N*/ #include <tools/debug.hxx>  //for stripping
class Printer;
class OutputDevice;
class FontMetric;
namespace binfilter {

class SwFntObj;
class SwDrawTextInfo;   // DrawText
class SwScriptInfo;
class ViewShell;
class SwSubFont;

/*************************************************************************
 *                      class SwFntCache
 *************************************************************************/

class SwFntCache : public SwCache
{
public:

    inline SwFntCache() : SwCache(50,50
#ifndef PRODUCT
    , ByteString( RTL_CONSTASCII_STRINGPARAM(
                        "Globaler Font-Cache pFntCache" ))
#endif
    ) {}

    inline SwFntObj *First( ) { return (SwFntObj *)SwCache::First(); }
    inline SwFntObj *Next( SwFntObj *pFntObj)
        { return (SwFntObj *)SwCache::Next( (SwCacheObj *)pFntObj ); }
    void Flush();
};

// Font-Cache, globale Variable, in txtinit.Cxx angelegt/zerstoert
extern SwFntCache *pFntCache;
extern SwFntObj *pLastFont;
extern BYTE *pMagicNo;
extern Color *pWaveCol;

/*************************************************************************
 *                      class SwFntObj
 *************************************************************************/

class SwFntObj : public SwCacheObj
{
    friend class SwFntAccess;
    friend void _InitCore();
    friend void _FinitCore();

    Font aFont;
    Font *pScrFont;
    Font *pPrtFont;
    OutputDevice* pPrinter;
    USHORT nLeading;
    USHORT nScrAscent;
    USHORT nPrtAscent;
    USHORT nScrHeight;
    USHORT nPrtHeight;
    USHORT nPropWidth;
    USHORT nZoom;
    BOOL bSymbol : 1;
    BOOL bPaintBlank : 1;
    void ChooseFont( ViewShell *pSh, OutputDevice *pOut );

    static long nPixWidth;
    static MapMode *pPixMap;
    static OutputDevice *pPixOut;

public:
    DECL_FIXEDMEMPOOL_NEWDEL(SwFntObj)

    SwFntObj( const SwSubFont &rFont, const void* pOwner,
              ViewShell *pSh );

    virtual ~SwFntObj();

    inline       Font *GetScrFont()     { return pScrFont; }
    inline       Font *GetFont()        { return &aFont; }
    inline const Font *GetFont() const  { return &aFont; }

    inline USHORT GetLeading() const  { return nLeading; }

    void GuessLeading( const ViewShell *pSh, const FontMetric& rMet );
    USHORT GetAscent( const ViewShell *pSh, const OutputDevice *pOut );
    USHORT GetHeight( const ViewShell *pSh, const OutputDevice *pOut );

    void SetDevFont( const ViewShell *pSh, OutputDevice *pOut );
    inline OutputDevice* GetPrt() const { return pPrinter; }
    inline USHORT   GetZoom() const { return nZoom; }
    inline USHORT   GetPropWidth() const { return nPropWidth; }
    inline BOOL     IsSymbol() const { return bSymbol; }

    Size  GetTextSize( SwDrawTextInfo &rInf );

    void CreateScrFont( const ViewShell *pSh, const OutputDevice& rOut );
    void CreatePrtFont( const OutputDevice& rOut );
};

/*************************************************************************
 *                      class SwFntAccess
 *************************************************************************/


class SwFntAccess : public SwCacheAccess
{
    ViewShell *pShell;
protected:
    virtual SwCacheObj *NewObj( );

public:
    SwFntAccess( const void * &rMagic, USHORT &rIndex, const void *pOwner,
                 ViewShell *pShell,
                 BOOL bCheck = FALSE  );
    inline SwFntObj* Get() { return (SwFntObj*) SwCacheAccess::Get(); };
};


} //namespace binfilter
#endif
