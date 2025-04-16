#include "interupts.h"


void print(char* str);



InteruptManager::GateDescriptor InteruptManager::interuptDescriptorTable[256];

void InteruptManager::SetInteruptDescriptorTableEntry(
    uint8_t interuptNumber,
    uint16_t codeSegmentSelectoroffset,
    void (*handler)(),
    uint8_t DescriptorPrivilegeLevel,
   	uint8_t DescriptorType )
{   
const uint8_t IDT_DESC_PRESENT = 0x80;   


 	interuptDescriptorTable[interuptNumber].handlerAddressLowBits = ((uint32_t)handler) & 0xFFFF;
 	interuptDescriptorTable[interuptNumber].handlerAddressHighBits = (((uint32_t)handler) >> 16) & 0xFFFF;
 	interuptDescriptorTable[interuptNumber].gdt_codeSegmentSelector = codeSegmentSelectoroffset;
 	interuptDescriptorTable[interuptNumber].access = IDT_DESC_PRESENT | DescriptorType| ((DescriptorPrivilegeLevel&3) << 5);
 	interuptDescriptorTable[interuptNumber].reserved = 0;
}

     

InteruptManager::InteruptManager(GlobalDescriptorTable* gdt)
:picMasterCommand(0x20),
picMasterData(0x21),
picSlaveCommand(0xA0),
picSlaveData(0xA1)

{
	uint16_t CodeSegment = gdt -> CodeSegmentSelector();
	const uint8_t IDT_INTERUPT_GATE = 0xE;

	for(uint16_t i =0; i < 256; i++)
	    SetInteruptDescriptorTableEntry(i, CodeSegment, &IgnoreInteruptRequest, 0, IDT_INTERUPT_GATE);
	    
	 SetInteruptDescriptorTableEntry(0x20, CodeSegment, &HandleInteruptRequest0x00, 0, IDT_INTERUPT_GATE);
	 SetInteruptDescriptorTableEntry(0x21, CodeSegment, &HandleInteruptRequest0x01, 0, IDT_INTERUPT_GATE);  



	 picMasterCommand.Write(0x11);
	 picSlaveCommand.Write(0x11);

	 picMasterData.Write(0x20);
	 picSlaveData.Write(0x28);
	 
	 picMasterData.Write(0x04);
	 picSlaveData.Write(0x02);

	 picMasterData.Write(0x01);
	 picSlaveData.Write(0x01);

	 picMasterData.Write(0x00);
	 picSlaveData.Write(0x00);

	 interuptDescriptorTablePointer idt;
	 idt.size = 256 * sizeof(GateDescriptor) - 1;
	 idt.base = (uint32_t)interuptDescriptorTable;
	 asm volatile("lidt %0" : : "m" (idt));
}
InteruptManager::~InteruptManager()
{
	
}

void InteruptManager::Activate()
{
	asm("sti");
}



uint32_t InteruptManager::handleInterupt(uint8_t interuptNumber, uint32_t esp)
{   
    print(" INTERUPT");
	return esp;
}
