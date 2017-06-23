#ifndef PARSER_DECLARE_H
#define PARSER_DECLARE_H

#include <stack>
#include <vector>
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

#include "node.h"
#include "lex.h"
#include "public_func.h"
#include "token_def.h"
#include "parser_expression.h"
namespace decl
{
	using namespace tree_node;
	using namespace pub_func;
	using namespace lex;
	using namespace expr;
	

	item_declaration* declaration();
	item_init_declarator_list* init_declarator_list();
	item_init_declarator_list_ex* init_declarator_list_ex();
	item_init_declarator* init_declarator();
	item_initializer* initializer();

	item_declarator * declarator();

	item_declaration_specifiers* declaration_specifiers();

	item_parameter_type_list* parameter_type_list();
	item_struct_declarator_list_ex* struct_declarator_list_ex();
	item_abstract_declarator* abstract_declarator();
	item_type_qualifier* type_qualifier();
	item_type_specifier* type_specifier();
	item_struct_or_union_specifier* struct_or_union_specifier();

	item_specifier_qualifier_list* specifier_qualifier_list();



}

#endif