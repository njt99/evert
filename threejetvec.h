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

#ifndef __THREEJETVEC
#define __THREEJETVEC
#include "threejet.h"
#include "twojetvec.h"
struct ThreeJetVec {
  ThreeJet x;
  ThreeJet y;
  ThreeJet z;
  operator TwoJetVec() { return TwoJetVec(x,y,z); }
};

ThreeJetVec operator+(ThreeJetVec v, ThreeJetVec w);
ThreeJetVec operator*(ThreeJetVec v, ThreeJet  a);
ThreeJetVec operator*(ThreeJetVec v, double a);
ThreeJetVec AnnihilateVec(ThreeJetVec v, int index);
ThreeJetVec Cross(ThreeJetVec v, ThreeJetVec w);
ThreeJet Dot(ThreeJetVec v, ThreeJetVec w);
TwoJetVec D(ThreeJetVec x, int index);
ThreeJetVec Normalize(ThreeJetVec v);
ThreeJetVec RotateZ(ThreeJetVec v, ThreeJet angle);
ThreeJetVec RotateY(ThreeJetVec v, ThreeJet angle);
ThreeJetVec RotateX(ThreeJetVec v, ThreeJet angle);
ThreeJetVec InterpolateVec(ThreeJetVec v1, ThreeJetVec v2, ThreeJet weight);
ThreeJet Length(ThreeJetVec v);
#endif
