/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: forms_frm_resource.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 06:45:19 $
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

#include "frm_resource.hxx"

#ifndef _TOOLS_SIMPLERESMGR_HXX_
#include <tools/simplerm.hxx>
#endif

// ---- needed as long as we have no contexts for components ---
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
//---------------------------------------------------

#ifndef _SOLAR_HRC
#include <bf_svtools/solar.hrc>
#endif
namespace binfilter {

//.........................................................................
namespace frm
{

    //==================================================================
    //= ResourceManager
    //==================================================================
    SimpleResMgr* ResourceManager::m_pImpl = NULL;

    //------------------------------------------------------------------
    ResourceManager::EnsureDelete::~EnsureDelete()
    {
        delete ResourceManager::m_pImpl;
    }

    //------------------------------------------------------------------
    void ResourceManager::ensureImplExists()
    {
        if (m_pImpl)
            return;

        ByteString sFileName("bf_frm"); //STRIP005

        m_pImpl = SimpleResMgr::Create(sFileName.GetBuffer(), Application::GetSettings().GetUILocale());

        if (m_pImpl)
        {
            // no that we have a impl class make sure it's deleted on unloading the library
            static ResourceManager::EnsureDelete    s_aDeleteTheImplClas;
        }
    }

    //------------------------------------------------------------------
    ::rtl::OUString ResourceManager::loadString(sal_uInt16 _nResId)
    {
        ::rtl::OUString sReturn;

        ensureImplExists();
        if (m_pImpl)
            sReturn = m_pImpl->ReadString(_nResId);

        return sReturn;
    }

//.........................................................................
}
//.........................................................................

}
