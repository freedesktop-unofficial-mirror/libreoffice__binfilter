/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: swblocks.hxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 14:04:49 $
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
#ifndef _SWBLOCKS_HXX
#define _SWBLOCKS_HXX

#ifndef _PERSIST_HXX //autogen
#include <bf_so3/persist.hxx>
#endif
/*N*/#include <tools/debug.hxx> //addded for stripping
class SvxMacroTableDtor;
namespace binfilter {

class SfxMedium;
class SwPaM;
class SwDoc;

class SvXMLTextBlocks;
// Name eines Textblocks:




class SwImpBlocks
{
    friend class SwTextBlocks;
protected:
    String aFile;                       // physikalischer Dateiname
    String aName;                       // logischer Name der Datei
    SwImpBlocks( const String&, BOOL = FALSE ){DBG_ASSERT(0, "STRIP")}; //STRIP001 ;
public:
    const String& GetFileName() const {return aFile;}   // phys. Dateinamen liefern
};




class Sw3Io;
class Sw3IoImp;

class Sw3TextBlocks : public SwImpBlocks
{

public:
    Sw3TextBlocks( const String& rFile): SwImpBlocks( rFile ){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001   Sw3TextBlocks( const String& );



    // Methoden fuer die neue Autokorrektur



};

} //namespace binfilter
#endif
