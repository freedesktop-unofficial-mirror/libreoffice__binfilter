/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: uitool.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 00:58:40 $
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

#ifndef _UITOOL_HXX
#define _UITOOL_HXX

#ifndef _SV_WINTYPES_HXX //autogen
#include <vcl/wintypes.hxx>
#endif
#ifndef _SV_FIELD_HXX
#include <vcl/field.hxx>
#endif

/*N*/ #include <tools/debug.hxx> //for stripping
class SfxItemSet;
class Printer;
class ListBox;
class DateTime;
namespace binfilter {
class MetricFormatter;
class SfxMedium;
class SwPageDesc;

class SvxTabStopItem;
class SwWrtShell;

class SwDocShell;
class SwFrmFmt;
class SwTabCols;


// Umschalten einer Metric

// BoxInfoAttribut fuellen

// SfxItemSets <-> PageDesc
void ItemSetToPageDesc( const SfxItemSet& rSet, SwPageDesc& rPageDesc );
void PageDescToItemSet( const SwPageDesc& rPageDesc, SfxItemSet& rSet);

// Auffuellen der Tabs mit DefaultTabs

// DefaultTabs loeschen aus dem TabStopArray
//void  EraseDefTabs(SvxTabStopItem& rTabs);

// Abstand zwischen dem 1. und zweitem Element ermitteln
 USHORT     GetTabDist(const SvxTabStopItem& rTabs);

// erfrage ob im Set eine Sfx-PageDesc-Kombination vorliegt
// und setze diesen im Set und loesche die Transport Items
// (PageBreak & PageModel) aus dem Set


// Umwandlung:  Sub(LibName.ModulName) -> LibName.ModulName.Sub

// besorge einen Filenamen/Filternamen. Wird ppMed uebergeben, wird das
// erzeugte Medium returnt. Auch das FilePassword kann returnt werden.

// ListBox mit allen Zeichenvorlagen fuellen - ausser Standard!
//inserts a string sorted into a ListBox,

// Tabellenbreite und Ausrichtung ermitteln


} //namespace binfilter
#endif // _UITOOL_HXX
