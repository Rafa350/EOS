#include "eos.h"
#include "Services/Http/eosHttpServer.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor del objecte.
/// \param    data: Dades de la solicitut.
///
HttpRequest::HttpRequest(
	const String& data) {

	parseData(data);
}


/// ----------------------------------------------------------------------
/// \brief    Analitza les dades de la solicitut.
/// \param    data: Les dades a analitzar.
///
void HttpRequest::parseData(
	const String& data) {

	uint8_t state = 0;
	for (auto it = data.begin(); it != data.end(); it++) {
		switch (state) {

			// Espera l'inici del verb
			//
			case 0:
				if (!isspace(*it)) {
					pVerb = it;
					verbLength = 1;
					state = 1;
				}
				break;

			// Captura el verb
			//
			case 1:
				if (isspace(*it))
					state = 2;
				else
					verbLength++;
				break;

			// Espera l'inici del URI
			//
			case 2:
				if (!isspace(*it)) {
					pUri = it;
					uriLength = 1;
					state = 3;
				}
				break;

			// Captura el URI
			//
			case 3:
				if (isspace(*it))
					state = 4;
				else
					uriLength++;
				break;

			case 4:
				break;
		}
	}
}
