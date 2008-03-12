/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: SchTransferable.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 07:25:00 $
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
#ifndef _SCH_TRANSFERABLE_HXX_
#define _SCH_TRANSFERABLE_HXX_

#ifndef _TRANSFER_HXX
#include <bf_svtools/transfer.hxx>
#endif

/*N*/ #include <tools/debug.hxx> //for stripping
class Graphic;
class VirtualDevice;
namespace binfilter {
class SdrModel;
class SdrExchangeView;

class SchTransferable :
    public TransferableHelper
{
private:
    SdrExchangeView  *              mpSourceView;

protected:

    // implementation of TransferableHelper methods

public:

    /** CTOR for clipboard, drag and drop and selection clipboard
        @param pObjModel the model containing all objects for the clipboard.
                         The transferable becomes the owner of this model.
        @param pSrcView  the view for drag and drop and the selection clipboard
                         The transferable does not care about destruction of this view
        @param rObjDesc  A descriptor object that holds properties like the starting
                         position of a drag action
        @param bLateInit If true, the actual data is created in GetData (on paste),
                         else data is created on construction
     */
    SchTransferable( SdrModel* pObjModel,
                     SdrExchangeView* pSrcView,
                     const TransferableObjectDescriptor& rObjDesc,
                     sal_Bool bLateInit = sal_False );
      const SdrExchangeView* GetView() throw()      { return mpSourceView; }
};

} //namespace binfilter
#endif  // _SCH_TRANSFERABLE_HXX_
