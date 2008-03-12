/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: transprt.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:46:56 $
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

#ifndef _TRANSPRT_HXX
#define _TRANSPRT_HXX "$Revision: 1.3 $"

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

#ifndef _ERRCODE_HXX
#include <tools/errcode.hxx>
#endif

#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif

#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif

#ifndef _BINDING_HXX
#include <bf_so3/binding.hxx>
#endif

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

class DateTime;

namespace binfilter {
class SvBindingTransport;
class SvBindingTransportFactory;
class SvBindingTransportCallback;
class SvBindingTransportContext;

#ifndef COPYCTOR_API
#define COPYCTOR_API(C) C (const C&); C& operator= (const C&)
#endif

/*========================================================================
 *
 * SvBindingTransport interface.
 *
 *======================================================================*/
class SO3_DLLPUBLIC SvBindingTransport
{
    /** Not implemented.
    */
    SO3_DLLPRIVATE COPYCTOR_API(SvBindingTransport);

public:
    SvBindingTransport (void);
    virtual ~SvBindingTransport (void);

    virtual void Start (void) = 0;
    virtual void Abort (void) = 0;

    static  BOOL HasTransport (
        const String &rUrl);

    static SvBindingTransport* CreateTransport (
        const String               &rUrl,
        SvBindingTransportContext  &rCtx,
        SvBindingTransportCallback *pCallback);
};

/*========================================================================
 *
 * SvBindingTransportFactory interface.
 *
 *======================================================================*/
class SO3_DLLPUBLIC SvBindingTransportFactory
{
    /** Not implemented.
    */
    SO3_DLLPRIVATE COPYCTOR_API(SvBindingTransportFactory);

public:
    SvBindingTransportFactory (void);
    virtual ~SvBindingTransportFactory (void);

    virtual BOOL HasTransport (
        const String &rUrl) = 0;

    virtual SvBindingTransport* CreateTransport (
        const String               &rUrl,
        SvBindingTransportContext  &rCtx,
        SvBindingTransportCallback *pCallback) = 0;
};

/*========================================================================
 *
 * SvBindingTransportCallback interface.
 *
 *======================================================================*/
class SO3_DLLPUBLIC SvBindingTransportCallback
{
public:
    virtual void OnStart (void) = 0;

    virtual void OnError (ErrCode eErrCode) = 0;

    virtual void OnMimeAvailable (const String &rMime) = 0;

    virtual void OnExpiresAvailable (const DateTime &rExpires) = 0;

    virtual void OnHeaderAvailable (
        const String &rName, const String &rValue) = 0;

    virtual void OnDataAvailable (
        SvStatusCallbackType eType,
        ULONG nSize, SvLockBytes *pLockBytes) = 0;

    virtual void OnProgress (
        ULONG nNow, ULONG nEnd, SvBindStatus eStatus) = 0;

    virtual void OnRedirect (const String &rUrl) = 0;
};

/*========================================================================
 *
 * SvBindingTransportContext.
 *
 *======================================================================*/
class SO3_DLLPUBLIC SvBindingTransportContext
{
    /** Representation.
    */
    SvBindAction   m_eBindAction;
    SvBindMode     m_eBindMode;
    StreamMode     m_eStrmMode;
    USHORT         m_nPriority;
    String         m_aReferer;
    String         m_aSendMimeType;
    SvLockBytesRef m_xPostLockBytes;

public:
    SvBindingTransportContext (void);
    virtual ~SvBindingTransportContext (void);

    /** BindAction.
    */
    SvBindAction GetBindAction (void) const { return m_eBindAction; }
    void SetBindAction (SvBindAction eAction) { m_eBindAction = eAction; }

    /** BindMode.
    */
    SvBindMode GetBindMode (void) const { return m_eBindMode; }
    void SetBindMode (SvBindMode eMode) { m_eBindMode = eMode; }

    /** StreamMode.
    */
    StreamMode GetStreamMode (void) const { return m_eStrmMode; }
    void SetStreamMode (StreamMode eMode) { m_eStrmMode = eMode; }

    /** Priority.
    */
    USHORT GetPriority (void) const { return m_nPriority; }
    void SetPriority (USHORT nPriority) { m_nPriority = nPriority; }

    /** Referer.
    */
    const String& GetReferer (void) const { return m_aReferer; }
    void SetReferer (const String &rReferer) { m_aReferer = rReferer; }

    /** SendMimeType (actions PUT and POST).
    */
    const String& GetSendMimeType (void) const
    {
        return m_aSendMimeType;
    }
    void SetSendMimeType (const String &rSendMimeType)
    {
        m_aSendMimeType = rSendMimeType;
    }

    /** PostLockBytes (actions PUT and POST).
    */
    SvLockBytes* GetPostLockBytes (void) const
    {
        return m_xPostLockBytes;
    }
    void SetPostLockBytes (SvLockBytesRef &rxPostLockBytes)
    {
        m_xPostLockBytes = rxPostLockBytes;
    }
};

/*========================================================================
 *
 * SvLockBytesFactory interface.
 *
 *======================================================================*/
class SO3_DLLPUBLIC SvLockBytesFactory
{
    /** Representation.
    */
    String m_aWildcard;

    /** Not implemented.
    */
    SO3_DLLPRIVATE COPYCTOR_API(SvLockBytesFactory);

public:
    SvLockBytesFactory (const String & rWildcard);
    virtual ~SvLockBytesFactory (void);

    virtual SvLockBytesRef CreateLockBytes (
        const String &rUrl, String &rMime) = 0;

    static SvLockBytesFactory* GetFactory (const String &rUrl);

    const String& GetWildcard (void) const { return m_aWildcard; }
};

/*========================================================================
 *
 * SfxSimpleLockBytesFactory interface.
 *
 *======================================================================*/
class SO3_DLLPUBLIC SfxSimpleLockBytesFactory :
    public SvLockBytesFactory, public SvRefBase
{
    /** Representation.
    */
    SvLockBytesRef m_xLockBytes;
    String         m_aMime;

    static USHORT  m_nCounter;

    /** Not implemented.
    */
    SO3_DLLPRIVATE COPYCTOR_API(SfxSimpleLockBytesFactory);

public:
    /** Destruction (protected) (SvRefBase).
    */
    virtual ~SfxSimpleLockBytesFactory (void);

public:
    SfxSimpleLockBytesFactory (
        SvLockBytes  *pLockBytes,
        const String &rUrl,
        const String &rMime);

    SfxSimpleLockBytesFactory (
        SvLockBytes  *pLockBytes,
        const String &rMime);

    static String TempURL (const String &rExtension);

    virtual SvLockBytesRef CreateLockBytes (
        const String &rUrl, String &rMime);
};

SV_DECL_IMPL_REF(SfxSimpleLockBytesFactory);

/*========================================================================
 *
 * SvLockBytesTransportFactory interface.
 *
 *======================================================================*/
class SO3_DLLPUBLIC SvLockBytesTransportFactory : public SvBindingTransportFactory
{
    /** Not implemented.
    */
    SO3_DLLPRIVATE COPYCTOR_API(SvLockBytesTransportFactory);

public:
    SvLockBytesTransportFactory (void);
    virtual ~SvLockBytesTransportFactory (void);

    virtual BOOL HasTransport (
        const String &rUrl);

    virtual SvBindingTransport* CreateTransport (
        const String               &rUrl,
        SvBindingTransportContext  &rCtx,
        SvBindingTransportCallback *pCB);
};

/*========================================================================
 *
 * CntTransportFactory interface.
 *
 *======================================================================*/
class SO3_DLLPUBLIC CntTransportFactory : public SvBindingTransportFactory
{
    /** Not implemented.
    */
    SO3_DLLPRIVATE COPYCTOR_API(CntTransportFactory);

public:
    CntTransportFactory (void);
    virtual ~CntTransportFactory (void);

    virtual BOOL HasTransport (
        const String &rUrl);

    virtual SvBindingTransport* CreateTransport (
        const String               &rUrl,
        SvBindingTransportContext  &rCtx,
        SvBindingTransportCallback *pCB);
};

/*========================================================================
 *
 * The End.
 *
 *======================================================================*/

}

#endif /* _TRANSPRT_HXX */

