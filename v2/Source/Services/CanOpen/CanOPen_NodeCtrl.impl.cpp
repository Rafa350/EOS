module Eos.Services.CanOpen;


using namespace eos;


/// ----------------------------------------------------------------------
/// @brief    Posa un node en estat 'operational'.
/// @param    nodeId: Node destinatari.
/// @param    blockTime: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
StdResult CanOpenService::start(
	NodeID nodeId,
	Ticks blockTime) {

	// Comprova que de veritat sigui un node remot
	//
	if (nodeId == _nodeId)
		return StdErrorCode::errorParameter;

	// Emet la comanda NMT Start
	//
	UInt8 data[2];
	data[0] = 0x01;
	data[1] = nodeId;

	return postMessage_TransmitFrame(
		CobID::makeNMT(),
		data,
		sizeof(data),
		blockTime);
}


/// ----------------------------------------------------------------------
/// @brief    Posar un node en estat 'stoped'
/// @param    nodeId: Node destinatati
/// @param    blockTime: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
///
StdResult CanOpenService::stop(
	NodeID nodeId,
	Ticks blockTime) {

	// Comprova que de veritat sigui un node remot
	//
	if (nodeId == _nodeId)
		return StdErrorCode::errorParameter;

	// Emet la comanda NMT Stop
	//
	UInt8 data[2];
	data[0] = 0x02;
	data[1] = nodeId;

	return postMessage_TransmitFrame(
		CobID::makeNMT(),
		data,
		sizeof(data),
		blockTime);
}


/// ----------------------------------------------------------------------
/// @brief    Posar un node en estat 'pre-operational'.
/// @param    nodeId: Node destinatati
/// @param    blockTime: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
StdResult CanOpenService::enterPreOperational(
	NodeID nodeId,
	Ticks blockTime) {

	// Comprova que de veritat sigui un node remot
	//
	if (nodeId == _nodeId)
		return StdErrorCode::errorParameter;

	// Emet la comanda NMT Enter Pre-Operational
	//
	UInt8 data[2];
	data[0] = 0x80;
	data[1] = nodeId;

	return postMessage_TransmitFrame(
		CobID::makeNMT(),
		data,
		sizeof(data),
		blockTime);
}


/// ----------------------------------------------------------------------
/// @brief    Reseteja un node..
/// @param    nodeId: Node destinatati
/// @param    blockTime: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
StdResult eos::CanOpenService::resetNode(
	NodeID nodeId,
	Ticks blockTime) {

	// Comprova que de veritat sigui un node remot
	//
	if (nodeId == _nodeId)
		return StdErrorCode::errorParameter;

	// Emet la comanda NMT Reset Node
	//
	UInt8 data[2];
	data[0] = 0x81;
	data[1] = nodeId;

	return postMessage_TransmitFrame(
		CobID::makeNMT(),
		data,
		sizeof(data),
		blockTime);
}


/// ----------------------------------------------------------------------
/// @brief    Reseteja les comunicacions d'un node.
/// @param    nodeId: Node destinatati
/// @param    blockTime: El temps maxim d'espera.
/// \return   El resultat de l'operacio.
/// \remarks  L'ordre es posa en cua per execucio posterior.
///
StdResult CanOpenService::resetCommunication(
	NodeID nodeId,
	Ticks blockTime) {

	// Comprova que de veritat sigui un node remot
	//
	if (nodeId == _nodeId)
		return StdErrorCode::errorParameter;

	// Emet la comanda NMT Rerset Comunication
	//
	UInt8 data[2];
	data[0] = 0x82;
	data[1] = nodeId;

	return postMessage_TransmitFrame(
		CobID::makeNMT(),
		data,
		sizeof(data),
		blockTime);
}
