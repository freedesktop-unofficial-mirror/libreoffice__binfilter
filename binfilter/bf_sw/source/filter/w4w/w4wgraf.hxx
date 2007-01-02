/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: w4wgraf.hxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:08:31 $
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

#ifndef _GEN_HXX //autogen
#include <tools/gen.hxx>
#endif
class Graphic;
class SvStream;
class Bitmap;
class OutputDevice;
namespace binfilter {


class RGBQuad;
class BmpFileHd;
class BmpInfoHd;
struct WmfFileHd;
class BmpFileHd;


class SwW4WGraf
{
    Point      aVectPos;          // W4W-Vector: aktuelle Position MoveTo/LineTo
    SvStream&  rInp;            // aus diesem Stream lesen
    Graphic*   pGraph;
    Bitmap*    pBmp;
    RGBQuad*   pPal;
    BmpFileHd* pBmpHead;
    BmpInfoHd* pBmpInfo;
    USHORT     nPalColors;
    USHORT     nVectMinX;
    USHORT     nVectMaxX;
    USHORT     nVectMinY;
    USHORT     nVectMaxY;
//  Size       aVectSiz;          // Maximale Ausdehnung der W4W-Vectorgrafik (wird von ReadHexPoint() gesezt)

    short      nStat;             // 1 = File-Grafik, 2 = Mem-Grafik
    BYTE       nError;

    void   ReadHexPoint(Point& aPnt);
    int    GetNextRecord();
    int    GetNextVectRec(OutputDevice& rOut);
    short  GetHexByte();
    USHORT GetHexUShort();
    ULONG  GetHexULong();
    long   GetVarSize();
    short  ReadPalette( long nVarSize );
    short  DefaultPalette( USHORT nColors );
    short  ReadBitmap( long nVarSize );
    void   SkipBytes( register long nBytes );

    ULONG ReadWmfHeader( WmfFileHd& rHd );
    short ReadW4WGrafBMap( long nTyp, long nWidth, long nHeight );
    short ReadW4WGrafVect( long nTyp, long nWidth, long nHeight );
    short ReadGrafFile( long nTyp, long nWidth, long nHeight );

    BOOL  CheckW4WVector();       // enth„lt die W4W-Grafik Vektordaten ? (Joe)

    sal_Char ReadChar()     { sal_Char c = 0; rInp.Read( &c, 1 ); return c; }

public:
    SwW4WGraf( SvStream& rIstream );
    ~SwW4WGraf();
    short Read( long nGrafPDSType, long nGrWidthTw, long nGrHeightTw );
    Graphic* GetGraphic() const { return pGraph; };
};

} //namespace binfilter
