#! make -f
# Define default flags (include your source tree for example
ifdef final
	WX_CONFIG=wx-config-static
else
	WX_CONFIG=wx-config
endif
CXX = `$(WX_CONFIG) --cxx`
INCFLAGS = -I./src
CXXFLAGS = -std=c++17 `$(WX_CONFIG) --cxxflags` $(INCFLAGS) -DwxOVERRIDE=override
ifdef final
	LDLIBS   = `$(WX_CONFIG) --libs` -static
else
	LDLIBS   = `$(WX_CONFIG) --libs`
endif
RESCOMP = `$(WX_CONFIG) --rescomp`

ifdef final
    EXTRAFLAGS = -MD
else
    EXTRAFLAGS = -MD -g
endif

PROGRAM = wx01

OBJECTS = $(PROGRAM).o $(PROGRAM)_resources.o

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
	rm -rf $(PROGRAM).exe $(OBJECTS) Test_resources.o
