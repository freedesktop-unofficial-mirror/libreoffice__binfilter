/*************************************************************************
 *
 *  $RCSfile: swdtflvr.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:55:41 $
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
#ifndef _SWDTFLVR_HXX
#define _SWDTFLVR_HXX

#ifndef _TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif
#ifndef _EMBOBJ_HXX
#include <so3/embobj.hxx>
#endif
#ifndef _SV_GRAPH_HXX
#include <vcl/graph.hxx>
#endif
#ifndef _LNKBASE_HXX
#include <so3/lnkbase.hxx>
#endif
class Graphic;
class ImageMap;
namespace binfilter {



class INetBookmark;
class INetImage;
class SwDoc;
class SwDocFac;
class SwNode;
class SwTextBlocks;
class SwWrtShell;
class Reader;
class SvxClipboardFmtItem;
class ViewShell;
class SwView_Impl;

enum TransferBufferType
{
    TRNSFR_NONE             = 0x0000,
    TRNSFR_DOCUMENT         = 0x0001,
    TRNSFR_DOCUMENT_WORD    = 0x0002,
    TRNSFR_GRAPHIC          = 0x0004,
    TRNSFR_TABELLE          = 0x0008,
    TRNSFR_DDELINK          = 0x0010,
    TRNSFR_OLE              = 0x0020,
    TRNSFR_INETFLD          = 0x0040,
    TRNSFR_DRAWING          = 0x0081    //Drawing ist auch intern!
};

#define DATA_FLAVOR     ::com::sun::star::datatransfer::DataFlavor

class SwTransferable : public TransferableHelper
{
    friend class SwView_Impl;
    SvEmbeddedObjectRef             aDocShellRef;
    TransferableDataHelper          aOleData;
    TransferableObjectDescriptor    aObjDesc;
    ::so3::SvBaseLinkRef            refDdeLink;

    SwWrtShell      *pWrtShell;
    /* #96392# Added pCreatorView to distinguish SwFrameShell from
       SwWrtShell. */
    const ViewShell       *pCreatorView;
    SwDocFac        *pClpDocFac;
    Graphic         *pClpGraphic, *pClpBitmap, *pOrigGrf;
    INetBookmark    *pBkmk;     // URL und Beschreibung!
    ImageMap        *pImageMap;
    INetImage       *pTargetURL;

    TransferBufferType eBufferType;

    BOOL bOldIdle   :1; //D&D Idle flag from the viewsettings
    BOOL bCleanUp   :1; //D&D cleanup after Drop (not by internal Drop)

    // helper methods for the copy
//STRIP001  SvEmbeddedObject* FindOLEObj() const;
//STRIP001  void DeleteSelection();

    // helper methods for the paste
//STRIP001  static void SetSelInShell( SwWrtShell& , BOOL , const Point* );
//STRIP001  static BOOL _CheckForURLOrLNKFile( TransferableDataHelper& rData,
//STRIP001                              String& rFileName, String* pTitle = 0 );
    static int _TestAllowedFormat( const TransferableDataHelper& rData,
                                        ULONG nFormat, USHORT nDestination );

//STRIP001  static int _PasteFileContent( TransferableDataHelper&,
//STRIP001                                  SwWrtShell& rSh, ULONG nFmt, BOOL bMsg );
//STRIP001  static int _PasteOLE( TransferableDataHelper& rData, SwWrtShell& rSh,
//STRIP001                          ULONG nFmt, BYTE nActionFlags, BOOL bMsg );
//STRIP001  static int _PasteTargetURL( TransferableDataHelper& rData, SwWrtShell& rSh,
//STRIP001                      USHORT nAction, const Point* pPt, BOOL bInsertGRF );

//STRIP001  static int _PasteDDE( TransferableDataHelper& rData, SwWrtShell& rWrtShell,
//STRIP001                          FASTBOOL bReReadGrf, BOOL bMsg );

//STRIP001  static int _PasteSdrFormat(  TransferableDataHelper& rData,
//STRIP001                                  SwWrtShell& rSh, USHORT nAction,
//STRIP001                                  const Point* pPt, BYTE nActionFlags );

//STRIP001  static int _PasteGrf( TransferableDataHelper& rData, SwWrtShell& rSh,
//STRIP001                              ULONG nFmt, USHORT nAction, const Point* pPt,
//STRIP001                              BYTE nActionFlags, BOOL bMsg );

//STRIP001  static int _PasteImageMap( TransferableDataHelper& rData,
//STRIP001                                  SwWrtShell& rSh );

//STRIP001  static int _PasteAsHyperlink( TransferableDataHelper& rData,
//STRIP001                                      SwWrtShell& rSh, ULONG nFmt );

//STRIP001  static int _PasteFileName( TransferableDataHelper& rData,
//STRIP001                          SwWrtShell& rSh, ULONG nFmt, USHORT nAction,
//STRIP001                          const Point* pPt, BYTE nActionFlags, BOOL bMsg );

//STRIP001  static int _PasteDBData( TransferableDataHelper& rData, SwWrtShell& rSh,
//STRIP001                          ULONG nFmt, BOOL bLink, const Point* pDragPt,
//STRIP001                          BOOL bMsg );

//STRIP001  static int _PasteFileList( TransferableDataHelper& rData,
//STRIP001                              SwWrtShell& rSh, BOOL bLink,
//STRIP001                              const Point* pPt, BOOL bMsg );

//STRIP001  int PrivateDrop( SwWrtShell& rSh, const Point& rDragPt, BOOL bMove,
//STRIP001                      BOOL bIsXSelection );
//STRIP001  int PrivatePaste( SwWrtShell& rShell );

//STRIP001  void SetDataForDragAndDrop( const Point& rSttPos );

                                    // not available
//STRIP001                                  SwTransferable();
//STRIP001                                  SwTransferable( const SwTransferable& );
//STRIP001  SwTransferable&                 operator=( const SwTransferable& );

protected:
//STRIP001  virtual void        AddSupportedFormats();
//STRIP001  virtual sal_Bool    GetData( const DATA_FLAVOR& rFlavor );
//STRIP001  virtual sal_Bool    WriteObject( SotStorageStreamRef& rxOStm,
//STRIP001                                      void* pUserObject,
//STRIP001                                      sal_uInt32 nUserObjectId,
//STRIP001                                      const DATA_FLAVOR& rFlavor );
//STRIP001  virtual void        DragFinished( sal_Int8 nDropAction );
//STRIP001  virtual void        ObjectReleased();

public:
//STRIP001  SwTransferable( SwWrtShell& );
//STRIP001  virtual ~SwTransferable();

    static USHORT GetSotDestination( const SwWrtShell& rSh, const Point* = 0 );

    // set properties on the document, like PageMargin, VisArea.
    // And set real Size
    static void InitOle( SvEmbeddedObjectRef rRef, SwDoc& rDoc );

    // copy - methods and helper methods for the copy
//STRIP001  int  Cut();
//STRIP001  int  Copy( BOOL bIsCut = FALSE );
//STRIP001  int  CalculateAndCopy();                // special for Calculator
//STRIP001  int  CopyGlossary( SwTextBlocks& rGlossary, const String& rStr );

    // remove the DDE-Link format promise
//STRIP001  void RemoveDDELinkFormat( const Window& rWin );

    // paste - methods and helper methods for the paste
    static BOOL IsPaste( const SwWrtShell&, const TransferableDataHelper& );
//STRIP001  static int Paste( SwWrtShell&, TransferableDataHelper& );
//STRIP001  static int PasteData( TransferableDataHelper& rData,
//STRIP001                        SwWrtShell& rSh, USHORT nAction, ULONG nFormat,
//STRIP001                        USHORT nDestination, BOOL bIsPasteFmt,
//STRIP001                           sal_Bool bIsDefault,
//STRIP001                           const Point* pDDPos = 0, sal_Int8 nDropAction = 0,
//STRIP001                        BOOL bPasteSelection = FALSE );

    static BOOL IsPasteSpecial( const SwWrtShell& rWrtShell,
                                const TransferableDataHelper& );
//STRIP001     static int PasteSpecial( SwWrtShell& rSh, TransferableDataHelper&, ULONG& rFormatUsed );
//STRIP001  static int PasteFormat( SwWrtShell& rSh, TransferableDataHelper& rData,
//STRIP001                           ULONG nFormat );

    static void FillClipFmtItem( const SwWrtShell& rSh,
                                const TransferableDataHelper& rData,
                                SvxClipboardFmtItem & rToFill );

    // Interfaces for Drag & Drop
//STRIP001  void StartDrag( Window* pWin, const Point& rPos );
//STRIP001  SwWrtShell* GetShell()              { return pWrtShell; }
//STRIP001  void SetCleanUp( BOOL bFlag )       { bCleanUp = bFlag; }

    // Interfaces for Selection
    /* #96392# Added pCreator to distinguish SwFrameShell from SwWrtShell. */
//STRIP001  static void CreateSelection( SwWrtShell & rSh,
//STRIP001                               const ViewShell * pCreator = NULL );
    static void ClearSelection( SwWrtShell& rSh,
                                const ViewShell * pCreator = NULL );

    // the related SwView is being closed and the SwTransferable is invalid now
    void    Invalidate() {pWrtShell = 0;}
    static const ::com::sun::star::uno::Sequence< sal_Int8 >& getUnoTunnelId();

    virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& rId ) throw( ::com::sun::star::uno::RuntimeException );
};


} //namespace binfilter
#endif
