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
	extern CSymbolTable* g_cur_symbol_table;


	bool insert_item(const std::string& name, item* node);
	item* find_item(const std::string& name);
	bool erase_item(const std::string& name);


}
#endif