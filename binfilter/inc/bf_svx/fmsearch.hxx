/*************************************************************************
 *
 *  $RCSfile: fmsearch.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 21:14:05 $
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

#ifndef _FMSEARCH_HXX
#define _FMSEARCH_HXX

#ifndef _COM_SUN_STAR_SDBC_XRESULTSET_HPP_
#include <com/sun/star/sdbc/XResultSet.hpp>
#endif

#define _SVSTDARR_STRINGSDTOR
#include <svtools/svstdarr.hxx>

#ifndef _DIALOG_HXX //autogen
#include <vcl/dialog.hxx>
#endif

#ifndef _BUTTON_HXX //autogen
#include <vcl/button.hxx>
#endif

#ifndef _FIXED_HXX //autogen
#include <vcl/fixed.hxx>
#endif

#ifndef _EDIT_HXX //autogen
#include <vcl/edit.hxx>
#endif

#ifndef _SV_COMBOBOX_HXX //autogen
#include <vcl/combobox.hxx>
#endif

#ifndef _SV_LSTBOX_HXX //autogen
#include <vcl/lstbox.hxx>
#endif

#ifndef _LINK_HXX //autogen
#include <tools/link.hxx>
#endif

// auto strip #ifndef _SFXCFGITEM_HXX //autogen
// auto strip #include <bf_sfx2/cfgitem.hxx>
// auto strip #endif

#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif
// auto strip #ifndef _STRING_HXX
// auto strip #include <tools/string.hxx>
// auto strip #endif
FORWARD_DECLARE_INTERFACE(util,XNumberFormatsSupplier)
namespace binfilter {

//FORWARD_DECLARE_INTERFACE(uno,Reference)
//STRIP008 FORWARD_DECLARE_INTERFACE(util,XNumberFormatsSupplier)

// ===================================================================================================
// moegliche Rueckgabewerte fuer den Found-Handler
#define FM_SEARCH_GETFOCUS_ASYNC    0x0001
    // setzt den Fokus auf den Dialog nicht sofort nach dem Aufruf des Found-Handlers, sondern postet sich selber dafuer
    // ein Ereignis

#define MAX_HISTORY_ENTRIES     50

// ===================================================================================================
// Hilfsmethoden

//STRIP001 sal_Bool IsSearchableControl(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& _xControl, ::rtl::OUString* pCurrentText = NULL);
    // check if the control has one of the interfaces we can use for searching
    // *pCurrentText will be filled with the current text of the control (as used when searching this control)

// ===================================================================================================
// Hilfsstrukturen

struct FmFoundRecordInformation
{
    ::com::sun::star::uno::Any      aPosition;  // Bookmark des Datensatzes, in dem der Text gefunden wurde
    sal_Int16       nFieldPos;  // dito : die relative Position der Spalte (im Stringnamen in Feldliste im Constructor)
    sal_Int16       nContext;   // Kontext, in dem gesucht und gefunden wurde (falls die aktuelle Suche verschiedene solche kennt)
};

DECLARE_STL_VECTOR( ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>, InterfaceArray);
    // TODO : use stl

// ===================================================================================================
// = struct FmSearchContext - Informationen fuer Suche in verschiedenen Kontexten
// ===================================================================================================

struct FmSearchContext
{
    // [in]
    sal_Int16                   nContext;       // die Nummer des Kontextes
    // [out]
    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>           xCursor;        // der Iterator fuer diesen Kontext
    String                  strUsedFields;  // eine Liste von durch ';' getrennten Feldnamen
    InterfaceArray          arrFields;      // die korrespondierenden Text-Interfaces fuer die Felder in strUsedFields
    String                  sFieldDisplayNames;     // if not empty : names to be displayed for the searchable fields (must have the same token count as strUsedFields !)
};

// ===================================================================================================
// = class FmSearchDialog - Dialog fuer Suchen in Formularen/Tabellen
// ===================================================================================================

namespace svxform {
    class FmSearchConfigItem;
}

class FmSearchEngine;
struct FmSearchProgress;
//STRIP001 class FmSearchDialog : public ModalDialog
//STRIP001 {
//STRIP001  friend class FmSearchEngine;
//STRIP001
//STRIP001  // meine ganzen Controls
//STRIP001     FixedLine       m_flSearchFor;
//STRIP001  RadioButton     m_rbSearchForText;
//STRIP001  RadioButton     m_rbSearchForNull;
//STRIP001  RadioButton     m_rbSearchForNotNull;
//STRIP001  ComboBox        m_cmbSearchText;
//STRIP001     FixedLine       m_flWhere;
//STRIP001  FixedText       m_ftForm;
//STRIP001  ListBox         m_lbForm;
//STRIP001  RadioButton     m_rbAllFields;
//STRIP001  RadioButton     m_rbSingleField;
//STRIP001  ListBox         m_lbField;
//STRIP001     FixedLine       m_flOptions;
//STRIP001  FixedText       m_ftPosition;
//STRIP001  ListBox         m_lbPosition;
//STRIP001  CheckBox        m_cbUseFormat;
//STRIP001  CheckBox        m_cbCase;
//STRIP001  CheckBox        m_cbBackwards;
//STRIP001  CheckBox        m_cbStartOver;
//STRIP001  CheckBox        m_cbWildCard;
//STRIP001  CheckBox        m_cbRegular;
//STRIP001  CheckBox        m_cbApprox;
//STRIP001  PushButton      m_pbApproxSettings;
//STRIP001  CheckBox        m_aHalfFullFormsCJK;
//STRIP001  CheckBox        m_aSoundsLikeCJK;
//STRIP001  PushButton      m_aSoundsLikeCJKSettings;
//STRIP001     FixedLine       m_flState;
//STRIP001  FixedText       m_ftRecordLabel;
//STRIP001  FixedText       m_ftRecord;
//STRIP001  FixedText       m_ftHint;
//STRIP001  PushButton      m_pbSearchAgain;
//STRIP001  CancelButton    m_pbClose;
//STRIP001  HelpButton      m_pbHelp;
//STRIP001
//STRIP001  Window*         m_pPreSearchFocus;
//STRIP001
//STRIP001  Link    m_lnkFoundHandler;          // Handler fuer "gefunden"
//STRIP001  Link    m_lnkCanceledNotFoundHdl;   // Handler fuer Positionierung des Cursors
//STRIP001
//STRIP001  Link    m_lnkContextSupplier;       // fuer Suche in verschiedenen Kontexten
//STRIP001
//STRIP001  // ein Array, in dem ich mir fuer jeden Kontext das aktuell selektierte Feld merke
//STRIP001  ::std::vector<String> m_arrContextFields;
//STRIP001
//STRIP001  // fuer die eigentliche Arbeit ...
//STRIP001  FmSearchEngine* m_pSearchEngine;
//STRIP001
//STRIP001  Timer           m_aDelayedPaint;
//STRIP001      // siehe EnableSearchUI
//STRIP001
//STRIP001  ::svxform::FmSearchConfigItem*      m_pConfig;
//STRIP001 public:
//STRIP001  /** die drei moeglichen Such-Modi :
//STRIP001      SM_BRUTE sucht einfach nur ... da wird das Office in der Zeit wohl stehen
//STRIP001      SM_ALLOWSCHEDULE ruft nach jedem durchsuchten Feld ein Application::Reschedule auf, so dass die Suche zwar im aufrufenden
//STRIP001      Thread laeuft, aber die Office-UI wenigstens noch funktionieren sollte. Soweit das den Dialog angeht, achtet der selber
//STRIP001      darauf, dass keine Inkonsistenzen entstehen, was dabei ausserhalb des Dialoges liegt, muss natuerlich vom Aufrufer
//STRIP001      erledigt werden (Was nicht allzu kompliziert sein duerfte, da der Dialog hier ja modal sein sollte)
//STRIP001      SM_USETHREAD startet einen eigenen Thread, der die Suche erledigt, so dass also die UI auch hier weiterhin funktioniert.
//STRIP001  */
//STRIP001  enum SEARCH_MODE { SM_BRUTE, SM_ALLOWSCHEDULE, SM_USETHREAD };
//STRIP001
//STRIP001  /** Constructor 1:
//STRIP001      gesucht wird mittels des uebergebenen Iterators, wenn man also seinen Original-Cursor nicht bewegen will, muss
//STRIP001      man hier einen Clone uebergeben
//STRIP001      strVisibleFields muss eine (durch ; getrennte) Liste aller Felder, die zur Auswahl stehen sollen, enthalten
//STRIP001      xFormatter wird benutzt, wenn die Daten aus den Feldern vor dem Vergleich entsprechend ihrem FormatKey formatiert
//STRIP001      werden sollen
//STRIP001      Zu eMode siehe SEARCH_MODE.
//STRIP001  */
//STRIP001  FmSearchDialog(Window* pParent, const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>& xCursor, const String& strVisibleFields, const String& strInitialText,
//STRIP001      const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatsSupplier>& xFormatSupplier, SEARCH_MODE eMode = SM_ALLOWSCHEDULE);
//STRIP001  /** Constructor 2:
//STRIP001      hiermit kann in verschiedenen Saetzen von Feldern gesucht werden. Es gibt eine Reihe von Kontexten, deren Namen in
//STRIP001      strContexts stehen (getrennt durch ';'), der Benutzer kann einen davon auswaehlen.
//STRIP001      Wenn der Benutzer einen Kontext auswaehlt, wird lnkContextSupplier aufgerufen, er bekommt einen Zeiger auf eine
//STRIP001      FmSearchContext-Struktur, die gefuellt werden muss.
//STRIP001      Fuer die Suche gilt dann :
//STRIP001      a) bei formatierter Suche wird der Iterator selber verwendet (wie beim ersten Constructor auch)
//STRIP001      b) bei formatierter Suche wird NICHT der FormatKey an den Fields des Iterators verwendet, sondern die entsprechende
//STRIP001          TextComponent wird gefragt (deshalb auch die Verwendung des originalen Iterator, durch dessen Move werden hoffentlich
//STRIP001          die hinter den TextComponent-Interfaces stehenden Controls geupdatet)
//STRIP001      c) bei nicht formatierter Suche wird ein Clone des Iterators verwendet (da ich hier die TextComponent-Interfaces nicht
//STRIP001          fragen muss)
//STRIP001      (natuerlich zwingend erforderlich : der String Nummer i in strUsedFields eines Kontexts muss mit dem Interface Nummer i
//STRIP001      in arrFields des Kontexts korrespondieren)
//STRIP001  */
//STRIP001  FmSearchDialog(Window* pParent, const String& strInitialText, const String& strContexts, sal_Int16 nInitialContext,
//STRIP001      const Link& lnkContextSupplier, SEARCH_MODE eMode = SM_ALLOWSCHEDULE);
//STRIP001
//STRIP001  virtual ~FmSearchDialog();
//STRIP001
//STRIP001  /** der Found-Handler bekommt im "gefunden"-Fall einen Zeiger auf eine FmFoundRecordInformation-Struktur
//STRIP001      (dieser ist nur im Handler gueltig, wenn man sich also die Daten merken muss, nicht den Zeiger, sondern die
//STRIP001      Struktur kopieren)
//STRIP001      Dieser Handler MUSS gesetzt werden.
//STRIP001      Ausserdem sollte beachtet werden, dass waehrend des Handlers der Suchdialog immer noch modal ist
//STRIP001  */
//STRIP001  void SetFoundHandler(const Link& lnk) { m_lnkFoundHandler = lnk; }
//STRIP001  /**
//STRIP001      Wenn die Suche abgebrochen oder erfolglos beendet wurde, wird im Suchdialog immer der aktuelle Datensatz angezeigt
//STRIP001      Damit das mit der eventuellen Anzeige des Aufrufers synchron geht, existiert dieser Handler (der nicht undbedingt gesetzt
//STRIP001      werden muss).
//STRIP001      Der dem Handler uebergebene Zeiger zeigt auf eine FmFoundRecordInformation-Struktur, bei der aPosition und eventuell
//STRIP001      (bei Suche mit Kontexten) nContext gueltig sind.
//STRIP001  */
//STRIP001  void SetCanceledNotFoundHdl(const Link& lnk) { m_lnkCanceledNotFoundHdl = lnk; }
//STRIP001
//STRIP001  inline void SetActiveField(const String& strField);
//STRIP001
//STRIP001 protected:
//STRIP001  virtual sal_Bool Close();
//STRIP001
//STRIP001  void Init(const String& strVisibleFields, const String& strInitialText);
//STRIP001      // nur von den Constructoren aus zu verwenden
//STRIP001
//STRIP001  void OnFound(const ::com::sun::star::uno::Any& aCursorPos, sal_Int16 nFieldPos);
//STRIP001
//STRIP001  void EnableSearchUI(sal_Bool bEnable);
//STRIP001      // beim Suchen in einem eigenen Thread moechte ich natuerlich die UI zum Starten/Parameter-Setzen der Suche disablen
//STRIP001      // Bei bEnable == sal_False wird fuer alle betroffenen Controls das Painten kurz aus- und mittels m_aDelayedPaint nach
//STRIP001      // einer kurzen Weile wieder angeschaltet. Wenn inzwischen eine Anforderung mit bEnable==sal_True kommt, wird der Timer gestoppt
//STRIP001      // und das Painten gleich wieder angeschaltet. Als Konsequenz dieses umstaendlichen Vorgehens ist kein Flackern zu sehen,
//STRIP001      // wenn man schnell hintereinander aus- und wieder einschaltet.
//STRIP001
//STRIP001  void EnableSearchForDependees(sal_Bool bEnable);
//STRIP001
//STRIP001  void EnableControlPaint(sal_Bool bEnable);
//STRIP001      // enabled (disabled) fuer alle wichtigen Controls ihr Paint
//STRIP001
//STRIP001  void InitContext(sal_Int16 nContext);
//STRIP001
//STRIP001  void LoadParams();
//STRIP001  void SaveParams() const;
//STRIP001
//STRIP001 private:
//STRIP001  // Handler fuer die Controls
//STRIP001  DECL_LINK( OnClickedFieldRadios, Button* );
//STRIP001  DECL_LINK( OnClickedSearchAgain, Button* );
//STRIP001  DECL_LINK( OnClickedSpecialSettings, Button* );
//STRIP001
//STRIP001  DECL_LINK( OnSearchTextModified, ComboBox* );
//STRIP001
//STRIP001  DECL_LINK( OnPositionSelected, ListBox* );
//STRIP001  DECL_LINK( OnFieldSelected, ListBox* );
//STRIP001
//STRIP001  DECL_LINK( OnCheckBoxToggled, CheckBox* );
//STRIP001
//STRIP001  DECL_LINK( OnContextSelection, ListBox* );
//STRIP001
//STRIP001  // um sich den Fokus nach einem Found wiederzuholen ... (wenn der Found-Handler das entsprechende Flag zurueckgibt)
//STRIP001  DECL_LINK( AsyncGrabFocus, void* );
//STRIP001
//STRIP001  // Such-Fortschritt
//STRIP001  DECL_LINK( OnSearchProgress, FmSearchProgress* );
//STRIP001
//STRIP001  DECL_LINK( OnDelayedPaint, void* );
//STRIP001      // siehe EnableSearchUI
//STRIP001
//STRIP001  void implMoveControls(Control** _ppControls, sal_Int32 _nControls, sal_Int32 _nUp, Control* _pToResize);
//STRIP001
//STRIP001  void initCommon( const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet >& _rxCursor );
//STRIP001 };

//STRIP001 inline void FmSearchDialog::SetActiveField(const String& strField)
//STRIP001 {
//STRIP001  sal_uInt16 nInitialField = m_lbField.GetEntryPos(strField);
//STRIP001  if (nInitialField == COMBOBOX_ENTRY_NOTFOUND)
//STRIP001      nInitialField = 0;
//STRIP001  m_lbField.SelectEntryPos(nInitialField);
//STRIP001  LINK(this, FmSearchDialog, OnFieldSelected).Call(&m_lbField);
//STRIP001 }

}//end of namespace binfilter
#endif // _FMSEARCH_HXX
