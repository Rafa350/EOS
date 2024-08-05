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

	_commands.push_front(command);
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
/// \param    info: Definicio de la comanda.
///
CommandDefinition::CommandDefinition(
	const CommandDefinitionInfo &info):
	_info {&info} {

}

