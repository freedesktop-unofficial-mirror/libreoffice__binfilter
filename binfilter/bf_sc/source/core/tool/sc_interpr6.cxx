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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <basegfx/numeric/ftools.hxx>


#include "interpre.hxx"
namespace binfilter {


//! #66556# for os2icci3 this function MUST be compiled without optimizations,
//! otherwise it won't work at all or even worse will produce false results!
double ScInterpreter::GetGammaDist(double x, double alpha, double beta)
{
    if (x == 0.0)
        return 0.0;

    x /= beta;
    double gamma = alpha;

    double c = 0.918938533204672741;
    double d[10] = {
        0.833333333333333333E-1,
        -0.277777777777777778E-2,
        0.793650793650793651E-3,
        -0.595238095238095238E-3,
        0.841750841750841751E-3,
        -0.191752691752691753E-2,
        0.641025641025641025E-2,
        -0.295506535947712418E-1,
        0.179644372368830573,
        -0.139243221690590111E1
    };

    double dx = x;
    double dgamma = gamma;
    int maxit = 10000;

    double z = dgamma;
    double den = 1.0;
    while ( z < 10.0 )      //! approx?
    {
        den *= z;
        z += 1.0;
    }

    double z2 = z*z;
    double z3 = z*z2;
    double z4 = z2*z2;
    double z5 = z2*z3;
    double a = ( z - 0.5 ) * log(z) - z + c;
    double b = d[0]/z + d[1]/z3 + d[2]/z5 + d[3]/(z2*z5) + d[4]/(z4*z5) +
               d[5]/(z*z5*z5) + d[6]/(z3*z5*z5) + d[7]/(z5*z5*z5) + d[8]/(z2*z5*z5*z5);
    // double g = exp(a+b) / den;

    double sum = 1.0 / dgamma;
    double term = 1.0 / dgamma;
    double cut1 = dx - dgamma;
    double cut2 = dx * 10000000000.0;

    for ( int i=1; i<=maxit; i++ )
    {
        double ai = i;
        term = dx * term / ( dgamma + ai );
        sum += term;
        double cutoff = cut1 + ( cut2 * term / sum );
        if ( ai > cutoff )
        {
            double t = sum;
            // return pow( dx, dgamma ) * exp( -dx ) * t / g;
            return exp( dgamma * log(dx) - dx - a - b ) * t * den;
        }
    }

//  OSL_FAIL("GetGammaDist bricht nicht ab");

    return 1.0;     // should not happen ...
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
