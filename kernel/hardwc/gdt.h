
#ifndef __GDT__H
#define __GDT__H

#include "types.h"

	class GlobalDescriptorTable{
	// global descriptor table

	public:
		class SegmentDescriptor{
			// segment decriptor
			private:
				uint16_t limit_lo;
				uint16_t base_lo;
				uint8_t base_hi;
				uint8_t type;
				uint8_t flags_limit_hi;
				uint8_t base_vhi;
			public:
				SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);
				uint32_t Base();
				uint32_t Limit();
				
		} __attribute__((packed));

		SegmentDescriptor nullSegmentSelector; //null segment selector
		SegmentDescriptor unusedSegmentSelector; // unusedsegment selector
		SegmentDescriptor codeSegmentSelector; //codesegment selector
		SegmentDescriptor dataSegmentSelector; //data segment selector


	public:
		GlobalDescriptorTable();
		~GlobalDescriptorTable();

		uint16_t CodeSegmentSelector();
		uint16_t DataSegmentSelector();
};



#endif
