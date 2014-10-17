#include <jni.h>
#include <stdio.h>
#include <android/log.h>
#include <dlfcn.h>
#include <unistd.h>
#include <pthread.h>

#include <GTASA.h>

#include "hooks.h"

#include "../raknet/RakClient.h"
#include "../raknet/RakNetworkFactory.h"
#include "../raknet/PacketEnumerations.h"
#include "../raknet/StringCompressor.h"
#include "../network/CNetGame.h"


int log(const char *format, ...)
{
   va_list arg;
   int done;

   va_start (arg, format);

   char buf[2048];
   done = vsprintf (buf, format, arg);

   __android_log_write(ANDROID_LOG_INFO, "SA_HACK_LOG", buf);

   va_end (arg);

   return done;
}

#define _byteswap_ulong(x) __builtin_bswap32(x)
#define _byteswap_uint64(x) __builtin_bswap64(x)

void *wantedthread(void* punused)
{
    while(gGameState != 9)
		sleep(1); 
	
    log("Game loaded!");

    ToggleDebugFPS();

    sleep(5);

	CWanted::SetMaximumWantedLevel(0);
    FindPlayerPed(-1)->SetWantedLevel(0);
	
	CNetGame l_NetGame;
	l_NetGame.DbgConnect();
	
	for(;;)
	{
		Packet* l_Packet = 0;
		while((l_Packet = l_NetGame.getRakInterface()->Receive()))
		{
			int packetId = l_Packet->data[0];
			switch(packetId) 
			{
				case ID_DISCONNECTION_NOTIFICATION:
					log("Disconnected !");
					break;
				case ID_CONNECTION_LOST:
					log("Connection lost !");
					break;
				case ID_MODIFIED_PACKET:
					log("Modified packet !");
					break;
				default:
					log("Packet received -> %d\n", packetId);
					break;
			}
		
			l_NetGame.getRakInterface()->DeallocatePacket(l_Packet);	
		}
	
		sleep(10);
	}
	
	
	
	return 0;
}

void inithack()
{
    log("Starting thread...");
    pthread_t thread;
    pthread_create(&thread, NULL, wantedthread, 0);

	InitHooks();
	
}

extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved);
jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    // Get jclass with env->FindClass.
    // Register methods with env->RegisterNatives.
	
	inithack();

    return JNI_VERSION_1_6;
}