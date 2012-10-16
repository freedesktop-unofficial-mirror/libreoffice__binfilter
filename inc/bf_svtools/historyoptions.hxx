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
#ifndef INCLUDED_SVTOOLS_HISTORYOPTIONS_HXX
#define INCLUDED_SVTOOLS_HISTORYOPTIONS_HXX

#include <sal/types.h>

#include <osl/mutex.hxx>

#include <com/sun/star/uno/Sequence.h>

#include <com/sun/star/beans/PropertyValue.hpp>

#include <rtl/ustring.hxx>

#include <bf_svtools/options.hxx>

namespace binfilter
{

//_________________________________________________________________________________________________________________
//  types, enums, ...
//_________________________________________________________________________________________________________________

/*-************************************************************************************************************//**
    @descr          The method GetList() returns a list of property values.
                    Use follow defines to seperate values by names.
*//*-*************************************************************************************************************/

#define HISTORY_PROPERTYNAME_URL            ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("URL"       ))
#define HISTORY_PROPERTYNAME_FILTER         ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Filter"    ))
#define HISTORY_PROPERTYNAME_TITLE          ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Title"     ))
#define HISTORY_PROPERTYNAME_PASSWORD       ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Password"  ))

/*-************************************************************************************************************//**
    @descr          You can use these enum values to specify right history if you call ouer interface methods.
*//*-*************************************************************************************************************/

enum EHistoryType
{
    ePICKLIST       = 0,
    eHISTORY        = 1,
    eHELPBOOKMARKS  = 2
};

//_________________________________________________________________________________________________________________
//  forward declarations
//_________________________________________________________________________________________________________________

/*-************************************************************************************************************//**
    @short          forward declaration to our private date container implementation
    @descr          We use these class as internal member to support small memory requirements.
                    You can create the container if it is neccessary. The class which use these mechanism
                    is faster and smaller then a complete implementation!
*//*-*************************************************************************************************************/

class SvtHistoryOptions_Impl;

/*-************************************************************************************************************//**
    @short          collect informations about history features
    @descr          -

    @implements     -
    @base           -

    @devstatus      ready to use
*//*-*************************************************************************************************************/

class  SvtHistoryOptions: public Options
{
    //-------------------------------------------------------------------------------------------------------------
    //  public methods
    //-------------------------------------------------------------------------------------------------------------

    public:

        //---------------------------------------------------------------------------------------------------------
        //  constructor / destructor
        //---------------------------------------------------------------------------------------------------------

        /*-****************************************************************************************************//**
            @short      standard constructor and destructor
            @descr      This will initialize an instance with default values.
                        We implement these class with a refcount mechanism! Every instance of this class increase it
                        at create and decrease it at delete time - but all instances use the same data container!
                        He is implemented as a static member ...

            @seealso    member m_nRefCount
            @seealso    member m_pDataContainer

            @param      -
            @return     -

            @onerror    -
        *//*-*****************************************************************************************************/

         SvtHistoryOptions();
        virtual ~SvtHistoryOptions();

        //---------------------------------------------------------------------------------------------------------
        //  interface
        //---------------------------------------------------------------------------------------------------------

        /*-****************************************************************************************************//**
            @short      interface methods to get and set value of config key "org.openoffice.Office.Common/History/..."
            @descr      key "PickList"  : The last used documents displayed in the file menu.
                        key "History"   : The last opened documents general.
*/

    //-------------------------------------------------------------------------------------------------------------
    //  private methods
    //-------------------------------------------------------------------------------------------------------------

    private:

        /*-****************************************************************************************************//**
            @short      return a reference to a static mutex
            @descr      Make these class threadsafe.

            @seealso    -

            @param      -
            @return     A reference to a static mutex member.

            @onerror    -
        *//*-*****************************************************************************************************/

         static ::osl::Mutex& GetOwnStaticMutex();

    //-------------------------------------------------------------------------------------------------------------
    //  private member
    //-------------------------------------------------------------------------------------------------------------

    private:

        /*Attention

            Don't initialize these static member in these header!
            a) Double dfined symbols will be detected ...
            b) and unresolved externals exist at linking time.
            Do it in your source only.
         */

        static SvtHistoryOptions_Impl*  m_pDataContainer    ;   /// impl. data container as dynamic pointer for smaller memory requirements!
        static sal_Int32                m_nRefCount         ;   /// internal ref count mechanism

};      // class SvtHistoryOptions

}

#endif  // #ifndef INCLUDED_SVTOOLS_HISTORYOPTIONS_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
