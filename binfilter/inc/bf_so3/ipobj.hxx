/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ipobj.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:43:14 $
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

#ifndef _IPOBJ_HXX
#define _IPOBJ_HXX

#include <bf_so3/embobj.hxx>
#include <bf_so3/ipobj.hxx>

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

/*************************************************************************/
/*************************************************************************/
class  MenuBar;
class  Window;
class  KeyEvent;
class  Palette;

namespace binfilter {
class  SvContainerEnvironment;
class  ImpInPlaceObject;
class  ImpInPlaceSite;
class  ImpOleInPlaceActiveObject;
struct IOleInPlaceObject;
struct IOleInPlaceActiveObject;
class SvInPlaceEnvironment;
class  SvInPlaceObjectList;
class  SvInPlaceClipWindow;
class  SvInPlaceWindow;
/*************************************************************************
*************************************************************************/
class SvInPlaceObject;
#ifndef SO2_DECL_SVINPLACEOBJECT_DEFINED
#define SO2_DECL_SVINPLACEOBJECT_DEFINED
SO2_DECL_REF(SvInPlaceObject)
#endif

class SO3_DLLPUBLIC SvInPlaceObject : public SvEmbeddedObject
{
friend class ImpInPlaceObject;
friend class ImpInPlaceSite;
friend class SvInPlaceClient;
friend class ImpOleInPlaceActiveObject;
friend class SvEditObjectProtocol;
friend class ImplSvEditObjectProtocol;
friend class SvInPlaceEnvironment;

private:
    IOleInPlaceObject *         pObjI;
    IOleInPlaceActiveObject *   pActiveObj;
    SvInPlaceEnvironment *      pIPEnv;
    BOOL                        bIsUndoable:1,
                                bDeleteIPEnv:1;

    SO3_DLLPRIVATE BOOL                         DoMergePalette();
protected:
                     ~SvInPlaceObject();

    virtual void    TopWinActivate( BOOL bActivate );
    virtual void    DocWinActivate( BOOL bActivate );

    SO3_DLLPRIVATE void         SetIPEnv( SvInPlaceEnvironment * pFrm );

    virtual ErrCode Verb( long nVerbPos, SvEmbeddedClient * pCallerClient,
                        Window * pWin, const Rectangle * pWorkAreaPixel );
    virtual void    Open( BOOL bOpen );
    virtual void    InPlaceActivate( BOOL bActivate );
    virtual void    UIActivate( BOOL bActivate );

    SO3_DLLPRIVATE void         SetUndoable( BOOL bUndoable )
                    { bIsUndoable = bUndoable; }
    // View
    virtual BOOL    MergePalette( const Palette & rContainerPal );
public:
                    SvInPlaceObject();
                    SO2_DECL_STANDARD_CLASS_DLL(SvInPlaceObject,SOAPP)
    IOleInPlaceObject *         GetInPlaceObject() const;
    IOleInPlaceActiveObject *   GetInPlaceActiveObject() const;
    BOOL                        SetInPlaceActiveObject( IOleInPlaceActiveObject * );

    SvInPlaceEnvironment* GetIPEnv() const { return pIPEnv; }
    SvInPlaceClient * GetIPClient() const
                    { return aProt.GetIPClient(); }
    static  SvInPlaceObjectList & GetIPActiveObjectList();

    // Robuste Protokollsteuerung
    ErrCode         DoInPlaceActivate( BOOL bActivate );
    ErrCode         DoUIActivate( BOOL bActivate );

    virtual void    SetVisArea( const Rectangle & rVisArea );
    BOOL            IsUndoable() const { return bIsUndoable; }
    virtual BOOL    ReactivateAndUndo();
    static SvInPlaceObjectRef CreateObject( const SvGlobalName & rName );
};

DECLARE_LIST(SvInPlaceObjectList,SvInPlaceObject*)
SO2_IMPL_REF(SvInPlaceObject)

//=========================================================================
class SO3_DLLPUBLIC SvDeathObject : public SvInPlaceObject
/*  [Beschreibung]

    Wenn das Laden eine Ole-Objektes fehlschl"agt, kann dieses Objekt
    teilweise als ersatzt dienen.

    [Probleme]

    Nicht an allen Methoden des Objektes erkennt der Aufrufer,
    dass es sich um eine Ersatzobjekt handelt.
*/
{
protected:
    SO3_DLLPRIVATE virtual ErrCode Verb( long, SvEmbeddedClient * pCallerClient,
                        Window * pWin, const Rectangle * pWorkRectPixel );
    SO3_DLLPRIVATE virtual void    Draw( OutputDevice *,
                          const JobSetup & rSetup,
                          USHORT nAspect = ASPECT_CONTENT );
public:
                    SvDeathObject( const Rectangle & rVisArea );
};

}

#endif // _IPOBJ_HXX
