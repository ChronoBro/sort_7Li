OBJECTS = det.o silicon.o histo.o caen.o calibrate.o TDC1190.o  elist.o telescope.o pixels.o doppler.o ZApar.o pid.o solution.o einstein.o newton.o correl.o loss.o blockCal.o 
ALLOBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
CFLAGS= -c -O2 -std=c++11 -W -I$(shell root-config --incdir) -g
COMPILER= g++
LINKOPTION = $(shell root-config --libs)


sort: sort.o $(OBJECTS)
	$(COMPILER) -o sort sort.o $(OBJECTS) $(LINKOPTION)
 
MixedRPie: MixedRPie.o $(OBJECTS)
	$(COMPILER) -o MixedRPie MixedRPie.o $(OBJECTS) $(LINKOPTION)

MixedRRing: MixedRRing.o $(OBJECTS)
	$(COMPILER) -o MixedRRing MixedRRing.o $(OBJECTS) $(LINKOPTION)

MixedSPie: MixedSPie.o $(OBJECTS)
	$(COMPILER) -o MixedSPie MixedSPie.o $(OBJECTS) $(LINKOPTION)
 
 
MixedSRing: MixedSRing.o $(OBJECTS)
	$(COMPILER) -o MixedSRing MixedSRing.o $(OBJECTS) $(LINKOPTION)

$(ALLOBJECTS): %.o : %.cpp
	$(COMPILER) $(CFLAGS) $< -o $@


clean:
	rm -f *.o

