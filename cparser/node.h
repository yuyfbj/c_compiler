#ifndef NODE_EXPR_H
#define NODE_EXPR_H

#include "gen.h"

//各种表达式的集合定义。
//定义的产生式的结构结点。
//=====================================================
//所表达式要用的结构都在这里。
#include "token_def.h"
#include "public_func.h"
#include "symbol_table.h"

namespace tree_node
{
	using namespace pub_func;
	using namespace symbol;

	struct i_node
	{
		virtual void gen_json(Json::Value& json) = 0;
		
		
		
	};
	//----------------------------------------------
	struct item_expression;
	struct item_additive_expression;
	struct item_and_expression;
	struct item_equality_expression;
	struct item_exclusive_or_expression;
	struct item_inclusive_or_expression;
	struct item_logical_and_expression;
	struct item_logical_or_expression;

	struct item_postfix_expression;
	struct item_cast_expression;
	struct item_type_name;
	struct item_relational_expression;
	struct item_shift_expression;




	//----------------------------------------------
	//所有符合交换律的左递归变成右递归。
	/*assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;*/
	struct item_assignment_operator :public  i_node
	{
		std::string type = "item_assignment_operator";
		int gen_index = 0;
		int op = 0;
		int num_child = 0;
		std::string right;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<item_assignment_operator>(json,this);
		}
		int evaluate()
		{
			return 0;
		}
	};


	struct item_unary_operator :public  i_node
	{
		std::string type = "item_unary_operator";

		int gen_index = 0;
		int op = 0;
		int num_child = 0;
		std::string right;
		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<item_unary_operator>(json, this);
		}
		int evaluate()
		{
			return 0;
		}
	};

	/*primary_expression
	: IDENTIFIER
	| CONSTANT
	| STRING_LITERAL
	| '(' expression ')'
	;

	//词法分析给返回了另外两个类型，所以要修正。
	//primary_expression
	//	: IDENTIFIER
	//	| CONSTANT
	//|F_CONSTANT
	//|I_CONSTANT
	//	| STRING_LITERAL
	//	| '(' expression ')'
	//	;

	*/


	
	struct item_primary_expression :public  i_node
	{
		std::string type = "item_primary_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 1;
		std::string right;
		item_expression* right1 = NULL;
		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_primary_expression
				,item_expression
			>(json, this);
		}

		int evaluate()
		{
			

			//======================================
			return 0;
		}

	};

	/*
	消除产生式中的直接左递归是比较容易的。例如假设非终结符P的规则为
	P→Pα / β
	其中，β是不以P开头的符号串。那么，我们可以把P的规则改写为如下的非直接左递归形式：
	P→βP’
	P’→αP’ / ε
	*/
	/*expression
	: assignment_expression
	| expression ',' assignment_expression


	//消除左递归。
	expression
	:   assignment_expression expression_ex

	expression_ex
	: ',' assignment_expression expression_ex
	| EMPTY

	;*/
	struct item_assignment_expression;

	/*expression_ex
	: ',' assignment_expression expression_ex
	| EMPTY
	*/
	struct item_expression_ex :public  i_node
	{
		std::string type = "item_expression_ex";
		int gen_index = 0;
		int op = 0;
		
		int num_child = 2;
		std::string right;
		item_assignment_expression* right1 = NULL;
		item_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_expression_ex
				, item_assignment_expression
				,item_expression_ex
			>(json, this);
		}
		int evaluate()
		{
			return 0;
		}
	};
	/*expression
	:   assignment_expression expression_ex*/
	struct item_expression :public  i_node
	{
		std::string type = "item_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_assignment_expression* right1 = NULL;
		item_expression_ex* right2 = NULL;
		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_expression
				, item_assignment_expression
				, item_expression_ex
			>(json, this);
		}

		int evaluate()
		{//============================


			return 0;
		}

	};


	/*
	assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;
	*/
	struct item_conditional_expression;
	struct item_unary_expression;
	struct item_assignment_expression :public  i_node
	{
		std::string type = "item_assignment_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 4;
		std::string right;
		item_conditional_expression* right1 = NULL;
		item_unary_expression* right2 = NULL;
		item_assignment_operator* right3 = NULL;
		item_assignment_expression* right4 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_assignment_expression
				, item_conditional_expression
				, item_unary_expression
				, item_assignment_operator
				,item_assignment_expression
			>(json, this);
		}
		int evaluate()
		{
			return 0;
		}
	};


	//unary_expression
	//	: postfix_expression
	//	| INC_OP unary_expression
	//	| DEC_OP unary_expression
	//	| unary_operator cast_expression
	//	| SIZEOF unary_expression
	//	| SIZEOF '(' type_name ')'
	//	;

	//=======================================
	struct item_unary_expression :public  i_node
	{
		std::string type = "item_unary_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 4;
		std::string right;
		item_postfix_expression* right1 = NULL;
		item_unary_expression* right2 = NULL;
		item_cast_expression* right3 = NULL;
		item_type_name* right4 = NULL;
		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_unary_expression
				, item_postfix_expression
				, item_unary_expression
				, item_cast_expression
				, item_type_name
			>(json, this);
		}
		int inc_expr(item_unary_expression* item)
		{
			//======================
			return 0;
		}
		int dec_expr(item_unary_expression* item)
		{
			//======================
			return 0;
		}
		int sizeof_expr(item_unary_expression* item)
		{
			//======================
			return 0;
		}
		int sizeof_expr(item_type_name* item)
		{
			//======================
			return 0;
		}
		int unary_op_expr(int op, item_cast_expression* item)
		{
			if (op == '&')
			{

			}
			else if (op == '*')
			{

			}
			else if (op == '+')
			{

			}
			else if (op == '-')
			{

			}
			else if (op == '~')
			{

			}
			else if (op == '!')
			{


			}
		}

		int evaluate()
		{
			
			//=====================================
			return 0;
		}
	};

	//postfix_expression
	//	: primary_expression
	//	| postfix_expression '[' expression ']'
	//	| postfix_expression '(' ')'
	//	| postfix_expression '(' argument_expression_list ')'
	//	| postfix_expression '.' IDENTIFIER
	//	| postfix_expression PTR_OP IDENTIFIER
	//	| postfix_expression INC_OP
	//	| postfix_expression DEC_OP
	//	;

	/*消除左递归后
	postfix_expression
	: primary_expression postfix_expression_ex
	;
	postfix_expression_ex
	: '[' expression ']'   postfix_expression_ex
	| '(' ')'  postfix_expression_ex
	| '(' argument_expression_list ')'   postfix_expression_ex
	| '.' IDENTIFIER  postfix_expression_ex
	| PTR_OP IDENTIFIER   postfix_expression_ex
	|  INC_OP    postfix_expression_ex
	|  DEC_OP    postfix_expression_ex
	| EMPTY

	*/

	///---------这个要思考，如何解析的问题 。这个左递怎么破。
	struct item_identifier :public  i_node
	{
		std::string type = "item_identifier";
		int gen_index = 0;
		int op = 0;
		int num_child = 0;
		std::string right;
		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_identifier
			>(json, this);
		}
		int evaluate()
		{
			return 0;
		}
	};
	struct item_argument_expression_list;
	struct item_postfix_expression_ex :public  i_node
	{
		std::string type = "item_postfix_expression_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 4;
		std::string right;
		item_expression* right1 = NULL;
		item_postfix_expression_ex* right2 = NULL;
		item_identifier * right3 = NULL;
		item_argument_expression_list* right4 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_postfix_expression_ex
				, item_expression
				, item_postfix_expression_ex
				, item_identifier
				, item_argument_expression_list
			>(json, this);
		}
		int evaluate()
		{

			//=================================
			return 0;
		}
	};

	struct item_postfix_expression :public  i_node
	{
		std::string type = "item_postfix_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_primary_expression* right1 = NULL;
		item_postfix_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_postfix_expression
				, item_primary_expression
				, item_postfix_expression_ex
			>(json, this);
		}
		int evaluate()
		{

			//=================================
			return 0;
		}
	};

	/*argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

	argument_expression_list
	: assignment_expression argument_expression_list_ex
	;

	argument_expression_list_ex
	: ',' assignment_expression argument_expression_list_ex
	|EMPTY
	;

	*/

	struct item_argument_expression_list_ex :public  i_node
	{
		std::string type = "item_argument_expression_list_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_assignment_expression* right1 = NULL;
		item_argument_expression_list_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_argument_expression_list_ex
				, item_assignment_expression
				, item_argument_expression_list_ex
			>(json, this);
		}
		int evaluate()
		{

			//=================================
			return 0;
		}
	};
	struct item_argument_expression_list :public  i_node
	{
		std::string type = "item_argument_expression_list";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_assignment_expression* right1 = NULL;
		item_argument_expression_list_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_argument_expression_list
				, item_assignment_expression
				, item_argument_expression_list_ex
			>(json, this);
		}

		int evaluate()
		{

			//=================================
			return 0;
		}
	};


	//=======================================

	//conditional_expression
	//	: logical_or_expression
	//	| logical_or_expression '?' expression ':' conditional_expression

	
	struct item_conditional_expression :public  i_node
	{
		std::string type = "item_conditional_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 3;
		std::string right;
		item_logical_or_expression* right1 = NULL;
		item_expression * right2 = NULL;
		item_conditional_expression* right3 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_conditional_expression
				, item_logical_or_expression
				, item_expression
				, item_conditional_expression
			>(json, this);
		}
		int evaluate()
		{
			

			return 0;
		}
	};

	//logical_or_expression
	//	: logical_and_expression
	//	| logical_or_expression OR_OP logical_and_expression
	//	;
	/*

	logical_or_expression
	: logical_and_expression  logical_or_expression_ex
	;
	logical_or_expression_ex
	: OR_OP logical_and_expression logical_or_expression_ex
	|EMPTY
	;


	*/


	
	struct item_logical_or_expression_ex :public  i_node
	{
		std::string type = "item_logical_or_expression_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_logical_and_expression* right1 = NULL;
		item_logical_or_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_logical_or_expression_ex
				, item_logical_and_expression
				, item_logical_or_expression_ex
			>(json, this);
		}
		int evaluate()
		{
			
			return 0;
		}

	};
	struct item_logical_or_expression :public  i_node
	{
		std::string type = "item_logical_or_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_logical_and_expression* right1 = NULL;
		item_logical_or_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_logical_or_expression
				, item_logical_and_expression
				, item_logical_or_expression_ex
			>(json, this);
		}

		int evaluate()
		{
			
			return 0;
		}

	};

	/*logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression
	;
	logical_and_expression
	: inclusive_or_expression  logical_and_expression_ex
	;
	logical_and_expression_ex
	:  AND_OP inclusive_or_expression 	logical_and_expression_ex
	|EMPTY
	;
	*/
	

	struct item_logical_and_expression_ex :public  i_node
	{
		std::string type = "item_logical_and_expression_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_inclusive_or_expression* right1 = NULL;
		item_logical_and_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_logical_and_expression_ex
				, item_inclusive_or_expression
				, item_logical_and_expression_ex
			>(json, this);
		}
		int evaluate()
		{
			return 0;
		}
	};

	struct item_logical_and_expression :public  i_node
	{
		std::string type = "item_logical_and_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_inclusive_or_expression* right1 = NULL;
		item_logical_and_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_logical_and_expression
				, item_inclusive_or_expression
				, item_logical_and_expression_ex
			>(json, this);
		}
		int evaluate()
		{
			
			return 0;
		}
	};

	/*inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

	inclusive_or_expression
	: exclusive_or_expression inclusive_or_expression_ex
	;
	inclusive_or_expression_ex
	:  '|' exclusive_or_expression inclusive_or_expression_ex
	|EMPTY;
	*/
	
	struct item_inclusive_or_expression_ex :public  i_node
	{
		std::string type = "item_inclusive_or_expression_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_exclusive_or_expression* right1 = NULL;
		item_inclusive_or_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_inclusive_or_expression_ex
				, item_exclusive_or_expression
				, item_inclusive_or_expression_ex
			>(json, this);
		}
		int evaluate()
		{
			
			
			return 0;
		}
	};
	struct item_inclusive_or_expression :public  i_node
	{
		std::string type = "item_inclusive_or_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_exclusive_or_expression* right1 = NULL;
		item_inclusive_or_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_inclusive_or_expression
				, item_exclusive_or_expression
				, item_inclusive_or_expression_ex
			>(json, this);
		}
		int evaluate()
		{
			


			return 0;
		}
	};

	/*exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

	exclusive_or_expression
	: and_expression  exclusive_or_expression_ex
	;
	exclusive_or_expression_ex
	|  '^' and_expression exclusive_or_expression_ex
	|EMPTY
	;

	*/
	

	struct item_exclusive_or_expression_ex :public  i_node
	{
		std::string type = "item_exclusive_or_expression_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_and_expression* right1 = NULL;
		item_exclusive_or_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_exclusive_or_expression_ex
				, item_and_expression
				, item_exclusive_or_expression_ex
			>(json, this);
		}
		int evaluate()
		{
			

			return 0;
		}
	};

	struct item_exclusive_or_expression :public  i_node
	{
		std::string type = "item_exclusive_or_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_and_expression* right1 = NULL;
		item_exclusive_or_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_exclusive_or_expression
				, item_and_expression
				, item_exclusive_or_expression_ex
			>(json, this);
		}
		int evaluate()
		{
			

			return 0;
		}
	};

	/*and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

	and_expression
	: equality_expression and_expression_ex
	;
	and_expression_ex
	:	 '&' equality_expression and_expression_ex
	|EMPTY
	*/
	

	struct item_and_expression_ex :public  i_node
	{
		std::string type = "item_and_expression_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_equality_expression* right1 = NULL;
		item_and_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_and_expression_ex
				, item_equality_expression
				, item_and_expression_ex
			>(json, this);
		}

		int evaluate()
		{
			


			return 0;
		}
	};
	struct item_and_expression :public  i_node
	{
		std::string type = "item_and_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_equality_expression* right1 = NULL;
		item_and_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_and_expression
				, item_equality_expression
				, item_and_expression_ex
			>(json, this);
		}
		int evaluate()
		{
			



			return 0;
		}
	};

	/*equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;

	equality_expression
	: relational_expression equality_expression_ex
	;
	equality_expression_ex
	: EQ_OP relational_expression equality_expression_ex
	| NE_OP relational_expression equality_expression_ex
	| EMPTY
	*/

	
	struct item_equality_expression_ex :public  i_node
	{
		std::string type = "item_equality_expression_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_relational_expression* right1 = NULL;
		item_equality_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_equality_expression_ex
				, item_relational_expression
				, item_equality_expression_ex
			>(json, this);
		}

		int evaluate()
		{
			





			return 0;
		}

	};
	struct item_equality_expression :public  i_node
	{
		std::string type = "item_equality_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_relational_expression* right1 = NULL;
		item_equality_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_equality_expression
				, item_relational_expression
				, item_equality_expression_ex
			>(json, this);
		}
		int evaluate()
		{
			



			
			return 0;
		}

	};

	//relational_expression
	//	: shift_expression
	//	| relational_expression '<' shift_expression
	//	| relational_expression '>' shift_expression
	//	| relational_expression LE_OP shift_expression
	//	| relational_expression GE_OP shift_expression
	//	;

	/*
	relational_expression
	: shift_expression relational_expression_ex
	;
	relational_expression_ex
	: '<' shift_expression   relational_expression_ex
	|  '>' shift_expression  relational_expression_ex
	|  LE_OP shift_expression  relational_expression_ex
	|  GE_OP shift_expression  relational_expression_ex
	|EMPTY
	;

	*/
	

	struct item_relational_expression_ex :public  i_node
	{
		std::string type = "item_relational_expression_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_shift_expression* right1 = NULL;
		item_relational_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_relational_expression_ex
				, item_shift_expression
				, item_relational_expression_ex
			>(json, this);
		}
		int evaluate()
		{
			



			
			return 0;
		}
	};


	struct item_relational_expression :public  i_node
	{
		std::string type = "item_relational_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_shift_expression* right1 = NULL;
		item_relational_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_relational_expression
				, item_shift_expression
				, item_relational_expression_ex
			>(json, this);
		}
		int evaluate()
		{
			




			return 0;
		}
	};

	/*shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

	shift_expression
	: additive_expression  shift_expression_ex
	;
	shift_expression_ex
	:  LEFT_OP additive_expression shift_expression_ex
	|  RIGHT_OP additive_expression shift_expression_ex
	|EMPTY
	;
	*/

	

	struct item_shift_expression_ex :public  i_node
	{
		std::string type = "item_shift_expression_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_additive_expression* right1 = NULL;
		item_shift_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_shift_expression_ex
				, item_additive_expression
				, item_shift_expression_ex
			>(json, this);
		}
		int evaluate()
		{
			
			
			
			
			return 0;
		}

	};
	struct item_shift_expression :public  i_node
	{
		std::string type = "item_shift_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_additive_expression* right1 = NULL;
		item_shift_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_shift_expression
				, item_additive_expression
				, item_shift_expression_ex
			>(json, this);
		}
		int evaluate()
		{
			

			return 0;
		}
	};


	/*additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

	additive_expression
	: multiplicative_expression additive_expression_ex
	;
	additive_expression
	: '+' multiplicative_expression additive_expression_ex
	|  '-' multiplicative_expression additive_expression_ex
	|EMPTY
	;

	*/
	struct item_multiplicative_expression;

	struct item_additive_expression_ex :public  i_node
	{
		std::string type = "item_additive_expression_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_multiplicative_expression* right1 = NULL;
		item_additive_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_additive_expression_ex
				, item_multiplicative_expression
				, item_additive_expression_ex
			>(json, this);
		}
		int evaluate()
		{
			//==========================
			return 0;
		}
	};
	struct item_additive_expression :public  i_node
	{
		std::string type = "item_additive_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_multiplicative_expression* right1 = NULL;
		item_additive_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_additive_expression
				, item_multiplicative_expression
				, item_additive_expression_ex
			>(json, this);
		}
		int evaluate()
		{
			//==========================
			return 0;
		}
	};

	/*multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	| multiplicative_expression '/' cast_expression
	| multiplicative_expression '%' cast_expression
	;

	multiplicative_expression
	: cast_expression   multiplicative_expression_ex
	;
	multiplicative_expression_ex
	:  '*' cast_expression multiplicative_expression_ex
	|  '/' cast_expression multiplicative_expression_ex
	|  '%' cast_expression multiplicative_expression_ex
	;
	*/

	struct item_cast_expression;

	struct item_multiplicative_expression_ex :public  i_node
	{
		std::string type = "item_multiplicative_expression_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_cast_expression* right1 = NULL;
		item_multiplicative_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_multiplicative_expression_ex
				, item_cast_expression
				, item_multiplicative_expression_ex
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}

	};
	struct item_multiplicative_expression :public  i_node
	{
		std::string type = "item_multiplicative_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_cast_expression* right1 = NULL;
		item_multiplicative_expression_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_multiplicative_expression
				, item_cast_expression
				, item_multiplicative_expression_ex
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	;*/

	struct item_cast_expression :public  i_node
	{
		std::string type = "item_cast_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 3;
		std::string right;
		item_unary_expression* right1 = NULL;
		item_type_name* right2 = NULL;
		item_cast_expression* right3 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_cast_expression
				, item_unary_expression
				, item_type_name
				, item_cast_expression
			>(json, this);
		}
		int evaluate()
		{

			//=====================================
			return 0;
		}
	};


	/*constant_expression
	: conditional_expression
	;*/


	struct item_constant_expression :public  i_node
	{
		std::string type = "item_constant_expression";
		int gen_index = 0;
		int op = 0;
		int num_child = 1;
		std::string right;
		item_conditional_expression* right1 = NULL;
		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_constant_expression
				, item_conditional_expression
			>(json, this);
		}

		int evaluate()
		{
			if (right1)
			{
				return right1->evaluate();
			}

			return 0;
		}

	};


	//=======================================
	/*type_name
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	*/

	/*type_name
	: type_specifier
	| specifier_qualifier_list abstract_declarator
	;
	*/
	struct item_type_specifier;
	struct item_specifier_qualifier_list;
	struct item_abstract_declarator;
	struct item_type_name :public  i_node
	{
		std::string type = "item_type_name";
		int gen_index = 0;
		int op = 0;
		int num_child = 3;
		std::string right;
		item_type_specifier* right1 = NULL;
		item_specifier_qualifier_list* right2 = NULL;
		item_abstract_declarator* right3 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_type_name
				, item_type_specifier
				, item_specifier_qualifier_list
				, item_abstract_declarator
			>(json, this);
		}

		int evaluate()
		{

			//=====================================
			return 0;
		}

	};

	/*struct item_type_specifier
	{
	int type = type_type_specifier;
	int gen_index;
	int op;
	};*/
	//所有表达式结构目前只依赖类型这两个结构。这两个结构暂时还不完整，是为了切割后面的其它产生式结构。
	//==============================================================
	//上述所有结构解决了表达式相关问题 

	//==============================================================
	//下面定义声明相关部分。


	//声明

	/*declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;*/
	struct item_declaration_specifiers;
	struct item_init_declarator_list;
	struct item_declaration :public  i_node
	{
		std::string type = "item_declaration";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_declaration_specifiers* right1 = NULL;
		item_init_declarator_list* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_declaration
				, item_declaration_specifiers
				, item_init_declarator_list
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| type_qualifier
	| type_qualifier declaration_specifiers
	;*/
	struct item_type_qualifier;
	struct item_storage_class_specifier;
	struct item_type_specifier;
	struct item_declaration_specifiers :public  i_node
	{
		std::string type = "item_declaration_specifiers";
		int gen_index = 0;
		int op = 0;
		int num_child = 4;
		std::string right;
		item_storage_class_specifier* right1 = NULL;
		item_declaration_specifiers* right2 = NULL;
		item_type_specifier* right3 = NULL;
		item_type_qualifier* right4 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_declaration_specifiers
				, item_storage_class_specifier
				, item_declaration_specifiers
				, item_type_specifier
				, item_type_qualifier
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}

	};
	/*type_qualifier
	: CONST
	| VOLATILE
	;*/

	struct item_type_qualifier :public  i_node
	{
		std::string type = "item_type_qualifier";
		int gen_index = 0;
		int op = 0;
		int num_child = 0;
		std::string right;
		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_type_qualifier
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*
	init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;
	init_declarator_list
	: init_declarator init_declarator_list_ex
	;
	init_declarator_list_ex
	:',' init_declarator init_declarator_list_ex
	|empty
	;


	*/
	/*
	init_declarator_list_ex
	:',' init_declarator init_declarator_list_ex
	|empty
	;
	*/
	struct item_init_declarator;
	struct item_init_declarator_list_ex :public  i_node
	{
		std::string type = "item_init_declarator_list_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_init_declarator* right1 = NULL;
		item_init_declarator_list_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_init_declarator_list_ex
				, item_init_declarator
				, item_init_declarator_list_ex
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};
	/*
	init_declarator_list
	: init_declarator init_declarator_list_ex
	;
	*/
	struct item_init_declarator;
	struct item_init_declarator_list :public  i_node
	{
		std::string type = "item_init_declarator_list";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_init_declarator* right1 = NULL;
		item_init_declarator_list_ex* right2 = NULL;
		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_init_declarator_list
				, item_init_declarator
				, item_init_declarator_list_ex
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*init_declarator
	: declarator
	| declarator '=' initializer
	;*/
	struct item_initializer;
	struct item_declarator;
	struct item_init_declarator :public  i_node
	{
		std::string type = "item_init_declarator";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_declarator* right1 = NULL;
		item_initializer* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_init_declarator
				, item_declarator
				, item_initializer
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}


	};
	/*
	initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;
	*/
	struct item_initializer_list;
	struct item_initializer :public  i_node
	{
		std::string type = "item_initializer";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_assignment_expression* right1 = NULL;
		item_initializer_list* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_initializer
				, item_assignment_expression
				, item_initializer_list
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}

	};

	//initializer_list
	//	: initializer
	//	| initializer_list ',' initializer
	//	;

	/*
	initializer_list_ex
	: ',' initializer initializer_list_ex
	|empty
	*/
	struct item_initializer_list_ex :public  i_node
	{
		std::string type = "item_initializer_list_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_initializer* right1 = NULL;
		item_initializer_list_ex* right2 = NULL;
		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_initializer_list_ex
				, item_initializer
				, item_initializer_list_ex
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}

	};
	/*
	initializer_list
	: initializer initializer_list_ex
	;
	*/
	struct item_initializer_list :public  i_node
	{
		std::string type = "item_initializer_list";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_initializer* right1 = NULL;
		item_initializer_list_ex* right2 = NULL;
		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_initializer_list
				, item_initializer
				, item_initializer_list_ex
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*
	storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

	*/
	struct item_storage_class_specifier :public  i_node
	{
		std::string type = "item_storage_class_specifier";
		int gen_index = 0;
		int op = 0;
		int num_child = 0;
		std::string right;
		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_storage_class_specifier
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*
	type_specifier
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| struct_or_union_specifier
	| enum_specifier
	| TYPE_NAME
	;
	*/
	struct item_enum_specifier;
	struct item_struct_or_union_specifier;
	struct item_type_specifier :public  i_node
	{
		std::string type = "item_type_specifier";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_struct_or_union_specifier* right1 = NULL;
		item_enum_specifier* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_type_specifier
				, item_struct_or_union_specifier
				, item_enum_specifier
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}

	};

	/*
	enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;
	*/
	struct item_enumerator_list;
	struct item_enum_specifier :public  i_node
	{
		std::string type = "item_enum_specifier";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_enumerator_list* right1 = NULL;
		item_identifier* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_enum_specifier
				, item_enumerator_list
				, item_identifier
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};


	/*enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;
	*/
	/*

	enumerator_list
	: enumerator  enumerator_list_ex
	;
	*/
	struct item_enumerator;
	struct item_enumerator_list_ex;
	struct item_enumerator_list :public  i_node
	{
		std::string type = "item_enumerator_list";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_enumerator* right1;
		item_enumerator_list_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_enumerator_list
				, item_enumerator
				, item_enumerator_list_ex
			>(json, this);
		}
		int evaluate()
		{
			return 0;
		}


	};
	/*enumerator_list_ex
	: ',' enumerator  enumerator_list_ex
	|empty
	;*/
	struct item_enumerator_list_ex :public  i_node
	{
		std::string type = "item_enumerator_list_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_enumerator* right1 = NULL;
		item_enumerator_list_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_enumerator_list_ex
				, item_enumerator
				, item_enumerator_list_ex
			>(json, this);
		}
		int evaluate()
		{
			return 0;
		}
	};
	/*
	enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;*/

	struct item_enumerator :public  i_node
	{
		std::string type = "item_enumerator";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_identifier* right1 = NULL;
		item_constant_expression* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_enumerator
				, item_identifier
				, item_constant_expression
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*
	struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER
	;
	*/
	struct item_struct_or_union;
	struct item_struct_declaration_list;
	struct item_struct_or_union_specifier :public  i_node
	{
		std::string type = "item_struct_or_union_specifier";
		int gen_index = 0;
		int op = 0;
		int num_child = 3;
		std::string right;
		item_struct_or_union* right1 = NULL;
		item_identifier* right2 = NULL;
		item_struct_declaration_list* right3 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_struct_or_union_specifier
				, item_struct_or_union
				, item_identifier
				, item_struct_declaration_list
			>(json, this);
		}
		int evaluate()
		{
			return 0;
		}

	};

	/*struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

	可以
	struct_declaration_list
	: struct_declaration
	| struct_declaration  struct_declaration_list
	;

	*/
	struct item_struct_declaration;
	struct item_struct_declaration_list :public  i_node
	{
		std::string type = "item_struct_declaration_list";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_struct_declaration* right1 = NULL;
		item_struct_declaration_list* right2 = NULL;
		
		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_struct_declaration_list
				, item_struct_declaration
				, item_struct_declaration_list
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	; */
	struct item_specifier_qualifier_list;
	struct item_struct_declarator_list;
	struct item_struct_declaration :public  i_node
	{
		std::string type = "item_struct_declaration";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_specifier_qualifier_list* right1 = NULL;
		item_struct_declarator_list* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_struct_declaration
				, item_specifier_qualifier_list
				, item_struct_declarator_list
			>(json, this);
		}
	};
	/*
	specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;
	*/
	struct item_specifier_qualifier_list :public  i_node
	{
		std::string type = "item_specifier_qualifier_list";
		int gen_index = 0;
		int op = 0;
		int num_child = 3;
		std::string right;
		item_type_specifier* right1 = NULL;
		item_type_qualifier* right2 = NULL;
		item_specifier_qualifier_list* right3 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_specifier_qualifier_list
				, item_type_specifier
				, item_type_qualifier
				, item_specifier_qualifier_list
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}

	};
	/*
	struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;
	改为
	struct_declarator_list
	: struct_declarator struct_declarator_list_ex
	;
	
	struct_declarator_list_ex
	:',' struct_declarator struct_declarator_list_ex
	;
	
	*/
	struct item_struct_declarator;
	struct item_struct_declarator_list_ex;
	struct item_struct_declarator_list :public  i_node
	{
		std::string type = "item_struct_declarator_list";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_struct_declarator* right1 = NULL;
		item_struct_declarator_list_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_struct_declarator_list
				, item_struct_declarator
				, item_struct_declarator_list_ex
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};
	/*
	struct_declarator_list_ex
	:',' struct_declarator struct_declarator_list_ex
	;
	*/
	struct item_struct_declarator_list_ex :public  i_node
	{
		std::string type = "item_struct_declarator_list_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_struct_declarator* right1 = NULL;
		item_struct_declarator_list_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_struct_declarator_list_ex
				, item_struct_declarator
				, item_struct_declarator_list_ex
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*
	struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;
	*/

	struct item_struct_declarator :public  i_node
	{
		std::string type = "item_struct_declarator";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_declarator* right1 = NULL;
		item_constant_expression* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_struct_declarator
				, item_declarator
				, item_constant_expression
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*
	declarator
	: pointer direct_declarator
	| direct_declarator
	;
	*/
	struct item_pointer;
	struct item_direct_declarator;
	struct item_declarator :public  i_node
	{
		std::string type = "item_declarator";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_pointer* right1 = NULL;
		item_direct_declarator* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_declarator
				, item_pointer
				, item_direct_declarator
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*direct_declarator
	: IDENTIFIER
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']'
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_type_list ')'
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'
	;
	direct_declarator
	: IDENTIFIER direct_declarator_ex
	| '(' declarator ')' direct_declarator_ex
	;

	direct_declarator_ex
	: '[' constant_expression ']' direct_declarator_ex
	|  '[' ']' direct_declarator_ex
	|  '(' parameter_type_list ')' direct_declarator_ex
	|  '(' identifier_list ')' direct_declarator_ex
	|  '(' ')' direct_declarator_ex
	;
	*/
	/*
	direct_declarator
	: IDENTIFIER direct_declarator_ex
	| '(' declarator ')' direct_declarator_ex
	;
	*/
	struct item_direct_declarator_ex;
	struct item_direct_declarator :public  i_node
	{
		std::string type = "item_direct_declarator";
		int gen_index = 0;
		int op = 0;
		int num_child = 3;
		std::string right;
		item_identifier* right1 = NULL;
		item_declarator* right2 = NULL;
		item_direct_declarator_ex* right3 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_direct_declarator
				, item_identifier
				, item_declarator
				, item_direct_declarator_ex
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*
	direct_declarator_ex
	: '[' constant_expression ']' direct_declarator_ex
	|  '[' ']' direct_declarator_ex
	|  '(' parameter_type_list ')' direct_declarator_ex
	|  '(' identifier_list ')' direct_declarator_ex
	|  '(' ')' direct_declarator_ex
	;
	*/
	struct item_parameter_type_list;
	struct item_identifier_list;
	struct item_direct_declarator_ex :public  i_node
	{
		std::string type = "item_direct_declarator_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 4;
		std::string right;
		
		item_constant_expression* right1 = NULL;
		item_parameter_type_list* right2 = NULL;
		item_identifier_list* right3 = NULL;
		item_direct_declarator_ex* right4 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_direct_declarator_ex
				, item_constant_expression
				, item_parameter_type_list
				, item_identifier_list
				, item_direct_declarator_ex
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*
	parameter_type_list
	: parameter_list
	| parameter_list ',' ELLIPSIS
	;
	*/
	struct item_parameter_list;
	struct item_ellipsis;
	struct item_parameter_type_list :public  i_node
	{
		std::string type = "item_parameter_type_list";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_parameter_list* right1 = NULL;
		item_ellipsis* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_parameter_type_list
				, item_parameter_list
				, item_ellipsis
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	struct item_ellipsis :public  i_node
	{
		std::string type = "item_ellipsis";
		int gen_index = 0;
		int op = 0;
		int num_child = 0;
		std::string right;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_ellipsis
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*parameter_list
	: parameter_declaration parameter_list_ex
	;*/
	struct item_parameter_list_ex;
	struct item_parameter_declaration;
	struct item_parameter_list :public  i_node
	{
		std::string type = "item_parameter_list";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_parameter_declaration* right1 = NULL;
		item_parameter_list_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_parameter_list
				, item_parameter_declaration
				, item_parameter_list_ex
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}

	};

	/*
	parameter_list_ex
	: ',' parameter_declaration parameter_list_ex
	|empty
	;
	*/
	struct item_parameter_list_ex :public  i_node
	{
		std::string type = "item_parameter_list_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_parameter_declaration* right1 = NULL;
		item_parameter_list_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_parameter_list_ex
				, item_parameter_declaration
				, item_parameter_list_ex
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	//parameter_declaration
	//	: declaration_specifiers declarator
	//	| declaration_specifiers abstract_declarator
	//	| declaration_specifiers
	//	;
	struct item_abstract_declarator;
	struct item_parameter_declaration :public  i_node
	{
		std::string type = "item_parameter_declaration";
		int gen_index = 0;
		int op = 0;
		int num_child = 3;
		std::string right;
		item_declaration_specifiers* right1 = NULL;
		item_declarator* right2 = NULL;
		item_abstract_declarator* right3 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_parameter_declaration
				, item_declaration_specifiers
				, item_declarator
				, item_abstract_declarator
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*	abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;
	*/
	struct item_direct_abstract_declarator;
	struct item_pointer;
	struct item_abstract_declarator :public  i_node
	{
		std::string type = "item_abstract_declarator";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_pointer* right1 = NULL;
		item_direct_abstract_declarator* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_abstract_declarator
				, item_pointer
				, item_direct_abstract_declarator
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}

	};

	/*direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	;*/

	/*
	direct_abstract_declarator
	: '(' abstract_declarator ')' direct_abstract_declarator_ex
	| '(' ')' direct_abstract_declarator_ex
	| '(' parameter_type_list ')' direct_abstract_declarator_ex
	| '[' ']' direct_abstract_declarator_ex
	| '[' constant_expression ']' direct_abstract_declarator_ex
	
	;
	*/
	struct item_direct_abstract_declarator_ex;
	struct item_direct_abstract_declarator :public  i_node
	{
		std::string type = "item_direct_abstract_declarator";
		int gen_index = 0;
		int op = 0;
		int num_child = 4;
		std::string right;
		item_abstract_declarator* right1 = NULL;
		item_parameter_type_list* right2 = NULL;
		item_constant_expression* right3 = NULL;
		item_direct_abstract_declarator_ex* right4 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_direct_abstract_declarator
				, item_abstract_declarator
				, item_parameter_type_list
				, item_constant_expression
				, item_direct_abstract_declarator_ex
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};
	/*
	direct_abstract_declarator_ex
	:  '(' ')' direct_abstract_declarator_ex
	|  '(' parameter_type_list ')' direct_abstract_declarator_ex
	|  '[' ']' direct_abstract_declarator_ex
	|  '[' constant_expression ']' direct_abstract_declarator_ex

	*/
	struct item_direct_abstract_declarator_ex :public  i_node
	{
		std::string type = "item_direct_abstract_declarator_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 3;
		std::string right;
		item_parameter_type_list* right1 = NULL;
		item_constant_expression* right2 = NULL;
		item_direct_abstract_declarator_ex* right3 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_direct_abstract_declarator_ex
				, item_parameter_type_list
				, item_constant_expression
				, item_direct_abstract_declarator_ex
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*
	identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;
	*/
	/*identifier_list
	: IDENTIFIER identifier_list_ex
	*/
	struct item_identifier_list_ex;
	struct item_identifier_list :public  i_node
	{
		std::string type = "item_identifier_list";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_identifier* right1 = NULL;
		item_identifier_list_ex* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_identifier_list
				, item_identifier
				, item_identifier_list_ex
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};
	/*
	identifier_list_ex
	: ',' IDENTIFIER identifier_list_ex
	*/

	struct item_identifier_list_ex :public  i_node
	{
		std::string type = "item_identifier_list_ex";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_identifier* right1 = NULL;
		item_identifier_list_ex* right2 = NULL;


		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_identifier_list_ex
				, item_identifier
				, item_identifier_list_ex
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*pointer
	: '*'
	| '*' type_qualifier_list
	| '*' pointer
	| '*' type_qualifier_list pointer
	;*/
	struct item_type_qualifier_list;
	struct item_pointer :public  i_node
	{
		std::string type = "item_pointer";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_type_qualifier_list* right1 = NULL;
		item_pointer* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_pointer
				, item_type_qualifier_list
				, item_pointer
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;
	转成直接的交换就行。
	type_qualifier_list
	: type_qualifier
	| type_qualifier type_qualifier_list
	;
	*/
	struct item_type_qualifier_list :public  i_node
	{
		std::string type = "item_type_qualifier_list";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_type_qualifier* right1 = NULL;
		item_type_qualifier_list* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_type_qualifier_list
				, item_type_qualifier
				, item_type_qualifier_list
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};


	/*
	struct_or_union
	: STRUCT
	| UNION
	;
	*/
	struct item_struct_or_union :public  i_node
	{
		std::string type = "item_struct_or_union";
		int gen_index = 0;
		int op = 0;
		int num_child = 0;
		std::string right;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_struct_or_union
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};

	/*struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

	struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;*/

	//==============================================================
	//下面定义语句相关部分。
	/*
	expression_statement
	: ';'
	| expression ';'
	;
	*/
	struct item_expression_statement :public  i_node
	{
		std::string type = "item_expression_statement";
		int gen_index = 0;
		int op = 0;
		int num_child = 1;
		std::string right;
		item_expression* right1 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_expression_statement
				, item_expression
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}

	};
	/*
	statement
	:
	 jump_statement
	 | iteration_statement
	 | selection_statement
	|labeled_statement
	| compound_statement
	| expression_statement
	
	
	
	;*/

	struct item_labeled_statement;
	struct item_compound_statement;
	struct item_expression_statement;
	struct item_selection_statement;
	struct item_iteration_statement;
	struct item_jump_statement;
	struct item_statement :public  i_node
	{
		std::string type = "item_statement";
		int gen_index = 0;
		int op = 0;
		int num_child = 6;
		std::string right;
		item_jump_statement* right1 = NULL;
		item_iteration_statement* right2 = NULL;
		item_selection_statement* right3 = NULL;
		item_labeled_statement* right4 = NULL;
		item_compound_statement* right5 = NULL;
		item_expression_statement* right6 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_statement
				, item_jump_statement
				, item_iteration_statement
				, item_selection_statement
				, item_labeled_statement
				, item_compound_statement
				, item_expression_statement
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
		
	};

	/*declaration_list
	: declaration
	| declaration_list declaration
	;
	改成：
	declaration_list
	: declaration
	|  declaration declaration_list
	;
	*/
	struct item_declaration_list :public  i_node
	{
		std::string type = "item_declaration_list";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_declaration* right1 = NULL;
		item_declaration_list* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_declaration_list
				, item_declaration
				, item_declaration_list
			>(json, this);
		}
		int evaluate()
		{
			return 0;
		}

	};

	/*statement_list
	: statement
	| statement_list statement
	改成：
	statement_list
	: statement
	| statement  statement_list

	;*/
	struct item_statement_list :public  i_node
	{
		std::string type = "item_statement_list";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_statement* right1 = NULL;
		item_statement_list* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_statement_list
				, item_statement
				, item_statement_list
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}

	};

	/*
	labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;
	*/
	struct item_labeled_statement :public  i_node
	{
		std::string type = "item_labeled_statement";
		int gen_index = 0;
		int op = 0;
		int num_child = 3;
		std::string right;
		item_identifier* right1 = NULL;
		item_constant_expression* right2 = NULL;
		item_statement* right3 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_labeled_statement
				, item_identifier
				, item_constant_expression
				, item_statement
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}

	};
	/*
	compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
	;
	*/
	struct item_compound_statement :public  i_node
	{
		std::string type = "item_compound_statement";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_statement_list* right1 = NULL;
		item_declaration_list* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_compound_statement
				, item_statement_list
				, item_declaration_list
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}

	};

	/*
	selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	| SWITCH '(' expression ')' statement
	;
	*/

	struct item_selection_statement :public  i_node
	{
		std::string type = "item_selection_statement";
		int gen_index = 0;
		int op = 0;
		int num_child = 3;
		std::string right;
		item_expression* right1 = NULL;
		item_statement* right2 = NULL; //then
		item_statement* right3 = NULL;//else

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_selection_statement
				, item_expression
				, item_statement
				, item_statement
			>(json, this);
		}
		
		int evaluate()
		{
			return 0;
		}
	};

	/*
	jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;
	*/
	struct item_jump_statement :public  i_node
	{
		std::string type = "item_jump_statement";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_identifier* right1 = NULL;
		item_expression* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_jump_statement
				, item_identifier
				, item_expression
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}

	};
	/*
	iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;
	*/
	struct item_iteration_statement :public  i_node
	{
		std::string type = "item_iteration_statement";
		int gen_index = 0;
		int op = 0;
		int num_child = 5;
		std::string right;
		item_expression* right1 = NULL;
		item_expression_statement* right2 = NULL;
		item_expression_statement* right3 = NULL;
		item_expression* right4 = NULL;
		item_statement* right5 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_iteration_statement
				, item_expression
				, item_expression_statement
				, item_expression_statement
				, item_expression
				, item_statement
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}

	};


	/*
	translation_unit
	: external_declaration
	| translation_unit external_declaration
	;
	改成
	translation_unit
	: external_declaration
	|external_declaration  translation_unit
	;


	*/
	struct item_external_declaration;
	struct item_translation_unit :public  i_node
	{
		std::string type = "item_translation_unit";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_external_declaration* right1 = NULL;
		item_translation_unit* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_translation_unit
				, item_external_declaration
				, item_translation_unit
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}

	};
	/*
	external_declaration
	: function_definition
	| declaration
	;
	*/
	struct item_function_definition;
	struct item_external_declaration :public  i_node
	{
		std::string type = "item_external_declaration";
		int gen_index = 0;
		int op = 0;
		int num_child = 2;
		std::string right;
		item_function_definition* right1 = NULL;
		item_declaration* right2 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_external_declaration
				, item_function_definition
				, item_declaration
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}

	};
	/*
	function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;
	*/
	struct item_function_definition :public  i_node
	{
		std::string type = "item_function_definition";
		int gen_index = 0;
		int op = 0;
		int num_child = 4;
		std::string right;
		item_declaration_specifiers* right1 = NULL;
		item_declarator* right2 = NULL;
		item_declaration_list* right3 = NULL;
		item_compound_statement* right4 = NULL;

		virtual void gen_json(Json::Value& json)
		{
			gen::gen_json<
				item_function_definition
				, item_declaration_specifiers
				, item_declarator
				, item_declaration_list
				, item_compound_statement
			>(json, this);
		}

		int evaluate()
		{
			return 0;
		}
	};


}







#endif