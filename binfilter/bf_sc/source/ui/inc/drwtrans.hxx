/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: drwtrans.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 13:31:52 $
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

#ifndef SC_DRWTRANS_HXX
#define SC_DRWTRANS_HXX

#ifndef _TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif

#ifndef _IPOBJ_HXX
#include <bf_so3/ipobj.hxx>
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
namespace binfilter {


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



public:
            ScDrawTransferObj( SdrModel* pClipModel, ScDocShell* pContainerShell,   const TransferableObjectDescriptor& rDesc ){DBG_BF_ASSERT(0, "STRIP");}; //STRIP001 ScDrawTransferObj( SdrModel* pClipModel, ScDocShell* pContainerShell,
    virtual ~ScDrawTransferObj(){DBG_BF_ASSERT(0, "STRIP");}; //STRIP001 virtual ~ScDrawTransferObj();





    static ScDrawTransferObj* GetOwnClipboard( Window* pUIWin );
};

} //namespace binfilter
#endif

