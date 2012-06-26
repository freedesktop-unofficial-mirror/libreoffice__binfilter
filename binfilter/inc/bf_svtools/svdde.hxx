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

#ifndef _SVDDE_HXX
#define _SVDDE_HXX

#include <bf_svtools/bf_solar.h>

#include "bf_svtools/svtdllapi.h"

#include <sot/exchange.hxx>

#include <bf_tools/string.hxx>
#include <tools/list.hxx>
#include <tools/link.hxx>

namespace binfilter
{

class DdeString;
class DdeData;
class DdeConnection;
class DdeTransaction;
class DdeLink;
class DdeRequest;
class DdeWarmLink;
class DdeHotLink;
class ConvList;
struct DdeDataImp;
struct DdeImp;

DECLARE_LIST( DdeConnections, DdeConnection* )
DECLARE_LIST( DdeTransactions, DdeTransaction* )
DECLARE_LIST( DdeFormats, long )

#ifdef WNT
class DdeService;
class DdeItem;
class DdeItemImp;
class DdeTopic;
DECLARE_LIST( DdeServices, DdeService* )
DECLARE_LIST( DdeTopics, DdeTopic* )
DECLARE_LIST( DdeItems, DdeItem* )
#endif


// -----------
// - DdeData -
// -----------

class  DdeData
{
    friend class    DdeInternal;
#ifdef WNT
    friend class    DdeService;
#endif
    friend class    DdeConnection;
    friend class    DdeTransaction;
    DdeDataImp*     pImp;

    void            Lock();
    void            SetFormat( ULONG nFmt );

public:
                    DdeData();
#ifdef WNT
                    DdeData( const void*, long, ULONG = FORMAT_STRING );
                    DdeData( const String& );
#endif
                    DdeData( const DdeData& );
                    ~DdeData();

    operator const  void*() const;
    operator        long() const;

    ULONG           GetFormat() const;

    DdeData&        operator = ( const DdeData& );

    static ULONG GetExternalFormat( ULONG nFmt );
    static ULONG GetInternalFormat( ULONG nFmt );
};

// ------------------
// - DdeTransaction -
// ------------------

class  DdeTransaction
{
public:
    virtual void    Data( const DdeData* );
    virtual void    Done( BOOL bDataValid );
protected:
    DdeConnection&  rDde;
    DdeData         aDdeData;
    DdeString*      pName;
    short           nType;
    long            nId;
    long            nTime;
    Link            aData;
    Link            aDone;
    BOOL            bBusy;

                    DdeTransaction( DdeConnection&, const String&, long = 0 );

public:
    virtual        ~DdeTransaction();

    BOOL            IsBusy() { return bBusy; }
    const String&   GetName() const;

    void            Execute();

    void            SetDataHdl( const Link& rLink ) { aData = rLink; }
    const Link&     GetDataHdl() const { return aData; }

    void            SetDoneHdl( const Link& rLink ) { aDone = rLink; }
    const Link&     GetDoneHdl() const { return aDone; }

    void            SetFormat( ULONG nFmt ) { aDdeData.SetFormat( nFmt );  }
    ULONG           GetFormat() const       { return aDdeData.GetFormat(); }

    long            GetError();

private:
    friend class    DdeInternal;
    friend class    DdeConnection;

                            DdeTransaction( const DdeTransaction& );
    const DdeTransaction&   operator= ( const DdeTransaction& );

};

// -----------
// - DdeLink -
// -----------

class  DdeLink : public DdeTransaction
{
    Link            aNotify;

public:
                    DdeLink( DdeConnection&, const String&, long = 0 );
    virtual        ~DdeLink();

    void            SetNotifyHdl( const Link& rLink ) { aNotify = rLink; }
    const Link&     GetNotifyHdl() const { return aNotify; }
    virtual void    Notify();
};

// ---------------
// - DdeWarmLink -
// ---------------

class  DdeWarmLink : public DdeLink
{
public:
            DdeWarmLink( DdeConnection&, const String&, long = 0 );
};

// --------------
// - DdeHotLink -
// --------------

class  DdeHotLink : public DdeLink
{
public:
            DdeHotLink( DdeConnection&, const String&, long = 0 );
};

// --------------
// - DdeRequest -
// --------------

class  DdeRequest : public DdeTransaction
{
public:
            DdeRequest( DdeConnection&, const String&, long = 0 );
};

#ifdef WNT
// -----------
// - DdePoke -
// -----------

class  DdePoke : public DdeTransaction
{
public:
            DdePoke( DdeConnection&, const String&, const char*, long,
                     ULONG = FORMAT_STRING, long = 0 );
            DdePoke( DdeConnection&, const String&, const DdeData&, long = 0 );
            DdePoke( DdeConnection&, const String&, const String&, long = 0 );
};

// --------------
// - DdeExecute -
// --------------

class  DdeExecute : public DdeTransaction
{
public:
            DdeExecute( DdeConnection&, const String&, long = 0 );
};
#endif

// -----------------
// - DdeConnection -
// -----------------

class  DdeConnection
{
    friend class    DdeInternal;
    friend class    DdeTransaction;
    DdeTransactions aTransactions;
    DdeString*      pService;
    DdeString*      pTopic;
    DdeImp*         pImp;

public:
                    DdeConnection( const String&, const String& );
                    ~DdeConnection();

    long            GetError();
    long            GetConvId();

    static const DdeConnections& GetConnections();

    BOOL            IsConnected();

    const String&   GetServiceName();
    const String&   GetTopicName();

private:
                            DdeConnection( const DdeConnection& );
    const DdeConnection&    operator= ( const DdeConnection& );
};

#ifdef WNT
// -----------
// - DdeItem -
// -----------

class  DdeItem
{
    friend class    DdeInternal;
    friend class    DdeTopic;
    DdeString*      pName;
    DdeTopic*       pMyTopic;
    DdeItemImp*     pImpData;

    void            IncMonitor( ULONG );
    void            DecMonitor( ULONG );

protected:
    BYTE            nType;

public:
                    DdeItem( const sal_Unicode* );
                    DdeItem( const String& );
                    DdeItem( const DdeItem& );
                    virtual ~DdeItem();

    const String&   GetName() const;
    short           GetLinks();
    void            NotifyClient();
};

// -----------
// - DdeItem -
// -----------

class  DdeGetPutItem : public DdeItem
{
public:
                    DdeGetPutItem( const String& rStr );
                    DdeGetPutItem( const sal_Unicode* p );
                    DdeGetPutItem( const DdeItem& rItem );
    virtual DdeData* Get( ULONG );
    virtual BOOL    Put( const DdeData* );
    virtual void    AdviseLoop( BOOL );     // AdviseLoop starten/stoppen
};

// ------------
// - DdeTopic -
// ------------

class  DdeTopic
{
    void _Disconnect( long );

public:
    virtual void    Connect( long );
    virtual void    Disconnect( long );
    virtual DdeData* Get( ULONG );
    virtual BOOL    Put( const DdeData* );
    virtual BOOL    Execute( const String* );
        // evt. ein neues anlegen; return 0 -> es konnte nicht angelegt werden
    virtual BOOL MakeItem( const String& rItem );

        // es wird ein Warm-/Hot-Link eingerichtet. Return-Wert
        // besagt ob es geklappt hat
    virtual BOOL    StartAdviseLoop();
    virtual BOOL    StopAdviseLoop();

private:
    friend class    DdeInternal;
    friend class    DdeService;
    friend class    DdeItem;

private:
    DdeString*      pName;
    String          aItem;
    DdeItems        aItems;
    Link            aConnectLink;
    Link            aDisconnectLink;
    Link            aGetLink;
    Link            aPutLink;
    Link            aExecLink;

public:
                    DdeTopic( const String& );
    virtual        ~DdeTopic();
    const String&   GetName() const;
    long            GetConvId();

    void            SetConnectHdl( const Link& rLink ) { aConnectLink = rLink; }
    const Link&     GetConnectHdl() const { return aConnectLink;  }
    void            SetDisconnectHdl( const Link& rLink ) { aDisconnectLink = rLink; }
    const Link&     GetDisconnectHdl() const { return aDisconnectLink;  }
    void            SetGetHdl( const Link& rLink ) { aGetLink = rLink; }
    const Link&     GetGetHdl() const { return aGetLink;  }
    void            SetPutHdl( const Link& rLink ) { aPutLink = rLink; }
    const Link&     GetPutHdl() const { return aPutLink;  }
    void            SetExecuteHdl( const Link& rLink ) { aExecLink = rLink; }
    const Link&     GetExecuteHdl() const { return aExecLink; }

    void            NotifyClient( const String& );

    BOOL            IsSystemTopic();
    DdeItem*        AddItem( const DdeItem& );  // werden kopiert !

    const String&   GetCurItem() { return aItem;  }
    const DdeItems& GetItems()   { return aItems; }

private:
                    DdeTopic( const DdeTopic& );
    const DdeTopic& operator= ( const DdeTopic& );
};

// --------------
// - DdeService -
// --------------

class  DdeService
{
    friend class    DdeInternal;

public:
    virtual BOOL    IsBusy();
    virtual String  GetHelp();
        // evt. ein neues anlegen; return 0 -> es konnte nicht angelegt werden
    virtual BOOL    MakeTopic( const String& rItem );

protected:
    virtual String  Topics();
    virtual String  Formats();
    virtual String  SysItems();
    virtual String  Status();
    virtual String  SysTopicGet( const String& );
    virtual BOOL    SysTopicExecute( const String* );

    const DdeTopic* GetSysTopic() const { return pSysTopic; }
private:
    DdeTopics       aTopics;
    DdeFormats      aFormats;
    DdeTopic*       pSysTopic;
    DdeString*      pName;
    ConvList*       pConv;
    short           nStatus;

    BOOL            HasCbFormat( USHORT );

public:
                    DdeService( const String& );
    virtual        ~DdeService();

    const String&   GetName() const;
    short           GetError()              { return nStatus; }
    static DdeServices& GetServices();
    DdeTopics&      GetTopics()             { return aTopics; }
    void            AddTopic( const DdeTopic& );
    void            RemoveTopic( const DdeTopic& );
    void            AddFormat( ULONG );
    void            RemoveFormat( ULONG );
    BOOL            HasFormat( ULONG );

private:
      //              DdeService( const DdeService& );
    //int             operator= ( const DdeService& );
};
#endif

// ------------------
// - DdeTransaction -
// ------------------

inline long DdeTransaction::GetError()
{
    return rDde.GetError();
}

}

#endif // _SVDDE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
