#include <jni.h>
#include <stdio.h>
#include <android/log.h>
#include <dlfcn.h>
#include <unistd.h>
#include <pthread.h>

#include <GTASA.h>

#include "hooks.h"
#include "CNetGame.h"


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

void *networkthread(void* punused)
{
    while(gGameState != 9)
		sleep(1); 
	
    log("Game loaded!");
	
	CNetGame::Instance()->DbgConnect();	
	
	while (true)
	{
		CNetGame::Instance()->Process();
	}
	return 0;
}

void inithack()
{
    log("Starting thread...");
    pthread_t thread;
    pthread_create(&thread, NULL, networkthread, 0);

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