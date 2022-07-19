#pragma once

// Copyright (C) 2006, 2009 Marcin Kalicinski
// Copyright (C) 2022 Jasper Drescher
// Version 1.15
// Revision 2022/07/19
//! \file rapidxml_utils.hpp This file contains high-level rapidxml utilities that can be useful
//! in certain simple scenarios. They should probably not be used if maximizing performance is the main objective.

#include "rapidxml.hpp"

#include <fstream>
#include <stdexcept>
#include <vector>

namespace rapidxml
{
	//! Represents data loaded from a file
	template<class Ch = char>
	class file
	{
	public:
		//! Loads file into the memory. Data will be automatically destroyed by the destructor.
		//! \param filename Filename to load.
		file(const char* filename)
		{
			// Open stream
			std::basic_ifstream<Ch> stream(filename, std::ios::binary);
			if (!stream)
				throw std::runtime_error(std::string("cannot open file ") + filename);
			stream.unsetf(std::ios::skipws);

			// Determine stream size
			stream.seekg(0, std::ios::end);
			size_t size = stream.tellg();
			stream.seekg(0);

			// Load data and add terminating 0
			m_data.resize(size + 1);
			stream.read(&m_data.front(), static_cast<std::streamsize>(size));
			m_data[size] = 0;
		}

		//! Loads file into the memory. Data will be automatically destroyed by the destructor
		//! \param stream Stream to load from
		file(std::basic_istream<Ch>& stream)
		{
			// Load data and add terminating 0
			stream.unsetf(std::ios::skipws);
			m_data.assign(std::istreambuf_iterator<Ch>(stream), std::istreambuf_iterator<Ch>());
			if (stream.fail() || stream.bad())
				throw std::runtime_error("error reading stream");
			m_data.push_back(0);
		}

		//! Gets file data.
		//! \return Pointer to data of file.
		Ch* data()
		{
			return &m_data.front();
		}

		//! Gets file data.
		//! \return Pointer to data of file.
		const Ch* data() const
		{
			return &m_data.front();
		}

		//! Gets file data size.
		//! \return Size of file data, in characters.
		[[nodiscard]] std::size_t size() const
		{
			return m_data.size();
		}

	private:
		std::vector<Ch> m_data; // File data
	};

	//! Counts children of node. Time complexity is O(n).
	//! \return Number of children of node
	template<class Ch>
	std::size_t count_children(xml_node<Ch>* node)
	{
		xml_node<Ch>* child = node->first_node();
		std::size_t count = 0;
		while (child)
		{
			++count;
			child = child->next_sibling();
		}

		return count;
	}

	//! Counts attributes of node. Time complexity is O(n).
	//! \return Number of attributes of node
	template<class Ch>
	std::size_t count_attributes(xml_node<Ch>* node)
	{
		xml_attribute<Ch>* attr = node->first_attribute();
		std::size_t count = 0;
		while (attr)
		{
			++count;
			attr = attr->next_attribute();
		}

		return count;
	}
}
