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
#ifndef _SWDBMGR_HXX
#define _SWDBMGR_HXX

#include <bf_svtools/bf_solar.h>


#include <bf_tools/string.hxx>

#include <bf_svtools/svarray.hxx>
#include <com/sun/star/util/Date.hpp>

#include <swdbdata.hxx>
#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/Sequence.hxx>
#include <com/sun/star/lang/Locale.hpp>

namespace com{namespace sun{namespace star{
    namespace sdbc{
        class XConnection;
        class XStatement;
        class XDataSource;
        class XResultSet;
    }
    namespace beans{

        class XPropertySet;
        struct PropertyValue;
    }
    namespace sdbcx{
        class XColumnsSupplier;
    }
    namespace util{
        class XNumberFormatter;
    }
}}}
class ListBox;
class Button;
namespace binfilter {
class SvNumberFormatter;
namespace svx {
    class ODataAccessDescriptor;
}

struct SwDBFormatData
{
    ::com::sun::star::util::Date aNullDate;
    ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter> xFormatter;
    ::com::sun::star::lang::Locale aLocale;
};

class SwView;
class SwWrtShell;
class SwPrtOptions;
class SfxProgress;

class SwMailMergeDlg;
class SwXMailMerge;

// -----------------------------------------------------------------------

enum DBMgrOptions
{
    DBMGR_MERGE,            // Datensaetze in Felder
    DBMGR_INSERT,           // Datensaetze in Text
    DBMGR_MERGE_MAILMERGE,  // Serienbriefe drucken
    DBMGR_MERGE_MAILING,    // Serienbriefe als email versenden
    DBMGR_MERGE_MAILFILES   // Serienbriefe als Datei(en) speichern
};

// -----------------------------------------------------------------------

/*--------------------------------------------------------------------
     Beschreibung: (neue) Logische Datenbanken verwalten
 --------------------------------------------------------------------*/
#define SW_DB_SELECT_UNKNOWN    0
#define SW_DB_SELECT_TABLE      1
#define SW_DB_SELECT_QUERY      2

struct SwDSParam : public SwDBData
{
    ::com::sun::star::util::Date    aNullDate;

    ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter>     xFormatter;
    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection>      xConnection;
    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XStatement>       xStatement;
    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>       xResultSet;
    ::com::sun::star::uno::Sequence<  ::com::sun::star::uno::Any >              aSelection;
    BOOL bScrollable;
    BOOL bEndOfDB;
    BOOL bAfterSelection;
    long nSelectionIndex;

    SwDSParam(const SwDBData& rData) :
        SwDBData(rData),
        bScrollable(FALSE),
        bEndOfDB(FALSE),
        bAfterSelection(FALSE),
        nSelectionIndex(0)
        {}

    SwDSParam(const SwDBData& rData,
        const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>&    xResSet,
        const ::com::sun::star::uno::Sequence<  ::com::sun::star::uno::Any >&   rSelection) :
        SwDBData(rData),
        xResultSet(xResSet),
        aSelection(rSelection),
        bScrollable(TRUE),
        bEndOfDB(FALSE),
        bAfterSelection(FALSE),
        nSelectionIndex(0)
        {}

        void CheckEndOfDB()
        {
            if(bEndOfDB)
                bAfterSelection = TRUE;
        }
};
typedef SwDSParam* SwDSParamPtr;
SV_DECL_PTRARR_DEL(SwDSParamArr, SwDSParamPtr, 0, 5)

struct SwNewDBMgr_Impl;
class SwConnectionDisposedListener_Impl;
class SwNewDBMgr
{
friend class SwConnectionDisposedListener_Impl;

    String              sEMailAddrFld;  // Mailing: Spaltenname der E-Mail Adresse
    String              sSubject;       // Mailing: Subject
    String              sAttached;      // Mailing: Attachte Files
    USHORT              nMergeType;
    BOOL                bInitDBFields : 1;  // TRUE: Datenbank an Feldern beim Mergen
    BOOL                bSingleJobs : 1;    // Einzelne Druckjobs bei Aufruf aus Basic
    BOOL                bCancel : 1;        // Serienbrief-Save abgebrochen

    BOOL                bInMerge    : 1;    //merge process active
    BOOL                bMergeSilent : 1;   // suppress display of dialogs/boxes (used when called over API)
    BOOL                bMergeLock : 1;     // prevent update of database fields while document is
                                            // actually printed at the ViewShell
    SwDSParamArr        aDataSourceParams;
    SwNewDBMgr_Impl*    pImpl;
    const SwXMailMerge* pMergeEvtSrc;   // != 0 if mail merge events are to be send

    SwDSParam*          pMergeData;
    SwMailMergeDlg*     pMergeDialog;

    SwDSParam*          FindDSData(const SwDBData& rData, BOOL bCreate);
    SwDSParam*          FindDSConnection(const ::rtl::OUString& rSource, BOOL bCreate);



    // Datensaetze als Text ins Dokument einfuegen

    // Einzelnen Datensatz als Text ins Dokument einfuegen

    // Mischen von Datensaetzen in Felder, dann per email versenden
    // Mischen von Datensaetzen in Felder, dann als Datei abspeichern
    BOOL            ToNextRecord(SwDSParam* pParam);

public:
    SwNewDBMgr();
    ~SwNewDBMgr();

    // Art des aktellen Mergens. Siehe DBMgrOptions-enum
    inline USHORT   GetMergeType() const            { return nMergeType; }
    inline void     SetMergeType( USHORT nTyp )     { nMergeType = nTyp; }

    // MailMergeEvent source
    const SwXMailMerge *    GetMailMergeEvtSrc() const  { return pMergeEvtSrc; }
    void SetMailMergeEvtSrc( const SwXMailMerge *pSrc ) { pMergeEvtSrc = pSrc; }

    inline BOOL     IsMergeSilent() const           { return bMergeSilent != 0; }
    inline void     SetMergeSilent( BOOL bVal )     { bMergeSilent = bVal; }

    // Mischen von Datensaetzen in Felder, dann drucken
    // Datenbankfelder mit fehlendem Datenbankname initialisieren
    inline BOOL     IsInitDBFields() const  { return bInitDBFields; }
    inline void     SetInitDBFields(BOOL b) { bInitDBFields = b;    }

    // Serienbriefe einzelnd oder alle zusammen drucken/speichern
    inline BOOL     IsSingleJobs() const    { return bSingleJobs;   }
    inline void     SetSingleJobs(BOOL b)   { bSingleJobs = b;  }

    // Mailing
    // email-Daten setzen
    inline void     SetEMailColumn(const String& sColName) { sEMailAddrFld = sColName; }
    inline void     SetSubject(const String& sSbj) { sSubject = sSbj; }
    inline void     SetAttachment(const String& sAtt) { sAttached = sAtt; }


    // Listbox mit allen Tabellennamen einer Datenbank fuellen

    // Listbox mit allen Spaltennamen einer Datenbanktabelle fuellen



    inline BOOL     IsInMerge() const   { return bInMerge; }

    // check if a data source is open
    BOOL            IsDataSourceOpen(const String& rDataSource,
                                    const String& rTableOrQuery, sal_Bool bMergeOnly);

    // add data source information to the data source array - was PreInitDBData
    void            AddDSData(const SwDBData& rData, long nSelStart, long nSelEnd);

    // open the source while fields are updated - for the calculator only!
    BOOL            OpenDataSource(const String& rDataSource, const String& rTableOrQuery, sal_Int32 nCommandType = -1);
    sal_uInt32      GetSelectedRecordId(const String& rDataSource, const String& rTableOrQuery, sal_Int32 nCommandType = -1);
    BOOL            GetColumnCnt(const String& rSourceName, const String& rTableName,
                            const String& rColumnName, sal_uInt32 nAbsRecordId, long nLanguage,
                            String& rResult, double* pNumber);
    //create and store or find an already stored connection to a data source for use
    //in SwFldMgr and SwDBTreeList
    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection>
                    RegisterConnection(::rtl::OUString& rSource);

    const SwDSParam* CreateDSData(const SwDBData& rData)
                        {return FindDSData(rData, TRUE);}
    const SwDSParamArr& GetDSParamArray() const {return aDataSourceParams;}


    //close all data sources - after fields were updated
    void            CloseAll(BOOL bIncludingMerge = TRUE);

    BOOL            ToNextRecord(const String& rDataSource, const String& rTableOrQuery, sal_Int32 nCommandType = -1);

    sal_uInt32      GetSelectedRecordId();

    const SwDBData& GetAddressDBName();


    static ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection>
            GetConnection(const String& rDataSource,
                ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDataSource>& rxSource);
};

} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
