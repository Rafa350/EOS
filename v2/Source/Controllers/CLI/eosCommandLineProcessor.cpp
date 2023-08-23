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
			command->invoke(text);
			return true;
		}
	}

	return false;
}


CommandDefinition::CommandDefinition(
	const char *cmd,
	const char *shortDescription,
	const char *longDescription,
	ICommandEvent &event) :

	_cmd {cmd},
	_shortDescription {shortDescription},
	_longDescription {longDescription},
	_commandEvent {&event} {

}


void CommandDefinition::invoke(
	const char *text) {

	CommandDefinition::CommandEventArgs args = {
		.command {this},
		.text {text}
	};
	_commandEvent->execute(args);
}
