/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: so2dll.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 14:27:29 $
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

#ifndef _SO2DLL_HXX
#define _SO2DLL_HXX

#ifndef _PSTM_HXX //autogen
#include <tools/pstm.hxx>
#endif
#ifndef _LINK_HXX //autogen
#include <tools/link.hxx>
#endif
#ifndef _GLOBNAME_HXX //autogen
#include <tools/globname.hxx>
#endif

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

/*************************************************************************
*************************************************************************/
class ImpFactory;
class SotFactory;
class SvObjectList;
class SotFactoryList;
class SvAdviseSinkIndex;
class SvInPlaceClient;
class SvInPlaceClientList;
class SvInPlaceObjectList;
class WorkWindow;
class MDIWindow;
class ImpSO2Clipboard;
class ResMgr;
class SvSoIPCServer;
class SvIPCServerInfo;
class ImplSvEditObjectProtocol;
class Impl_DeathTimer;
class Timer;
class SvContainerEnvironmentList;
class SvInPlaceEnvironment;
class SvVerbList;
struct SvBindingData;

//=========================================================================
struct SO3_DLLPRIVATE ConvertTo_Impl
/*  [Beschreibung]

    In dieser Struktur werden Informationen "uber den Vorg"anger und den
    Nachfolger von Datenformaten und dazugeh"origen CLSId's gepflegt.
    Die Struktur kann nur in einem Array sinnvoll eingesetzt werden.
*/
{
    SvGlobalName    aName;          // CLSID    des Servers
    SvGlobalName    aSvName;        // Starview-Klasse die diese CLSID supported
    long            aFormat;        // Format

    ConvertTo_Impl() {};
    ConvertTo_Impl( const SvGlobalName & a1, long a2 )
        : aName( a1 )
        , aSvName( a1 )
        , aFormat( a2 )
    {}
    ConvertTo_Impl( const SvGlobalName & a1,
                    const SvGlobalName & rSvClass,
                    long a2 )
        : aName( a1 )
        , aSvName( rSvClass )
        , aFormat( a2 )
    {}
};
#define SO3_OFFICE_VERSIONS 5

class SO3_DLLPUBLIC SoDll
{
friend class ImpFactory;
friend class SvFactory;
friend class Impl_DeathTimer;
    BOOL            bInit;
    BOOL            bSelfInit;
    ResMgr*         pResMgr;

public:
    // Factories
    SotFactory *     pSvObjectFactory;
    SotFactory *     pSvStorageStreamFactory;
    SotFactory *     pSvStorageFactory;
    SotFactory *     pSvEmbeddedObjectFactory;
    SotFactory *     pSvEmbeddedClientFactory;
    SotFactory *     pSvInPlaceObjectFactory;
    SotFactory *     pSvPlugInObjectFactory;
    SotFactory *     pSvAppletObjectFactory;
    SotFactory *     pSvInPlaceClientFactory;
    SotFactory *     pSvPersistFactory;
    SotFactory *     pSvPseudoObjectFactory;
    SotFactory *     pSvSimplePersistFactory;
    SotFactory *     pSvObjectContainerFactory;
    SotFactory *     pSvFactory_ImplFactory;
    SotFactory *     pDfltPlugInFactory;
    SotFactory *     pDfltAppletFactory;
    SotFactory *     pSoBindingFactory;

    // Listen
    SvContainerEnvironmentList *pContEnvList;

    // InPlace-Bearbeitung
    SvInPlaceClientList *       pIPActiveClientList;
    SvInPlaceObjectList *       pIPActiveObjectList;
    SvInPlaceEnvironment *      pUIShowIPEnv;
    ImplSvEditObjectProtocol *  pIEOPDflt;

    // Sonstiges
    SvClassManager              aInfoClassMgr;
    SvGlobalName                aSvInterface;

    // PlugIn
    SvVerbList *                pPlugInVerbList;
    ULONG                       nPlugInDocFormat;

    // PlugIn
    SvVerbList *                pAppletVerbList;
    ULONG                       nAppletDocFormat;

    Timer *                     pDeathTimer;
    void *                      pDead;
    SvBindingData*              pBindingData;
    ConvertTo_Impl              (*pConvTable)[SO3_OFFICE_VERSIONS];
    USHORT                      nConvTableEntries;

                            SoDll();
                            ~SoDll();
    ResMgr *                GetResMgr();
    SvIPCServerInfo *       GetIPCServerInfo();

    static SoDll*           GetOrCreate();
    static void             Delete();
};

#endif //_SO2DLL_HXX

