/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant 
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

/// \file ConsoleServer.h
/// \brief Contains ConsoleServer , used to plugin to your game to accept remote console-based connections
///

#ifndef __CONSOLE_SERVER_H
#define __CONSOLE_SERVER_H

class TransportInterface;
class CommandParserInterface;

#include "DS_List.h"
#include "NetworkTypes.h"
#include "Export.h"

/// \brief The main entry point for the server portion of your remote console application support.
/// ConsoleServer takes one TransportInterface and one or more CommandParserInterface (s)
/// The TransportInterface will be used to send data between the server and the client.  The connecting client must support the
/// protocol used by your derivation of TransportInterface . TelnetTransport and RakNetTransport are two such derivations .
/// When a command is sent by a remote console, it will be processed by your implementations of CommandParserInterface
class RAK_DLL_EXPORT ConsoleServer
{
public:
	ConsoleServer();
	~ConsoleServer();

	/// Call this with a derivation of TransportInterface so that the console server can send and receive commands
	/// \param[in] transportInterface Your interface to use.
	/// \param[in] port The port to host on.  Telnet uses port 23 by default.  RakNet can use whatever you want.
	void SetTransportProvider(TransportInterface *transportInterface, unsigned short port);

	/// Add an implementation of CommandParserInterface to the list of command parsers.
	/// \param[in] commandParserInterface The command parser referred to
	void AddCommandParser(CommandParserInterface *commandParserInterface);

	/// Remove an implementation of CommandParserInterface previously added with AddCommandParser()
	/// \param[in] commandParserInterface The command parser referred to
	void RemoveCommandParser(CommandParserInterface *commandParserInterface);

	/// Call update to read packet sent from your TransportInterface.
	/// You should do this fairly frequently.
	void Update(void);
protected:
	void ListParsers(PlayerID playerId);
	TransportInterface *transport;
	DataStructures::List<CommandParserInterface *> commandParserList;
	char* password[256];
};

#endif
