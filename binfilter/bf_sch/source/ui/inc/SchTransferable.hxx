/*************************************************************************
 *
 *  $RCSfile: SchTransferable.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:17:39 $
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
#ifndef _SCH_TRANSFERABLE_HXX_
#define _SCH_TRANSFERABLE_HXX_

#ifndef _TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif
#ifndef _EMBOBJ_HXX
#include <so3/embobj.hxx>
#endif
/*N*/ #include <tools/debug.hxx> //for stripping
class SdrModel;
class SdrExchangeView;
class Graphic;
class VirtualDevice;

class SchTransferable :
    public TransferableHelper
{
private:
//STRIP001
//STRIP001     SdrModel *                      mpContentModel;
    SdrExchangeView  *              mpSourceView;
//STRIP001     TransferableObjectDescriptor    maObjDesc;
//STRIP001     sal_Bool                        mbLateInit;
//STRIP001
//STRIP001     SdrModel *                      mpOwnModel;
//STRIP001     SdrExchangeView  *              mpOwnView;
//STRIP001     Graphic  *                      mpGraphic;
//STRIP001
//STRIP001     bool                            mbDataCreated;
//STRIP001     bool                            mbOwnView;
//STRIP001     bool                            mbOwnDoc;
//STRIP001
//STRIP001     void                            CreateData();

protected:

    // implementation of TransferableHelper methods
//STRIP001  virtual void        AddSupportedFormats();
//STRIP001  virtual sal_Bool    GetData( const ::com::sun::star::datatransfer::DataFlavor& rFlavor );
//STRIP001  virtual sal_Bool    WriteObject( SotStorageStreamRef& rxOStm, void* pUserObject, sal_uInt32 nUserObjectId,
//STRIP001                                   const ::com::sun::star::datatransfer::DataFlavor& rFlavor );
//STRIP001  virtual void        ObjectReleased();

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
//STRIP001
//STRIP001  virtual ~SchTransferable();
//STRIP001
//STRIP001  static const com::sun::star::uno::Sequence< sal_Int8 > & getUnoTunnelId() throw();
//STRIP001  static SchTransferable* getImplementation( com::sun::star::uno::Reference< com::sun::star::uno::XInterface > ) throw();
//STRIP001
//STRIP001     // XUnoTunnel ( ::TransferableHelper )
//STRIP001     virtual sal_Int64 SAL_CALL getSomething( const com::sun::star::uno::Sequence< sal_Int8 >& aIdentifier )
//STRIP001      throw( com::sun::star::uno::RuntimeException );
//STRIP001
      const SdrExchangeView* GetView() throw()      { return mpSourceView; }
};

#endif  // _SCH_TRANSFERABLE_HXX_
