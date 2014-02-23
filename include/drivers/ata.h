/*
 *   Public ide header file.
 *   Copyright (C) 2014  Steven van der Schoot
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

#include <types.h>

#ifndef __ATA_H
#define __ATA_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	ATA_TYPE_UNKNOWN,
	ATA_TYPE_PATAPI,
	ATA_TYPE_SATAPI,
	ATA_TYPE_PATA,
	ATA_TYPE_SATA
} ol_ata_type;

typedef struct __attribute__((packed))
{
  struct __attribute__((packed)) {
    uint16_t Reserved1          :1; // [ 0- 0]
    uint16_t Retired3           :1; // [ 1- 1]
    uint16_t ResponseIncomplete :1; // [ 2- 2]
    uint16_t Retired2           :3; // [ 3- 5]
    uint16_t FixedDevice        :1; // [ 6- 6]
    uint16_t RemovableMedia     :1; // [ 7- 7]: 1 = media is removable
    uint16_t Retired1           :7; // [ 8-14]
    uint16_t DeviceType         :1; // [15-15]: 0 = ata device
  } GeneralConfiguration;
  uint16_t NumCylinders;
  uint16_t ReservedWord2;
  uint16_t NumHeads;
  uint16_t Retired1[2];
  uint16_t NumSectorsPerTrack;
  uint16_t VendorUnique1[3];
  uint8_t  SerialNumber[20]; // 20 ASCII characters
  uint16_t Retired2[2];
  uint16_t Obsolete1;
  uint8_t  FirmwareRevision[8]; // 8 ASCII characters
  uint8_t  ModelNumber[40]; // 40 ASCII characters
  uint8_t  MaximumBlockTransfer; // 0: reserved | 0x01-0xff: max. number of serctors transferred per interrupt
  uint8_t  VendorUnique2;
  uint16_t ReservedWord48;
  struct __attribute__((packed)) {
    uint8_t  ReservedByte49;          // [ 0- 7]
    uint8_t  DmaSupported         :1; // [ 8- 8]
    uint8_t  LbaSupported         :1; // [ 9- 9]
    uint8_t  IordyDisable         :1; // [10-10]
    uint8_t  IordySupported       :1; // [11-11]
    uint8_t  Reserved1            :1; // [12-12]
    uint8_t  StandybyTimerSupport :1; // [13-13]
    uint8_t  Reserved2            :2; // [14-15]
    uint16_t ReservedWord50;          // [16-31]: Not actualy reserved, but the bit in here have static values...
  } Capabilities;
  uint16_t ObsoleteWords51[2];
  struct __attribute__((packed)) {
		uint16_t Obsolete1              :1;  // [ 0- 0]
		uint16_t Words64till70valid     :1;  // [ 1- 1]: 1 = words 64:70 are valid
		uint16_t Word88vaild            :1;  // [ 2- 2]: 1 = word 88 is valid
		uint16_t Reserved3              :13; // [ 3-15]
	} Validity;
  uint16_t NumberOfCurrentCylinders;
  uint16_t NumberOfCurrentHeads;
  uint16_t CurrentSectorsPerTrack;
  uint32_t CurrentSectorCapacity;
  struct __attribute__((packed)) {
		uint8_t  CurrentMultiSectorSetting   ; // [ 0- 7]
		uint8_t  MultiSectorSettingValid   :1; // [ 8- 8]
		uint8_t  ReservedByte59            :7; // [ 9-15]
	} MultiSectorSetting;
  uint32_t UserAddressableSectors;
  uint16_t ObsoleteWord62;
  struct __attribute__((packed)) {
		uint16_t MultiWordDMASupportMode1 :1; // [ 0- 0]
		uint16_t MultiWordDMASupportMode2 :1; // [ 1- 1]
		uint16_t MultiWordDMASupportMode3 :1; // [ 2- 2]
		uint16_t Reserved1                :5; // [ 3- 7]
		uint16_t MultiWordDMAActiveMode1  :1; // [ 8- 8]
		uint16_t MultiWordDMAActiveMode2  :1; // [ 98- 9]
		uint16_t Reserved2                :6; // [10-15]
	} MultiWordDMA;
	uint8_t AdvancedPIOModes;
	uint8_t ReservedByte64;
  uint16_t MinimumMWXferCycleTime;
  uint16_t RecommendedMWXferCycleTime;
  uint16_t MinimumPIOCycleTime;
  uint16_t MinimumPIOCycleTimeIORDY;
  uint16_t ReservedWords69[6];
  struct __attribute__((packed)) {
		uint16_t QueueDepth     :5;  // [ 0- 4]: Maximum queue depth - 1
		uint16_t ReservedWord75 :11; // [ 5-15]
	} QueueDepth;
  uint16_t ReservedWords76[4];
  struct __attribute__((packed)) {
		uint16_t Reserved1   :1; // [ 0- 0]
		uint16_t ATA_ATAPI1  :1; // [ 1- 1]: Does not exsist in ATA/ATAPI1: obsolete
		uint16_t ATA_ATAPI2  :1; // [ 2- 2]: Does not exsist in ATA/ATAPI2: obsolete
		uint16_t ATA_ATAPI3  :1; // [ 3- 3]: Does not exsist in ATA/ATAPI3: obsolete
		uint16_t ATA_ATAPI4  :1; // [ 4- 4]: 1 = support for ATA/ATAPI4
		uint16_t ATA_ATAPI5  :1; // [ 5- 5]: 1 = support for ATA/ATAPI5
		uint16_t ATA_ATAPI6  :1; // [ 6- 6]: 1 = support for ATA/ATAPI6
		uint16_t ATA_ATAPI7  :1; // [ 7- 7]: 1 = support for ATA/ATAPI7
		uint16_t ATA_ATAPI8  :1; // [ 8- 8]: 1 = support for ATA/ATAPI8
		uint16_t ATA_ATAPI9  :1; // [ 9- 9]: Reserved for ATA/ATAPI9
		uint16_t ATA_ATAPI10 :1; // [10-10]: Reserved for ATA/ATAPI10
		uint16_t ATA_ATAPI11 :1; // [11-11]: Reserved for ATA/ATAPI11
		uint16_t ATA_ATAPI12 :1; // [12-12]: Reserved for ATA/ATAPI12
		uint16_t ATA_ATAPI13 :1; // [13-13]: Reserved for ATA/ATAPI13
		uint16_t ATA_ATAPI14 :1; // [14-14]: Reserved for ATA/ATAPI14
		uint16_t Reserved2   :1; // [15-15]
	} MajorRevision; // 0x0000 of 0xffff means device does not report version
  uint16_t MinorRevision; // 0x0000 of 0xffff means device does not report version
	struct __attribute__((packed)) {
    uint16_t SmartCommands         :1;
    uint16_t SecurityMode          :1;
    uint16_t RemovableMediaFeature :1;
    uint16_t PowerManagement       :1;
    uint16_t Reserved1             :1;
    uint16_t WriteCache            :1;
    uint16_t LookAhead             :1;
    uint16_t ReleaseInterrupt      :1;
    uint16_t ServiceInterrupt      :1;
    uint16_t DeviceReset           :1;
    uint16_t HostProtectedArea     :1;
    uint16_t Obsolete1             :1;
    uint16_t WriteBuffer           :1;
    uint16_t ReadBuffer            :1;
    uint16_t Nop                   :1;
    uint16_t Obsolete2             :1;
    uint16_t DownloadMicrocode     :1;
    uint16_t DmaQueued             :1;
    uint16_t Cfa                   :1;
    uint16_t AdvancedPm            :1;
    uint16_t Msn                   :1;
    uint16_t PowerUpInStandby      :1;
    uint16_t ManualPowerUp         :1;
    uint16_t Reserved2             :1;
    uint16_t SetMax                :1;
    uint16_t Acoustics             :1;
    uint16_t BigLba                :1;
    uint16_t DeviceConfigOverlay   :1;
    uint16_t FlushCache            :1;
    uint16_t FlushCacheExt         :1;
    uint16_t Resrved3              :2;
    uint16_t SmartErrorLog         :1;
    uint16_t SmartSelfTest         :1;
    uint16_t MediaSerialNumber     :1;
    uint16_t MediaCardPassThrough  :1;
    uint16_t StreamingFeature      :1;
    uint16_t GpLogging             :1;
    uint16_t WriteFua              :1;
    uint16_t WriteQueuedFua        :1;
    uint16_t WWN64Bit              :1;
    uint16_t URGReadStream         :1;
    uint16_t URGWriteStream        :1;
    uint16_t ReservedForTechReport :2;
    uint16_t IdleWithUnloadFeature :1;
    uint16_t Reserved4             :2;
  } CommandSetSupport;
  struct __attribute__((packed)) {
    uint16_t SmartCommands         :1;
    uint16_t SecurityMode          :1;
    uint16_t RemovableMediaFeature :1;
    uint16_t PowerManagement       :1;
    uint16_t Reserved1             :1;
    uint16_t WriteCache            :1;
    uint16_t LookAhead             :1;
    uint16_t ReleaseInterrupt      :1;
    uint16_t ServiceInterrupt      :1;
    uint16_t DeviceReset           :1;
    uint16_t HostProtectedArea     :1;
    uint16_t Obsolete1             :1;
    uint16_t WriteBuffer           :1;
    uint16_t ReadBuffer            :1;
    uint16_t Nop                   :1;
    uint16_t Obsolete2             :1;
    uint16_t DownloadMicrocode     :1;
    uint16_t DmaQueued             :1;
    uint16_t Cfa                   :1;
    uint16_t AdvancedPm            :1;
    uint16_t Msn                   :1;
    uint16_t PowerUpInStandby      :1;
    uint16_t ManualPowerUp         :1;
    uint16_t Reserved2             :1;
    uint16_t SetMax                :1;
    uint16_t Acoustics             :1;
    uint16_t BigLba                :1;
    uint16_t DeviceConfigOverlay   :1;
    uint16_t FlushCache            :1;
    uint16_t FlushCacheExt         :1;
    uint16_t Resrved3              :2;
    uint16_t SmartErrorLog         :1;
    uint16_t SmartSelfTest         :1;
    uint16_t MediaSerialNumber     :1;
    uint16_t MediaCardPassThrough  :1;
    uint16_t StreamingFeature      :1;
    uint16_t GpLogging             :1;
    uint16_t WriteFua              :1;
    uint16_t WriteQueuedFua        :1;
    uint16_t WWN64Bit              :1;
    uint16_t URGReadStream         :1;
    uint16_t URGWriteStream        :1;
    uint16_t ReservedForTechReport :2;
    uint16_t IdleWithUnloadFeature :1;
    uint16_t Reserved4             :2;
  } CommandSetActive;
  struct __attribute__((packed)) {
		uint8_t DMAMode0 :1; // [ 0- 0]
		uint8_t DMAMode1 :1; // [ 1- 1]
		uint8_t DMAMode2 :1; // [ 2- 2]
		uint8_t DMAMode3 :1; // [ 3- 3]
		uint8_t DMAMode4 :1; // [ 4- 4]
		uint8_t DMAMode5 :1; // [ 5- 5]
		uint8_t DMAMode6 :1; // [ 6- 6]
		uint8_t Reserved :1; // [ 7- 7]
  } UltraDMASupport ;
  struct __attribute__((packed)) {
		uint8_t DMAMode0 :1; // [ 0- 0]
		uint8_t DMAMode1 :1; // [ 1- 1]
		uint8_t DMAMode2 :1; // [ 2- 2]
		uint8_t DMAMode3 :1; // [ 3- 3]
		uint8_t DMAMode4 :1; // [ 4- 4]
		uint8_t DMAMode5 :1; // [ 5- 5]
		uint8_t DMAMode6 :1; // [ 6- 6]
		uint8_t Reserved :1; // [ 7- 7]
  } UltraDMAActive ;
	uint16_t SecureEraseUnitCompletionTime;
	uint16_t EnhancedSecureEraseUnitCompletionTime;
	uint16_t CurrentAdvancedPowerManagementValue;
	uint16_t MasterPasswordRevisionCode;
  struct __attribute__((packed)) {
		uint16_t Device0_Obsolete           :1; // [0 - 0]: always 1
		uint16_t Device0_DeviceNumberMethod :2; // [1 - 2]: 0 = Reserved; 1 = A jumper was used; 2 = the CSEL signal was used; 2 = Other or unknown method was used
		uint16_t Device0_Diagnostics        :1; // [3 - 3]: 1 = passed diagnostics
		uint16_t Device0_PDIAG              :1; // [4 - 4]: 1 = detected assertion of PDIAG
		uint16_t Device0_DASP               :1; // [5 - 5]: 1 = detected assertion of DASP
		uint16_t Device0_ResponceUnselected :1; // [6 - 6]: 1 = Device 0 repsonds when Device 1 is selcted
		uint16_t Reserved1                  :1; // [7 - 7]
		uint16_t Device1_Obsolete           :1; // [8 - 8]: always 1
		uint16_t Device1_DeviceNumberMethod :2; // [9 -10]: 0 = Reserved; 1 = A jumper was used; 2 = the CSEL signal was used; 2 = Other or unknown method was used
		uint16_t Device1_PDIAG              :1; // [11-11]: 1 = detected assertion of PDIAG
		uint16_t Reserved2                  :1; // [12-12]
		uint16_t CBLID                      :1; // [13-13]: 0 = device detected CBLID- below Vil; 1 = device detected CBLID- above Vih
		uint16_t Reserved3                  :2; // [14-15]: Shall be 0b01
	} HardwareResetResult;
	uint8_t CurrentAcousticValue;
	uint8_t RecommendedAcousticValue;
	uint16_t StreamMinimumRequestSize;
	uint16_t StreamingTransferTime_DMA;
	uint16_t StreamingAccessLatency; // DMA and PIO
	uint32_t StreamingPerformanceGranularity;
  uint64_t Max48BitLBA;
  uint16_t StreamingTransferTime_PIO;
  uint16_t ReservedWord105;
  struct __attribute__((packed)) {
    uint16_t LogicalSectorsPerPhysicalSector         :4; // [ 0- 3]: 2^LogicalSectorsPerPhysicalSector = amount of logical sectors per physical sector
    uint16_t Reserved0                               :8; // [ 4-11]
    uint16_t LogicalSectorLongerThan256Words         :1; // [12-12]: 1 = Device logical sector longer than 256 words
    uint16_t MultipleLogicalSectorsPerPhysicalSector :1; // [13-13]: 1 = Device has multiple logical sectors per physical sector
    uint16_t Reserved1                               :2; // [14-15]: shall be 0b01
  } PhysicalLogicalSectorSize;
  uint16_t InterSeekDelay;
  struct __attribute__((packed)) {
		uint16_t IEEE_OUI :12; // [ 0-11]
		uint16_t NAA      :4;  // [12-15]
  } IEEE_NAA;
  struct __attribute__((packed)) {
		uint16_t UniqueID_part1 :4;  // [ 0- 3]
		uint16_t IEEE_OUI       :12; // [ 4-15]
  } UniqueID_IEEE;
	uint16_t UniqueID_part2;
	uint16_t UniqueID_part3;
  uint16_t ReservedForWorldWideName128[4];
  uint16_t ReservedForTlcTechnicalReport;
  uint16_t WordsPerLogicalSector[2];
  struct __attribute__((packed)) {
    uint16_t ReservedForDrqTechnicalReport :1;  // [ 0- 0]
    uint16_t WriteReadVerifySupported      :1;  // [ 1- 1]
    uint16_t Reserved01                    :11; // [ 2-12]
    uint16_t Reserved1                     :2;  // [13-15]
  } CommandSetSupportExt;
  struct __attribute__((packed)) {
    uint16_t ReservedForDrqTechnicalReport :1;  // [ 0- 0]
    uint16_t WriteReadVerifyEnabled        :1;  // [ 1- 1]
    uint16_t Reserved01                    :11; // [ 2-12]
    uint16_t Reserved1                     :2;  // [13-15]
  } CommandSetActiveExt;
  uint16_t ReservedForExpandedSupportandActive[6];
  struct __attribute__((packed)) {
		uint16_t MsnSupport       :2;               // [ 0- 1]: 0 = Removable Media Status Notification feature set not supported; 1 = Removable Media Status Notification feature set supported; 2-3: Reserved
		uint16_t ReservedWord1274 :14;              // [ 2-15]
	} MsnSupport;
  struct __attribute__((packed)) {
    uint16_t SecuritySupported              :1; // [ 0- 0]: 1 = Secority supported
    uint16_t SecurityEnabled                :1; // [ 1- 1]: 1 = Security enabled
    uint16_t SecurityLocked                 :1; // [ 2- 2]: 1 = Security locked
    uint16_t SecurityFrozen                 :1; // [ 3- 3]: 1 = Security frozen
    uint16_t SecurityCountExpired           :1; // [ 4- 4]: 1 = Security count expired
    uint16_t EnhancedSecurityEraseSupported :1; // [ 5- 5]: 1 = Enhanced security erase supported
    uint16_t Reserved0                      :2; // [ 6- 7]
    uint16_t SecurityLevel                  :1; // [ 8- 8]: 0 = High; 1 = Maximum
    uint16_t Reserved1                      :7; // [ 9-15]
  } SecurityStatus;
  uint16_t VendorSpecific[31];
  struct __attribute__((packed)) {
    uint16_t MaximumCurrentInMA2   :12; // [ 0-11]
    uint16_t CfaPowerMode1Disabled :1;  // [12-12]
    uint16_t CfaPowerMode1Required :1;  // [13-13]
    uint16_t Reserved0             :1;  // [14-14]
    uint16_t Word160Supported      :1;  // [15-15]
  } CfaPowerModel;
  uint16_t ReservedForCfaWord161[8];
  struct __attribute__((packed)) {
    uint16_t SupportsTrim :1;  // [ 0- 0]
    uint16_t Reserved0    :15; // [ 1-15]
  } DataSetManagementFeature;
  uint16_t ReservedForCfaWord170[6];
  uint16_t CurrentMediaSerialNumber[30];
  uint16_t ReservedWord206;
  uint16_t ReservedWord207[2];
  struct __attribute__((packed)) {
    uint16_t AlignmentOfLogicalWithinPhysical :14; // [ 0-13]
    uint16_t Word209Supported                 :1;  // [14-14]
    uint16_t Reserved0                        :1;  // [15-15]
  } BlockAlignment;
  uint16_t WriteReadVerifySectorCountMode3Only[2];
  uint16_t WriteReadVerifySectorCountMode2Only[2];
  struct __attribute__((packed)) {
    uint16_t NVCachePowerModeEnabled  :1; // [ 0- 0]
    uint16_t Reserved0                :3; // [ 1- 3]
    uint16_t NVCacheFeatureSetEnabled :1; // [ 4- 4]
    uint16_t Reserved1                :3; // [ 5- 7]
    uint16_t NVCachePowerModeVersion  :4; // [ 8-11]
    uint16_t NVCacheFeatureSetVersion :4; // [12-15]
  } NVCacheCapabilities;
  uint16_t NVCacheSizeLSW;
  uint16_t NVCacheSizeMSW;
  uint16_t NominalMediaRotationRate;
  uint16_t ReservedWord218;
  struct __attribute__((packed)) {
    uint8_t NVCacheEstimatedTimeToSpinUpInSeconds;
    uint8_t Reserved;
  } NVCacheOptions;
  uint16_t ReservedWord220[35];
  struct __attribute__((packed)) {
		uint16_t Signature :8; // [ 0- 7]
		uint16_t CheckSum  :8; // [ 8-15]
	} Integrity;
} ol_ata_data_identify_device;

typedef struct ol_ata_device_s
{
	uint32_t base;
	ol_ata_type type;
	ol_ata_data_identify_device identifier;
	uint32_t sectorsize;
} ol_ata_device;

void
ol_ata_init(uint32_t, ol_ata_device*);

void
ol_ata_test(ol_ata_device*);

int
ol_ata_sector_read(ol_ata_device*, const uint64_t, const uint32_t, void*);

int
ol_ata_sector_write(ol_ata_device*, const uint64_t, const uint32_t, void*);

#ifdef __cplusplus
}
#endif

#endif // __ATA_H