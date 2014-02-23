#include <stdio.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

typedef union {
	struct __attribute__((packed)) {
		uint8_t command;
		uint8_t feature;
	} parts;
	uint16_t descriptor;
} ata_atapi_command_description;

ata_atapi_command_description x = (ata_atapi_command_description){.parts={0x02, 0x01}};


int main()
{
	printf("%x\n", x.parts.command);
	printf("%x\n", x.parts.feature);
	printf("%x\n", x.descriptor);
	return 0;
}
