/*************************************************************************
 *
 *  $RCSfile: docpool.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:59:43 $
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

#ifndef SC_SCDOCPOL_HXX
#define SC_SCDOCPOL_HXX

#ifndef _SFXITEMPOOL_HXX //autogen
#include <svtools/itempool.hxx>
#endif
namespace binfilter {

class ScStyleSheet;

//------------------------------------------------------------------------

class ScDocumentPool: public SfxItemPool
{
    SfxPoolItem**   ppPoolDefaults;
    SfxItemPool*    pSecondary;
    static USHORT*  pVersionMap1;
    static USHORT*  pVersionMap2;
    static USHORT*  pVersionMap3;
    static USHORT*  pVersionMap4;
    static USHORT*  pVersionMap5;
    static USHORT*  pVersionMap6;
    static USHORT*  pVersionMap7;
    static USHORT*  pVersionMap8;
    static USHORT*  pVersionMap9;

public:
            ScDocumentPool( SfxItemPool* pSecPool = NULL, BOOL bLoadRefCounts = FALSE );
            ~ScDocumentPool();

//STRIP001  virtual SfxItemPool*        Clone() const;
//STRIP001  virtual SfxMapUnit          GetMetric( USHORT nWhich ) const;

    virtual const SfxPoolItem&  Put( const SfxPoolItem&, USHORT nWhich = 0 );
    virtual void                Remove( const SfxPoolItem& );
    static void                 CheckRef( const SfxPoolItem& );
    void                        MyLoadCompleted();

//STRIP001  void StyleDeleted( ScStyleSheet* pStyle );      // Loeschen von Vorlagen im Organizer
//STRIP001  virtual SfxItemPresentation     GetPresentation(
//STRIP001                                      const SfxPoolItem&  rItem,
//STRIP001                                      SfxItemPresentation ePresentation,
//STRIP001                                      SfxMapUnit          ePresentationMetric,
//STRIP001                                      String&             rText,
//STRIP001                                         const IntlWrapper* pIntl = 0 ) const;

    static void InitVersionMaps();
    static void DeleteVersionMaps();
};




} //namespace binfilter
#endif
