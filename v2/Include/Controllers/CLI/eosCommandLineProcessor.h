#pragma once
#ifndef __eosCommandLineProcessor__
#define __eosCommandLineProcessor__


// EOS includes
//
#include "eos.h"
#include "System/eosEvents.h"
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
				const CommandDefinition *command;
				const char *text;
			};
			using CommandEventRaiser = EventRaiser<CommandID, CommandEventArgs>;
			using ICommandEvent = CommandEventRaiser::IEvent;
			template <typename Instance_> using CommandEvent = CommandEventRaiser::Event<Instance_>;

		private:
    		CommandDefinitionList _commands;
    		CommandEventRaiser _erCommand;

		public:
    		CommandLineProcessor();

    		inline void setCommandEvent(ICommandEvent &event, bool enabled = true) {
    			_erCommand.set(event, enabled);
    		}
    		inline void enableCommandEvent() {
    			_erCommand.enable();
    		}
    		inline void disableCommandEvent() {
    			_erCommand.disable();
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
