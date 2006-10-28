/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: shell.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 03:09:03 $
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
#ifndef _SFX_SHELL_HXX
#define _SFX_SHELL_HXX

#ifndef _DEBUG_HXX //autogen
#include <tools/debug.hxx>
#endif
#ifndef _RTTI_HXX //autogen
#include <tools/rtti.hxx>
#endif
#ifndef _SFXBRDCST_HXX //autogen
#include <svtools/brdcst.hxx>
#endif

class ResMgr;
class Window;
class ToolBox;
class SfxItemPool;
class SfxPoolItem;
class SfxItemSet;
class StatusBar;
class SvGlobalName;
class SvVerbList;
class SfxUndoManager;
class SfxRepeatTarget;
class SbxVariable;
class SbxBase;
namespace binfilter {
class SfxRequest;
struct SfxFormalArgument;
class SfxInterface;
class SfxViewShell;
class SfxObjectShell;
class SfxSlotPool;

class SfxShellObject;
class SfxShell;
struct SfxShell_Impl;
struct SfxTypeLibImpl;
class SfxShellObject;
class SfxShellSubObject;
class SfxDispatcher;
class SfxViewFrame;
class SfxSlot;
class SfxBindings;

//====================================================================

enum SfxInterfaceId

/*  [Beschreibung]

    Id f"ur die <SfxInterface>s, damit wird "uber ein Array an der
    <SfxApplication> ein quasi-statischer Zugriff auf die Interfaces
    erlaubt.
*/

{
    SFX_INTERFACE_NONE,
    SFX_INTERFACE_SFXAPP,
    SFX_INTERFACE_SFXDOCSH,
    SFX_INTERFACE_SFXTOPFRM,
    SFX_INTERFACE_SFXIPFRM,
    SFX_INTERFACE_SFXVIEWSH,
    SFX_INTERFACE_SFXVIEWFRM,
    SFX_INTERFACE_SFXPLUGINFRM,
    SFX_INTERFACE_SFXPLUGINOBJ,
    SFX_INTERFACE_SFXPLUGINVIEWSH,
    SFX_INTERFACE_SFXFRAMESETOBJ,
    SFX_INTERFACE_SFXFRAMESETVIEWSH,
    SFX_INTERFACE_SFXINTERNALFRM,
    SFX_INTERFACE_SFXCOMPONENTDOCSH,
    SFX_INTERFACE_SFXGENERICOBJ,
    SFX_INTERFACE_SFXGENERICVIEWSH,
    SFX_INTERFACE_SFXEXPLOBJ,
    SFX_INTERFACE_SFXEXPLVIEWSH,
    SFX_INTERFACE_SFXPLUGINVIEWSHDYNAMIC,
    SFX_INTERFACE_SFXEXTERNALVIEWFRM,
    SFX_INTERFACE_SFXMODULE,
    SFX_INTERFACE_SFXFRAMESETVIEW,
    SFX_INTERFACE_SFXFRAMESETSOURCEVIEW,
    SFX_INTERFACE_SFXHELP_DOCSH,
    SFX_INTERFACE_SFXHELP_VIEWSH,
    SFX_INTERFACE_SFXTASK,
    SFX_INTERFACE_OFA_START         =  100,
    SFX_INTERFACE_OFA_END           =  100,
    SFX_INTERFACE_SC_START          =  150,
    SFX_INTERFACE_SC_END            =  199,
    SFX_INTERFACE_SD_START          =  200,
    SFX_INTERFACE_SD_END            =  249,
    SFX_INTERFACE_SW_START          =  250,
    SFX_INTERFACE_SW_END            =  299,
    SFX_INTERFACE_SIM_START         =  300,
    SFX_INTERFACE_SIM_END           =  319,
    SFX_INTERFACE_SCH_START         =  320,
    SFX_INTERFACE_SCH_END           =  339,
    SFX_INTERFACE_SMA_START         =  340,
    SFX_INTERFACE_SMA_END           =  359,
    SFX_INTERFACE_SBA_START         =  360,
    SFX_INTERFACE_SBA_END           =  399,
    SFX_INTERFACE_IDE_START         =  400,
    SFX_INTERFACE_IDE_END           =  409,
    //-falls die noch einer braucht
    SFX_INTERFACE_APP               =  SFX_INTERFACE_SW_START,
    SFX_INTERFACE_LIB               =  450
};

//====================================================================

typedef void (*SfxExecFunc)(SfxShell *, SfxRequest &rReq);
typedef void (*SfxStateFunc)(SfxShell *, SfxItemSet &rSet);

class SfxShell: public SfxBroadcaster

/*  [Beschreibung]

    Die Klasse SfxShell ist Basisklasse f"ur alle Schichten, die
    Funktionalit"at Form von <Slot>s bereitstellen wollen.

    Jede Instanz hat einen Verweis auf eine Interface-Beschreibung, der
    mit <SfxShell::GetInterface()const> erh"altlich ist. Dieses Interface
    stellt die Verbindung zu konkreten Methoden her und enth"alt einige
    weitere beschreibende Daten f"ur Controller wie Menus und Toolboxen, aber
    auch f"ur die diversen APIs. Der Hautpteil der Interface-Beschreibung
    liegt in Form einer <Type-Library> vor, die mit dem <SVIDL-Compiler>
    aus einem IDL-File generiert wird. F"ur jede SfxShell-Subclass ist ein
    solches IDL-File zu schreiben.

*/

{
    friend class SfxObjectItem;

    SfxShell_Impl*              pImp;
    SfxItemPool*                pPool;
    SfxUndoManager*             pUndoMgr;

private:
                                SfxShell( const SfxShell & ); // n.i.
    SfxShell&                   operator = ( const SfxShell & ); // n.i.

protected:
                                SfxShell();
                                SfxShell( SfxViewShell *pViewSh );

    static SfxInterface*        _GetInterfaceImpl() { return 0; }

#ifndef _SFXSH_HXX
    void                        SetViewShell_Impl( SfxViewShell* pView );
    void                        Invalidate_Impl( SfxBindings& rBindings, USHORT nId );
    SfxShellObject*             GetShellObj_Impl() const;
    void                        SetShellObj_Impl( SfxShellObject* pObj );
#endif

public:
                                TYPEINFO();
    virtual                     ~SfxShell();

    SfxBroadcaster*             GetBroadcaster();

    virtual SvGlobalName        GetGlobalName() const;
    virtual SfxInterface*       GetInterface() const;
    void                        SetName( const String &rName );
    const String&               GetName() const;

    SfxViewShell*               GetViewShell() const;

    void                        CallExec( SfxExecFunc pFunc, SfxRequest &rReq )
                                { (*pFunc)(this, rReq); }
    void                        CallState( SfxStateFunc pFunc, SfxItemSet &rSet )
                                { (*pFunc)(this, rSet); }

    static void                 EmptyExecStub(SfxShell *pShell, SfxRequest &);
    static void                 EmptyStateStub(SfxShell *pShell, SfxItemSet &);

    const SfxPoolItem*          GetSlotState( USHORT nSlotId, const SfxInterface *pIF = 0, SfxItemSet *pStateSet = 0 );
    const SfxPoolItem*          ExecuteSlot( SfxRequest &rReq, const SfxInterface *pIF = 0 );
    const SfxPoolItem*          ExecuteSlot( SfxRequest &rReq, BOOL bAsync );
    ULONG                       ExecuteSlot( USHORT nSlot, USHORT nMemberId, SbxVariable& rRet, SbxBase* pArgs = 0 );

    inline SfxItemPool&         GetPool() const;
    inline void                 SetPool( SfxItemPool *pNewPool ) ;

    virtual SfxUndoManager*     GetUndoManager();
    void                        SetUndoManager( SfxUndoManager *pNewUndoMgr );

    SfxRepeatTarget*            GetRepeatTarget() const;
    void                        SetRepeatTarget( SfxRepeatTarget *pTarget );
#if SUPD>603
    virtual
#endif
            void                Invalidate(USHORT nId = 0);

            void                DoActivate( SfxViewFrame *pFrame, BOOL bMDI);
            void                DoDeactivate( SfxViewFrame *pFrame, BOOL bMDI);
    BOOL                        IsActive() const;
    virtual void                Activate(BOOL bMDI);
    virtual void                Deactivate(BOOL bMDI);
    virtual void                ParentActivate();
    virtual void                ParentDeactivate();

    SfxDispatcher*              GetDispatcher() const;
    SfxViewFrame*               GetFrame() const;
    ResMgr*                     GetResMgr() const;
    virtual BOOL                HasUIFeature( ULONG nFeature );
    void                        UIFeatureChanged();

    // Items
    const SfxPoolItem*          GetItem( USHORT nSlotId ) const;
    void                        PutItem( const SfxPoolItem& rItem );
    void                        RemoveItem( USHORT nSlotId );

    virtual void                FillStatusBar( StatusBar& );
    void                        SetVerbs(const SvVerbList *pVerbs);
    const SvVerbList*           GetVerbs() const;
    void                        VerbExec (SfxRequest&);
    void                        VerbState (SfxItemSet&);

    const SfxSlot*              GetVerbSlot_Impl(USHORT nId) const;
    void                        SetHelpId(ULONG nId);
    ULONG                       GetHelpId() const;
    virtual SfxObjectShell*     GetObjectShell();
    void                        SetDisableFlags( ULONG nFlags );
    ULONG                       GetDisableFlags() const;

    virtual SfxItemSet*         CreateItemSet( USHORT nId );
    virtual void                ApplyItemSet( USHORT nId, const SfxItemSet& rSet );

#ifndef _SFXSH_HXX
    FASTBOOL                    CanExecuteSlot_Impl( const SfxSlot &rSlot );
    SfxSlotPool&                GetSlotPool_Impl() const;
#endif
};

//--------------------------------------------------------------------
SfxItemPool& SfxShell::GetPool() const
/*
  [Beschreibung]

    Jede Subclass von SfxShell mu"s einen Pool referenzieren. Dieser
    wird teilweise von SFx-eigenen Subklassen gesetzt (z.B. <SfxViewShell>),
    mu"s aber insbesondere bei direkt von SfxShell abgeleiteten Klassen
    und bei Ableitungen von SfxObjectShell selbst gesetzt werden.

    Die Klasse SfxShell selbst hat noch keinen SfxItemPool, es wird
    daher ein 0-Pointer zur"uckgeliefert.
*/

{
    DBG_ASSERT( pPool, "no pool" );
    return *pPool;
}
//-------------------------------------------------------------------
inline void SfxShell::SetPool
(
    SfxItemPool*    pNewPool    // Pointer auf den neuen Pool oder 0
)

/*  [Beschreibung]

    Mit dieser Methode melden die Subklassen ihren speziellen <SfxItemPool>
    an der SfxShell an. Jede SfxShell Instanz mu\s Zugriff auf einen
    SfxItemPool haben. In der Regel ist dies der SfxItemPool der
    SfxDocumentShell. Die SfxShell Subklasse "ubernimmt nicht die
    Eigent"umerschaft "uber den "ubergebenen Pool. Bevor er gel"oscht
    wirde, mu\s er mit SetPool(0) abgemeldet werden.
*/

{
    pPool = pNewPool;
}

//=====================================================================

#define SFX_ARGUMENTMAP(ShellClass) static SfxFormalArgument __FAR_DATA a##ShellClass##Args_Impl[] =

#define SFX_SLOTMAP(ShellClass) static SfxFormalArgument __FAR_DATA a##ShellClass##Args_Impl[1]; \
                                static SfxSlot __FAR_DATA a##ShellClass##Slots_Impl[] =

#define SFX_SLOTMAP_ARG(ShellClass) static SfxSlot __FAR_DATA a##ShellClass##Slots_Impl[] =

#define SFX_DECL_INTERFACE(nId)                                             \
            static SfxInterfaceId               nClassId;                   \
        private:                                                            \
            static void                         InitInterface_Impl();       \
        protected:                                                          \
            static SfxInterface*                _GetInterfaceImpl();        \
        public:                                                             \
            static SfxInterfaceId               _GetInterfaceIdImpl()       \
                                                { return SfxInterfaceId(nId); } \
            static const SfxFormalArgument     *pSfxFormalArgs_Impl;        \
            virtual SfxInterface*               GetInterface() const;       \
            static void                         RegisterInterface(SfxModule* pMod=NULL)

#define SFX_IMPL_INTERFACE(Class,SuperClass, NameResId)                     \
                                                                            \
    SfxInterfaceId Class::nClassId = SFX_INTERFACE_NONE;                    \
    const SfxFormalArgument* Class::pSfxFormalArgs_Impl = a##Class##Args_Impl;\
                                                                            \
    SfxInterface* Class::_GetInterfaceImpl()                                \
    { return SFX_APP()->GetInterfaceByIdImpl(_GetInterfaceIdImpl()); }      \
                                                                            \
    SfxInterface* __EXPORT Class::GetInterface() const                      \
        { return _GetInterfaceImpl(); }                                     \
                                                                            \
    void Class::RegisterInterface(SfxModule* pMod)                                      \
        {   SFX_APP()->SetInterfaceByIdImpl(_GetInterfaceIdImpl(),          \
            new SfxInterface( pMod,                                         \
                #Class, NameResId, _GetInterfaceIdImpl(),                   \
                SuperClass::_GetInterfaceImpl(),                            \
                NULL,                                                       \
                a##Class##Slots_Impl[0],                                    \
                (USHORT) (sizeof(a##Class##Slots_Impl) / sizeof(SfxSlot) ) ) );\
            InitInterface_Impl();                                           \
            _GetInterfaceImpl()->LoadConfig();                              \
        }                                                                   \
                                                                            \
    void Class::InitInterface_Impl()

#define SFX_POSITION_MASK               0x000F
#define SFX_VISIBILITY_MASK             0xFFF0
#define SFX_VISIBILITY_UNVISIBLE        0x0000  // nie sichtbar
#define SFX_VISIBILITY_PLUGSERVER       0x0010
#define SFX_VISIBILITY_PLUGCLIENT       0x0020
#define SFX_VISIBILITY_VIEWER           0x0040
                                                // noch 1 sind frei!
#define SFX_VISIBILITY_RECORDING        0x0200
#define SFX_VISIBILITY_READONLYDOC      0x0400
#define SFX_VISIBILITY_DESKTOP          0x0800
#define SFX_VISIBILITY_STANDARD         0x1000
#define SFX_VISIBILITY_FULLSCREEN       0x2000
#define SFX_VISIBILITY_CLIENT           0x4000
#define SFX_VISIBILITY_SERVER           0x8000
#define SFX_VISIBILITY_NOCONTEXT        0xFFFF  // immer sichtbar

#define SFX_OBJECTBAR_REGISTRATION(nPos,rResId) \
        _GetInterfaceImpl()->RegisterObjectBar( nPos, rResId )

#define SFX_FEATURED_OBJECTBAR_REGISTRATION(nPos,rResId,nFeature) \
        _GetInterfaceImpl()->RegisterObjectBar( nPos, rResId, nFeature )

#define SFX_CHILDWINDOW_REGISTRATION(nId) \
        _GetInterfaceImpl()->RegisterChildWindow( nId, (BOOL) FALSE )

#define SFX_FEATURED_CHILDWINDOW_REGISTRATION(nId,nFeature) \
        _GetInterfaceImpl()->RegisterChildWindow( nId, (BOOL) FALSE, nFeature )

#define SFX_CHILDWINDOW_CONTEXT_REGISTRATION(nId) \
        _GetInterfaceImpl()->RegisterChildWindow( nId, (BOOL) TRUE )

#define SFX_POPUPMENU_REGISTRATION(rResId) \
        _GetInterfaceImpl()->RegisterPopupMenu( rResId )

#define SFX_OBJECTMENU_REGISTRATION(nPos,rResId) \
        _GetInterfaceImpl()->RegisterObjectMenu( nPos, rResId )

#define SFX_STATUSBAR_REGISTRATION(rResId) \
        _GetInterfaceImpl()->RegisterStatusBar( rResId )

}//end of namespace binfilter
#endif

