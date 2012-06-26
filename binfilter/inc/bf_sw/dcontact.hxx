/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */
#ifndef _DCONTACT_HXX
#define _DCONTACT_HXX

#include <bf_svx/svdobj.hxx>
// OD 14.05.2003 #108784#
#include <bf_svx/svdovirt.hxx>

// OD 17.06.2003 #108784#
#include <list>

#include "calbck.hxx"
namespace binfilter {

class SfxPoolItem;

class SwFrmFmt;
class SwFlyFrmFmt;
class SwDrawFrmFmt;
class SwFlyFrm;
class SwFrm;
class SwPageFrm;
class SwVirtFlyDrawObj;
class SwFmtAnchor;
class SwFlyDrawObj;
class SwRect;
// OD 17.06.2003 #108784# - forward declaration for class <SwDrawVirtObj>
class SwDrawContact;

//Der Umgekehrte Weg: Sucht das Format zum angegebenen Objekt.
//Wenn das Object ein SwVirtFlyDrawObj ist so wird das Format von
//selbigem besorgt.
//Anderfalls ist es eben ein einfaches Zeichenobjekt. Diese hat einen
//UserCall und der ist Client vom gesuchten Format.
//Implementierung in dcontact.cxx
SwFrmFmt *FindFrmFmt( SdrObject *pObj );
inline const SwFrmFmt *FindFrmFmt( const SdrObject *pObj )
{   return ::binfilter::FindFrmFmt( (SdrObject*)pObj ); }
sal_Bool HasWrap( const SdrObject* pObj );

//Bei Aenderungen das Objekt aus dem ContourCache entfernen.
//Implementierung in TxtFly.Cxx
void ClrContourCache( const SdrObject *pObj );

// liefert BoundRect inklusive Abstand
SwRect GetBoundRect( const SdrObject* pObj );

// Moves a SdrObj so that it fits to a given frame
void CaptureDrawObj( SdrObject& rObj, const SwRect& rFrm );

//Liefert den UserCall ggf. vom Gruppenobjekt
SdrObjUserCall* GetUserCall( const SdrObject* );

// liefert TRUE falls das SrdObject ein Marquee-Object (Lauftext) ist
bool IsMarqueeTextObj( const SdrObject& rObj );

//Basisklasse fuer die folgenden KontaktObjekte (Rahmen+Zeichenobjekte)
class SwContact : public SdrObjUserCall, public SwClient
{
    SdrObject *pMasterObj;
public:
    TYPEINFO();

    //Fuer den Reader, es wir nur die Verbindung hergestellt.
    SwContact( SwFrmFmt *pToRegisterIn, SdrObject *pObj );
    SwContact( SwModify *pToRegisterIn ) : SwClient( pToRegisterIn ){}

    // OD 13.05.2003 #108784# - made methods virtual and not inline
    virtual const SdrObject *GetMaster() const;
    virtual SdrObject *GetMaster();
    virtual void SetMaster( SdrObject* pNew );

    virtual ~SwContact();

          SwFrmFmt  *GetFmt(){ return (SwFrmFmt*)GetRegisteredIn(); }
    const SwFrmFmt  *GetFmt() const
        { return (const SwFrmFmt*)GetRegisteredIn(); }

};

//KontactObjekt fuer die Verbindung zwischen Rahmen bzw. deren Formaten
//im StarWriter (SwClient) und den Zeichenobjekten des Drawing (SdrObjUserCall)

class SwFlyDrawContact : public SwContact
{
public:
    TYPEINFO();

    //Legt das DrawObjekt an und meldet es beim Model an.
    SwFlyDrawContact( SwFlyFrmFmt *pToRegisterIn, SdrModel *pMod );
    SwFlyDrawContact( SwFrmFmt *pToRegisterIn, SdrObject *pObj ):
        SwContact( pToRegisterIn, pObj ){}

    SwVirtFlyDrawObj *CreateNewRef( SwFlyFrm *pFly );

    // virtuelle Methoden von SwClient
    virtual void Modify( SfxPoolItem *, SfxPoolItem * ) {} //DBG_BF_ASSERT

};

// OD 16.05.2003 #108784# - new class for re-direct methods calls at a 'virtual'
//      drawing object to its referenced object.
class SwDrawVirtObj : public SdrVirtObj
{
    private:
        // data for connection to writer layout
        SwFrm*      mpAnchorFrm;
        SwPageFrm*  mpPageFrm;

        // #108784#
        // implement a real offset for this object since the anchor pos will be
        // needed, too.
        Point       maOffset;

        // writer-drawing contact object the 'virtual' drawing object is controlled by.
        // This object is also the <UserCall> of the drawing object, if it's
        // inserted into the drawing layer.
        SwDrawContact&  mrDrawContact;

    public:
        TYPEINFO();

        SwDrawVirtObj( SdrObject&       _rNewObj,
                       SwDrawContact&   _rDrawContact );
        virtual ~SwDrawVirtObj();

        // access to offset
        void SetOffset( const Point& rNewOffset );
        // OD 30.06.2003 #108784# - virtual!!!
        virtual const Point GetOffset() const;

        using SdrObject::Clone;
        virtual SdrObject* Clone() const;
        virtual void operator=( const SdrObject& ) {} //DBG_BF_ASSERT

        // connection to writer layout
        void SetAnchorFrm( SwFrm* _pNewAnchorFrm );
        SwFrm* GetAnchorFrm() const;
        void SetPageFrm( SwPageFrm* _pNewPageFrm );
        SwPageFrm* GetPageFrm() const;
        void RemoveFromWriterLayout();

        // connection to drawing layer
        void AddToDrawingPage();
        void RemoveFromDrawingPage();

        // is 'virtual' drawing object connected to writer layout and
        // to drawing layer.
        bool IsConnected() const;

        // OD 19.06.2003 #108784# - adjust the relative postion of the 'virtual'
        // drawing object to the reference object
        void AdjustRelativePosToReference();

        // #108784#
        // All overloaded methods which need to use the offset to move
        // the object position virtually.
        virtual void NbcSetRelativePos(const Point& rPnt);
        virtual void NbcSetAnchorPos(const Point& rPnt);

        // #108784#
        // All overloaded methods which need to use the offset
        virtual const Rectangle& GetBoundRect() const;
        virtual void RecalcBoundRect();
        virtual bool Paint(ExtOutputDevice& rOut, const SdrPaintInfoRec& rInfoRec) const;
        virtual SdrObject* CheckHit(const Point& rPnt, USHORT nTol, const SetOfByte* pVisiLayer) const;
        virtual void TakeXorPoly(XPolyPolygon& rPoly, bool bDetail) const;
        virtual void TakeContour(XPolyPolygon& rPoly) const;
        using SdrObject::TakeContour;
        virtual SdrHdl* GetHdl(USHORT) const { return NULL; } //DBG_BF_ASSERT
        virtual SdrHdl* GetPlusHdl(const SdrHdl&, USHORT) const { return NULL; } //DBG_BF_ASSERT
        virtual void NbcMove(const Size& rSiz);
        virtual void NbcResize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
        virtual void NbcRotate(const Point& rRef, long nWink, double sn, double cs);
        virtual void NbcMirror(const Point& rRef1, const Point& rRef2);
        virtual void NbcShear(const Point& rRef, double tn, bool bVShear);
        virtual void Move(const Size& rSiz);
        virtual void Resize(const Point& rRef, const Fraction& xFact, const Fraction& yFact);
        virtual void Rotate(const Point& rRef, long nWink, double sn, double cs);
        virtual void Mirror(const Point&, const Point&) {} //DBG_BF_ASSERT
        virtual void Shear(const Point& rRef, long nWink, double tn, bool bVShear);
        virtual void RecalcSnapRect();
        virtual const Rectangle& GetSnapRect() const;
        virtual void SetSnapRect(const Rectangle& rRect);
        virtual void NbcSetSnapRect(const Rectangle& rRect);
        virtual const Rectangle& GetLogicRect() const;
        virtual void SetLogicRect(const Rectangle& rRect);
        virtual void NbcSetLogicRect(const Rectangle& rRect);
        virtual Point GetSnapPoint(USHORT) const { Point ap; return ap; } //DBG_BF_ASSERT
        virtual const Point& GetPoint(USHORT i) const;
        virtual void NbcSetPoint(const Point& rPnt, USHORT i);

        // #108784#
        virtual bool HasTextEdit() const;

        // OD 17.06.2003 #108784# - overload 'layer' methods
        virtual SdrLayerID GetLayer() const;
        using SdrObject::GetLayer;
        virtual void NbcSetLayer(SdrLayerID nLayer);
        virtual void SetLayer(SdrLayerID nLayer);
};

// OD 26.06.2003 #108784#
bool CheckControlLayer( const SdrObject *pObj );

//KontactObjekt fuer die Verbindung von Formaten als Repraesentanten der
//Zeichenobjekte im StarWriter (SwClient) und den Objekten selbst im Drawing
//(SdrObjUserCall).

class SwDrawContact : public SwContact
{
    private:
        SwFrm     *pAnchor;
        SwPageFrm *pPage;

        // OD 16.05.2003 #108784# - data structure for collecting 'virtual'
        // drawing object supporting drawing objects in headers/footers.
        std::list<SwDrawVirtObj*> maDrawVirtObjs;

        // unary function used by <list> iterator to find a disconnected 'virtual'
        // drawing object
        struct UsedOrUnusedVirtObjPred
        {
            bool mbUsedPred;
            UsedOrUnusedVirtObjPred( bool _bUsed ) : mbUsedPred( _bUsed ) {};
            bool operator() ( const SwDrawVirtObj* _pDrawVirtObj )
            {
                if ( mbUsedPred )
                {
                    return _pDrawVirtObj->IsConnected();
                }
                else
                {
                    return !_pDrawVirtObj->IsConnected();
                }
            }
        };

        // unary function used by <list> iterator to find a 'virtual' drawing
        // object anchored at a given frame
        struct VirtObjAnchoredAtFrmPred
        {
            const SwFrm& mrAnchorFrm;
            VirtObjAnchoredAtFrmPred( const SwFrm& _rAnchorFrm ) : mrAnchorFrm( _rAnchorFrm ) {};
            bool operator() ( const SwDrawVirtObj* _pDrawVirtObj )
            {
                return ( _pDrawVirtObj->GetAnchorFrm() == &mrAnchorFrm );
            }
        };

        // OD 16.05.2003 #108784# - method for adding/removing 'virtual' drawing object.
        SwDrawVirtObj* CreateVirtObj();
        void DestroyVirtObj( SwDrawVirtObj* pVirtObj );
        void RemoveAllVirtObjs();

    public:
        TYPEINFO();

        SwDrawContact( SwFrmFmt *pToRegisterIn, SdrObject *pObj );
        virtual ~SwDrawContact();

        const SwPageFrm *GetPage() const            { return pPage; }
              SwPageFrm *GetPage()                  { return pPage; }
        const SwFrm     *GetAnchor() const          { return pAnchor; }
              SwFrm     *GetAnchor()                { return pAnchor; }
              void       ChgAnchor( SwFrm *pNew )   { pAnchor = pNew; }
              void       ChgPage  ( SwPageFrm *pNew){ pPage   = pNew; }

              void       ChkPage();     //Muss immer nach SetAnchorPos() gerufen
                                        //werden. Das Objekt haengt sich dann an
                                        //die richtige Seite.
              SwPageFrm* FindPage( const SwRect &rRect );

        //Fuegt das SdrObject in die Arrays (SwPageFrm und SwFrm) des Layouts ein.
        //Der Anker wird Anhand des Attributes SwFmtAnchor bestimmt.
        //Das Objekt wird ggf. beim alten Anker abgemeldet.
        void ConnectToLayout( const SwFmtAnchor *pAnch = 0 );

        void DisconnectFromLayout( bool _bMoveMasterToInvisibleLayer = true );
        // OD 19.06.2003 #108784# - disconnect for a dedicated drawing object -
        // could be 'master' or 'virtual'.
        void DisconnectObjFromLayout( SdrObject* _pDrawObj );
        // OD 26.06.2003 #108784# - method to remove 'master' drawing object
        // from drawing page.
        // To be used by the undo for delete of object. Call it after method
        // <DisconnectFromLayout( bool = true )> is already performed.
        // Note: <DisconnectFromLayout( bool )> no longer removes the 'master'
        // drawing object from drawing page.
        void RemoveMasterFromDrawPage();

        // OD 16.05.2003 #108784# - overload in order to perform work for 'virtual'
        //      drawing object
        virtual void SetMaster( SdrObject* pNew );
        // OD 19.06.2003 #108784# - get drawing object ('master' or 'virtual')
        // by frame.
        SdrObject* GetDrawObjectByAnchorFrm( const SwFrm& _rAnchorFrm );

        // virtuelle Methoden von SwClient
        virtual void Modify( SfxPoolItem *pOld, SfxPoolItem *pNew );

        // virtuelle Methoden von SdrObjUserCall
        virtual void Changed(const SdrObject& rObj, SdrUserCallType eType, const Rectangle& rOldBoundRect);

        // wird von Changed() und auch vom UndoDraw benutzt, uebernimmt
        // das Notifien von Absaetzen, die ausweichen muessen
        void _Changed(const SdrObject& rObj, SdrUserCallType eType, const Rectangle* pOldBoundRect);

        //Moved alle SW-Verbindungen zu dem neuen Master.

        // OD 19.06.2003 #108784#
        SwDrawVirtObj* AddVirtObj();

        // OD 20.06.2003 #108784#
        void CorrectRelativePosOfVirtObjs();
        void MoveOffsetOfVirtObjs( const Size& _rMoveSize );
        void InvalidateAnchorOfVirtObjs();
        void NotifyBackgrdOfAllVirtObjs( const Rectangle* pOldBoundRect );
};


} //namespace binfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
