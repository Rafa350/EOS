#pragma once
#ifndef __eosCommandLineProcessor__
#define __eosCommandLineProcessor__


// EOS includes
//
#include "eos.h"
#include "eosCallbacks.h"
#include "System/Collections/eosIntrusiveForwardList.h"


namespace eos {

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


#endif // __eosCommandLineProcessor__
