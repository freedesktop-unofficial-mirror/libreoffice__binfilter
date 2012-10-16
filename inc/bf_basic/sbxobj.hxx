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

#ifndef _SBX_SBXOBJECT_HXX
#define _SBX_SBXOBJECT_HXX

#include <bf_svtools/bf_solar.h>


#include <bf_svtools/lstner.hxx>

#include "sbxvar.hxx"

///////////////////////////////////////////////////////////////////////////

namespace binfilter {

class SbxProperty;
class SbxObjectImpl;

class SbxObject : public SbxVariable, public SfxListener
{
    SbxObjectImpl* mpSbxObjectImpl; // Impl data

    SbxArray* FindVar( SbxVariable*, USHORT& );
protected:
    SbxArrayRef  pMethods;          // Methoden
    SbxArrayRef  pProps;            // Properties
    SbxArrayRef  pObjs;             // Objekte
    SbxProperty* pDfltProp;         // Default-Property
    String       aClassName;        // Klassenname
    String       aDfltPropName;
    virtual BOOL LoadData( SvStream&, USHORT );
    virtual BOOL StoreData( SvStream& ) const {return FALSE;}
    virtual ~SbxObject();
    virtual void SFX_NOTIFY( SfxBroadcaster& rBC, const TypeId& rBCType,
                             const SfxHint& rHint, const TypeId& rHintType );
public:
    SBX_DECL_PERSIST_NODATA(SBXCR_SBX,SBXID_OBJECT,1);
    TYPEINFO();
    SbxObject( const String& rClassname );
    SbxObject( const SbxObject& );
    SbxObject& operator=( const SbxObject& );
    virtual SbxDataType GetType() const;
    virtual SbxClassType GetClass() const;
    virtual void Clear();

    virtual BOOL  IsClass( const String& ) const;
    const String& GetClassName() const { return aClassName; }
    void          SetClassName( const String &rNew ) { aClassName = rNew; }
    // Default-Property
    SbxProperty* GetDfltProperty();
    // Suchen eines Elements
    virtual SbxVariable* FindUserData( UINT32 nUserData );
    virtual SbxVariable* Find( const String&, SbxClassType );
    SbxVariable* FindQualified( const String&, SbxClassType );
    // Quick-Call-Interface fuer Methoden
    virtual BOOL Call( const String&, SbxArray* = NULL );
    // Execution von DDE-Kommandos
    SbxVariable* Execute( const String& );
    // Elemente verwalten
    virtual BOOL GetAll( SbxClassType ) { return TRUE; }
    SbxVariable* Make( const String&, SbxClassType, SbxDataType );
    virtual SbxObject* MakeObject( const String&, const String& );
    virtual void Insert( SbxVariable* );
    // AB 23.4.1997, Optimierung, Einfuegen ohne Ueberpruefung auf doppelte
    // Eintraege und ohne Broadcasts, wird nur in SO2/auto.cxx genutzt
    void QuickInsert( SbxVariable* );
    virtual void Remove( const String&, SbxClassType );
    virtual void Remove( SbxVariable* );

    // Makro-Recording
    virtual String GenerateSource( const String &rLinePrefix,
                                   const SbxObject *pRelativeTo );
    // Direktzugriff auf die Arrays
    SbxArray* GetMethods()      { return pMethods;  }
    SbxArray* GetProperties()   { return pProps;    }
    SbxArray* GetObjects()      { return pObjs;     }
    // Debugging
    void Dump( SvStream&, BOOL bDumpAll=FALSE );
};

#ifndef __SBX_SBXOBJECTREF_HXX

#ifndef SBX_OBJECT_DECL_DEFINED
#define SBX_OBJECT_DECL_DEFINED
SV_DECL_REF(SbxObject)
#endif
SV_IMPL_REF(SbxObject)

#endif /* __SBX_SBXOBJECTREF_HXX */

}

#endif /* _SBX_SBXOBJECT_HXX */

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
