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

#include "threejetvec.h"
#include "figureeight.h"
#include "spline.h"
#include "sphere.h"
extern "C" {
#include <strings.h>
}

double scale = M_PI;
int scene = 0;
int bezier = 0;
char *parts = NULL;

int n_strips = N_STRIPS;

static char Usage[] = "\
Usage: evert [-time T] [-nstrips N] [-scale S] [-bezier] [-whole] [-parts PARTS]\n\
	[-umin Umin] [-umax Umax]  [-du Ustep]\n\
	[-vmin Vmin] [-vmax Vmax]  [-dv Vstep]\n\
	[-corr Tc] [-push Tp] [-twist Tt] [-unpush Tu] [-uncorr Tf]\n\
Generate an everting sphere in Geomview/OOGL MESH or (if -bezier) Bezier form,\n\
at eversion time T (0<=T<=1).  Surface (of T=0 sphere) parametrized by\n\
  \"u\": u=0 at +Z pole, u=1 at equator, u=2 at -Z pole,\n\
  \"v\": v=0 at +Y, increasing toward +X, v=1 at longitude 2pi/(number of strips)\n\
Emits slice ranging in u from Umin..Umax, v from Vmin..Vmax,\n\
with each OOGL MESH (or Bezier) element spanning range Ustep x Vstep.\n\
With -whole, include transformations to replicate [0..1,0..1] to whole sphere.\n\
With -parts, replicate selected portions, e.g. +0-0+2+4+6 for one pole-to-pole\n\
strip, plus every other strip in +Z hemisphere; numbers range 0 .. nstrips-1.\n\
Eversion stages corrugate-push-twist-unpush begin at times given by\n\
-corr -push -twist -unpush respectively.  Produces radius-S sphere.  Defaults:\n\
  -time 0 -nstrips 8 -scale 1  -parts +0\n\
  -umin 0 -umax 1  -du .08333  -vmin 0  -vmax 1  -dv .08333\n\
  -corr 0 -push .1 -twist .23 -unpush .6 -uncorr .93\n";

int main(int argc, char **argv) {
  double umin, vmin, umax, vmax;
  double du, dv;
  double time = 0.0;
  double corrstart, pushstart, twiststart, unpushstart, uncorrstart;
  double bendtime;
  int havetime = 0;

  bendtime = -1.0;		// -1 means don't do bendtime at all
  corrstart = 0;
  pushstart = .1;
  twiststart = .23;
  unpushstart = .6;
  uncorrstart = .93;
  int binary = 0;

  vmin = 0.0;
  umin = 0.0;
  vmax = 1.0;
  umax = 1.0;
  du = dv = 1./12.;

  argv++;
  while (--argc) {
    if (!strcmp("-scene", argv[0])) {
      scene = 1;
    } else if (!strcmp("-time", argv[0])) {
      time = atof(argv[1]);
      havetime = 1;
      argv++; argc--;
    } else if (!strcmp("-corr", argv[0])) {
      corrstart = atof(argv[1]);
      argv++; argc--;
    } else if (!strcmp("-push", argv[0])) {
      pushstart = atof(argv[1]);
      argv++; argc--;
    } else if (!strcmp("-twist", argv[0])) {
      twiststart = atof(argv[1]);
      argv++; argc--;
    } else if (!strcmp("-unpush", argv[0])) {
      unpushstart = atof(argv[1]);
      argv++; argc--;
    } else if (!strcmp("-uncorr", argv[0])) {
      uncorrstart = atof(argv[1]);
      argv++; argc--;
    } else if (!strcmp("-umin", argv[0])) {
      umin = atof(argv[1]);
      argv++; argc--;
    } else if (!strcmp("-umax", argv[0])) {
      umax = atof(argv[1]);
      argv++; argc--;
    } else if (!strcmp("-vmin", argv[0])) {
      vmin = atof(argv[1]);
      argv++; argc--;
    } else if (!strcmp("-vmax", argv[0])) {
      vmax = atof(argv[1]);
      argv++; argc--;
    } else if (!strcmp("-du", argv[0])) {
      du = atof(argv[1]);
      argv++; argc--;
    } else if (!strcmp("-dv", argv[0])) {
      dv = atof(argv[1]);
      argv++; argc--;
    } else if (!strcmp("-jmax", argv[0]) || !strcmp("-kmax", argv[0])) {
      fprintf(stderr, "evert: -jmax and -kmax are no longer recognized.\n");
      fprintf(stderr, "use -du and -dv instead.");
      argv++,argc--;
    } else if (!strcmp("-whole", argv[0])) {
      parts = "*";
    } else if (!strcmp("-parts", argv[0])) {
      parts = argv[1];
      argv++, argc--;
    } else if (!strcmp("-nstrips", argv[0])) {
      n_strips = atoi(argv[1]);
      argv++; argc--;
    } else if (!strcmp("-scale", argv[0])) {
      scale = atof(argv[1]);
      argv++; argc--;
    } else if (!strcmp("-bscene", argv[0])) {
      scene = 0;
    } else if (!strcmp("-bezier", argv[0])) {
      bezier = 1;
    } else {
      fprintf(stderr, "evert: Unrecognized argument \"%s\"\n%s",
	argv[0], Usage);
      exit(1);
    }
    argv++;
  }

  if(!havetime) {
    fprintf(stderr, "evert: Must specify -time.\n%s", Usage);
    exit(1);
  }

  if (bendtime >= 0.0) {
    printScene(BendIn, umin, umax, du, vmin, vmax, dv, bendtime, binary);
  } else {

    /* time = (time - howfar) / chunk */
    if (!scene) 
      if (time >= uncorrstart && uncorrstart >= 0) 
	printScene(UnCorrugate, umin, umax, du, vmin, vmax, dv, 
		   (time - uncorrstart) / (1.0 - uncorrstart), binary);
      else if (time >= unpushstart && unpushstart >= 0) 
	printScene(UnPush, umin, umax, du, vmin, vmax, dv,
		   (time - unpushstart) / 
		   (((uncorrstart < 0) ? 1.0 : uncorrstart) - unpushstart), binary);
      else if (time >= twiststart && twiststart >= 0) 
	printScene(Twist, umin, umax, du, vmin, vmax, dv, 
		   (time - twiststart) / 
		   (((unpushstart < 0) ? 1.0 : unpushstart) - twiststart), binary);
      else if (time >= pushstart && pushstart >= 0) 
	printScene(PushThrough, umin, umax, du, vmin, vmax, dv,
		   (time - pushstart) / 
		   (((twiststart < 0) ? 1.0 : twiststart) - pushstart), binary);
      else if (time >= corrstart && corrstart >= 0) 
	printScene(Corrugate, umin, umax, du, vmin, vmax, dv,
		   (time - corrstart) / 
		   (((pushstart < 0) ? 1.0 : pushstart) - corrstart), binary);
  }

  exit(0);
}






