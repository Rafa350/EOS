#pragma once
#ifndef __eos_canopen_protocols__
#define __eos_canopen_protocols__


namespace eos {

	struct SdoError {
		static constexpr uint32_t none                           = 0;
		static constexpr uint32_t commandSpecifierNotValid       = 0x0504001;
		static constexpr uint32_t unsupportedAccesssToObject     = 0x0601000;
		static constexpr uint32_t attemptToReadWriteOnlyObject   = 0x0601001;
		static constexpr uint32_t attemptToWriteReadOnlyObject   = 0x0601001;
		static constexpr uint32_t objectDoesNotExistInDictionary = 0x0602000;
		static constexpr uint32_t dataTypeDoesNotMatch           = 0x06070010;
	};

	struct SDO0 {

		// Command
		static constexpr uint8_t CCS_Pos      = 5;
		static constexpr uint8_t CCS_Msk      = 0b111 << CCS_Pos;
		static constexpr uint8_t CCS_DNSEG    = 0 << CCS_Pos;
		static constexpr uint8_t CCS_DN       = 1 << CCS_Pos;
		static constexpr uint8_t CCS_UP       = 2 << CCS_Pos;
		static constexpr uint8_t CCS_UPSEG    = 3 << CCS_Pos;
		static constexpr uint8_t CCS_ABORT    = 4 << CCS_Pos;

		// Response
		static constexpr uint8_t SCS_Pos      = 5;
		static constexpr uint8_t SCS_Msk      = 0b111 << SCS_Pos;
		static constexpr uint8_t SCS_ULSEG    = 0 << SCS_Pos;
		static constexpr uint8_t SCS_DLSEG    = 1 << SCS_Pos;
		static constexpr uint8_t SCS_UL       = 2 << SCS_Pos;
		static constexpr uint8_t SCS_DL       = 3 << SCS_Pos;

		// Expedited flag
		static constexpr uint8_t E_Pos        = 1;
		static constexpr uint8_t E_Msk        = 0b1 << E_Pos;
		static constexpr uint8_t E_SEG        = 0 << E_Pos;
		static constexpr uint8_t E_EXP        = 1 << E_Pos;

		// Continue flag
		static constexpr uint8_t C_Pos        = 1;
		static constexpr uint8_t C_Msk        = 0b1 << C_Pos;
		static constexpr uint8_t C_PARTIAL    = 0 << C_Pos;
		static constexpr uint8_t C_LAST       = 1 << C_Pos;

		// Size flag
		static constexpr uint8_t S_Pos        = 0;
		static constexpr uint8_t S_Msk        = 0b1;
		static constexpr uint8_t S_NO         = 0 << S_Pos;
		static constexpr uint8_t S_SIZE       = 1 << S_Pos;

		// Toggle flag
		static constexpr uint8_t T_Pos        = 1;
		static constexpr uint8_t T_Msk        = 0b1;

		// Size
		static constexpr uint8_t SIZE_Pos     = 2;
		static constexpr uint8_t SIZE_Msk     = 0b11 << SIZE_Pos;
		static constexpr uint8_t SIZE_1       = 3 << SIZE_Pos;
		static constexpr uint8_t SIZE_2       = 2 << SIZE_Pos;
		static constexpr uint8_t SIZE_3       = 1 << SIZE_Pos;
		static constexpr uint8_t SIZE_4       = 0 << SIZE_Pos;
	};

	struct COBID {
		static constexpr uint16_t Msk       = 0x7FF;
		static constexpr uint16_t NMT       = 0x000;
		static constexpr uint16_t SDO       = 0x600;
		static constexpr uint16_t SDOr      = 0x580;
		static constexpr uint16_t Heartbeat = 0x700;
		static constexpr uint16_t TPDO1     = 0x180;
		static constexpr uint16_t TPDO2     = 0x280;
		static constexpr uint16_t TPDO3     = 0x380;
		static constexpr uint16_t TPDO4     = 0x480;
		static constexpr uint16_t RPDO1     = 0x200;
		static constexpr uint16_t RPDO2     = 0x300;
		static constexpr uint16_t RPDO3     = 0x400;
		static constexpr uint16_t RPDO4     = 0x500;
		static constexpr uint16_t SYNC      = 0x080;
		static constexpr uint16_t TIME      = 0x100;
	};

	struct NMT0 {
		static constexpr uint8_t CS_Pos    = 0;
		static constexpr uint8_t CS_Msk    = 0xFF << CS_Pos;
		static constexpr uint8_t CS_START  = 0x01 << CS_Pos;
		static constexpr uint8_t CS_STOP   = 0x02 << CS_Pos;
		static constexpr uint8_t CS_PREOP  = 0x80 << CS_Pos;
		static constexpr uint8_t CS_RST    = 0x81 << CS_Pos;
		static constexpr uint8_t CS_RSTCOM = 0x82 << CS_Pos;
	};

}


#endif // __eos_canopen_protocols__

