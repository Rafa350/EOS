export module Eos.Services.CanOpen.SDOCommon;

import Eos.Types;


export namespace eos {

	enum class SdoError: UInt32 {
		none                           = 0,
		commandSpecifierNotValid       = 0x0504001,
		unsupportedAccesssToObject     = 0x0601000,
		attemptToReadWriteOnlyObject   = 0x0601001,
		attemptToWriteReadOnlyObject   = 0x0601001,
		objectDoesNotExistInDictionary = 0x0602000,
		dataTypeDoesNotMatch           = 0x0607010
	};

	enum class SdoCCS: UInt8 {
		downloadSegment  = 0,
		initiateDownload = 1,
		initiateUpload   = 2,
		uploadSegment    = 3,
		abort            = 4
	};

	enum class SdoSCS: UInt8 {
		uploadSegment    = 0,
		downloadSegment  = 1,
		initiateUpload   = 2,
		initiateDownload = 3,
		abort            = 4
	};

	enum class SdoCS: UInt8 {
		abort = 4
	};

	// Client -> Server: Peticio d'escriptura (Download Request)
	//
	struct  __attribute__((packed)) SdoDownloadInitiateRequest {
		bool   withSize    : 1; // True si incorpora el tamany
		bool   expedited   : 1; // True si es expedited
		UInt8  unusedBytes : 2; // Nombre de bites no utilitzats
		UInt8  x           : 1; // Reservat (Sempre 0)
		SdoCCS ccs         : 3; // SdoCCS::initiateDownload
		UInt16 index;           // Index
		UInt8  subIndex;        // subindex
		UInt8  data[4];         // Dades
	};

	// Server -> Client: Confirmació d'escriptura (Download Response)
	//
	struct __attribute__((packed)) SdoDownloadInitiateResponse {
		UInt8  x   : 5;     // Reservats (Sempre 0)
		SdoSCS scs : 3;     // SdoSCS::initiateDownload (3)
		UInt16 index;
		UInt8  subIndex;
		UInt8  reserved[4]; // Reservats (sempre 0)
	};

	// Abort
	//
	struct __attribute__((packed)) SdoAbort {
		UInt8    x  : 5;    // Reservats (Sempre 0)
		SdoCS    cs : 3;    // SdoCS::Abort (4)
		UInt16   index;     // Index
		UInt8    subIndex;  // Subindex
		SdoError errorCode; // Codi d'error
	};

	union SdoFrame {
		UInt8 raw[8];
		SdoDownloadInitiateRequest downloadRequest;
		SdoDownloadInitiateResponse downloadResponse;
		SdoAbort abort;
	};

	static_assert(sizeof(SdoFrame) == 8, "La trama SDO ha de fer 8 bytes");
}
