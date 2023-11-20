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
    		CommandList& getCommands() {
    			return _commands;
    		}
	};

	class CommandDefinition final {
		private:
			uint32_t _id;
			const char *_cmd;
			const char *_shortDescription;
			const char *_longDescription;

		private:
    		CommandDefinition(const CommandDefinition&) = delete;
    		CommandDefinition& operator = (const CommandDefinition&) = delete;

		public:
			CommandDefinition(uint32_t id, const char *cmd, const char *shortDescription = nullptr, const char *longDescription = nullptr);

			inline uint32_t getID() const { return _id; }
			inline const char *getCmd() const { return _cmd; }
			inline const char *getShortDescription() const { return _shortDescription; }
			inline const char *getLongDescription() const { return _longDescription; }
	};

}
