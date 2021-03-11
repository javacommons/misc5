#! make -f
# Define default flags (include your source tree for example
ifdef final
	WX_CONFIG=wx-config-static
else
	WX_CONFIG=wx-config
endif
CXX = `$(WX_CONFIG) --cxx`
INCFLAGS = -I./src
CXXFLAGS = `$(WX_CONFIG) --cxxflags` -DwxOVERRIDE=override
ifdef final
	LDLIBS   = `$(WX_CONFIG) --libs` -static
else
	LDLIBS   = `$(WX_CONFIG) --libs`
endif
REZFLAGS = `$(WX_CONFIG) --rez-flags`

ifdef final
    EXTRAFLAGS = -MD -g
    #EXTRAFLAGS = -MD -O2 -fno-rtti -fno-exceptions -fomit-frame-pointer
else
    EXTRAFLAGS = -MD -g
endif

PROGRAM = wx01

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

Test_resources.o: Test.rc
	windres -i Test.rc -o Test_resources.o $(REZFLAGS)

clean:
	rm -rf $(PROGRAM).exe $(OBJECTS) Test_resources.o
