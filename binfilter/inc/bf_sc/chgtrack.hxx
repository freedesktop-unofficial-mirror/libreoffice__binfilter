/*************************************************************************
 *
 *  $RCSfile: chgtrack.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:59:35 $
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

#ifndef SC_CHGTRACK_HXX
#define SC_CHGTRACK_HXX


#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _DATETIME_HXX //autogen
#include <tools/datetime.hxx>
#endif
#ifndef _TOOLS_TABLE_HXX //autogen
#include <tools/table.hxx>
#endif
#ifndef _STACK_HXX //autogen
#include <tools/stack.hxx>
#endif
#ifndef _QUEUE_HXX //autogen
#include <tools/queue.hxx>
#endif
#ifndef _SVMEMPOOL_HXX //autogen
#include <tools/mempool.hxx>
#endif
#ifndef _LINK_HXX //autogen
#include <tools/link.hxx>
#endif
#ifndef _SFXLSTNER_HXX //autogen
#include <svtools/lstner.hxx>
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
#ifndef SC_BIGRANGE_HXX
#include "bigrange.hxx"
#endif
#ifndef SC_COLLECT_HXX
#include "collect.hxx"
#endif

#ifdef SC_CHGTRACK_CXX
// core/inc
#ifndef SC_REFUPDAT_HXX
#include "refupdat.hxx"
#endif
#endif
/*STRIP001 */#include <tools/debug.hxx>
class SvStream;
namespace binfilter {

class ScBaseCell;
class ScDocument;


enum ScChangeActionType
{
    SC_CAT_NONE,
    SC_CAT_INSERT_COLS,
    SC_CAT_INSERT_ROWS,
    SC_CAT_INSERT_TABS,
    SC_CAT_DELETE_COLS,
    SC_CAT_DELETE_ROWS,
    SC_CAT_DELETE_TABS,
    SC_CAT_MOVE,
    SC_CAT_CONTENT,
    SC_CAT_REJECT
};


enum ScChangeActionState
{
    SC_CAS_VIRGIN,
    SC_CAS_ACCEPTED,
    SC_CAS_REJECTED
};


enum ScChangeActionClipMode
{
    SC_CACM_NONE,
    SC_CACM_CUT,
    SC_CACM_COPY,
    SC_CACM_PASTE
};

class ScMultipleReadHeader;
class ScMultipleWriteHeader;

// --- ScChangeActionLinkEntry ---------------------------------------------

// Fuegt sich selbst am Beginn einer Kette ein, bzw. vor einem anderen
// LinkEntry, on delete selbstaendiges ausklinken auch des gelinkten.
// ppPrev == &previous->pNext oder Adresse des Pointers auf Beginn der Kette,
// *ppPrev == this

class ScChangeAction;

class ScChangeActionLinkEntry
{
                                // not implemented, prevent usage
                                ScChangeActionLinkEntry(
                                    const ScChangeActionLinkEntry& );
//STRIP001  ScChangeActionLinkEntry&    operator=( const ScChangeActionLinkEntry& );

protected:

    ScChangeActionLinkEntry*    pNext;
    ScChangeActionLinkEntry**   ppPrev;
    ScChangeAction*             pAction;
    ScChangeActionLinkEntry*    pLink;

public:

    DECL_FIXEDMEMPOOL_NEWDEL( ScChangeActionLinkEntry )

                                ScChangeActionLinkEntry(
                                        ScChangeActionLinkEntry** ppPrevP,
                                        ScChangeAction* pActionP )
                                    :   ppPrev( ppPrevP ),
                                        pNext( *ppPrevP ),
                                        pAction( pActionP ),
                                        pLink( NULL )
                                    {
                                        if ( pNext )
                                            pNext->ppPrev = &pNext;
                                        *ppPrevP = this;
                                    }

    virtual                     ~ScChangeActionLinkEntry()
                                    {
                                        ScChangeActionLinkEntry* p = pLink;
                                        UnLink();
                                        Remove();
                                        if ( p )
                                            delete p;
                                    }

            void                SetLink( ScChangeActionLinkEntry* pLinkP )
                                    {
                                        UnLink();
                                        if ( pLinkP )
                                        {
                                            pLink = pLinkP;
                                            pLinkP->pLink = this;
                                        }
                                    }

            void                UnLink()
                                    {
                                        if ( pLink )
                                        {
                                            pLink->pLink = NULL;
                                            pLink = NULL;
                                        }
                                    }

            void                Remove()
                                    {
                                        if ( ppPrev )
                                        {
                                            if ( *ppPrev = pNext )
                                                pNext->ppPrev = ppPrev;
                                            ppPrev = NULL;  // not inserted
                                        }
                                    }

            void                Insert( ScChangeActionLinkEntry** ppPrevP )
                                    {
                                        if ( !ppPrev )
                                        {
                                            ppPrev = ppPrevP;
                                            if ( pNext = *ppPrevP )
                                                pNext->ppPrev = &pNext;
                                            *ppPrevP = this;
                                        }
                                    }

    const ScChangeActionLinkEntry*  GetLink() const     { return pLink; }
    ScChangeActionLinkEntry*        GetLink()           { return pLink; }
    const ScChangeActionLinkEntry*  GetNext() const     { return pNext; }
    ScChangeActionLinkEntry*        GetNext()           { return pNext; }
    const ScChangeAction*           GetAction() const   { return pAction; }
    ScChangeAction*                 GetAction()         { return pAction; }
};

// --- ScChangeActionCellListEntry -----------------------------------------
// this is only for the XML Export in the hxx
class ScChangeActionContent;

class ScChangeActionCellListEntry
{
    friend class ScChangeAction;
    friend class ScChangeActionDel;
    friend class ScChangeActionMove;
    friend class ScChangeTrack;

            ScChangeActionCellListEntry*    pNext;
            ScChangeActionContent*          pContent;

                                ScChangeActionCellListEntry(
                                    ScChangeActionContent* pContentP,
                                    ScChangeActionCellListEntry* pNextP )
                                    :   pContent( pContentP ),
                                        pNext( pNextP )
                                    {}

public:
    const ScChangeActionCellListEntry* GetNext() const { return pNext; } // this is only for the XML Export public
    const ScChangeActionContent* GetContent() const { return pContent; } // this is only for the XML Export public

    DECL_FIXEDMEMPOOL_NEWDEL( ScChangeActionCellListEntry )
};

// --- ScChangeAction -------------------------------------------------------

class ScChangeTrack;
class ScChangeActionIns;
class ScChangeActionDel;
class ScChangeActionContent;

class ScChangeAction
{
    friend class ScChangeTrack;
    friend class ScChangeActionIns;
    friend class ScChangeActionDel;
    friend class ScChangeActionMove;
    friend class ScChangeActionContent;
//STRIP001
//STRIP001                              // not implemented, prevent usage
//STRIP001                              ScChangeAction( const ScChangeAction& );
            ScChangeAction&     operator=( const ScChangeAction& );
//STRIP001
protected:

             ScBigRange         aBigRange;          // Ins/Del/MoveTo/ContentPos
             DateTime           aDateTime;          //! UTC
             String             aUser;              // wer war's
             String             aComment;           // Benutzerkommentar
             ScChangeAction*        pNext;              // naechster in Kette
             ScChangeAction*        pPrev;              // vorheriger in Kette
             ScChangeActionLinkEntry*   pLinkAny;   // irgendwelche Links
             ScChangeActionLinkEntry*   pLinkDeletedIn; // Zuordnung zu
                                                     // geloeschten oder
                                                     // druebergemoveten oder
                                                     // rejecteten Insert
                                                     // Bereichen
             ScChangeActionLinkEntry*   pLinkDeleted;   // Links zu geloeschten
             ScChangeActionLinkEntry*   pLinkDependent; // Links zu abhaengigen
             ULONG              nAction;
             ULONG              nRejectAction;
             ScChangeActionType eType;
             ScChangeActionState    eState;


                            ScChangeAction( ScChangeActionType,
                                                const ScRange& );

                                 // only to be used in the XML import
                                ScChangeAction( ScChangeActionType,
                                                const ScBigRange&,
                                                const ULONG nAction,
                                                const ULONG nRejectAction,
                                                const ScChangeActionState eState,
                                                const DateTime& aDateTime,
                                                const String& aUser,
                                                const String& aComment );
//STRIP001                              // only to be used in the XML import
                                ScChangeAction( ScChangeActionType,
                                                const ScBigRange&,
                                                const ULONG nAction);

                                ScChangeAction( SvStream&,
                                    ScMultipleReadHeader&, ScChangeTrack* );
    virtual                     ~ScChangeAction();
//STRIP001
//STRIP001  static  void                StoreCell( ScBaseCell*, SvStream&,
//STRIP001                                  ScMultipleWriteHeader& );
//STRIP001  static ScBaseCell*          LoadCell( SvStream&, ScMultipleReadHeader&,
//STRIP001                                  ScDocument*, USHORT nVer );
//STRIP001
//STRIP001  static  BOOL                StoreLinkChain( ScChangeActionLinkEntry*,
//STRIP001                                  SvStream& );
//STRIP001  static  BOOL                LoadLinkChain( ScChangeAction*,
//STRIP001                                  ScChangeActionLinkEntry**,
//STRIP001                                  SvStream&, ScChangeTrack*,
//STRIP001                                  BOOL bLinkDeleted );
//STRIP001
//STRIP001  static  BOOL                StoreCellList( ScChangeActionCellListEntry*,
//STRIP001                                  SvStream& );
//STRIP001  static  BOOL                LoadCellList( ScChangeAction* pOfAction,
//STRIP001                                  ScChangeActionCellListEntry*&, SvStream&,
//STRIP001                                  ScChangeTrack* );
//STRIP001
//STRIP001          String              GetRefString( const ScBigRange&,
//STRIP001                                  ScDocument*, BOOL bFlag3D = FALSE ) const;
//STRIP001
//STRIP001          void                SetActionNumber( ULONG n ) { nAction = n; }
//STRIP001          void                SetRejectAction( ULONG n ) { nRejectAction = n; }
//STRIP001          void                SetUser( const String& r ) { aUser = r; }
//STRIP001          void                SetType( ScChangeActionType e ) { eType = e; }
//STRIP001          void                SetState( ScChangeActionState e ) { eState = e; }
//STRIP001          void                SetRejected();
//STRIP001
            ScBigRange&         GetBigRange() { return aBigRange; }
//STRIP001
//STRIP001          ScChangeActionLinkEntry*    AddLink( ScChangeAction* p,
//STRIP001                                          ScChangeActionLinkEntry* pL )
//STRIP001                                  {
//STRIP001                                      ScChangeActionLinkEntry* pLnk =
//STRIP001                                          new ScChangeActionLinkEntry(
//STRIP001                                          &pLinkAny, p );
//STRIP001                                      pLnk->SetLink( pL );
//STRIP001                                      return pLnk;
//STRIP001                                  }
//STRIP001          void                RemoveLink( ScChangeAction* p );
//STRIP001          void                RemoveAllAnyLinks();
//STRIP001                              // zeigt ein AnyLink auf p?
//STRIP001          BOOL                DependsOn( ScChangeAction* p ) const;
//STRIP001
     virtual    ScChangeActionLinkEntry*    GetDeletedIn() const
                                             { return pLinkDeletedIn; }
//STRIP001  virtual ScChangeActionLinkEntry**   GetDeletedInAddress()
//STRIP001                                          { return &pLinkDeletedIn; }
//STRIP001          ScChangeActionLinkEntry*    AddDeletedIn( ScChangeAction* p )
//STRIP001                                  {
//STRIP001                                      return new ScChangeActionLinkEntry(
//STRIP001                                          GetDeletedInAddress(), p );
//STRIP001                                  }
//STRIP001          BOOL                RemoveDeletedIn( const ScChangeAction* );
//STRIP001          void                RemoveAllDeletedIn();
//STRIP001          void                SetDeletedIn( ScChangeAction* );
//STRIP001
//STRIP001          ScChangeActionLinkEntry*    AddDeleted( ScChangeAction* p )
//STRIP001                                  {
//STRIP001                                      return new ScChangeActionLinkEntry(
//STRIP001                                          &pLinkDeleted, p );
//STRIP001                                  }
//STRIP001          BOOL                RemoveDeleted( const ScChangeAction* p );
//STRIP001          void                RemoveAllDeleted();
//STRIP001
            ScChangeActionLinkEntry*    AddDependent( ScChangeAction* p )
                                    {
                                        return new ScChangeActionLinkEntry(
                                            &pLinkDependent, p );
                                    }
//STRIP001          void                RemoveDependent( ScChangeAction* p );
//STRIP001          void                RemoveAllDependent();
//STRIP001
            void                RemoveAllLinks();
//STRIP001
//STRIP001  virtual void                AddContent( ScChangeActionContent* ) = 0;
//STRIP001  virtual void                DeleteCellEntries() = 0;
//STRIP001
//STRIP001  virtual void                UpdateReference( const ScChangeTrack*,
//STRIP001                                  UpdateRefMode, const ScBigRange&,
//STRIP001                                  INT32 nDx, INT32 nDy, INT32 nDz );
//STRIP001
//STRIP001          void                Accept();
//STRIP001  virtual BOOL                Reject( ScDocument* ) = 0;
//STRIP001          void                RejectRestoreContents( ScChangeTrack*,
//STRIP001                                  short nDx, short nDy );
//STRIP001
//STRIP001                              // used in Reject() instead of IsRejectable()
//STRIP001          BOOL                IsInternalRejectable() const;
//STRIP001
//STRIP001  virtual BOOL                Store( SvStream&, ScMultipleWriteHeader& ) const;
//STRIP001  virtual BOOL                StoreLinks( SvStream& ) const;
//STRIP001  virtual BOOL                LoadLinks( SvStream&, ScChangeTrack* );
//STRIP001
public:
//STRIP001
             BOOL               IsInsertType() const
                                     {
                                         return eType == SC_CAT_INSERT_COLS ||
                                             eType == SC_CAT_INSERT_ROWS ||
                                             eType == SC_CAT_INSERT_TABS;
                                     }
             BOOL               IsDeleteType() const
                                     {
                                         return eType == SC_CAT_DELETE_COLS ||
                                             eType == SC_CAT_DELETE_ROWS ||
                                             eType == SC_CAT_DELETE_TABS;
                                     }
//STRIP001          BOOL                IsVirgin() const
//STRIP001                                  { return eState == SC_CAS_VIRGIN; }
             BOOL               IsAccepted() const
                                     { return eState == SC_CAS_ACCEPTED; }
             BOOL               IsRejected() const
                                     { return eState == SC_CAS_REJECTED; }
//STRIP001
//STRIP001                              // Action rejects another Action
             BOOL               IsRejecting() const
                                     { return nRejectAction != 0; }
//STRIP001
//STRIP001                              // ob Action im Dokument sichtbar ist
//STRIP001          BOOL                IsVisible() const;
//STRIP001
//STRIP001                              // ob Action anfassbar ist
//STRIP001          BOOL                IsTouchable() const;
//STRIP001
//STRIP001                              // ob Action ein Eintrag in Dialog-Root ist
//STRIP001          BOOL                IsDialogRoot() const;
//STRIP001
//STRIP001                              // ob ein Eintrag im Dialog aufklappbar sein soll
//STRIP001          BOOL                IsDialogParent() const;
//STRIP001
//STRIP001                              // ob Action ein Delete ist, unter dem
//STRIP001                              // aufgeklappt mehrere einzelne Deletes sind
//STRIP001          BOOL                IsMasterDelete() const;
//STRIP001
//STRIP001                              // ob Action akzeptiert/selektiert/abgelehnt
//STRIP001                              // werden kann
//STRIP001          BOOL                IsClickable() const;
//STRIP001
//STRIP001                              // ob Action abgelehnt werden kann
//STRIP001          BOOL                IsRejectable() const;
//STRIP001
            const ScBigRange&   GetBigRange() const { return aBigRange; }
//STRIP001          DateTime            GetDateTime() const;        // local time
             const DateTime&        GetDateTimeUTC() const      // UTC time
                                     { return aDateTime; }
            const String&       GetUser() const { return aUser; }
            const String&       GetComment() const { return aComment; }
            ScChangeActionType  GetType() const { return eType; }
//STRIP001          ScChangeActionState GetState() const { return eState; }
            ULONG               GetActionNumber() const { return nAction; }
            ULONG               GetRejectAction() const { return nRejectAction; }
//STRIP001
            ScChangeAction*     GetNext() const { return pNext; }
//STRIP001          ScChangeAction*     GetPrev() const { return pPrev; }
//STRIP001
             BOOL               IsDeletedIn() const
                                     { return GetDeletedIn() != NULL; }
//STRIP001          BOOL                IsDeleted() const
//STRIP001                                  { return IsDeleteType() || IsDeletedIn(); }
//STRIP001          BOOL                IsDeletedIn( const ScChangeAction* ) const;
//STRIP001          BOOL                IsDeletedInDelType( ScChangeActionType ) const;
//STRIP001
             const ScChangeActionLinkEntry* GetFirstDeletedEntry() const
                                     { return pLinkDeleted; }
             const ScChangeActionLinkEntry* GetFirstDependentEntry() const
                                     { return pLinkDependent; }
             BOOL               HasDependent() const
                                     { return pLinkDependent != NULL; }
             BOOL               HasDeleted() const
                                     { return pLinkDeleted != NULL; }
//STRIP001
//STRIP001                              // Description wird an String angehaengt.
//STRIP001                              // Mit bSplitRange wird bei Delete nur
//STRIP001                              // eine Spalte/Zeile beruecksichtigt (fuer
//STRIP001                              // Auflistung der einzelnen Eintraege).
//STRIP001  virtual void                GetDescription( String&, ScDocument*,
//STRIP001                                  BOOL bSplitRange = FALSE ) const {}
//STRIP001
//STRIP001  virtual void                GetRefString( String&, ScDocument*,
//STRIP001                                  BOOL bFlag3D = FALSE ) const;
//STRIP001
//STRIP001                              // fuer DocumentMerge altes Datum einer anderen
//STRIP001                              // Action setzen, mit GetDateTimeUTC geholt
//STRIP001          void                SetDateTimeUTC( const DateTime& rDT )
//STRIP001                                  { aDateTime = rDT; }
//STRIP001
//STRIP001                              // Benutzerkommentar setzen
//STRIP001          void                SetComment( const String& rStr )
//STRIP001                                  { aComment = rStr; }
//STRIP001
//STRIP001                              // only to be used in the XML import
            void                SetDeletedInThis( ULONG nActionNumber,
                                        const ScChangeTrack* pTrack );
//STRIP001                              // only to be used in the XML import
            void                AddDependent( ULONG nActionNumber,
                                        const ScChangeTrack* pTrack );
};


// --- ScChangeActionIns ----------------------------------------------------

class ScChangeActionIns : public ScChangeAction
{
    friend class ScChangeTrack;

                                ScChangeActionIns( const ScRange& rRange );
                                ScChangeActionIns( SvStream&,
                                    ScMultipleReadHeader&, ScChangeTrack* );
    virtual                     ~ScChangeActionIns();
//STRIP001
//STRIP001  virtual void                AddContent( ScChangeActionContent* ) {}
//STRIP001  virtual void                DeleteCellEntries() {}
//STRIP001
//STRIP001  virtual BOOL                Reject( ScDocument* );
//STRIP001
//STRIP001  virtual BOOL                Store( SvStream&, ScMultipleWriteHeader& ) const;
//STRIP001
public:
                                ScChangeActionIns(const ULONG nActionNumber,
                                        const ScChangeActionState eState,
                                        const ULONG nRejectingNumber,
                                        const ScBigRange& aBigRange,
                                        const String& aUser,
                                        const DateTime& aDateTime,
                                        const String &sComment,
                                        const ScChangeActionType eType); // only to use in the XML import

//STRIP001  virtual void                GetDescription( String&, ScDocument*,
//STRIP001                                  BOOL bSplitRange = FALSE ) const;
};


// --- ScChangeActionDel ----------------------------------------------------

class ScChangeActionMove;

class ScChangeActionDelMoveEntry : public ScChangeActionLinkEntry
{
    friend class ScChangeActionDel;
    friend class ScChangeTrack;

            short               nCutOffFrom;
            short               nCutOffTo;


                                ScChangeActionDelMoveEntry(
                                    ScChangeActionDelMoveEntry** ppPrev,
                                    ScChangeActionMove* pMove,
                                    short nFrom, short nTo )
                                    :   ScChangeActionLinkEntry(
                                            (ScChangeActionLinkEntry**)
                                                ppPrev,
                                            (ScChangeAction*) pMove ),
                                        nCutOffFrom( nFrom ),
                                        nCutOffTo( nTo )
                                    {DBG_ASSERT(0, "STRIP");} //STRIP001 {};

//STRIP001          ScChangeActionDelMoveEntry* GetNext()
//STRIP001                                  {
//STRIP001                                      return (ScChangeActionDelMoveEntry*)
//STRIP001                                      ScChangeActionLinkEntry::GetNext();
//STRIP001                                  }
//STRIP001          ScChangeActionMove* GetMove()
//STRIP001                                  {
//STRIP001                                      return (ScChangeActionMove*)
//STRIP001                                      ScChangeActionLinkEntry::GetAction();
//STRIP001                                  }
//STRIP001
public:
             const ScChangeActionDelMoveEntry*  GetNext() const
                                     {
                                         return (const ScChangeActionDelMoveEntry*)
                                         ScChangeActionLinkEntry::GetNext();
                                     }
//STRIP001          const ScChangeActionMove*   GetMove() const
//STRIP001                                  {
//STRIP001                                      return (const ScChangeActionMove*)
//STRIP001                                      ScChangeActionLinkEntry::GetAction();
//STRIP001                                  }
            short               GetCutOffFrom() const { return nCutOffFrom; }
            short               GetCutOffTo() const { return nCutOffTo; }
};


class ScChangeActionDel : public ScChangeAction
{
    friend class ScChangeTrack;
//STRIP001  friend void ScChangeAction::Accept();

            ScChangeTrack*      pTrack;
            ScChangeActionCellListEntry* pFirstCell;
            ScChangeActionIns*  pCutOff;        // abgeschnittener Insert
            short               nCutOff;        // +: Start  -: End
            ScChangeActionDelMoveEntry* pLinkMove;
            short               nDx;
            short               nDy;

                                ScChangeActionDel( const ScRange& rRange,
                                    short nDx, short nDy, ScChangeTrack* );
                                ScChangeActionDel( SvStream&,
                                    ScMultipleReadHeader&, ScDocument*,
                                    USHORT nVer, ScChangeTrack* );
//STRIP001  virtual                     ~ScChangeActionDel();
//STRIP001
            ScChangeActionIns*  GetCutOffInsert() { return pCutOff; }
//STRIP001
//STRIP001  virtual void                AddContent( ScChangeActionContent* );
//STRIP001  virtual void                DeleteCellEntries();
//STRIP001
//STRIP001          void                UndoCutOffMoves();
//STRIP001          void                UndoCutOffInsert();
//STRIP001
//STRIP001  virtual void                UpdateReference( const ScChangeTrack*,
//STRIP001                                  UpdateRefMode, const ScBigRange&,
//STRIP001                                  INT32 nDx, INT32 nDy, INT32 nDz );
//STRIP001
//STRIP001  virtual BOOL                Reject( ScDocument* );
//STRIP001
//STRIP001  virtual BOOL                Store( SvStream&, ScMultipleWriteHeader& ) const;
//STRIP001  virtual BOOL                StoreLinks( SvStream& ) const;
//STRIP001  virtual BOOL                LoadLinks( SvStream&, ScChangeTrack* );
//STRIP001
public:
                                ScChangeActionDel(const ULONG nActionNumber,
                                                const ScChangeActionState eState,
                                                const ULONG nRejectingNumber,
                                                const ScBigRange& aBigRange,
                                                const String& aUser,
                                                const DateTime& aDateTime,
                                                const String &sComment,
                                                const ScChangeActionType eType,
                                                const short nD,
                                                ScChangeTrack* pTrack); // only to use in the XML import
                                                                        // wich of nDx and nDy is set is depend on the type

                                // ob dieses das unterste einer Reihe (oder
                                // auch einzeln) ist
//STRIP001          BOOL                IsBaseDelete() const;

                                // ob dieses das oberste einer Reihe (oder
                                // auch einzeln) ist
//STRIP001          BOOL                IsTopDelete() const;

                                // ob dieses ein Teil einer Reihe ist
            BOOL                IsMultiDelete() const{DBG_ASSERT(0, "STRIP");return FALSE;} //STRIP001 BOOL             IsMultiDelete() const;

                                // ob es eine Col ist, die zu einem TabDelete gehoert
//STRIP001          BOOL                IsTabDeleteCol() const;

            short               GetDx() const { return nDx; }
            short               GetDy() const { return nDy; }
//STRIP001          ScBigRange          GetOverAllRange() const;    // BigRange + (nDx, nDy)

//STRIP001          const ScChangeActionCellListEntry* GetFirstCellEntry() const
//STRIP001                                  { return pFirstCell; }
             const ScChangeActionDelMoveEntry* GetFirstMoveEntry() const
                                     { return pLinkMove; }
            const ScChangeActionIns*    GetCutOffInsert() const { return pCutOff; }
        short               GetCutOffCount() const { return nCutOff; }
//STRIP001
//STRIP001  virtual void                GetDescription( String&, ScDocument*,
//STRIP001                                  BOOL bSplitRange = FALSE ) const;
            void                SetCutOffInsert( ScChangeActionIns* p, short n )
                                    { pCutOff = p; nCutOff = n; }   // only to use in the XML import
//STRIP001                                                                  // this should be protected, but for the XML import it is public
//STRIP001          // only to use in the XML import
//STRIP001          // this should be protected, but for the XML import it is public
            ScChangeActionDelMoveEntry* AddCutOffMove( ScChangeActionMove* pMove,
                                        short nFrom, short nTo )
                                    {
                                        return new ScChangeActionDelMoveEntry(
                                        &pLinkMove, pMove, nFrom, nTo );
                                    }
};


// --- ScChangeActionMove ---------------------------------------------------

class ScChangeActionMove : public ScChangeAction
{
    friend class ScChangeTrack;
//STRIP001  friend void ScChangeActionDel::UndoCutOffMoves();

            ScBigRange          aFromRange;
            ScChangeTrack*      pTrack;
            ScChangeActionCellListEntry* pFirstCell;
            ULONG               nStartLastCut;  // fuer PasteCut Undo
            ULONG               nEndLastCut;

                                ScChangeActionMove( const ScRange& rFromRange,
                                    const ScRange& rToRange,
                                    ScChangeTrack* pTrackP )
                                    : ScChangeAction( SC_CAT_MOVE, rToRange ),
                                        aFromRange( rFromRange ),
                                        pTrack( pTrackP ),
                                        pFirstCell( NULL ),
                                        nStartLastCut(0),
                                        nEndLastCut(0)
                                    {DBG_ASSERT(0, "STRIP");} //STRIP001 {};
                                ScChangeActionMove( SvStream&,
                                    ScMultipleReadHeader&, ScChangeTrack* );
//STRIP001  virtual                     ~ScChangeActionMove();

//STRIP001  virtual void                AddContent( ScChangeActionContent* );
//STRIP001  virtual void                DeleteCellEntries();
//STRIP001
            ScBigRange&         GetFromRange() { return aFromRange; }
//STRIP001
//STRIP001          void                SetStartLastCut( ULONG nVal ) { nStartLastCut = nVal; }
//STRIP001          ULONG               GetStartLastCut() const { return nStartLastCut; }
//STRIP001          void                SetEndLastCut( ULONG nVal ) { nEndLastCut = nVal; }
//STRIP001          ULONG               GetEndLastCut() const { return nEndLastCut; }
//STRIP001
//STRIP001  virtual void                UpdateReference( const ScChangeTrack*,
//STRIP001                                  UpdateRefMode, const ScBigRange&,
//STRIP001                                  INT32 nDx, INT32 nDy, INT32 nDz );
//STRIP001
//STRIP001  virtual BOOL                Reject( ScDocument* );
//STRIP001
//STRIP001  virtual BOOL                Store( SvStream&, ScMultipleWriteHeader& ) const;
//STRIP001  virtual BOOL                StoreLinks( SvStream& ) const;
//STRIP001  virtual BOOL                LoadLinks( SvStream&, ScChangeTrack* );
//STRIP001
public:
                                ScChangeActionMove(const ULONG nActionNumber,
                                                const ScChangeActionState eState,
                                                const ULONG nRejectingNumber,
                                                const ScBigRange& aToBigRange,
                                                const String& aUser,
                                                const DateTime& aDateTime,
                                                const String &sComment,
                                                const ScBigRange& aFromBigRange,
                                                ScChangeTrack* pTrack); // only to use in the XML import
//STRIP001          const ScChangeActionCellListEntry* GetFirstCellEntry() const
//STRIP001                                  { return pFirstCell; } // only to use in the XML export
//STRIP001
            const ScBigRange&   GetFromRange() const { return aFromRange; }
//STRIP001          void                GetDelta( INT32& nDx, INT32& nDy, INT32& nDz ) const;
//STRIP001
//STRIP001  virtual void                GetDescription( String&, ScDocument*,
//STRIP001                                  BOOL bSplitRange = FALSE ) const;
//STRIP001
//STRIP001  virtual void                GetRefString( String&, ScDocument*,
//STRIP001                                  BOOL bFlag3D = FALSE ) const;
};


// --- ScChangeActionContent ------------------------------------------------

enum ScChangeActionContentCellType
{
    SC_CACCT_NONE = 0,
    SC_CACCT_NORMAL,
    SC_CACCT_MATORG,
    SC_CACCT_MATREF
};

class Stack;

class ScChangeActionContent : public ScChangeAction
{
    friend class ScChangeTrack;

            String              aOldValue;
            String              aNewValue;
            ScBaseCell*         pOldCell;
            ScBaseCell*         pNewCell;
        ScChangeActionContent*  pNextContent;   // an gleicher Position
        ScChangeActionContent*  pPrevContent;
        ScChangeActionContent*  pNextInSlot;    // in gleichem Slot
        ScChangeActionContent** ppPrevInSlot;

                                ScChangeActionContent( SvStream&,
                                    ScMultipleReadHeader&, ScDocument*,
                                    USHORT nVer, ScChangeTrack* );

//STRIP001          void                InsertInSlot( ScChangeActionContent** pp )
//STRIP001                                  {
//STRIP001                                      if ( !ppPrevInSlot )
//STRIP001                                      {
//STRIP001                                          ppPrevInSlot = pp;
//STRIP001                                          if ( pNextInSlot = *pp )
//STRIP001                                              pNextInSlot->ppPrevInSlot = &pNextInSlot;
//STRIP001                                          *pp = this;
//STRIP001                                      }
//STRIP001                                  }
//STRIP001          void                RemoveFromSlot()
//STRIP001                                  {
//STRIP001                                      if ( ppPrevInSlot )
//STRIP001                                      {
//STRIP001                                          if ( *ppPrevInSlot = pNextInSlot )
//STRIP001                                              pNextInSlot->ppPrevInSlot = ppPrevInSlot;
//STRIP001                                          ppPrevInSlot = NULL;    // not inserted
//STRIP001                                      }
//STRIP001                                  }
//STRIP001      ScChangeActionContent*  GetNextInSlot() { return pNextInSlot; }
//STRIP001
//STRIP001          void                ClearTrack();
//STRIP001
//STRIP001  static  void                GetStringOfCell( String& rStr,
//STRIP001                                  const ScBaseCell* pCell,
//STRIP001                                  const ScDocument* pDoc,
//STRIP001                                  const ScAddress& rPos );
//STRIP001
//STRIP001  static  void                GetStringOfCell( String& rStr,
//STRIP001                                  const ScBaseCell* pCell,
//STRIP001                                  const ScDocument* pDoc,
//STRIP001                                  ULONG nFormat );
//STRIP001
//STRIP001  static  void                SetValue( String& rStr, ScBaseCell*& pCell,
//STRIP001                                  const ScAddress& rPos,
//STRIP001                                  const ScBaseCell* pOrgCell,
//STRIP001                                  const ScDocument* pFromDoc,
//STRIP001                                  ScDocument* pToDoc );
//STRIP001
//STRIP001  static  void                SetValue( String& rStr, ScBaseCell*& pCell,
//STRIP001                                  ULONG nFormat,
//STRIP001                                  const ScBaseCell* pOrgCell,
//STRIP001                                  const ScDocument* pFromDoc,
//STRIP001                                  ScDocument* pToDoc );
//STRIP001
//STRIP001  static  void                SetCell( String& rStr, ScBaseCell* pCell,
//STRIP001                                  ULONG nFormat, const ScDocument* pDoc );
//STRIP001
//STRIP001  static  BOOL                NeedsNumberFormat( const ScBaseCell* );
//STRIP001
//STRIP001          void                SetValueString( String& rValue,
//STRIP001                                  ScBaseCell*& pCell, const String& rStr,
//STRIP001                                  ScDocument* pDoc );
//STRIP001
//STRIP001          void                GetValueString( String& rStr,
//STRIP001                                  const String& rValue,
//STRIP001                                  const ScBaseCell* pCell ) const;
//STRIP001
//STRIP001          void                GetFormulaString( String& rStr,
//STRIP001                                  const ScFormulaCell* pCell ) const;
//STRIP001
//STRIP001  virtual void                AddContent( ScChangeActionContent* ) {}
//STRIP001  virtual void                DeleteCellEntries() {}
//STRIP001
//STRIP001  virtual void                UpdateReference( const ScChangeTrack*,
//STRIP001                                  UpdateRefMode, const ScBigRange&,
//STRIP001                                  INT32 nDx, INT32 nDy, INT32 nDz );
//STRIP001
//STRIP001  virtual BOOL                Reject( ScDocument* );
//STRIP001
//STRIP001                              // pRejectActions!=NULL: reject actions get
//STRIP001                              // stacked, no SetNewValue, no Append
//STRIP001          BOOL                Select( ScDocument*, ScChangeTrack*,
//STRIP001                                  BOOL bOldest, Stack* pRejectActions );
//STRIP001
//STRIP001          void                PutValueToDoc( ScBaseCell*, const String&,
//STRIP001                                  ScDocument*, short nDx, short nDy ) const;
//STRIP001
//STRIP001  virtual BOOL                Store( SvStream&, ScMultipleWriteHeader& ) const;
//STRIP001  virtual BOOL                StoreLinks( SvStream& ) const;
//STRIP001  virtual BOOL                LoadLinks( SvStream&, ScChangeTrack* );
//STRIP001
public:

    DECL_FIXEDMEMPOOL_NEWDEL( ScChangeActionContent )

                                ScChangeActionContent( const ScRange& rRange )
                                    : ScChangeAction( SC_CAT_CONTENT, rRange ),
                                        pOldCell( NULL ),
                                        pNewCell( NULL ),
                                        pNextContent( NULL ),
                                        pPrevContent( NULL ),
                                        pNextInSlot( NULL ),
                                        ppPrevInSlot( NULL )
                                    {DBG_ASSERT(0, "STRIP");} //STRIP001 {};
                                ScChangeActionContent(const ULONG nActionNumber,
                                                const ScChangeActionState eState,
                                                const ULONG nRejectingNumber,
                                                const ScBigRange& aBigRange,
                                                const String& aUser,
                                                const DateTime& aDateTime,
                                                const String &sComment,
                                                ScBaseCell* pOldCell,
                                                ScDocument* pDoc,
                                                const String& sResult); // to use for XML Import
                                ScChangeActionContent(const ULONG nActionNumber,
                                                ScBaseCell* pNewCell,
                                                const ScBigRange& aBigRange,
                                                ScDocument* pDoc); // to use for XML Import of Generated Actions
//STRIP001  virtual                     ~ScChangeActionContent();
//STRIP001
//STRIP001      ScChangeActionContent*  GetNextContent() const { return pNextContent; }
        ScChangeActionContent*  GetPrevContent() const { return pPrevContent; }
//STRIP001      ScChangeActionContent*  GetTopContent() const;
             BOOL               IsTopContent() const
                                     { return pNextContent == NULL; }
//STRIP001
//STRIP001  virtual ScChangeActionLinkEntry*    GetDeletedIn() const;
//STRIP001  virtual ScChangeActionLinkEntry**   GetDeletedInAddress();
//STRIP001
//STRIP001          void                PutOldValueToDoc( ScDocument*,
//STRIP001                                  short nDx, short nDy ) const;
//STRIP001          void                PutNewValueToDoc( ScDocument*,
//STRIP001                                  short nDx, short nDy ) const;
//STRIP001
//STRIP001          void                SetOldValue( const ScBaseCell*,
//STRIP001                                  const ScDocument* pFromDoc,
//STRIP001                                  ScDocument* pToDoc,
//STRIP001                                  ULONG nFormat );
//STRIP001          void                SetOldValue( const ScBaseCell*,
//STRIP001                                  const ScDocument* pFromDoc,
//STRIP001                                  ScDocument* pToDoc );
//STRIP001          void                SetNewValue( const ScBaseCell*, ScDocument* );
//STRIP001
//STRIP001                              // Used in import filter AppendContentOnTheFly,
//STRIP001                              // takes ownership of cells.
//STRIP001          void                SetOldNewCells( ScBaseCell* pOldCell,
//STRIP001                                  ULONG nOldFormat, ScBaseCell* pNewCell,
//STRIP001                                  ULONG nNewFormat, ScDocument* pDoc );
//STRIP001
//STRIP001                              // Use this only in the XML import,
//STRIP001                              // takes ownership of cell.
            void                SetNewCell( ScBaseCell* pNewCell, ScDocument* pDoc );
//STRIP001
//STRIP001                              // These functions should be protected but for
//STRIP001                              // the XML import they are public.
            void                SetNextContent( ScChangeActionContent* p )
                                    { pNextContent = p; }
            void                SetPrevContent( ScChangeActionContent* p )
                                    { pPrevContent = p; }
//STRIP001
//STRIP001                              // moeglichst nicht verwenden,
//STRIP001                              // setzt nur String bzw. generiert Formelzelle
//STRIP001          void                SetOldValue( const String& rOld, ScDocument* );
//STRIP001          void                SetNewValue( const String& rNew, ScDocument* );
//STRIP001
            void                GetOldString( String& ) const{DBG_ASSERT(0, "STRIP");} //STRIP001 void              GetOldString( String& ) const;
            void                GetNewString( String& ) const{DBG_ASSERT(0, "STRIP");} //STRIP001 void              GetNewString( String& ) const;
            const ScBaseCell*   GetOldCell() const { return pOldCell; }
            const ScBaseCell*   GetNewCell() const { return pNewCell; }
//STRIP001  virtual void                GetDescription( String&, ScDocument*,
//STRIP001                                  BOOL bSplitRange = FALSE ) const;
//STRIP001  virtual void                GetRefString( String&, ScDocument*,
//STRIP001                                  BOOL bFlag3D = FALSE ) const;
//STRIP001
//STRIP001  static  ScChangeActionContentCellType   GetContentCellType( const ScBaseCell* );
//STRIP001
//STRIP001                              // NewCell
//STRIP001          BOOL                IsMatrixOrigin() const
//STRIP001                                  {
//STRIP001                                      return GetContentCellType( GetNewCell() )
//STRIP001                                          == SC_CACCT_MATORG;
//STRIP001                                  }
//STRIP001          BOOL                IsMatrixReference() const
//STRIP001                                  {
//STRIP001                                      return GetContentCellType( GetNewCell() )
//STRIP001                                          == SC_CACCT_MATREF;
//STRIP001                                  }
//STRIP001                              // OldCell
//STRIP001          BOOL                IsOldMatrixOrigin() const
//STRIP001                                  {
//STRIP001                                      return GetContentCellType( GetOldCell() )
//STRIP001                                          == SC_CACCT_MATORG;
//STRIP001                                  }
//STRIP001          BOOL                IsOldMatrixReference() const
//STRIP001                                  {
//STRIP001                                      return GetContentCellType( GetOldCell() )
//STRIP001                                          == SC_CACCT_MATREF;
//STRIP001                                  }
//STRIP001
};


// --- ScChangeActionReject -------------------------------------------------

class Stack;

class ScChangeActionReject : public ScChangeAction
{
    friend class ScChangeTrack;
//STRIP001  friend BOOL ScChangeActionContent::Select( ScDocument*, ScChangeTrack*, BOOL, Stack* );

                                ScChangeActionReject( ULONG nReject )
                                    : ScChangeAction( SC_CAT_REJECT, ScRange() )
                                    {
                                        DBG_ASSERT(0, "STRIP"); //STRIP001 SetRejectAction( nReject );
//STRIP001                                      SetState( SC_CAS_ACCEPTED );
                                    }
                                ScChangeActionReject( SvStream&,
                                    ScMultipleReadHeader&, ScChangeTrack* );

//STRIP001  virtual void                AddContent( ScChangeActionContent* ) {}
//STRIP001  virtual void                DeleteCellEntries() {}
//STRIP001
//STRIP001  virtual BOOL                Reject( ScDocument* p ) { return FALSE; }
//STRIP001
//STRIP001  virtual BOOL                Store( SvStream&, ScMultipleWriteHeader& ) const;
//STRIP001
public:
                                ScChangeActionReject(const ULONG nActionNumber,
                                                const ScChangeActionState eState,
                                                const ULONG nRejectingNumber,
                                                const ScBigRange& aBigRange,
                                                const String& aUser,
                                                const DateTime& aDateTime,
                                                const String &sComment); // only to use in the XML import
};


// --- ScChangeTrack --------------------------------------------------------

enum ScChangeTrackMsgType
{
    SC_CTM_NONE,
    SC_CTM_APPEND,      // Actions angehaengt
    SC_CTM_REMOVE,      // Actions weggenommen
    SC_CTM_CHANGE,      // Actions geaendert
    SC_CTM_PARENT       // war kein Parent und ist jetzt einer
};

struct ScChangeTrackMsgInfo
{
    DECL_FIXEDMEMPOOL_NEWDEL( ScChangeTrackMsgInfo )

    ScChangeTrackMsgType    eMsgType;
    ULONG                   nStartAction;
    ULONG                   nEndAction;
};

// MsgQueue fuer Benachrichtigung via ModifiedLink
//STRIP001 DECLARE_QUEUE( ScChangeTrackMsgQueue, ScChangeTrackMsgInfo* );
//STRIP001 DECLARE_STACK( ScChangeTrackMsgStack, ScChangeTrackMsgInfo* );

enum ScChangeTrackMergeState
{
    SC_CTMS_NONE,
    SC_CTMS_PREPARE,
    SC_CTMS_OWN,
    SC_CTMS_OTHER
};

// zusaetzlich zu pFirst/pNext/pLast/pPrev eine Table, um schnell sowohl
// per ActionNumber als auch ueber Liste zugreifen zu koennen
DECLARE_TABLE( ScChangeActionTable, ScChangeAction* )//STRIP008 ;

// Intern generierte Actions beginnen bei diesem Wert (fast alle Bits gesetzt)
// und werden runtergezaehlt, um sich in einer Table wertemaessig nicht mit den
// "normalen" Actions in die Quere zu kommen.
#define SC_CHGTRACK_GENERATED_START ((UINT32) 0xfffffff0)

// SfxListener an der Applikation, um Aenderungen des Usernamens mitzubekommen

class ScChangeTrack : public SfxListener
{
//STRIP001  friend void ScChangeAction::RejectRestoreContents( ScChangeTrack*, short, short );
//STRIP001  friend BOOL ScChangeActionDel::Reject( ScDocument* pDoc );
//STRIP001  friend void ScChangeActionDel::DeleteCellEntries();
//STRIP001  friend void ScChangeActionMove::DeleteCellEntries();
//STRIP001  friend BOOL ScChangeActionMove::Reject( ScDocument* pDoc );

    static  const USHORT        nContentRowsPerSlot;
    static  const USHORT        nContentSlots;

     ::com::sun::star::uno::Sequence< sal_Int8 >    aProtectPass;
             ScChangeActionTable    aTable;
             ScChangeActionTable    aGeneratedTable;
             ScChangeActionTable    aPasteCutTable;
//STRIP001          ScChangeTrackMsgQueue   aMsgQueue;
//STRIP001          ScChangeTrackMsgStack   aMsgStackTmp;
//STRIP001          ScChangeTrackMsgStack   aMsgStackFinal;
             StrCollection      aUserCollection;
             String             aUser;
             Link               aModifiedLink;
             ScRange                aInDeleteRange;
             DateTime           aFixDateTime;
             ScChangeAction*        pFirst;
             ScChangeAction*        pLast;
         ScChangeActionContent* pFirstGeneratedDelContent;
         ScChangeActionContent**    ppContentSlots;
         ScChangeActionMove*        pLastCutMove;
     ScChangeActionLinkEntry*   pLinkInsertCol;
     ScChangeActionLinkEntry*   pLinkInsertRow;
     ScChangeActionLinkEntry*   pLinkInsertTab;
     ScChangeActionLinkEntry*   pLinkMove;
         ScChangeTrackMsgInfo*  pBlockModifyMsg;
             ScDocument*            pDoc;
             ULONG              nActionMax;
             ULONG              nGeneratedMin;
             ULONG              nMarkLastSaved;
             ULONG              nStartLastCut;
             ULONG              nEndLastCut;
             ULONG              nLastMerge;
         ScChangeTrackMergeState    eMergeState;
             USHORT             nLoadedFileFormatVersion;
             BOOL               bLoadSave;
             BOOL               bInDelete;
             BOOL               bInDeleteUndo;
             BOOL               bInDeleteTop;
             BOOL               bInPasteCut;
             BOOL               bUseFixDateTime;
             BOOL                bTime100thSeconds;

                                // not implemented, prevent usage
                                ScChangeTrack( const ScChangeTrack& ){DBG_ASSERT(0, "STRIP");} //STRIP001 ScChangeTrack( const ScChangeTrack& );
            ScChangeTrack&      operator=( const ScChangeTrack& );

#ifdef SC_CHGTRACK_CXX
    static  USHORT              InitContentRowsPerSlot();

                                // TRUE if one is MM_FORMULA and the other is
                                // not, or if both are and range differs
//STRIP001  static  BOOL                IsMatrixFormulaRangeDifferent(
//STRIP001                                  const ScBaseCell* pOldCell,
//STRIP001                                  const ScBaseCell* pNewCell );

//STRIP001  virtual void                Notify( SfxBroadcaster&, const SfxHint& );
//STRIP001          void                Init();
//STRIP001          void                DtorClear();
//STRIP001          void                SetLoadSave( BOOL bVal ) { bLoadSave = bVal; }
//STRIP001          void                SetInDeleteRange( const ScRange& rRange )
//STRIP001                                  { aInDeleteRange = rRange; }
//STRIP001          void                SetInDelete( BOOL bVal )
//STRIP001                                  { bInDelete = bVal; }
//STRIP001          void                SetInDeleteTop( BOOL bVal )
//STRIP001                                  { bInDeleteTop = bVal; }
//STRIP001          void                SetInDeleteUndo( BOOL bVal )
//STRIP001                                  { bInDeleteUndo = bVal; }
//STRIP001          void                SetInPasteCut( BOOL bVal )
//STRIP001                                  { bInPasteCut = bVal; }
//STRIP001          void                SetMergeState( ScChangeTrackMergeState eState )
//STRIP001                                  { eMergeState = eState; }
//STRIP001      ScChangeTrackMergeState GetMergeState() const { return eMergeState; }
//STRIP001          void                SetLastMerge( ULONG nVal ) { nLastMerge = nVal; }
//STRIP001          ULONG               GetLastMerge() const { return nLastMerge; }
//STRIP001
//STRIP001          void                SetLastCutMoveRange( const ScRange&, ScDocument* );
//STRIP001
//STRIP001                              // ModifyMsg blockweise und nicht einzeln erzeugen
//STRIP001          void                StartBlockModify( ScChangeTrackMsgType,
//STRIP001                                  ULONG nStartAction );
//STRIP001          void                EndBlockModify( ULONG nEndAction );
//STRIP001
//STRIP001          void                AddDependentWithNotify( ScChangeAction* pParent,
//STRIP001                                  ScChangeAction* pDependent );
//STRIP001
//STRIP001          void                Dependencies( ScChangeAction* );
//STRIP001          void                UpdateReference( ScChangeAction*, BOOL bUndo );
//STRIP001          void                UpdateReference( ScChangeAction** ppFirstAction,
//STRIP001                                  ScChangeAction* pAct, BOOL bUndo );
//STRIP001          void                Append( ScChangeAction* pAppend, ULONG nAction );
//STRIP001          void                AppendDeleteRange( const ScRange&,
//STRIP001                                  ScDocument* pRefDoc, short nDz,
//STRIP001                                  ULONG nRejectingInsert );
//STRIP001          void                AppendOneDeleteRange( const ScRange& rOrgRange,
//STRIP001                                  ScDocument* pRefDoc,
//STRIP001                                  short nDx, short nDy, short nDz,
//STRIP001                                  ULONG nRejectingInsert );
//STRIP001          void                LookUpContents( const ScRange& rOrgRange,
//STRIP001                                  ScDocument* pRefDoc,
//STRIP001                                  short nDx, short nDy, short nDz );
//STRIP001          void                Remove( ScChangeAction* );
//STRIP001          void                MasterLinks( ScChangeAction* );
//STRIP001
//STRIP001                              // Content on top an Position
//STRIP001      ScChangeActionContent*  SearchContentAt( const ScBigAddress&,
//STRIP001                                  ScChangeAction* pButNotThis ) const;
//STRIP001                              // das gleiche fuer generierte Del-Eintraege,
//STRIP001                              // wobei der Content nicht in der angegebenen
//STRIP001                              // Richtung geloescht sein darf
//STRIP001      ScChangeActionContent*  SearchGeneratedDelContentAt(
//STRIP001                                  const ScBigAddress&,
//STRIP001                                  ScChangeActionType eNotInDelType ) const;
//STRIP001          void                DeleteGeneratedDelContent(
//STRIP001                                  ScChangeActionContent* );
//STRIP001      ScChangeActionContent*  GenerateDelContent( const ScAddress&,
//STRIP001                                  const ScBaseCell*,
//STRIP001                                  const ScDocument* pFromDoc );
//STRIP001          void                DeleteCellEntries(
//STRIP001                                  ScChangeActionCellListEntry*&,
//STRIP001                                  ScChangeAction* pDeletor );
//STRIP001
//STRIP001                              // Action und alle abhaengigen rejecten,
//STRIP001                              // Table stammt aus vorherigem GetDependents,
//STRIP001                              // ist nur bei Insert und Move (MasterType)
//STRIP001                              // noetig, kann ansonsten NULL sein.
//STRIP001                              // bRecursion == Aufruf aus Reject mit Table
//STRIP001          BOOL                Reject( ScChangeAction*,
//STRIP001                                  ScChangeActionTable*, BOOL bRecursion );
//STRIP001
#endif  // SC_CHGTRACK_CXX
//STRIP001
//STRIP001          void                ClearMsgQueue();
//STRIP001
public:

//STRIP001  static  USHORT              ComputeContentSlot( INT32 nRow )
//STRIP001                                  {
//STRIP001                                      if ( nRow < 0 || nRow > MAXROW )
//STRIP001                                          return nContentSlots - 1;
//STRIP001                                      return nRow / nContentRowsPerSlot;
//STRIP001                                  }

                                ScChangeTrack( ScDocument* ){DBG_ASSERT(0, "STRIP");} //STRIP001 ScChangeTrack( ScDocument* );
                                ScChangeTrack( ScDocument*,
                                            const StrCollection& ) {DBG_ASSERT(0, "STRIP");} //STRIP001 const StrCollection& ); // only to use in the XML import
//STRIP001  virtual                     ~ScChangeTrack();
//STRIP001          void                Clear();
//STRIP001
            ScChangeActionContent*  GetFirstGenerated() const { return pFirstGeneratedDelContent; }
            ScChangeAction*     GetFirst() const { return pFirst; }
            ScChangeAction*     GetLast() const { return pLast; }
            ULONG               GetActionMax() const { return nActionMax; }
             BOOL               IsGenerated( ULONG nAction ) const
                                     { DBG_ASSERT(0, "STRIP");return FALSE;} //STRIP001 { return nAction >= nGeneratedMin;}
            ScChangeAction*     GetAction( ULONG nAction ) const
                                    { return aTable.Get( nAction ); }
//STRIP001          ScChangeAction*     GetGenerated( ULONG nGenerated ) const
//STRIP001                                  { return aGeneratedTable.Get( nGenerated ); }
//STRIP001          ScChangeAction*     GetActionOrGenerated( ULONG nAction ) const
//STRIP001                                  {
//STRIP001                                      return IsGenerated( nAction ) ?
//STRIP001                                          GetGenerated( nAction ) :
//STRIP001                                          GetAction( nAction );
//STRIP001                                  }
//STRIP001          ULONG               GetLastSavedActionNumber() const
//STRIP001                                  { return nMarkLastSaved; }
            void                SetLastSavedActionNumber(ULONG nNew)
                                    { nMarkLastSaved = nNew; }
//STRIP001          ScChangeAction*     GetLastSaved() const
//STRIP001                                  { return aTable.Get( nMarkLastSaved ); }
//STRIP001      ScChangeActionContent** GetContentSlots() const { return ppContentSlots; }
//STRIP001
//STRIP001          BOOL                IsLoadSave() const { return bLoadSave; }
//STRIP001          const ScRange&      GetInDeleteRange() const
//STRIP001                                  { return aInDeleteRange; }
//STRIP001          BOOL                IsInDelete() const { return bInDelete; }
//STRIP001          BOOL                IsInDeleteTop() const { return bInDeleteTop; }
            BOOL                IsInDeleteUndo() const { return bInDeleteUndo; }
//STRIP001          BOOL                IsInPasteCut() const { return bInPasteCut; }
//STRIP001          void                SetUser( const String& );
//STRIP001          const String&       GetUser() const { return aUser; }
            const StrCollection&    GetUserCollection() const
                                    { return aUserCollection; }
//STRIP001          ScDocument*         GetDocument() const { return pDoc; }
//STRIP001                              // for import filter
//STRIP001          const DateTime&     GetFixDateTime() const { return aFixDateTime; }
//STRIP001
//STRIP001                              // set this if the date/time set with
//STRIP001                              // SetFixDateTime...() shall be applied to
//STRIP001                              // appended actions
//STRIP001          void                SetUseFixDateTime( BOOL bVal )
//STRIP001                                  { bUseFixDateTime = bVal; }
//STRIP001                              // for MergeDocument, apply original date/time as UTC
//STRIP001          void                SetFixDateTimeUTC( const DateTime& rDT )
//STRIP001                                  { aFixDateTime = rDT; }
//STRIP001                              // for import filter, apply original date/time as local time
//STRIP001          void                SetFixDateTimeLocal( const DateTime& rDT )
//STRIP001                                  { aFixDateTime = rDT; aFixDateTime.ConvertToUTC(); }
//STRIP001
//STRIP001          void                Append( ScChangeAction* );
//STRIP001
//STRIP001                              // pRefDoc may be NULL => no lookup of contents
//STRIP001                              // => no generation of deleted contents
//STRIP001          void                AppendDeleteRange( const ScRange&,
//STRIP001                                  ScDocument* pRefDoc,
//STRIP001                                  ULONG& nStartAction, ULONG& nEndAction,
//STRIP001                                  short nDz = 0 );
//STRIP001                                  // nDz: Multi-TabDel, LookUpContent ist
//STRIP001                                  // um -nDz verschoben zu suchen
//STRIP001
//STRIP001                              // nachdem neuer Wert im Dokument gesetzt wurde,
//STRIP001                              // alter Wert aus RefDoc/UndoDoc
//STRIP001          void                AppendContent( const ScAddress& rPos,
//STRIP001                                  ScDocument* pRefDoc );
//STRIP001                              // nachdem neue Werte im Dokument gesetzt wurden,
//STRIP001                              // alte Werte aus RefDoc/UndoDoc
//STRIP001          void                AppendContentRange( const ScRange& rRange,
//STRIP001                                  ScDocument* pRefDoc,
//STRIP001                                  ULONG& nStartAction, ULONG& nEndAction,
//STRIP001                                  ScChangeActionClipMode eMode = SC_CACM_NONE );
//STRIP001                              // nachdem neuer Wert im Dokument gesetzt wurde,
//STRIP001                              // alter Wert aus pOldCell, nOldFormat,
//STRIP001                              // RefDoc==NULL => Doc
//STRIP001          void                AppendContent( const ScAddress& rPos,
//STRIP001                                  const ScBaseCell* pOldCell,
//STRIP001                                  ULONG nOldFormat, ScDocument* pRefDoc = NULL );
//STRIP001                              // nachdem neuer Wert im Dokument gesetzt wurde,
//STRIP001                              // alter Wert aus pOldCell, Format aus Doc
//STRIP001          void                AppendContent( const ScAddress& rPos,
//STRIP001                                  const ScBaseCell* pOldCell );
//STRIP001                              // nachdem neuer Wert im Dokument gesetzt wurde,
//STRIP001                              // alter Wert aus pOldCell, Format aus RefDoc
//STRIP001          void                AppendContent( const ScAddress& rPos,
//STRIP001                                  const ScBaseCell* pOldCell,
//STRIP001                                  ScDocument* pRefDoc );
//STRIP001                              // nachdem neue Werte im Dokument gesetzt wurden,
//STRIP001                              // alte Werte aus RefDoc/UndoDoc.
//STRIP001                              // Alle Contents, wo im RefDoc eine Zelle steht.
//STRIP001          void                AppendContentsIfInRefDoc( ScDocument* pRefDoc,
//STRIP001                                  ULONG& nStartAction, ULONG& nEndAction );
//STRIP001
//STRIP001                              // Meant for import filter, creates and inserts
//STRIP001                              // an unconditional content action of the two
//STRIP001                              // cells without querying the document, not
//STRIP001                              // even for number formats (though the number
//STRIP001                              // formatter of the document may be used).
//STRIP001                              // The action is returned and may be used to
//STRIP001                              // set user name, description, date/time et al.
//STRIP001                              // Takes ownership of the cells!
//STRIP001      ScChangeActionContent*  AppendContentOnTheFly( const ScAddress& rPos,
//STRIP001                                  ScBaseCell* pOldCell,
//STRIP001                                  ScBaseCell* pNewCell,
//STRIP001                                  ULONG nOldFormat = 0,
//STRIP001                                  ULONG nNewFormat = 0 );
//STRIP001
//STRIP001                              // die folgenden beiden nur benutzen wenn's
//STRIP001                              // nicht anders geht (setzen nur String fuer
//STRIP001                              // NewValue bzw. Formelerzeugung)
//STRIP001
//STRIP001                              // bevor neuer Wert im Dokument gesetzt wird
//STRIP001          void                AppendContent( const ScAddress& rPos,
//STRIP001                                  const String& rNewValue );
//STRIP001                              // bevor neuer Wert im Dokument gesetzt wird
//STRIP001          void                AppendContent( const ScAddress& rPos,
//STRIP001                                  const String& rNewValue,
//STRIP001                                  ScBaseCell* pOldCell );
//STRIP001
//STRIP001          void                AppendInsert( const ScRange& );
//STRIP001
//STRIP001                              // pRefDoc may be NULL => no lookup of contents
//STRIP001                              // => no generation of deleted contents
//STRIP001          void                AppendMove( const ScRange& rFromRange,
//STRIP001                                  const ScRange& rToRange,
//STRIP001                                  ScDocument* pRefDoc );
//STRIP001
//STRIP001                              // Cut to Clipboard
//STRIP001          void                ResetLastCut()
//STRIP001                                  {
//STRIP001                                      nStartLastCut = nEndLastCut = 0;
//STRIP001                                      if ( pLastCutMove )
//STRIP001                                      {
//STRIP001                                          delete pLastCutMove;
//STRIP001                                          pLastCutMove = NULL;
//STRIP001                                      }
//STRIP001                                  }
//STRIP001          BOOL                HasLastCut() const
//STRIP001                                  {
//STRIP001                                      return nEndLastCut > 0 &&
//STRIP001                                          nStartLastCut <= nEndLastCut &&
//STRIP001                                          pLastCutMove;
//STRIP001                                  }
//STRIP001
//STRIP001          void                Undo( ULONG nStartAction, ULONG nEndAction );
//STRIP001
//STRIP001                              // fuer MergeDocument, Referenzen anpassen,
//STRIP001                              //! darf nur in einem temporaer geoeffneten
//STRIP001                              //! Dokument verwendet werden, der Track
//STRIP001                              //! ist danach verhunzt
//STRIP001          void                MergePrepare( ScChangeAction* pFirstMerge );
//STRIP001          void                MergeOwn( ScChangeAction* pAct, ULONG nFirstMerge );
//STRIP001  static  BOOL                MergeIgnore( const ScChangeAction&, ULONG nFirstMerge );
//STRIP001
//STRIP001                              // Abhaengige in Table einfuegen.
//STRIP001                              // Bei Insert sind es echte Abhaengige,
//STRIP001                              // bei Move abhaengige Contents im FromRange
//STRIP001                              // und geloeschte im ToRange bzw. Inserts in
//STRIP001                              // FromRange oder ToRange,
//STRIP001                              // bei Delete eine Liste der geloeschten,
//STRIP001                              // bei Content andere Contents an gleicher
//STRIP001                              // Position oder MatrixReferences zu MatrixOrigin.
//STRIP001                              // Mit bListMasterDelete werden unter einem
//STRIP001                              // MasterDelete alle zu diesem Delete gehoerenden
//STRIP001                              // Deletes einer Reihe gelistet.
//STRIP001                              // Mit bAllFlat werden auch alle Abhaengigen
//STRIP001                              // der Abhaengigen flach eingefuegt.
//STRIP001          void                GetDependents( ScChangeAction*,
//STRIP001                                  ScChangeActionTable&,
//STRIP001                                  BOOL bListMasterDelete = FALSE,
//STRIP001                                  BOOL bAllFlat = FALSE );
//STRIP001
//STRIP001                              // Reject visible Action (und abhaengige)
//STRIP001          BOOL                Reject( ScChangeAction* );
//STRIP001
//STRIP001                              // Accept visible Action (und abhaengige)
//STRIP001          BOOL                Accept( ScChangeAction* );
//STRIP001
//STRIP001          void                AcceptAll();    // alle Virgins
//STRIP001          BOOL                RejectAll();    // alle Virgins
//STRIP001
//STRIP001                              // Selektiert einen Content von mehreren an
//STRIP001                              // gleicher Position und akzeptiert diesen und
//STRIP001                              // die aelteren, rejected die neueren.
//STRIP001                              // Mit bOldest==TRUE wird der erste OldValue
//STRIP001                              // einer Virgin-Content-Kette restauriert.
//STRIP001          BOOL                SelectContent( ScChangeAction*,
//STRIP001                                  BOOL bOldest = FALSE );
//STRIP001
//STRIP001                              // wenn ModifiedLink gesetzt, landen
//STRIP001                              // Aenderungen in ScChangeTrackMsgQueue
//STRIP001          void                SetModifiedLink( const Link& r )
//STRIP001                                  { aModifiedLink = r; ClearMsgQueue(); }
//STRIP001          const Link&         GetModifiedLink() const { return aModifiedLink; }
//STRIP001          ScChangeTrackMsgQueue& GetMsgQueue() { return aMsgQueue; }
//STRIP001
//STRIP001          void                NotifyModified( ScChangeTrackMsgType eMsgType,
//STRIP001                                  ULONG nStartAction, ULONG nEndAction );
//STRIP001
//STRIP001          BOOL                Load( SvStream& rStrm, USHORT nVer );
//STRIP001          BOOL                Store( SvStream& rStrm );
//STRIP001          USHORT              GetLoadedFileFormatVersion() const
//STRIP001                                  { return nLoadedFileFormatVersion; }
//STRIP001
            ULONG               AddLoadedGenerated(ScBaseCell* pOldCell,
                                                const ScBigRange& aBigRange ); // only to use in the XML import
             void               AppendLoaded( ScChangeAction* pAppend ); // this is only for the XML import public, it should be protected
             void               SetActionMax(ULONG nTempActionMax)
                                    { nActionMax = nTempActionMax; } // only to use in the XML import
//STRIP001
            void                SetProtection( const ::com::sun::star::uno::Sequence< sal_Int8 >& rPass )
                                    { aProtectPass = rPass; }
     ::com::sun::star::uno::Sequence< sal_Int8 >   GetProtection() const
                                     { return aProtectPass; }
             BOOL                IsProtected() const
                                     { return aProtectPass.getLength() != 0; }
//STRIP001
//STRIP001                                 // If time stamps of actions of this
//STRIP001                                 // ChangeTrack and a second one are to be
//STRIP001                                 // compared including 100th seconds.
            void                SetTime100thSeconds( BOOL bVal )
                                    { bTime100thSeconds = bVal; }
//STRIP001             BOOL                IsTime100thSeconds() const
//STRIP001                                     { return bTime100thSeconds; }
};


} //namespace binfilter
#endif


