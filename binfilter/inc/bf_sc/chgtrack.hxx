/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: chgtrack.hxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:29:32 $
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

#ifndef SC_CHGTRACK_HXX
#define SC_CHGTRACK_HXX


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
#ifndef _SFXLSTNER_HXX //autogen
#include <svtools/lstner.hxx>
#endif

#ifndef SC_BIGRANGE_HXX
#include "bigrange.hxx"
#endif
#ifndef SC_COLLECT_HXX
#include "collect.hxx"
#endif

#ifdef SC_CHGTRACK_CXX
// core/inc
#endif
/*N*/#include <tools/debug.hxx>
/*N*/
class SvStream;
/*N*/class Stack;
/*N*/
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
/*N*/   ScChangeActionLinkEntry&    operator=( const ScChangeActionLinkEntry& );

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
/*N*/
/*N*/                               // not implemented, prevent usage
/*N*/                               ScChangeAction( const ScChangeAction& );
            ScChangeAction&     operator=( const ScChangeAction& );
/*N*/
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
/*N*/                               // only to be used in the XML import
                                ScChangeAction( ScChangeActionType,
                                                const ScBigRange&,
                                                const ULONG nAction);

                                ScChangeAction( SvStream&,
                                    ScMultipleReadHeader&, ScChangeTrack* );
    virtual                     ~ScChangeAction();
/*N*/
/*N*/   static  void                StoreCell( ScBaseCell*, SvStream&,
/*N*/                                   ScMultipleWriteHeader& );
/*N*/   static ScBaseCell*          LoadCell( SvStream&, ScMultipleReadHeader&,
/*N*/                                   ScDocument*, USHORT nVer );
/*N*/
/*N*/   static  BOOL                StoreLinkChain( ScChangeActionLinkEntry*,
/*N*/                                   SvStream& );
/*N*/   static  BOOL                LoadLinkChain( ScChangeAction*,
/*N*/                                   ScChangeActionLinkEntry**,
/*N*/                                   SvStream&, ScChangeTrack*,
/*N*/                                   BOOL bLinkDeleted );
/*N*/
/*N*/   static  BOOL                StoreCellList( ScChangeActionCellListEntry*,
/*N*/                                   SvStream& );
/*N*/   static  BOOL                LoadCellList( ScChangeAction* pOfAction,
/*N*/                                   ScChangeActionCellListEntry*&, SvStream&,
/*N*/                                   ScChangeTrack* );
/*N*/
/*N*/           String              GetRefString( const ScBigRange&,
/*N*/                                   ScDocument*, BOOL bFlag3D = FALSE ) const;
/*N*/
/*N*/           void                SetActionNumber( ULONG n ) { nAction = n; }
/*N*/           void                SetRejectAction( ULONG n ) { nRejectAction = n; }
/*N*/           void                SetUser( const String& r ) { aUser = r; }
/*N*/           void                SetType( ScChangeActionType e ) { eType = e; }
/*N*/           void                SetState( ScChangeActionState e ) { eState = e; }
/*N*/           void                SetRejected();
/*N*/
            ScBigRange&         GetBigRange() { return aBigRange; }
/*N*/
/*N*/           ScChangeActionLinkEntry*    AddLink( ScChangeAction* p,
/*N*/                                           ScChangeActionLinkEntry* pL )
/*N*/                                   {
/*N*/                                       ScChangeActionLinkEntry* pLnk =
/*N*/                                           new ScChangeActionLinkEntry(
/*N*/                                           &pLinkAny, p );
/*N*/                                       pLnk->SetLink( pL );
/*N*/                                       return pLnk;
/*N*/                                   }
/*N*/           void                RemoveLink( ScChangeAction* p );
/*N*/           void                RemoveAllAnyLinks();
/*N*/                               // zeigt ein AnyLink auf p?
/*N*/           BOOL                DependsOn( ScChangeAction* p ) const;
/*N*/
     virtual    ScChangeActionLinkEntry*    GetDeletedIn() const
                                             { return pLinkDeletedIn; }
/*N*/   virtual ScChangeActionLinkEntry**   GetDeletedInAddress()
/*N*/                                           { return &pLinkDeletedIn; }
/*N*/           ScChangeActionLinkEntry*    AddDeletedIn( ScChangeAction* p )
/*N*/                                   {
/*N*/                                       return new ScChangeActionLinkEntry(
/*N*/                                           GetDeletedInAddress(), p );
/*N*/                                   }
/*N*/           BOOL                RemoveDeletedIn( const ScChangeAction* );
/*N*/           void                RemoveAllDeletedIn();
/*N*/           void                SetDeletedIn( ScChangeAction* );
/*N*/
/*N*/           ScChangeActionLinkEntry*    AddDeleted( ScChangeAction* p )
/*N*/                                   {
/*N*/                                       return new ScChangeActionLinkEntry(
/*N*/                                           &pLinkDeleted, p );
/*N*/                                   }
/*N*/           BOOL                RemoveDeleted( const ScChangeAction* p );
/*N*/           void                RemoveAllDeleted();
/*N*/
            ScChangeActionLinkEntry*    AddDependent( ScChangeAction* p )
                                    {
                                        return new ScChangeActionLinkEntry(
                                            &pLinkDependent, p );
                                    }
/*N*/           void                RemoveDependent( ScChangeAction* p );
/*N*/           void                RemoveAllDependent();
/*N*/
            void                RemoveAllLinks();
/*N*/
/*N*/   virtual void                AddContent( ScChangeActionContent* ) = 0;
/*N*/   virtual void                DeleteCellEntries() = 0;
/*N*/
/*N*/   virtual void                UpdateReference( const ScChangeTrack*,
/*N*/                                   UpdateRefMode, const ScBigRange&,
/*N*/                                   INT32 nDx, INT32 nDy, INT32 nDz );
/*N*/
/*N*/           void                Accept();
/*N*/   virtual BOOL                Reject( ScDocument* ) = 0;
/*N*/           void                RejectRestoreContents( ScChangeTrack*,
/*N*/                                   short nDx, short nDy );
/*N*/
/*N*/                               // used in Reject() instead of IsRejectable()
/*N*/           BOOL                IsInternalRejectable() const;
/*N*/
/*N*/   virtual BOOL                Store( SvStream&, ScMultipleWriteHeader& ) const;
/*N*/   virtual BOOL                StoreLinks( SvStream& ) const;
/*N*/   virtual BOOL                LoadLinks( SvStream&, ScChangeTrack* );
/*N*/
public:
/*N*/
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
/*N*/           BOOL                IsVirgin() const
/*N*/                                   { return eState == SC_CAS_VIRGIN; }
             BOOL               IsAccepted() const
                                     { return eState == SC_CAS_ACCEPTED; }
             BOOL               IsRejected() const
                                     { return eState == SC_CAS_REJECTED; }
/*N*/
/*N*/                               // Action rejects another Action
             BOOL               IsRejecting() const
                                     { return nRejectAction != 0; }
/*N*/
/*N*/                               // ob Action im Dokument sichtbar ist
/*N*/           BOOL                IsVisible() const;
/*N*/
/*N*/                               // ob Action anfassbar ist
/*N*/           BOOL                IsTouchable() const;
/*N*/
/*N*/                               // ob Action ein Eintrag in Dialog-Root ist
/*N*/           BOOL                IsDialogRoot() const;
/*N*/
/*N*/                               // ob ein Eintrag im Dialog aufklappbar sein soll
/*N*/           BOOL                IsDialogParent() const;
/*N*/
/*N*/                               // ob Action ein Delete ist, unter dem
/*N*/                               // aufgeklappt mehrere einzelne Deletes sind
/*N*/           BOOL                IsMasterDelete() const;
/*N*/
/*N*/                               // ob Action akzeptiert/selektiert/abgelehnt
/*N*/                               // werden kann
/*N*/           BOOL                IsClickable() const;
/*N*/
/*N*/                               // ob Action abgelehnt werden kann
/*N*/           BOOL                IsRejectable() const;
/*N*/
            const ScBigRange&   GetBigRange() const { return aBigRange; }
/*N*/           DateTime            GetDateTime() const;        // local time
             const DateTime&        GetDateTimeUTC() const      // UTC time
                                     { return aDateTime; }
            const String&       GetUser() const { return aUser; }
            const String&       GetComment() const { return aComment; }
            ScChangeActionType  GetType() const { return eType; }
/*N*/           ScChangeActionState GetState() const { return eState; }
            ULONG               GetActionNumber() const { return nAction; }
            ULONG               GetRejectAction() const { return nRejectAction; }
/*N*/
            ScChangeAction*     GetNext() const { return pNext; }
/*N*/           ScChangeAction*     GetPrev() const { return pPrev; }
/*N*/
             BOOL               IsDeletedIn() const
                                     { return GetDeletedIn() != NULL; }
/*N*/           BOOL                IsDeleted() const
/*N*/                                   { return IsDeleteType() || IsDeletedIn(); }
/*N*/           BOOL                IsDeletedIn( const ScChangeAction* ) const;
/*N*/           BOOL                IsDeletedInDelType( ScChangeActionType ) const;
/*N*/
             const ScChangeActionLinkEntry* GetFirstDeletedEntry() const
                                     { return pLinkDeleted; }
             const ScChangeActionLinkEntry* GetFirstDependentEntry() const
                                     { return pLinkDependent; }
             BOOL               HasDependent() const
                                     { return pLinkDependent != NULL; }
             BOOL               HasDeleted() const
                                     { return pLinkDeleted != NULL; }
/*N*/
/*N*/                               // Description wird an String angehaengt.
/*N*/                               // Mit bSplitRange wird bei Delete nur
/*N*/                               // eine Spalte/Zeile beruecksichtigt (fuer
/*N*/                               // Auflistung der einzelnen Eintraege).
/*N*/   virtual void                GetDescription( String&, ScDocument*,
/*N*/                                   BOOL bSplitRange = FALSE ) const {}
/*N*/
/*N*/   virtual void                GetRefString( String&, ScDocument*,
/*N*/                                   BOOL bFlag3D = FALSE ) const;
/*N*/
/*N*/                               // fuer DocumentMerge altes Datum einer anderen
/*N*/                               // Action setzen, mit GetDateTimeUTC geholt
/*N*/           void                SetDateTimeUTC( const DateTime& rDT )
/*N*/                                   { aDateTime = rDT; }
/*N*/
/*N*/                               // Benutzerkommentar setzen
/*N*/           void                SetComment( const String& rStr )
/*N*/                                   { aComment = rStr; }
/*N*/
/*N*/                               // only to be used in the XML import
            void                SetDeletedInThis( ULONG nActionNumber,
                                        const ScChangeTrack* pTrack );
/*N*/                               // only to be used in the XML import
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
/*N*/
/*N*/   virtual void                AddContent( ScChangeActionContent* ) {}
/*N*/   virtual void                DeleteCellEntries() {}
/*N*/
/*N*/   virtual BOOL                Reject( ScDocument* );
/*N*/
/*N*/   virtual BOOL                Store( SvStream&, ScMultipleWriteHeader& ) const;
/*N*/
public:
                                ScChangeActionIns(const ULONG nActionNumber,
                                        const ScChangeActionState eState,
                                        const ULONG nRejectingNumber,
                                        const ScBigRange& aBigRange,
                                        const String& aUser,
                                        const DateTime& aDateTime,
                                        const String &sComment,
                                        const ScChangeActionType eType); // only to use in the XML import

/*N*/   virtual void                GetDescription( String&, ScDocument*,
/*N*/                                   BOOL bSplitRange = FALSE ) const;
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
/*N*/                                   {};

/*N*/           ScChangeActionDelMoveEntry* GetNext()
/*N*/                                   {
/*N*/                                       return (ScChangeActionDelMoveEntry*)
/*N*/                                       ScChangeActionLinkEntry::GetNext();
/*N*/                                   }
/*N*/           ScChangeActionMove* GetMove()
/*N*/                                   {
/*N*/                                       return (ScChangeActionMove*)
/*N*/                                       ScChangeActionLinkEntry::GetAction();
/*N*/                                   }
/*N*/
public:
             const ScChangeActionDelMoveEntry*  GetNext() const
                                     {
                                         return (const ScChangeActionDelMoveEntry*)
                                         ScChangeActionLinkEntry::GetNext();
                                     }
/*N*/           const ScChangeActionMove*   GetMove() const
/*N*/                                   {
/*N*/                                       return (const ScChangeActionMove*)
/*N*/                                       ScChangeActionLinkEntry::GetAction();
/*N*/                                   }
            short               GetCutOffFrom() const { return nCutOffFrom; }
            short               GetCutOffTo() const { return nCutOffTo; }
};


class ScChangeActionDel : public ScChangeAction
{
    friend class ScChangeTrack;
/*N*/   friend class ScChangeAction;

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
/*N*/   virtual                     ~ScChangeActionDel();
/*N*/
            ScChangeActionIns*  GetCutOffInsert() { return pCutOff; }
/*N*/
/*N*/   virtual void                AddContent( ScChangeActionContent* );
/*N*/   virtual void                DeleteCellEntries();
/*N*/
/*N*/           void                UndoCutOffMoves();
/*N*/           void                UndoCutOffInsert();
/*N*/
/*N*/   virtual void                UpdateReference( const ScChangeTrack*,
/*N*/                                   UpdateRefMode, const ScBigRange&,
/*N*/                                   INT32 nDx, INT32 nDy, INT32 nDz );
/*N*/
/*N*/   virtual BOOL                Reject( ScDocument* );
/*N*/
/*N*/   virtual BOOL                Store( SvStream&, ScMultipleWriteHeader& ) const;
/*N*/   virtual BOOL                StoreLinks( SvStream& ) const;
/*N*/   virtual BOOL                LoadLinks( SvStream&, ScChangeTrack* );
/*N*/
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
/*N*/           BOOL                IsBaseDelete() const;

                                // ob dieses das oberste einer Reihe (oder
                                // auch einzeln) ist
/*N*/           BOOL                IsTopDelete() const;

                                // ob dieses ein Teil einer Reihe ist
/*N*/           BOOL                IsMultiDelete() const;

                                // ob es eine Col ist, die zu einem TabDelete gehoert
/*N*/           BOOL                IsTabDeleteCol() const;

            short               GetDx() const { return nDx; }
            short               GetDy() const { return nDy; }
/*N*/           ScBigRange          GetOverAllRange() const;    // BigRange + (nDx, nDy)

/*N*/           const ScChangeActionCellListEntry* GetFirstCellEntry() const
/*N*/                                   { return pFirstCell; }
             const ScChangeActionDelMoveEntry* GetFirstMoveEntry() const
                                     { return pLinkMove; }
            const ScChangeActionIns*    GetCutOffInsert() const { return pCutOff; }
        short               GetCutOffCount() const { return nCutOff; }
/*N*/
/*N*/   virtual void                GetDescription( String&, ScDocument*,
/*N*/                                   BOOL bSplitRange = FALSE ) const;
            void                SetCutOffInsert( ScChangeActionIns* p, short n )
                                    { pCutOff = p; nCutOff = n; }   // only to use in the XML import
/*N*/                                                                   // this should be protected, but for the XML import it is public
/*N*/           // only to use in the XML import
/*N*/           // this should be protected, but for the XML import it is public
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
/*N*/   friend class ScChangeActionDel;

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
/*N*/                                   {};
                                ScChangeActionMove( SvStream&,
                                    ScMultipleReadHeader&, ScChangeTrack* );
/*N*/   virtual                     ~ScChangeActionMove();

/*N*/   virtual void                AddContent( ScChangeActionContent* );
/*N*/   virtual void                DeleteCellEntries();
/*N*/
            ScBigRange&         GetFromRange() { return aFromRange; }
/*N*/
/*N*/           void                SetStartLastCut( ULONG nVal ) { nStartLastCut = nVal; }
/*N*/           ULONG               GetStartLastCut() const { return nStartLastCut; }
/*N*/           void                SetEndLastCut( ULONG nVal ) { nEndLastCut = nVal; }
/*N*/           ULONG               GetEndLastCut() const { return nEndLastCut; }
/*N*/
/*N*/   virtual void                UpdateReference( const ScChangeTrack*,
/*N*/                                   UpdateRefMode, const ScBigRange&,
/*N*/                                   INT32 nDx, INT32 nDy, INT32 nDz );
/*N*/
/*N*/   virtual BOOL                Reject( ScDocument* );
/*N*/
/*N*/   virtual BOOL                Store( SvStream&, ScMultipleWriteHeader& ) const;
/*N*/   virtual BOOL                StoreLinks( SvStream& ) const;
/*N*/   virtual BOOL                LoadLinks( SvStream&, ScChangeTrack* );
/*N*/
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
/*N*/           const ScChangeActionCellListEntry* GetFirstCellEntry() const
/*N*/                                   { return pFirstCell; } // only to use in the XML export
/*N*/
            const ScBigRange&   GetFromRange() const { return aFromRange; }
/*N*/           void                GetDelta( INT32& nDx, INT32& nDy, INT32& nDz ) const;
/*N*/
/*N*/   virtual void                GetDescription( String&, ScDocument*,
/*N*/                                   BOOL bSplitRange = FALSE ) const;
/*N*/
/*N*/   virtual void                GetRefString( String&, ScDocument*,
/*N*/                                   BOOL bFlag3D = FALSE ) const;
};


// --- ScChangeActionContent ------------------------------------------------

enum ScChangeActionContentCellType
{
    SC_CACCT_NONE = 0,
    SC_CACCT_NORMAL,
    SC_CACCT_MATORG,
    SC_CACCT_MATREF
};

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

/*N*/           void                InsertInSlot( ScChangeActionContent** pp )
/*N*/                                   {
/*N*/                                       if ( !ppPrevInSlot )
/*N*/                                       {
/*N*/                                           ppPrevInSlot = pp;
/*N*/                                           if ( pNextInSlot = *pp )
/*N*/                                               pNextInSlot->ppPrevInSlot = &pNextInSlot;
/*N*/                                           *pp = this;
/*N*/                                       }
/*N*/                                   }
/*N*/           void                RemoveFromSlot()
/*N*/                                   {
/*N*/                                       if ( ppPrevInSlot )
/*N*/                                       {
/*N*/                                           if ( *ppPrevInSlot = pNextInSlot )
/*N*/                                               pNextInSlot->ppPrevInSlot = ppPrevInSlot;
/*N*/                                           ppPrevInSlot = NULL;    // not inserted
/*N*/                                       }
/*N*/                                   }
/*N*/       ScChangeActionContent*  GetNextInSlot() { return pNextInSlot; }
/*N*/
/*N*/           void                ClearTrack();
/*N*/
/*N*/   static  void                GetStringOfCell( String& rStr,
/*N*/                                   const ScBaseCell* pCell,
/*N*/                                   const ScDocument* pDoc,
/*N*/                                   const ScAddress& rPos );
/*N*/
/*N*/   static  void                GetStringOfCell( String& rStr,
/*N*/                                   const ScBaseCell* pCell,
/*N*/                                   const ScDocument* pDoc,
/*N*/                                   ULONG nFormat );
/*N*/
/*N*/   static  void                SetValue( String& rStr, ScBaseCell*& pCell,
/*N*/                                   const ScAddress& rPos,
/*N*/                                   const ScBaseCell* pOrgCell,
/*N*/                                   const ScDocument* pFromDoc,
/*N*/                                   ScDocument* pToDoc );
/*N*/
/*N*/   static  void                SetValue( String& rStr, ScBaseCell*& pCell,
/*N*/                                   ULONG nFormat,
/*N*/                                   const ScBaseCell* pOrgCell,
/*N*/                                   const ScDocument* pFromDoc,
/*N*/                                   ScDocument* pToDoc );
/*N*/
/*N*/   static  void                SetCell( String& rStr, ScBaseCell* pCell,
/*N*/                                   ULONG nFormat, const ScDocument* pDoc );
/*N*/
/*N*/   static  BOOL                NeedsNumberFormat( const ScBaseCell* );
/*N*/
/*N*/           void                SetValueString( String& rValue,
/*N*/                                   ScBaseCell*& pCell, const String& rStr,
/*N*/                                   ScDocument* pDoc );
/*N*/
/*N*/           void                GetValueString( String& rStr,
/*N*/                                   const String& rValue,
/*N*/                                   const ScBaseCell* pCell ) const;
/*N*/
/*N*/           void                GetFormulaString( String& rStr,
/*N*/                                   const ScFormulaCell* pCell ) const;
/*N*/
/*N*/   virtual void                AddContent( ScChangeActionContent* ) {}
/*N*/   virtual void                DeleteCellEntries() {}
/*N*/
/*N*/   virtual void                UpdateReference( const ScChangeTrack*,
/*N*/                                   UpdateRefMode, const ScBigRange&,
/*N*/                                   INT32 nDx, INT32 nDy, INT32 nDz );
/*N*/
/*N*/   virtual BOOL                Reject( ScDocument* );
/*N*/
/*N*/                               // pRejectActions!=NULL: reject actions get
/*N*/                               // stacked, no SetNewValue, no Append
/*N*/           BOOL                Select( ScDocument*, ScChangeTrack*,
/*N*/                                   BOOL bOldest, Stack* pRejectActions );
/*N*/
/*N*/           void                PutValueToDoc( ScBaseCell*, const String&,
/*N*/                                   ScDocument*, short nDx, short nDy ) const;
/*N*/
/*N*/   virtual BOOL                Store( SvStream&, ScMultipleWriteHeader& ) const;
/*N*/   virtual BOOL                StoreLinks( SvStream& ) const;
/*N*/   virtual BOOL                LoadLinks( SvStream&, ScChangeTrack* );
/*N*/
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
/*N*/                                   {};
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
/*N*/   virtual                     ~ScChangeActionContent();
/*N*/
/*N*/       ScChangeActionContent*  GetNextContent() const { return pNextContent; }
        ScChangeActionContent*  GetPrevContent() const { return pPrevContent; }
/*N*/       ScChangeActionContent*  GetTopContent() const;
             BOOL               IsTopContent() const
                                     { return pNextContent == NULL; }
/*N*/
/*N*/   virtual ScChangeActionLinkEntry*    GetDeletedIn() const;
/*N*/   virtual ScChangeActionLinkEntry**   GetDeletedInAddress();
/*N*/
/*N*/           void                PutOldValueToDoc( ScDocument*,
/*N*/                                   short nDx, short nDy ) const;
/*N*/           void                PutNewValueToDoc( ScDocument*,
/*N*/                                   short nDx, short nDy ) const;
/*N*/
/*N*/           void                SetOldValue( const ScBaseCell*,
/*N*/                                   const ScDocument* pFromDoc,
/*N*/                                   ScDocument* pToDoc,
/*N*/                                   ULONG nFormat );
/*N*/           void                SetOldValue( const ScBaseCell*,
/*N*/                                   const ScDocument* pFromDoc,
/*N*/                                   ScDocument* pToDoc );
/*N*/           void                SetNewValue( const ScBaseCell*, ScDocument* );
/*N*/
/*N*/                               // Used in import filter AppendContentOnTheFly,
/*N*/                               // takes ownership of cells.
/*N*/           void                SetOldNewCells( ScBaseCell* pOldCell,
/*N*/                                   ULONG nOldFormat, ScBaseCell* pNewCell,
/*N*/                                   ULONG nNewFormat, ScDocument* pDoc );
/*N*/
/*N*/                               // Use this only in the XML import,
/*N*/                               // takes ownership of cell.
            void                SetNewCell( ScBaseCell* pNewCell, ScDocument* pDoc );
/*N*/
/*N*/                               // These functions should be protected but for
/*N*/                               // the XML import they are public.
            void                SetNextContent( ScChangeActionContent* p )
                                    { pNextContent = p; }
            void                SetPrevContent( ScChangeActionContent* p )
                                    { pPrevContent = p; }
/*N*/
/*N*/                               // moeglichst nicht verwenden,
/*N*/                               // setzt nur String bzw. generiert Formelzelle
/*N*/           void                SetOldValue( const String& rOld, ScDocument* );
/*N*/           void                SetNewValue( const String& rNew, ScDocument* );
/*N*/
/*N*/           void                GetOldString( String& ) const;
/*N*/           void                GetNewString( String& ) const;
            const ScBaseCell*   GetOldCell() const { return pOldCell; }
            const ScBaseCell*   GetNewCell() const { return pNewCell; }
/*N*/   virtual void                GetDescription( String&, ScDocument*,
/*N*/                                   BOOL bSplitRange = FALSE ) const;
/*N*/   virtual void                GetRefString( String&, ScDocument*,
/*N*/                                   BOOL bFlag3D = FALSE ) const;
/*N*/
/*N*/   static  ScChangeActionContentCellType   GetContentCellType( const ScBaseCell* );
/*N*/
/*N*/                               // NewCell
/*N*/           BOOL                IsMatrixOrigin() const
/*N*/                                   {
/*N*/                                       return GetContentCellType( GetNewCell() )
/*N*/                                           == SC_CACCT_MATORG;
/*N*/                                   }
/*N*/           BOOL                IsMatrixReference() const
/*N*/                                   {
/*N*/                                       return GetContentCellType( GetNewCell() )
/*N*/                                           == SC_CACCT_MATREF;
/*N*/                                   }
/*N*/                               // OldCell
/*N*/           BOOL                IsOldMatrixOrigin() const
/*N*/                                   {
/*N*/                                       return GetContentCellType( GetOldCell() )
/*N*/                                           == SC_CACCT_MATORG;
/*N*/                                   }
/*N*/           BOOL                IsOldMatrixReference() const
/*N*/                                   {
/*N*/                                       return GetContentCellType( GetOldCell() )
/*N*/                                           == SC_CACCT_MATREF;
/*N*/                                   }
/*N*/
};


// --- ScChangeActionReject -------------------------------------------------

class ScChangeActionReject : public ScChangeAction
{
    friend class ScChangeTrack;
/*N*/   friend class ScChangeActionContent;

                                ScChangeActionReject( ULONG nReject )
                                    : ScChangeAction( SC_CAT_REJECT, ScRange() )
                                    {
/*N*/                                       SetRejectAction( nReject );
/*N*/                                       SetState( SC_CAS_ACCEPTED );
                                    }
                                ScChangeActionReject( SvStream&,
                                    ScMultipleReadHeader&, ScChangeTrack* );

/*N*/   virtual void                AddContent( ScChangeActionContent* ) {}
/*N*/   virtual void                DeleteCellEntries() {}
/*N*/
/*N*/   virtual BOOL                Reject( ScDocument* p ) { return FALSE; }
/*N*/
/*N*/   virtual BOOL                Store( SvStream&, ScMultipleWriteHeader& ) const;
/*N*/
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
/*N*/ DECLARE_QUEUE( ScChangeTrackMsgQueue, ScChangeTrackMsgInfo* )
/*N*/ DECLARE_STACK( ScChangeTrackMsgStack, ScChangeTrackMsgInfo* )

enum ScChangeTrackMergeState
{
    SC_CTMS_NONE,
    SC_CTMS_PREPARE,
    SC_CTMS_OWN,
    SC_CTMS_OTHER
};

// zusaetzlich zu pFirst/pNext/pLast/pPrev eine Table, um schnell sowohl
// per ActionNumber als auch ueber Liste zugreifen zu koennen
/*N*/DECLARE_TABLE( ScChangeActionTable, ScChangeAction* )

// Intern generierte Actions beginnen bei diesem Wert (fast alle Bits gesetzt)
// und werden runtergezaehlt, um sich in einer Table wertemaessig nicht mit den
// "normalen" Actions in die Quere zu kommen.
#define SC_CHGTRACK_GENERATED_START ((UINT32) 0xfffffff0)

// SfxListener an der Applikation, um Aenderungen des Usernamens mitzubekommen

class ScChangeTrack : public SfxListener
{
/*N*/   friend void ScChangeAction::RejectRestoreContents( ScChangeTrack*, short, short );
/*N*/   friend BOOL ScChangeActionDel::Reject( ScDocument* pDoc );
/*N*/   friend void ScChangeActionDel::DeleteCellEntries();
/*N*/   friend void ScChangeActionMove::DeleteCellEntries();
/*N*/   friend BOOL ScChangeActionMove::Reject( ScDocument* pDoc );

    static  const USHORT        nContentRowsPerSlot;
    static  const USHORT        nContentSlots;

     ::com::sun::star::uno::Sequence< sal_Int8 >    aProtectPass;
             ScChangeActionTable    aTable;
             ScChangeActionTable    aGeneratedTable;
             ScChangeActionTable    aPasteCutTable;
/*N*/       ScChangeTrackMsgQueue   aMsgQueue;
/*N*/       ScChangeTrackMsgStack   aMsgStackTmp;
/*N*/       ScChangeTrackMsgStack   aMsgStackFinal;
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
/*N*/                               ScChangeTrack( const ScChangeTrack& );
            ScChangeTrack&      operator=( const ScChangeTrack& );

#ifdef SC_CHGTRACK_CXX
    static  USHORT              InitContentRowsPerSlot();

                                // TRUE if one is MM_FORMULA and the other is
                                // not, or if both are and range differs
/*N*/   static  BOOL                IsMatrixFormulaRangeDifferent(
/*N*/                                   const ScBaseCell* pOldCell,
/*N*/                                   const ScBaseCell* pNewCell );
/*N*/
/*N*/   virtual void                Notify( SfxBroadcaster&, const SfxHint& );
/*N*/           void                Init();
/*N*/           void                DtorClear();
/*N*/           void                SetLoadSave( BOOL bVal ) { bLoadSave = bVal; }
/*N*/           void                SetInDeleteRange( const ScRange& rRange )
/*N*/                                   { aInDeleteRange = rRange; }
/*N*/           void                SetInDelete( BOOL bVal )
/*N*/                                   { bInDelete = bVal; }
/*N*/           void                SetInDeleteTop( BOOL bVal )
/*N*/                                   { bInDeleteTop = bVal; }
/*N*/           void                SetInDeleteUndo( BOOL bVal )
/*N*/                                   { bInDeleteUndo = bVal; }
/*N*/           void                SetInPasteCut( BOOL bVal )
/*N*/                                   { bInPasteCut = bVal; }
/*N*/           void                SetMergeState( ScChangeTrackMergeState eState )
/*N*/                                   { eMergeState = eState; }
/*N*/       ScChangeTrackMergeState GetMergeState() const { return eMergeState; }
/*N*/           void                SetLastMerge( ULONG nVal ) { nLastMerge = nVal; }
/*N*/           ULONG               GetLastMerge() const { return nLastMerge; }
/*N*/
/*N*/           void                SetLastCutMoveRange( const ScRange&, ScDocument* );
/*N*/
/*N*/                               // ModifyMsg blockweise und nicht einzeln erzeugen
/*N*/           void                StartBlockModify( ScChangeTrackMsgType,
/*N*/                                   ULONG nStartAction );
/*N*/           void                EndBlockModify( ULONG nEndAction );
/*N*/
/*N*/           void                AddDependentWithNotify( ScChangeAction* pParent,
/*N*/                                   ScChangeAction* pDependent );
/*N*/
/*N*/           void                Dependencies( ScChangeAction* );
/*N*/           void                UpdateReference( ScChangeAction*, BOOL bUndo );
/*N*/           void                UpdateReference( ScChangeAction** ppFirstAction,
/*N*/                                   ScChangeAction* pAct, BOOL bUndo );
/*N*/           void                Append( ScChangeAction* pAppend, ULONG nAction );
/*N*/           void                AppendDeleteRange( const ScRange&,
/*N*/                                   ScDocument* pRefDoc, short nDz,
/*N*/                                   ULONG nRejectingInsert );
/*N*/           void                AppendOneDeleteRange( const ScRange& rOrgRange,
/*N*/                                   ScDocument* pRefDoc,
/*N*/                                   short nDx, short nDy, short nDz,
/*N*/                                   ULONG nRejectingInsert );
/*N*/           void                LookUpContents( const ScRange& rOrgRange,
/*N*/                                   ScDocument* pRefDoc,
/*N*/                                   short nDx, short nDy, short nDz );
/*N*/           void                Remove( ScChangeAction* );
/*N*/           void                MasterLinks( ScChangeAction* );
/*N*/
/*N*/                               // Content on top an Position
/*N*/       ScChangeActionContent*  SearchContentAt( const ScBigAddress&,
/*N*/                                   ScChangeAction* pButNotThis ) const;
/*N*/                               // das gleiche fuer generierte Del-Eintraege,
/*N*/                               // wobei der Content nicht in der angegebenen
/*N*/                               // Richtung geloescht sein darf
/*N*/       ScChangeActionContent*  SearchGeneratedDelContentAt(
/*N*/                                   const ScBigAddress&,
/*N*/                                   ScChangeActionType eNotInDelType ) const;
/*N*/           void                DeleteGeneratedDelContent(
/*N*/                                   ScChangeActionContent* );
/*N*/       ScChangeActionContent*  GenerateDelContent( const ScAddress&,
/*N*/                                   const ScBaseCell*,
/*N*/                                   const ScDocument* pFromDoc );
/*N*/           void                DeleteCellEntries(
/*N*/                                   ScChangeActionCellListEntry*&,
/*N*/                                   ScChangeAction* pDeletor );
/*N*/
/*N*/                               // Action und alle abhaengigen rejecten,
/*N*/                               // Table stammt aus vorherigem GetDependents,
/*N*/                               // ist nur bei Insert und Move (MasterType)
/*N*/                               // noetig, kann ansonsten NULL sein.
/*N*/                               // bRecursion == Aufruf aus Reject mit Table
/*N*/           BOOL                Reject( ScChangeAction*,
/*N*/                                   ScChangeActionTable*, BOOL bRecursion );
/*N*/
#endif  // SC_CHGTRACK_CXX
/*N*/
/*N*/           void                ClearMsgQueue();
/*N*/
public:

/*N*/   static  USHORT              ComputeContentSlot( INT32 nRow )
/*N*/                                   {
/*N*/                                       if ( nRow < 0 || nRow > MAXROW )
/*N*/                                           return nContentSlots - 1;
/*N*/                                       return nRow / nContentRowsPerSlot;
/*N*/                                   }

/*N*/                               ScChangeTrack( ScDocument* );
                                ScChangeTrack( ScDocument*,
/*N*/                                           const StrCollection& ); // only to use in the XML import
/*N*/   virtual                     ~ScChangeTrack();
/*N*/           void                Clear();
/*N*/
            ScChangeActionContent*  GetFirstGenerated() const { return pFirstGeneratedDelContent; }
            ScChangeAction*     GetFirst() const { return pFirst; }
            ScChangeAction*     GetLast() const { return pLast; }
            ULONG               GetActionMax() const { return nActionMax; }
             BOOL               IsGenerated( ULONG nAction ) const
/*N*/                                   { return nAction >= nGeneratedMin;}
            ScChangeAction*     GetAction( ULONG nAction ) const
                                    { return aTable.Get( nAction ); }
/*N*/           ScChangeAction*     GetGenerated( ULONG nGenerated ) const
/*N*/                                   { return aGeneratedTable.Get( nGenerated ); }
/*N*/           ScChangeAction*     GetActionOrGenerated( ULONG nAction ) const
/*N*/                                   {
/*N*/                                       return IsGenerated( nAction ) ?
/*N*/                                           GetGenerated( nAction ) :
/*N*/                                           GetAction( nAction );
/*N*/                                   }
/*N*/           ULONG               GetLastSavedActionNumber() const
/*N*/                                   { return nMarkLastSaved; }
            void                SetLastSavedActionNumber(ULONG nNew)
                                    { nMarkLastSaved = nNew; }
/*N*/           ScChangeAction*     GetLastSaved() const
/*N*/                                   { return aTable.Get( nMarkLastSaved ); }
/*N*/       ScChangeActionContent** GetContentSlots() const { return ppContentSlots; }
/*N*/
/*N*/           BOOL                IsLoadSave() const { return bLoadSave; }
/*N*/           const ScRange&      GetInDeleteRange() const
/*N*/                                   { return aInDeleteRange; }
/*N*/           BOOL                IsInDelete() const { return bInDelete; }
/*N*/           BOOL                IsInDeleteTop() const { return bInDeleteTop; }
            BOOL                IsInDeleteUndo() const { return bInDeleteUndo; }
/*N*/           BOOL                IsInPasteCut() const { return bInPasteCut; }
/*N*/           void                SetUser( const String& );
/*N*/           const String&       GetUser() const { return aUser; }
            const StrCollection&    GetUserCollection() const
                                    { return aUserCollection; }
/*N*/           ScDocument*         GetDocument() const { return pDoc; }
/*N*/                               // for import filter
/*N*/           const DateTime&     GetFixDateTime() const { return aFixDateTime; }
/*N*/
/*N*/                               // set this if the date/time set with
/*N*/                               // SetFixDateTime...() shall be applied to
/*N*/                               // appended actions
/*N*/           void                SetUseFixDateTime( BOOL bVal )
/*N*/                                   { bUseFixDateTime = bVal; }
/*N*/                               // for MergeDocument, apply original date/time as UTC
/*N*/           void                SetFixDateTimeUTC( const DateTime& rDT )
/*N*/                                   { aFixDateTime = rDT; }
/*N*/                               // for import filter, apply original date/time as local time
/*N*/           void                SetFixDateTimeLocal( const DateTime& rDT )
/*N*/                                   { aFixDateTime = rDT; aFixDateTime.ConvertToUTC(); }
/*N*/
/*N*/           void                Append( ScChangeAction* );
/*N*/
/*N*/                               // pRefDoc may be NULL => no lookup of contents
/*N*/                               // => no generation of deleted contents
/*N*/           void                AppendDeleteRange( const ScRange&,
/*N*/                                   ScDocument* pRefDoc,
/*N*/                                   ULONG& nStartAction, ULONG& nEndAction,
/*N*/                                   short nDz = 0 );
/*N*/                                   // nDz: Multi-TabDel, LookUpContent ist
/*N*/                                   // um -nDz verschoben zu suchen
/*N*/
/*N*/                               // nachdem neuer Wert im Dokument gesetzt wurde,
/*N*/                               // alter Wert aus RefDoc/UndoDoc
/*N*/           void                AppendContent( const ScAddress& rPos,
/*N*/                                   ScDocument* pRefDoc );
/*N*/                               // nachdem neue Werte im Dokument gesetzt wurden,
/*N*/                               // alte Werte aus RefDoc/UndoDoc
/*N*/           void                AppendContentRange( const ScRange& rRange,
/*N*/                                   ScDocument* pRefDoc,
/*N*/                                   ULONG& nStartAction, ULONG& nEndAction,
/*N*/                                   ScChangeActionClipMode eMode = SC_CACM_NONE );
/*N*/                               // nachdem neuer Wert im Dokument gesetzt wurde,
/*N*/                               // alter Wert aus pOldCell, nOldFormat,
/*N*/                               // RefDoc==NULL => Doc
/*N*/           void                AppendContent( const ScAddress& rPos,
/*N*/                                   const ScBaseCell* pOldCell,
/*N*/                                   ULONG nOldFormat, ScDocument* pRefDoc = NULL );
/*N*/                               // nachdem neuer Wert im Dokument gesetzt wurde,
/*N*/                               // alter Wert aus pOldCell, Format aus Doc
/*N*/           void                AppendContent( const ScAddress& rPos,
/*N*/                                   const ScBaseCell* pOldCell );
/*N*/                               // nachdem neuer Wert im Dokument gesetzt wurde,
/*N*/                               // alter Wert aus pOldCell, Format aus RefDoc
/*N*/           void                AppendContent( const ScAddress& rPos,
/*N*/                                   const ScBaseCell* pOldCell,
/*N*/                                   ScDocument* pRefDoc );
/*N*/                               // nachdem neue Werte im Dokument gesetzt wurden,
/*N*/                               // alte Werte aus RefDoc/UndoDoc.
/*N*/                               // Alle Contents, wo im RefDoc eine Zelle steht.
/*N*/           void                AppendContentsIfInRefDoc( ScDocument* pRefDoc,
/*N*/                                   ULONG& nStartAction, ULONG& nEndAction );
/*N*/
/*N*/                               // Meant for import filter, creates and inserts
/*N*/                               // an unconditional content action of the two
/*N*/                               // cells without querying the document, not
/*N*/                               // even for number formats (though the number
/*N*/                               // formatter of the document may be used).
/*N*/                               // The action is returned and may be used to
/*N*/                               // set user name, description, date/time et al.
/*N*/                               // Takes ownership of the cells!
/*N*/       ScChangeActionContent*  AppendContentOnTheFly( const ScAddress& rPos,
/*N*/                                   ScBaseCell* pOldCell,
/*N*/                                   ScBaseCell* pNewCell,
/*N*/                                   ULONG nOldFormat = 0,
/*N*/                                   ULONG nNewFormat = 0 );
/*N*/
/*N*/                               // die folgenden beiden nur benutzen wenn's
/*N*/                               // nicht anders geht (setzen nur String fuer
/*N*/                               // NewValue bzw. Formelerzeugung)
/*N*/
/*N*/                               // bevor neuer Wert im Dokument gesetzt wird
/*N*/           void                AppendContent( const ScAddress& rPos,
/*N*/                                   const String& rNewValue );
/*N*/                               // bevor neuer Wert im Dokument gesetzt wird
/*N*/           void                AppendContent( const ScAddress& rPos,
/*N*/                                   const String& rNewValue,
/*N*/                                   ScBaseCell* pOldCell );
/*N*/
/*N*/           void                AppendInsert( const ScRange& );
/*N*/
/*N*/                               // pRefDoc may be NULL => no lookup of contents
/*N*/                               // => no generation of deleted contents
/*N*/           void                AppendMove( const ScRange& rFromRange,
/*N*/                                   const ScRange& rToRange,
/*N*/                                   ScDocument* pRefDoc );
/*N*/
/*N*/                               // Cut to Clipboard
/*N*/           void                ResetLastCut()
/*N*/                                   {
/*N*/                                       nStartLastCut = nEndLastCut = 0;
/*N*/                                       if ( pLastCutMove )
/*N*/                                       {
/*N*/                                           delete pLastCutMove;
/*N*/                                           pLastCutMove = NULL;
/*N*/                                       }
/*N*/                                   }
/*N*/           BOOL                HasLastCut() const
/*N*/                                   {
/*N*/                                       return nEndLastCut > 0 &&
/*N*/                                           nStartLastCut <= nEndLastCut &&
/*N*/                                           pLastCutMove;
/*N*/                                   }
/*N*/
/*N*/           void                Undo( ULONG nStartAction, ULONG nEndAction );
/*N*/
/*N*/                               // fuer MergeDocument, Referenzen anpassen,
/*N*/                               //! darf nur in einem temporaer geoeffneten
/*N*/                               //! Dokument verwendet werden, der Track
/*N*/                               //! ist danach verhunzt
/*N*/           void                MergePrepare( ScChangeAction* pFirstMerge );
/*N*/           void                MergeOwn( ScChangeAction* pAct, ULONG nFirstMerge );
/*N*/   static  BOOL                MergeIgnore( const ScChangeAction&, ULONG nFirstMerge );
/*N*/
/*N*/                               // Abhaengige in Table einfuegen.
/*N*/                               // Bei Insert sind es echte Abhaengige,
/*N*/                               // bei Move abhaengige Contents im FromRange
/*N*/                               // und geloeschte im ToRange bzw. Inserts in
/*N*/                               // FromRange oder ToRange,
/*N*/                               // bei Delete eine Liste der geloeschten,
/*N*/                               // bei Content andere Contents an gleicher
/*N*/                               // Position oder MatrixReferences zu MatrixOrigin.
/*N*/                               // Mit bListMasterDelete werden unter einem
/*N*/                               // MasterDelete alle zu diesem Delete gehoerenden
/*N*/                               // Deletes einer Reihe gelistet.
/*N*/                               // Mit bAllFlat werden auch alle Abhaengigen
/*N*/                               // der Abhaengigen flach eingefuegt.
/*N*/           void                GetDependents( ScChangeAction*,
/*N*/                                   ScChangeActionTable&,
/*N*/                                   BOOL bListMasterDelete = FALSE,
/*N*/                                   BOOL bAllFlat = FALSE );
/*N*/
/*N*/                               // Reject visible Action (und abhaengige)
/*N*/           BOOL                Reject( ScChangeAction* );
/*N*/
/*N*/                               // Accept visible Action (und abhaengige)
/*N*/           BOOL                Accept( ScChangeAction* );
/*N*/
/*N*/           void                AcceptAll();    // alle Virgins
/*N*/           BOOL                RejectAll();    // alle Virgins
/*N*/
/*N*/                               // Selektiert einen Content von mehreren an
/*N*/                               // gleicher Position und akzeptiert diesen und
/*N*/                               // die aelteren, rejected die neueren.
/*N*/                               // Mit bOldest==TRUE wird der erste OldValue
/*N*/                               // einer Virgin-Content-Kette restauriert.
/*N*/           BOOL                SelectContent( ScChangeAction*,
/*N*/                                   BOOL bOldest = FALSE );
/*N*/
/*N*/                               // wenn ModifiedLink gesetzt, landen
/*N*/                               // Aenderungen in ScChangeTrackMsgQueue
/*N*/           void                SetModifiedLink( const Link& r )
/*N*/                                   { aModifiedLink = r; ClearMsgQueue(); }
/*N*/           const Link&         GetModifiedLink() const { return aModifiedLink; }
/*N*/           ScChangeTrackMsgQueue& GetMsgQueue() { return aMsgQueue; }
/*N*/
/*N*/           void                NotifyModified( ScChangeTrackMsgType eMsgType,
/*N*/                                   ULONG nStartAction, ULONG nEndAction );
/*N*/
/*N*/           BOOL                Load( SvStream& rStrm, USHORT nVer );
/*N*/           BOOL                Store( SvStream& rStrm );
/*N*/           USHORT              GetLoadedFileFormatVersion() const
/*N*/                                   { return nLoadedFileFormatVersion; }
/*N*/
            ULONG               AddLoadedGenerated(ScBaseCell* pOldCell,
                                                const ScBigRange& aBigRange ); // only to use in the XML import
             void               AppendLoaded( ScChangeAction* pAppend ); // this is only for the XML import public, it should be protected
             void               SetActionMax(ULONG nTempActionMax)
                                    { nActionMax = nTempActionMax; } // only to use in the XML import
/*N*/
            void                SetProtection( const ::com::sun::star::uno::Sequence< sal_Int8 >& rPass )
                                    { aProtectPass = rPass; }
     ::com::sun::star::uno::Sequence< sal_Int8 >   GetProtection() const
                                     { return aProtectPass; }
             BOOL                IsProtected() const
                                     { return aProtectPass.getLength() != 0; }
/*N*/
/*N*/                                 // If time stamps of actions of this
/*N*/                                 // ChangeTrack and a second one are to be
/*N*/                                 // compared including 100th seconds.
            void                SetTime100thSeconds( BOOL bVal )
                                    { bTime100thSeconds = bVal; }
/*N*/             BOOL                IsTime100thSeconds() const
/*N*/                                     { return bTime100thSeconds; }
};


} //namespace binfilter
#endif


