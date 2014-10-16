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
unsigned char hookdata[] =
{	
	0x01, 0xB4, 0x01, 0xB4, 
	0x01, 0x48, 0x01, 0x90, 
	0x01, 0xBD, 0x00, 0xBF, 
	0x00, 0x00, 0x00, 0x00
};

int g_hookpos;
int g_hookmax;

int log(const char *format, ...);

int copyhookcrap(int to, int form)
{
  int limited_dataptr; // r6@1
  int limited_to; // r5@1
  int result; // r0@1
  char dest[16]; // [sp+4h] [bp-24h]@1


  limited_dataptr = to & 0xFFFFFFFE;

  limited_to = form | 1;
  memcpy(dest, hookdata, 16u);
  *(unsigned int *)&dest[12] = limited_to;
  result = memcpy_protect((unsigned char*)limited_dataptr, (unsigned char*)dest, 16);

  return result;
}

void callpatch(int from, int to)
{
  int _to; // r5@1

  _to = to;
  if (g_hookmax < g_hookpos + 16)
  {
    log("SPACE LIMIT REACHED");
  //  exit(1);
  }
  ARMJMP((unsigned int)from, (unsigned int)g_hookpos);
  copyhookcrap(g_hookpos, _to);
  g_hookpos += 16;
}



void setuphook(int a1, int a2)
{
  g_hookpos = a1;
  g_hookmax = a1 + a2;
}

void Test()
{
	int v0;
	void* pGTAso = dlopen("libGTASA.so", RTLD_NOW);
    if ( pGTAso )
      v0 = (int)((char *)dlsym(pGTAso, "gzprintf") - 1);
    else
      v0 = 0xFFFFFFFFu;
    setuphook(v0, 256);
}