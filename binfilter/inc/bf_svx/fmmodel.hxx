/*************************************************************************
 *
 *  $RCSfile: fmmodel.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:35 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _SVX_FMMODEL_HXX
#define _SVX_FMMODEL_HXX

#if SUPD < 396
#ifndef _SVX_SIVCDRMOD_HXX //autogen
//#include "vcdrmod.hxx"
#endif
#else
#ifndef _SVDMODEL_HXX
#include <bf_svx/svdmodel.hxx>
#endif
#endif

class SvPersist;
class SfxItemPool;
class VCItemPool;
class FmXUndoEnvironment;
class SfxObjectShell;
class SbxObject;
class SbxArray;
class SbxValue;

struct FmFormModelImplData;
class FmFormModel :
    public SdrModel
{
private:
    FmFormModelImplData*    m_pImpl;
//  FmXUndoEnvironment*     pUndoEnv;
    SfxObjectShell*         pObjShell;
    sal_Bool            bStreamingOldVersion;

    sal_Bool            m_bOpenInDesignMode : 1;
    sal_Bool            m_bAutoControlFocus : 1;

//STRIP001  FmFormModel( const FmFormModel& );
//STRIP001  void operator=(const FmFormModel& rSrcModel);
//STRIP001  FASTBOOL operator==(const FmFormModel& rCmpModel) const;

public:
    TYPEINFO();

//STRIP001  FmFormModel(SfxItemPool* pPool=NULL, SvPersist* pPers=NULL );
    FmFormModel(const XubString& rPath, SfxItemPool* pPool=NULL,
                SvPersist* pPers=NULL );
//STRIP001  FmFormModel(SfxItemPool* pPool, SvPersist* pPers, FASTBOOL bUseExtColorTable);
    FmFormModel(const XubString& rPath, SfxItemPool* pPool, SvPersist* pPers,
                FASTBOOL bUseExtColorTable);

    virtual ~FmFormModel();

//STRIP001  virtual SdrPage* AllocPage(FASTBOOL bMasterPage);
    virtual void     InsertPage(SdrPage* pPage, sal_uInt16 nPos=0xFFFF);
    virtual SdrPage* RemovePage(sal_uInt16 nPgNum);
    virtual void     MovePage(USHORT nPgNum, USHORT nNewPos);
    virtual void     InsertMasterPage(SdrPage* pPage, sal_uInt16 nPos=0xFFFF);
    virtual SdrPage* RemoveMasterPage(sal_uInt16 nPgNum);

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrIOHeader& rHead, SvStream& rIn);

    virtual SdrLayerID      GetControlExportLayerId( const SdrObject& rObj ) const;
    SfxObjectShell*         GetObjectShell() const { return pObjShell; }
    void                    SetObjectShell( SfxObjectShell* pShell );

    sal_Bool GetOpenInDesignMode() const { return m_bOpenInDesignMode; }
    void SetOpenInDesignMode( sal_Bool _bOpenDesignMode );

    sal_Bool    GetAutoControlFocus() const { return m_bAutoControlFocus; }
    void        SetAutoControlFocus( sal_Bool _bAutoControlFocus );

    /** check whether the OpenInDesignMode has been set explicitly or been loaded (<FALSE/>)
        or if it still has the default value from construction (<TRUE/>)
    */
    sal_Bool    OpenInDesignModeIsDefaulted( );

#if _SOLAR__PRIVATE
    void        implSetOpenInDesignMode( sal_Bool _bOpenDesignMode, sal_Bool _bForce );

    sal_Bool IsStreamingOldVersion() const { return bStreamingOldVersion; }
    FmXUndoEnvironment& GetUndoEnv();

    XubString GetUniquePageId();
#endif

};

#endif          // _FM_FMMODEL_HXX

