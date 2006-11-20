/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: excdocum.hxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: vg $ $Date: 2006-11-20 12:38:55 $
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
#ifdef USED

#ifndef __EXCDOCUM_HXX__
#define __EXCDOCUM_HXX__

// auto strip #ifndef _STRING_HXX //autogen
// auto strip #include <tools/string.hxx>
// auto strip #endif
namespace binfilter {


// Q&D defines statt consts
#define MAX_TABS_EXCDOK 1024

class ExcDokument

// -----------------------------------------------------------------------
// beschreibt eine Excel-Tabelle
class ExcTabelle
    {
    private:
        friend ExcDokument;
        String              aName;
        USHORT              nCS;
        USHORT              nCE;
        USHORT              nRS;
        USHORT              nRE;
        ULONG               nStrPos;

        ExcTabelle( ULONG );                            // mit Stream-Pos
        ExcTabelle( const String & );                   // mit Name
        ExcTabelle( USHORT, USHORT, USHORT, USHORT );   // mit Range
    public:
        ExcTabelle();
        ~ExcTabelle();

        void GetRange( USHORT& rCS, USHORT& rCE, USHORT& rRS, USHORT& rRE ) const
            {
            rCS = nCS;
            rCE = nCE;
            rRS = nRS;
            rRE = nRE;
            }

        ULONG GetStrPos( void ) const
            {
            return nStrPos;
            }

        const String &GetName( void ) const
            {
            return aName;
            }
    };

// -----------------------------------------------------------------------
// beschreibt ein Excel-Dokument
class ExcDokument
    {
    private:
        ExcTabelle          **ppTabellen;
        INT32               nAktGetNext;        // aktueller Index fuer GetNext
        USHORT              nAktTabIndex;       // aktuelle Tabelle in ppTabellen
    public:
        ExcDokument();
        ~ExcDokument();

#ifdef USED
        USHORT              GetAnzTabs( void ) const;
        ExcTabelle          *operator[]( USHORT );
        void                NewTab( const String &rName,
                                ULONG nStrPos = 0xFFFFFFFF );
        void                Set( USHORT nNewCS, USHORT nNewCE,
                                USHORT nNewRS, USHORT nNewRE,
                                USHORT nIndex = 0xFFFF );
        ExcTabelle          *GetNextTab( void );
        ExcTabelle          *GetFirstTab( void );
        void                Set( ULONG nStrPos, USHORT nIndex = 0xFFFF );
        void                Set( const String &rName,
                                USHORT nIndex = 0xFFFF );
#endif
    };

#endif

} //namespace binfilter
#endif

