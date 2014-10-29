/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

/// \file
/// \brief Contains TelnetTransport , used to supports the telnet transport protocol.  Insecure
///

#ifndef __TELNET_TRANSPORT
#define __TELNET_TRANSPORT

#include "TransportInterface.h"
#include "DS_List.h"
#include "Export.h"
class TCPInterface;
struct TelnetClient;

/// \brief Use TelnetTransport to easily allow windows telnet to connect to your ConsoleServer
/// \details To run Windows telnet, go to your start menu, click run, and in the edit box type "telnet <IP>" where <IP> is the ip address.<BR>
/// of your ConsoleServer (most likely the same IP as your game).<BR>
/// This implementation always echos commands.
class RAK_DLL_EXPORT TelnetTransport : public TransportInterface
{
public:
	TelnetTransport();
	~TelnetTransport();
	bool Start(unsigned short port, bool serverMode);
	void Stop(void);
	void Send( PlayerID playerId, const char *data, ... );
	void CloseConnection( PlayerID playerId );
	Packet* Receive( void );
	void DeallocatePacket( Packet *packet );
	PlayerID HasNewConnection(void);
	PlayerID HasLostConnection(void);
	CommandParserInterface* GetCommandParser(void);
protected:

	struct TelnetClient
	{
		PlayerID playerId;
		char textInput[REMOTE_MAX_TEXT_INPUT];
		unsigned cursorPosition;
	};

	TCPInterface *tcpInterface;
	void AutoAllocate(void);
	bool ReassembleLine(TelnetTransport::TelnetClient* telnetClient, unsigned char c);

	// Crap this sucks but because windows telnet won't send line at a time, I have to reconstruct the lines at the server per player
	DataStructures::List<TelnetClient*> remoteClients;
};

#endif
