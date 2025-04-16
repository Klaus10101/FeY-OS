#ifndef __INTERUPTS_H
#define __INTERUPTS_H	

#include "types.h"
#include "port.h"
#include "gdt.h"
    class InteruptManager
    {


     protected:
         struct GateDescriptor
         {
             uint16_t handlerAddressLowBits;
             uint16_t gdt_codeSegmentSelector;
             uint8_t reserved;
             uint8_t access;
             uint16_t handlerAddressHighBits;

         	
         }__attribute__((packed));
         static GateDescriptor interuptDescriptorTable[256];

         struct interuptDescriptorTablePointer
         {  
            uint16_t size;
         	uint32_t base;
         }__attribute__((packed));




         
         static void SetInteruptDescriptorTableEntry(
         	uint8_t interuptNumber,
         	uint16_t gdt_codeSegmentSelectoroffset,
         	void (*handler)(),
         	uint8_t DescriptorPrivilegeLevel,
         	uint8_t DescriptorType 
         );



         Port8Bitslow picMasterCommand;
         Port8Bitslow picMasterData;
         Port8Bitslow picSlaveCommand;
         Port8Bitslow picSlaveData;
         

     
   	 public:
         InteruptManager(GlobalDescriptorTable* gdt);
         ~InteruptManager();

         void Activate();
   	 
   	     static uint32_t handleInterupt(uint8_t interuptNumber, uint32_t esp);

         static void IgnoreInteruptRequest();
   	     static void HandleInteruptRequest0x00();
   	     static void HandleInteruptRequest0x01();
    };

#endif
  
