/*************************************************************************
 *
 *  $RCSfile: svx_fmprop.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:43:41 $
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
#pragma hdrstop

#define USE_PROPERTY_HELPER

#ifndef _SVX_FMPROP_HXX
#include "fmprop.hxx"
#endif
#ifndef _SVX_FMPROP_HRC
#include "fmprop.hrc"
#endif

#ifndef _TOOLS_DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif

#ifndef _SHL_HXX
#include <tools/shl.hxx>
#endif

#ifndef _SVX_DIALMGR_HXX //autogen
#include "dialmgr.hxx"
#endif

#ifndef _TOOLS_RESID_HXX //autogen
#include <tools/resid.hxx>
#endif

#ifndef _SVX_FMRESIDS_HRC
#include "fmresids.hrc"
#endif
#ifndef _SVX_FMHELP_HRC
#include "fmhelp.hrc"
#endif
#ifndef _SVX_FMTOOLS_HXX
#include "fmtools.hxx"
#endif

#ifndef _XCEPTION_HXX_ //autogen
#include <vos/xception.hxx>
#endif
#ifndef _FM_STATIC_HXX_
#include "fmstatic.hxx"
#endif
namespace binfilter {

//STRIP001 sal_uInt16 FmPropertyInfoService::nCount = 0;
//STRIP001 FmPropertyInfo* FmPropertyInfoService::pPropertyInfos = NULL;
//STRIP001
//STRIP001
//STRIP001 // Vergleichen von PropertyInfo
//STRIP001 static int
//STRIP001 #if defined( WNT )
//STRIP001  __cdecl
//STRIP001 #endif
//STRIP001 #if defined( ICC ) && defined( OS2 )
//STRIP001 _Optlink
//STRIP001 #endif
//STRIP001  PropertyInfoCompare(const void* pFirst, const void* pSecond)
//STRIP001 {
//STRIP001  return reinterpret_cast<const FmPropertyInfo*>(pFirst)->aName.compareTo(reinterpret_cast<const FmPropertyInfo*>(pSecond)->aName);
//STRIP001 }
//STRIP001
/*?*/ namespace svxform
/*?*/ {
//STRIP001
//STRIP001  // property names
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_TABINDEX,"TabIndex");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_TAG,"Tag");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_NAME,"Name");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_CLASSID,"ClassId");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ROWCOUNT,"RowCount");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ROWCOUNTFINAL,"IsRowCountFinal");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FETCHSIZE,"FetchSize");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_VALUE,"Value");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_TEXT,"Text");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_LABEL,"Label");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_CANINSERT,"CanInsert");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_CANUPDATE,"CanUpdate");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_CANDELETE,"CanDelete");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_NAVIGATION,"NavigationBarMode");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_HASNAVIGATION,"HasNavigationBar");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_CYCLE,"Cycle");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_CONTROLSOURCE,"DataField");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ENABLED,"Enabled");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_READONLY,"ReadOnly");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ISREADONLY,"IsReadOnly");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FILTER_CRITERIA,"Filter");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ISREQUIRED,"IsRequired");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_AUTOINCREMENT,"IsAutoIncrement");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_CACHESIZE,"CacheSize");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DATAENTRY,"DataEntry");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_LASTDIRTY,"LastUpdated");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_STATEMENT,"Statement");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_WIDTH,"Width");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_SEARCHABLE,"IsSearchable");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_MULTILINE,"MultiLine");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_TARGET_URL,"TargetURL");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_TARGET_FRAME,"TargetFrame");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DEFAULTCONTROL,"DefaultControl");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_MAXTEXTLEN,"MaxTextLen");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_EDITMASK,"EditMask");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_SIZE,"Size");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_SPIN,"Spin");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DATE,"Date");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_TIME,"Time");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_STATE,"State");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_TRISTATE,"TriState");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_HIDDEN_VALUE, "HiddenValue");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_BUTTONTYPE,"ButtonType");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_STRINGITEMLIST,"StringItemList");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DEFAULT_TEXT,"DefaultText");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DEFAULTCHECKED,"DefaultState");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FORMATKEY,"FormatKey");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FORMATSSUPPLIER,"FormatsSupplier");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_SUBMIT_ACTION,"SubmitAction");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_SUBMIT_TARGET,"SubmitTarget");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_SUBMIT_METHOD,"SubmitMethod");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_SUBMIT_ENCODING,"SubmitEncoding");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_IMAGE_URL,"ImageURL");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_EMPTY_IS_NULL,"ConvertEmptyToNull");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_LISTSOURCETYPE,"ListSourceType");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_LISTSOURCE,"ListSource");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_SELECT_SEQ,"SelectedItems");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_VALUE_SEQ,"ValueItemList");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DEFAULT_SELECT_SEQ,"DefaultSelection");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_MULTISELECTION,"MultiSelection");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ALIGN,"Align");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DEFAULT_DATE,"DefaultDate");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DEFAULT_TIME,"DefaultTime");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DEFAULT_VALUE,"DefaultValue");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DECIMAL_ACCURACY,"DecimalAccuracy");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_CURSORSOURCE,"DataSelection");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_CURSORSOURCETYPE,"DataSelectionType");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FIELDTYPE,"Type");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DECIMALS,"Decimals");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_REFVALUE,"RefValue");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_VALUEMIN,"ValueMin");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_VALUEMAX,"ValueMax");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_STRICTFORMAT,"StrictFormat");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ALLOWADDITIONS,"AllowInserts");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ALLOWEDITS,"AllowUpdates");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ALLOWDELETIONS,"AllowDeletes");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_MASTERFIELDS,"MasterFields");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ISPASSTHROUGH,"IsPassThrough");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_QUERY,"Query");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_LITERALMASK,"LiteralMask");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_VALUESTEP,"ValueStep");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_SHOWTHOUSANDSEP,"ShowThousandsSeparator");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_CURRENCYSYMBOL,"CurrencySymbol");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DATEFORMAT,"DateFormat");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DATEMIN,"DateMin");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DATEMAX,"DateMax");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DATE_SHOW_CENTURY,"DateShowCentury");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_TIMEFORMAT, "TimeFormat");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_TIMEMIN, "TimeMin");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_TIMEMAX,"TimeMax");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_LINECOUNT,"LineCount");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_BOUNDCOLUMN, "BoundColumn");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FONT,"FontDescriptor");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_BACKGROUNDCOLOR,"BackgroundColor");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FILLCOLOR,"FillColor");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_TEXTCOLOR,"TextColor");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_LINECOLOR,"LineColor");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_BORDER,"Border");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DROPDOWN,"Dropdown");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_MULTI,"Multi");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_HSCROLL,"HScroll");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_VSCROLL,"VScroll");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_TABSTOP,"Tabstop");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_AUTOCOMPLETE,"Autocomplete");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_HARDLINEBREAKS,"HardLineBreaks");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_PRINTABLE,"Printable");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ECHO_CHAR,"EchoChar");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ROWHEIGHT,"RowHeight");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_HELPTEXT, "HelpText");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FONT_NAME, "FontName");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FONT_STYLENAME, "FontStyleName");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FONT_FAMILY, "FontFamily");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FONT_CHARSET, "FontCharset");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FONT_HEIGHT, "FontHeight");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FONT_WEIGHT, "FontWeight");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FONT_SLANT, "FontSlant");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FONT_UNDERLINE, "FontUnderline");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FONT_STRIKEOUT, "FontStrikeout");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_HELPURL, "HelpURL");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_RECORDMARKER, "HasRecordMarker");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_BOUNDFIELD, "BoundField");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_EFFECTIVE_VALUE, "EffectiveValue");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_EFFECTIVE_DEFAULT, "EffectiveDefault");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_EFFECTIVE_MIN, "EffectiveMin");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_EFFECTIVE_MAX, "EffectiveMax");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_HIDDEN, "Hidden");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FILTERPROPOSAL, "UseFilterValueProposal");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FIELDSOURCE, "FieldSource");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_TABLENAME, "TableName");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FILTERSUPPLIER, "FilterSupplier");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_CURRENTFILTER, "CurrentFilter");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_SELECTED_FIELDS, "SelectedFields");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_SELECTED_TABLES, "SelectedTables");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_THREADSAFE, "ThreadSafe");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ISFILTERAPPLIED, "IsFilterApplied");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_CONTROLLABEL, "LabelControl");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_CURRSYM_POSITION, "PrependCurrencySymbol");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_SOURCE, "Source");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_CURSORCOLOR, "CursorColor");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ALWAYSSHOWCURSOR, "AlwaysShowCursor");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DISPLAYSYNCHRON, "DisplayIsSynchron");
//STRIP001
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ISMODIFIED, "IsModified");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ISNEW, "IsNew");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_PRIVILEGES, "Privileges");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_COMMAND,"Command");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_COMMANDTYPE,"CommandType");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_RESULTSET_CONCURRENCY, "ResultSetConcurrency");
//STRIP001  // renamed
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_INSERTONLY, "IgnoreResult");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_RESULTSET_TYPE, "ResultSetType");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ESCAPE_PROCESSING, "EscapeProcessing");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_APPLYFILTER, "ApplyFilter");
//STRIP001
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ISNULLABLE, "IsNullable");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ACTIVECOMMAND, "ActiveCommand");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ISCURRENCY, "IsCurrency");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_NUMBER_FORMATS_SUPPLIER, "NumberFormatsSupplier");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_URL, "URL");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_TITLE, "Title");
/*?*/   IMPLEMENT_CONSTASCII_USTRING(FM_PROP_ACTIVE_CONNECTION, "ActiveConnection");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_SCALE, "Scale");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_SORT, "Order");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DATASOURCE, "DataSourceName");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_DETAILFIELDS,"DetailFields");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_REALNAME,"RealName");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_CONTROLSOURCEPROPERTY,"DataFieldProperty");
//STRIP001
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_TEXTLINECOLOR, "TextLineColor");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FONTEMPHASISMARK, "FontEmphasisMark");
//STRIP001  IMPLEMENT_CONSTASCII_USTRING(FM_PROP_FONTRELIEF, "FontRelief");
//STRIP001
/*?*/ } // namespace svxform
//STRIP001
//STRIP001 using namespace svxform;
//STRIP001
//STRIP001
//STRIP001 // Zuordnung von Namen auf Properties Id's, das koennten auch WhichId's fuer Itemset sein
//STRIP001 //------------------------------------------------------------------
//STRIP001 const FmPropertyInfo* FmPropertyInfoService::getPropertyInfo()
//STRIP001 {
//STRIP001  // dieser umstaendliche Weg wird gewaehlt um die Reihenfolge der Initialisierung
//STRIP001  // abzusichern
//STRIP001
//STRIP001  sal_uInt16 nPos=1;
//STRIP001  if (pPropertyInfos == NULL)
//STRIP001  {
//STRIP001      // the following does not contain all know properties
//STRIP001      // ever property which is _not_ multi-property-able (means cannot be set on multiple controls at once)
//STRIP001      // and which does not have an UI name is omitted by definition
//STRIP001      static FmPropertyInfo __READONLY_DATA aPropertyInfos[] =
//STRIP001      {
//STRIP001          FmPropertyInfo(FM_PROP_NAME,                sal_False, RID_STR_NAME),
//STRIP001          FmPropertyInfo(FM_PROP_LABEL,               sal_True,  RID_STR_LABEL),
//STRIP001          FmPropertyInfo(FM_PROP_CONTROLLABEL,        sal_False, RID_STR_LABELCONTROL),
//STRIP001          FmPropertyInfo(FM_PROP_TEXT,                sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_MAXTEXTLEN,          sal_True,  RID_STR_MAXTEXTLEN),
//STRIP001          FmPropertyInfo(FM_PROP_EDITMASK,            sal_True,  RID_STR_EDITMASK),
//STRIP001          FmPropertyInfo(FM_PROP_LITERALMASK,         sal_True,  RID_STR_LITERALMASK),
//STRIP001          FmPropertyInfo(FM_PROP_STRICTFORMAT,        sal_True,  RID_STR_STRICTFORMAT),
//STRIP001          FmPropertyInfo(FM_PROP_ENABLED,             sal_True,  RID_STR_ENABLED),
//STRIP001          FmPropertyInfo(FM_PROP_READONLY,            sal_True,  RID_STR_READONLY),
//STRIP001          FmPropertyInfo(FM_PROP_PRINTABLE,           sal_True,  RID_STR_PRINTABLE),
//STRIP001          FmPropertyInfo(FM_PROP_CONTROLSOURCE,       sal_True,  RID_STR_CONTROLSOURCE),
//STRIP001          FmPropertyInfo(FM_PROP_TABSTOP,             sal_True,  RID_STR_TABSTOP),
//STRIP001          FmPropertyInfo(FM_PROP_TABINDEX,            sal_True,  RID_STR_TABINDEX),
//STRIP001          FmPropertyInfo(FM_PROP_DATASOURCE,          sal_True,  RID_STR_DATASOURCE),
//STRIP001          FmPropertyInfo(FM_PROP_COMMAND,             sal_False, RID_STR_CURSORSOURCE),
//STRIP001          FmPropertyInfo(FM_PROP_COMMANDTYPE,         sal_False, RID_STR_CURSORSOURCETYPE),
//STRIP001          FmPropertyInfo(FM_PROP_ESCAPE_PROCESSING,   sal_False, RID_STR_ESCAPE_PROCESSING),
//STRIP001          FmPropertyInfo(FM_PROP_FILTER_CRITERIA,     sal_False, RID_STR_FILTER_CRITERIA),
//STRIP001          FmPropertyInfo(FM_PROP_SORT,                sal_False, RID_STR_SORT_CRITERIA),
//STRIP001          FmPropertyInfo(FM_PROP_INSERTONLY,          sal_False, RID_STR_DATAENTRY),
//STRIP001          FmPropertyInfo(FM_PROP_ALLOWADDITIONS,      sal_True,  RID_STR_ALLOW_ADDITIONS),
//STRIP001          FmPropertyInfo(FM_PROP_ALLOWEDITS,          sal_True,  RID_STR_ALLOW_EDITS),
//STRIP001          FmPropertyInfo(FM_PROP_ALLOWDELETIONS,      sal_True,  RID_STR_ALLOW_DELETIONS),
//STRIP001          FmPropertyInfo(FM_PROP_INSERTONLY,          sal_True,  RID_STR_DATAENTRY),
//STRIP001          FmPropertyInfo(FM_PROP_NAVIGATION,          sal_True,  RID_STR_NAVIGATIONBAR),
//STRIP001          FmPropertyInfo(FM_PROP_CYCLE,               sal_True,  RID_STR_CYCLE),
//STRIP001          FmPropertyInfo(FM_PROP_CACHESIZE,           sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_LASTDIRTY,           sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_HIDDEN_VALUE,        sal_True,  RID_STR_VALUE),
//STRIP001          FmPropertyInfo(FM_PROP_VALUE,               sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_VALUEMIN,            sal_True,  RID_STR_VALUEMIN),
//STRIP001          FmPropertyInfo(FM_PROP_VALUEMAX,            sal_True,  RID_STR_VALUEMAX),
//STRIP001          FmPropertyInfo(FM_PROP_VALUESTEP,           sal_True,  RID_STR_VALUESTEP),
//STRIP001          FmPropertyInfo(FM_PROP_DEFAULT_VALUE,       sal_True,  RID_STR_DEFAULTVALUE),
//STRIP001          FmPropertyInfo(FM_PROP_DECIMAL_ACCURACY,    sal_True,  RID_STR_DECIMAL_ACCURACY),
//STRIP001          FmPropertyInfo(FM_PROP_DECIMALS,            sal_True,   0),
//STRIP001          FmPropertyInfo(FM_PROP_SHOWTHOUSANDSEP,     sal_True,  RID_STR_SHOWTHOUSANDSEP),
//STRIP001          FmPropertyInfo(FM_PROP_REFVALUE,            sal_True,  RID_STR_REFVALUE),
//STRIP001          FmPropertyInfo(FM_PROP_CURRENCYSYMBOL,      sal_True,  RID_STR_CURRENCYSYMBOL),
//STRIP001          FmPropertyInfo(FM_PROP_CURRSYM_POSITION,    sal_True,  RID_STR_CURRSYM_POSITION),
//STRIP001          FmPropertyInfo(FM_PROP_DATE,                sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_DATEMIN,             sal_True,  RID_STR_DATEMIN),
//STRIP001          FmPropertyInfo(FM_PROP_DATEMAX,             sal_True,  RID_STR_DATEMAX),
//STRIP001          FmPropertyInfo(FM_PROP_DATEFORMAT,          sal_True,  RID_STR_DATEFORMAT),
//STRIP001          FmPropertyInfo(FM_PROP_DEFAULT_DATE,        sal_True,  RID_STR_DEFAULTVALUE),
//STRIP001          FmPropertyInfo(FM_PROP_TIME,                sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_TIMEMIN,             sal_True,  RID_STR_TIMEMIN),
//STRIP001          FmPropertyInfo(FM_PROP_TIMEMAX,             sal_True,  RID_STR_TIMEMAX),
//STRIP001          FmPropertyInfo(FM_PROP_TIMEFORMAT,          sal_True,  RID_STR_TIMEFORMAT),
//STRIP001          FmPropertyInfo(FM_PROP_DEFAULT_TIME,        sal_True,  RID_STR_DEFAULTVALUE),
//STRIP001          FmPropertyInfo(FM_PROP_EFFECTIVE_MIN,       sal_False, RID_STR_VALUEMIN),
//STRIP001          FmPropertyInfo(FM_PROP_EFFECTIVE_MAX,       sal_False, RID_STR_VALUEMAX),
//STRIP001          FmPropertyInfo(FM_PROP_EFFECTIVE_DEFAULT,   sal_False, RID_STR_DEFAULTVALUE),
//STRIP001          FmPropertyInfo(FM_PROP_FORMATKEY,           sal_True,  RID_STR_FORMATKEY),
//STRIP001          FmPropertyInfo(FM_PROP_FORMATSSUPPLIER,     sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_SIZE,                sal_True,  RID_STR_SIZE),
//STRIP001          FmPropertyInfo(FM_PROP_CLASSID,             sal_False, RID_STR_CLASSID),
//STRIP001          FmPropertyInfo(FM_PROP_WIDTH,               sal_True,  RID_STR_WIDTH),
//STRIP001          FmPropertyInfo(FM_PROP_DEFAULTCONTROL,      sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_BOUNDCOLUMN,         sal_True,  RID_STR_BOUNDCOLUMN),
//STRIP001          FmPropertyInfo(FM_PROP_LISTSOURCETYPE,      sal_True,  RID_STR_LISTSOURCETYPE),
//STRIP001          FmPropertyInfo(FM_PROP_LISTSOURCE,          sal_True,  RID_STR_LISTSOURCE),
//STRIP001          FmPropertyInfo(FM_PROP_STRINGITEMLIST,      sal_True,  RID_STR_STRINGITEMLIST),
//STRIP001          FmPropertyInfo(FM_PROP_DEFAULT_TEXT,        sal_True,  RID_STR_DEFAULTVALUE),
//STRIP001          FmPropertyInfo(FM_PROP_FONT_NAME,           sal_True,  RID_STR_FONT),
//STRIP001          FmPropertyInfo(FM_PROP_FONT_STYLENAME,      sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_FONT_FAMILY,         sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_FONT_CHARSET,        sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_FONT_HEIGHT,         sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_FONT_WEIGHT,         sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_FONT_SLANT,          sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_FONT_UNDERLINE,      sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_FONT_STRIKEOUT,      sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_ALIGN,               sal_True,  RID_STR_ALIGN),
//STRIP001          FmPropertyInfo(FM_PROP_ROWHEIGHT,           sal_True,  RID_STR_ROWHEIGHT),
//STRIP001          FmPropertyInfo(FM_PROP_BACKGROUNDCOLOR,     sal_True,  RID_STR_BACKGROUNDCOLOR),
//STRIP001          FmPropertyInfo(FM_PROP_FILLCOLOR,           sal_True,  RID_STR_FILLCOLOR),
//STRIP001          FmPropertyInfo(FM_PROP_TEXTCOLOR,           sal_True,  RID_STR_TEXTCOLOR),
//STRIP001          FmPropertyInfo(FM_PROP_LINECOLOR,           sal_True,  RID_STR_LINECOLOR),
//STRIP001          FmPropertyInfo(FM_PROP_BORDER,              sal_True,  RID_STR_BORDER),
//STRIP001          FmPropertyInfo(FM_PROP_DROPDOWN,            sal_True,  RID_STR_DROPDOWN),
//STRIP001          FmPropertyInfo(FM_PROP_AUTOCOMPLETE,        sal_True,  RID_STR_AUTOCOMPLETE),
//STRIP001          FmPropertyInfo(FM_PROP_LINECOUNT,           sal_True,  RID_STR_LINECOUNT),
//STRIP001          FmPropertyInfo(FM_PROP_MULTI,               sal_True,  RID_STR_MULTILINE),
//STRIP001          FmPropertyInfo(FM_PROP_MULTILINE,           sal_True,  RID_STR_MULTILINE),
//STRIP001          FmPropertyInfo(FM_PROP_MULTISELECTION,      sal_True,  RID_STR_MULTISELECTION),
//STRIP001          FmPropertyInfo(FM_PROP_HARDLINEBREAKS,      sal_True,  RID_STR_HARDLINEBREAKS),
//STRIP001          FmPropertyInfo(FM_PROP_HSCROLL,             sal_True,  RID_STR_HSCROLL),
//STRIP001          FmPropertyInfo(FM_PROP_VSCROLL,             sal_True,  RID_STR_VSCROLL),
//STRIP001          FmPropertyInfo(FM_PROP_SPIN,                sal_True,  RID_STR_SPIN),
//STRIP001          FmPropertyInfo(FM_PROP_STATE,               sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_BUTTONTYPE,          sal_True,  RID_STR_BUTTONTYPE),
//STRIP001          FmPropertyInfo(FM_PROP_TARGET_URL,          sal_True,  RID_STR_TARGET_URL),
//STRIP001          FmPropertyInfo(FM_PROP_TARGET_FRAME,        sal_True,  RID_STR_TARGET_FRAME),
//STRIP001          FmPropertyInfo(FM_PROP_SUBMIT_ACTION,       sal_True,  RID_STR_SUBMIT_ACTION),
//STRIP001          FmPropertyInfo(FM_PROP_SUBMIT_TARGET,       sal_True,  RID_STR_SUBMIT_TARGET),
//STRIP001          FmPropertyInfo(FM_PROP_SUBMIT_METHOD,       sal_True,  RID_STR_SUBMIT_METHOD),
//STRIP001          FmPropertyInfo(FM_PROP_SUBMIT_ENCODING,     sal_True,  RID_STR_SUBMIT_ENCODING),
//STRIP001          FmPropertyInfo(FM_PROP_DEFAULTCHECKED,      sal_True,  RID_STR_DEFAULT_CHECKED),
//STRIP001          FmPropertyInfo(::rtl::OUString::createFromAscii("DefaultButton"), sal_True,  RID_STR_DEFAULT_BUTTON),
//STRIP001          FmPropertyInfo(FM_PROP_VALUE_SEQ,           sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_IMAGE_URL,           sal_True,  RID_STR_IMAGE_URL),
//STRIP001          FmPropertyInfo(FM_PROP_SELECT_SEQ,          sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_DEFAULT_SELECT_SEQ,  sal_True,  RID_STR_DEFAULT_SELECT_SEQ),
//STRIP001          FmPropertyInfo(FM_PROP_ECHO_CHAR,           sal_True,  RID_STR_ECHO_CHAR),
//STRIP001          FmPropertyInfo(FM_PROP_EMPTY_IS_NULL,       sal_True,  RID_STR_EMPTY_IS_NULL),
//STRIP001          FmPropertyInfo(FM_PROP_TRISTATE,            sal_True,  RID_STR_TRISTATE),
//STRIP001          FmPropertyInfo(FM_PROP_MASTERFIELDS,        sal_True,  RID_STR_MASTERFIELDS),
//STRIP001          FmPropertyInfo(FM_PROP_DETAILFIELDS,        sal_True,  RID_STR_SLAVEFIELDS),
//STRIP001          FmPropertyInfo(FM_PROP_HASNAVIGATION,       sal_True,  RID_STR_NAVIGATIONBAR),
//STRIP001          FmPropertyInfo(FM_PROP_RECORDMARKER,        sal_True,  RID_STR_RECORDMARKER),
//STRIP001          FmPropertyInfo(FM_PROP_FILTERPROPOSAL,      sal_True,  RID_STR_FILTERPROPOSAL),
//STRIP001          FmPropertyInfo(FM_PROP_QUERY,               sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_ISPASSTHROUGH,       sal_True,  0),
//STRIP001          FmPropertyInfo(FM_PROP_TAG,                 sal_True,  RID_STR_TAG),
//STRIP001          FmPropertyInfo(FM_PROP_HELPTEXT,            sal_False, RID_STR_HELPTEXT),
//STRIP001          FmPropertyInfo(FM_PROP_HELPURL,             sal_False, RID_STR_HELPURL),
//STRIP001          FmPropertyInfo(FM_PROP_CURSORCOLOR,         sal_True, 0),
//STRIP001          FmPropertyInfo(FM_PROP_ALWAYSSHOWCURSOR,    sal_True, 0),
//STRIP001          FmPropertyInfo(FM_PROP_DISPLAYSYNCHRON,     sal_True, 0)
//STRIP001      };
//STRIP001
//STRIP001      pPropertyInfos = (FmPropertyInfo*)aPropertyInfos;
//STRIP001      nCount = sizeof(aPropertyInfos) / sizeof(FmPropertyInfo);
//STRIP001
//STRIP001      // nochmal sortieren, sicher ist sicher
//STRIP001      qsort((void*) aPropertyInfos,
//STRIP001           nCount,
//STRIP001           sizeof(FmPropertyInfo),
//STRIP001           &PropertyInfoCompare);
//STRIP001
//STRIP001  }
//STRIP001  return pPropertyInfos;
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------
//STRIP001 FmPropertyInfo::FmPropertyInfo(const ::rtl::OUString& _rName, sal_Bool bMSel,
//STRIP001                             sal_uInt16 _nDisplayNameResId)
//STRIP001
//STRIP001             :aName(_rName)
//STRIP001             ,bMultiSelectable(bMSel)
//STRIP001             ,nDisplayNameResId( _nDisplayNameResId )
//STRIP001 {
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------
//STRIP001 ::rtl::OUString FmPropertyInfoService::getPropertyTranslation( const ::rtl::OUString _rName )
//STRIP001 {
//STRIP001  const FmPropertyInfo* pInfo = getPropertyInfo( _rName );
//STRIP001  return  ( pInfo && ( pInfo->nDisplayNameResId > 0 ) )
//STRIP001      ?   ::rtl::OUString( SVX_RES( pInfo->nDisplayNameResId ) )
//STRIP001      :   ::rtl::OUString();
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------------
//STRIP001 sal_Bool FmPropertyInfoService::getPropertyMultiFlag( const ::rtl::OUString _rName )
//STRIP001 {
//STRIP001  const FmPropertyInfo* pInfo = getPropertyInfo( _rName );
//STRIP001  return (pInfo) ? pInfo->bMultiSelectable : sal_False;
//STRIP001 }
//STRIP001
//STRIP001 //------------------------------------------------------------------------
//STRIP001 const FmPropertyInfo* FmPropertyInfoService::getPropertyInfo(const ::rtl::OUString& _rName)
//STRIP001 {
//STRIP001  // intialisierung
//STRIP001  if(!pPropertyInfos)
//STRIP001      getPropertyInfo();
//STRIP001  FmPropertyInfo  aSearch( _rName, sal_False, 0 );
//STRIP001
//STRIP001  const FmPropertyInfo* pPropInfo = (FmPropertyInfo*) bsearch(&aSearch,
//STRIP001                                  (void*) pPropertyInfos,
//STRIP001                                   nCount,
//STRIP001                                   sizeof(FmPropertyInfo),
//STRIP001                                   &PropertyInfoCompare);
//STRIP001
//STRIP001  return pPropInfo;
//STRIP001 }


}
