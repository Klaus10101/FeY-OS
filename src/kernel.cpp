
#include "types.h"
#include "gdt.h"
#include "interupts.h"

void print(char* string){         

	static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x = 0, y = 0;
    
	for(int i = 0; string[i] != '\0'; i++){


	    switch(string[i]){ 

        case '\n':
            y++;
            x = 0;
            break;
	    default:
		    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xff00) | string[i];
		    x++;
		    break;


	    }
	    if (x >= 80){
	    	y++;
	    	x = 0;
	    }
	    if (y >= 25){
	    	for(y = 0; y < 25; y++)
	    	    for(x = 0; x <80; x++)
	    	        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xff00) | ' ';

	    	 y = 0;
	    	 x = 0;
	    }

	    
	}
}

typedef void(*constructor)();

extern "C" constructor* start_cons;
extern "C" constructor* end_cons;

extern "C" void callConstructors()
{
	for(constructor* i = start_cons; i != end_cons; i++)
	(*i)();
}
extern "C" void FeyKernelMain(const void* multiboot_structure, uint32_t){

     
     print("..............FeY-os kernel! written  in cpp :.........\n");
     print("             --------------------------------         \n");

     



    
     GlobalDescriptorTable gdt;
     InteruptManager interupts(&gdt);

     interupts.Activate();

     
     while(1);
    
     
     
}
