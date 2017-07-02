#include "symbol_table.h"

namespace symbol
{
	

	CSymbolTable::CSymbolTable()
	{

	}

	CSymbolTable::~CSymbolTable()
	{

	}

	bool CSymbolTable::insert_item(const std::string& name, item* node)
	{
		if (node && name.size())
			m_map[name] = node;

		return true;
	}
	item* CSymbolTable::find_item(const std::string& name)
	{
		auto itfind = m_map.find(name);
		if (itfind != m_map.end())
			return itfind->second;
		return NULL;
	}

	bool CSymbolTable::erase_item(const std::string& name)
	{
		m_map.erase(name);

		return true;
	}


	CSymbolTable* g_cur_symbol_table = NULL;

	bool init_symbol_table()
	{
		if (NULL == g_cur_symbol_table)
			g_cur_symbol_table = new CSymbolTable;
		if (g_cur_symbol_table)
			return true;
		return false;
	}

	bool insert_item(const std::string& name, item* node)
	{
		if (g_cur_symbol_table)
		{
			return g_cur_symbol_table->insert_item(name, node);
		}
		return false;
	}
	item* find_item(const std::string& name)
	{
		if (g_cur_symbol_table)
		{
			return g_cur_symbol_table->find_item(name);
		}
		return false;
	}

	bool erase_item(const std::string& name)
	{
		if (g_cur_symbol_table)
		{
			return g_cur_symbol_table->erase_item(name);
		}
		return false;
	}





}