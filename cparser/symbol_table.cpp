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

	CSymbolTable g_var_table;
	bool insert_var(const std::string& name, item* node)
	{
		return g_var_table.insert_item(name, node);
	}
	item* find_var(const std::string& name)
	{
		return g_var_table.find_item(name);
	}
	bool erase_var(const std::string& name)
	{
		return g_var_table.erase_item(name);
	}

	CSymbolTable g_const_table;
	bool insert_const(const std::string& name, item* node)
	{
		return g_const_table.insert_item(name, node);
	}
	item* find_const(const std::string& name)
	{
		return g_const_table.find_item(name);
	}
	bool erase_const(const std::string& name)
	{
		return g_const_table.erase_item(name);
	}


	CSymbolTable g_string_table;
	bool insert_string(const std::string& name, item* node)
	{
		return g_string_table.insert_item(name, node);
	}
	item* find_string(const std::string& name)
	{
		return g_string_table.find_item(name);
	}
	bool erase_string(const std::string& name)
	{
		return g_string_table.erase_item(name);
	}


	CSymbolTable g_decl_table;
	bool insert_decl(const std::string& name, item* node)
	{
		return g_decl_table.insert_item(name, node);
	}
	item* find_decl(const std::string& name)
	{
		return g_decl_table.find_item(name);
	}
	bool erase_decl(const std::string& name)
	{
		return g_decl_table.erase_item(name);
	}


	CSymbolTable g_label_table;
	bool insert_label(const std::string& name, item* node)
	{
		return g_label_table.insert_item(name, node);
	}
	item* find_lable(const std::string& name)
	{
		return g_label_table.find_item(name);
	}
	bool erase_label(const std::string& name)
	{
		return g_label_table.erase_item(name);
	}

	CSymbolTable g_extern_table;
	bool insert_extern(const std::string& name, item* node)
	{
		return g_extern_table.insert_item(name, node);
	}
	item* find_extern(const std::string& name)
	{
		return g_extern_table.find_item(name);
	}
	bool erase_extern(const std::string& name)
	{
		return g_extern_table.erase_item(name);
	}



	

}