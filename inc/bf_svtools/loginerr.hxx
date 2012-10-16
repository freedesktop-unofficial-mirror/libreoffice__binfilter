/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef _LOGINERR_HXX
#define _LOGINERR_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_tools/string.hxx>
#include <tools/errcode.hxx>

#include <bf_svtools/hint.hxx>

namespace binfilter
{

//=========================================================================

#define LOGINERROR_FLAG_SET_SAVE_PASSWORD   1
#define LOGINERROR_FLAG_MODIFY_ACCOUNT      2
#define LOGINERROR_FLAG_MODIFY_USER_NAME    4
#define LOGINERROR_FLAG_PERSISTENT_PASSWORD 8

class LoginErrorInfo
{
private:
    String _aTitle;
    String _aServer;
    String _aAccount;
    String _aUserName;
    String _aPassword;
    String _aPath;
    String _aErrorText;
    BYTE   _nFlags;
    USHORT _nRet;

public:
                    LoginErrorInfo()
                    : _nFlags( LOGINERROR_FLAG_MODIFY_USER_NAME ),
                      _nRet( ERRCODE_BUTTON_CANCEL )
                    {
                    }

    const String&   GetTitle() const        { return _aTitle; }
    const String&   GetServer() const       { return _aServer; }
    const String&   GetAccount() const      { return _aAccount; }
    const String&   GetUserName() const     { return _aUserName; }
    const String&   GetPassword() const     { return _aPassword; }
    const String&   GetPath() const         { return _aPath; }
    const String&   GetErrorText() const    { return _aErrorText; }
    BOOL            GetIsPersistentPassword() const
                    { return ( _nFlags & LOGINERROR_FLAG_PERSISTENT_PASSWORD ); }
    BOOL            GetIsSavePassword() const
                    { return ( _nFlags & LOGINERROR_FLAG_SET_SAVE_PASSWORD ); }
    BYTE            GetFlags() const        { return _nFlags; }
    USHORT          GetResult() const       { return _nRet; }

    void            SetTitle( const String& aTitle )
                    { _aTitle = aTitle; }
    void            SetServer( const String& aServer )
                    { _aServer = aServer; }
    void            SetAccount( const String& aAccount )
                    { _aAccount = aAccount; }
    void            SetUserName( const String& aUserName )
                    { _aUserName = aUserName; }
    void            SetPassword( const String& aPassword )
                    { _aPassword = aPassword; }
    void            SetPath( const String& aPath )
                    { _aPath = aPath; }
    void            SetErrorText( const String& aErrorText )
                    { _aErrorText = aErrorText; }
    void            SetFlags( BYTE nFlags )
                    { _nFlags = nFlags; }
    inline void     SetSavePassword( BOOL bSet );
    inline void     SetPersistentPassword( BOOL bSet );
    inline void     SetModifyAccount( BOOL bSet );
    inline void     SetModifyUserName( BOOL bSet );
    void            SetResult( USHORT nRet )
                    { _nRet = nRet; }
};

inline void LoginErrorInfo::SetSavePassword( BOOL bSet )
{
    if ( bSet )
        _nFlags |= LOGINERROR_FLAG_SET_SAVE_PASSWORD;
    else
        _nFlags &= ~LOGINERROR_FLAG_SET_SAVE_PASSWORD;
}

inline void LoginErrorInfo::SetPersistentPassword( BOOL bSet )
{
    if ( bSet )
        _nFlags |= LOGINERROR_FLAG_PERSISTENT_PASSWORD;
    else
        _nFlags &= ~LOGINERROR_FLAG_PERSISTENT_PASSWORD;
}

inline void LoginErrorInfo::SetModifyAccount( BOOL bSet )
{
    if ( bSet )
        _nFlags |= LOGINERROR_FLAG_MODIFY_ACCOUNT;
    else
        _nFlags &= ~LOGINERROR_FLAG_MODIFY_ACCOUNT;
}

inline void LoginErrorInfo::SetModifyUserName( BOOL bSet )
{
    if ( bSet )
        _nFlags |= LOGINERROR_FLAG_MODIFY_USER_NAME;
    else
        _nFlags &= ~LOGINERROR_FLAG_MODIFY_USER_NAME;
}

//=========================================================================

class CntLoginErrorHint : public SfxHint
{
private:
    LoginErrorInfo*         _pInfo;

                            CntLoginErrorHint( const CntLoginErrorHint& ); // n.i.
    CntLoginErrorHint&      operator=( const CntLoginErrorHint& ); // n.i.

public:
                            TYPEINFO();

                            CntLoginErrorHint( LoginErrorInfo* pInfo )
                            :   _pInfo( pInfo )
                            {
                            }

    LoginErrorInfo&         GetErrorInfo() const { return *_pInfo; }
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
