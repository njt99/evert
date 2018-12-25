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

#ifndef __TWOJETVEC
#define __TWOJETVEC
#include "twojet.h"
struct TwoJetVec {
  TwoJet x;
  TwoJet y;
  TwoJet z;
  TwoJetVec() {}
  TwoJetVec(TwoJet a, TwoJet b, TwoJet c) { x = a; y = b; z = c; }
};

TwoJetVec operator+(TwoJetVec v, TwoJetVec w);
TwoJetVec operator*(TwoJetVec v, TwoJet  a);
TwoJetVec operator*(TwoJetVec v, double a);
TwoJetVec AnnihilateVec(TwoJetVec v, int index);
TwoJetVec Cross(TwoJetVec v, TwoJetVec w);
TwoJet Dot(TwoJetVec v, TwoJetVec w);
TwoJetVec Normalize(TwoJetVec v);
TwoJetVec RotateZ(TwoJetVec v, TwoJet angle);
TwoJetVec RotateY(TwoJetVec v, TwoJet angle);
TwoJetVec RotateX(TwoJetVec v, TwoJet angle);
TwoJetVec InterpolateVec(TwoJetVec v1, TwoJetVec v2, TwoJet weight);
TwoJet Length(TwoJetVec v);
#endif
