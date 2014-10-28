//#include <dlfcn.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#include <android/log.h>

int log(const char *format, ...)
{
   va_list arg;
   int done;

   va_start (arg, format);

   char buf[2048];
   done = vsprintf (buf, format, arg);

   __android_log_write(ANDROID_LOG_INFO, "SA_HACK_LOG", buf);

   //TODO: Save it to file or something...
   
   va_end (arg);

   return done;
}

int memcpy_protect(void* to, void* from, int len)
{	
	int result = 0;
	
	if (len)
	{
		unsigned char *to_page = (unsigned char *)((unsigned int)(to) & 0xFFFFF000);	
		size_t page_size = 0;
		
		for(int i = 0, j = 0; i < len; ++i)
		{
			page_size = j * 4096;
			if ( &((unsigned char *)(to))[i] >= &to_page[page_size])
				++j;
		}

		result = mprotect(to_page, page_size, 7);	
		memcpy(to, from, len);
	}

	return result;
}

void ARMCALL(void* from, void* to)
{
	unsigned long diff = (unsigned long)(to) - (((unsigned long)(from) & 0xFFFFFFFE) + 4); //Size of the opcode is 4

	unsigned long opcode = (diff >> 12) & 0x7FF | 0xF000 | (((diff >> 1) & 0x7FF | 0xF800) << 16);
	
	memcpy_protect((void*)((unsigned long)(from) & 0xFFFFFFFE), &opcode, 4);
}

void ARMJMP(void* from, void* to)
{
	unsigned long diff = (unsigned long)(to) - (((unsigned long)(from) & 0xFFFFFFFE) + 4); //Size of the opcode is 4

	unsigned long opcode = (diff >> 12) & 0x7FF | 0xF000 | (((diff >> 1) & 0x7FF | 0xB800) << 16);
	
	memcpy_protect((void*)((unsigned long)(from) & 0xFFFFFFFE), &opcode, 4);
}

// void* g_vGTAHandle = (void*)0;

// unsigned int GetBaseAddress()
// {
	// unsigned int l_uiFuncAddr;
	
	// if(g_vGTAHandle == (void*)0)
	// {
		// g_vGTAHandle = dlopen("libGTASA.so", RTLD_NOW);
	// }
	
	// l_uiFuncAddr = (unsigned int)dlsym(g_vGTAHandle, "_ZN7CEntityC2Ev");	
	// l_uiFuncAddr -= 0x00362EBC + 1;	
	// return l_uiFuncAddr;
// }

void ARMBIGJMP(void* from, void* to)
{
	unsigned char hookdata[] =
	{	
		0x01, 0xB4,				// PUSH {R0}
		0x01, 0xB4,				// PUSH {R0}
		0x01, 0x48,				// LDR  R0, ADDR
		0x01, 0x90,				// STR  R0, [SP,#8+var_4]
		0x01, 0xBD,				// POP  {R0,PC}
		0x00, 0xBF,				// NOP
		0x00, 0x00, 0x00, 0x00	// ADDR
	};
	
	*(unsigned long *)&hookdata[12] = (unsigned long)(to);
	
	memcpy_protect((void*)((unsigned long)(from) & 0xFFFFFFFE), hookdata, 16);
}