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

	enum class SdoCCS: UInt8 { // Client command specification
		downloadSegment  = 0,
		initiateDownload = 1,
		initiateUpload   = 2,
		uploadSegment    = 3,
		abort            = 4
	};

	enum class SdoSCS: UInt8 { // Server command specitifacion
		uploadSegment    = 0,
		downloadSegment  = 1,
		initiateUpload   = 2,
		initiateDownload = 3,
		abort            = 4
	};

	enum class SdoCS: UInt8 { // Client/Server command specification
		abort = 4
	};

	// Client --> Server: Peticio 'SDO Download Initiate'
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

	// Server --> Client: Resposta 'SDO Download initiate'.
	//
	struct __attribute__((packed)) SdoDownloadInitiateResponse {
		UInt8  x   : 5;     // Reservats (Sempre 0)
		SdoSCS scs : 3;     // SdoSCS::initiateDownload (3)
		UInt16 index;
		UInt8  subIndex;
		UInt8  reserved[4]; // Reservats (sempre 0)
	};

	// Client --> Server: Peticio 'SDO Download Segment'
	//
	struct __attribute__((packed)) SdoDownloadSegmentRequest {

	};

	// Server --> Client: Resposta 'SDO Download Segment'
	//
	struct __attribute__((packed)) SdoDownloadSegmentResponse {

	};

	// Server/Client --> Client/Server: 'Abort'
	//
	struct __attribute__((packed)) SdoAbortRequest {
		UInt8    x  : 5;    // Reservats (Sempre 0)
		SdoCS    cs : 3;    // SdoCS::Abort (4)
		UInt16   index;     // Index
		UInt8    subIndex;  // Subindex
		SdoError errorCode; // Codi d'error
	};

	// Client -> Server: Capcelera de solicitut
	//
	struct __attribute__((packed)) SdoRequestHeader {
		UInt8  x   : 5;      // Reservats (Sempre 0)
		SdoCCS ccs : 3;      // Client command specifier
		UInt8  reserverd[7];
	};

	// Server -> Client: Capcelera de resposta
	//
	struct __attribute__((packed)) SdoResponseHeader {
		UInt8  x   : 5;      // Reservats (Sempre 0)
		SdoSCS scs : 3;      // Server command specifier
		UInt8  reserverd[7];
	};

	union SdoFrame {
		UInt8 raw[8];
		SdoRequestHeader requestHeader;
		SdoResponseHeader responseHeader;
		SdoDownloadInitiateRequest downloadInitiateRequest;
		SdoDownloadInitiateResponse downloadInitiatResponse;
		SdoDownloadSegmentRequest downloadSegmentRequest;
		SdoDownloadSegmentResponse downloadSegmentResponse;
		SdoAbortRequest abortRequest;
	};

	static_assert(sizeof(SdoFrame) == 8, "La trama SDO ha de fer 8 bytes");
}
