/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: saveopt.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:39:07 $
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
#ifndef _SFX_SAVEOPT_HXX
#define _SFX_SAVEOPT_HXX


#ifndef _SV_WINTYPES_HXX //autogen
#include <vcl/wintypes.hxx>
#endif
#ifndef _SV_FIELD_HXX //autogen
#include <vcl/field.hxx>
#endif
#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _SFXPOOLITEM_HXX //autogen
#include <bf_svtools/poolitem.hxx>
#endif
// -----------------------------------------------------------------------
#include "bf_sfx2/cfgitem.hxx"
namespace binfilter {

struct SfxOptions_Impl;

// -----------------------------------------------------------------------
class SfxOptions : public SfxConfigItem
{
#if _SOLAR__PRIVATE
    struct SfxOptions_Impl
    {
        SfxMapUnit  eUserMetric;
        BOOL        bSaveDocWins:1,
                    bSaveDocView:1,
                    bSaveRelINet:1,
                    bSaveRelFSys:1,
                    bAutoHelpAgent:1,
                    bSaveGrfCompr:1,
                    bSaveGrfOrig:1,
                    bWelcomeScreen:1;
        String      aRet;
    };
#endif

    SfxOptions_Impl*pImp;
    String          aDocMgrConfig;
    USHORT          nAutoSaveTime;
    USHORT          nUndoActions;
    FieldUnit       eMetric;
    BOOL            bBackup:1,
                    bAutoSave:1,
                    bDocInfSave:1,
                    bIndepGrfFmt:1,
                    bAutoSavePrompt:1,
                    bSaveWorkingSet:1,
                    bHelpBalloons:1,
                    bHelpTips:1;

private:
    void            SetMetric_Impl( FieldUnit e, BOOL bLoading );

protected:
    virtual int     Load(SvStream&);
    virtual BOOL    Store(SvStream&);
    virtual void    UseDefault();

public:
                    SfxOptions();
                    ~SfxOptions();

    void            SetBackup( BOOL b )         { bBackup = b;SetDefault(FALSE);}
    BOOL            IsBackup() const            { return bBackup;         }
    void            SetAutoSave( BOOL b )       { bAutoSave = b;    SetDefault(FALSE);    }
    BOOL            IsAutoSave() const          { return bAutoSave;       }
    void            SetAutoSavePrompt( BOOL b ) { bAutoSavePrompt = b;SetDefault(FALSE);  }
    BOOL            IsAutoSavePrompt() const    { return bAutoSavePrompt; }
    void            SetAutoSaveTime( USHORT n ) { nAutoSaveTime = n;SetDefault(FALSE);  }
    USHORT          GetAutoSaveTime() const     { return nAutoSaveTime;   }
    void            SetDocInfoSave(BOOL b)      { bDocInfSave = b;   SetDefault(FALSE); }
    BOOL            IsDocInfoSave() const       { return bDocInfSave;     }

    void            SetSaveOriginalGraphics(BOOL b);
    BOOL            IsSaveOriginalGraphics() const;
    void            SetSaveGraphicsCompressed(BOOL b);
    BOOL            IsSaveGraphicsCompressed() const;

    void            SetIndepGrfFmt(BOOL b)      { bIndepGrfFmt = b;   SetDefault(FALSE);}
    BOOL            IsIndepGrfFmt() const       { return bIndepGrfFmt;    }
    void            SetSaveWorkingSet( BOOL b ) { bSaveWorkingSet = b;SetDefault(FALSE);}
    BOOL            IsSaveWorkingSet() const    { return bSaveWorkingSet;         }
    void            SetSaveDocWins( BOOL b );
    BOOL            IsSaveDocWins() const;
    void            SetSaveDocView( BOOL b );
    BOOL            IsSaveDocView() const;
    void            SetAutoHelpAgent( BOOL b );
    BOOL            IsAutoHelpAgent() const;
    void            SetWelcomeScreen( BOOL b );
    BOOL            IsWelcomeScreen() const;

    void            SetMetric(FieldUnit e);
    FieldUnit       GetMetric() const           { return eMetric; }
    SfxMapUnit      GetUserMetric() const;

    void            SetUndoCount(USHORT n)      { nUndoActions = n; SetDefault(FALSE);}
    USHORT          GetUndoCount() const        { return nUndoActions; }

    void            SetHelpBalloons( BOOL b )   { bHelpBalloons = b; SetDefault(FALSE); }
    BOOL            IsHelpBalloons() const      { return bHelpBalloons; }
    void            SetHelpTips( BOOL b )       { bHelpTips = b; SetDefault(FALSE); }
    BOOL            IsHelpTips() const          { return bHelpTips; }

    const String&   GetDocumentManagerConfig() const
                    { return aDocMgrConfig; }
    void            SetDocumentManagerConfig( const String &rConfig )
                    { aDocMgrConfig = rConfig; SetDefault(FALSE); }

    void            SetSaveRelINet( BOOL b );
    BOOL            IsSaveRelINet() const;
    void            SetSaveRelFSys( BOOL b );
    BOOL            IsSaveRelFSys() const;
};

}//end of namespace binfilter
#endif
