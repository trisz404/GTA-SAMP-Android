TOOLCHAIN_PREFIX = arm-linux-androideabi-
CC = $(TOOLCHAIN_PREFIX)gcc
CXX = $(TOOLCHAIN_PREFIX)g++
STRIP = $(TOOLCHAIN_PREFIX)strip

DUMMYDIR = dummy_libs
DUMMYS = libGTASA.so libImmEmulatorJ.so libSCAnd.so

CFLAGS = -shared -g -Wall -O2 -pipe -fexceptions -D_THREAD_SAFE -DNDEBUG -std=c++11 -ffunction-sections -fdata-sections -Wl,--gc-sections
CFLAGS += -march=armv7-a -mfloat-abi=softfp -mfpu=neon

INCDIRS = rw_include sa_include

LIBDIRS = $(DUMMYDIR)
LIBS = log GTASA

SRCDIR = src
SRCFILES = main.cpp

OBJDIR = obj

TARGET = libSAMP.so

default: init $(DUMMYS:%.so=$(DUMMYDIR)/%.so) $(SRCFILES:%.cpp=$(OBJDIR)/%.o) $(TARGET)
	@echo --------------------------------------
	@echo Build Done
	@echo --------------------------------------

init:
	@if not exist $(OBJDIR) mkdir $(OBJDIR)
	@if not exist $(DUMMYDIR) mkdir $(DUMMYDIR)

$(DUMMYDIR)/%.so:
	@echo Make dummy for $(@:$(DUMMYDIR)/%.so=%.so)
	@echo. >> dummy.cpp
	@$(CXX) -shared dummy.cpp -o $@
	@del dummy.cpp

$(OBJDIR)/%.o:
	@echo compile $(@:$(OBJDIR)/%.o=%.cpp)
	@$(CXX) $(CFLAGS) $(INCDIRS:%=-I%) -c $(@:$(OBJDIR)/%.o=$(SRCDIR)/%.cpp) -o $@

$(TARGET):
	@echo linking $@
	@$(CXX) $(CFLAGS) $(LIBDIRS:%=-L%) $(OBJDIR)/$(SRCFILES:%.cpp=%.o) $(LIBS:%=-l%) -o $(TARGET)
	@$(STRIP) -s -R .comment -R .gnu.version --strip-unneeded $(TARGET)
	
clean:
	@if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	@if exist $(DUMMYDIR) rmdir /s /q $(DUMMYDIR)
	@if exist $(TARGET) del $(TARGET)
	@echo --------------------------------------
	@echo Clean Done
	@echo --------------------------------------