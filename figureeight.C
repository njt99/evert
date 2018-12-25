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

#include "figureeight.h"

extern n_strips;

TwoJetVec FigureEight(
  TwoJetVec w, TwoJetVec h, TwoJetVec bend, TwoJet form, TwoJet v
) {
  TwoJet height;
  v %= 1;
  height = (Cos (v*2) + -1) * (-1);
  if (v > 0.25 && v < 0.75)
    height = height*-1 + 4;
  height = height*0.6;
  h = h + bend*(height*height*(1/64.));
  return 
    w*Sin (v*2) + (h) * (Interpolate((Cos (v) + -1) * (-2), height, form))
  ;
}
  
TwoJetVec AddFigureEight(ThreeJetVec p, ThreeJet u, TwoJet v, ThreeJet form, ThreeJet scale)
{
  ThreeJet size = form*scale;
  form = form*2 + form*form*-1;
  TwoJetVec dv = AnnihilateVec(D(p, 1), 1);
  p = AnnihilateVec(p, 1);
  TwoJetVec du = Normalize(D(p, 0));
  TwoJetVec h = Normalize(Cross(du, dv))*TwoJet(size);
  TwoJetVec w = Normalize(Cross(h, du))*(TwoJet(size)*1.1);
  return RotateZ(
    TwoJetVec(p) +
      FigureEight(w, h, du*D(size, 0)*(D(u, 0)^(-1)), form, v),
    v*(1./n_strips)
  );
}
