/*************************************************************************
 *
 *  $RCSfile: attributeproperties.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:51 $
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

#ifndef _ATTRIBUTEPROPERTIES_HXX
#define _ATTRIBUTEPROPERTIES_HXX

#ifndef _DEFAULTPROPERTIES_HXX
#include <sdr/properties/defaultproperties.hxx>
#endif

//////////////////////////////////////////////////////////////////////////////

namespace Sdr
{
    namespace Properties
    {
        class AttributeProperties : public DefaultProperties
        {
            // add style sheet, do all the necessary handling
            void ImpAddStyleSheet(SfxStyleSheet* pNewStyleSheet, sal_Bool bDontRemoveHardAttr);

            // remove StyleSheet, do all the necessary handling
            void ImpRemoveStyleSheet();

        protected:
            // the SytleSheet of this object
            SfxStyleSheet*                                  mpStyleSheet;

            // create a new itemset
            virtual SfxItemSet& CreateObjectSpecificItemSet(SfxItemPool& pPool);

        public:
            // basic constructor
            AttributeProperties(SdrObject& rObj);

            // constructor for copying, but using new object
            AttributeProperties(const AttributeProperties& rProps, SdrObject& rObj);

            // Clone() operator, normally just calls the local copy constructor
            virtual Properties& Clone(SdrObject& rObj) const;

            // destructor
            virtual ~AttributeProperties();

            // react on ItemSet changes
            virtual void ItemSetChanged(const SfxItemSet& rSet);

            // Do the ItemChange, may do special handling
            virtual void ItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem = 0);

            // set a new StyleSheet and broadcast
            virtual void SetStyleSheet(SfxStyleSheet* pNewStyleSheet, sal_Bool bDontRemoveHardAttr);

            // get the installed StyleSheet
            virtual SfxStyleSheet* GetStyleSheet() const;

            // pre/post-process saving
            virtual void PreProcessSave();
            virtual void PostProcessSave();

            // Move properties to a new ItemPool.
            virtual void MoveToItemPool(SfxItemPool* pSrcPool, SfxItemPool* pDestPool, SdrModel* pNewModel = 0L);

            // Set new model.
            virtual void SetModel(SdrModel* pOldModel, SdrModel* pNewModel);

            // force all attributes which come from styles to hard attributes
            // to be able to live without the style.
            virtual void ForceStyleToHardAttributes(sal_Bool bPseudoSheetsOnly = sal_False);

            // This is the notifyer from SfxListener
            virtual void Notify(SfxBroadcaster& rBC, const SfxHint& rHint);
        };
    } // end of namespace Properties
} // end of namespace Sdr

//////////////////////////////////////////////////////////////////////////////

#endif //_ATTRIBUTEPROPERTIES_HXX

// eof
