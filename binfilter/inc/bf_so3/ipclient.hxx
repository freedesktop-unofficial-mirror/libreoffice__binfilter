/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ipclient.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:42:42 $
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

#ifndef _IPCLIENT_HXX
#define _IPCLIENT_HXX

#include <bf_so3/client.hxx>

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

/*************************************************************************
*************************************************************************/
class  MenuBar;
class  Accelerator;
struct IOleInPlaceSite;
struct IOleInPlaceFrame;
struct IOleInPlaceUIWindow;

namespace binfilter {
class  SvInPlaceEnvironment;
class SvContainerEnvironment;
class  SvInPlaceClientList;
class  SvInPlaceClient;
class  SvInPlaceClient;
class  SvInPlaceObject;
class  ImpInPlaceSite;
class  ImpInPlaceFrame;
class  ImpInPlaceUIWin;

    //=========================================================================
class SO3_DLLPUBLIC SvInPlaceClient : public SvEmbeddedClient
{
friend class ImpInPlaceSite;
friend class ImpInPlaceFrame;
friend class ImpInPlaceUIWin;
friend class SvInPlaceObject;
friend class SvEditObjectProtocol;
friend class ImplSvEditObjectProtocol;
friend class SvContainerEnvironment;

    IOleInPlaceSite *       pObjI;

    SO3_DLLPRIVATE  BOOL                CanInPlaceActivate() const;
protected:
                             ~SvInPlaceClient();

    virtual void        Opened( BOOL bOpen );
    virtual void        InPlaceActivate( BOOL bActivate );
    virtual void        UIActivate( BOOL bActivate );

    virtual void        MakeViewData();
public:
                        SvInPlaceClient();
                        SvInPlaceClient( WorkWindow * pTopWin,
                                         WorkWindow * pDocWin,
                                         Window * pEditWin );
                        SO2_DECL_STANDARD_CLASS_DLL(SvInPlaceClient,SOAPP)

    IOleInPlaceSite *           GetInPlaceSite() const;

    static SvInPlaceClientList & GetIPActiveClientList();

    SvContainerEnvironment *    GetEnv();
    virtual void                MakeVisible();

    BOOL                        IsInPlaceActive() const
                                { return aProt.IsInPlaceActive(); }
    SvInPlaceObject *           GetIPObj() const
                                { return aProt.GetIPObj(); }

    virtual void                DeactivateAndUndo();
    virtual void                DiscardUndoState();
};
#ifndef SO2_DECL_SVINPLACECLIENT_DEFINED
#define SO2_DECL_SVINPLACECLIENT_DEFINED
SO2_DECL_REF(SvInPlaceClient)
#endif
SO2_IMPL_REF(SvInPlaceClient)

SV_DECL_REF_LIST(SvInPlaceClient,SvInPlaceClient*)
SV_IMPL_REF_LIST(SvInPlaceClient,SvInPlaceClient*)

}

#endif // _IPCLIENT_HXX
