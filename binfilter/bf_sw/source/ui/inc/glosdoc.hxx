/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/
#ifndef _GLOSDOC_HXX
#define _GLOSDOC_HXX

#include <bf_svtools/bf_solar.h>


#include <tools/string.hxx>


#include <bf_svtools/svarray.hxx>
#include <com/sun/star/text/XAutoTextGroup.hpp>
class SvStrings;
namespace binfilter {
class SwTextBlocks;

class SwDocShell;
} //namespace binfilter

#ifndef SW_DECL_SWDOCSHELL_DEFINED
#define SW_DECL_SWDOCSHELL_DEFINED
#include <tools/ref.hxx>
namespace binfilter {
SV_DECL_REF( SwDocShell )
} //namespace binfilter
#endif

#include <cppuhelper/weakref.hxx>

#include <vector>
namespace binfilter {

typedef ::com::sun::star::uno::WeakReference< ::com::sun::star::text::XAutoTextGroup > AutoTextGroupRef;
typedef ::std::vector< AutoTextGroupRef > UnoAutoTextGroups;

typedef ::com::sun::star::uno::Reference< ::com::sun::star::text::XAutoTextEntry > AutoTextEntryRef;
typedef ::std::vector< AutoTextEntryRef > UnoAutoTextEntries;

#define GLOS_DELIM (sal_Unicode)'*'

// CLASS -----------------------------------------------------------------
class SwGlossaries
{
    UnoAutoTextGroups       aGlossaryGroups;
    UnoAutoTextEntries      aGlossaryEntries;
    String                  aPath;
    String                  sOldErrPath;
    String                  sErrPath;
    SvStrings               *pPathArr;
    SvStrings               *pGlosArr;
    BOOL                    bError;
    SwTextBlocks*   GetGlosDoc(const String &rName, BOOL bCreate = TRUE) const{DBG_BF_ASSERT(0, "STRIP"); return NULL;};
    SvStrings       *GetNameList();
    void RemoveFileFromList( const String& rGroup );
    void InvalidateUNOOjects();

public:
    SwGlossaries();
    ~SwGlossaries();

    /** returns the cached AutoTextGroup (if any) for the given group name

        @precond
            If <arg>_bCreate</arg> is <TRUE/>, the SolarMutex must be locked when calling into this method.

        @param _rGroupName
            the name of the glossaries group
        @param _bCreate
            if <TRUE/>, the group is created if it does not yet exist
    */
    ::com::sun::star::uno::Reference< ::com::sun::star::text::XAutoTextGroup >
                            GetAutoTextGroup(
                                const ::rtl::OUString& _rGroupName,
                                bool _bCreate = false
                            );

    /** returns the cached AutoTextEntry (if any) for the given group/with the given name

        @precond
            If <arg>_bCreate</arg> is <TRUE/>, the SolarMutex must be locked when calling into this method.

        @param _rGroupAccessName
            the name to access the group
        @param _rGroupName
            the name of the glossaries group, as to be passed to the entry
        @param _rEntryName
            the name of the auto text entry
        @param _bCreate
            if <TRUE/>, the entry is created if it does not yet exist
    */
    ::com::sun::star::uno::Reference< ::com::sun::star::text::XAutoTextEntry >
                            GetAutoTextEntry(
                                const String& _rCompleteGroupName,
                                const ::rtl::OUString& _rGroupName,
                                const ::rtl::OUString& _rEntryName,
                                bool _bCreate = false
                            );

    USHORT                  GetGroupCnt();
    String                  GetGroupName(USHORT );
    String                  GetGroupTitle( const String& rGroupName );

    BOOL            FindGroupName(String & rGroup);

    SwTextBlocks*   GetGroupDoc(const String &rName,
                                BOOL bCreate = FALSE) const;
    SwTextBlocks*   GetDefGroupDoc() const {return GetGroupDoc(GetDefName());}
    void            PutGroupDoc(SwTextBlocks *pBlock);
    static String   GetDefName();
    static String   GetExtension();

    BOOL            NewGroupDoc(String &rGroupName, const String& rTitle);
    BOOL            RenameGroupDoc(const String& sOldGroup, String& sNewGroup, const String& rNewTitle);
    BOOL            DelGroupDoc(const String &);
    SwDocShellRef   EditGroupDoc(const String &rGrpName, const String& rShortName, BOOL bShow = TRUE );
    void            UpdateGlosPath(BOOL bFull);
};


} //namespace binfilter
#endif // _GLOSDOC_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
