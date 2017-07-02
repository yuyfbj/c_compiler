#ifndef PARSER_STSATEMENT_H
#define PARSER_STSATEMENT_H
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
#include "parser_declare.h"
namespace stmt
{
	using namespace tree_node;
	using namespace pub_func;
	using namespace lex;
	using namespace expr;
	using namespace decl;

	item_statement* statement();
	item_translation_unit* translation_unit();

	
	

}

#endif