/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: pageiter.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 16:17:49 $
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

//STRIP001 class SwDoc;
//STRIP001 class SwPageFrm;
//STRIP001 struct SwPosition;
//STRIP001 class SwPageDesc;

//STRIP001 class SwPageIter {
//STRIP001  const SwDoc &rPDoc;
//STRIP001  const SwPageFrm *pPage;
//STRIP001
//STRIP001 public:
//STRIP001  SwPageIter( const SwDoc &rDoc, const SwPosition &rStartPos );
//STRIP001
//STRIP001  BOOL IsEnd() const { return 0 == pPage; }
//STRIP001  BOOL NextPage();
//STRIP001  const SwPageDesc* GetPageDesc() const;
//STRIP001  BOOL Seek( const SwPosition &rPos );
//STRIP001  BOOL GetPosition( SwPosition &rPos ) const;
//STRIP001 };


} //namespace binfilter
#endif

