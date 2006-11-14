/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: app.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: ihi $ $Date: 2006-11-14 12:20:00 $
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
#ifndef _OFF_APP_HXX
#define _OFF_APP_HXX

// include ---------------------------------------------------------------

#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
class SvStringsDtor;
class SimpleResMgr;
namespace binfilter {

// defines ---------------------------------------------------------------

#define SFX_INTERFACE_OFFAPP SFX_INTERFACE_OFA_START

#define ADDRPI_BTN_INSERT   1
#define ADDRPI_BTN_MERGE    2

#define OFA_REFERER         "private:user"

// forward ---------------------------------------------------------------

class MailServer;
class OfaHtmlOptions;
class OfaAutoCorrCfg;
class SvxAutoCorrect;

//class BasicIDE;
class SchDLL;
class SimDLL;
class SmDLL;
class XColorTable;
class XOutdevItemPool;
class OfaTabAppearanceCfg;
class CntAnchor;
class SfxTabPage;

class OfaFilterOptions;

class  OfficeData_Impl;
struct ConvertData;

// struct OfficeAppl_Impl ------------------------------------------------

#if _SOLAR__PRIVATE
struct OfficeAppl_Impl
{
    ResMgr*             pResMgr;
    SfxObjectFactory*   pOffMessageDoc_ImplFactory;
    SimpleResMgr*       m_pThreadSafeRessources;

    OfficeAppl_Impl() :
        pResMgr( NULL ),
        pOffMessageDoc_ImplFactory( NULL ),
        m_pThreadSafeRessources( NULL )
    {}
};
#else
struct OfficeAppl_Impl;
#endif

// class OfficeApplication -----------------------------------------------

class OfficeApplication : public SfxApplication
{
private:
    OfficeAppl_Impl*    pImpl;            // "offentlich f"ur SFX-Makros
    OfficeData_Impl*    pDataImpl;        // privat
    USHORT              nAddrButtonFlags; // welche Buttons vom Adressbuch sind
    Link                aSbaCreatedLink;

#if _SOLAR__PRIVATE
                                 DECL_LINK( ImplGetAutoCorrect, void* );
                                DECL_LINK( ChangeUserDataHdl_Impl, void* );
                                DECL_LINK( GlobalBasicErrorHdl, StarBASIC* );
#endif

#if _SOLAR__PRIVATE
    void                        CreateDataImpl();
    void                        DeleteDataImpl();

    void *                      GetSSOCreator( void );

public:
    void                        WriterExec_Impl( SfxRequest &rReq );
    void                        DrawExec_Impl( SfxRequest &rReq );
    void                        BaseExec_Impl( SfxRequest &rReq );
    void                        ModuleState_Impl( SfxItemSet &rState );
    void                        Execute_Impl( SfxRequest &rReq );
     void                       GetState_Impl( SfxItemSet &rState );
     void                       ExecuteApp_Impl( SfxRequest &rReq );
    void                        GetStateApp_Impl( SfxItemSet &rState );
    void                        ExecAPI_Impl( SfxRequest &rReq );
    void                        StateAPI_Impl( SfxItemSet &rState );
#endif

protected:
#if SUPD<590
    virtual void                Main( );
#endif
    virtual void                Init( );
    virtual void                Exit();

public:
                                TYPEINFO();
                                SFX_DECL_INTERFACE(SFX_INTERFACE_OFFAPP);

                                OfficeApplication();
                                ~OfficeApplication();

#if SUPD<590
    virtual SbxObject*          GetSbxObject();
#endif

    ResMgr*                     GetOffResManager();

    OfaHtmlOptions*             GetHtmlOptions();
    OfaFilterOptions*           GetFilterOptions();
    //BasicIDE*                 GetBasicIDE();

    // Autokorrektur
    OfaAutoCorrCfg*             GetAutoCorrConfig();
    SvxAutoCorrect*             GetAutoCorrect();

    // Config
    OfaTabAppearanceCfg*        GetTabAppearanceConfig();
    void                        UseFontSubst();

    // ColorTable
    XColorTable*                GetStdColorTable();

    static void                 InitMailServer( MailServer* pServer );
    static BOOL                 GetEmailNames( SvStringsDtor& rNameList );


    //TreeOptionsDialog

#if _SOLAR__PRIVATE
    OfficeAppl_Impl*            Get_Impl() { return pImpl; }
#endif

};

#define OFF_APP()   ( (OfficeApplication*)SfxGetpApp() )

} //namespace binfilter
#endif // #ifndef _OFF_APP_HXX

