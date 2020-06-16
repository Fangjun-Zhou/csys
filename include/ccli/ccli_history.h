#ifndef CCLI_HISTORY_H
#define CCLI_HISTORY_H
#pragma once

#include "ccli_pch.h"
#include "ccli_api.h"

namespace ccli
{
	class CCLI_API CommandHistory
	{
	public:

		/*!
		 * \brief Command history constructor.
		 * \param maxRecord Maximum amount of command strings to keep track at once.
		 */
		explicit CommandHistory(unsigned int maxRecord = 100);

		/*!
		 * \brief Record command string. (Start at the beginning once end is reached).
		 * \param line Command string to be recorded.
		 */
		void push_back(const std::string & line);

		/*!
		 * \brief Get newest register command entry index
		 * \return Newest command entry index
		 */
		[[nodiscard]] unsigned int get_new_index() const;

		/*!
		 * \brief Get newest register command entry
		 * \return Newest command entry
		 */
		const std::string & get_new();

		/*!
		 * \brief Get oldest register command entry index
		 * \return Oldest command entry index
		 */
		[[nodiscard]] unsigned int get_old_index() const;

		/*!
		 * \brief Get oldest register command entry
		 * \return Oldest command entry string
		 */
		const std::string & get_old();

		/*!
		 * \brief Clear command history
		 */
		void clear();

		/*!
		 * \brief Retrieve command history at given index
		 * \param index Position to lookup in command history vector
		 * \return Command at given index
		 *
		 * \note No bound checking is performed when accessing with these index operator.
		 *  Use the *index()* method for safe history vector indexing.
		 */
		const std::string &operator[](size_t index);

		/*!
		 * \brief Output available command history.
		 * \param os Output stream
		 * \param history Reference to history to be printed
		 * \return Reference to history to be printed
		 */
		friend std::ostream &operator<<(std::ostream &os, const CommandHistory &history);

		/*!
		 * \return Number of registered commands.
		 */
		size_t size();

		/*!
		 * \return Maximum commands that are able to be recorded
		 */
		size_t capacity();

	private:
		unsigned int m_Record;				//!< Amount of commands recorded
		unsigned int m_MaxRecord;			//!< Maximum command record to keep track of
		std::vector<std::string> m_History; //!< Console command history TODO: Check if this should be a poitner to a vector.
	};
}

#ifdef CCLI_HEADER_ONLY
#include "ccli_history.inl"
#endif

#endif //CCLI_HISTORY_H
