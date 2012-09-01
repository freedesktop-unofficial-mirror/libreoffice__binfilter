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

#ifndef _SVDSOB_HXX
#define _SVDSOB_HXX

#include <bf_svtools/bf_solar.h>

#include <com/sun/star/uno/Any.hxx>

#include <tools/stream.hxx>

#ifndef _STRING_H
#define _STRING_H
#endif
namespace binfilter {

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
  Deklaration eines statischen Mengentyps. Die Menge kann die Elemente
  0..255 aufnehmen und verbraucht stets 32 Bytes.
*/

class SetOfByte {
protected:
    BYTE aData[32];
public:
    SetOfByte(bool bInitVal=FALSE)                  { memset(aData,bInitVal ? 0xFF : 0x00,sizeof(aData)); }
    bool operator==(const SetOfByte& rCmpSet) const { return (memcmp(aData,rCmpSet.aData,sizeof(aData))==0); }
    bool operator!=(const SetOfByte& rCmpSet) const { return (memcmp(aData,rCmpSet.aData,sizeof(aData))!=0); }
    void     Set  (BYTE a)                              { aData[a/8]|=1<<a%8; }
    void     Clear(BYTE a)                              { aData[a/8]&=~(1<<a%8); }
    void     Set  (BYTE a, bool b)                  { if (b) Set(a); else Clear(a); }
    bool IsSet(BYTE a) const                        { return (aData[a/8]&1<<a%8)!=0; }
    bool IsSet(USHORT a) const                      { return (a<=255) && (aData[a/8]&1<<a%8)!=0; }
    void     SetAll()                                   { memset(aData,0xFF,sizeof(aData)); }
    void     ClearAll()                                 { memset(aData,0x00,sizeof(aData)); }
    bool IsEmpty() const;
    void     operator&=(const SetOfByte& r2ndSet);
    friend inline SvStream& operator<<(SvStream& rOut, const SetOfByte& rSet);
    friend inline SvStream& operator>>(SvStream& rIn, SetOfByte& rSet);

     void   PutValue( const ::com::sun::star::uno::Any & rAny );        // initialize this set with a uno sequence of sal_Int8
    void    QueryValue( ::com::sun::star::uno::Any & rAny ) const;  // returns a uno sequence of sal_Int8
};

inline SvStream& operator<<(SvStream& rOut, const SetOfByte& rSet)
{
    rOut.Write((char*)rSet.aData,32);
    return rOut;
}

inline SvStream& operator>>(SvStream& rIn, SetOfByte& rSet)
{
    rIn.Read((char*)rSet.aData,32);
    return rIn;
}

}//end of namespace binfilter
#endif // _SVDSOB_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
