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

#ifndef _SFXSTYLE_HXX
#define _SFXSTYLE_HXX

#include <bf_svtools/bf_solar.h>


#include <rsc/rscsfx.hxx>

#include <bf_tools/string.hxx>
#include <bf_svtools/hint.hxx>
#include <bf_svtools/lstner.hxx>
#include <bf_svtools/brdcst.hxx>

#include <bf_svtools/poolitem.hxx>

#include <bf_svtools/style.hrc>

#include <vector>

class SvStream;

namespace binfilter
{

class SfxItemSet;
class SfxItemPool;
class SfxStyleSheetBasePool;


/*=========================================================================

Jeder, der an Intanzen der Klassen SfxStyleSheetBasePool oder am
SfxStyleSheetBase strukturelle ?nderungen vornimmt, mu? diese ?ber
<SfxStyleSheetBasePool::GetBroadcaster()> broadcasten. Daf?r Gibt es die
Klasse <SfxStyleSheetHint>, die eine Action-Id und einen Pointer auf einen
<SfxStyleSheetBase> erh?lt. Die Actions sind:

#define SFX_STYLESHEET_CREATED      // neu
#define SFX_STYLESHEET_MODIFIED     // ver"andert
#define SFX_STYLESHEET_CHANGED      // ausgetauscht
#define SFX_STYLESHEET_ERASED       // gel"oscht

Es machen bereits die folgenden Methoden von sich aus:

SfxStyleSheetHint(SFX_STYLESHEET_MODIFIED) aus:
   SfxStyleSheetBase::SetName( const String& rName )
   SfxStyleSheetBase::SetParent( const String& rName )
   SfxStyleSheetBase::SetFollow( const String& rName )

SfxSimpleHint(SFX_HINT_DYING) aus:
   SfxStyleSheetBasePool::~SfxStyleSheetBasePool()

SfxStyleSheetHint( SFX_STYLESHEET_CREATED, *p ) aus:
   SfxStyleSheetBasePool::Make( const String& rName,
   SfxStyleFamily eFam, USHORT mask, USHORT nPos)

SfxStyleSheetHint( SFX_STYLESHEET_CHANGED, *pNew ) aus:
   SfxStyleSheetBasePool::Add( SfxStyleSheetBase& rSheet )

SfxStyleSheetHint( SFX_STYLESHEET_ERASED, *p ) aus:
   SfxStyleSheetBasePool::Erase( SfxStyleSheetBase* p )
   SfxStyleSheetBasePool::Clear()

=========================================================================*/

#define VIRTUAL510 virtual

class  SfxStyleSheetBase
{
    friend class SfxStyleSheetBasePool;

protected:
    SfxStyleSheetBasePool&  rPool;          // zugehoeriger Pool
    SfxStyleFamily          nFamily;        // Familie

    UniString                   aName, aParent, aFollow;
    String                  aHelpFile;      // Name der Hilfedatei
    SfxItemSet*             pSet;           // ItemSet
    USHORT                  nMask;          // Flags

    ULONG                   nHelpId;        // Hilfe-ID

    BOOL                    bMySet;         // TRUE: Set loeschen im dtor

    SfxStyleSheetBase( const UniString&, SfxStyleSheetBasePool&,
                        SfxStyleFamily eFam, USHORT mask );
    SfxStyleSheetBase( const SfxStyleSheetBase& );
    virtual ~SfxStyleSheetBase();
    virtual void Load( SvStream&, USHORT );
    virtual void Store( SvStream& ) {}

public:
    TYPEINFO();
    virtual const UniString& GetName() const;
    virtual BOOL SetName( const UniString& );
    virtual const UniString& GetParent() const;
    virtual BOOL SetParent( const UniString& );
    virtual const UniString& GetFollow() const;
    virtual BOOL SetFollow( const UniString& );
    virtual BOOL HasFollowSupport() const;      // Default TRUE
    virtual BOOL HasParentSupport() const;      // Default TRUE
    virtual BOOL HasClearParentSupport() const; // Default FALSE
    virtual BOOL IsUsed() const;                // Default TRUE
        // Default aus dem Itemset; entweder dem uebergebenen
        // oder aus dem per GetItemSet() zurueckgelieferten Set
    virtual UniString GetDescription();
    virtual UniString GetDescription( SfxMapUnit eMetric );

    SfxStyleSheetBasePool& GetPool() { return rPool;   }
    SfxStyleFamily GetFamily() const     { return nFamily; }
    USHORT   GetMask() const     { return nMask; }
    void     SetMask( USHORT mask) { nMask = mask; }
    BOOL   IsUserDefined() const
           { return BOOL( ( nMask & SFXSTYLEBIT_USERDEF) != 0 ); }

    virtual ULONG GetHelpId( String& rFile );
    virtual void   SetHelpId( const String& r, ULONG nId );

    virtual SfxItemSet& GetItemSet();
    virtual USHORT GetVersion() const;
};

//=========================================================================

typedef ::std::vector< SfxStyleSheetBase* > SfxStyles;

//=========================================================================

class  SfxStyleSheetIterator

/*  [Beschreibung]

    Klasse zum Iterieren und Suchen auf einem SfxStyleSheetBasePool.

*/

{
public:
    SfxStyleSheetIterator(SfxStyleSheetBasePool *pBase,
                          SfxStyleFamily eFam, USHORT n=0xFFFF );
    virtual USHORT GetSearchMask() const;
    virtual SfxStyleFamily GetSearchFamily() const;
    virtual USHORT Count();
    virtual SfxStyleSheetBase *operator[](USHORT nIdx);
    virtual SfxStyleSheetBase* First();
    virtual SfxStyleSheetBase* Next();
    virtual SfxStyleSheetBase* Find(const UniString& rStr);
    virtual ~SfxStyleSheetIterator();

protected:

    SfxStyleSheetBasePool*  pBasePool;
    SfxStyleFamily          nSearchFamily;
    USHORT                  nMask;
    BOOL                    SearchUsed() const { return bSearchUsed; }

private:
    USHORT                  GetPos(){return nAktPosition;}
    BOOL                    IsTrivialSearch();
    BOOL                    DoesStyleMatch(SfxStyleSheetBase *pStyle);

    void*                   pImp;
    SfxStyleSheetBase*      pAktStyle;
    USHORT                  nAktPosition;
    BOOL                    bSearchUsed;

friend class SfxStyleSheetBasePool;
};

//=========================================================================

class SfxStyleSheetBasePool_Impl;

class  SfxStyleSheetBasePool: public SfxBroadcaster
{
friend class SfxStyleSheetIterator;
friend class SfxStyleSheetBase;

    SfxStyleSheetBasePool_Impl *pImp;

private:
    BOOL                        Load1_Impl( SvStream& );
    SfxStyleSheetIterator&      GetIterator_Impl();
protected:
    String                      aAppName;
    SfxItemPool&                rPool;
    SfxStyles                   aStyles;
    SfxStyleFamily              nSearchFamily;
    USHORT                      nMask;

    SfxStyleSheetBase&          Add( SfxStyleSheetBase& );
    void                        ChangeParent( const UniString&, const UniString&, BOOL bVirtual = TRUE );
    virtual SfxStyleSheetBase*  Create( const UniString&, SfxStyleFamily, USHORT );
    virtual SfxStyleSheetBase*  Create( const SfxStyleSheetBase& );

public:
                                SfxStyleSheetBasePool( SfxItemPool& );
                                SfxStyleSheetBasePool( const SfxStyleSheetBasePool& );
                                ~SfxStyleSheetBasePool();

    static String               GetStreamName();

    const String&               GetAppName() const { return aAppName;   }

    SfxItemPool&                GetPool();
    const SfxItemPool&          GetPool() const;

    virtual SfxStyleSheetIterator* CreateIterator(SfxStyleFamily, USHORT nMask);
    virtual USHORT              Count();
    virtual SfxStyleSheetBase*  operator[](USHORT nIdx);

    virtual SfxStyleSheetBase&  Make(const UniString&,
                                     SfxStyleFamily eFam,
                                     USHORT nMask = 0xffff ,
                                     USHORT nPos = 0xffff);

    VIRTUAL510 void             Replace(
        SfxStyleSheetBase& rSource, SfxStyleSheetBase& rTarget );
    virtual SfxStyleSheetBase * Remove( SfxStyleSheetBase* );
    virtual void                Insert( SfxStyleSheetBase* );

    virtual void                Erase( SfxStyleSheetBase* );
    virtual void                Clear();

    SfxStyleSheetBasePool&      operator=( const SfxStyleSheetBasePool& );
    SfxStyleSheetBasePool&      operator+=( const SfxStyleSheetBasePool& );

    SfxStyles&                  GetStyles() { return aStyles; }
    virtual SfxStyleSheetBase*  First();
    virtual SfxStyleSheetBase*  Next();
    virtual SfxStyleSheetBase*  Find( const UniString&,
                                      SfxStyleFamily eFam, USHORT n=0xFFFF );
    virtual BOOL                SetParent(SfxStyleFamily eFam,
                                          const UniString &rStyle,
                                          const UniString &rParent);

    SfxStyleSheetBase*          Find(const UniString& rStr)
                                { return Find(rStr, nSearchFamily, nMask); }

    void                        SetSearchMask(SfxStyleFamily eFam, USHORT n=0xFFFF );
    USHORT                      GetSearchMask() const;
    SfxStyleFamily              GetSearchFamily() const  { return nSearchFamily; }

    BOOL                        Load( SvStream& );
    BOOL Store( SvStream&, BOOL /*bUsed*/ = TRUE ) {return FALSE;}
};

//=========================================================================

class  SfxStyleSheet: public SfxStyleSheetBase,
                     public SfxListener, public SfxBroadcaster
{
public:
                        TYPEINFO();

                        SfxStyleSheet( const UniString&, SfxStyleSheetBasePool&, SfxStyleFamily, USHORT );
                        SfxStyleSheet( const SfxStyleSheet& );

    virtual             ~SfxStyleSheet();

    virtual void        SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                                const SfxHint& rHint, const TypeId& rHintType );
    virtual BOOL        SetParent( const UniString& );
};

//=========================================================================

class  SfxStyleSheetPool: public SfxStyleSheetBasePool
{
protected:
    using SfxStyleSheetBasePool::Create;
    virtual SfxStyleSheetBase* Create(const UniString&, SfxStyleFamily, USHORT mask);
    virtual SfxStyleSheetBase* Create(const SfxStyleSheet &);

public:
    SfxStyleSheetPool( SfxItemPool& );

//  virtual BOOL CopyTo(SfxStyleSheetPool &rDest, const String &rSourceName);
};

//=========================================================================

#define SFX_STYLESHEET_CREATED       1  // neu
#define SFX_STYLESHEET_MODIFIED      2  // ver"andert
#define SFX_STYLESHEET_CHANGED       3  // gel"oscht und neu (ausgetauscht)
#define SFX_STYLESHEET_ERASED        4  // gel"oscht
#define SFX_STYLESHEET_INDESTRUCTION 5  // wird gerade entfernt

#define SFX_STYLESHEETPOOL_CHANGES  1  // Aenderungen, die den Zustand
                                       // des Pools anedern, aber nicht
                                       // ueber die STYLESHEET Hints
                                       // verschickt werden sollen.

//========================================================================

class  SfxStyleSheetPoolHint : public SfxHint
{
    USHORT nHint;

public:
    TYPEINFO();

                        SfxStyleSheetPoolHint(USHORT nArgHint) :  nHint(nArgHint){}
    USHORT              GetHint() const
                        { return nHint; }
};

//=========================================================================

class  SfxStyleSheetHint: public SfxHint
{
    SfxStyleSheetBase*  pStyleSh;
    USHORT              nHint;

public:
                        TYPEINFO();

                        SfxStyleSheetHint( USHORT, SfxStyleSheetBase& );
    SfxStyleSheetBase*  GetStyleSheet() const
                        { return pStyleSh; }
    USHORT              GetHint() const
                        { return nHint; }
};

class  SfxStyleSheetHintExtended: public SfxStyleSheetHint
{
    String              aName;

public:
                        TYPEINFO();

                        SfxStyleSheetHintExtended(
                            USHORT, const String& rOld,
                            SfxStyleSheetBase& );
    const String&       GetOldName() { return aName; }
};

}

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
