/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: frameobj.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 12:18:08 $
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

#ifndef _FRAMEOBJ_HXX
#define _FRAMEOBJ_HXX

#ifndef _IPOBJ_HXX //autogen
#include <so3/ipobj.hxx>
#endif
// auto strip #include <bf_sfx2/app.hxx>
namespace binfilter {

//=========================================================================
struct SfxFrameObject_Impl;
class SfxFrameDescriptor;

struct SfxFrameObjectFactoryPtr
{
    // Ist n"otig, da im SO2_DECL_BASIC_CLASS_DLL-Macro ein Pointer auf
    // eine exportierbare struct/class "ubergeben werden mu\s
    SotFactory *pSfxFrameObjectFactory;
    SfxFrameObjectFactoryPtr();
};

class SfxFrameObject : public SvInPlaceObject
/*  [Beschreibung]

*/
{
    SfxFrameObject_Impl*    pImpl;

#if _SOLAR__PRIVATE
//STRIP001  void                    DataChanged_Impl( BOOL bOnlyEmbedSource );
    DECL_LINK(              NewObjectHdl_Impl, Timer* );
#endif

protected:
    BOOL                    ConstructFrame();
#if SUPD<=628
//STRIP001  virtual void            FillClass( SvGlobalName * pClassName,
//STRIP001                             ULONG * pFormat,
//STRIP001                             String * pAppName,
//STRIP001                             String * pFullTypeName,
//STRIP001                             String * pShortTypeName ) const;
 #else
//STRIP001     virtual void            FillClass( SvGlobalName * pClassName,
//STRIP001                             ULONG * pFormat,
//STRIP001                             String * pAppName,
//STRIP001                             String * pFullTypeName,
//STRIP001                             String * pShortTypeName,
//STRIP001                                long nFileFormat = SOFFICE_FILEFORMAT_CURRENT ) const;
#endif

                            // Protokoll
//STRIP001  virtual void            Open( BOOL bOpen );
//STRIP001  virtual void            InPlaceActivate( BOOL );
//STRIP001  virtual ErrCode         Verb( long, SvEmbeddedClient * pCallerClient,
//STRIP001                              Window * pWin, const Rectangle * pWorkRectPixel );

                            // Datenaustausch
//STRIP001  virtual void            SetVisArea( const Rectangle & rVisArea );
//STRIP001  virtual Rectangle       GetVisArea( USHORT nAspect ) const;
//STRIP001  virtual void            Draw( OutputDevice *,
//STRIP001                              const JobSetup & rSetup,
//STRIP001                              USHORT nAspect = ASPECT_CONTENT );

                            // Laden speichern
//STRIP001  virtual BOOL            InitNew( SvStorage * );
    virtual BOOL            Load( SvStorage * );
    virtual BOOL            Save();
    virtual BOOL            SaveAs( SvStorage * );
//STRIP001  virtual void            HandsOff();
    virtual BOOL            SaveCompleted( SvStorage * );

                            ~SfxFrameObject();
public:

    static SfxFrameObjectFactoryPtr*
                            GetFactoryPtr();

                            // Macro mu\s exportiert werden, sonst geht das
                            // SO2-RTTI schief, da GetFactoryAdress() die
                            // Factory-Adresse der Basisklasse liefert.
                            // Da das zweite Argument in einer Inline-Funktion
                            // verwendet wird, mu\s dieses exportierbare
                            // Funktionsaufrufe verwenden, also nicht z.B.
                            // SFX_APP()->Get_Impl()
                            SO2_DECL_BASIC_CLASS_DLL(SfxFrameObject, GetFactoryPtr())

                            SfxFrameObject();

//STRIP001  virtual ULONG           GetMiscStatus() const;
//STRIP001  virtual BOOL            IsLink() const;
    void                    SetFrameDescriptor( const SfxFrameDescriptor*);
    const SfxFrameDescriptor*
                            GetFrameDescriptor() const;
//STRIP001  SfxFrame*               GetFrame() const;

#if _SOLAR__PRIVATE
//STRIP001  void                    ReleaseFrame_Impl();
#endif
};

inline SfxFrameObjectFactoryPtr::SfxFrameObjectFactoryPtr()
    : pSfxFrameObjectFactory(0)     // sonst funzt ClassFactory() nicht!
{
    // hier Factory nicht erzeugen, da GetFactoryPtr() erst nach Beenden dieses
    // ctors einen vern"unftigen Wert liefern kann!
}

SO2_DECL_IMPL_REF(SfxFrameObject)

//STRIP001 class SfxInsertFloatingFrameDialog
//STRIP001 {
//STRIP001  Window*             pParentWindow;
//STRIP001 public://STRIP001
//STRIP001                      SfxInsertFloatingFrameDialog( Window *pParent );
//STRIP001  SvInPlaceObjectRef  Execute( SvStorage* pStor );
//STRIP001 };

}//end of namespace binfilter
#endif
