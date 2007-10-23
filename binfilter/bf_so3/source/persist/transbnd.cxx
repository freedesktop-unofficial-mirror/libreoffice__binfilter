/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: transbnd.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 13:53:30 $
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

#define _TRANSBND_CXX "$Revision: 1.2 $"

#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif

#ifndef _COM_SUN_STAR_UCB_XCONTENT_HPP_
#include <com/sun/star/ucb/XContent.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XCOMMANDPROCESSOR_HPP_
#include <com/sun/star/ucb/XCommandProcessor.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif

#ifndef _RTL_USTRING_
#include <rtl/ustring.h>
#endif

#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
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

#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif

#ifndef _SFXCANCEL_HXX
#include <svtools/cancel.hxx>
#endif
#ifndef _INETHIST_HXX
#include <svtools/inethist.hxx>
#endif
#ifndef _SVARRAY_HXX
#include <svtools/svarray.hxx>
#endif

#ifndef _BINDING_HXX
#include <bf_so3/binding.hxx>
#endif
#ifndef _BINDDATA_HXX
#include <binddata.hxx>
#endif
#ifndef _TRANSBND_HXX
#include <bf_so3/transbnd.hxx>
#endif
#ifndef _TRANSPRT_HXX
#include <bf_so3/transprt.hxx>
#endif
#ifndef _TRANSUNO_HXX
#include <transuno.hxx>
#endif
#ifndef _SO2DEFS_HXX
#include <bf_so3/so2defs.hxx>
#endif

#include <algorithm>

using namespace com::sun::star::sdbc;
using namespace com::sun::star::beans;
using namespace com::sun::star::ucb;
using namespace com::sun::star::uno;
using namespace com::sun::star::container;

/*========================================================================
 *
 * SvBindingCancelable_Impl.
 *
 *======================================================================*/
class SvBindingCancelable_Impl : public SfxCancellable
{
    SvBinding &m_rBinding;

public:
    SvBindingCancelable_Impl (
        SfxCancelManager *pMgr, SvBinding &rBinding);

    virtual void Cancel (void);
};

SvBindingCancelable_Impl::SvBindingCancelable_Impl (
    SfxCancelManager *pMgr, SvBinding &rBinding)
    : SfxCancellable (pMgr, String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "dummy") ) ),
      m_rBinding     (rBinding)
{
}

/*
 * Cancel.
 */
void SvBindingCancelable_Impl::Cancel (void)
{
    m_rBinding.Abort();
}

class SvBindingCookieRequest_Impl
{
    /** Representation.
    */
    Reference<XContent> m_xContent;

public:
    SvBindingCookieRequest_Impl (const String &rUrl);
    virtual ~SvBindingCookieRequest_Impl (void);

    String GetCookie (void);
    void   SetCookie (const String &rCookieField);
};

/*
 * SvBindingCookieRequest_Impl.
 */
SvBindingCookieRequest_Impl::SvBindingCookieRequest_Impl (const String &rUrl)
    : m_xContent (NULL)
{
    if (BAPP()->HasHttpCache())
    {
        String aDocUrl (String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "private:httpcache#" ) ));
        aDocUrl += rUrl;

        m_xContent = SvBindingTransport_Impl::createContent (aDocUrl);
    }
}

/*
 * ~SvBindingCookieRequest_Impl.
 */
SvBindingCookieRequest_Impl::~SvBindingCookieRequest_Impl (void)
{
}

/*
 * GetCookie.
 */
String SvBindingCookieRequest_Impl::GetCookie (void)
{
    String aCookie;

    Reference<XCommandProcessor> xProcessor (m_xContent, UNO_QUERY);
    if (xProcessor.is())
    {
        rtl::OUString aName (String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "Cookie" ) ) );
        Sequence<Property> aProps(1);

        aProps[0].Name = aName;
        aProps[0].Handle = -1;

        Any aAny = SvBindingTransport_Impl::getProperties (xProcessor, aProps);
        Reference< XRow > xValues;
        if ( aAny >>= xValues )
        {
            Any aValue = xValues->getObject( 1, Reference< XNameAccess>() );
            rtl::OUString aResult;
            if ( aValue >>= aResult )
                aCookie = aResult;
        }
    }
    return aCookie;
}

/*
 * SetCookie.
 */
void SvBindingCookieRequest_Impl::SetCookie (const String &rCookieField)
{
    Reference<XCommandProcessor> xProcessor (m_xContent, UNO_QUERY);
    if (xProcessor.is())
    {
        Sequence<PropertyValue> aProps(1);

        aProps[0].Name = String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "Cookie" ) );
        aProps[0].Handle = -1;
        aProps[0].Value <<= rtl::OUString( rCookieField );

        SvBindingTransport_Impl::setProperties (xProcessor, aProps);
    }
}

/*========================================================================
 *
 * SvBinding implementation.
 *
 *======================================================================*/
/*
 * SvBinding.
 */
SvBinding::SvBinding (
    const String         &rUrl,
    SvBindMode            eBindMode,
    StreamMode            eStrmMode,
    SvBindStatusCallback *pCallback)
    : m_aUrlObj     (rUrl),
      m_xCallback   (pCallback),
      m_pTransport  (NULL),
      m_pCancelable (NULL),
      m_eErrCode    (ERRCODE_NONE),
      m_aExpires    (0, 0),
      m_xLockBytes  (NULL),
      m_bStarted    (FALSE),
      m_bComplete   (FALSE),
      m_bErrorDoc   (FALSE),
      m_bMimeAvail  (FALSE)
{
    m_aBindCtx.SetBindMode   (eBindMode);
    m_aBindCtx.SetStreamMode (eStrmMode);
}

/*
 * ~SvBinding.
 */
SvBinding::~SvBinding (void)
{
    delete m_pTransport;
    delete m_pCancelable;
}

/*
 * Start.
 */
void SvBinding::StartTransport (void)
{
    if (!m_bStarted)
    {
        // Cleanup current transport and mark started.
        DELETEZ (m_pTransport);
        m_bStarted = TRUE;

        // Create transport.
        m_pTransport = SvBindingTransport::CreateTransport (
            m_aUrlObj.GetMainURL( INetURLObject::DECODE_TO_IURI ), m_aBindCtx, this);
        if (m_pTransport)
            m_pTransport->Start();
        else
            OnError (ERRCODE_IO_NOTSUPPORTED);
    }
}

/*
 * SetCancelManager.
 */
void SvBinding::SetCancelManager (SfxCancelManager *pMgr)
{
    DELETEZ (m_pCancelable);
    if (pMgr)
        m_pCancelable = new SvBindingCancelable_Impl (pMgr, *this);
}

/*
 * Abort.
 */
void SvBinding::Abort (void)
{
    m_eErrCode = ERRCODE_IO_ABORT;

    if (m_pTransport)
        m_pTransport->Abort();

    DELETEZ (m_pTransport);
    DELETEZ (m_pCancelable);

    m_xCallback.Clear();
}

/*
 * Suspend.
 */
void SvBinding::Suspend (void)
{
    DBG_WARNING ("SvBinding::Suspend(): not implemented");
}

/*
 * Resume.
 */
void SvBinding::Resume (void)
{
    DBG_WARNING ("SvBinding::Resume(): not implemented");
}

/*
 * GetMimeType.
 */
ErrCode SvBinding::GetMimeType (String &rMime)
{
    if (!m_bStarted)
    {
        // Initialize context.
        if (m_aBindCtx.GetPostLockBytes() != NULL)
            m_aBindCtx.SetBindAction (BINDACTION_POST);
        else
            m_aBindCtx.SetBindAction (BINDACTION_GET);

        // Start transport.
        StartTransport();
    }

    while (!m_bMimeAvail && !m_eErrCode)
    {
        if (m_aBindCtx.GetBindMode() & SVBIND_ASYNC)
            return ERRCODE_IO_PENDING;
        else
            Application::Yield();
    }

    if (m_bMimeAvail)
    {
        rMime = m_aMime;
        m_eErrCode = ERRCODE_NONE;
    }
    return m_eErrCode;
}

/*
 * GetStream.
 */
ErrCode SvBinding::GetStream (SvStream *&rpStrm)
{
    SvLockBytesRef xLockBytes;

    ErrCode eErrCode = GetLockBytes (xLockBytes);
    if (eErrCode == ERRCODE_NONE)
        rpStrm = new SvStream (xLockBytes);
    else
        rpStrm = NULL;

    return eErrCode;
}

/*
 * GetLockBytes.
 */
ErrCode SvBinding::GetLockBytes (SvLockBytesRef &rxLockBytes)
{
    if (!m_bStarted)
    {
        // Initialize context.
        if (m_aBindCtx.GetPostLockBytes() != NULL)
            m_aBindCtx.SetBindAction (BINDACTION_POST);
        else
            m_aBindCtx.SetBindAction (BINDACTION_GET);

        // Start transport.
        StartTransport();
    }

    while (!m_xLockBytes.Is() && !m_eErrCode)
    {
        if (m_aBindCtx.GetBindMode() & SVBIND_ASYNC)
            return ERRCODE_IO_PENDING;
        else
            Application::Yield();
    }

    if (m_xLockBytes.Is())
    {
        rxLockBytes = m_xLockBytes;
        m_eErrCode = ERRCODE_NONE;
    }
    return m_eErrCode;
}

/*
 * PutStream.
 */
ErrCode SvBinding::PutStream (SvStream *pStrm)
{
    SvLockBytesRef xLockBytes (new SvLockBytes (pStrm));
    return PutLockBytes (xLockBytes);
}

/*
 * PutLockBytes.
 */
ErrCode SvBinding::PutLockBytes (SvLockBytesRef &rxLockBytes)
{
    if (!m_bStarted)
    {
        // Initialize context.
        m_aBindCtx.SetPostLockBytes (rxLockBytes);
        m_aBindCtx.SetBindAction (BINDACTION_PUT);

        // Start transport.
        StartTransport();
    }

    while (!m_bComplete && !m_eErrCode)
    {
        if (m_aBindCtx.GetBindMode() & SVBIND_ASYNC)
            return ERRCODE_IO_PENDING;
        else
            Application::Yield();
    }
    return m_eErrCode;
}

/*
 * OnStart.
 */
void SvBinding::OnStart (void)
{
    SvBindingRef xThis (this);
    if (m_xCallback.Is())
    {
        vos::OGuard aAppGuard (Application::GetSolarMutex());
        if (m_xCallback.Is())
            m_xCallback->InitStartTime();
    }
}

/*
 * OnError.
 */
void SvBinding::OnError (ErrCode eErrCode)
{
    SvBindingRef xThis (this);
    m_eErrCode = eErrCode;

    if (m_xCallback.Is())
    {
        vos::OGuard aAppGuard (Application::GetSolarMutex());
        if (m_xCallback.Is())
            m_xCallback->OnStopBinding (m_eErrCode, String());
    }

    DELETEZ (m_pTransport);
    DELETEZ (m_pCancelable);
}

/*
 * OnMimeAvailable.
 */
void SvBinding::OnMimeAvailable (const String &rMime)
{
    m_aMime = rMime;
    m_bMimeAvail = TRUE;
}

/*
 * OnExpiresAvailable.
 */
void SvBinding::OnExpiresAvailable (const DateTime &rExpires)
{
    m_aExpires = rExpires;
}

/*
 * OnHeaderAvailable.
 */
void SvBinding::OnHeaderAvailable (const String &rName, const String &rValue)
{
    if (!m_xHeadIter.Is())
        m_xHeadIter = new SvKeyValueIterator;

    m_xHeadIter->Append (SvKeyValue (rName, rValue));
}

/*
 * OnDataAvailable.
 */
void SvBinding::OnDataAvailable (
    SvStatusCallbackType eType, ULONG nSize, SvLockBytes *pLockBytes)
{
    SvBindingRef xThis (this);

    if (!m_xLockBytes.Is())
        m_xLockBytes = pLockBytes;

    switch (eType)
    {
        case SVBSCF_FIRSTDATANOTIFICATION:
        case SVBSCF_INTERMEDIATEDATANOTIFICATION:
            if (m_bMimeAvail && m_xLockBytes.Is() && nSize)
            {
                vos::IMutex &rAppMutex = Application::GetSolarMutex();
                if (m_xCallback.Is() && rAppMutex.tryToAcquire())
                {
                    m_xCallback->OnDataAvailable (
                        eType, nSize, *m_xLockBytes);
                    rAppMutex.release();
                }
            }
            break;

        case SVBSCF_LASTDATANOTIFICATION:
            m_bComplete = TRUE;
            OnError (ERRCODE_NONE);
            break;

        default: // Ignored.
            break;
    }
}

/*
 * OnProgress.
 */
void SvBinding::OnProgress (
    ULONG nNow, ULONG nEnd, SvBindStatus eStat)
{
    SvBindingRef xThis (this);
    if (m_xCallback.Is())
    {
        vos::IMutex &rAppMutex = Application::GetSolarMutex();
        if (m_xCallback.Is() && rAppMutex.tryToAcquire())
        {
            m_xCallback->OnProgress (
                nNow, nEnd, eStat, m_aUrlObj.GetMainURL( INetURLObject::DECODE_TO_IURI ));
            rAppMutex.release();
        }
    }
}

/*
 * OnRedirect.
 */
void SvBinding::OnRedirect (const String &rUrl)
{
    SvBindingRef xThis (this);
    if (m_xCallback.Is())
    {
        vos::OGuard aAppGuard (Application::GetSolarMutex());

        INetURLHistory::GetOrCreate()->PutUrl (m_aUrlObj);
        m_aUrlObj.SetURL (rUrl);

        if (m_xCallback.Is())
            m_xCallback->OnProgress (0, 0, SVBINDSTATUS_REDIRECTING, rUrl);
    }
}

/*
 * GetCookie.
 */
String SvBinding::GetCookie (void) const
{
    INetProtocol eProto = m_aUrlObj.GetProtocol();
    if ((eProto == INET_PROT_HTTP) || (eProto == INET_PROT_HTTPS))
    {
        // Get Cookie(s).
        SvBindingCookieRequest_Impl aRequest(m_aUrlObj.GetMainURL(INetURLObject::DECODE_TO_IURI));
        return aRequest.GetCookie();
    }
    else
    {
        // Not supported.
        return String();
    }
}

/*
 * SetCookie.
 */
void SvBinding::SetCookie (const String &rCookieField)
{
    INetProtocol eProto = m_aUrlObj.GetProtocol();
    if ((eProto == INET_PROT_HTTP) || (eProto == INET_PROT_HTTPS))
    {
        // Set Cookie.
        SvBindingCookieRequest_Impl aRequest(m_aUrlObj.GetMainURL(INetURLObject::DECODE_TO_IURI));
        aRequest.SetCookie (rCookieField);
    }
}

/*
 * GetHeaders.
 */
SvKeyValueIteratorRef SvBinding::GetHeaders (void) const
{
    if (m_xHeadIter.Is())
        return SvKeyValueIteratorRef(m_xHeadIter);
    else
        return SvKeyValueIteratorRef(new SvKeyValueIterator);
}

/*
 * SetHeaders.
 */
void SvBinding::SetHeaders (SvKeyValueIteratorRef & )
{
}

/*
 * ShouldUseFtpProxy.
 */
BOOL SvBinding::ShouldUseFtpProxy (const String &rUrl)
{
    return BAPP()->ShouldUseFtpProxy (rUrl);
}

/*========================================================================
 *
 * SvBindStatusCallback implementation.
 *
 *======================================================================*/
/*
 * SvBindStatusCallback.
 */
SvBindStatusCallback::SvBindStatusCallback (void)
    : m_bInAvailableCall (FALSE),
      m_bDonePending     (FALSE),
      m_bDataPending     (FALSE),
      m_bReloadPending   (FALSE),
      m_bPartPending     (FALSE)
{
}

/*
 * ~SvBindStatusCallback.
 */
SvBindStatusCallback::~SvBindStatusCallback (void)
{
}

/*
 * SetProgressCallback.
 */
Link SvBindStatusCallback::m_aProgressCallback;

void SvBindStatusCallback::SetProgressCallback (const Link &rLink)
{
    m_aProgressCallback = rLink;
}

/*
 * InitStartTime.
 */
void SvBindStatusCallback::InitStartTime (void)
{
    m_nStartTicks = Time::GetSystemTicks();
}

/*
 * OnProgress.
 */
void SvBindStatusCallback::OnProgress (
    ULONG nNow, ULONG nMax, SvBindStatus eStat, const String& rStatusText)
{
    ULONG nTicks = std::max((Time::GetSystemTicks() - m_nStartTicks), (ULONG) 1);

    SvProgressArg aArg (rStatusText);
    aArg.nProgress = nNow;
    aArg.nMax      = nMax;
    aArg.eStatus   = eStat;
    aArg.nRate     = (float)((nNow * 1000.0) / nTicks);

    m_aProgressCallback.Call (&aArg);
}

/*
 * OnDataAvailable (SvLockBytes).
 */
void SvBindStatusCallback::OnDataAvailable (
    SvStatusCallbackType eType, ULONG, SvLockBytes&)
{
    SvBindStatusCallbackRef xThis (this);

    if (!m_bInAvailableCall)
    {
        do
        {
            m_bInAvailableCall = TRUE;

            m_bReloadPending |=
                (eType == SVBSCF_RELOADAVAILABLENOTIFICATION);
            if (m_bReloadPending)
            {
                m_bReloadPending = FALSE;
                m_aReloadLink.Call (this);
            }

            m_bPartPending |=
                (eType == SVBSCF_NEWPARTAVAILABLENOTIFICATION);
            if (m_bPartPending)
            {
                m_bPartPending = FALSE;
                m_aPartLink.Call (this);
            }

            m_bDataPending |=
                ((eType == SVBSCF_FIRSTDATANOTIFICATION) ||
                 (eType == SVBSCF_LASTDATANOTIFICATION ) ||
                 (eType == SVBSCF_INTERMEDIATEDATANOTIFICATION));
            if (m_bDataPending)
            {
                m_bDataPending = FALSE;
                m_aDataLink.Call (this);
            }

            m_bInAvailableCall = FALSE;
        } while (m_bDataPending || m_bPartPending || m_bReloadPending);
    }
    else
    {
        switch (eType)
        {
            case SVBSCF_RELOADAVAILABLENOTIFICATION:
                m_bReloadPending = TRUE;
                break;

            case SVBSCF_NEWPARTAVAILABLENOTIFICATION:
                m_bPartPending = TRUE;
                break;

            default:
                m_bDataPending = TRUE;
                break;
        }
    }

    if (m_bDonePending)
    {
        m_bDonePending = FALSE;
        m_aDoneLink.Call (this);
    }
}

/*
 * OnDataAvailable (SvStream).
 */
void SvBindStatusCallback::OnDataAvailable (
    SvStatusCallbackType eType, ULONG, SvStream&)
{
    SvLockBytes aLB(NULL);
    OnDataAvailable (eType, 0, aLB);
}

/*
 * OnStopBinding.
 */
void SvBindStatusCallback::OnStopBinding (
    ErrCode eErrCode, const String &rStatusText)
{
    (void)eErrCode;
    (void)rStatusText;

    if (!m_bInAvailableCall)
        m_aDoneLink.Call (this);
    else
        m_bDonePending = TRUE;
}

/*========================================================================
 *
 * SvKeyValueIterator implementation.
 *
 *======================================================================*/
SV_DECL_PTRARR_DEL(SvKeyValueList_Impl, SvKeyValue*, 0, 4)
SV_IMPL_PTRARR(SvKeyValueList_Impl, SvKeyValue*);

/*
 * SvKeyValueIterator.
 */
SvKeyValueIterator::SvKeyValueIterator (void)
    : m_pList (new SvKeyValueList_Impl),
      m_nPos  (0)
{
}

/*
 * ~SvKeyValueIterator.
 */
SvKeyValueIterator::~SvKeyValueIterator (void)
{
    delete m_pList;
}

/*
 * GetFirst.
 */
BOOL SvKeyValueIterator::GetFirst (SvKeyValue &rKeyVal)
{
    m_nPos = m_pList->Count();
    return GetNext (rKeyVal);
}

/*
 * GetNext.
 */
BOOL SvKeyValueIterator::GetNext (SvKeyValue &rKeyVal)
{
    if (m_nPos > 0)
    {
        rKeyVal = *m_pList->GetObject(--m_nPos);
        return TRUE;
    }
    else
    {
        // Nothing to do.
        return FALSE;
    }
}

/*
 * Append.
 */
void SvKeyValueIterator::Append (const SvKeyValue &rKeyVal)
{
    SvKeyValue *pKeyVal = new SvKeyValue (rKeyVal);
    m_pList->C40_INSERT(SvKeyValue, pKeyVal, m_pList->Count());
}

/*========================================================================
 *
 * SvRemoteStream implementation.
 *
 *======================================================================*/
/*
 * SvRemoteStream.
 */
SvRemoteStream::SvRemoteStream (const String &rUrl, StreamMode eMode)
    : m_aUrl  (rUrl),
      m_eMode (eMode)
{
    SvStream::bIsWritable = (m_eMode & STREAM_WRITE) != 0;

    m_xBinding = new SvBinding (
        m_aUrl, 0, m_eMode, new SvBindStatusCallback);

    SvLockBytesRef xLockBytes_;
    SetError (m_xBinding->GetLockBytes (xLockBytes_));
    SetLockBytes (xLockBytes_);
}

/*
 * ~SvRemoteStream.
 */
SvRemoteStream::~SvRemoteStream (void)
{
    m_xBinding->Abort();
}

/*
 * SetDataAvailableLink.
 */
void SvRemoteStream::SetDataAvailableLink (const Link &rLink)
{
    if (m_xBinding->GetCallback())
        m_xBinding->GetCallback()->SetDataAvailableLink (rLink);
}

/*
 * SetDoneLink.
 */
void SvRemoteStream::SetDoneLink (const Link &rLink)
{
    if (m_xBinding->GetCallback())
        m_xBinding->GetCallback()->SetDoneLink (rLink);
}

/*
 * Commit.
 */
ErrCode SvRemoteStream::Commit (void)
{
    ErrCode eErrCode = ERRCODE_IO_INVALIDACCESS;
    DBG_ASSERT(
        m_xBinding->IsComplete(),
        "SvRemoteStream::Commit(): Binding not yet complete");

    if (m_xBinding->IsComplete())
    {
        m_xBinding = new SvBinding (
            m_aUrl, 0, m_eMode, new SvBindStatusCallback);

        SvLockBytesRef xLockBytes_ (GetLockBytes());
        eErrCode = m_xBinding->PutLockBytes (xLockBytes_);
    }

    SetError (eErrCode);
    return eErrCode;
}



