#include "eos.h"
#include "Services/Http/eosHttpServer.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    text: Text de la solicitut.
///
HttpRequest::HttpRequest(
	const String& text):

	_pHeaders(nullptr) {

	parseText(text);
}


/// ----------------------------------------------------------------------
/// \brief    Constructor copia.
/// \param    other: L'objectre a copiar.
///
HttpRequest::HttpRequest(
	const HttpRequest& other):

	_method(other._method),
	_uri(other._uri) {

}


/// ----------------------------------------------------------------------
/// \brief    Analitza el text de la solicitut.
/// \param    text: El text a analitzar.
///
void HttpRequest::parseText(
	const String &text) {

	uint8_t state = 0;

	unsigned p, l;

	for (int i = 0; i < text.getLength(); i++) {
		char ch = text[i];

		switch (state) {

			// Espera l'inici del method
			//
			case 0:
				if (!isspace(ch)) {
					p =  i;
					l = 1;
					state = 1;
				}
				break;

			// Captura el method
			//
			case 1:
				if (isspace(ch)) {
					_method = String(text, p, l);
					state = 2;
				}
				else
					l++;
				break;

			// Espera l'inici del URI
			//
			case 2:
				if (!isspace(ch)) {
					p = i;
					l = 1;
					state = 3;
				}
				break;

			// Captura el URI
			//
			case 3:
				if (isspace(ch)) {
					_uri = String(text, p, l);
					state = 4;
				}
				else
					l++;
				break;

		    // Espera l'inici dels headers
			//
			case 4:
				if (!isspace(ch)) {
					//_pHeaders = &text[i];
					_headersLength = 1;
					state = 5;
				}
				break;

			case 5:
				_headersLength++;
				break;
		}
	}
}


/// ----------------------------------------------------------------------
/// \brief    Obte el valor d'un header.
/// \param    header: El nom del header.
/// \return   El seu valor.
///
String HttpRequest::getHeader(
	const String& header) const {

	if (_pHeaders != nullptr) {

		uint8_t state = 0;

		const char *pName;
		unsigned nameLength;
		const char *pValue;
		unsigned valueLength;

		for (auto it = _pHeaders; it < _pHeaders + _headersLength; it++) {
			switch (state) {

				// Espara l'inici del nom
			    //
				case 0:
					if (!isspace(*it)) {
						pName = it;
						nameLength = 1;
						state = 1;
					}
					break;

				// Captura el nom
				//
				case 1:
					if (*it == ':') {
						state = 2;
					}
					else
						nameLength++;
					break;

				// Espera l'inici del valor
				//
				case 2:
					if (!isspace(*it)) {
						pValue = it;
						valueLength = 1;
						state = 3;
					}
					break;

				// Captura el valor
				//
				case 3:
					if (!isspace(*it)) {
						state = 4;
					}
					else
						valueLength++;
					break;

				case 4:
					break;
			}
		}
	}

	return "";
}
