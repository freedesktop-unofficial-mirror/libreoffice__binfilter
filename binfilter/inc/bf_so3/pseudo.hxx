/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: pseudo.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:45:26 $
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
#ifndef _PSEUDO_HXX
#define _PSEUDO_HXX

#ifndef _UNQID_HXX //autogen
#include <tools/unqid.hxx>
#endif
#ifndef _IFACE_HXX
#include <bf_so3/iface.hxx>
#endif
#ifndef _OWNLIST_HXX
#include <bf_svtools/ownlist.hxx>
#endif

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

class  Menu;

namespace binfilter {

class  SvBaseLink;
class  SvEmbeddedClient;
class  ImpOleObject;

//=========================================================================
class SO3_DLLPUBLIC SvVerb
/*  [Beschreibung]

    Die Klasse beschreibt einen Befehl, der an ein SvPseudoObject
    geschickt werden kann.

    [Querverweise]

    <SvPseudoObject::DoVerb>
*/
{
private:
    long            nId;
    String          aName;
    UniqueItemId    aMenuId;
    BOOL            bOnMenu : 1,
                    bConst  : 1;
public:
                    SvVerb( long nIdP, const String & rNameP,
                            BOOL bConstP = FALSE, BOOL bOnMenuP = TRUE );
                    SvVerb( const SvVerb & );
    SvVerb &        operator = ( const SvVerb & );
                    ~SvVerb();

    const String &  GetName() const { return aName; }
    long            GetId() const { return nId; }
    USHORT          GetMenuId() const { return (USHORT)aMenuId.GetId(); }
    BOOL            IsConst() const { return bConst; }
    BOOL            IsOnMenu() const { return bOnMenu; }
};

//=========================================================================
class SO3_DLLPUBLIC SvVerbList
{
    PRV_SV_DECL_OWNER_LIST(SvVerbList,SvVerb)
};

//=========================================================================
// Muessen mit OLE2 Werten uebereinstimmen
#define SVVERB_SHOW         -1
#define SVVERB_OPEN         -2
#define SVVERB_HIDE         -3
#define SVVERB_UIACTIVATE   -4
#define SVVERB_IPACTIVATE   -5

// Eigene Verbs
#define SVVERB_PROPS        1

// Muessen mit OLE2 Werten uebereinstimmen
#define SVOBJ_MISCSTATUS_SERVERRESIZE           1
#define SVOBJ_MISCSTATUS_NOTREPLACE             4
#define SVOBJ_MISCSTATUS_CANTLINKINSIDE         16
#define SVOBJ_MISCSTATUS_LINK                   64
#define SVOBJ_MISCSTATUS_INSIDEOUT              128
#define SVOBJ_MISCSTATUS_ACTIVATEWHENVISIBLE    256
#define SVOBJ_MISCSTATUS_NOTRESIZEABLE          512
#define SVOBJ_MISCSTATUS_ALWAYSACTIVATE         1024
#define SVOBJ_MISCSTATUS_RESIZEONPRINTERCHANGE  2048
#define SVOBJ_MISCSTATUS_SPECIALOBJECT          4096

class SO3_DLLPUBLIC SvPseudoObject : virtual public SvObject
/*  [Beschreibung]

    Diese Klasse stellt die Basisschnittstelle fuer Klassen zur Verfuegung,
    deren Instanzen von aussen, z.B. via Link oder als Ole-Objekt,
    angesprochen werden kann. Sie besitzt folgende Eigenschaften:
    -Informationen (z.B. den Typ) ueber das Objekt liefern.
    -Daten- und Benachrichtigungsquelle ueber die Klassen
     <SvDataObject> und <SvAdvise>
    -Das Objekt anzeigen oder im Server aktivieren.
*/
{
friend class ImpOleObject;
private:
    SvVerbList *    pVerbs;             // Liste der Verben
    BOOL            bDeleteVerbs;       // TRUE, wenn pVerbs loeschen
protected:
                    ~SvPseudoObject();

    virtual ErrCode Verb( long nVerbPos, SvEmbeddedClient * pCallerClient,
                        Window * pWin, const Rectangle * pWorkAreaPixel );
    virtual BOOL    Close();
public:
    SvPseudoObject();

    SO2_DECL_STANDARD_CLASS_DLL( SvPseudoObject, SOAPP )

    virtual void    FillClass( SvGlobalName * pClassName,
                               ULONG * pFormat,
                               String * pAppName,
                               String * pFullTypeName,
                               String * pShortTypeName,
                               long nFileFormat = SOFFICE_FILEFORMAT_CURRENT ) const;
    SvGlobalName    GetClassName() const;
    String          GetAppName() const;
    String          GetFullTypeName() const;
    String          GetShortTypeName() const;

                    // Befehle
    void            SetVerbList( SvVerbList * pVerbsP, BOOL bDeleteVerbs=FALSE );
    virtual const SvVerbList & GetVerbList() const;
    const SvVerb *  GetVerb( USHORT nMenuId ) const;
    ErrCode         DoVerb( long nVerbPos, SvEmbeddedClient * pCallerClient,
                            Window * pWin, const Rectangle * pWorkAreaPixel );
    void            AppendVerbs( Menu & rMenu );

    virtual ULONG   GetMiscStatus() const;

};

#ifndef SO2_DECL_SVPSEUDOOBJECT_DEFINED
#define SO2_DECL_SVPSEUDOOBJECT_DEFINED
SO2_DECL_REF(SvPseudoObject)
#endif
SO2_IMPL_REF( SvPseudoObject )

}

#endif

