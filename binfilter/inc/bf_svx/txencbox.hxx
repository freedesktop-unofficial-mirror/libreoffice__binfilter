/*************************************************************************
 *
 *  $RCSfile: txencbox.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:30:00 $
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
#ifndef _SVX_TXENCBOX_HXX
#define _SVX_TXENCBOX_HXX

// include ---------------------------------------------------------------

#ifndef _LSTBOX_HXX //autogen
#include <vcl/lstbox.hxx>
#endif
#ifndef _RTL_TEXTENC_H
#include <rtl/textenc.h>
#endif
namespace binfilter {

//STRIP001 class SvxTextEncodingTable;

class SvxTextEncodingBox : public ListBox
{
//STRIP001 private:
//STRIP001  const SvxTextEncodingTable*     m_pEncTable;
//STRIP001
//STRIP001  USHORT              EncodingToPos_Impl( rtl_TextEncoding nEnc ) const;
//STRIP001
public:
     SvxTextEncodingBox( Window* pParent, const ResId& rResId );
    ~SvxTextEncodingBox(){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 ;
//STRIP001
//STRIP001  /** Fill with all known encodings but exclude those matching one or more
//STRIP001      given flags as defined in rtl/tencinfo.h
//STRIP001
//STRIP001      <p> If nButIncludeInfoFlags is given, encodings are included even if they
//STRIP001      match nExcludeInfoFlags. Thus it is possible to exclude 16/32-bit
//STRIP001      Unicode with RTL_TEXTENCODING_INFO_UNICODE but to include UTF7 and UTF8
//STRIP001      with RTL_TEXTENCODING_INFO_MIME </p>
//STRIP001
//STRIP001         @param bExcludeImportSubsets
//STRIP001             If <TRUE/>, some specific encodings are not listed, as they are a
//STRIP001             subset of another encoding. This is the case for
//STRIP001             RTL_TEXTENCODING_GB_2312, RTL_TEXTENCODING_GBK,
//STRIP001             RTL_TEXTENCODING_MS_936, which are covered by
//STRIP001             RTL_TEXTENCODING_GB_18030. Normally, this flag should be set to
//STRIP001             <TRUE/> whenever the box is used in import dialogs. */
//STRIP001  void                FillFromTextEncodingTable(
//STRIP001                             sal_Bool bExcludeImportSubsets = FALSE,
//STRIP001                          sal_uInt32 nExcludeInfoFlags = 0,
//STRIP001                          sal_uInt32 nButIncludeInfoFlags = 0
//STRIP001                          );
//STRIP001
//STRIP001     /** Fill with all encodings known to the dbtools::OCharsetMap but exclude
//STRIP001         those matching one or more given flags as defined in rtl/tencinfo.h
//STRIP001
//STRIP001      <p> If nButIncludeInfoFlags is given, encodings are included even if they
//STRIP001      match nExcludeInfoFlags. Thus it is possible to exclude 16/32-bit
//STRIP001      Unicode with RTL_TEXTENCODING_INFO_UNICODE but to include UTF7 and UTF8
//STRIP001      with RTL_TEXTENCODING_INFO_MIME </p>
//STRIP001
//STRIP001         @param bExcludeImportSubsets
//STRIP001             If <TRUE/>, some specific encodings are not listed, as they are a
//STRIP001             subset of another encoding. This is the case for
//STRIP001             RTL_TEXTENCODING_GB_2312, RTL_TEXTENCODING_GBK,
//STRIP001             RTL_TEXTENCODING_MS_936, which are covered by
//STRIP001             RTL_TEXTENCODING_GB_18030. Normally, this flag should be set to
//STRIP001             <TRUE/> whenever the box is used in import dialogs. */
//STRIP001     void                FillFromDbTextEncodingMap(
//STRIP001                             sal_Bool bExcludeImportSubsets = FALSE,
//STRIP001                          sal_uInt32 nExcludeInfoFlags = 0,
//STRIP001                          sal_uInt32 nButIncludeInfoFlags = 0
//STRIP001                          );
//STRIP001
//STRIP001     /** Fill with all known MIME encodings and select the best according to
//STRIP001         <method>GetBestMimeEncoding</method>
//STRIP001   */
//STRIP001  void                FillWithMimeAndSelectBest();
//STRIP001
//STRIP001     /** Get the best MIME encoding matching the system locale, or if that isn't
//STRIP001         determinable one that matches the UI locale, or UTF8 if everything else
//STRIP001         fails.
//STRIP001      */
//STRIP001     static  rtl_TextEncoding    GetBestMimeEncoding();
//STRIP001
//STRIP001  const SvxTextEncodingTable*     GetTextEncodingTable() const
//STRIP001                          { return m_pEncTable; }
//STRIP001
//STRIP001  void                InsertTextEncoding( const rtl_TextEncoding nEnc,
//STRIP001                          USHORT nPos = LISTBOX_APPEND );
//STRIP001
//STRIP001  void                InsertTextEncoding( const rtl_TextEncoding nEnc,
//STRIP001                          const String& rEntry,
//STRIP001                          USHORT nPos = LISTBOX_APPEND );
//STRIP001
//STRIP001  void                RemoveTextEncoding( const rtl_TextEncoding nEnc );
//STRIP001
//STRIP001  void                SelectTextEncoding( const rtl_TextEncoding nEnc,
//STRIP001                          BOOL bSelect = TRUE );
//STRIP001
//STRIP001  rtl_TextEncoding    GetSelectTextEncoding() const;
//STRIP001
//STRIP001  const String&       GetSelectTextString() const;
//STRIP001
//STRIP001  BOOL                IsTextEncodingSelected( const rtl_TextEncoding nEnc ) const;
};

}//end of namespace binfilter
#endif

