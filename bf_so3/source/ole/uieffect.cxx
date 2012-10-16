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


#include "soole.h"

namespace binfilter {

    void DrawHandle(HDC hDC, int x, int y, UINT cSize, BOOL fInvert
    , BOOL fDraw);

//Hatch pattern brush bits
static WORD g_wHatchBmp[]={0x11, 0x22, 0x44, 0x88, 0x11, 0x22, 0x44, 0x88};


/*
 * UIDrawHandles
 *
 * Purpose:
 *  Draw handles or/and boundary around Container Object when selected
 *
 * Parameters:
 *  pRect           Dimensions of Container Object
 *  hDC             HDC of the site
 *  dwFlags         DWORD specifying how to draw the handles.
 *  cSize           UINT size of handle box
 *  fDraw           BOOL draw if TRUE, erase if FALSE
 *
 * Return Value:
 *  None
 */

STDAPI_(void) UIDrawHandles(LPRECT pRect, HDC hDC, DWORD dwFlags, UINT cSize
    , BOOL fDraw)
    {
    HBRUSH  hBR;
    RECT    rc;
    int     bkmodeOld;
    BOOL    fInvert=(BOOL)(dwFlags & UI_HANDLES_USEINVERSE);

    CopyRect((LPRECT)&rc, pRect);

    bkmodeOld=SetBkMode(hDC, TRANSPARENT);

    if (dwFlags & UI_HANDLES_OUTSIDE)
        InflateRect((LPRECT)&rc, cSize - 1, cSize - 1);

    //Draw the handles inside the rectangle boundary
    DrawHandle(hDC, rc.left, rc.top, cSize, fInvert, fDraw);
    DrawHandle(hDC, rc.left, rc.top+(rc.bottom-rc.top-cSize)/2, cSize, fInvert, fDraw);
    DrawHandle(hDC, rc.left, rc.bottom-cSize, cSize, fInvert, fDraw);
    DrawHandle(hDC, rc.left+(rc.right-rc.left-cSize)/2, rc.top, cSize, fInvert, fDraw);
    DrawHandle(hDC, rc.left+(rc.right-rc.left-cSize)/2, rc.bottom-cSize, cSize, fInvert, fDraw);
    DrawHandle(hDC, rc.right-cSize, rc.top, cSize, fInvert, fDraw);
    DrawHandle(hDC, rc.right-cSize, rc.top+(rc.bottom-rc.top-cSize)/2, cSize, fInvert, fDraw);
    DrawHandle(hDC, rc.right-cSize, rc.bottom-cSize, cSize, fInvert, fDraw);

    if (!(dwFlags & UI_HANDLES_NOBORDER))
        {
        if (fDraw)
            hBR=(HBRUSH)GetStockObject(BLACK_BRUSH);
        else
            hBR=(HBRUSH)GetStockObject(WHITE_BRUSH);

        FrameRect(hDC, pRect, hBR);
        }

    SetBkMode(hDC, bkmodeOld);
    }



/*
 * DrawHandle
 *
 * Purpose:
 *  Draw a handle box at the specified coordinate
 *
 * Parameters:
 *  hDC             HDC to be drawn into
 *  x, y            int upper left corner coordinate of the handle box
 *  cSize           UINT size of handle box
 *  fInvert         BOOL indicating to invert the rect or fill it
 *  fDraw           BOOL draw if TRUE, erase if FALSE,
 *                  ignored if fInvert is TRUE
 *
 * Return Value:
 *  None
 */

void DrawHandle(HDC hDC, int x, int y, UINT cSize, BOOL fInvert
    , BOOL fDraw)
    {
    HBRUSH  hBR;
    HBRUSH  hBROld;
    HPEN    hPen;
    HPEN    hPenOld;
    RECT    rc;

    if (!fInvert)
        {
        if (fDraw)
            {
            hPen=(HPEN)GetStockObject(BLACK_PEN);
            hBR=(HBRUSH)GetStockObject(BLACK_BRUSH);
            }
        else
            {
            hPen=(HPEN)GetStockObject(WHITE_PEN);
            hBR=(HBRUSH)GetStockObject(WHITE_PEN);
            }

        hPenOld=(HPEN)SelectObject(hDC, hPen);
        hBROld=(HBRUSH)SelectObject(hDC, hBR);
        Rectangle(hDC, x, y, x+cSize, y+cSize);
        SelectObject(hDC, hPenOld);
        SelectObject(hDC, hBROld);
        }
    else
        {
        rc.left=x;
        rc.top=y;
        rc.right=x + cSize;
        rc.bottom=y + cSize;
        InvertRect(hDC, (LPRECT)&rc);
        }

    return;
    }



/*
 * UIDrawShading
 *
 * Purpose:
 *  Draw a hatching across a rectangle, inside a rectangle, or
 *  outside a rectangle.
 *
 * Parameters:
 *  prc             LPRECT containing the rectangle.
 *  hDC             HDC on which to draw.
 *  dwFlags         DWORD specifying how to draw the shading.
 *  cWidth          UINT width of the border to draw.  Ignored
 *                  if dwFlags has UI_SHADE_FULLRECT.
 *
 * Return Value:
 *  None
 */

STDAPI_(void) UIDrawShading(LPRECT prc, HDC hDC, DWORD dwFlags, UINT cWidth)
    {
    HBRUSH      hBR;
    HBRUSH      hBROld;
    HBITMAP     hBM;
    RECT        rc;
    UINT        cx, cy;
    COLORREF    crText;
    COLORREF    crBk;
    const DWORD dwROP=0x00A000C9L;  //DPa

    if (NULL==prc || NULL==hDC)
        return;

    hBM=CreateBitmap(8, 8, 1, 1, g_wHatchBmp);
    hBR=CreatePatternBrush(hBM);
    hBROld=(HBRUSH)SelectObject(hDC, hBR);

    rc=*prc;
    cx=rc.right-rc.left;
    cy=rc.bottom-rc.top;

    if (UI_SHADE_FULLRECT==dwFlags)
        {
        crText=SetTextColor(hDC, RGB(255, 255, 255));
        crBk=SetBkColor(hDC, RGB(0, 0, 0));
        PatBlt(hDC, rc.left, rc.top, cx, cy, dwROP);
        }
    else
        {
        if (UI_SHADE_BORDEROUT==dwFlags)
            InflateRect((LPRECT)&rc, cWidth-1, cWidth-1);

        crText=SetTextColor(hDC, RGB(255, 255, 255));
        crBk=SetBkColor(hDC, RGB(0, 0, 0));
        PatBlt(hDC, rc.left, rc.top, cx, cWidth, dwROP);
        PatBlt(hDC, rc.left, rc.top, cWidth, cy, dwROP);
        PatBlt(hDC, rc.right-cWidth, rc.top, cWidth, cy, dwROP);
        PatBlt(hDC, rc.left, rc.bottom-cWidth, cx, cWidth, dwROP);
        }

    SetTextColor(hDC, crText);
    SetBkColor(hDC, crBk);
    SelectObject(hDC, hBROld);
    DeleteObject(hBR);
    DeleteObject(hBM);

    return;
    }




/*
 * UIShowObject
 *
 * Purpose:
 *  Draw the ShowObject effect around an embedded or linked
 *  object.
 *
 * Parameters:
 *  prc             LPRECT to draw around.
 *  hDC             HDC on which to draw.
 *  fLink           BOOL specifying a linked (TRUE) or
 *                  embedded (FALSE) object
 *
 * Return Value:
 *  None
 */

STDAPI_(void) UIShowObject(LPCRECT prc, HDC hDC, BOOL fLink)
    {
    HPEN    hPen;
    HPEN    hPenOld;
    HBRUSH  hBROld;

    if (NULL==prc || NULL==hDC)
        return;

    hPen=fLink ? CreatePen(PS_DASH, 1, RGB(0,0,0))
        : (HPEN)GetStockObject(BLACK_PEN);

    if (!hPen)
        return;

    hPenOld=(HPEN)SelectObject(hDC, hPen);
    hBROld=(HBRUSH)SelectObject(hDC, GetStockObject(NULL_BRUSH));

    Rectangle(hDC, prc->left, prc->top, prc->right, prc->bottom);

    SelectObject(hDC, hPenOld);
    SelectObject(hDC, hBROld);

    if (fLink)
        DeleteObject(hPen);

    return;
    }
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
