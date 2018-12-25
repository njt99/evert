include Makefile.preamble
DEBUGOBJS= debug.o threejet.o threejetvec.o spline.o figureeight.o
SPHEREOBJS= sphere.o evert.o threejet.o threejetvec.o spline.o figureeight.o twojet.o twojetvec.o


.SUFFIXES: .o .c .m .C

.C.o:
	$(CC) $(CFLAGS) -c ${@:o=C}

evert: $(SPHEREOBJS)
	$(CC) $(CFLAGS) $(SPHEREOBJS) $(LIBS) -o evert

debug: $(DEBUGOBJS)
	$(CC) $(CFLAGS) $(DEBUGOBJS) $(LIBS) -o debug

test.000: jet
	-rm test.???
	jet

jet: jet.o
	$(CC) $(CFLAGS) jet.o $(LIBS) -o jet

npp: npp.c
	$(CC) $(CFLAGS) -o npp npp.c

clean:
	rm -f $(SPHEREOBJS) $(DEBUGOBJS) debug evert

manual:
	latex manual

sphere.o: spline.h figureeight.h threejetvec.h threejet.h 
twojet.o: twojet.h threejet.h
twojetvec.o: twojetvec.h twojet.h threejet.h
threejet.o: threejet.h
threejetvec.o: threejetvec.h threejet.h
spline.o: spline.h threejetvec.h threejet.h twojet.h
figureeight.o: figureeight.h threejetvec.h threejet.h twojet.h
evert.o: spline.h threejetvec.h threejet.h evert.h figureeight.h twojet.h
