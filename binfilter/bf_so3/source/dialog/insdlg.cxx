/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: insdlg.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:11:32 $
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

#define _INSDLG_CXX

// include ---------------------------------------------------------------

#include <stdio.h>
#include "insdlg.hxx"

#include <tools/urlobj.hxx>
#include <tools/debug.hxx>
#include <bf_svtools/urihelper.hxx>
#include <vcl/button.hxx>
#include <vcl/fixed.hxx>
#include <vcl/group.hxx>
#include <vcl/lstbox.hxx>
#include <vcl/msgbox.hxx>
#include <vcl/svapp.hxx>

#include <svuidlg.hrc>
#include <bf_so3/svstor.hxx>
#include <bf_so3/ipobj.hxx>
#include "bf_so3/plugin.hxx"
#include "bf_so3/applet.hxx"
#include "bf_so3/outplace.hxx"
#include "bf_so3/staticbaseurl.hxx"

#include <com/sun/star/ui/dialogs/TemplateDescription.hpp>
#include <com/sun/star/ui/dialogs/ExecutableDialogResults.hpp>
#include <com/sun/star/ui/dialogs/XFilePicker.hpp>
#include <com/sun/star/ui/dialogs/XFilterManager.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XInitialization.hpp>
#include <comphelper/processfactory.hxx>

#include <osl/file.hxx>
#include <sot/stg.hxx>

#include <com/sun/star/container/XHierarchicalNameAccess.hpp>
#include <com/sun/star/container/XNameAccess.hpp>
#include <unotools/processfactory.hxx>

#define _SVSTDARR_STRINGSDTOR
#include <bf_svtools/svstdarr.hxx>

using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::uno;
using namespace ::rtl;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::ui::dialogs;

namespace binfilter
{

/********************** SvObjectServerList ********************************
**************************************************************************/
PRV_SV_IMPL_OWNER_LIST( SvObjectServerList, SvObjectServer )

/*************************************************************************
|*    SvObjectServerList::SvObjectServerList()
|*
|*    Beschreibung
*************************************************************************/
const SvObjectServer * SvObjectServerList::Get( const String & rHumanName ) const
{
    for( ULONG i = 0; i < Count(); i++ )
    {
        if( rHumanName == GetObject( i ).GetHumanName() )
            return &GetObject( i );
    }
    return NULL;
}

/*************************************************************************
|*    SvObjectServerList::SvObjectServerList()
|*
|*    Beschreibung
*************************************************************************/
const SvObjectServer * SvObjectServerList::Get( const SvGlobalName & rName ) const
{
    for( ULONG i = 0; i < Count(); i++ )
    {
        if( rName == GetObject( i ).GetClassName() )
            return &GetObject( i );
    }
    return NULL;
}

void SvObjectServerList::Remove( const SvGlobalName & rName )
{
    SvObjectServer * pS = (SvObjectServer *)aTypes.First();
    while( pS )
    {
        if( rName == pS->GetClassName() )
        {
            Remove();
            pS = (SvObjectServer *)aTypes.GetCurObject();
        }
        else
            pS = (SvObjectServer *)aTypes.Next();
    }
}

//---------------------------------------------------------------------
void SvObjectServerList::FillInsertObjects()
/* [Beschreibung]

    Die Liste wird mit allen Typen gef"ullt, die im Insert-Dialog
    ausgew"ahlt werden k"onnen.
*/
{
    try{
    Reference< XMultiServiceFactory > _globalMSFactory= utl::getProcessServiceFactory();
    if( _globalMSFactory.is())
    {
        OUString sProviderService =
        OUString::createFromAscii( "com.sun.star.configuration.ConfigurationProvider" );
        Reference<XMultiServiceFactory > sProviderMSFactory(
            _globalMSFactory->createInstance( sProviderService ),UNO_QUERY );

        if( sProviderMSFactory.is())
        {
            OUString sReaderService =
                OUString::createFromAscii( "com.sun.star.configuration.ConfigurationAccess" );
            Sequence< Any > aArguments( 1 );
            aArguments[0] <<= OUString::createFromAscii( "org.openoffice.Office.Common");

            Reference< XHierarchicalNameAccess > xHierNameAccess(
                sProviderMSFactory->createInstanceWithArguments( sReaderService,aArguments ),
                UNO_QUERY );

            if( xHierNameAccess.is())
            {
                OUString sTagName=  OUString::createFromAscii("OfficeObjects");
                Any _a= xHierNameAccess->getByHierarchicalName(sTagName);
                Reference<XNameAccess> nameAccess;
                _a >>= nameAccess;
                if( nameAccess.is())
                {
                    Sequence<OUString> seqNames= nameAccess->getElementNames();
                    OUString sSeparator( OUString::createFromAscii("/"));
                    for(int i=0; i<seqNames.getLength(); i++)
                    {

                        OUString sComponentName= sTagName + sSeparator + seqNames[i] + sSeparator +
                            OUString::createFromAscii("Name");
                        OUString sKey= sTagName + sSeparator + seqNames[i] + sSeparator +
                            OUString::createFromAscii("Key");
                        Any anyName= xHierNameAccess->getByHierarchicalName(sComponentName);
                        Any anyKey= xHierNameAccess->getByHierarchicalName( sKey);

                        anyName >>= sComponentName;
                        anyKey >>= sKey;

                        SvGlobalName aClassName;
                        if( aClassName.MakeId( String(sKey.getStr())))
                        {
                            if( !Get( aClassName ) )
                                // noch nicht eingetragen
                                Append( SvObjectServer( aClassName, String( sComponentName.getStr() ) ) );

                        }
                    }
                }
            }
        }

    }


#ifdef WNT
    //SvGlobalName aOleFact = *SvOutPlaceObject::ClassFactory();
    //String aOleObj( SoResid( STR_FURTHER_OBJECT ) );
    //Append( SvObjectServer( aOleFact, aOleObj ) );
    DBG_ERROR( "non-working code!" );
    // TODO: dead corpses
#endif

    }catch( com::sun::star::container::NoSuchElementException)
    {
    }catch( ::com::sun::star::uno::Exception)
    {
    }
    catch(...)
    {
    }
}

}
