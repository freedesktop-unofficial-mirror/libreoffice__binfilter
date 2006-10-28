/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: cusshow.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:52:03 $
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

#ifndef _SD_CUSSHOW_HXX
#define _SD_CUSSHOW_HXX


#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif


#ifndef _CPPUHELPER_WEAKREF_HXX_
#include <cppuhelper/weakref.hxx>
#endif
namespace binfilter {

class SdDrawDocument;

/*************************************************************************
|*
|* CustomShow
|*
\************************************************************************/
class SdCustomShow : public List
{
private:
    String          aName;
    SdDrawDocument* pDoc;

    // this is a weak reference to a possible living api wrapper for this custom show
    ::com::sun::star::uno::WeakReference< ::com::sun::star::uno::XInterface > mxUnoCustomShow;

public:
    SdCustomShow(SdDrawDocument* pDrawDoc);
    SdCustomShow(SdDrawDocument* pDrawDoc, ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > xShow );

    SdCustomShow( const SdCustomShow& rShow );
    virtual ~SdCustomShow();

    void   SetName(const String& rName) { aName = rName; }
    String GetName() const              { return aName; }

    SdDrawDocument* GetDoc() const { return pDoc; }

    friend SvStream& operator << (SvStream& rOut, const SdCustomShow& rCustomShow);
    friend SvStream& operator >> (SvStream& rIn, SdCustomShow& rCustomShow);

    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > getUnoCustomShow();
};

} //namespace binfilter
#endif      // _SD_CUSSHOW_HXX

