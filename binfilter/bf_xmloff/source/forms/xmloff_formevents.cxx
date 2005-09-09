/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_formevents.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 09:13:07 $
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

// auto strip #ifndef _XMLOFF_FORMS_FORMEVENTS_HXX_
// auto strip #include "formevents.hxx"
// auto strip #endif
#ifndef _XMLOFF_XMLEVENT_HXX
#include "xmlevent.hxx"
#endif
namespace binfilter {

//.........................................................................
namespace xmloff
{
//.........................................................................

    //=====================================================================
    //= event translation table
    //=====================================================================
    static const XMLEventNameTranslation aEventTranslations[] =
    {
        { "XApproveActionListener::approveAction",      "on-approveaction" },
        { "XActionListener::actionPerformed",           "on-performaction" },
        { "XChangeListener::changed",                   "on-change" },
        { "XTextListener::textChanged",                 "on-textchange" },
        { "XItemListener::itemStateChanged",            "on-itemstatechange" },
        { "XFocusListener::focusGained",                "on-focus" },
        { "XFocusListener::focusLost",                  "on-blur" },
        { "XKeyListener::keyPressed",                   "on-keydown" },
        { "XKeyListener::keyReleased",                  "on-keyup" },
        { "XMouseListener::mouseEntered",               "on-mouseover" },
        { "XMouseMotionListener::mouseDragged",         "on-mousedrag" },
        { "XMouseMotionListener::mouseMoved",           "on-mousemove" },
        { "XMouseListener::mousePressed",               "on-mousedown" },
        { "XMouseListener::mouseReleased",              "on-mouseup" },
        { "XMouseListener::mouseExited",                "on-mouseout" },
        { "XResetListener::approveReset",               "on-approvereset" },
        { "XResetListener::resetted",                   "on-reset" },
        { "XSubmitListener::approveSubmit",             "on-submit" },
        { "XUpdateListener::approveUpdate",             "on-approveupdate" },
        { "XUpdateListener::updated",                   "on-update" },
        { "XLoadListener::loaded",                      "on-load" },
        { "XLoadListener::reloading",                   "on-startreload" },
        { "XLoadListener::reloaded",                    "on-reload" },
        { "XLoadListener::unloading",                   "on-startunload" },
        { "XLoadListener::unloaded",                    "on-unload" },
        { "XConfirmDeleteListener::confirmDelete",      "on-confirmdelete" },
        { "XRowSetApproveListener::approveRowChange",   "on-approverowchange" },
        { "XRowSetListener::rowChanged",                "on-rowchange" },
        { "XRowSetApproveListener::approveCursorMove",  "on-approvecursormove" },
        { "XRowSetListener::cursorMoved",               "on-cursormove" },
        { "XDatabaseParameterListener::approveParameter","on-supplyparameter" },
        { "XSQLErrorListener::errorOccured",            "on-error" },
        { 0, 0 }
    };

    const XMLEventNameTranslation* g_pFormsEventTranslation = aEventTranslations;

//.........................................................................
}   // namespace xmloff
//.........................................................................

/*************************************************************************
 * history:
 *  $Log: not supported by cvs2svn $
 *  Revision 1.2.128.1  2005/09/05 11:30:21  rt
 *  #i54170# Change license header: remove SISSL
 *
 *  Revision 1.2  2004/08/03 19:59:06  hr
 *  INTEGRATION: CWS bff2 (1.1.20); FILE MERGED
 *  2004/07/13 08:48:49 aw 1.1.20.1: #117295# minimize_includes step2
 *
 *  Revision 1.1.20.1  2004/07/13 08:48:49  aw
 *  #117295# minimize_includes step2
 *
 *  Revision 1.1  2003/12/05 09:34:14  aw
 *  Added bf_xmloff files
 *
 *  Revision 1.1  2001/01/02 15:56:27  fs
 *  initial checkin - code common to event ex- and import
 *
 *
 *  Revision 1.0 21.12.00 15:19:52  fs
 ************************************************************************/

}//end of namespace binfilter
