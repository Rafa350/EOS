export module Eos.Services.CanOpen.Protocol;

import Eos.Types;


export namespace eos {

	struct SdoError {
		static constexpr UInt32 none                           = 0;
		static constexpr UInt32 commandSpecifierNotValid       = 0x0504001;
		static constexpr UInt32 unsupportedAccesssToObject     = 0x0601000;
		static constexpr UInt32 attemptToReadWriteOnlyObject   = 0x0601001;
		static constexpr UInt32 attemptToWriteReadOnlyObject   = 0x0601001;
		static constexpr UInt32 objectDoesNotExistInDictionary = 0x0602000;
		static constexpr UInt32 dataTypeDoesNotMatch           = 0x0607010;
	};

	struct SDO0 {

		// Command
		static constexpr UInt8 CCS_Pos      = 5;
		static constexpr UInt8 CCS_Msk      = 0b111 << CCS_Pos;
		static constexpr UInt8 CCS_DNSEG    = 0 << CCS_Pos;
		static constexpr UInt8 CCS_DN       = 1 << CCS_Pos;
		static constexpr UInt8 CCS_UP       = 2 << CCS_Pos;
		static constexpr UInt8 CCS_UPSEG    = 3 << CCS_Pos;
		static constexpr UInt8 CCS_ABORT    = 4 << CCS_Pos;

		// Response
		static constexpr UInt8 SCS_Pos      = 5;
		static constexpr UInt8 SCS_Msk      = 0b111 << SCS_Pos;
		static constexpr UInt8 SCS_ULSEG    = 0 << SCS_Pos;
		static constexpr UInt8 SCS_DLSEG    = 1 << SCS_Pos;
		static constexpr UInt8 SCS_UL       = 2 << SCS_Pos;
		static constexpr UInt8 SCS_DL       = 3 << SCS_Pos;

		// Expedited flag
		static constexpr UInt8 E_Pos        = 1;
		static constexpr UInt8 E_Msk        = 0b1 << E_Pos;
		static constexpr UInt8 E_SEG        = 0 << E_Pos;
		static constexpr UInt8 E_EXP        = 1 << E_Pos;

		// Continue flag
		static constexpr UInt8 C_Pos        = 1;
		static constexpr UInt8 C_Msk        = 0b1 << C_Pos;
		static constexpr UInt8 C_PARTIAL    = 0 << C_Pos;
		static constexpr UInt8 C_LAST       = 1 << C_Pos;

		// Size flag
		static constexpr UInt8 S_Pos        = 0;
		static constexpr UInt8 S_Msk        = 0b1;
		static constexpr UInt8 S_NO         = 0 << S_Pos;
		static constexpr UInt8 S_SIZE       = 1 << S_Pos;

		// Toggle flag
		static constexpr UInt8 T_Pos        = 1;
		static constexpr UInt8 T_Msk        = 0b1;

		// Size
		static constexpr UInt8 SIZE_Pos     = 2;
		static constexpr UInt8 SIZE_Msk     = 0b11 << SIZE_Pos;
		static constexpr UInt8 SIZE_1       = 3 << SIZE_Pos;
		static constexpr UInt8 SIZE_2       = 2 << SIZE_Pos;
		static constexpr UInt8 SIZE_3       = 1 << SIZE_Pos;
		static constexpr UInt8 SIZE_4       = 0 << SIZE_Pos;
	};

	struct COBID {
		static constexpr UInt16 Msk       = 0x7FF;
		static constexpr UInt16 NMT       = 0x000;
		static constexpr UInt16 SDO       = 0x600;
		static constexpr UInt16 SDOr      = 0x580;
		static constexpr UInt16 Heartbeat = 0x700;
		static constexpr UInt16 TPDO1     = 0x180;
		static constexpr UInt16 TPDO2     = 0x280;
		static constexpr UInt16 TPDO3     = 0x380;
		static constexpr UInt16 TPDO4     = 0x480;
		static constexpr UInt16 RPDO1     = 0x200;
		static constexpr UInt16 RPDO2     = 0x300;
		static constexpr UInt16 RPDO3     = 0x400;
		static constexpr UInt16 RPDO4     = 0x500;
		static constexpr UInt16 SYNC      = 0x080;
		static constexpr UInt16 TIME      = 0x100;
	};

	struct NMT0 {
		static constexpr UInt8 CS_Pos    = 0;
		static constexpr UInt8 CS_Msk    = 0xFF << CS_Pos;
		static constexpr UInt8 CS_START  = 0x01 << CS_Pos;
		static constexpr UInt8 CS_STOP   = 0x02 << CS_Pos;
		static constexpr UInt8 CS_PREOP  = 0x80 << CS_Pos;
		static constexpr UInt8 CS_RST    = 0x81 << CS_Pos;
		static constexpr UInt8 CS_RSTCOM = 0x82 << CS_Pos;
	};

}
