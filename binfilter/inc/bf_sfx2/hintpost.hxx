/*************************************************************************
 *
 *  $RCSfile: hintpost.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:32 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef _SFXHINTPOST_HXX
#define _SFXHINTPOST_HXX

#ifndef _SFXGENLINK_HXX
#include <bf_sfx2/genlink.hxx>
#endif

#ifndef _REF_HXX //autogen
#include <tools/ref.hxx>
#endif

//===================================================================

class SfxHint;

//-------------------------------------------------------------------

class SfxHintPoster: public SvRefBase

/*  [Beschreibung]

    Mit Instanzen dieser Klasse k"onnen eindeutige Events per PostUserEvent
    "uber die StarView-Application verschickt werden. Wenn das User-Event
    ausgel"ost wird, wird der Handler <Event()> gerufen, dessen
    Basisimplementierung den mit <SetEventHdl()> angegbenen Link ruft.

    Die Instanz wird via Ref-Count mindestens solange gehalten, wie
    ein ggf. abgeschicktes Event noch nicht angekommen ist. Sollte das
    Ziel vorher sterben, ist die Verbindung zuvor mit 'SetEventHdl(GenLink())'
    zu kappen.
*/

{
    ULONG           nId;
    GenLink         aLink;

private:
//STRIP001  void            RegisterEvent();
#if _SOLAR__PRIVATE
                    DECL_LINK( DoEvent_Impl, SfxHint * );
#endif

protected:
    virtual         ~SfxHintPoster();
    virtual void    Event( SfxHint* pPostedHint );

public:
//STRIP001                  SfxHintPoster();
                    SfxHintPoster( const GenLink& rLink );

    void            Post( SfxHint* pHint = 0 );
    void            SetEventHdl( const GenLink& rLink );
};

//-------------------------------------------------------------------

SV_DECL_IMPL_REF(SfxHintPoster);

#endif
