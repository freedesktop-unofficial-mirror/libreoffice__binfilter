/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: factory.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 14:24:02 $
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

#ifndef _FACTORY_HXX
#define _FACTORY_HXX

#ifndef _LIST_HXX //autogen
#include <tools/list.hxx>
#endif
#include <bf_so3/so2ref.hxx>
#ifndef _SFXBRDCST_HXX //autogen
#include <svtools/brdcst.hxx>
#endif
#ifndef _GLOBNAME_HXX //autogen
#include <tools/globname.hxx>
#endif
#ifndef _SOT_FACTORY_HXX
#include <sot/factory.hxx>
#endif
#ifndef _COM_SUN_STAR_DATATRANSFER_XTRANSFERABLE_HPP_
#include <com/sun/star/datatransfer/XTransferable.hpp>
#endif

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

/*************************************************************************
*************************************************************************/
class SvObject;
class SvStorage;
class SvFactory_Impl;

typedef SvGlobalName SvUniqueName;

//==================class SvFactory========================================
class SO3_DLLPUBLIC SvFactory : public SotFactory
/*  [Beschreibung]

    Die Methoden der Klasse kann man in zwei Gruppen aufteilen.
    Erstens allgemeine Verwaltung des So-Projektes. Dies bedeutet den
    Zugriff auf Resourcen, Variablen und Methoden, die das Projekt
    zur Verfuegung stellt. Alle diese Methoden sind static.
    Zweitens bereitstellen von speziellen Informationen "uber die
    einzelnen Klassen. Diese Methoden sind nicht static. Factories f"ur
    verschiedene Klassen bekommt man "uber die Methode
    Klasse::ClassFactory (<SvObject::ClassFactory>). Die Factory zu einem
    Objekt bekommt man durch <SvObject::GetSvFactory>.
*/
{
    SvFactory_Impl *    pImp;
    ULONG               nRegisterId;

    SO3_DLLPRIVATE void                Revoke();
protected:
    virtual             ~SvFactory();
public:
                        TYPEINFO();

    static  BOOL                    Init();
    static  void                    DeInit();

    static  String                  GetConfigFileName();

    static  void                    SetDefaultPlugInFactory( SvFactory * );
    static  SvFactory *             GetDefaultPlugInFactory();

    static  void                    SetDefaultAppletFactory( SvFactory * );
    static  SvFactory *             GetDefaultAppletFactory();

    SvObjectRef         Create( const SvGlobalName & rSvClassName ) const;
    SvObjectRef         CreateAndLoad( SvStorage *, BOOL bLink = FALSE ) const;
    SvObjectRef         CreateAndLoad( SvStream &, ULONG * nLen = NULL ) const;
    SvObjectRef         CreateAndInit( const SvGlobalName & rSvClassName,
                                       SvStorage * ) const;
    SvObjectRef         CreateAndInit( const String & rFileName,
                                       SvStorage *, BOOL bLink = FALSE ) const;

    SvObjectRef CreateAndInit( const ::com::sun::star::uno::Reference<
                               ::com::sun::star::datatransfer::XTransferable>&,
                               SvStorage*) const;
    // do not use this function. bLink and bStorFilled are not supported anymore
    // use CreateAndInit( const Reference<XTransferable>&, SvStorage*) instead

    SvObjectRef CreateAndInit( const ::com::sun::star::uno::Reference<
                               ::com::sun::star::datatransfer::XTransferable>&,
                               SvStorage*, BOOL bLink, BOOL bStorFilled) const;

            SvFactory( const SvGlobalName &,
                       const String & rClassName, CreateInstanceType );

    void                Register();
    BOOL                IsRegistered() const { return nRegisterId != 0; }

                        // Emulieren
    static void         SetAutoTreatAs( const SvGlobalName & rOldClass,
                                        const String & rOldFullUserTypeName,
                                        const SvGlobalName & rNewClass );
    static SvGlobalName GetAutoTreatAs( const SvGlobalName & rClass );
                        // Konvertieren
    static void         SetAutoConvertTo( const SvGlobalName & rOldClass,
                                        const String & rOldFullUserTypeName,
                                        const SvGlobalName & rNewClass );
    static SvGlobalName GetAutoConvertTo( const SvGlobalName & rClass );
    static SvGlobalName GetSvClass31( const SvGlobalName & rClass );
    static SvGlobalName GetSvClass( INT32 nFileFormat, const SvGlobalName & rClass );
    static BOOL         IsIntern31( const SvGlobalName & rClass );
    static BOOL         IsIntern( const SvGlobalName & rClass,
                                     long *pFileFormat  );
    static SvGlobalName GetServerName( long nStorageFormat );
    static String       GetServiceName( const SvGlobalName& );

private:
                        SvFactory( const SvFactory & );
    SvFactory &         operator = ( const SvFactory & );
};

#define SV_IMPL_FACTORY(ClassName)                                  \
class ClassName : public SvFactory                                  \
{                                                                   \
public:                                                             \
         TYPEINFO();                                                 \
        ClassName( const SvGlobalName & rName,                      \
                              const String & rClassName,              \
                              CreateInstanceType pCreateFuncP )       \
            : SvFactory( rName, rClassName, pCreateFuncP )

#endif
