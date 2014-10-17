#include <dlfcn.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

int memcpy_protect(unsigned char* to, unsigned char* from, int len);

void ARMCALL(unsigned char* from, unsigned char* to)
{
	unsigned long diff = (unsigned long)(to) - (((unsigned long)(from) & 0xFFFFFFFE) + 4); //Size of the opcode is 4

	unsigned long opcode = (diff >> 12) & 0x7FF | 0xF000 | (((diff >> 1) & 0x7FF | 0xF800) << 16);
	
	memcpy_protect((unsigned char*)((unsigned long)(from) & 0xFFFFFFFE), (unsigned char*)(&opcode), 4);
}

void ARMJMP(unsigned char* from, unsigned char* to)
{
	unsigned long diff = (unsigned long)(to) - (((unsigned long)(from) & 0xFFFFFFFE) + 4); //Size of the opcode is 4

	unsigned long opcode = (diff >> 12) & 0x7FF | 0xF000 | (((diff >> 1) & 0x7FF | 0xB800) << 16);
	
	memcpy_protect((unsigned char*)((unsigned long)(from) & 0xFFFFFFFE), (unsigned char*)(&opcode), 4);
}

void* g_vGTAHandle = (void*)0;

unsigned int GetBaseAddress()
{
	unsigned int l_uiFuncAddr;
	
	if(g_vGTAHandle == (void*)0)
	{
		g_vGTAHandle = dlopen("libGTASA.so", RTLD_NOW);
	}
	
	l_uiFuncAddr = (unsigned int)dlsym(g_vGTAHandle, "_ZN7CEntityC2Ev");	
	l_uiFuncAddr -= 0x00362EBC + 1;	
	return l_uiFuncAddr;
}

int memcpy_protect(unsigned char* to, unsigned char* from, int len)
{	
	int result = 0;
	
	if (len)
	{
		unsigned char *to_page = (unsigned char *)((unsigned int)to & 0xFFFFF000);	
		size_t page_size = 0;
		
		for(int i = 0, j = 0; i < len; ++i)
		{
			page_size = j * 4096;
			if ( &to[i] >= &to_page[page_size])
				++j;
		}

		result = mprotect(to_page, page_size, 7);	
		memcpy(to, from, len);
	}

	return result;
}
unsigned char hookdata[] =
{	
	0x01, 0xB4, 0x01, 0xB4, 
	0x01, 0x48, 0x01, 0x90, 
	0x01, 0xBD, 0x00, 0xBF, 
	0x00, 0x00, 0x00, 0x00
};

unsigned char* g_hookpos;
unsigned char* g_hookmax;

int log(const char *format, ...);

void copyhookcrap(unsigned char* to, unsigned char* form)
{
	unsigned char dest[16];

	memcpy(dest, hookdata, 16u);
	*(unsigned long *)&dest[12] = (unsigned long)(form)/* | 1*/;
	memcpy_protect((unsigned char*)((unsigned long)(to) & 0xFFFFFFFE), dest, 16);
}

void jmppatch(unsigned char* from, unsigned char* to)
{
  if (g_hookmax < g_hookpos + 16)
  {
    log("SPACE LIMIT REACHED");
	// exit(1);
  }
  
  ARMJMP(from, g_hookpos);
  copyhookcrap(g_hookpos, to);
  g_hookpos += 16;
}

void setuphook(unsigned char* a1, int a2)
{
  g_hookpos = a1;
  g_hookmax = a1 + a2;
}

void Test()
{
	void* pGTAso = dlopen("libGTASA.so", RTLD_NOW);
	unsigned char * v0 = (unsigned char *) 0xFFFFFFFF;
	
    if ( pGTAso )
      v0 = (unsigned char *)dlsym(pGTAso, "gzprintf") - 1;
	  
    setuphook(v0, 256);
}