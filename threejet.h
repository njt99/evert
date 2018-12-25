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

#ifndef __THREEJET
#define __THREEJET
#include "twojet.h"

#define DIM 2
class ThreeJet {
  double f;
  double fu, fv;
  double fuu, fuv, fvv;
  double fuuv, fuvv;

  ThreeJet(double d, double du, double dv, double duu, double duv, double dvv,
   double duuv, double duvv)
   { f = d; fu = du; fv = dv; fuu = duu; fuv = duv; fvv = dvv;
     fuuv = duuv; fuvv = duvv; }
  public:
  ThreeJet() {}
  ThreeJet(double d, double du, double dv)
   { f = d; fu = du; fv = dv; fuu = fuv = fvv = fuuv = fuvv = 0;}
  operator TwoJet() { return TwoJet(f, fu, fv, fuv); }
  operator double() { return f; }
  operator<(double d) { return f < d; }
  operator>(double d) { return f > d; }
  operator<=(double d) { return f <= d; }
  operator>=(double d) { return f >= d; }
  void operator %=(double d)
   { f = fmod(f, d); if (f < 0) f += d; }
  friend ThreeJet operator+(const ThreeJet x, const ThreeJet y);
  friend ThreeJet operator*(const ThreeJet x, const ThreeJet y);
  friend ThreeJet operator+(const ThreeJet x, double d);
  friend ThreeJet operator*(const ThreeJet x, double d);
  friend ThreeJet Sin(const ThreeJet x);
  friend ThreeJet Cos(const ThreeJet x);
  friend ThreeJet operator^(const ThreeJet x, double n);
  friend ThreeJet Annihilate(const ThreeJet x, int index);
  friend ThreeJet Interpolate(const ThreeJet v1, const ThreeJet v2, const ThreeJet weight);
  friend void printJet(const ThreeJet);
  friend class TwoJet D(const class ThreeJet x, int index);
};

#endif
