/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: frameobj.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:59:44 $
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
    DECL_LINK(              NewObjectHdl_Impl, Timer* );
#endif

protected:
    BOOL                    ConstructFrame();
#if SUPD<=628
 #else
#endif

                            // Protokoll

                            // Datenaustausch

                            // Laden speichern
    virtual BOOL            Load( SvStorage * );
    virtual BOOL            Save();
    virtual BOOL            SaveAs( SvStorage * );
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

    void                    SetFrameDescriptor( const SfxFrameDescriptor*);
    const SfxFrameDescriptor*
                            GetFrameDescriptor() const;

#if _SOLAR__PRIVATE
#endif
};

inline SfxFrameObjectFactoryPtr::SfxFrameObjectFactoryPtr()
    : pSfxFrameObjectFactory(0)     // sonst funzt ClassFactory() nicht!
{
    // hier Factory nicht erzeugen, da GetFactoryPtr() erst nach Beenden dieses
    // ctors einen vern"unftigen Wert liefern kann!
}

SO2_DECL_IMPL_REF(SfxFrameObject)


}//end of namespace binfilter
#endif
