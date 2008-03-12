/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: forbiuno.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:17:15 $
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

#ifndef SC_FORBIUNO_HXX
#define SC_FORBIUNO_HXX

#ifndef _SVX_UNOFORBIDDENCHARSTABLE_HXX_
#include <bf_svx/UnoForbiddenCharsTable.hxx>
#endif
#ifndef _SFXLSTNER_HXX
#include <bf_svtools/lstner.hxx>
#endif
namespace binfilter {

class ScDocShell;

//------------------------------------------------------------------------

//  object to set forbidden charaters to document

class ScForbiddenCharsObj : public SvxUnoForbiddenCharsTable, public SfxListener
{
    ScDocShell*     pDocShell;

protected:
    virtual void    onChange();

public:
                    ScForbiddenCharsObj( ScDocShell* pDocSh );
    virtual         ~ScForbiddenCharsObj();

    virtual void    Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
};

} //namespace binfilter
#endif

