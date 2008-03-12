/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fmexch.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 09:28:40 $
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
#ifndef _SVX_FMEXCH_HXX
#define _SVX_FMEXCH_HXX

#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif

#ifndef _TRANSFER_HXX
#include <bf_svtools/transfer.hxx>
#endif

class SvTreeListBox;
namespace binfilter {

class FmFormShell;
class FmFormPage;
class SvLBoxEntry;

//========================================================================
// Exchange types
#define SVX_FM_FIELD_EXCH           String("SvxFormFieldExch",              sizeof("SvxFormFieldExch"))
#define SVX_FM_CONTROL_EXCH         String("SvxFormExplCtrlExch",           sizeof("SvxFormExplCtrlExch"))
#define SVX_FM_CONTROLS_AS_PATH     String("SvxFormControlsAsPathExchange", sizeof("SvxFormControlsAsPathExchange"))
#define SVX_FM_HIDDEN_CONTROLS      String("SvxFormHiddenControlsExchange", sizeof("SvxFormHiddenControlsExchange"))
#define SVX_FM_FILTER_FIELDS        String("SvxFilterFieldExchange",        sizeof("SvxFilterFieldExchange"))

//========================================================================

//........................................................................
namespace svxform
{
//........................................................................

    //====================================================================

    DECLARE_STL_VECTOR( SvLBoxEntry*, ListBoxEntryArray );

    //====================================================================
    //= OLocalExchange
    //====================================================================

    //====================================================================
    //= OLocalExchangeHelper
    //====================================================================
    /// a helper for navigator windows (SvTreeListBox'es) which allow DnD within themself
    class OLocalExchangeHelper
    {
    protected:
        Window*             m_pDragSource;

    public:
        OLocalExchangeHelper( Window* _pDragSource );
        ~OLocalExchangeHelper();

        void        prepareDrag( );

        void        startDrag( sal_Int8 nDragSourceActions );
        void        copyToClipboard( ) const;



    protected:

    protected:
        void implReset();
    };

    //====================================================================
    //= OControlTransferData
    //====================================================================

    //====================================================================

    //====================================================================
    //= OControlExchange
    //====================================================================

    //====================================================================
    //= OControlExchangeHelper
    //====================================================================
/*N*/   class OControlExchangeHelper : public OLocalExchangeHelper
/*N*/   {
/*N*/   public:
/*N*/       OControlExchangeHelper(Window* _pDragSource) : OLocalExchangeHelper(_pDragSource) { }
/*N*/
/*N*/
/*N*/   protected:
/*N*/   };

    //====================================================================
    //====================================================================

//........................................................................
}   // namespace svxform
//........................................................................

}//end of namespace binfilter
#endif

