#include <jni.h>
#include <GTASA.h>
#include "hooks.h"
#include "CNetGame.h"
#include "utils.h"

extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved);
jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    // Get jclass with env->FindClass.
    // Register methods with env->RegisterNatives.
	
	InitHooks();

    return JNI_VERSION_1_6;
}