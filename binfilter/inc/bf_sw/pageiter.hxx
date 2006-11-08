/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: pageiter.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: kz $ $Date: 2006-11-08 13:11:42 $
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
#ifndef _PAGEITER_HXX
#define _PAGEITER_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
namespace binfilter {

 class SwDoc;
 class SwPageFrm;
 struct SwPosition;
 class SwPageDesc;

 class SwPageIter {
    const SwDoc &rPDoc;
    const SwPageFrm *pPage;

 public:
    SwPageIter( const SwDoc &rDoc, const SwPosition &rStartPos );

    BOOL IsEnd() const { return 0 == pPage; }
    BOOL NextPage();
    const SwPageDesc* GetPageDesc() const;
    BOOL Seek( const SwPosition &rPos );
    BOOL GetPosition( SwPosition &rPos ) const;
 };


} //namespace binfilter
#endif

