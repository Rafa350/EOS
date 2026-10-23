export module Eos.Services.CanOpen._Types;


import Eos.Types;


export namespace eos {

    using NodeID = UInt8;

	class CobID {
		public:
			static constexpr UInt16 baseNMT       = 0x000;
			static constexpr UInt16 baseSDO       = 0x600;
			static constexpr UInt16 baseSDOr      = 0x580;
			static constexpr UInt16 baseSYNC      = 0x080;
			static constexpr UInt16 baseTIME      = 0x100;
			static constexpr UInt16 baseHeartbeat = 0x700;
			static constexpr UInt16 baseTPDO1     = 0x180;
			static constexpr UInt16 baseTPDO2     = 0x280;
			static constexpr UInt16 baseTPDO3     = 0x380;
			static constexpr UInt16 baseTPDO4     = 0x480;
			static constexpr UInt16 baseRPDO1     = 0x200;
			static constexpr UInt16 baseRPDO2     = 0x300;
			static constexpr UInt16 baseRPDO3     = 0x400;
			static constexpr UInt16 baseRPDO4     = 0x500;

		private:
			static constexpr UInt16 _nodeIdMask = 0x007F;
			static constexpr UInt16 _cobIdMask = 0x0780;

		private:
			UInt16 _value;

		private:
			constexpr explicit CobID(UInt16 value): _value {(UInt16)(value & 0x7FF)} {}
			constexpr explicit CobID(UInt16 base, NodeID nodeId): _value {(UInt16)((base & _cobIdMask) | (nodeId & _nodeIdMask))} {}

		public:
			inline operator UInt16() const { return value(); }
			inline bool operator == (CobID other) const { return _value == other._value; }
			inline bool operator != (CobID other) const { return _value != other._value; }

			inline UInt16 value() const { return _value; }
			inline UInt16 base() const { return _value & _cobIdMask; }
			inline NodeID nodeId() const { return _value & _nodeIdMask; }

			inline bool isNMT() const { return _value == baseNMT; }
			inline bool isSDO() const { return (_value & _cobIdMask) == baseSDO; }
			inline bool isSYNC() const { return _value == baseSYNC; }
			inline bool isTIME() const { return _value == baseTIME; }
			inline bool isHeartbeat() const { return (_value & _cobIdMask) == baseHeartbeat; }

			static constexpr CobID make(UInt16 value) { return CobID(value); }
			static constexpr CobID make(UInt16 base, NodeID nodeId) { return CobID(base, nodeId); }

			static constexpr CobID makeNMT() { return CobID(baseNMT); }
			static constexpr CobID makeSDO(NodeID nodeId) { return CobID(baseSDO, nodeId); }
			static constexpr CobID makeSYNC() { return CobID(baseSYNC); }
			static constexpr CobID makeTIME() { return CobID(baseTIME); }
			static constexpr CobID makeHeartbeat(NodeID nodeId) { return CobID(baseHeartbeat, nodeId); }

			static constexpr NodeID getNodeID(UInt16 cobId) { return cobId & _nodeIdMask; }
	};
}
