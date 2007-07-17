/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: app.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 12:30:13 $
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

#ifndef _SCH_APP_HXX
#define _SCH_APP_HXX

// Die folgenden includes gehoeren eigentlich in app.cxx

#include "schdll.hxx"

class SdClipboard;
class SdBasic;
class BasicIDE;

#ifndef _SCH_GLOB_HXX
#include <glob.hxx>
#endif

#ifndef _SFXNEW_HXX //autogen
#include <bf_sfx2/new.hxx>
#endif

#ifndef _SVXERR_HXX //autogen
#include <bf_svx/svxerr.hxx>
#endif

#ifndef _SFXAPP_HXX //autogen
#include <bf_sfx2/app.hxx>
#endif
namespace binfilter {

/*************************************************************************
|*
|* Klasse fuer Applikationsobjekt
|*
\************************************************************************/

class SchApp: public SfxApplication
{
protected :
    virtual void Init();
    virtual void Exit();
    virtual void OpenClients();

    SvxErrorHandler *pSvxErrorHandler;

public:
    SchApp();
    virtual ~SchApp();

    virtual void Main();
};



} //namespace binfilter
#endif      // _SCH_APP_HXX

