module;


#include "hardware.h"


export module Eos.Hardware.CAN.__INTERNAL;


import Eos.Types;


export namespace eos::hardware::can::internal {

	constexpr UInt32 absoluteMaxStandardFilters = 28;
	constexpr UInt32 absoluteMaxExtendedFilters = 8;

	// Standard message filter element
	//
	struct SF {
		static constexpr UInt32 SFT_Pos = 30;
		static constexpr UInt32 SFT_Msk = 0b11 << SFT_Pos;

		static constexpr UInt32 SFEC_Pos = 27;
		static constexpr UInt32 SFEC_Msk = 0b111 << SFEC_Pos;

		static constexpr UInt32 SFID1_Pos = 16;
		static constexpr UInt32 SFID1_Msk = 0x7FF << SFID1_Pos;

		static constexpr UInt32 SFID2_Pos = 0;
		static constexpr UInt32 SFID2_Msk = 0x7FF << SFID2_Pos;
	};


	// Extended message filter element
	//
	struct EF0 {
		static constexpr UInt32 EFEC_Pos = 29;
		static constexpr UInt32 EFEC_Msk = 0b111 << EFEC_Pos;

		static constexpr UInt32 EFID1_Pos = 0;
		static constexpr UInt32 EFID1_Msk = 0x1FFFFFFF << EFID1_Pos;
	};

	struct EF1 {
		static constexpr UInt32 EFT_Pos = 30;
		static constexpr UInt32 EFT_Msk = 0b11 << EFT_Pos;

		static constexpr UInt32 EFID2_Pos = 0;
		static constexpr UInt32 EFID2_Msk = 0x1FFFFFFF << EFID2_Pos;
	};


	// Tx buffer element
	//
	struct T0 {
		static constexpr UInt32 ESI_Pos = 31;
		static constexpr UInt32 ESI_Msk = 0b1 << ESI_Pos;

		static constexpr UInt32 XTD_Pos = 30;
		static constexpr UInt32 XTD_Msk = 0b1 << XTD_Pos;

		static constexpr UInt32 RTR_Pos = 29;
		static constexpr UInt32 RTR_Msk = 0b1 << RTR_Pos;

		static constexpr UInt32 SID_Pos = 18;
		static constexpr UInt32 SID_Msk = 0x7FF << SID_Pos;

		static constexpr UInt32 EID_Pos = 0;
		static constexpr UInt32 EID_Msk = 0x1FFFFFFF << EID_Pos;
	};

	struct T1 {
		static constexpr UInt32 MM_Pos = 24;
		static constexpr UInt32 MM_Msk = 0xFF << MM_Pos;

		static constexpr UInt32 EFC_Pos = 23;
		static constexpr UInt32 EFC_Msk = 0b1 << EFC_Pos;

		static constexpr UInt32 FDF_Pos = 21;
		static constexpr UInt32 FDF_Msk = 0b1 << FDF_Pos;

		static constexpr UInt32 BRS_Pos = 20;
		static constexpr UInt32 BRS_Msk = 0b1 << BRS_Pos;

		static constexpr UInt32 DLC_Pos = 16;
		static constexpr UInt32 DLC_Msk = 0b1111 << DLC_Pos;
	};


	// RX Fifo element
	//
	struct R0 {
		static constexpr UInt32 ESI_Pos = 31;
		static constexpr UInt32 ESI_Msk = 0b1 << ESI_Pos;

		static constexpr UInt32 XTD_Pos = 30;
		static constexpr UInt32 XTD_Msk = 0b1 << XTD_Pos;

		static constexpr UInt32 RTR_Pos = 29;
		static constexpr UInt32 RTR_Msk = 0b1 << RTR_Pos;

		static constexpr UInt32 SID_Pos = 18;
		static constexpr UInt32 SID_Msk = 0x7FF << SID_Pos;

		static constexpr UInt32 EID_Pos = 0;
		static constexpr UInt32 EID_Msk = 0x1FFFFFFF << EID_Pos;
	};

	struct R1 {
		static constexpr UInt32 ANMF_Pos = 31;
		static constexpr UInt32 ANMF_Msk = 0b1 << ANMF_Pos;

		static constexpr UInt32 FIDX_Pos = 24;
		static constexpr UInt32 FIDX_Msk = 0x7F << FIDX_Pos;

		static constexpr UInt32 FDF_Pos = 21;
		static constexpr UInt32 FDF_Msk = 0b1 << FDF_Pos;

		static constexpr UInt32 BRS_Pos = 20;
		static constexpr UInt32 BRS_Msk = 0b1 << BRS_Pos;

		static constexpr UInt32 DLC_Pos = 16;
		static constexpr UInt32 DLC_Msk = 0b1111 << DLC_Pos;

		static constexpr UInt32 RXTS_Pos = 0;
		static constexpr UInt32 RXTS_Msk = 0xFFFF << RXTS_Pos;
	};

}
