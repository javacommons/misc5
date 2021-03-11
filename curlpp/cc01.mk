#! make -f
ifdef final
	WX_CONFIG=wx-config-static
else
	WX_CONFIG=wx-config
endif
CXX = g++
INCFLAGS = -I./src
CXXFLAGS = -std=c++17 $(INCFLAGS) `curlpp-config --cflags`
ifdef final
	LDLIBS   = `curlpp-config --static-libs` -static
else
	LDLIBS   = `curlpp-config --libs`
endif
RESCOMP =

ifdef final
    EXTRAFLAGS = -MD
else
    EXTRAFLAGS = -MD -g
endif

PROGRAM = cc01

#OBJECTS = $(PROGRAM).o $(PROGRAM)_resources.o
OBJECTS = $(PROGRAM).o

.SUFFIXES: .o .cpp

.cpp.o:
	$(CXX) $(CXXFLAGS) $(EXTRAFLAGS) -c  -o $@ $<

all: $(PROGRAM)

$(PROGRAM):$(OBJECTS)
	$(CXX) -o $(PROGRAM) $(OBJECTS) $(LDLIBS)
ifdef final
	strip $(PROGRAM).exe
endif

$(PROGRAM)_resources.o: $(PROGRAM).rc
	$(RESCOMP) -i $(PROGRAM).rc -o $(PROGRAM)_resources.o

clean:
	rm -rf $(PROGRAM).d $(PROGRAM).exe $(OBJECTS) $(PROGRAM)_resources.o
