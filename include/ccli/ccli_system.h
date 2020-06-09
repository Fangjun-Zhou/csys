#ifndef CCLI_SYSTEM_H
#define CCLI_SYSTEM_H

#pragma once

#include "ccli_pch.h"
#include "ccli_command.h"
#include "ccli_autocomplete.h"
#include "ccli_history.h"
#include "ccli_command_data.h"

namespace ccli
{
	// TODO: Integrate autocomplete. (Separate variables and their commands)
	// TODO: Add a CommandData Into Registration and return it when parsing.
	// TODO: Use modern pointers.
	// TODO: Logging filters.

	class CCLI_API System
	{
	public:

		///////////////////////////////////////////////////////////////////////
		// System methods /////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////

		void parse(const std::string &line);

		template<typename Fn, typename ...Args>
		void registerCommand(const String &name, const String &description, Fn function, Args... args)
		{
			// Check if function can be called with the given arguments
			static_assert(std::is_invocable_v<Fn, typename Args::ValueType...>, "Arguments specified do not match that of the function");

			// TODO: This should be an exception.
			if (m_CommandContainer.find(name.m_String) != m_CommandContainer.end())
			{
				std::cout << "ERROR: Command already exists." << std::endl;
				return;
			}

			m_SuggestionTree.insert(name.m_String);

			// Add commands to system here
			m_CommandContainer[name.m_String] = new Command<Fn, Args...>(name, description, function, args...);
		}

		template<typename T, typename V>
		void registerVariable(const std::string &name, V &var)
		{
			ccli::System::registerCommand(std::string("set " + name).data(), "Set variable", [&var](T value)
			{ var = value; }, ccli::Arg<T>(name.data()));

			ccli::System::registerCommand(std::string("get " + name).data(), "Get variable", [&]()
			{ m_CommandData.log(LOG) << var << endl; });
		}

		acTernarySearchTree &autocomplete()
		{ return m_SuggestionTree; }

		CommandHistory &history()
		{ return m_CommandHistory; };

		std::vector<CommandItem> &items()
		{ return m_CommandData.items(); }

		CommandData &log(ItemType type = ItemType::LOG)
		{ return m_CommandData.log(type); };

		std::unordered_map<std::string, CommandBase *> commands()
		{ return m_CommandContainer; }

	private:
		std::unordered_map<std::string, CommandBase *> m_CommandContainer;
		acTernarySearchTree m_SuggestionTree;
		CommandHistory m_CommandHistory;
		CommandData m_CommandData;
	};
}

#ifdef CCLI_HEADER_ONLY

#include "ccli_system.inl"

#endif

#endif //CCLI_SYSTEM_H
