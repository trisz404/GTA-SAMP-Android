#include <dlfcn.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

unsigned long ARMCALL(unsigned long from, unsigned long to)
{
	unsigned long diff = to - ((from & 0xFFFFFFFE) + 4); //Size of the opcode is 4

	return (diff >> 12) & 0x7FF | 0xF000 | (((diff >> 1) & 0x7FF | 0xF800) << 16);
}

unsigned long ARMJMP(unsigned long from, unsigned long to)
{
	unsigned long diff = to - ((from & 0xFFFFFFFE) + 4); //Size of the opcode is 4

	return (diff >> 12) & 0x7FF | 0xF000 | (((diff >> 1) & 0x7FF | 0xB800) << 16);
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
		memcpy((void*)to, (void*)from, len);
	}

	return result;
}


