/*************************************************************************
 *
 *  $RCSfile: paralist.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hjs $ $Date: 2004-06-28 12:33:18 $
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

#ifndef _PARALIST_HXX
#define _PARALIST_HXX

//STRIP008 class Paragraph;

#ifndef _LIST_HXX
#include <tools/list.hxx>
#endif

#ifndef _LINK_HXX
#include <tools/link.hxx>
#endif
namespace binfilter {
class Paragraph;

class ParagraphList : private List
{
private:
    Link            aVisibleStateChangedHdl;

public:
    void            Clear( BOOL bDestroyParagraphs );

    ULONG           GetParagraphCount() const           { return List::Count(); }
    Paragraph*      GetParagraph( ULONG nPos ) const    { return (Paragraph*)List::GetObject( nPos ); }

    ULONG           GetAbsPos( Paragraph* pParent ) const { return List::GetPos( pParent ); }
//STRIP001  ULONG           GetVisPos( Paragraph* pParagraph );

    void            Insert( Paragraph* pPara, ULONG nAbsPos = LIST_APPEND ) { List::Insert( pPara, nAbsPos ); }
    void            Remove( ULONG nPara ) { List::Remove( nPara ); }
//STRIP001  void            MoveParagraphs( ULONG nStart, ULONG nDest, ULONG nCount );

//STRIP001  Paragraph*      NextVisible( Paragraph* ) const;
//STRIP001  Paragraph*      PrevVisible( Paragraph* ) const;
//STRIP001  Paragraph*      LastVisible() const;

/*NBFF*/    Paragraph*      GetParent( Paragraph* pParagraph, USHORT& rRelPos ) const;
//STRIP001  BOOL            HasChilds( Paragraph* pParagraph ) const;
//STRIP001  BOOL            HasHiddenChilds( Paragraph* pParagraph ) const;
//STRIP001  BOOL            HasVisibleChilds( Paragraph* pParagraph ) const;
//STRIP001  ULONG           GetChildCount( Paragraph* pParagraph ) const;

//STRIP001  void            Expand( Paragraph* pParent );
//STRIP001  void            Collapse( Paragraph* pParent );

    void            SetVisibleStateChangedHdl( const Link& rLink ) { aVisibleStateChangedHdl = rLink; }
    Link            GetVisibleStateChangedHdl() const { return aVisibleStateChangedHdl; }
};

}//end of namespace binfilter
#endif
