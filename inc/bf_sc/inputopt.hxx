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

#ifndef SC_INPUTOPT_HXX
#define SC_INPUTOPT_HXX


#include <unotools/configitem.hxx>

#include <bf_svtools/bf_solar.h>

class SvStream;

namespace binfilter {

class ScInputOptions
{
private:
    USHORT      nMoveDir;           // enum ScDirection
    BOOL        bMoveSelection;
    BOOL        bEnterEdit;
    BOOL        bExtendFormat;
    BOOL        bRangeFinder;
    BOOL        bExpandRefs;
    BOOL        bMarkHeader;
    BOOL        bUseTabCol;
    BOOL        bTextWysiwyg;
    BOOL        bReplCellsWarn;

public:
                ScInputOptions();
                ScInputOptions( const ScInputOptions& rCpy );
                ~ScInputOptions();

    void        SetDefaults();

    void        SetMoveDir(USHORT nNew)         { nMoveDir = nNew;       }
    USHORT      GetMoveDir() const              { return nMoveDir;       }
    void        SetMoveSelection(BOOL bSet)     { bMoveSelection = bSet; }
    BOOL        GetMoveSelection() const        { return bMoveSelection; }
    void        SetEnterEdit(BOOL bSet)         { bEnterEdit = bSet;     }
    BOOL        GetEnterEdit() const            { return bEnterEdit;     }
    void        SetExtendFormat(BOOL bSet)      { bExtendFormat = bSet;  }
    BOOL        GetExtendFormat() const         { return bExtendFormat;  }
    void        SetRangeFinder(BOOL bSet)       { bRangeFinder = bSet;   }
    BOOL        GetRangeFinder() const          { return bRangeFinder;   }
    void        SetExpandRefs(BOOL bSet)        { bExpandRefs = bSet;    }
    BOOL        GetExpandRefs() const           { return bExpandRefs;    }
    void        SetMarkHeader(BOOL bSet)        { bMarkHeader = bSet;    }
    BOOL        GetMarkHeader() const           { return bMarkHeader;    }
    void        SetUseTabCol(BOOL bSet)         { bUseTabCol = bSet;     }
    BOOL        GetUseTabCol() const            { return bUseTabCol;     }
    void        SetTextWysiwyg(BOOL bSet)       { bTextWysiwyg = bSet;   }
    BOOL        GetTextWysiwyg() const          { return bTextWysiwyg;   }
    void        SetReplaceCellsWarn(BOOL bSet)  { bReplCellsWarn = bSet; }
    BOOL        GetReplaceCellsWarn() const     { return bReplCellsWarn; }

    const ScInputOptions&   operator=   ( const ScInputOptions& rOpt );
/*N*/   friend SvStream&        operator>>  ( SvStream& rStream, ScInputOptions& rOpt );
/*N*/   friend SvStream&        operator<<  ( SvStream& rStream, const ScInputOptions& rOpt );
};


//==================================================================
// CfgItem fuer Eingabe-Optionen
//==================================================================

class ScInputCfg : public ScInputOptions,
    public ::utl::ConfigItem
{
    ::com::sun::star::uno::Sequence<rtl::OUString> GetPropertyNames();

public:
            ScInputCfg();

    virtual void                Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& aPropertyNames );
    virtual void                Commit();
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
