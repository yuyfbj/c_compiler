#ifndef PARSER_EXPRESSION_H
#define PARSER_EXPRESSION_H

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

#include "token_def.h"

#include "public_func.h"
#include "lex.h"

#include "node.h"
namespace expr
{
	//assignment_operator
	using namespace tree_node;
	using namespace pub_func;
	using namespace lex;

	

	//------------------------------------------------------------
	item_assignment_operator* assignment_operator();
	item_unary_operator* unary_operator();
	item_type_name* type_name();
	item_cast_expression*  cast_expression();
	item_multiplicative_expression_ex* multiplicative_expression_ex();
	item_multiplicative_expression* multiplicative_expression();
	item_additive_expression_ex* additive_expression_ex();
	item_additive_expression* additive_expression();
	item_shift_expression_ex* shift_expression_ex();
	item_shift_expression* shift_expression();

	item_relational_expression_ex* relational_expression_ex();
	item_relational_expression* relational_expression();
	item_equality_expression_ex* equality_expression_ex();
	item_equality_expression* equality_expression();

	item_and_expression_ex* and_expression_ex();
	item_and_expression* and_expression();
	item_exclusive_or_expression_ex* exclusive_or_expression_ex();
	item_exclusive_or_expression* exclusive_or_expression();

	item_inclusive_or_expression_ex* inclusive_or_expression_ex();
	item_inclusive_or_expression* inclusive_or_expression();
	item_logical_and_expression_ex* logical_and_expression_ex();
	item_logical_and_expression* logical_and_expression();

	item_logical_or_expression_ex* logical_or_expression_ex();
	item_logical_or_expression*  logical_or_expression();
	item_conditional_expression* conditional_expression();
	item_argument_expression_list_ex* argument_expression_list_ex();
	item_argument_expression_list* argument_expression_list();
	item_postfix_expression_ex* postfix_expression_ex();
	item_postfix_expression* postfix_expression();
	item_unary_expression * unary_expression();
	item_assignment_expression* assignment_expression();
	item_expression_ex* expression_ex();
	item_expression* expression();
	item_primary_expression* primary_expression();

	item_constant_expression* constant_expression();








	//------------------------------------------------------------
	bool main_parse();


}

#endif