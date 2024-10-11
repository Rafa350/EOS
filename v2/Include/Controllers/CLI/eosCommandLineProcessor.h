#pragma once
#ifndef __eosCommandLineProcessor__
#define __eosCommandLineProcessor__


// EOS includes
//
#include "eos.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosIntrusiveForwardList.h"


namespace eos {

	class CommandDefinition;

    using CommandDefinitionList = IntrusiveForwardList<CommandDefinition, 1>;
    using CommandDefinitionListNode = IntrusiveForwardListNode<CommandDefinition, 1>;

	class CommandLineProcessor final {
		public:
			struct CommandEventArgs {
				const CommandDefinition *command;
				const char *text;
			};
			using ICommandEvent = eos::ICallbackP2<const CommandLineProcessor *, const CommandEventArgs&>;
			template <typename Instance_> using CommandEvent = eos::CallbackP2<Instance_, const CommandLineProcessor*, const CommandEventArgs&>;

		private:
    		CommandDefinitionList _commands;
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

    		const CommandDefinition *process(const char *buffer) const;

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


#endif // __eosCOmmandLineProcessor__
