/*************************************************************************
 *
 *  $RCSfile: docinf.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:20:01 $
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
#ifndef _DOCINF_HXX
#define _DOCINF_HXX

#ifndef _LIST_HXX //autogen
#include <tools/list.hxx>
#endif

#ifndef _DATETIME_HXX //autogen
#include <tools/datetime.hxx>
#endif

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif

class Date;
class Time;
class DateTime;
class SvStream;

// EXTERN ----------------------------------------------------------------
struct DataTupel;

// ENUM -----------------------------------------------------------------
enum InfoType
{
    INFOTYPE_DATE, INFOTYPE_TIME, INFOTYPE_DATETIME,
    INFOTYPE_MODIFYINFO,
    INFOTYPE_STRING, INFOTYPE_STRINGLIST,
    INFOTYPE_BOOL, INFOTYPE_LONG,
    INFOTYPE_TEMPLATE
};


// CLASS -----------------------------------------------------------------
DECLARE_LIST( DataTupelList, DataTupel* )

// CLASS -----------------------------------------------------------------
class VarDocInfos
{
public:
                        VarDocInfos();
                        ~VarDocInfos();

            void        AddDate( String& rName, Date& rDate );
            void        AddTime( String& rName, Time& rTime );
            void        AddDateTime( String& rName, DateTime& rDateTime );

            void        AddString( String& rName, String& rString );
            void        AddStringList( String& rName, String& rStringList );
            void        AddBool( String& rName, BOOL bBool );
            void        AddLong( String& rName, long lLong );

            USHORT      GetCount();
            InfoType    GetType( USHORT nPos );
    const   String&     GetName( USHORT nPos );

    const   Date&       GetDate( USHORT nPos );
    const   Time&       GetTime( USHORT nPos );
    const   DateTime&   GetDateTime( USHORT nPos );

    const   String&     GetString( USHORT nPos );
    const   String&     GetStringList( USHORT nPos );
            BOOL        GetBool( USHORT nPos );
            long        GetLong( USHORT nPos );

friend      SvStream&    operator<<( SvStream&, VarDocInfos& ); //$ ostream
friend      SvStream&    operator>>( SvStream&, VarDocInfos& ); //$ istream

private:
    DataTupelList*      pInfoList;
};

// CLASS -----------------------------------------------------------------
struct ModifyInfo {
    DateTime    aModifiedDateTime;
    String      aModifiedById;
    String      aModifiedByName;

    friend      SvStream&    operator<<( SvStream&, ModifyInfo& ); //$ ostream
    friend      SvStream&    operator>>( SvStream&, ModifyInfo& ); //$ istream
};

// CLASS -----------------------------------------------------------------
class FixDocInfos
{
public:
                        FixDocInfos();
                        ~FixDocInfos();

            void        SetTitle( String& rTitle );
    const   String&     GetTitle() const;

    void                SetCreated( ModifyInfo& rInfo );
    const   ModifyInfo& GetCreated() const;

            void        SetLastChanged( ModifyInfo& rInfo );
    const   ModifyInfo& GetLastChanged() const;

            void        SetLastPrinted( ModifyInfo& rInfo );
    const   ModifyInfo& GetLastPrinted() const;

            void        SetTotalEditingTime( Time& rTime );
    const   Time&       GetTotalEditingTime() const;

friend      SvStream&    operator<<( SvStream&, FixDocInfos& ); //$ ostream
friend      SvStream&    operator>>( SvStream&, FixDocInfos& ); //$ istream

private:
    String          aTitle;

    ModifyInfo      aCreated;
    ModifyInfo      aLastChanged;
    ModifyInfo      aLastPrinted;
    Time            aTotalEditingTime;
};

// CLASS -----------------------------------------------------------------
struct TemplateInfo {
    String      aTitle;
    ULONG       lTemplateId;

                TemplateInfo() {}
                TemplateInfo( String& rName, ULONG lId ) :
                    aTitle( rName ),
                    lTemplateId( lId ) {}

    friend      SvStream&    operator<<( SvStream&, TemplateInfo& ); //$ ostream
    friend      SvStream&    operator>>( SvStream&, TemplateInfo& ); //$ istream
};

// CLASS -----------------------------------------------------------------
DECLARE_LIST( TemplateInfos, TemplateInfo* )

SvStream&    operator<<( SvStream&, TemplateInfos& ); //$ ostream
SvStream&    operator>>( SvStream&, TemplateInfos& ); //$ istream

#endif // _DOCINF_HXX
