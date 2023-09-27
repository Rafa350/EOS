#include "eos.h"
#include "Controllers/CLI/eosCommandLineProcessor.h"


using namespace eos;


/// ----------------------------------------------------------------------
/// \brief    Constructor de l'objecte.
///
CommandLineProcessor::CommandLineProcessor() {

}


/// ----------------------------------------------------------------------
/// \brief    Registra una comanda.
/// \param    command: La comanda a registrar
///
void CommandLineProcessor::addCommand(
	CommandDefinition *command) {

	_commands.pushBack(command);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la linia de comanda.
/// \param    text: El text de la linia de comanda.
/// \return   True si tot es correcte.
///
bool CommandLineProcessor::process(
	const char *text) {

	for (auto command: _commands) {

		const char *pc = command->getCmd();
		const char *pt = text;

		while ((*pc == *pt) && (*pc != '\0') && (*pt != '\0')) {
			pc++;
			pt++;
		}
		if ((*pc == '\0') && ((*pt == '\0') || (*pt == ' ') || (*pt == '\t'))) {

			if (_commandEventEnabled) {

				while ((*pt == ' ') || (*pt == '\t'))
					pt++;

				CommandEventArgs args = {
					.command = command,
					.text = pt
				};
				_commandEvent->execute(this, args);
			}
			return true;
		}
	}

	return false;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    id: Identificador de la comanda.
/// \param    cmd: Text de la comanda.
/// \param    shortDescription: Descripcio curta.
/// \param    longDescription: Descripcio llarga.
///
CommandDefinition::CommandDefinition(
	uint32_t id,
	const char *cmd,
	const char *shortDescription,
	const char *longDescription) :

	_id {id},
	_cmd {cmd},
	_shortDescription {shortDescription},
	_longDescription {longDescription} {

}

