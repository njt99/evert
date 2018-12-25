/*
 * Copyright 1995 Geometry Center, University of Minnesota.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#ifndef __SPLINE
#define __SPLINE
#include "threejetvec.h"
#include "twojetvec.h"

typedef TwoJetVec SurfaceTimeFunction(ThreeJet u, ThreeJet v, double t);

void print_point (FILE *fp, TwoJetVec p, double ps, double pus, double pvs, double puvs);
void printSpline(FILE *fp, TwoJetVec v00, TwoJetVec v01, TwoJetVec v10, TwoJetVec v11, double us, double vs, double s0,double s1,double t0,double t1);
void printScene(
  SurfaceTimeFunction *func,
  double umin, double umax, double du,
  double vmin, double vmax, double dv,
  double t, int binary
);        
void impossible(char *msg);
#endif
