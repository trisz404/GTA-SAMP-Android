TOOLCHAIN_PREFIX = arm-linux-androideabi-
CC = $(TOOLCHAIN_PREFIX)gcc
CXX = $(TOOLCHAIN_PREFIX)g++
STRIP = $(TOOLCHAIN_PREFIX)strip

DUMMYDIR = dummy_libs
DUMMYS = libGTASA.so libImmEmulatorJ.so libSCAnd.so

CFLAGS = -shared -g -Wall -Ofast -pipe -fexceptions -D_THREAD_SAFE -DNDEBUG -std=c++11 -ffunction-sections -fdata-sections -Wl,--gc-sections
CFLAGS += -march=armv7-a -mfloat-abi=softfp -mfpu=neon
CFLAGS += -w

INCDIRS = rw_include sa_include

LIBDIRS = $(DUMMYDIR)
LIBS = log GTASA

SRCDIR = src
SRCFILES = main.cpp utils.cpp hooks.cpp

# EmailSender.cpp FullyConnectedMesh.cpp NetworkIDGenerator.cpp
RNDIR = raknet
RNFILES = _findfirst.cpp AsynchronousFileIO.cpp BitStream.cpp \
	CheckSum.cpp CommandParserInterface.cpp ConsoleServer.cpp \
	DataBlockEncryptor.cpp DataCompressor.cpp DS_ByteQueue.cpp \
	DS_HuffmanEncodingTree.cpp DS_Table.cpp \
	EncodeClassName.cpp ExtendedOverlappedPool.cpp \
	FileOperations.cpp GetTime.cpp \
	InternalPacketPool.cpp LinuxStrings.cpp LogCommandParser.cpp \
	NetworkTypes.cpp PluginInterface.cpp \
	RakClient.cpp RakNetCommandParser.cpp RakNetStatistics.cpp \
	RakNetworkFactory.cpp RakPeer.cpp rakserver.cpp RakSleep.cpp \
	Rand.cpp ReliabilityLayer.cpp rijndael.cpp RPCMap.cpp SHA1.cpp \
	SimpleMutex.cpp SocketLayer.cpp StringCompressor.cpp StringTable.cpp \
	SystemAddressList.cpp SystemDatabaseClient.cpp SystemDatabaseServer.cpp \
	TableSerializer.cpp TCPInterface.cpp TelnetTransport.cpp \
	SAMP/samp_netencr.cpp
CFLAGS += -DHOST_ENDIAN_IS_LITTLE -DLITTLE_ENDIAN -DRAKSAMP_CLIENT -DNETCODE_OPENCONNLULZ=6969

OBJDIR = obj

TARGET = libSAMP.so

default: init $(DUMMYS:%.so=$(DUMMYDIR)/%.so) $(SRCFILES:%.cpp=$(OBJDIR)/$(SRCDIR)/%.o) $(RNFILES:%.cpp=$(OBJDIR)/$(RNDIR)/%.o) $(TARGET)
	@echo --------------------------------------
	@echo Build Done
	@echo --------------------------------------

init:
	@if not exist $(OBJDIR) mkdir $(OBJDIR)
	@if not exist $(OBJDIR)\$(SRCDIR) mkdir $(OBJDIR)\$(SRCDIR)
	@if not exist $(OBJDIR)\$(RNDIR) mkdir $(OBJDIR)\$(RNDIR)
	@if not exist $(OBJDIR)\$(RNDIR)\SAMP mkdir $(OBJDIR)\$(RNDIR)\SAMP
	@if not exist $(DUMMYDIR) mkdir $(DUMMYDIR)

$(DUMMYDIR)/%.so:
	@echo Make dummy for $(@:$(DUMMYDIR)/%.so=%.so)
	@echo. >> dummy.cpp
	@$(CXX) -shared dummy.cpp -o $@
	@del dummy.cpp

$(OBJDIR)/$(SRCDIR)/%.o:
	@echo compile $(@:$(OBJDIR)/%.o=%.cpp)
	@$(CXX) $(CFLAGS) $(INCDIRS:%=-I%) -c $(@:$(OBJDIR)/%.o=%.cpp) -o $@

$(OBJDIR)/$(RNDIR)/%.o:
	@echo compile $(@:$(OBJDIR)/%.o=%.cpp)
	@$(CXX) $(CFLAGS) $(INCDIRS:%=-I%) -c $(@:$(OBJDIR)/%.o=%.cpp) -o $@

$(TARGET):
	@echo linking $@
	@$(CXX) $(CFLAGS) $(LIBDIRS:%=-L%) $(SRCFILES:%.cpp=$(OBJDIR)/$(SRCDIR)/%.o) $(RNFILES:%.cpp=$(OBJDIR)/$(RNDIR)/%.o) $(LIBS:%=-l%) -o $(TARGET)
	@$(STRIP) --remove-section=.comment --remove-section=.note --remove-section=.gnu.version --strip-all $(TARGET)
	
clean:
	@if exist $(OBJDIR) rmdir /s /q $(OBJDIR)
	@if exist $(DUMMYDIR) rmdir /s /q $(DUMMYDIR)
	@if exist $(TARGET) del $(TARGET)
	@echo --------------------------------------
	@echo Clean Done
	@echo --------------------------------------