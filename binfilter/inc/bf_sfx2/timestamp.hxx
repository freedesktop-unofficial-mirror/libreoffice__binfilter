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
#ifndef _SFX2_TIMESTAMP_HXX
#define _SFX2_TIMESTAMP_HXX

#include <bf_svtools/bf_solar.h>

#include <bf_tools/string.hxx>

#include <tools/stream.hxx>

#include <tools/datetime.hxx>

namespace binfilter {

//______________________________________________________________________________________________________________________________
//  defines
//______________________________________________________________________________________________________________________________

#define TIMESTAMP_MAXLENGTH             31                                                      /// Max. length of valid timestamp in stream.

//______________________________________________________________________________________________________________________________
//  classes, structs
//______________________________________________________________________________________________________________________________

class TimeStamp
{
    //--------------------------------------------------------------------------------
    //  public method
    //--------------------------------------------------------------------------------
    public:

        //--------------------------------------------------------------------------------
        //  construct / destruct
        //--------------------------------------------------------------------------------

        TimeStamp (                                                 ) ;
        TimeStamp ( const String& rName                             ) ;
        TimeStamp ( const DateTime& rDateTime                       ) ;
        TimeStamp ( const String& rName, const DateTime& rDateTime  ) ;

        //--------------------------------------------------------------------------------
        //  operator methods
        //--------------------------------------------------------------------------------

        const TimeStamp&    operator=   ( const TimeStamp& rCopy    )       ;
        BOOL                operator==  ( const TimeStamp& rCompare ) const ;
        int                 operator!=  ( const TimeStamp& rCompare ) const ;

        //--------------------------------------------------------------------------------
        //  other methods
        //--------------------------------------------------------------------------------

        BOOL                IsValid (                           ) const ;
        void                SetInvalid();
        BOOL                Load    ( SvStream& rStream         )       ;
        BOOL                Save    ( SvStream& ) const {return false;}
        void                SetName ( const String& rName       )       ;
        void                SetTime ( const DateTime& rDateTime )       ;
        const String&       GetName (                           ) const ;
        const DateTime&     GetTime (                           ) const ;

    //--------------------------------------------------------------------------------
    //  protected methods
    //--------------------------------------------------------------------------------
    protected:

    //--------------------------------------------------------------------------------
    //  private methods
    //--------------------------------------------------------------------------------
    private:

        void    impl_adjustName     ( String& rName ) ;

        //--------------------------------------------------------------------------------
        //  debug methods
        //--------------------------------------------------------------------------------

        #ifdef DBG_UTIL

        BOOL    impl_debug_checkParameter   ( const String& rString                             ) const ;
        BOOL    impl_debug_checkParameter   ( const String& rString, const DateTime& rDateTime  ) const ;
        BOOL    impl_debug_checkParameter   ( const TimeStamp& rTimeStamp                       ) const ;
        BOOL    impl_debug_checkParameter   ( SvStream& rSvStream                               ) const ;
        BOOL    impl_debug_checkParameter   ( const DateTime& rDateTime                         ) const ;

        #endif // DBG_UTIL

    //--------------------------------------------------------------------------------
    //  private variables
    //--------------------------------------------------------------------------------
    private:

        String      m_sModifiedByName   ;   /// Name of stamp
        DateTime    m_aModifiedDateTime ;   /// Time and date of stamp
} ;

}
#endif // _TIMESTAMP_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
