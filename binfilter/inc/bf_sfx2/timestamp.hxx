/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: timestamp.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: ihi $ $Date: 2007-11-26 18:57:58 $
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
#ifndef _SFX2_TIMESTAMP_HXX
#define _SFX2_TIMESTAMP_HXX

#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif

#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif

#ifndef _DATETIME_HXX
#include <tools/datetime.hxx>
#endif

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
        BOOL                Save    ( SvStream& rStream         ) const ;
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
