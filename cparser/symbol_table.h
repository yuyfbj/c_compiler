#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stack>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include <queue>  
#include <fstream>
#include <string>


#include <regex>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <future>
#include <array>  
#include <tuple>

//#include "token_def.h"

//#include "public_func.h"

#include "symbol_item.h"
namespace symbol
{
	
	class CSymbolTable
	{
	public:
		CSymbolTable();

		~CSymbolTable();

	public :
		bool insert_item(const std::string& name,item* node);
		item* find_item(const std::string& name);
		bool erase_item(const std::string& name);

	private:

		std::map<std::string, item*> m_map;


	};
	extern CSymbolTable g_var_table;
	bool insert_var(const std::string& name, item* node);
	item* find_var(const std::string& name);
	bool erase_var(const std::string& name);

	extern CSymbolTable g_const_table;
	bool insert_const(const std::string& name, item* node);
	item* find_const(const std::string& name);
	bool erase_const(const std::string& name);

	extern CSymbolTable g_string_table;
	bool insert_string(const std::string& name, item* node);
	item* find_string(const std::string& name);
	bool erase_string(const std::string& name);

	extern CSymbolTable g_decl_table;
	bool insert_decl(const std::string& name, item* node);
	item* find_decl(const std::string& name);
	bool erase_decl(const std::string& name);

	extern CSymbolTable g_label_table;
	bool insert_label(const std::string& name, item* node);
	item* find_lable(const std::string& name);
	bool erase_label(const std::string& name);

	extern CSymbolTable g_extern_table;
	bool insert_extern(const std::string& name, item* node);
	item* find_extern(const std::string& name);
	bool erase_extern(const std::string& name);

}
#endif