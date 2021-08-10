#include "eos.h"
#include "Services/Http/eosHttpServer.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
/// \param    method: Metode per procesar.
/// \param    callback: Funcio per procesar el metode.
///
HttpController::HttpController(
	const String& method,
	ICallback* callback):

	_method(method),
	_callback(callback) {
}


/// ----------------------------------------------------------------------
/// \brief    Verifica si el controlador pot procesar el metode de la
///           solicitut.
/// \param    request: La soliditut.
/// \return   True si pot procesar la solicitut.
///
bool HttpController::canProcess(
	const HttpRequest& request) const {

	return _method == request.getMethod();
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la solicitut.
/// \param    request: La solicitut.
///
HttpResponse HttpController::process(
	const HttpRequest& request) {

	if (_callback != nullptr)
		return _callback->execute(request);
	else
		return HttpResponse(400, "Error", "");
}
