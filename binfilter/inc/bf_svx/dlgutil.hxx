/*************************************************************************
 *
 *  $RCSfile: dlgutil.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:34 $
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
 *  WITHOUT WARRUNTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRUNTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc..
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef _SVX_DLGUTIL_HXX
#define _SVX_DLGUTIL_HXX

// include ---------------------------------------------------------------
#ifndef _FIELD_HXX
#include <vcl/field.hxx>
#endif
#ifndef _SFXPOOLITEM_HXX
#include <svtools/poolitem.hxx>
#endif
#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif

// macro -----------------------------------------------------------------

#if SUPD<609
//STRIP001 #define GET_MODULE_FIELDUNIT( eFieldUnit )                                   \
//STRIP001 {                                                                            \
//STRIP001  SfxApplication* pSfxApp = SFX_APP();                                    \
//STRIP001  eFieldUnit = pSfxApp->GetOptions().GetMetric();                         \
//STRIP001  SfxModule* pModule = pSfxApp->GetActiveModule();                        \
//STRIP001                                                                          \
//STRIP001  if ( pModule )                                                          \
//STRIP001  {                                                                       \
//STRIP001      const SfxPoolItem* pItem = pModule->GetItem( SID_ATTR_METRIC );     \
//STRIP001                                                                          \
//STRIP001      if ( pItem )                                                        \
//STRIP001          eFieldUnit = (FieldUnit)( (SfxUInt16Item*)pItem )->GetValue();  \
//STRIP001  }                                                                       \
//STRIP001 }
#endif

// typedef ---------------------------------------------------------------

//STRIP001 typedef long (*FUNC_CONVERT)(long);

// Functions -------------------------------------------------------------

// HM- und LanguageStrings aus der Resource laden
//STRIP001 String   GetLanguageString( LanguageType eType );
//STRIP001 String   GetDicInfoStr( const String& rName, const USHORT nLang,
//STRIP001                     const BOOL bNeg );

// FieldUnit im MetricField oder -Box umsetzen
//STRIP001 void SetFieldUnit( MetricField& rCtrl,
//STRIP001                 FieldUnit eUnit, BOOL bAll = FALSE );
//STRIP001 void SetFieldUnit( MetricBox& rCtrl,
//STRIP001                 FieldUnit eUnit, BOOL bAll = FALSE );

FieldUnit GetModuleFieldUnit( const SfxItemSet* pSet = NULL );

// Metriken umrechnen
long        CalcToUnit( float nIn, SfxMapUnit eUnit );
long        CalcToPoint( long nIn, SfxMapUnit eUnit, USHORT nFaktor );

long        ItemToControl( long nIn, SfxMapUnit eItem, SfxFieldUnit eCtrl );
//STRIP001 long     ControlToItem( long nIn, SfxFieldUnit eCtrl, SfxMapUnit eItem );

//STRIP001 FieldUnit    MapToFieldUnit( const SfxMapUnit eUnit );
//STRIP001 MapUnit      FieldToMapUnit( const SfxFieldUnit eUnit );

//STRIP001 long     ConvertValueToMap( long nVal, SfxMapUnit eUnit );
//STRIP001 long     ConvertValueToUnit( long nVal, SfxMapUnit eUnit );

//STRIP001 void         SetMetricValue( MetricField& rField,
//STRIP001                          long lCoreValue, SfxMapUnit eUnit );
//STRIP001 long         GetCoreValue( const MetricField& rField, SfxMapUnit eUnit );

// to Twips
//STRIP001 long     CMToTwips( long nIn );
//STRIP001 long     MMToTwips( long nIn );
//STRIP001 long     InchToTwips( long nIn );
//STRIP001 long     PointToTwips( long nIn );
//STRIP001 long     PicaToTwips( long nIn );

// to CM
//STRIP001 long     TwipsToCM( long nIn );
//STRIP001 long     InchToCM( long nIn );
//STRIP001 long     MMToCM( long nIn );
//STRIP001 long     PointToCM( long nIn );
//STRIP001 long PicaToCM( long nIn );

// to MM
//STRIP001 long     TwipsToMM( long nIn );
//STRIP001 long     CMToMM( long nIn );
//STRIP001 long     InchToMM( long nIn );
//STRIP001 long     PointToMM( long nIn );
//STRIP001 long     PicaToMM( long nIn );

// to Inch
//STRIP001 long     TwipsToInch(long nIn );
//STRIP001 long     CMToInch(long nIn );
//STRIP001 long     MMToInch(long nIn );
//STRIP001 long     PointToInch(long nIn );
//STRIP001 long PicaToInch(long nIn );

// to Point
//STRIP001 long     TwipsToPoint(long nIn );
//STRIP001 long     InchToPoint(long nIn );
//STRIP001 long     CMToPoint(long nIn );
//STRIP001 long     MMToPoint(long nIn );
//STRIP001 long     PicaToPoint(long nIn );

// To Pica
//STRIP001 long     TwipsToPica(long nIn );
//STRIP001 long     InchToPica(long nIn );
//STRIP001 long     PointToPica(long nIn );
//STRIP001 long     CMToPica(long nIn );
//STRIP001 long MMToPica(long nIn );

// generische Wandlung
//STRIP001 long     TransformMetric( long nVal, FieldUnit aOld, FieldUnit aNew );

// replacement of the SfxIniManager
//STRIP001 String       ConvertPosSizeToIniString( const Point& rPos, const Size& rSize );
//STRIP001 sal_Bool ConvertIniStringToPosSize(  const String& rIniStr, Point& rPos, Size& rSize );

#define OUTPUT_DRAWMODE_COLOR       (DRAWMODE_DEFAULT)
#define OUTPUT_DRAWMODE_CONTRAST    (DRAWMODE_SETTINGSLINE | DRAWMODE_SETTINGSFILL | DRAWMODE_SETTINGSTEXT | DRAWMODE_SETTINGSGRADIENT)

#endif

