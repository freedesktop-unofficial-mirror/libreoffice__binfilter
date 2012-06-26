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

#include <bf_svtools/svdde.hxx>
#include <rtl/instance.hxx>

namespace binfilter
{

DdeData::DdeData()
{
}

DdeData::DdeData( const DdeData& )
{
}

DdeData::~DdeData( void )
{
}

void DdeData::SetFormat( ULONG )
{
}

ULONG DdeData::GetFormat() const
{
  return 0L;
}

DdeData& DdeData::operator = ( const DdeData& )
{
  return *this;
}

DdeData::operator long() const
{
  return 0L;
}

DdeData::operator const void*() const
{
  return NULL;
}

long DdeConnection::GetError()
{
  return 0L;
}

DdeConnection::DdeConnection( const String&, const String& )
{
}

DdeConnection::~DdeConnection( void )
{
}

const String& DdeConnection::GetServiceName()
{
  return String::EmptyString();
}

const String& DdeConnection::GetTopicName()
{
  return String::EmptyString();
}

DdeTransaction::DdeTransaction( DdeConnection& rConnection, const String&, long ) :
     rDde( rConnection )
{
}

DdeTransaction::DdeTransaction( const DdeTransaction& rTransaction ) :
     rDde( rTransaction.rDde )
{
}

void DdeTransaction::Execute(void)
{
}

void DdeTransaction::Done( BOOL )
{
}

void DdeTransaction::Data( const DdeData* )
{
}

DdeTransaction::~DdeTransaction(void)
{
}

DdeRequest::DdeRequest(DdeConnection& rConnection, const String& rString, long lLong ) :
     DdeTransaction( rConnection, rString, lLong )
{
}

DdeLink::DdeLink( DdeConnection& rConnection, const String& rString, long l ) :
DdeTransaction( rConnection, rString, l )
{
}

DdeLink::~DdeLink()
{
}

void DdeLink::Notify()
{
}

DdeHotLink::DdeHotLink( DdeConnection& rConnection, const String& rString, long l ) :
DdeLink( rConnection, rString, l )
{
}
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
