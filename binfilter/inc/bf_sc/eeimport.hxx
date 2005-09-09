/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: eeimport.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:13:43 $
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
#ifndef SC_EEIMPORT_HXX
#define SC_EEIMPORT_HXX

#include "global.hxx"
class SvStream;
class Table;
namespace binfilter {

class ScDocument;
class ScEEParser;
class ScTabEditEngine;

struct ScEEParseEntry;

class ScEEImport
{
protected:
    ScRange             aRange;
    ScDocument*         pDoc;
    ScEEParser*         pParser;
    ScTabEditEngine*    pEngine;
    Table*              pRowHeights;

    BOOL                GraphicSize( USHORT nCol, USHORT nRow, USHORT nTab,
                            ScEEParseEntry* );
    void                InsertGraphic( USHORT nCol, USHORT nRow, USHORT nTab,
                            ScEEParseEntry* );

public:
                        ScEEImport( ScDocument* pDoc, const ScRange& rRange );
    virtual             ~ScEEImport();

    ULONG               Read( SvStream& rStream );
    ScRange             GetRange()      { return aRange; }
    virtual void        WriteToDocument( BOOL bSizeColsRows = FALSE,
                                        double nOutputFactor = 1.0 );
};



} //namespace binfilter
#endif
