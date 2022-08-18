#include "eos.h"
#include "Services/Http/eosHttpServer.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor per defecte. Genera una resposta 500
///
HttpResponse::HttpResponse():

	_statusCode(500),
	_statusMessage("Internal Server Error.") {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor
/// \param    statusCode: Codi de la resposta.
/// \param    statusMessage: Missatge de la resposta.
/// \param    body: Text de la resposta.
///
HttpResponse::HttpResponse(
	unsigned statusCode,
	const String &statusMessage,
	const String &body):

	_statusCode(statusCode),
	_statusMessage(statusMessage),
	_body(body) {

}


/// ----------------------------------------------------------------------
/// \brief    Constructor de copia.
/// \param    other: L'altre objecte a copiar.
///
HttpResponse::HttpResponse(
	const HttpResponse &other):

	_statusCode(other._statusCode),
	_statusMessage(other._statusMessage),
	_body(other._body) {

}


String HttpResponse::printText() const {

	StringBuilder sb;

	sb.append("HTTP/1.1 ");
	sb.append(_statusCode);
	sb.append(' ');
	sb.append(_statusMessage);
	sb.append("\r\n");

	sb.append("Content-Length: ");
	sb.append(_body.getLength());
	sb.append("\r\n");
	sb.append("Content-Type: text/plain;charset=utf-8\r\n");
	sb.append("\r\n");

	sb.append(_body);

	return sb;
}


String HttpResponse::getText() const {

	return printText();
}
