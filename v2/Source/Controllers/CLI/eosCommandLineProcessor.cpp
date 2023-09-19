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

		if (strcmp(text, command->getCmd()) == 0) {
			if (_commandEventEnabled) {
				CommandEventArgs args = {
					.command = command,
					.text = text
				};
				_commandEvent->execute(this, args);
			}
			return true;
		}
	}

	return false;
}


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

