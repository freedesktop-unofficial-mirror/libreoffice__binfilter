/*************************************************************************
 *
 *  $RCSfile: request.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:29 $
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
#ifndef _SFXREQUEST_HXX
#define _SFXREQUEST_HXX

#ifndef _SFXITEMSET_HXX //autogen
#include <svtools/itemset.hxx>
#endif
#ifndef _SFXHINT_HXX //autogen
#include <svtools/hint.hxx>
#endif

#ifndef _COM_SUN_STAR_FRAME_XDISPATCHRECORDER_HPP_
#include <com/sun/star/frame/XDispatchRecorder.hpp>
#endif

class SfxMacro;
class SfxPoolItem;
class SfxAllItemSet;
class SfxItemSet;
class SfxItemPool;
class SfxShell;
class SfxSlot;
class SfxMacroStatement;
class SfxArguments;
class String;
class SfxViewFrame;
struct SfxRequest_Impl;

//==================================================================

class SfxRequest: public SfxHint
{
friend struct SfxRequest_Impl;

    USHORT              nSlot;
    SfxAllItemSet*      pArgs;
    SfxRequest_Impl*    pImp;

    //---------------------------------------------------------------------
#if _SOLAR__PRIVATE
public:
    void                Record_Impl( SfxShell &rSh, const SfxSlot &rSlot,
                                     com::sun::star::uno::Reference< com::sun::star::frame::XDispatchRecorder > xRecorder,
                                     SfxViewFrame* );
private:
    void                Done_Impl( const SfxItemSet *pSet );

#endif
    //---------------------------------------------------------------------

public:
                        SfxRequest( SfxViewFrame*, USHORT nSlotId );
                        SfxRequest( USHORT nSlot, USHORT nCallMode, SfxItemPool &rPool );
                        SfxRequest( USHORT nSlot, USHORT nCallMode, const SfxAllItemSet& rSfxArgs );
                        SfxRequest( const SfxRequest& rOrig );
                        ~SfxRequest();

    USHORT              GetSlot() const { return nSlot; }
    void                SetSlot(USHORT nNewSlot) { nSlot = nNewSlot; }

    USHORT              GetModifier() const;
    void                SetModifier( USHORT nModi );
    void                SetInternalArgs_Impl( const SfxAllItemSet& rArgs );
    const SfxItemSet*   GetInternalArgs_Impl() const;
    const SfxItemSet*   GetArgs() const { return pArgs; }
    void                SetArgs( const SfxAllItemSet& rArgs );
    void                AppendItem(const SfxPoolItem &);
    void                RemoveItem( USHORT nSlotId );

    static const SfxPoolItem* GetItem( const SfxItemSet*, USHORT nSlotId,
                                       FASTBOOL bDeep = FALSE,
                                       TypeId aType = 0 );
    const SfxPoolItem*  GetArg( USHORT nSlotId, FASTBOOL bDeep = FALSE, TypeId aType = 0 ) const;
    void                ReleaseArgs()
                        { DELETEZ(pArgs); }

    void                SetReturnValue(const SfxPoolItem &);
    const SfxPoolItem*  GetReturnValue() const;

    static SfxMacro*    GetRecordingMacro();
//STRIP001     static com::sun::star::uno::Reference< com::sun::star::frame::XDispatchRecorder > GetMacroRecorder( SfxViewFrame* pFrame=NULL );
    static BOOL         HasMacroRecorder( SfxViewFrame* pFrame=NULL );
    USHORT              GetCallMode() const;
//STRIP001  FASTBOOL            IsRecording() const;
    void                AllowRecording( BOOL );
    BOOL                AllowsRecording() const;
    BOOL                IsAPI() const;
    BOOL                IsSynchronCall() const;
    void                SetSynchronCall( BOOL bSynchron );
    void                SetTarget( const String &rTarget );

    BOOL                IsDone() const;
    void                Done( BOOL bRemove = FALSE );

    void                Ignore();
    void                Cancel();
    BOOL                IsCancelled() const;
    void                Done(const SfxItemSet &, FASTBOOL bKeep = TRUE );

private:
    const SfxRequest&   operator=(const SfxRequest &); // n.i.!!
};

//------------------------------------------------------------------------

#define SFX_REQUEST_ARG(rReq, pItem, ItemType, nSlotId, bDeep) \
        const ItemType *pItem = (const ItemType*) \
                rReq.GetArg( nSlotId, bDeep, TYPE(ItemType) )
#define SFX_ITEMSET_ARG(pArgs, pItem, ItemType, nSlotId, bDeep) \
    const ItemType *pItem = (const ItemType*) \
        SfxRequest::GetItem( pArgs, nSlotId, bDeep, TYPE(ItemType) )

#endif
