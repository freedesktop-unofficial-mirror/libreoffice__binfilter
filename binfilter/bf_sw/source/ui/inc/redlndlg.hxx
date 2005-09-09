/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: redlndlg.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 05:48:57 $
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
#ifndef _SWREDLNDLG_HXX
#define _SWREDLNDLG_HXX

#include "chldwrap.hxx"

#ifndef _BASEDLGS_HXX //autogen
#include <bf_sfx2/basedlgs.hxx>
#endif
namespace binfilter {

class SwChildWinWrapper;
//STRIP001 class SwRedlineAcceptDlg;

/*------------------------------------------------------------------------
    Beschreibung:
------------------------------------------------------------------------*/

//STRIP001 class SwModelessRedlineAcceptDlg : public SfxModelessDialog
//STRIP001 {
//STRIP001  SwRedlineAcceptDlg*     pImplDlg;
//STRIP001  SwChildWinWrapper*      pChildWin;
//STRIP001
//STRIP001  virtual void    Resize();
//STRIP001
//STRIP001 public:
//STRIP001  SwModelessRedlineAcceptDlg(SfxBindings*, SwChildWinWrapper*, Window *pParent);
//STRIP001  ~SwModelessRedlineAcceptDlg();
//STRIP001
//STRIP001  virtual void    Activate();
//STRIP001  virtual void    FillInfo(SfxChildWinInfo&) const;
//STRIP001  void            Initialize (SfxChildWinInfo* pInfo);
//STRIP001 };

/*------------------------------------------------------------------------
    Beschreibung:
------------------------------------------------------------------------*/

//STRIP001 class SwModalRedlineAcceptDlg : public SfxModalDialog
//STRIP001 {
//STRIP001  SwRedlineAcceptDlg*     pImplDlg;
//STRIP001
//STRIP001  virtual void    Resize();
//STRIP001
//STRIP001 public:
//STRIP001  SwModalRedlineAcceptDlg(Window *pParent);
//STRIP001  ~SwModalRedlineAcceptDlg();
//STRIP001
//STRIP001  void            AcceptAll( BOOL bAccept );
//STRIP001  virtual void    Activate();
//STRIP001 };

/*------------------------------------------------------------------------
    Beschreibung:
------------------------------------------------------------------------*/

class SwRedlineAcceptChild : public SwChildWinWrapper
{
public:
    SwRedlineAcceptChild(   Window* pParent,USHORT nId, SfxBindings*, SfxChildWinInfo* ):SwChildWinWrapper( pParent, nId ){DBG_BF_ASSERT(0, "STRIP");}; //STRIP001  SwRedlineAcceptChild(   Window* ,
//STRIP001                          USHORT nId,
//STRIP001                          SfxBindings*,
//STRIP001                          SfxChildWinInfo*  );

    SFX_DECL_CHILDWINDOW( SwRedlineAcceptChild );

//STRIP001  virtual BOOL    ReInitDlg(SwDocShell *pDocSh);
};


} //namespace binfilter
#endif


