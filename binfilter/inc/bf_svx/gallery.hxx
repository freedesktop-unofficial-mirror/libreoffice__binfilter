/*************************************************************************
 *
 *  $RCSfile: gallery.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 21:15:41 $
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

#ifndef _GALLERY_HXX_
#define _GALLERY_HXX_

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
// auto strip #ifndef _STRING_HXX
// auto strip #include <tools/string.hxx>
// auto strip #endif
// auto strip #ifndef _URLOBJ_HXX
// auto strip #include <tools/urlobj.hxx>
// auto strip #endif
class List;
class Graphic;
class Bitmap;
namespace binfilter {

// -----------
// - Defines -
// -----------

#define SGA_FORMAT_NONE     0x00000000L
#define SGA_FORMAT_STRING   0x00000001L
#define SGA_FORMAT_GRAPHIC  0x00000010L
#define SGA_FORMAT_SOUND    0x00000100L
#define SGA_FORMAT_OLE          0x00001000L
#define SGA_FORMAT_SVDRAW   0x00010000L
#define SGA_FORMAT_ALL      0xFFFFFFFFL

#define SVX_GALLERY() (GalleryExplorer::GetGallery())

// Defines for preinstalled themes
#define GALLERY_THEME_3D                1
#define GALLERY_THEME_ANIMATIONS    2
#define GALLERY_THEME_BULLETS       3
#define GALLERY_THEME_OFFICE            4
#define GALLERY_THEME_FLAGS             5
#define GALLERY_THEME_FLOWCHARTS    6
#define GALLERY_THEME_EMOTICONS         7
#define GALLERY_THEME_PHOTOS        8
#define GALLERY_THEME_BACKGROUNDS   9
#define GALLERY_THEME_HOMEPAGE      10
#define GALLERY_THEME_INTERACTION   11
#define GALLERY_THEME_MAPS              12
#define GALLERY_THEME_PEOPLE            13
#define GALLERY_THEME_SURFACES      14
#define GALLERY_THEME_HTMLBUTTONS   15
#define GALLERY_THEME_POWERPOINT    16
#define GALLERY_THEME_RULERS        17
#define GALLERY_THEME_SOUNDS        18
#define GALLERY_THEME_SYMBOLS       19
#define GALLERY_THEME_MYTHEME       20
#define GALLERY_THEME_USERSOUNDS    21
#define GALLERY_THEME_ARROWS            22
#define GALLERY_THEME_BALLOONS          23
#define GALLERY_THEME_KEYBOARD          24
#define GALLERY_THEME_TIME              25
#define GALLERY_THEME_PRESENTATION      26
#define GALLERY_THEME_CALENDAR          27
#define GALLERY_THEME_NAVIGATION        28
#define GALLERY_THEME_COMMUNICATION     29
#define GALLERY_THEME_FINANCES          30
#define GALLERY_THEME_COMPUTER          31
#define GALLERY_THEME_CLIMA             32
#define GALLERY_THEME_EDUCATION         33
#define GALLERY_THEME_TROUBLE           34
#define GALLERY_THEME_SCREENBEANS       35

#define GALLERY_THEME_DUMMY5            36

// -------------------
// - GalleryExplorer -
// -------------------

class Gallery;
class VCDrawModel;
class FmFormModel;
class FmFormModel;

//STRIP001 class GalleryExplorer
//STRIP001 {
//STRIP001 private:
//STRIP001
//STRIP001  static Gallery*             ImplGetGallery();
//STRIP001
//STRIP001 public:
//STRIP001
//STRIP001  static GalleryExplorer*     GetGallery();
//STRIP001
//STRIP001 public:
//STRIP001
//STRIP001  INetURLObject               GetURL() const;
//STRIP001  String                      GetFilterName() const;
//STRIP001  Graphic                     GetGraphic() const;
//STRIP001  BOOL                        GetVCDrawModel( FmFormModel& rModel ) const;
//STRIP001  BOOL                        IsLinkage() const;
//STRIP001
//STRIP001  static BOOL                 FillThemeList( List& rThemeList );
//STRIP001
//STRIP001  static BOOL                 FillObjList( const String& rThemeName, List& rObjList );
//STRIP001  static BOOL                 FillObjList( ULONG nThemeId, List& rObjList );
//STRIP001
//STRIP001  static BOOL                 InsertURL( const String& rThemeName, const String& rURL );
//STRIP001  static BOOL                 InsertURL( ULONG nThemeId, const String& rURL );
//STRIP001
//STRIP001  static BOOL                 InsertURL( const String& rThemeName, const String& rURL,
//STRIP001                                         const ULONG nSgaFormat /* = SGA_FORMAT_ALL */ );
//STRIP001  static BOOL                 InsertURL( ULONG nThemeId, const String& rURL,
//STRIP001                                         const ULONG nSgaFormat /* = SGA_FORMAT_ALL */ );
//STRIP001
//STRIP001  static ULONG                GetObjCount( const String& rThemeName );
//STRIP001  static ULONG                GetObjCount( ULONG nThemeId );
//STRIP001
//STRIP001  static BOOL                 GetGraphicObj( const String& rThemeName, ULONG nPos,
//STRIP001                                             Graphic* pGraphic = NULL, Bitmap* pThumb = NULL,
//STRIP001                                             BOOL bProgess = FALSE );
//STRIP001  static BOOL                 GetGraphicObj( ULONG nThemeId, ULONG nPos,
//STRIP001                                             Graphic* pGraphic = NULL, Bitmap* pThumb = NULL,
//STRIP001                                             BOOL bProgess = FALSE );
//STRIP001
//STRIP001  static BOOL                 InsertGraphicObj( const String& rThemeName, const Graphic& rGraphic );
//STRIP001  static BOOL                 InsertGraphicObj( ULONG nThemeId, const Graphic& rGraphic );
//STRIP001
//STRIP001  static ULONG                GetSdrObjCount( const String& rThemeName );
//STRIP001  static ULONG                GetSdrObjCount( ULONG nThemeId );
//STRIP001
//STRIP001  static BOOL                 GetSdrObj( const String& rThemeName, ULONG nSdrModelPos,
//STRIP001                                         FmFormModel* pModel = NULL, Bitmap* pThumb = NULL );
//STRIP001  static BOOL                 GetSdrObj( ULONG nThemeId, ULONG nSdrModelPos,
//STRIP001                                         FmFormModel* pModel = NULL, Bitmap* pThumb = NULL );
//STRIP001
//STRIP001  static BOOL                 InsertSdrObj( const String& rThemeName, FmFormModel& rModel );
//STRIP001  static BOOL                 InsertSdrObj( ULONG nThemeId, FmFormModel& rModel );
//STRIP001
//STRIP001  static BOOL                 BeginLocking( const String& rThemeName );
//STRIP001  static BOOL                 BeginLocking( ULONG nThemeId );
//STRIP001
//STRIP001  static BOOL                 EndLocking( const String& rThemeName );
//STRIP001  static BOOL                 EndLocking( ULONG nThemeId );
//STRIP001 };

}//end of namespace binfilter
#endif // _GALLERY_HXX_
