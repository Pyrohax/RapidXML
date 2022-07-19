#pragma once

// Copyright (C) 2006, 2009 Marcin Kalicinski
// Copyright (C) 2022 Jasper Drescher
// Version 1.15
// Revision 2022/07/19
//! \file rapidxml_iterators.hpp This file contains rapidxml iterators

#include "rapidxml.hpp"

namespace rapidxml
{
	//! Iterator of child nodes of xml_node
	template<class Ch>
	class node_iterator
	{
	public:
		using value_type = xml_node<Ch>;
		using reference = xml_node<Ch>&;
		using pointer = xml_node<Ch>*;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::bidirectional_iterator_tag;

		node_iterator()
			: m_node(nullptr) {}

		node_iterator(xml_node<Ch>* node)
			: m_node(node->first_node()) {}

		reference operator *() const
		{
			assert(m_node);
			return *m_node;
		}

		pointer operator->() const
		{
			assert(m_node);
			return m_node;
		}

		node_iterator& operator++()
		{
			assert(m_node);
			m_node = m_node->next_sibling();
			return *this;
		}

		node_iterator operator++(int)
		{
			node_iterator tmp = *this;
			++this;
			return tmp;
		}

		node_iterator& operator--()
		{
			assert(m_node && m_node->previous_sibling());
			m_node = m_node->previous_sibling();
			return *this;
		}

		node_iterator operator--(int)
		{
			node_iterator tmp = *this;
			++this;
			return tmp;
		}

		bool operator ==(const node_iterator<Ch>& rhs)
		{
			return m_node == rhs.m_node;
		}

		bool operator !=(const node_iterator<Ch>& rhs)
		{
			return m_node != rhs.m_node;
		}

	private:
		xml_node<Ch>* m_node;
	};

	//! Iterator of child attributes of xml_node
	template<class Ch>
	class attribute_iterator
	{
	public:
		using value_type = xml_attribute<Ch>;
		using reference = xml_attribute<Ch>&;
		using pointer = xml_attribute<Ch>*;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::bidirectional_iterator_tag;

		attribute_iterator()
			: m_attribute(nullptr) {}

		attribute_iterator(xml_node<Ch>* node)
			: m_attribute(node->first_attribute()) {}

		reference operator *() const
		{
			assert(m_attribute);
			return *m_attribute;
		}

		pointer operator->() const
		{
			assert(m_attribute);
			return m_attribute;
		}

		attribute_iterator& operator++()
		{
			assert(m_attribute);
			m_attribute = m_attribute->next_attribute();
			return *this;
		}

		attribute_iterator operator++(int)
		{
			attribute_iterator tmp = *this;
			++this;
			return tmp;
		}

		attribute_iterator& operator--()
		{
			assert(m_attribute && m_attribute->previous_attribute());
			m_attribute = m_attribute->previous_attribute();
			return *this;
		}

		attribute_iterator operator--(int)
		{
			attribute_iterator tmp = *this;
			++this;
			return tmp;
		}

		bool operator ==(const attribute_iterator<Ch>& rhs)
		{
			return m_attribute == rhs.m_attribute;
		}

		bool operator !=(const attribute_iterator<Ch>& rhs)
		{
			return m_attribute != rhs.m_attribute;
		}

	private:
		xml_attribute<Ch>* m_attribute;
	};
}
