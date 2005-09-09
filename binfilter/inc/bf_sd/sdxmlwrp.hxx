/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sdxmlwrp.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 12:05:54 $
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
#ifndef _SDXMLWRP_HXX
#define _SDXMLWRP_HXX

#include "sdfilter.hxx"
namespace binfilter {

// ---------------
// - SdXMLFilter -
// ---------------

enum SdXMLFilterMode
{
    SDXMLMODE_Normal,           // standard load and save of the complete document
    SDXMLMODE_Preview,          // only for import, only the first draw page and its master page is loaded
    SDXMLMODE_Organizer         // only for import, only the styles are loaded
};

class SdXMLFilter : public SdFilter
{
private:
    SdXMLFilterMode meFilterMode;

public:

                            SdXMLFilter( SfxMedium& rMedium, SdDrawDocShell& rDocShell, sal_Bool bShowProgress, SdXMLFilterMode eFilterMode = SDXMLMODE_Normal );
                            ~SdXMLFilter();

    virtual sal_Bool        Import();
    virtual sal_Bool        Export();
};

} //namespace binfilter
#endif  // _SDXMLWRP_HXX
