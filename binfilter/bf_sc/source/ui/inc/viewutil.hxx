/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: viewutil.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 20:29:34 $
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

#ifndef SC_VIEWUTIL_HXX
#define SC_VIEWUTIL_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
class String;
class SfxItemSet;
namespace binfilter {

class SvxFontItem;

class ScChangeAction;
class ScChangeViewSettings;
class ScDocument;
class ScAddress;


enum ScUpdateMode { SC_UPDATE_ALL, SC_UPDATE_CHANGED, SC_UPDATE_MARKS };


// ---------------------------------------------------------------------------

class ScViewUtil                                // static Methoden
{
public:
//STRIP001  static BOOL ExecuteCharMap( const SvxFontItem&  rOldFont,
//STRIP001                              SvxFontItem&        rNewFont,
//STRIP001                              String&             rString );

//STRIP001  static BOOL IsActionShown( const ScChangeAction& rAction,
//STRIP001                              const ScChangeViewSettings& rSettings,
//STRIP001                              ScDocument& rDocument );

    static void PutItemScript( SfxItemSet& rShellSet, const SfxItemSet& rCoreSet,
                                USHORT nWhichId, USHORT nScript );

//STRIP001  static USHORT GetEffLanguage( ScDocument* pDoc, const ScAddress& rPos );

//STRIP001  static sal_Int32 GetTransliterationType( USHORT nSlotID );
};

// ---------------------------------------------------------------------------

//STRIP001 class ScUpdateRect
//STRIP001 {
//STRIP001 private:
//STRIP001  USHORT  nOldStartX;
//STRIP001  USHORT  nOldStartY;
//STRIP001  USHORT  nOldEndX;
//STRIP001  USHORT  nOldEndY;
//STRIP001  USHORT  nNewStartX;
//STRIP001  USHORT  nNewStartY;
//STRIP001  USHORT  nNewEndX;
//STRIP001  USHORT  nNewEndY;
//STRIP001  USHORT  nContX1;
//STRIP001  USHORT  nContY1;
//STRIP001  USHORT  nContX2;
//STRIP001  USHORT  nContY2;
//STRIP001 public:
//STRIP001          ScUpdateRect( USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2 );
//STRIP001  void    SetNew( USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2 );
//STRIP001  BOOL    GetDiff( USHORT& rX1, USHORT& rY1, USHORT& rX2, USHORT& rY2 );
//STRIP001  BOOL    GetXorDiff( USHORT& rX1, USHORT& rY1, USHORT& rX2, USHORT& rY2, BOOL& rCont );
//STRIP001  void    GetContDiff( USHORT& rX1, USHORT& rY1, USHORT& rX2, USHORT& rY2 );
//STRIP001 };




} //namespace binfilter
#endif

