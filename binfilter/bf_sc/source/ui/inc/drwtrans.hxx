/*************************************************************************
 *
 *  $RCSfile: drwtrans.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:18:25 $
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

#ifndef SC_DRWTRANS_HXX
#define SC_DRWTRANS_HXX

#ifndef _TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif

#ifndef _IPOBJ_HXX
#include <so3/ipobj.hxx>
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif


class SdrModel;
class ScDocShell;
class INetBookmark;
class SdrObject;
class SdrView;
class ScDrawView;

class ScDrawTransferObj : public TransferableHelper
{
private:
    SdrModel*                       pModel;
    TransferableDataHelper          aOleData;
    TransferableObjectDescriptor    aObjDesc;
    SvEmbeddedObjectRef             aDocShellRef;
    SvEmbeddedObjectRef             aDrawPersistRef;
                                    // extracted from model in ctor:
    Size                            aSrcSize;
    INetBookmark*                   pBookmark;
    BOOL                            bGraphic;
    BOOL                            bGrIsBit;
    BOOL                            bOleObj;
                                    // source information for drag&drop:
                                    // (view is needed to handle drawing obejcts)
    SdrView*                        pDragSourceView;
    USHORT                          nDragSourceFlags;
    BOOL                            bDragWasInternal;

    sal_uInt32                      nSourceDocID;


//STRIP001  void                InitDocShell();
//STRIP001  SvInPlaceObjectRef  GetSingleObject();

public:
            ScDrawTransferObj( SdrModel* pClipModel, ScDocShell* pContainerShell,   const TransferableObjectDescriptor& rDesc ){DBG_ASSERT(0, "STRIP");}; //STRIP001 ScDrawTransferObj( SdrModel* pClipModel, ScDocShell* pContainerShell,
//STRIP001                              const TransferableObjectDescriptor& rDesc );
    virtual ~ScDrawTransferObj(){DBG_ASSERT(0, "STRIP");}; //STRIP001 virtual ~ScDrawTransferObj();

//STRIP001  virtual void        AddSupportedFormats();
//STRIP001  virtual sal_Bool    GetData( const ::com::sun::star::datatransfer::DataFlavor& rFlavor );
//STRIP001  virtual sal_Bool    WriteObject( SotStorageStreamRef& rxOStm, void* pUserObject, sal_uInt32 nUserObjectId,
//STRIP001                                      const ::com::sun::star::datatransfer::DataFlavor& rFlavor );
//STRIP001  virtual void        ObjectReleased();
//STRIP001  virtual void        DragFinished( sal_Int8 nDropAction );

//STRIP001  SdrModel*           GetModel()  { return pModel; }

//STRIP001  void                SetDrawPersist( const SvEmbeddedObjectRef& rRef );
//STRIP001  void                SetDragSource( ScDrawView* pView );
//STRIP001  void                SetDragSourceObj( SdrObject* pObj, USHORT nTab );
//STRIP001  void                SetDragSourceFlags( USHORT nFlags );
//STRIP001  void                SetDragWasInternal();

//STRIP001  SdrView*            GetDragSourceView()             { return pDragSourceView; }
//STRIP001  USHORT              GetDragSourceFlags() const      { return nDragSourceFlags; }
//STRIP001
//STRIP001     void                SetSourceDocID( sal_uInt32 nVal )
//STRIP001                             { nSourceDocID = nVal; }
//STRIP001     sal_uInt32          GetSourceDocID() const      { return nSourceDocID; }

    static ScDrawTransferObj* GetOwnClipboard( Window* pUIWin );
};

#endif

