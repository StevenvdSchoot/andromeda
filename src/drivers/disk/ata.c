/*
 *   Public ide header file.
 *   Copyright (C) 2011-2014  Michel Megens and Steven van der Schoot
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <drivers/ata.h>
#include <stdlib.h>
#include <sys/dev/pci.h>
#include <sys/disk/ide.h>
#include <drivers/kbd.h>


// All info from these documents:
//   - http://www.t10.org/t13/docs2004/d1532v1r4b-ATA-ATAPI-7.pdf
//   - http://www.t10.org/t13/docs2004/d1532v2r4b-ATA-ATAPI-7.pdf
//   - http://www.t10.org/t13/docs2004/d1532v3r4b-ATA-ATAPI-7.pdf

/*
typedef union {
	struct {
		uint8_t command;
		uint8_t feature;
	} parts;
	uint16_t descriptor;
} ata_atapi_command_description;

typedef enum __attribute__((packed)) {
	// This command pre-erases and conditions from 1 to 256 sectors as specified in the Sector Count register. This command
	// should be issued in advance of a CFA_ WRITE_SECTORS_WITHOUT_ERASE or a CFA_WRITE_MULTIPLE_WITHOUT_ERASE command to
	// increase the execution speed of the write operation.
	CFA_ERASE_SECTORS                = ((ata_atapi_command_description){.parts={0xc0, 0x00}}).descriptor,
	
	// This command provides an extended error code which identifies the cause of an error condition in more detail than is
	// available with Status and Error register values. The CFA REQUEST EXTENDED ERROR CODE command shall return an extended
	// error code if the previous command completed with an error or a no error detected extended error code if the previous command
	// completed without error.
	CFA_REQUEST_EXTENDED_ERROR_CODE  = ((ata_atapi_command_description){.parts={0x03, 0x00}}).descriptor,
	
	// This command provides information related to a specif ic sector. The data indicates the erased or not erased status of the
	// sector, and the number of erase and write cycles performed on thathttp://www.t10.org/t13/docs2004/d1532v2r4b-ATA-ATAPI-7.pdf sector. Devices may return zero in fields that do not apply
	// or that are not supported by the device.
	CFA_TRANSLATE_SECTOR             = ((ata_atapi_command_description){.parts={0x87, 0x00}}).descriptor,
	
	// TODO: Write documentation about all command beneath...
	CFA_WRITE_MULTIPLE_WITHOUT_ERASE = ((ata_atapi_command_description){.parts={0xCD, 0x00}}).descriptor,
	CFA_WRITE_SECTORS_WITHOUT_ERASE  = ((ata_atapi_command_description){.parts={0x38, 0x00}}).descriptor,
	CHECK_MEDIA_CARD_TYPE            = ((ata_atapi_command_description){.parts={0xD1, 0x00}}).descriptor,
	CHECK_POWER_MODE                 = ((ata_atapi_command_description){.parts={0xE5, 0x00}}).descriptor,
	CONFIGURE_STREAM                 = ((ata_atapi_command_description){.parts={0x51, 0x00}}).descriptor,
	DEVICE_CONFIGURATION_RESTORE     = ((ata_atapi_command_description){.parts={0xB1, 0xC0}}).descriptor,
	DEVICE_CONFIGURATION_FREEZE_LOCK = ((ata_atapi_command_description){.parts={0xB1, 0xC1}}).descriptor,
	DEVICE_CONFIGURATION_IDENTIFY    = ((ata_atapi_command_description){.parts={0xB1, 0xC2}}).descriptor,
	DEVICE_CONFIGURATION_SET         = ((ata_atapi_command_description){.parts={0xB1, 0xC3}}).descriptor,
	DEVICE_RESET                     = ((ata_atapi_command_description){.parts={0x08, 0x00}}).descriptor,
	OWNLOAD_MICROCOD                 = ((ata_atapi_command_description){.parts={0x92, 0x00}}).descriptor,
	EXECUTE_DEVICE_DIAGNOSTIC        = ((ata_atapi_command_description){.parts={0x90, 0x00}}).descriptor,
	FLUSH_CACHE                      = ((ata_atapi_command_description){.parts={0xE7, 0x00}}).descriptor,
	FLUSH_CACHE_EXT                  = ((ata_atapi_command_description){.parts={0xEA, 0x00}}).descriptor,
	GET_MEDIA_STATUS                 = ((ata_atapi_command_description){.parts={0xDA, 0x00}}).descriptor,
	IDENTIFY_DEVICE                  = ((ata_atapi_command_description){.parts={0xEC, 0x00}}).descriptor,
	IDENTIFY_PACKET_DEVICE           = ((ata_atapi_command_description){.parts={0xA1, 0x00}}).descriptor,
	IDLE                             = ((ata_atapi_command_description){.parts={0xE3, 0x00}}).descriptor,
	IDLE_IMMEDIATE                   = ((ata_atapi_command_description){.parts={0xE1, 0x00}}).descriptor,
	MEDIA_EJECT                      = ((ata_atapi_command_description){.parts={0xED, 0x00}}).descriptor,
	MEDIA_LOCK                       = ((ata_atapi_command_description){.parts={0xDE, 0x00}}).descriptor,
	MEDIA_UNLOCK                     = ((ata_atapi_command_description){.parts={0xDF, 0x00}}).descriptor,
	NOP                              = ((ata_atapi_command_description){.parts={0x00, 0x00}}).descriptor,
	PACKET                           = ((ata_atapi_command_description){.parts={0xA0, 0x00}}).descriptor,
	READ_BUFFER                      = ((ata_atapi_command_description){.parts={0xE4, 0x00}}).descriptor,
	READ_DMA                         = ((ata_atapi_command_description){.parts={0xC8, 0x00}}).descriptor,
	READ_DMA_EXT                     = ((ata_atapi_command_description){.parts={0x25, 0x00}}).descriptor,
	READ_DMA_QUEUED                  = ((ata_atapi_command_description){.parts={0xC7, 0x00}}).descriptor,
	READ_DMA_QUEUED_EXT              = ((ata_atapi_command_description){.parts={0x26, 0x00}}).descriptor,
	READ_LOG_EXT                     = ((ata_atapi_command_description){.parts={0x2F, 0x00}}).descriptor,
	READ_MULTIPLE                    = ((ata_atapi_command_description){.parts={0xC4, 0x00}}).descriptor,
	READ_MULTIPLE_EXT                = ((ata_atapi_command_description){.parts={0x29, 0x00}}).descriptor,
	READ_NATIVE_MAX_ADDRESS          = ((ata_atapi_command_description){.parts={0xF8, 0x00}}).descriptor,
	READ_NATIVE_MAX_ADDRESS_EXT      = ((ata_atapi_command_description){.parts={0x27, 0x00}}).descriptor,
	READ_SECTORS                     = ((ata_atapi_command_description){.parts={0x20, 0x00}}).descriptor,
	READ_SECTORS_EXT                 = ((ata_atapi_command_description){.parts={0x24, 0x00}}).descriptor,
	READ_STREAM_DMA_EXT              = ((ata_atapi_command_description){.parts={0x2A, 0x00}}).descriptor,
	READ_STREAM_EXT                  = ((ata_atapi_command_description){.parts={0x2B, 0x00}}).descriptor,
	READ_VERIFY_SECTORS              = ((ata_atapi_command_description){.parts={0x40, 0x00}}).descriptor,
	READ_VERIFY_SECTORS_EXT          = ((ata_atapi_command_description){.parts={0x42, 0x00}}).descriptor,
	SECURITY_DISABLE_PASSWORD        = ((ata_atapi_command_description){.parts={0xF6, 0x00}}).descriptor,
	SECURITY_ERASE_PREPARE           = ((ata_atapi_command_description){.parts={0xF3, 0x00}}).descriptor,
	SECURITY_ERASE_UNIT              = ((ata_atapi_command_description){.parts={0xF4, 0x00}}).descriptor,
	SECURITY_FREEZE_LOCK             = ((ata_atapi_command_description){.parts={0xF5, 0x00}}).descriptor,
	SECURITY_SET_PASSWORD            = ((ata_atapi_command_description){.parts={0xF1, 0x00}}).descriptor,
	SECURITY_UNLOCK                  = ((ata_atapi_command_description){.parts={0xF2, 0x00}}).descriptor,
	SERVICE                          = ((ata_atapi_command_description){.parts={0xA2, 0x00}}).descriptor,
	SET_FEATURES                     = ((ata_atapi_command_description){.parts={0xEF, 0x00}}).descriptor,
	SET_MAX_SET_PASSWORD             = ((ata_atapi_command_description){.parts={0xF9, 0x01}}).descriptor,
	SET_MAX_LOCK                     = ((ata_atapi_command_description){.parts={0xF9, 0x02}}).descriptor,
	SET_MAX_UNLOCK                   = ((ata_atapi_command_description){.parts={0xF9, 0x03}}).descriptor,
	SET_MAX_FREEZE_LOCK              = ((ata_atapi_command_description){.parts={0xF9, 0x04}}).descriptor,
	SET_MAX_ADDRESS_EXT              = ((ata_atapi_command_description){.parts={0x37, 0x00}}).descriptor,
	SET_MULTIPLE_MODE                = ((ata_atapi_command_description){.parts={0xC6, 0x00}}).descriptor,
	SLEEP                            = ((ata_atapi_command_description){.parts={0xE6, 0x00}}).descriptor,
	SMART_READ_DATA                  = ((ata_atapi_command_description){.parts={0xB0, 0xD0}}).descriptor,
	SMART_ENABLE_DISABLE_ATTRIBUTE_AUTOSAVE = ((ata_atapi_command_description){.parts={0xB0, 0xD2}}).descriptor,
	SMART_EXECUTE_OFF_ILE_IMMEDIATE  = ((ata_atapi_command_description){.parts={0xB0, 0xD4}}).descriptor,
	SMART_READ_LOG                   = ((ata_atapi_command_description){.parts={0xB0, 0xD5}}).descriptor,
	SMART_WRITE_LOG                  = ((ata_atapi_command_description){.parts={0xB0, 0xD6}}).descriptor,
	SMART_ENABLE_OPERATIONS          = ((ata_atapi_command_description){.parts={0xB0, 0xD8}}).descriptor,
	SMART_DISABLE_OPERATIONS         = ((ata_atapi_command_description){.parts={0xB0, 0xD9}}).descriptor,
	SMART_RETURN_STATUS              = ((ata_atapi_command_description){.parts={0xB0, 0xDA}}).descriptor,
	SMART_VENDOR_SPECIFIC_e0         = ((ata_atapi_command_description){.parts={0xB0, 0xE0}}).descriptor,
	SMART_VENDOR_SPECIFIC_e1         = ((ata_atapi_command_description){.parts={0xB0, 0xE1}}).descriptor,
	SMART_VENDOR_SPECIFIC_e2         = ((ata_atapi_command_description){.parts={0xB0, 0xE2}}).descriptor,
	SMART_VENDOR_SPECIFIC_e3         = ((ata_atapi_command_description){.parts={0xB0, 0xE3}}).descriptor,
	SMART_VENDOR_SPECIFIC_e4         = ((ata_atapi_command_description){.parts={0xB0, 0xE4}}).descriptor,
	SMART_VENDOR_SPECIFIC_e5         = ((ata_atapi_command_description){.parts={0xB0, 0xE5}}).descriptor,
	SMART_VENDOR_SPECIFIC_e6         = ((ata_atapi_command_description){.parts={0xB0, 0xE6}}).descriptor,
	SMART_VENDOR_SPECIFIC_e7         = ((ata_atapi_command_description){.parts={0xB0, 0xE7}}).descriptor,
	SMART_VENDOR_SPECIFIC_e8         = ((ata_atapi_command_description){.parts={0xB0, 0xE8}}).descriptor,
	SMART_VENDOR_SPECIFIC_e9         = ((ata_atapi_command_description){.parts={0xB0, 0xE9}}).descriptor,
	SMART_VENDOR_SPECIFIC_ea         = ((ata_atapi_command_description){.parts={0xB0, 0xEA}}).descriptor,
	SMART_VENDOR_SPECIFIC_eb         = ((ata_atapi_command_description){.parts={0xB0, 0xEB}}).descriptor,
	SMART_VENDOR_SPECIFIC_ec         = ((ata_atapi_command_description){.parts={0xB0, 0xEC}}).descriptor,
	SMART_VENDOR_SPECIFIC_ed         = ((ata_atapi_command_description){.parts={0xB0, 0xED}}).descriptor,
	SMART_VENDOR_SPECIFIC_ee         = ((ata_atapi_command_description){.parts={0xB0, 0xEE}}).descriptor,
	SMART_VENDOR_SPECIFIC_ef         = ((ata_atapi_command_description){.parts={0xB0, 0xEF}}).descriptor,
	SMART_VENDOR_SPECIFIC_f0         = ((ata_atapi_command_description){.parts={0xB0, 0xF0}}).descriptor,
	SMART_VENDOR_SPECIFIC_f1         = ((ata_atapi_command_description){.parts={0xB0, 0xF1}}).descriptor,
	SMART_VENDOR_SPECIFIC_f2         = ((ata_atapi_command_description){.parts={0xB0, 0xF2}}).descriptor,
	SMART_VENDOR_SPECIFIC_f3         = ((ata_atapi_command_description){.parts={0xB0, 0xF3}}).descriptor,
	SMART_VENDOR_SPECIFIC_f4         = ((ata_atapi_command_description){.parts={0xB0, 0xF4}}).descriptor,
	SMART_VENDOR_SPECIFIC_f5         = ((ata_atapi_command_description){.parts={0xB0, 0xF5}}).descriptor,
	SMART_VENDOR_SPECIFIC_f6         = ((ata_atapi_command_description){.parts={0xB0, 0xF6}}).descriptor,
	SMART_VENDOR_SPECIFIC_f7         = ((ata_atapi_command_description){.parts={0xB0, 0xF7}}).descriptor,
	SMART_VENDOR_SPECIFIC_f8         = ((ata_atapi_command_description){.parts={0xB0, 0xF8}}).descriptor,
	SMART_VENDOR_SPECIFIC_f9         = ((ata_atapi_command_description){.parts={0xB0, 0xF9}}).descriptor,
	SMART_VENDOR_SPECIFIC_fa         = ((ata_atapi_command_description){.parts={0xB0, 0xFA}}).descriptor,
	SMART_VENDOR_SPECIFIC_fb         = ((ata_atapi_command_description){.parts={0xB0, 0xFB}}).descriptor,
	SMART_VENDOR_SPECIFIC_fc         = ((ata_atapi_command_description){.parts={0xB0, 0xFC}}).descriptor,
	SMART_VENDOR_SPECIFIC_fd         = ((ata_atapi_command_description){.parts={0xB0, 0xFD}}).descriptor,
	SMART_VENDOR_SPECIFIC_fe         = ((ata_atapi_command_description){.parts={0xB0, 0xFE}}).descriptor,
	SMART_VENDOR_SPECIFIC_ff         = ((ata_atapi_command_description){.parts={0xB0, 0xFF}}).descriptor,
	STANDBY                          = ((ata_atapi_command_description){.parts={0xE2, 0x00}}).descriptor,
	STANDBY_IMMEDIATE                = ((ata_atapi_command_description){.parts={0xE0, 0x00}}).descriptor,
	WRITE_BUFFER                     = ((ata_atapi_command_description){.parts={0xE8, 0x00}}).descriptor,
	WRITE_DMA                        = ((ata_atapi_command_description){.parts={0xCA, 0x00}}).descriptor,
	WRITE_DMA_EXT                    = ((ata_atapi_command_description){.parts={0x35, 0x00}}).descriptor,
	WRITE_DMA_FUA_EXT                = ((ata_atapi_command_description){.parts={0x3D, 0x00}}).descriptor,
	WRITE_DMA_QUEUED                 = ((ata_atapi_command_description){.parts={0xCC, 0x00}}).descriptor,
	WRITE_DMA_QUEUED_EXT             = ((ata_atapi_command_description){.parts={0x36, 0x00}}).descriptor,
	WRITE_DMA_QUEUED_FUA_EXT         = ((ata_atapi_command_description){.parts={0x3E, 0x00}}).descriptor,
	WRITE_LOG_EXT                    = ((ata_atapi_command_description){.parts={0x3F, 0x00}}).descriptor,
	WRITE_MULTIPLE                   = ((ata_atapi_command_description){.parts={0xC5, 0x00}}).descriptor,
	WRITE_MULTIPLE_EXT               = ((ata_atapi_command_description){.parts={0x39, 0x00}}).descriptor,
	WRITE_MULTIPLE_FUA_EXT           = ((ata_atapi_command_description){.parts={0xCE, 0x00}}).descriptor,
	WRITE_SECTORS                    = ((ata_atapi_command_description){.parts={0x30, 0x00}}).descriptor,
	WRITE_SECTORS_EXT                = ((ata_atapi_command_description){.parts={0x34, 0x00}}).descriptor,
	WRITE_STREAM_DMA_EXT             = ((ata_atapi_command_description){.parts={0x3A, 0x00}}).descriptor,
	WRITE_STREAM_EXT                 = ((ata_atapi_command_description){.parts={0x3B, 0x00}}).descriptor,

} ata_atapi_command;


typedef enum __attribute__((packed)) {
	NO_ERROR = 0x00,
	SELF_TEST_PASSED = 0x01,
	WRITE_ERASE_FAILED = 0x03,
	SELF_TEST_OR_DIAGNOSTIC_FAILED = 0x05,
	MISCELLANEOUS_ERROR = 0x09,
	VENDOR_SPECIFIC_0 = 0x0B,
	CORRUPTED_MEDIA_FORMAT_0 = 0x0C,
	VENDOR_SPECIFIC_1 = 0x0D,
	VENDOR_SPECIFIC_2 = 0x0E,
	VENDOR_SPECIFIC_3 = 0x0F,
	ID_NOT_FOUND_OR_ID_ERROR = 0x10,
	UNCORRECTABLE_ECC_ERROR = 0x18,
	VENDOR_SPECIFIC_4 = 0x1D,
	VENDOR_SPECIFIC_5 = 0x1E,
	DATA_TRANSFER_ERROR_OR_COMMAND_ABORTED = 0x1F,
	INVALID_COMMAND = 0x20,
	INVALID_ADDRESS = 0x21,
	VENDOR_SPECIFIC_6 = 0x22,
	VENDOR_SPECIFIC_7 = 0x23,
	WRITE_PROTEC_VIOLATION = 0x27,
	ADDRESS_OVERFLOW = 0x2F,
	SELF_TEST_OR_DIAGNOSTIC_FAILED_0 = 0x30,
	SELF_TEST_OR_DIAGNOSTIC_FAILED_1 = 0x31,
	SELF_TEST_OR_DIAGNOSTIC_FAILED_2 = 0x32,
	SELF_TEST_OR_DIAGNOSTIC_FAILED_3 = 0x33,
	SELF_TEST_OR_DIAGNOSTIC_FAILED_4 = 0x34,
	SUPPLY_OR_GENERATED_VOLTAGE_OUT_OF_TOLERANCE_0 = 0x35,
	SUPPLY_OR_GENERATED_VOLTAGE_OUT_OF_TOLERANCE_1 = 0x36,
	SELF_TEST_OR_DIAGNOSTIC_FAILED_5 = 0x37,
	SELF_TEST_OR_DIAGNOSTIC_FAILED_6 = 0x3E,
	CORRUPTED_MEDIA_FORMAT_1 = 0x38,
	VENDOR_SPECIFIC_8 = 0x39,
	SPARE_SECTOR_EXHAUSTED = 0x3A,
	CORRUPTED_MEDIA_FORMAT_2 = 0x3B,
	CORRUPTED_MEDIA_FORMAT_3 = 0x3C,
	CORRUPTED_MEDIA_FORMAT_4 = 0x3F,
	VENDOR_SPECIFIC_9 = 0x3D
} ata_atapi_extended_error_codes;


// For command: CFA_TRANSLATE_SECTOR
typedef struct __attribute__((packed)) {
	uint8_t Obsolete[4];
	uint8_t LBA[3];
	uint8_t reserved_0[11];
	uint8_t erase; // 0xFF = erased, 0 = not erased
	uint8_t reserved_1[3];
	uint8_t writeCycleCount[3];
	uint8_t reserved_2[228];
} ata_atapi_data_translate_sector_information;

typedef union __attribute__((packed)) {
	uint8_t sector[256]; // TODO: Reconsider this length. Actual sector size is variable...
	ata_atapi_data_translate_sector_information cfa_translate_sector;
} ata_atapi_data;

	// Format: HOB, r{4}, SRST, nIEN, 0
	// HOB:  1-bit high order byte (1 if 48-bit sectors should be used, prohibited when PACKET Command feature is implemented).
	//       Cleared to 0 on every wridevice_selectte to command block register.
	// r{4}: 4-bit reserved
	// SRST: 1-bit host software reset bit (http://www.t10.org/t13/docs2004/d1532v2r4b-ATA-ATAPI-7.pdf#page=96&zoom=auto,94,723)
	// nIEN: 1-bit enable bit for the device assertion of INTRQ to the host. When the nIEN bit is cleared to zero, and the
	//       device is selected, INTRQ shall be enabled through a tri-state buffer and shall be asserted or negated by the device
	//       as appropriate. When the nIEN bit is set to one, or the device is not selected, the device shall release the INTRQ signal. 


typedef struct __attribute__((packed)) {
	// CFA_ERASE_SECTORS:
	//   type ata_atapi_data.sector
	// CFA_REQUEST_EXTENDED_ERROR_CODE:
	//   na
	// CFA_TRANSLATE_SECTOR:
	//   type ata_atapi_data.cfa_translate_sector
	uint16_t data;
	
	uint8_t features;
	
	// command depended (see: http://www.t10.org/t13/docs2004/d1532v1r4b-ATA-ATAPI-7.pdf#page=88&zoom=auto,71,723)
	// CFA_ERASE_SECTORS:
	//   number of sectors to be erased (wherevalue 0 means 256 sectors!)
	// CFA_REQUEST_EXTENDED_ERROR_CODE:
	//   na
	// CFA_TRANSLATE_SECTOR:
	//   na
	uint8_t sector_count;
	
	// command depended (see: http://www.t10.org/t13/docs2004/d1532v1r4b-ATA-ATAPI-7.pdf#page=88&zoom=auto,71,723)
	// CFA_ERASE_SECTORS:
	//   LBA bit 7:0
	// CFA_REQUEST_EXTENDED_ERROR_CODE:
	//   na
	// CFA_TRANSLATE_SECTOR:
	//   LBA bit 7:0
	uint8_t LBA_Low;
	
	// command depended (see: http://www.t10.org/t13/docs2004/d1532v1r4b-ATA-ATAPI-7.pdf#page=88&zoom=auto,71,723)
	// CFA_ERASE_SECTORS:
	//   LBA bit 15:8
	// CFA_REQUEST_EXTENDED_ERROR_CODE:
	//   na
	// CFA_TRANSLATE_SECTOR:
	//   LBA bit 15:8
	uint8_t byte_count_low;
	
	// command depended (see: http://www.t10.org/t13/docs2004/d1532v1r4b-ATA-ATAPI-7.pdf#page=88&zoom=auto,71,723)
	// CFA_ERASE_SECTORS:
	//   LBA bit 23:16
	// CFA_REQUEST_EXTENDED_ERROR_CODE:
	//   na
	// CFA_TRANSLATE_SECTOR:
	//   LBA bit 23:16
	uint8_t byte_count_high;
	
	// command depended (see: http://www.t10.org/t13/docs2004/d1532v1r4b-ATA-ATAPI-7.pdf#page=88&zoom=auto,71,723)
	// CFA_ERASE_SECTORS:
	//   obs(1): ...
	//   LBA(1): 1 indicates address is LBA format.
	//   obs(1): ...
	//   DEV(1): ...
	//   LBA(4): bit 27:24
	// CFA_REQUEST_EXTENDED_ERROR_CODE:
	//   obs(1): ...
	//   na (1)
	//   obs(1): ...
	//   DEV(1): ...
	//   na (4)
	// CFA_TRANSLATE_SECTOR:
	//   obs(1): ...
	//   LBA(1): 1 indicates address is LBA format.
	//   obs(1): ...
	//   DEV(1): ...
	//   LBA(4): bit 27:24
	uint8_t device_select;
	
	ata_atapi_command command;
} ata_atapi_command_content_input;

typedef struct __attribute__((packed)) {
	// CFA_ERASE_SECTORS:
	//   type ata_atapi_data.sector
	// CFA_REQUEST_EXTENDED_ERROR_CODE:
	//   na
	// CFA_TRANSLATE_SECTOR:
	//   type ata_atapi_data.cfa_translate_sector
	uint16_t data;
	
	// command depended (see: http://www.t10.org/t13/docs2004/d1532v1r4b-ATA-ATAPI-7.pdf#page=88&zoom=auto,71,723)
	//Note that bit 2 is defined to always indicate ABRT (abort).
	//
	// CFA_ERASE_SECTORS:
	//   Reserved(3): 
	//   IDNF(1)    :  address outside of the range of user-accessible addresses is requested and command aborted is not returned
	//   Reserved(1): 
	//   ABRT(1)    :  address outside of the range of user-accessible addresses is requested and IDNF is not set to one
	//   Reserved(1): 
	//   MED(1)     :  a media error is detected
	// CFA_REQUEST_EXTENDED_ERROR_CODE:
	//   extended error code: type ata_atapi_extended_error_codes
	// CFA_REQUEST_EXTENDED_ERROR_CODE ERROR:
	//   bit 2: ABRT (1 if command not supported, be set to one if the device is not able to complete the action requested by the command)
	// CFA_TRANSLATE_SECTOR:
	//   na
	// CFA_TRANSLATE_SECTOR ERROR:
	//   bit 2: ABRT (1 if command not supported, be set to one if the device is not able to complete the action requested by the command)
	uint8_t error;
	
	// command depended (see: http://www.t10.org/t13/docs2004/d1532v1r4b-ATA-ATAPI-7.pdf#page=88&zoom=auto,71,723)
	// CFA_ERASE_SECTORS:
	//   number of sectors to be erased (wherevalue 0 means 256 sectors!)
	// CFA_REQUEST_EXTENDED_ERROR_CODE:
	//   Optional vendor specific additional information
	// CFA_REQUEST_EXTENDED_ERROR_CODE ERROR:
	//   na
	// CFA_TRANSLATE_SECTOR:
	//   na
	uint8_t interrupt_reason;
	
	// command depended (see: http://www.t10.org/t13/docs2004/d1532v1r4b-ATA-ATAPI-7.pdf#page=88&zoom=auto,71,723)
	// CFA_ERASE_SECTORS:
	//   LBA bit 7:0
	// CFA_ERASE_SECTORS ERROR:
	//   address of first unrecoverable error bits 7:0
	// CFA_REQUEST_EXTENDED_ERROR_CODE:
	//   Optional vendor specific additional information
	// CFA_REQUEST_EXTENDED_ERROR_CODE ERROR:
	//   na
	// CFA_TRANSLATE_SECTOR:
	//   na
	uint8_t LBA_Low;
	
	// command depended (see: http://www.t10.org/t13/docs2004/d1532v1r4b-ATA-ATAPI-7.pdf#page=88&zoom=auto,71,723)
	// CFA_ERASE_SECTORS:
	//   LBA bit 15:8
	// CFA_ERASE_SECTORS ERROR:
	//   address of first unrecoverable error bits 15:8
	// CFA_REQUEST_EXTENDED_ERROR_CODE:
	//   Optional vendor specific additional information
	// CFA_REQUEST_EXTENDED_ERROR_CODE ERROR:
	//   na
	// CFA_TRANSLATE_SECTOR:
	//   na
	uint8_t byte_count_low;
	
	// command depended (see: http://www.t10.org/t13/docs2004/d1532v1r4b-ATA-ATAPI-7.pdf#page=88&zoom=auto,71,723)
	// CFA_ERASE_SECTORS:
	//   LBA bit 23:16
	// CFA_ERASE_SECTORS ERROR:
	//   address of first unrecoverable error bits 23:16
	// CFA_REQUEST_EXTENDED_ERROR_CODE:
	//   Optional vendor specific additional information
	// CFA_REQUEST_EXTENDED_ERROR_CODE ERROR:
	//   na
	// CFA_TRANSLATE_SECTOR:
	//   na
	uint8_t byte_count_high;
	
	// command depended (see: http://www.t10.org/t13/docs2004/d1532v1r4b-ATA-ATAPI-7.pdf#page=88&zoom=auto,71,723)
	// CFA_ERASE_SECTORS:
	//   obs(1): ...
	//   LBA(1): 1 indicates address is LBA format.
	//   obs(1): ...
	//   DEV(1): ...
	//   LBA(4): bit 27:24
	// CFA_ERASE_SECTORS ERROR:
	//   obs(1): ...
	//   na(1)
	//   obs(1): ...
	//   DEV(1): ...
	//   LBA(4): address of first unrecoverable error bits 27:24
	// CFA_REQUEST_EXTENDED_ERROR_CODE:
	//   obs(1): ...
	//   na (1)
	//   obs(1): ...
	//   DEV(1): ...
	//   vs (4): Optional vendor specific additional information
	// CFA_REQUEST_EXTENDED_ERROR_CODE ERROR:
	//   obs(1): ...
	//   na (1)
	//   obs(1): ...
	//   DEV(1): ...
	//   na (4)
	// CFA_TRANSLATE_SECTOR:
	//   obs(1): ...
	//   na (1)
	//   obs(1): ...
	//   DEV(1): ...
	//   na (4)
	uint8_t device_select;
	
	// base:
	//   BSY(1)          : 1 indicates the device being busy
	//   DRDY(1)         : ...
	//   DF/SE(1)        : Device Fault / Stream Error, a fault not described by error register
	//   CMD Specific(1) : 
	//   DRQ(1)          : Data request, 
	//   Obsolete(2)     : 
	//   ERR/CHK(1)      : 
	// 
	// CFA_ERASE_SECTORS:
	//   BSY(1)          : 1 indicates the device being busy
	//   DRDY(1)         : ...
	//   DF(1)           : Device Fault / Stream Error, a fault not described by error register
	//   na (4)
	//   ERR/CHK(1)      : 
	// CFA_ERASE_SECTORS ERROR:
	//   BSY(1)          : cleared to 0, indicating command completion
	//   DRDY(1)         : is set to 1
	//   DF(1)           : 1 if Device Fault occurred
	//   na (4)
	//   ERR(1)          : 1 if eror register bit is one
	// CFA_REQUEST_EXTENDED_ERROR_CODE:
	//   BSY(1)          : cleared to 0, indicating command completion
	//   DRDY(1)         : is set to 1
	//   na (5)
	//   ERR(1)          : cleared to 0
	// CFA_REQUEST_EXTENDED_ERROR_CODE ERROR:
	//   BSY(1)          : cleared to 0, indicating command completion
	//   DRDY(1)         : is set to 1
	//   DF(1)           : 1 if Device Fault occurred
	//   na (4)
	//   ERR(1)          : 1 if eror register bit is one
	// CFA_TRANSLATE_SECTOR:
	//   BSY(1)          : cleared to 0, indicating command completion
	//   DRDY(1)         : is set to 1
	//   na (5)
	//   ERR(1)          : cleared to 0
	// CFA_TRANSLATE_SECTOR ERROR:
	//   BSY(1)          : cleared to 0, indicating command completion
	//   DRDY(1)         : is set to 1
	//   DF(1)           : 1 if Device Fault occurred
	//   na (4)
	//   ERR(1)          : 1 if eror register bit is one
	uint8_t status;
} ata_atapi_command_content_output;

typedef union {
	ata_atapi_command_content_output output;
	ata_atapi_command_content_input input;
	unsigned char raw[sizeof(ata_atapi_command_content_output)];
} ata_atapi_command_content;

int
ata_readSector(const uint32_t bus, const uint32_t drive, const uint32_t lba, uint8_t* const buffer)
{
	const union {
		uint32_t uint;
		uint8_t uchar[sizeof(uint32_t)];
	} LBA = lba;
	
	// Set the LBA
	outb(bus + 2, LBA.uchar[3]);
	outb(bus + 3, LBA.uchar[2]);
	outb(bus + 4, LBA.uchar[1]);
	outb(bus + 5, LBA.uchar[0]);
	
	// Read with retry
	outb(bus + 7, 0x20);
}

static inline void
ata_atapi_setCommandData_command(ata_atapi_command_content_input* data, const ata_atapi_command command)
{
	const ata_atapi_command_description c = (ata_atapi_command_description){.descriptor=command};
	data->command = c.parts.command;
	data->features = c.parts.feature;
}

static inline void
ata_atapi_setCommandData_LBA(ata_atapi_command_content_input* data, const unsigned int LBA)
{
	data->LBA_Low = (LBA >>  0) & 0xff;
	data->byte_count_low = (LBA >>  8) & 0xff;
	data->byte_count_high = (LBA >> 16) & 0xff;
	data->device_select = (data->device_select & 0xf0) | ( (LBA >> 24) & 0x0f ) | (1 << 6);
}

static inline void
ata_atapi_setCommandData_sectorCount(ata_atapi_command_content_input* data, const unsigned char sectors)
{
	data->sector_count = sectors;
}

static void
ata_atapi_executeCommand(const uint32_t bus, ata_atapi_command_content_input* data)
{
	int i = 0;
	for(; i < sizeof(ata_atapi_command_content); i++)
	{
		outb(bus + i, ((ata_atapi_command_content*)data)->raw[i] );
	}
}

static void
ata_atapi_writeBytes(const uint32_t bus, short* buf, size_t size)
{
	while(size)
	{
		*buf = ins(bus);
		buf++;
		size--;
	}
}
*/

typedef enum
{
	CB_READ_DATA  = 0x000,   // data reg         in/out pio_base_addr1+0
	CB_READ_ERR   = 0x001,   // error            in     pio_base_addr1+1
	CB_READ_SC    = 0x002,   // sector count     in/out pio_base_addr1+2
	CB_READ_SN    = 0x003,   // sector number    in/out pio_base_addr1+3
	CB_READ_CL    = 0x004,   // cylinder low     in/out pio_base_addr1+4
	CB_READ_CH    = 0x005,   // cylinder high    in/out pio_base_addr1+5
	CB_READ_DH    = 0x006,   // device head      in/out pio_base_addr1+6
	CB_READ_STAT  = 0x007,   // primary status   in     pio_base_addr1+7
	CB_READ_ASTAT = 0x206,   // alternate status in     pio_base_addr2+6
	CB_READ_DA    = 0x207,   // device address   in     pio_base_addr2+7
} ol_ata_pio_readbytes;

typedef enum
{
	CB_WRITE_DATA  = 0x000,   // data reg         in/out pio_base_addr1+0
	CB_WRITE_FR    = 0x001,   // feature reg         out pio_base_addr1+1
	CB_WRITE_SC    = 0x002,   // sector count     in/out pio_base_addr1+2
	CB_WRITE_SN    = 0x003,   // sector number    in/out pio_base_addr1+3
	CB_WRITE_CL    = 0x004,   // cylinder low     in/out pio_base_addr1+4
	CB_WRITE_CH    = 0x005,   // cylinder high    in/out pio_base_addr1+5
	CB_WRITE_DH    = 0x006,   // device head      in/out pio_base_addr1+6
	CB_WRITE_CMD   = 0x007,   // command             out pio_base_addr1+7
	CB_WRITE_DC    = 0x206,   // device control      out pio_base_addr2+6
} ol_ata_pio_writebytes;

static inline uint8_t
readPIOByte(const uint32_t base, const ol_ata_pio_writebytes addr)
{
	return inb(base + addr);
}

static inline void
writePIOByte(const uint32_t base, const ol_ata_pio_writebytes addr, const uint8_t data)
{
	return outb(base + addr, data);
}

static inline void
readPIOData(const uint32_t base, uint8_t* addr, const uint32_t count)
{
	return insw(base, addr, count);
}

static inline void
writePIOData(const uint32_t base, const uint8_t* addr, const uint32_t count)
{
	return outsw(base, addr, count);
}

static void
writeLBA(const uint32_t base, const uint64_t LBA, uint8_t flag)
{
	writePIOByte(base, CB_WRITE_SN,   (LBA >>  0) & 0xff                );
	writePIOByte(base, CB_WRITE_CL,   (LBA >>  8) & 0xff                );
	writePIOByte(base, CB_WRITE_CH,   (LBA >> 16) & 0xff                );
	writePIOByte(base, CB_WRITE_DH, ( (LBA >> 24) & 0x0f) | (flag << 4) );
}

void
ol_ata_softreset(const uint32_t base)
{
	writePIOByte(base, CB_WRITE_DC, (1 << 2) );
	writePIOByte(base, CB_WRITE_DC, 0);
}

ol_ata_type
ol_ata_detect_drive_type(const uint32_t base, const boolean slave)
{
	writePIOByte(base, CB_WRITE_FR, 4);
	writePIOByte(base, CB_WRITE_DH, 0xA0 | (slave << 4) );
	
	readPIOByte(base, CB_WRITE_DC);
	readPIOByte(base, CB_WRITE_DC);
	readPIOByte(base, CB_WRITE_DC);
	readPIOByte(base, CB_WRITE_DC);
	
	uint8_t cl = readPIOByte(base, CB_WRITE_CL);
	uint8_t ch = readPIOByte(base, CB_WRITE_CH);
	
	if(cl == 0x14 && ch == 0xEB)
		return ATA_TYPE_PATAPI;
	if(cl == 0x69 && ch == 0x96)
		return ATA_TYPE_SATAPI;
	if(cl == 0 && ch == 0)
		return ATA_TYPE_PATA;
	if(cl == 0x3c && ch == 0xc3)
		return ATA_TYPE_SATA;
	
	return ATA_TYPE_UNKNOWN;
}

static void
waitDeviceNotBusy(const uint32_t base)
{
	while( readPIOByte(base, CB_READ_STAT) & (1 << 7) ) // Wait until bit 7 (busy bit) of status reg is low
		;
}

static void
waitDeviceReady(const uint32_t base)
{
	while( !(readPIOByte(base, CB_READ_STAT) & (1 << 6)) ) // Wait until bit 7 (busy bit) of status reg is low
		;
}

static void
waitDeviceData(const uint32_t base)
{
	while( !(readPIOByte(base, CB_READ_STAT) & (1 << 3)) ) // Wait until bit 7 (busy bit) of status reg is low
		;
}

static uint8_t
waitDeviceStatus(const uint32_t base)
{
	uint8_t status;
	int i;
	
	for(i = 0; i < 4; i++)
	{
		status = readPIOByte(base, CB_READ_STAT);
		
		if( status  & (1 << 7) ) // Keep waiting while busy
			continue;
		
		if( status  & (1 << 3) ) // Return when not busy and data ready
			return ( status  & ((1 << 5) | (1 << 0)) ) ? ( (status >> 3) & 0x03 ) : 0;
	}
	
	do
	{
		status = readPIOByte(base, CB_READ_STAT);
		
		if( status  & (1 << 7) ) // Keep waiting while busy
			continue;
		
		if( status  & ((1 << 5) | (1 << 0)) ) // Return when not busy and error or df
			return 0xf8 | ( (status >> 3) & 0x03 );
		
	} while ( 0 );
	
	return 0; // Return when not busy and no error or df
}

static void
prepareDevice(const uint32_t base)
{
	waitDeviceNotBusy(base);
	// __asm__ volatile("cli");
	waitDeviceReady(base);
}

static inline void
puthex_part(uint8_t num)
{
	if(num <= 9)
		putc('0' + num );
	else
		putc( ('a' - 10) + num );
}

static void
puthex(uint8_t num)
{
	puthex_part(num >> 4);
	puthex_part(num & 0x0f);
}

static void
puthex_int(uint32_t num)
{
	puthex_part((num >> 28) & 0x0f);
	puthex_part((num >> 24) & 0x0f);
	puthex_part((num >> 20) & 0x0f);
	puthex_part((num >> 16) & 0x0f);
	puthex_part((num >> 12) & 0x0f);
	puthex_part((num >>  8) & 0x0f);
	puthex_part((num >>  4) & 0x0f);
	puthex_part( num        & 0x0f);
}

static void
printBuf(const void* printbuf, const unsigned int offset, const unsigned int count)
{
	const char* buf = printbuf;
	unsigned int i = offset;
	while(i < count)
	{
		puthex_int(i);
		putc(' ');
		puthex(buf[i]);
		while( (i % 16) != 15 )
		{
			i++;
			if(!(i % 4))
				putc(' ');
			putc(' ');
			puthex(buf[i]);
		}
		putc('\n');
		i++;
	}
}

void
ol_ata_get_device_info(uint32_t base, ol_ata_data_identify_device* device)
{
	prepareDevice(base);
	writePIOByte(base, CB_WRITE_CMD, 0xEC);
	waitDeviceData(base);
	readPIOData(base, device, 256);
	// __asm__ volatile("sti");
}

void
ol_ata_printDeviceInfo(const ol_ata_data_identify_device* device)
{
#define PRINTINFO_BOOL2STRING(b) ( (b) ? "true" : "false" )
#define PRINTINFO_NUM2UINT(n) ( (uint32_t) n )
#define PRINTINFO_STRING2PRINTABLE(s) ({ char* str = ({ char* str[sizeof(s) + 1] __attribute__ ((aligned(8), packed)); str; }); memcpy(str, s, sizeof(s)); str[sizeof(s)] = '\0'; str; })
	
	puts("About to print lotsa info about your first hard drive...\n");
	pause();
	
	printf("ResponseIncomplete: %s\n", PRINTINFO_BOOL2STRING(device->GeneralConfiguration.ResponseIncomplete) );
	printf("FixedDevice: %s\n", PRINTINFO_BOOL2STRING(device->GeneralConfiguration.FixedDevice) );
	printf("RemovableMedia: %s\n", PRINTINFO_BOOL2STRING(device->GeneralConfiguration.RemovableMedia) );
	printf("DeviceType: %s\n", PRINTINFO_BOOL2STRING(device->GeneralConfiguration.DeviceType) );
	
	printf("NumCylinders: %u\n", PRINTINFO_NUM2UINT(device->NumCylinders) );
	printf("NumHeads: %u\n", PRINTINFO_NUM2UINT(device->NumHeads) );
	printf("NumSectorsPerTrack: %u\n", PRINTINFO_NUM2UINT(device->NumSectorsPerTrack) );
	printf("SerialNumber: %s\n", PRINTINFO_STRING2PRINTABLE(device->SerialNumber) );
	printf("FirmwareRevision: %s\n", PRINTINFO_STRING2PRINTABLE(device->FirmwareRevision) );
	printf("ModelNumber: %s\n", PRINTINFO_STRING2PRINTABLE(device->ModelNumber) );
	printf("MaximumBlockTransfer: %u\n", PRINTINFO_NUM2UINT(device->MaximumBlockTransfer) );
	
	printf("DmaSupported: %s\n", PRINTINFO_BOOL2STRING(device->Capabilities.DmaSupported) );
	printf("LbaSupported: %s\n", PRINTINFO_BOOL2STRING(device->Capabilities.LbaSupported) );
	printf("IordyDisable: %s\n", PRINTINFO_BOOL2STRING(device->Capabilities.IordyDisable) );
	printf("IordySupported: %s\n", PRINTINFO_BOOL2STRING(device->Capabilities.IordySupported) );
	printf("StandybyTimerSupport: %s\n", PRINTINFO_BOOL2STRING(device->Capabilities.StandybyTimerSupport) );
	
	printf("Words64till70valid: %s\n", PRINTINFO_BOOL2STRING(device->Validity.Words64till70valid) );
	printf("Word88vaild: %s\n", PRINTINFO_BOOL2STRING(device->Validity.Word88vaild) );
	
	printf("NumberOfCurrentCylinders: %u\n", PRINTINFO_NUM2UINT(device->NumberOfCurrentCylinders) );
	printf("NumberOfCurrentHeads: %u\n", PRINTINFO_NUM2UINT(device->NumberOfCurrentHeads) );
	printf("CurrentSectorsPerTrack: %u\n", PRINTINFO_NUM2UINT(device->CurrentSectorsPerTrack) );
	printf("CurrentSectorCapacity: %u\n", PRINTINFO_NUM2UINT(device->CurrentSectorCapacity) );
	
	printf("CurrentMultiSectorSetting: %u\n", PRINTINFO_NUM2UINT(device->MultiSectorSetting.CurrentMultiSectorSetting) );
	printf("MultiSectorSettingValid: %s\n", PRINTINFO_BOOL2STRING(device->MultiSectorSetting.MultiSectorSettingValid) );
	
	pause();
	
	printf("UserAddressableSectors: %u\n", PRINTINFO_NUM2UINT(device->UserAddressableSectors) );
	printf("MultiWordDMASupportMode1: %s\n", PRINTINFO_BOOL2STRING(device->MultiWordDMA.MultiWordDMASupportMode1) );
	printf("MultiWordDMASupportMode2: %s\n", PRINTINFO_BOOL2STRING(device->MultiWordDMA.MultiWordDMASupportMode2) );
	printf("MultiWordDMASupportMode3: %s\n", PRINTINFO_BOOL2STRING(device->MultiWordDMA.MultiWordDMASupportMode3) );
	printf("MultiWordDMAActiveMode1: %s\n", PRINTINFO_BOOL2STRING(device->MultiWordDMA.MultiWordDMAActiveMode1) );
	printf("MultiWordDMAActiveMode2: %s\n", PRINTINFO_BOOL2STRING(device->MultiWordDMA.MultiWordDMAActiveMode2) );
	
	printf("AdvancedPIOModes: %u\n", PRINTINFO_NUM2UINT(device->AdvancedPIOModes) );
	printf("MinimumMWXferCycleTime: %u\n", PRINTINFO_NUM2UINT(device->MinimumMWXferCycleTime) );
	printf("RecommendedMWXferCycleTime: %u\n", PRINTINFO_NUM2UINT(device->RecommendedMWXferCycleTime) );
	printf("MinimumPIOCycleTime: %u\n", PRINTINFO_NUM2UINT(device->MinimumPIOCycleTime) );
	printf("MinimumPIOCycleTimeIORDY: %u\n", PRINTINFO_NUM2UINT(device->MinimumPIOCycleTimeIORDY) );
	printf("AdvancedPIOModes: %u\n", PRINTINFO_NUM2UINT(device->AdvancedPIOModes) );
	
	printf("QueueDepth: %u\n", PRINTINFO_NUM2UINT(device->QueueDepth.QueueDepth) );
	
	printf("ATA/ATAPI1 support: %s\n", PRINTINFO_BOOL2STRING(device->MajorRevision.ATA_ATAPI1) );
	printf("ATA/ATAPI2 support: %s\n", PRINTINFO_BOOL2STRING(device->MajorRevision.ATA_ATAPI2) );
	printf("ATA/ATAPI3 support: %s\n", PRINTINFO_BOOL2STRING(device->MajorRevision.ATA_ATAPI3) );
	printf("ATA/ATAPI4 support: %s\n", PRINTINFO_BOOL2STRING(device->MajorRevision.ATA_ATAPI4) );
	printf("ATA/ATAPI5 support: %s\n", PRINTINFO_BOOL2STRING(device->MajorRevision.ATA_ATAPI5) );
	printf("ATA/ATAPI6 support: %s\n", PRINTINFO_BOOL2STRING(device->MajorRevision.ATA_ATAPI6) );
	printf("ATA/ATAPI7 support: %s\n", PRINTINFO_BOOL2STRING(device->MajorRevision.ATA_ATAPI7) );
	printf("ATA/ATAPI8 support: %s\n", PRINTINFO_BOOL2STRING(device->MajorRevision.ATA_ATAPI8) );
	printf("ATA/ATAPI9 support: %s\n", PRINTINFO_BOOL2STRING(device->MajorRevision.ATA_ATAPI9) );
	printf("ATA/ATAPI10 support: %s\n", PRINTINFO_BOOL2STRING(device->MajorRevision.ATA_ATAPI10) );
	printf("ATA/ATAPI11 support: %s\n", PRINTINFO_BOOL2STRING(device->MajorRevision.ATA_ATAPI11) );
	
	pause();
	
	printf("ATA/ATAPI12 support: %s\n", PRINTINFO_BOOL2STRING(device->MajorRevision.ATA_ATAPI12) );
	printf("ATA/ATAPI13 support: %s\n", PRINTINFO_BOOL2STRING(device->MajorRevision.ATA_ATAPI13) );
	printf("ATA/ATAPI14 support: %s\n", PRINTINFO_BOOL2STRING(device->MajorRevision.ATA_ATAPI14) );
	
	printf("MinorRevision: %u\n", PRINTINFO_NUM2UINT(device->MinorRevision) );
	
	printf("Support command SmartCommands: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.SmartCommands) );
	printf("Set active command SmartCommands: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.SmartCommands) );
	printf("Support command SecurityMode: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.SecurityMode) );
	printf("Set active command SecurityMode: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.SecurityMode) );
	printf("Support command RemovableMediaFeature: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.RemovableMediaFeature) );
	printf("Set active command RemovableMediaFeature: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.RemovableMediaFeature) );
	printf("Support command PowerManagement: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.PowerManagement) );
	printf("Set active command PowerManagement: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.PowerManagement) );
	printf("Support command WriteCache: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.WriteCache) );
	printf("Set active command WriteCache: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.WriteCache) );
	printf("Support command LookAhead: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.LookAhead) );
	printf("Set active command LookAhead: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.LookAhead) );
	printf("Support command ReleaseInterrupt: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.ReleaseInterrupt) );
	printf("Set active command ReleaseInterrupt: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.ReleaseInterrupt) );
	printf("Support command ServiceInterrupt: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.ServiceInterrupt) );
	printf("Set active command ServiceInterrupt: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.ServiceInterrupt) );
	printf("Support command DeviceReset: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.DeviceReset) );
	printf("Set active command DeviceReset: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.DeviceReset) );
	printf("Support command HostProtectedArea: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.HostProtectedArea) );
	printf("Set active command HostProtectedArea: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.HostProtectedArea) );
	
	pause();
	
	printf("Support command WriteBuffer: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.WriteBuffer) );
	printf("Set active command WriteBuffer: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.WriteBuffer) );
	printf("Support command ReadBuffer: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.ReadBuffer) );
	printf("Set active command ReadBuffer: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.ReadBuffer) );
	printf("Support command Nop: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.Nop) );
	printf("Set active command Nop: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.Nop) );
	printf("Support command DownloadMicrocode: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.DownloadMicrocode) );
	printf("Set active command DownloadMicrocode: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.DownloadMicrocode) );
	printf("Support command DmaQueued: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.DmaQueued) );
	printf("Set active command DmaQueued: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.DmaQueued) );
	printf("Support command Cfa: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.Cfa) );
	printf("Set active command Cfa: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.Cfa) );
	printf("Support command AdvancedPm: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.AdvancedPm) );
	printf("Set active command AdvancedPm: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.AdvancedPm) );
	printf("Support command Msn: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.Msn) );
	printf("Set active command Msn: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.Msn) );
	printf("Support command PowerUpInStandby: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.PowerUpInStandby) );
	printf("Set active command PowerUpInStandby: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.PowerUpInStandby) );
	printf("Support command ManualPowerUp: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.ManualPowerUp) );
	printf("Set active command ManualPowerUp: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.ManualPowerUp) );
	printf("Support command SetMax: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.SetMax) );
	printf("Set active command SetMax: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.SetMax) );
	printf("Support command Acoustics: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.Acoustics) );
	printf("Set active command Acoustics: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.Acoustics) );
	
	pause();
	
	printf("Support command BigLba: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.BigLba) );
	printf("Set active command BigLba: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.BigLba) );
	printf("Support command DeviceConfigOverlay: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.DeviceConfigOverlay) );
	printf("Set active command DeviceConfigOverlay: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.DeviceConfigOverlay) );
	printf("Support command FlushCache: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.FlushCache) );
	printf("Set active command FlushCache: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.FlushCache) );
	printf("Support command FlushCacheExt: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.FlushCacheExt) );
	printf("Set active command FlushCacheExt: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.FlushCacheExt) );
	printf("Support command SmartErrorLog: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.SmartErrorLog) );
	printf("Set active command SmartErrorLog: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.SmartErrorLog) );
	printf("Support command SmartSelfTest: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.SmartSelfTest) );
	printf("Set active command SmartSelfTest: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.SmartSelfTest) );
	printf("Support command MediaSerialNumber: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.MediaSerialNumber) );
	printf("Set active command MediaSerialNumber: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.MediaSerialNumber) );
	printf("Support command MediaCardPassThrough: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.MediaCardPassThrough) );
	printf("Set active command MediaCardPassThrough: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.MediaCardPassThrough) );
	printf("Support command StreamingFeature: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.StreamingFeature) );
	printf("Set active command StreamingFeature: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.StreamingFeature) );
	printf("Support command GpLogging: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.GpLogging) );
	printf("Set active command GpLogging: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.GpLogging) );
	printf("Support command WriteFua: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.WriteFua) );
	printf("Set active command WriteFua: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.WriteFua) );
	printf("Support command WriteQueuedFua: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.WriteQueuedFua) );
	printf("Set active command WriteQueuedFua: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.WriteQueuedFua) );
	
	pause();
	
	printf("Support command WWN64Bit: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.WWN64Bit) );
	printf("Set active command WWN64Bit: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.WWN64Bit) );
	printf("Support command URGReadStream: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.URGReadStream) );
	printf("Set active command URGReadStream: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.URGReadStream) );
	printf("Support command URGWriteStream: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.URGWriteStream) );
	printf("Set active command URGWriteStream: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.URGWriteStream) );
	printf("Support command IdleWithUnloadFeature: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupport.IdleWithUnloadFeature) );
	printf("Set active command IdleWithUnloadFeature: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActive.IdleWithUnloadFeature) );
	
	printf("DMAMode0 support: %s\n", PRINTINFO_BOOL2STRING(device->UltraDMASupport.DMAMode0) );
	printf("DMAMode0 active: %s\n", PRINTINFO_BOOL2STRING(device->UltraDMAActive.DMAMode0) );
	printf("DMAMode1 support: %s\n", PRINTINFO_BOOL2STRING(device->UltraDMASupport.DMAMode1) );
	printf("DMAMode1 active: %s\n", PRINTINFO_BOOL2STRING(device->UltraDMAActive.DMAMode1) );
	printf("DMAMode2 support: %s\n", PRINTINFO_BOOL2STRING(device->UltraDMASupport.DMAMode2) );
	printf("DMAMode2 active: %s\n", PRINTINFO_BOOL2STRING(device->UltraDMAActive.DMAMode2) );
	printf("DMAMode3 support: %s\n", PRINTINFO_BOOL2STRING(device->UltraDMASupport.DMAMode3) );
	printf("DMAMode3 active: %s\n", PRINTINFO_BOOL2STRING(device->UltraDMAActive.DMAMode3) );
	printf("DMAMode4 support: %s\n", PRINTINFO_BOOL2STRING(device->UltraDMASupport.DMAMode4) );
	printf("DMAMode4 active: %s\n", PRINTINFO_BOOL2STRING(device->UltraDMAActive.DMAMode4) );
	printf("DMAMode5 support: %s\n", PRINTINFO_BOOL2STRING(device->UltraDMASupport.DMAMode5) );
	printf("DMAMode5 active: %s\n", PRINTINFO_BOOL2STRING(device->UltraDMAActive.DMAMode5) );
	printf("DMAMode6 support: %s\n", PRINTINFO_BOOL2STRING(device->UltraDMASupport.DMAMode6) );
	printf("DMAMode6 active: %s\n", PRINTINFO_BOOL2STRING(device->UltraDMAActive.DMAMode6) );
	
	printf("SecureEraseUnitCompletionTime: %u\n", PRINTINFO_NUM2UINT(device->SecureEraseUnitCompletionTime) );
	printf("EnhancedSecureEraseUnitCompletionTime: %u\n", PRINTINFO_NUM2UINT(device->EnhancedSecureEraseUnitCompletionTime) );
	
	pause();
	
	printf("CurrentAdvancedPowerManagementValue: %u\n", PRINTINFO_NUM2UINT(device->CurrentAdvancedPowerManagementValue) );
	printf("MasterPasswordRevisionCode: %u\n", PRINTINFO_NUM2UINT(device->MasterPasswordRevisionCode) );
	
	printf("Device0_DeviceNumberMethod: %u\n", PRINTINFO_NUM2UINT(device->HardwareResetResult.Device0_DeviceNumberMethod) );
	printf("Device0_Diagnostics: %s\n", PRINTINFO_BOOL2STRING(device->HardwareResetResult.Device0_Diagnostics) );
	printf("Device0_PDIAG: %s\n", PRINTINFO_BOOL2STRING(device->HardwareResetResult.Device0_PDIAG) );
	printf("Device0_DASP: %s\n", PRINTINFO_BOOL2STRING(device->HardwareResetResult.Device0_DASP) );
	printf("Device0_ResponceUnselected: %s\n", PRINTINFO_BOOL2STRING(device->HardwareResetResult.Device0_ResponceUnselected) );
	printf("Device1_DeviceNumberMethod: %u\n", PRINTINFO_NUM2UINT(device->HardwareResetResult.Device1_DeviceNumberMethod) );
	printf("Device1_PDIAG: %s\n", PRINTINFO_BOOL2STRING(device->HardwareResetResult.Device1_PDIAG) );
	printf("CBLID: %s\n", PRINTINFO_BOOL2STRING(device->HardwareResetResult.CBLID) );
	
	printf("CurrentAcousticValue: %u\n", PRINTINFO_NUM2UINT(device->CurrentAcousticValue) );
	printf("RecommendedAcousticValue: %u\n", PRINTINFO_NUM2UINT(device->RecommendedAcousticValue) );
	printf("StreamMinimumRequestSize: %u\n", PRINTINFO_NUM2UINT(device->StreamMinimumRequestSize) );
	printf("StreamingTransferTime_DMA: %u\n", PRINTINFO_NUM2UINT(device->StreamingTransferTime_DMA) );
	printf("StreamingAccessLatency: %u\n", PRINTINFO_NUM2UINT(device->StreamingAccessLatency) );
	printf("StreamingPerformanceGranularity: %u\n", PRINTINFO_NUM2UINT(device->StreamingPerformanceGranularity) );
	printf("Max48BitLBA: %u\n", PRINTINFO_NUM2UINT(device->Max48BitLBA) );
	printf("StreamingTransferTime_PIO: %u\n", PRINTINFO_NUM2UINT(device->StreamingTransferTime_PIO) );
	
	printf("LogicalSectorsPerPhysicalSector: %u\n", PRINTINFO_NUM2UINT(device->PhysicalLogicalSectorSize.LogicalSectorsPerPhysicalSector) );
	printf("LogicalSectorLongerThan256Words: %s\n", PRINTINFO_BOOL2STRING(device->PhysicalLogicalSectorSize.LogicalSectorLongerThan256Words) );
	printf("MultipleLogicalSectorsPerPhysicalSector: %s\n", PRINTINFO_BOOL2STRING(device->PhysicalLogicalSectorSize.MultipleLogicalSectorsPerPhysicalSector) );
	
	printf("InterSeekDelay: %u\n", PRINTINFO_NUM2UINT(device->InterSeekDelay) );
	
	printf("IEEE_NAA.IEEE_OUI: %u\n", PRINTINFO_NUM2UINT(device->IEEE_NAA.IEEE_OUI) );
	printf("IEEE_NAA.NAA: %u\n", PRINTINFO_NUM2UINT(device->IEEE_NAA.NAA) );
	
	pause();
	
	printf("UniqueID_IEEE.UniqueID_part1: %u\n", PRINTINFO_NUM2UINT(device->UniqueID_IEEE.UniqueID_part1) );
	printf("UniqueID_IEEE.IEEE_OUI: %u\n", PRINTINFO_NUM2UINT(device->UniqueID_IEEE.IEEE_OUI) );
	
	printf("UniqueID_part2: %u\n", PRINTINFO_NUM2UINT(device->UniqueID_part2) );
	printf("UniqueID_part3: %u\n", PRINTINFO_NUM2UINT(device->UniqueID_part3) );
	// TODO: ReservedForWorldWideName128?  ReservedForTlcTechnicalReport?  WordsPerLogicalSector[0]?  WordsPerLogicalSector[1]?
	printf("WordsPerLogicalSector[0]: %u\n", PRINTINFO_NUM2UINT(device->WordsPerLogicalSector[0]) );
	printf("WordsPerLogicalSector[1]: %u\n", PRINTINFO_NUM2UINT(device->WordsPerLogicalSector[1]) );
	
	printf("WriteReadVerifySupported: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetSupportExt.WriteReadVerifySupported) );
	printf("WriteReadVerifyEnabled: %s\n", PRINTINFO_BOOL2STRING(device->CommandSetActiveExt.WriteReadVerifyEnabled) );
	
	printf("MsnSupport: %s\n", PRINTINFO_BOOL2STRING(device->MsnSupport.MsnSupport) );
	
	printf("SecuritySupported: %s\n", PRINTINFO_BOOL2STRING(device->SecurityStatus.SecuritySupported) );
	printf("SecurityEnabled: %s\n", PRINTINFO_BOOL2STRING(device->SecurityStatus.SecurityEnabled) );
	printf("SecurityLocked: %s\n", PRINTINFO_BOOL2STRING(device->SecurityStatus.SecurityLocked) );
	printf("SecurityFrozen: %s\n", PRINTINFO_BOOL2STRING(device->SecurityStatus.SecurityFrozen) );
	printf("SecurityCountExpired: %s\n", PRINTINFO_BOOL2STRING(device->SecurityStatus.SecurityCountExpired) );
	printf("EnhancedSecurityEraseSupported: %s\n", PRINTINFO_BOOL2STRING(device->SecurityStatus.EnhancedSecurityEraseSupported) );
	printf("SecurityLevel high: %s\n", PRINTINFO_BOOL2STRING(device->SecurityStatus.SecurityLevel) );
	
	printf("MaximumCurrentInMA2: %u\n", PRINTINFO_NUM2UINT(device->CfaPowerModel.MaximumCurrentInMA2) );
	printf("CfaPowerMode1Disabled: %s\n", PRINTINFO_BOOL2STRING(device->CfaPowerModel.CfaPowerMode1Disabled) );
	printf("CfaPowerMode1Required: %s\n", PRINTINFO_BOOL2STRING(device->CfaPowerModel.CfaPowerMode1Required) );
	printf("Word160Supported: %s\n", PRINTINFO_BOOL2STRING(device->CfaPowerModel.Word160Supported) );
	
	printf("SupportsTrim: %s\n", PRINTINFO_BOOL2STRING(device->DataSetManagementFeature.SupportsTrim) );
	
	printf("CurrentMediaSerialNumber: %s\n", PRINTINFO_STRING2PRINTABLE(device->CurrentMediaSerialNumber) ); // uint16_t CurrentMediaSerialNumber[30]
	
	printf("AlignmentOfLogicalWithinPhysical: %u\n", PRINTINFO_NUM2UINT(device->BlockAlignment.AlignmentOfLogicalWithinPhysical) );
	printf("Word209Supported: %s\n", PRINTINFO_BOOL2STRING(device->BlockAlignment.Word209Supported) );
	
	pause();
	
	printf("WriteReadVerifySectorCountMode3Only[0]: %u\n", PRINTINFO_NUM2UINT(device->WriteReadVerifySectorCountMode3Only[0]) );
	printf("WriteReadVerifySectorCountMode3Only[1]: %u\n", PRINTINFO_NUM2UINT(device->WriteReadVerifySectorCountMode3Only[1]) );
	printf("WriteReadVerifySectorCountMode2Only[0]: %u\n", PRINTINFO_NUM2UINT(device->WriteReadVerifySectorCountMode2Only[0]) );
	printf("WriteReadVerifySectorCountMode2Only[1]: %u\n", PRINTINFO_NUM2UINT(device->WriteReadVerifySectorCountMode2Only[1]) );
	
	printf("NVCachePowerModeEnabled: %s\n", PRINTINFO_BOOL2STRING(device->NVCacheCapabilities.NVCachePowerModeEnabled) );
	printf("NVCacheFeatureSetEnabled: %s\n", PRINTINFO_BOOL2STRING(device->NVCacheCapabilities.NVCacheFeatureSetEnabled) );
	printf("NVCachePowerModeVersion: %u\n", PRINTINFO_NUM2UINT(device->NVCacheCapabilities.NVCachePowerModeVersion) );
	printf("NVCacheFeatureSetVersion: %u\n", PRINTINFO_NUM2UINT(device->NVCacheCapabilities.NVCacheFeatureSetVersion) );
	
	printf("NVCacheSizeLSW: %u\n", PRINTINFO_NUM2UINT(device->NVCacheSizeLSW) );
	printf("NVCacheSizeMSW: %u\n", PRINTINFO_NUM2UINT(device->NVCacheSizeMSW) );
	printf("NominalMediaRotationRate: %u\n", PRINTINFO_NUM2UINT(device->NominalMediaRotationRate) );
	
	printf("NVCacheEstimatedTimeToSpinUpInSeconds: %u\n", PRINTINFO_NUM2UINT(device->NVCacheOptions.NVCacheEstimatedTimeToSpinUpInSeconds) );
	
	printf("Signature: %u\n", PRINTINFO_NUM2UINT(device->Integrity.Signature) );
	printf("CheckSum: %u\n", PRINTINFO_NUM2UINT(device->Integrity.CheckSum) );
	
	pause();
	
	puts("Derived from the info above:\n");
	
	uint32_t sectorsize;
	uint32_t driveCapacity;
	
	if(device->PhysicalLogicalSectorSize.LogicalSectorLongerThan256Words)
		sectorsize = (1 << device->PhysicalLogicalSectorSize.LogicalSectorsPerPhysicalSector) * 512;
	else
		sectorsize = 512;
	
	driveCapacity = sectorsize * device->UserAddressableSectors; // Only works for drives with less then 4G capacity ;)
	
	printf("User addressable sectors: %i\n", device->UserAddressableSectors);
	printf("Sectors size: %u bytes\n", sectorsize );
	printf("Drive capacity: %u bytes (= %u MB)\n", driveCapacity, (driveCapacity + 500*1000) /(1000*1000) );
}

static inline int
ol_ata_sector_read_LBA48(ol_ata_device* device, const uint64_t LBA, const uint32_t length, void* buf)
{
	if( LBA > device->identifier.Max48BitLBA )
		return 0;
	
	puts("Cannot read using 48 bit address at the moment...\n");
	return 0;
}

static inline int
ol_ata_sector_read_LBA28(ol_ata_device* device, const uint64_t LBA, const uint32_t length, void* buf)
{
	uint64_t _length = length;
	uint8_t currentLength = 0;
	do
	{
		currentLength = (_length > 256)? 0 : _length;
		
		writePIOByte(device->base, CB_WRITE_SC, currentLength);
		writeLBA(device->base, LBA, 0xe);
		writePIOByte(device->base, CB_WRITE_CMD, 0x20);
		
		uint8_t status = waitDeviceStatus(device->base);
		if(status)
		{
			printf("ERROR while reading sector: 0x0%x\n", status & 0x07);
			return length - _length;
		}
		
		readPIOData(device->base, buf, 256);
		
		if(currentLength == 0)
		{
			_length -= 256;
			buf += 256 * device->sectorsize;
			
			// wait 400ns before reading more sectors...
			readPIOByte(device->base, CB_READ_STAT);
			readPIOByte(device->base, CB_READ_STAT);
			readPIOByte(device->base, CB_READ_STAT);
			readPIOByte(device->base, CB_READ_STAT);
			
			continue;
		}
	}
	while( 0 );
	
	return length;
}

static inline int
ol_ata_sector_read_CHS(ol_ata_device* device, const uint64_t LBA, const uint32_t length, void* buf)
{
	puts("Cannot read using CHS address at the moment...\n");
	return 0;
}

int
ol_ata_sector_read(ol_ata_device* device, const uint64_t LBA, const uint32_t length, void* buf)
{
	if(!device->identifier.Capabilities.LbaSupported)
		return ol_ata_sector_read_CHS(device, LBA, length, buf);
	
	if( (LBA + length*device->sectorsize) > ((1<<28)-1) ) // Check if address fits in 28-bit
		return ol_ata_sector_read_LBA48(device, LBA, length, buf);
	
	return ol_ata_sector_read_LBA28(device, LBA, length, buf);
}

static inline int
ol_ata_sector_write_LBA48(ol_ata_device* device, const uint64_t LBA, const uint32_t length, void* buf)
{
	if( LBA > device->identifier.Max48BitLBA )
		return 0;
	
	puts("Cannot write using 48 bit address at the moment...\n");
	return 0;
}

static inline int
ol_ata_sector_write_LBA28(ol_ata_device* device, const uint64_t LBA, const uint32_t length, void* buf)
{
	//TODO: Test if this works...
	
	uint64_t _length = length;
	uint8_t currentLength = 0;
	do
	{
		currentLength = (_length > 256)? 0 : _length;
		
		writePIOByte(device->base, CB_WRITE_SC, currentLength);
		writeLBA(device->base, LBA, 0xe);
		writePIOByte(device->base, CB_WRITE_CMD, 0x30);
		
		uint8_t status = waitDeviceStatus(device->base);
		if(status)
		{
			printf("ERROR while reading sector: 0x0%x\n", status & 0x07);
			return length - _length;
		}
		
		writePIOData(device->base, buf, 256);
		
		if(currentLength == 0)
		{
			_length -= 256;
			buf += 256 * device->sectorsize;
			
			// wait 400ns before reading more sectors...
			readPIOByte(device->base, CB_READ_STAT);
			readPIOByte(device->base, CB_READ_STAT);
			readPIOByte(device->base, CB_READ_STAT);
			readPIOByte(device->base, CB_READ_STAT);
			
			continue;
		}
	}
	while( 0 );
	
	return length;
}

static inline int
ol_ata_sector_write_CHS(ol_ata_device* device, const uint64_t LBA, const uint32_t length, void* buf)
{
	puts("Cannot write using CHS address at the moment...\n");
	return 0;
}

int
ol_ata_sector_write(ol_ata_device* device, const uint64_t LBA, const uint32_t length, void* buf)
{
	if(!device->identifier.Capabilities.LbaSupported)
		return ol_ata_sector_write_CHS(device, LBA, length, buf);
	
	if( (LBA + length*device->sectorsize) > ((1<<28)-1) ) // Check if address fits in 28-bit
		return ol_ata_sector_write_LBA48(device, LBA, length, buf);
	
	return ol_ata_sector_write_LBA28(device, LBA, length, buf);
}

void
ol_ata_init(uint32_t base, ol_ata_device* device)
{
	printf("Init ATA...");
	device->base = base;
	device->type = ol_ata_detect_drive_type(base, false);
	ol_ata_get_device_info(device->base, &device->identifier);
	
	if(device->identifier.PhysicalLogicalSectorSize.LogicalSectorLongerThan256Words)
		device->sectorsize = (1 << device->identifier.PhysicalLogicalSectorSize.LogicalSectorsPerPhysicalSector) * 512;
	else
		device->sectorsize = 512;
}

void
ol_ata_test(ol_ata_device* device)
{
	uint8_t buf[device->sectorsize];
	
	printf("\nTesting ATA/ATAPI...\n");
	
	printf("Device type: ");
	switch(device->type)
	{
	case ATA_TYPE_PATAPI:
		printf("patapi\n");
		break;
	case ATA_TYPE_SATAPI:
		printf("satapi\n");
		break;
	case ATA_TYPE_PATA:
		printf("pata\n");
		break;
	case ATA_TYPE_SATA:
		printf("sata\n");
		break;
	default:
		printf("unknown!\n");
	}
	
	ol_ata_printDeviceInfo(&device->identifier);
	
	printf("\nAbout to read first sector...\n");
	pause();
	printf("Sector data:\n");
	
	ol_ata_sector_read(device, 0, 1, buf);
	
	printBuf(buf, 0, 256);
	pause();
	printBuf(buf, 256, 512);
	
	pause();
	buf[0] = ~buf[0];
	printf("Chaning byte 0 to 0x%x\n", buf[0]);
	
	ol_ata_sector_write(device, 0, 1, buf);
	
	printf("ATAPI test done!\n");
}

int
ol_ata_detect_dev_type (ol_ata_dev_t dev)
{
	ol_ata_soft_reset(dev); /* waits until master drive is ready again */
        outb(OL_ATA_FEATURES(dev->base_port), 4);
	outb(OL_ATA_DRIVE_SELECT(dev->base_port), 0xA0 | (dev->slave << 4));
	inb(dev->dcr); /* wait 400ns for drive select to work */
	inb(dev->dcr);
	inb(dev->dcr);
	inb(dev->dcr);
	uint8_t cl = inb(OL_ATA_MID_LBA(dev->base_port));
	uint8_t ch = inb(OL_ATA_HIGH_LBA(dev->base_port));

	/* differentiate ATA, ATAPI, SATA and SATAPI */
	if(cl == 0x14 && ch == 0xEB) return OL_ATA_PATAPI;
	if(cl == 0x69 && ch == 0x96) return OL_ATA_SATAPI;
	if(cl == 0 && ch == 0) return OL_ATA_PATA;
	if(cl == 0x3c && ch == 0xc3) return OL_ATA_SATA;
	return OL_ATA_UNKNOWN;
}

static void
ol_ata_soft_reset(ol_ata_dev_t dev)
{
        outb(dev->dcr, 4); /* set the srst bit - e.g. do a software reset */
        outb(dev->dcr, 0);
}
