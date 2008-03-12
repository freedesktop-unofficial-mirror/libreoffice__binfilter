/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: lnkbase.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:44:12 $
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
#ifndef _LNKBASE_HXX
#define _LNKBASE_HXX

#ifndef _SOT_EXCHANGE_HXX //autogen
#include <sot/exchange.hxx>
#endif
#ifndef _TOOLS_REF_HXX
#include <tools/ref.hxx>
#endif
#ifndef _LINKSOURCE_HXX
#include <bf_so3/linksrc.hxx>
#endif

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

namespace com { namespace sun { namespace star { namespace uno
{
    class Any;
    //class Type;
}}}}

namespace binfilter
{

struct ImplBaseLinkData;
class SvLinkManager;
class SvLinkSource;

#ifndef OBJECT_DDE_EXTERN
#define OBJECT_INTERN       0x00
//#define   OBJECT_SO_EXTERN    0x01
#define OBJECT_DDE_EXTERN   0x02
#endif

#define OBJECT_CLIENT_SO            0x80 // ein Link
#define OBJECT_CLIENT_DDE           0x81
//#define   OBJECT_CLIENT_OLE           0x82 // ein Ole-Link
//#define   OBJECT_CLIENT_OLE_CACHE     0x83 // ein Ole-Link mit SvEmbeddedObject
#define OBJECT_CLIENT_FILE          0x90
#define OBJECT_CLIENT_GRF           0x91

enum so3link {
    // Ole2 compatibel und persistent
    LINKUPDATE_ALWAYS = 1,
    LINKUPDATE_ONCALL = 3,

    LINKUPDATE_END      // dummy!
};

class SO3_DLLPUBLIC SvBaseLink : public SvRefBase
{
    friend class SvLinkManager;
    friend class SvLinkSource;
private:
    SvLinkSourceRef         xObj;
    String                  aLinkName;
    SvLinkManager*          pLinkMgr;
    USHORT                  nObjType;
    BOOL                    bVisible : 1;
    BOOL                    bSynchron : 1;
    BOOL                    bUseCache : 1;      // fuer GrafikLinks!

protected:
    void            SetObjType( USHORT );

                    // setzen des LinkSourceName ohne aktion
    SO3_DLLPRIVATE void         SetName( const String & rLn );
                    // LinkSourceName der im SvLinkBase steht
    SO3_DLLPRIVATE String           GetName() const;

    ImplBaseLinkData* pImplData;

    SO3_DLLPRIVATE              SvBaseLink();
                    SvBaseLink( USHORT nLinkType, ULONG nContentType = FORMAT_STRING );
    virtual         ~SvBaseLink();

    void            _GetRealObject( BOOL bConnect = TRUE );

    SO3_DLLPRIVATE SvLinkSource*    GetRealObject()
                    {
                        if( !xObj.Is() )
                            _GetRealObject();
                        return xObj;
                    }

public:
                    TYPEINFO();
                    // ask JP
    virtual void    Closed();
                    SvBaseLink( const String& rNm, USHORT nObjectType,
                                 SvLinkSource* );

    USHORT          GetObjType() const { return nObjType; }

    void            SetObj( SvLinkSource * pObj );
    SvLinkSource*   GetObj() const  { return xObj; }

    void            SetLinkSourceName( const String & rName );
    String          GetLinkSourceName() const;

    virtual void    DataChanged( const String & rMimeType,
                                const ::com::sun::star::uno::Any & rValue );

    void            SetUpdateMode( USHORT );
    USHORT          GetUpdateMode() const;
    ULONG           GetContentType() const;
    BOOL            SetContentType( ULONG nType );

    SvLinkManager*  GetLinkManager()            { return pLinkMgr; }
    const SvLinkManager* GetLinkManager() const { return pLinkMgr; }

    BOOL            Update();
    void            Disconnect();

    virtual BOOL    Edit( Window* );

        // soll der Link im Dialog angezeigt werden ? (Links im Link im ...)
    BOOL            IsVisible() const           { return bVisible; }
    void            SetVisible( BOOL bFlag )    { bVisible = bFlag; }
        // soll der Link synchron oder asynchron geladen werden?
    BOOL            IsSynchron() const          { return bSynchron; }
    void            SetSynchron( BOOL bFlag )   { bSynchron = bFlag; }

    BOOL            IsUseCache() const          { return bUseCache; }
    void            SetUseCache( BOOL bFlag )   { bUseCache = bFlag; }
};

SV_DECL_IMPL_REF(SvBaseLink);

}

#endif
