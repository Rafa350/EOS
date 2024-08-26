#pragma once


// EOS includes
//
#include "eos.h"
#include "System/eosCallbacks.h"

// STL includes
//
#include <forward_list>


namespace eos {

	class CommandDefinition;

	class CommandLineProcessor final {
		public:
    		using CommandList = std::forward_list<CommandDefinition*>;

		public:
			struct CommandEventArgs {
				const CommandDefinition *command;
				const char *text;
			};
			using ICommandEvent = eos::ICallbackP2<CommandLineProcessor *, const CommandEventArgs&>;
			template <typename Instance_> using CommandEvent = eos::CallbackP2<Instance_, CommandLineProcessor*, const CommandEventArgs&>;

		private:
    		CommandList _commands;
    		ICommandEvent *_commandEvent;
    		bool _commandEventEnabled;

		public:
    		CommandLineProcessor();

    		void setCommandEvent(ICommandEvent &event, bool enabled = true) {
    			_commandEvent = &event;
    			_commandEventEnabled = enabled;
    		}
    		void enableCommandEvent() {
    			_commandEventEnabled = _commandEvent != nullptr;
    		}
    		void disableCommandEvent() {
    			_commandEventEnabled = false;
    		}
    		void addCommand(CommandDefinition *definition);

    		bool process(const char *buffer);

    		inline CommandList& getCommands() { return _commands; }
	};

	struct CommandDefinitionInfo {
		unsigned id;
		const char *cmd;
		const char *shortDescription;
		const char *longDescription;
	};

	class CommandDefinition final {
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
