module;


#include "eos.h"
#include "eosEvents.h"


export module Eos.Controllers.CLI;


import Eos.System.Collections.IntrusiveForwardList;


export namespace eos {

	class CommandDefinition;

    using CommandDefinitionList = IntrusiveForwardList<CommandDefinition, 1>;
    using CommandDefinitionListNode = IntrusiveForwardListNode<CommandDefinition, 1>;

	class CommandLineProcessor final {
		public:
    		enum class CommandID {
    			command
    		};
			struct CommandEventArgs {
    			CommandID const id;
				const CommandDefinition *command;
				const char *text;
			};
			using ICommandEvent = ICallbackP2<CommandLineProcessor*, CommandEventArgs*>;
			template <typename Instance_> using CommandEvent = CallbackP2<Instance_, CommandLineProcessor*, CommandEventArgs*>;

		private:
    		CommandDefinitionList _commands;
    		ICommandEvent *_commandEvent;

		public:
    		CommandLineProcessor();

    		inline void enableCommandEvent(ICommandEvent &event) {
    			_commandEvent = &event;
    		}
    		inline void disableCommandEvent() {
    			_commandEvent = nullptr;
    		}
    		void addCommand(CommandDefinition *definition);

    		const CommandDefinition *process(const char *buffer);

    		inline CommandDefinitionList& getCommands() { return _commands; }
	};

	struct CommandDefinitionInfo {
		unsigned id;
		const char *cmd;
		const char *shortDescription;
		const char *longDescription;
	};

	class CommandDefinition final: public CommandDefinitionListNode {
		private:
			const CommandDefinitionInfo *_info;

		private:
    		CommandDefinition(const CommandDefinition&) = delete;
    		CommandDefinition& operator = (const CommandDefinition&) = delete;

		public:
			CommandDefinition(const CommandDefinitionInfo &info);

			inline unsigned getID() const { return _info->id; }
			inline const char *getCmd() const { return _info->cmd; }
			inline const char *getShortDescription() const { return _info->shortDescription; }
			inline const char *getLongDescription() const { return _info->longDescription; }
	};

}


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

	_commands.pushFront(command);
}


/// ----------------------------------------------------------------------
/// \brief    Procesa la linia de comanda.
/// \param    text: El text de la linia de comanda.
/// \return   La comanda a procesar. nullptr si no hi ha cap.
///
const CommandDefinition *CommandLineProcessor::process(
	const char *text) {

	for (auto command: _commands) {

		const char *pc = command->getCmd();
		const char *pt = text;

		while ((*pc == *pt) && (*pc != '\0') && (*pt != '\0')) {
			pc++;
			pt++;
		}

		if ((*pc == '\0') && ((*pt == '\0') || (*pt == ' ') || (*pt == '\t'))) {

			if (_commandEvent != nullptr) {

				while ((*pt == ' ') || (*pt == '\t'))
					pt++;

				CommandEventArgs args = {
					.id = CommandID::command,
					.command = command,
					.text = pt
				};
				_commandEvent->execute(this, &args);
			}
			return command;
		}
	}

	return nullptr;
}


/// ----------------------------------------------------------------------
/// \brief    Constructor.
/// \param    info: Definicio de la comanda.
///
CommandDefinition::CommandDefinition(
	const CommandDefinitionInfo &info):
	_info {&info} {

}
