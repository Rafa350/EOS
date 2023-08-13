#pragma once
#ifndef __eosCommandLineProcessor__
#define __eosCommandLineProcessor__


#include "eos.h"
#include "System/eosCallbacks.h"
#include "System/Collections/eosList.h"


namespace eos {

	class CommandDefinition;

	class CommandLineProcessor final {
		private:
    		using CommandList = eos::List<CommandDefinition*>;

		private:
    		CommandList _commands;

		public:
    		CommandLineProcessor();
    		void addCommand(CommandDefinition *definition);
    		bool process(const char *buffer);
	};

	class CommandDefinition final {
		public:
			struct CommandEventArgs {
				const CommandDefinition *command;
				const char *text;
			};
			using ICommandEvent = eos::ICallbackP1<const CommandEventArgs&>;
			template <typename _instance> using CommandEvent = eos::CallbackP1<_instance, const CommandEventArgs&>;

		private:
			const char *_cmd;
			const char *_shortDescription;
			const char *_longDescription;
			ICommandEvent *_commandEvent;

		private:
    		CommandDefinition(const CommandDefinition&) = delete;
    		CommandDefinition& operator = (const CommandDefinition&) = delete;

		public:
			CommandDefinition(const char *cmd, const char *shortDescription, const char *longDescription, ICommandEvent &event);

			inline const char *getCmd() const { return _cmd; }
			inline const char *getShortDescription() const { return _shortDescription; }
			inline const char *getLongDescription() const { return _longDescription; }
			void invoke(const char *text);
	};

}


#endif // __eosCOmmandLineProcessor__

