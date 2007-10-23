/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: transbnd.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 14:28:53 $
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

#ifndef _TRANSBND_HXX
#define _TRANSBND_HXX "$Revision: 1.2 $"

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

#ifndef _DATETIME_HXX
#include <tools/datetime.hxx>
#endif

#ifndef _ERRCODE_HXX
#include <tools/errcode.hxx>
#endif

#ifndef _LINK_HXX
#include <tools/link.hxx>
#endif

#ifndef _REF_HXX
#include <tools/ref.hxx>
#endif

#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif

#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif

#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif

#ifndef _BINDING_HXX
#include <bf_so3/binding.hxx>
#endif

#ifndef _TRANSPRT_HXX
#include <bf_so3/transprt.hxx>
#endif

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

class SfxCancelManager;
class SfxCancellable;

class SvBindStatusCallback;
SV_DECL_REF(SvBindStatusCallback)

class SvKeyValueIterator;
SV_DECL_REF(SvKeyValueIterator)

#ifndef COPYCTOR_API
#define COPYCTOR_API(C) C (const C&); C& operator= (const C&)
#endif

/*========================================================================
 *
 * SvBinding interface.
 *
 *======================================================================*/
class SO3_DLLPUBLIC SvBinding : public SvBindingTransportCallback, public SvRefBase
{
    /** Representation.
    */
    INetURLObject              m_aUrlObj;
    SvBindStatusCallbackRef    m_xCallback;

    SvBindingTransportContext  m_aBindCtx;
    SvBindingTransport        *m_pTransport;
    SfxCancellable            *m_pCancelable;

    ErrCode                    m_eErrCode;
    String                     m_aMime;
    DateTime                   m_aExpires;
    SvKeyValueIteratorRef      m_xHeadIter;
    SvLockBytesRef             m_xLockBytes;

    BOOL                       m_bStarted   : 1;
    BOOL                       m_bComplete  : 1;
    BOOL                       m_bErrorDoc  : 1;
    BOOL                       m_bMimeAvail : 1;

    /** StartTransport.
    */
    SO3_DLLPRIVATE void StartTransport (void);

    /** SvBindingTransportCallback implementation.
    */
    SO3_DLLPRIVATE virtual void OnStart (void);

    SO3_DLLPRIVATE virtual void OnError (
        ErrCode eErrCode);

    SO3_DLLPRIVATE virtual void OnMimeAvailable (
        const String &rMime);

    SO3_DLLPRIVATE virtual void OnExpiresAvailable (
        const DateTime &rExpires);

    SO3_DLLPRIVATE virtual void OnHeaderAvailable (
        const String &rName, const String &rValue);

    SO3_DLLPRIVATE virtual void OnDataAvailable (
        SvStatusCallbackType  eType,
        ULONG                 nSize,
        SvLockBytes          *pLockBytes);

    SO3_DLLPRIVATE virtual void OnProgress (
        ULONG nNow, ULONG nEnd, SvBindStatus eStatus);

    SO3_DLLPRIVATE virtual void OnRedirect (
        const String &rUrl);

    /** Not implemented.
    */
    SO3_DLLPRIVATE COPYCTOR_API(SvBinding);

protected:
    /** Destruction (SvRefBase).
    */
    SO3_DLLPRIVATE virtual ~SvBinding (void);

public:
    /** Construction.
    */
    SvBinding (
        const String         &rUrl,
        SvBindMode            eBindMode,
        StreamMode            eStrmMode,
        SvBindStatusCallback *pCallback);

    /** Callback.
    */
    SvBindStatusCallback* GetCallback (void) const
    {
        return m_xCallback;
    }

    /** BindContext.
    */
    SvBindingTransportContext & GetBindContext (void)
    {
        return m_aBindCtx;
    }

    /** Up/Download information.
    */
    ErrCode GetErrorCode  (void) const { return m_eErrCode; }
    BOOL    IsComplete    (void) const { return m_bComplete; }
    BOOL    IsErrorOutput (void) const { return m_bErrorDoc; }

    /** Up/Download manipulation.
    */
    void    SetCancelManager (SfxCancelManager *pMgr);

    void    Abort   (void);
    void    Suspend (void);
    void    Resume  (void);

    /** Initiate Up/Download.
    */
    ErrCode GetMimeType (String &rMime);

    ErrCode GetStream (SvStream *&rpStrm);
    ErrCode PutStream (SvStream *pStrm);

    ErrCode GetLockBytes (SvLockBytesRef &rxLockBytes);
    ErrCode PutLockBytes (SvLockBytesRef &rxLockBytes);

    /** RedirectedURL.
    */
    String GetRedirectedURL (void) const
    {
        return m_aUrlObj.GetMainURL(INetURLObject::DECODE_TO_IURI);
    }

    /** ExpireDateTime.
    */
    const DateTime& GetExpireDateTime (void) const
    {
        return m_aExpires;
    }

    /** Cookie (HTTP).
    */
    String  GetCookie (void) const;
    void    SetCookie (const String &rCookieField);

    /** Headers (HTTP).
    */
    SvKeyValueIteratorRef GetHeaders (void) const;
    void SetHeaders (SvKeyValueIteratorRef &rxHeadIter);

    /** Priority.
    */
    USHORT GetPriority (void) const
    {
        return m_aBindCtx.GetPriority();
    }
    void SetPriority (USHORT nPriority)
    {
        m_aBindCtx.SetPriority (nPriority);
    }

    /** Referer.
    */
    const String& GetReferer (void) const
    {
        return m_aBindCtx.GetReferer();
    }
    void SetReferer (const String &rReferer)
    {
        m_aBindCtx.SetReferer (rReferer);
    }

    /** SendMimeType.
    */
    const String& GetSendMimeType (void) const
    {
        return m_aBindCtx.GetSendMimeType();
    }
    void SetSendMimeType (const String &rMime)
    {
        m_aBindCtx.SetSendMimeType (rMime);
    }

    /** Proxy (FTP).
     */
    static BOOL ShouldUseFtpProxy (const String &rUrl);
};

SV_DECL_IMPL_REF(SvBinding);

/*========================================================================
 *
 * SvBindStatusCallback interface.
 *
 *======================================================================*/
struct SO3_DLLPRIVATE SvProgressArg
{
    ULONG         nProgress;
    ULONG         nMax;
    SvBindStatus  eStatus;
    const String &rStatus;
    float         nRate;

    SvProgressArg (const String& rStatusText) : rStatus (rStatusText) {}
};

class SO3_DLLPUBLIC SvBindStatusCallback : public SvRefBase
{
    /** Representation.
    */
    static Link m_aProgressCallback;

    Link  m_aDoneLink;
    Link  m_aDataLink;
    Link  m_aReloadLink;
    Link  m_aPartLink;

    ULONG m_nStartTicks;

    BOOL  m_bInAvailableCall : 1;
    BOOL  m_bDonePending     : 1;
    BOOL  m_bDataPending     : 1;
    BOOL  m_bReloadPending   : 1;
    BOOL  m_bPartPending     : 1;

public:
    SvBindStatusCallback (void);
    virtual ~SvBindStatusCallback (void);

    static void SetProgressCallback (const Link &rLink);
    void InitStartTime (void);

    const Link& GetDoneLink (void) const { return m_aDoneLink; }
    void SetDoneLink (const Link &rLink) { m_aDoneLink = rLink; }

    const Link& GetDataAvailableLink (void) const { return m_aDataLink; }
    void SetDataAvailableLink (const Link &rLink) { m_aDataLink = rLink; }

    const Link& GetReloadAvailableLink (void) const { return m_aReloadLink; }
    void SetReloadAvailableLink (const Link &rLink) { m_aReloadLink = rLink; }

    const Link& GetNewPartAvailableLink (void) const { return m_aPartLink; }
    void SetNewPartAvailableLink (const Link &rLink) { m_aPartLink = rLink; }

    virtual void OnDataAvailable (
        SvStatusCallbackType eType, ULONG, SvLockBytes&);

    virtual void OnDataAvailable (
        SvStatusCallbackType eType, ULONG, SvStream&);

    virtual void OnProgress (
        ULONG nProgress, ULONG nMax,
        SvBindStatus eStatus, const String &rStatusText);

    virtual void OnStopBinding (
        ErrCode eErrCode, const String &rStatusText);
};

SV_IMPL_REF(SvBindStatusCallback);

/*========================================================================
 *
 * SvKeyValue.
 *
 *======================================================================*/
class SO3_DLLPUBLIC SvKeyValue
{
    /** Representation.
    */
    String m_aKey;
    String m_aValue;

public:
    /** Construction.
    */
    SvKeyValue (void)
    {}

    SvKeyValue (const String &rKey, const String &rValue)
        : m_aKey (rKey), m_aValue (rValue)
    {}

    SvKeyValue (const SvKeyValue &rOther)
        : m_aKey (rOther.m_aKey), m_aValue (rOther.m_aValue)
    {}

    /** Assignment.
    */
    SO3_DLLPRIVATE SvKeyValue& operator= (SvKeyValue &rOther)
    {
        m_aKey   = rOther.m_aKey;
        m_aValue = rOther.m_aValue;
        return *this;
    }

    /** Operation.
    */
    const String& GetKey   (void) const { return m_aKey; }
    const String& GetValue (void) const { return m_aValue; }

    void SetKey   (const String &rKey  ) { m_aKey = rKey; }
    void SetValue (const String &rValue) { m_aValue = rValue; }
};

/*========================================================================
 *
 * SvKeyValueIterator.
 *
 *======================================================================*/
class SvKeyValueList_Impl;
class SO3_DLLPUBLIC SvKeyValueIterator : public SvRefBase
{
    /** Representation.
    */
    SvKeyValueList_Impl* m_pList;
    USHORT               m_nPos;

    /** Not implemented.
    */
    SO3_DLLPRIVATE COPYCTOR_API(SvKeyValueIterator);

public:
    /** Construction/Destruction.
    */
    SvKeyValueIterator (void);
    virtual ~SvKeyValueIterator (void);

    /** Operation.
    */
    virtual BOOL GetFirst (SvKeyValue &rKeyVal);
    virtual BOOL GetNext  (SvKeyValue &rKeyVal);
    virtual void Append   (const SvKeyValue &rKeyVal);
};

SV_IMPL_REF(SvKeyValueIterator);

/*========================================================================
 *
 * SvRemoteStream.
 *
 *======================================================================*/
class SO3_DLLPUBLIC SvRemoteStream : public SvStream
{
    SvBindingRef m_xBinding;
    String       m_aUrl;
    StreamMode   m_eMode;

public:
    SvRemoteStream (const String &rUrl, StreamMode eMode);
    virtual ~SvRemoteStream (void);

    void SetDataAvailableLink (const Link &rLink);
    void SetDoneLink (const Link &rLink);

    ErrCode Commit (void);
};

/*========================================================================
 *
 * The End.
 *
 *======================================================================*/

#endif /* _TRANSBND_HXX */

