
#include "parser_expression.h"
#include "public_func.h"
#include "parser_declare.h"
namespace expr
{

	using namespace pub_func;
	using namespace decl;
	item_assignment_operator* assignment_operator()
	{
		//每个函数只关注自己预期得到，若得不到就报错。说明有语法问题 。
		//assignment_operator
		//	: '='
		//	| MUL_ASSIGN
		//	| DIV_ASSIGN
		//	| MOD_ASSIGN
		//	| ADD_ASSIGN
		//	| SUB_ASSIGN
		//	| LEFT_ASSIGN
		//	| RIGHT_ASSIGN
		//	| AND_ASSIGN
		//	| XOR_ASSIGN
		//	| OR_ASSIGN
		//	;
		//item_assignment_operator* item = new item_assignment_expression;
		auto item = NewItem<item_assignment_operator>();
		if (NULL == item)
			return NULL;
		std::string strval;
		int token = pre_get_token_val(strval);
		if ('=' == token
			|| MUL_ASSIGN == token
			|| DIV_ASSIGN == token
			|| MOD_ASSIGN == token
			|| ADD_ASSIGN == token
			|| SUB_ASSIGN == token
			|| LEFT_ASSIGN == token
			|| RIGHT_ASSIGN == token
			|| AND_ASSIGN == token
			|| XOR_ASSIGN == token
			|| OR_ASSIGN == token
			)
		{
			pop_token();
			item->op = token;
			item->right = strval;

			return item;
		}
		return ReleaseItem<item_assignment_operator>(item);
	};
	//unary_operator
	item_unary_operator* unary_operator()
	{
		//unary_operator
		//: '&'
		//| '*'
		//| '+'
		//| '-'
		//| '~'
		//| '!'
		//;

		auto item = NewItem<item_unary_operator>();
		if (NULL == item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (
			'&' == token
			|| '*' == token
			|| '+' == token
			|| '-' == token
			|| '~' == token
			|| '!' == token
			)
		{
			pop_token();
			item->op = token;
			item->right = val;
			return item;
		}
		return ReleaseItem<item_unary_operator>(item);
	};
	item_type_name* type_name()
	{
		/*type_name
		: type_specifier
		| specifier_qualifier_list abstract_declarator
		;
		*/
		auto item = NewItem<item_type_name>();
		if (!item)
			return NULL;

		auto item1 = type_specifier();
		if (item1)
		{
			item->right1 = item1;
			return item;
		}
		auto item2 = specifier_qualifier_list();
		if (item2)
		{
			item->right2 = item2;
			auto item3 = abstract_declarator();
			if (item3)
			{
				item->right3 = item3;
				return item;
			}
		}
		return ReleaseItem<item_type_name>(item);

	}
	item_cast_expression*  cast_expression()
	{
		/*	cast_expression
		: unary_expression
		| '(' type_name ')' cast_expression
		;*/
		auto item = NewItem<item_cast_expression>();
		if (!item)
			return NULL;
		std::string val;
		int token = pre_get_token_val(val);
		if ('(' == token)
		{//'(' type_name ')' cast_expression
			pop_token();
			item->op = token;
			item->right = val;
			auto item2 = type_name();
			if (item2)
			{
				item->right2 = item2;

				token = pre_get_token_val(val);
				if (')' == token)
				{
					pop_token();
					item->right += val;
					auto item3 = cast_expression();
					if (item3)
					{
						item->right3 = item3;
						return item;
					}
				}
			}
		}

		auto item1 = unary_expression();
		if (item1)
		{// unary_expression
			item->right1 = item1;
			return item;
		}
		return ReleaseItem<item_cast_expression>(item);
	}
	/*消除产生式中的直接左递归是比较容易的。例如假设非终结符P的规则为
	P→Pα / β
	其中，β是不以P开头的符号串。那么，我们可以把P的规则改写为如下的非直接左递归形式：
	P→βP’
	P’→αP’ / ε*/
	item_multiplicative_expression_ex* multiplicative_expression_ex()
	{
		/*multiplicative_expression_ex
		:  '*' cast_expression multiplicative_expression_ex
		| '/' cast_expression multiplicative_expression_ex
		| '%' cast_expression multiplicative_expression_ex
		;*/
		auto item = NewItem<item_multiplicative_expression_ex>();
		if (!item)
			return NULL;
		
		std::string val;
		int token = pre_get_token_val(val);
		if ('*' == token
			|| '/' == token
			|| '%' == token
			)
		{
			pop_token();
			item->op = token;
			item->right = val;

			auto item1 = cast_expression();
			if (item1)
			{
				item->right1 = item1;
				auto item2 = multiplicative_expression_ex();
				if (item2)
					item->right2 = item2;
				return item;
			}
		}
		return ReleaseItem<item_multiplicative_expression_ex>(item);
	}
	item_multiplicative_expression* multiplicative_expression()
	{
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
		auto item = NewItem<item_multiplicative_expression>();
		if (!item)
			return NULL;

		auto item1 = cast_expression();
		if (item1)
		{
			item->right1 = item1;
			auto item2 = multiplicative_expression_ex();
			if (item2)
			{
				item->right2 = item2;
			}
			return item;
		}
		
		return ReleaseItem<item_multiplicative_expression>(item);
	}
	item_additive_expression_ex* additive_expression_ex()
	{
		/*additive_expression_ex
		: '+' multiplicative_expression additive_expression_ex
		| '-' multiplicative_expression additive_expression_ex
		| EMPTY
		;*/

		auto item = NewItem<item_additive_expression_ex>();
		if (!item)
			return NULL;
		std::string val;
		int token = pre_get_token_val(val);
		if (token == '+'
			|| token == '-'
			)
		{
			pop_token();
			item->op = token;
			item->right = val;

			auto item1 = multiplicative_expression();
			if (item1)
			{
				item->right1 = item1;
				auto item2 = additive_expression_ex();
				if (item2)
					item->right2 = item2;
				return item;
			}
		}
		return ReleaseItem<item_additive_expression_ex>(item);
	}
	item_additive_expression* additive_expression()
	{
		/*additive_expression
		: multiplicative_expression
		| additive_expression '+' multiplicative_expression
		| additive_expression '-' multiplicative_expression
		;

		additive_expression
		: multiplicative_expression additive_expression_ex
		;
		additive_expression_ex
		: '+' multiplicative_expression additive_expression_ex
		|  '-' multiplicative_expression additive_expression_ex
		|EMPTY
		;
		*/
		auto item = NewItem<item_additive_expression>();
		if (!item)
			return NULL;

		auto item1 = multiplicative_expression();
		if (item1)
		{
			item->right1 = item1;
			auto item2 = additive_expression_ex();
			if (item2)
				item->right2 = item2;
			return item;
		}
		return ReleaseItem<item_additive_expression>(item);
	}
	/*消除产生式中的直接左递归是比较容易的。例如假设非终结符P的规则为
	P→Pα / β
	其中，β是不以P开头的符号串。那么，我们可以把P的规则改写为如下的非直接左递归形式：
	P→βP’
	P’→αP’ / ε


	shift_expression
	: additive_expression  P'

	P':
	LEFT_OP additive_expression  P'
	|  empty
	*/
	item_shift_expression_ex* shift_expression_ex()
	{
		/*shift_expression_ex
		:  LEFT_OP additive_expression shift_expression_ex
		| RIGHT_OP additive_expression shift_expression_ex
		| EMPTY
		;*/

		auto item = NewItem<item_shift_expression_ex>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (LEFT_OP == token 
			|| RIGHT_OP == token
			)
		{
			pop_token();
			item->op = token;
			item->right = val;

			auto item1 = additive_expression();
			if (item1)
			{
				item->right1 = item1;
				auto item2 = shift_expression_ex();
				if (item2)
					item->right2 = item2;
				return item;
			}
		}
		return ReleaseItem<item_shift_expression_ex>(item);
	}
	item_shift_expression* shift_expression()
	{
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
		auto item = NewItem<item_shift_expression>();
		if (!item)
			return NULL;
		auto item1 = additive_expression();
		if (item1)
		{
			item->right1 = item1;
			auto item2 = shift_expression_ex();
			if (item2)
				item->right2 = item2;
			return item;
		}
		return ReleaseItem<item_shift_expression>(item);
	}
	item_relational_expression_ex* relational_expression_ex()
	{
		/*
		relational_expression_ex
		: '<' shift_expression   relational_expression_ex
		|  '>' shift_expression  relational_expression_ex
		|  LE_OP shift_expression  relational_expression_ex
		|  GE_OP shift_expression  relational_expression_ex
		|EMPTY
		;
		*/

		auto item = NewItem<item_relational_expression_ex>();
		if (!item)
			return NULL;
		std::string val;
		int token = pre_get_token_val(val);
		if ('>' == token 
			|| '<' == token 
			|| LE_OP == token 
			|| GE_OP == token
			)
		{
			pop_token();
			item->op = token;
			item->right = val;

			auto item1 = shift_expression();
			if (item1)
			{
				item->right1 = item1;
				auto item2 = relational_expression_ex();
				if (item2)
					item->right2 = item2;
				return item;
			}
		}
		return ReleaseItem<item_relational_expression_ex>(item);
	}

	item_relational_expression* relational_expression()
	{
		/*relational_expression
		: shift_expression
		| relational_expression '<' shift_expression
		| relational_expression '>' shift_expression
		| relational_expression LE_OP shift_expression
		| relational_expression GE_OP shift_expression
		;

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
		auto item = NewItem<item_relational_expression>();
		if (!item)
			return NULL;
		auto item1 = shift_expression();
		if (item1)
		{
			item->right1 = item1;

			auto item2 = relational_expression_ex();
			if (item2)
				item->right2 = item2;

			return item;
		}
		return ReleaseItem<item_relational_expression>(item);
	}

	item_equality_expression_ex* equality_expression_ex()
	{
		/*
		equality_expression_ex
		: EQ_OP relational_expression equality_expression_ex
		| NE_OP relational_expression equality_expression_ex
		| EMPTY
		;
		*/
		auto item = NewItem<item_equality_expression_ex>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (EQ_OP == token 
			|| NE_OP == token)
		{
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = relational_expression();
			if (item1)
			{

				return ReleaseItem<item_equality_expression_ex>(item);

			}
			item->right1 = item1;

			auto item2 = equality_expression_ex();
			if (item2)
				item->right2 = item2;

		}


		return item;
	}
	item_equality_expression* equality_expression()
	{
		/*equality_expression
		: relational_expression
		//| equality_expression EQ_OP relational_expression
		|   relational_expression EQ_OP  equality_expression
		//| equality_expression NE_OP relational_expression
		|    relational_expression NE_OP equality_expression
		;

		equality_expression
		: relational_expression equality_expression_ex
		;
		equality_expression_ex
		: EQ_OP relational_expression equality_expression_ex
		| NE_OP relational_expression equality_expression_ex
		| EMPTY
		;
		*/
		auto item = NewItem<item_equality_expression>();
		if (!item)
			return NULL;

		auto item1 = relational_expression();
		if (item1)
		{
			item->right1 = item1;
			auto item2 = equality_expression_ex();
			if (item2)
			{
				item->right2 = item2;
			}
			return item;
		}
		return ReleaseItem<item_equality_expression>(item);
	}


	item_and_expression_ex* and_expression_ex()
	{
		/*and_expression_ex
		:	 '&' equality_expression and_expression_ex
		| EMPTY*/
		auto item = NewItem<item_and_expression_ex>();
		if (!item)
			return NULL;
		std::string val;
		int token = pre_get_token_val(val);
		if ('&' == token)
		{
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = equality_expression();
			if (item1)
			{
				item->right1 = item1;
				auto item2 = and_expression_ex();
				if (item2)
					item->right2 = item2;

				return item;
			}
		}	
		return ReleaseItem<item_and_expression_ex>(item);
	}
	item_and_expression* and_expression()
	{
		/*and_expression
		: equality_expression
		//| and_expression '&' equality_expression
		|   equality_expression  '&' and_expression
		;

		and_expression
		: equality_expression and_expression_ex
		;
		and_expression_ex
		:	 '&' equality_expression and_expression_ex
		|EMPTY

		*/
		auto item = NewItem<item_and_expression>();
		if (!item)
			return NULL;

		auto item1 = equality_expression();
		if (item1)
		{
			item->right1 = item1;
			auto item2 = and_expression_ex();
			if (item2)
			{
				item->right2 = item2;
			}
			return item;
		}
		
		return ReleaseItem<item_and_expression>(item);
	}


	item_exclusive_or_expression_ex* exclusive_or_expression_ex()
	{
		/*    exclusive_or_expression_ex
		|  '^' and_expression exclusive_or_expression_ex
		|EMPTY
		;
		*/
		auto item = NewItem<item_exclusive_or_expression_ex>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if ('^' == token)
		{
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = and_expression();
			if (item1)
			{
				item->right1 = item1;
				auto item2 = exclusive_or_expression_ex();
				if (item2)
					item->right2 = item2;
				return item;
			}
		}
		return ReleaseItem<item_exclusive_or_expression_ex>(item);
	}
	item_exclusive_or_expression* exclusive_or_expression()
	{
		/*exclusive_or_expression
		: and_expression
		//|   exclusive_or_expression  '^'   and_expression
		|   and_expression '^'   exclusive_or_expression
		;

		exclusive_or_expression
		: and_expression  exclusive_or_expression_ex
		;
		exclusive_or_expression_ex
		|  '^' and_expression exclusive_or_expression_ex
		|EMPTY
		;
		*/
		auto item = NewItem<item_exclusive_or_expression>();
		if (!item)
			return NULL;

		auto item1 = and_expression();
		if (item1)
		{
			item->right1 = item1;

			auto item2 = exclusive_or_expression_ex();
			if (item2)
				item->right2 = item2;

			return item;
		}
		return ReleaseItem<item_exclusive_or_expression>(item);
	}
	item_inclusive_or_expression_ex* inclusive_or_expression_ex()
	{
		/*	;
		inclusive_or_expression_ex
		:  '|' exclusive_or_expression inclusive_or_expression_ex
		|EMPTY;
		*/
		auto item = NewItem<item_inclusive_or_expression_ex>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if ('|' == token)
		{
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = exclusive_or_expression();
			if (item1)
			{
				item->right1 = item1;

				auto item2 = inclusive_or_expression_ex();
				if (item2)
				{
					item->right2 = item2;
				}
				return item;
			}
		}
		return ReleaseItem<item_inclusive_or_expression_ex>(item);
	}
	item_inclusive_or_expression* inclusive_or_expression()
	{
		/*inclusive_or_expression
		: exclusive_or_expression
		//| inclusive_or_expression '|' exclusive_or_expression
		|   exclusive_or_expression '|'  inclusive_or_expression
		;

		inclusive_or_expression
		: exclusive_or_expression inclusive_or_expression_ex
		;
		inclusive_or_expression_ex
		:  '|' exclusive_or_expression inclusive_or_expression_ex
		|EMPTY;

		*/
		auto item = NewItem<item_inclusive_or_expression>();
		if (!item)
			return NULL;
		auto item1 = exclusive_or_expression();
		if (item1)
		{
			item->right1 = item1;

			auto item2 = inclusive_or_expression_ex();
			if (item2)
				item->right2 = item2;

			return item;
		}
		
		return ReleaseItem<item_inclusive_or_expression>(item);
	}

	item_logical_and_expression_ex* logical_and_expression_ex()
	{
		/*logical_and_expression_ex
		:  AND_OP inclusive_or_expression 	logical_and_expression_ex
		| EMPTY
		;*/
		auto item = NewItem<item_logical_and_expression_ex>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);

		if (AND_OP == token)
		{
			pop_token();
			item->op = token;
			item->right = val;

			auto item1 = inclusive_or_expression();
			if (item1)
			{
				item->right1 = item1;

				auto item2 = logical_and_expression_ex();
				if (item2)
					item->right2 = item2;

				return item;
			}
		}
		return ReleaseItem<item_logical_and_expression_ex>(item);
	}
	item_logical_and_expression* logical_and_expression()
	{
		/*logical_and_expression
		: inclusive_or_expression
		//| logical_and_expression AND_OP inclusive_or_expression
		|   inclusive_or_expression  AND_OP logical_and_expression
		;

		logical_and_expression
		: inclusive_or_expression  logical_and_expression_ex
		;
		logical_and_expression_ex
		:  AND_OP inclusive_or_expression 	logical_and_expression_ex
		|EMPTY
		;


		*/
		auto item = NewItem<item_logical_and_expression>();
		if (!item)
			return NULL;
		auto item1 = inclusive_or_expression();
		if (item1)
		{
			item->right1 = item1;
			auto item2 = logical_and_expression_ex();
			if (item2)
				item->right2 = item2;
			return item;
		}

		return ReleaseItem<item_logical_and_expression>(item);
	}
	item_logical_or_expression_ex* logical_or_expression_ex()
	{
		/*logical_or_expression_ex
		: OR_OP logical_and_expression logical_or_expression_ex
		| EMPTY
		;*/
		auto item = NewItem<item_logical_or_expression_ex>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (OR_OP == token)
		{
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = logical_and_expression();
			if (item1)
			{
				item->right1 = item1;
				auto item2 = logical_or_expression_ex();
				if (item2)
					item->right2 = item2;
				return item;
			}
		}
		
		return ReleaseItem<item_logical_or_expression_ex>(item);
	}
	item_logical_or_expression*  logical_or_expression()
	{
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
		auto item = NewItem<item_logical_or_expression>();
		if (!item)
			return NULL;

		auto item1 = logical_and_expression();
		if (item1)
		{
			item->right1 = item1;

			auto item2 = logical_or_expression_ex();
			if (item2)
				item->right2 = item2;

			return item;
		}

		return ReleaseItem<item_logical_or_expression>(item);
	}

	item_conditional_expression* conditional_expression()
	{
		/*conditional_expression
		: logical_or_expression
		| logical_or_expression '?' expression ':' conditional_expression
		;*/
		auto item = NewItem<item_conditional_expression>();
		if (NULL == item)
			return NULL;
		auto item1 = logical_or_expression();
		if (item1)
		{
			item->right1 = item1;
			std::string val;
			int token = pre_get_token_val(val);
			if ('?' == token)
			{
				pop_token();
				item->op = token;
				item->right = val;
				auto item2 = expression();
				if (item2)
				{
					item->right2 = item2;
					token = pre_get_token_val(val);
					if (':' == token)
					{
						pop_token();
						auto item3 = conditional_expression();
						if (item3)
						{
							item->right3 = item3;
							return item;
						}
					}
				}
			}
			return item;
		}
		return ReleaseItem<item_conditional_expression>(item);
	};

	//======================================================
	item_argument_expression_list_ex* argument_expression_list_ex()
	{
		auto item = NewItem<item_argument_expression_list_ex>();
		if (!item)
			return NULL;
		/*
		argument_expression_list_ex
		: ',' assignment_expression argument_expression_list_ex
		|EMPTY
		;
		*/
		std::string val;
		int token = pre_get_token_val(val);
		if (',' == token)
		{
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = assignment_expression();
			if (item1)
			{
				item->right1 = item1;
				auto item2 = argument_expression_list_ex();
				if (item2)
					item->right2 = item2;

				return item;
			}
		}
		return ReleaseItem<item_argument_expression_list_ex>(item);
	}
	item_argument_expression_list* argument_expression_list()
	{
		auto item = NewItem<item_argument_expression_list>();
		if (!item)
			return NULL;

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
		auto item1 = assignment_expression();
		if (item1)
		{
			auto item2 = argument_expression_list_ex();
			if (item2)
				item->right2 = item2;
			return item;
		}
		return ReleaseItem<item_argument_expression_list>(item);
	}

	item_postfix_expression_ex* postfix_expression_ex()
	{
		/*
		postfix_expression_ex
		: '[' expression ']'   postfix_expression_ex
		| '(' ')'  postfix_expression_ex
		| '(' argument_expression_list ')'   postfix_expression_ex
		| '.' IDENTIFIER  postfix_expression_ex
		| PTR_OP IDENTIFIER   postfix_expression_ex
		|  INC_OP    postfix_expression_ex
		|  DEC_OP    postfix_expression_ex
		| EMPTY
		;
		*/
		auto item = NewItem<item_postfix_expression_ex>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if ('.' == token
			|| PTR_OP == token
			)
		{
			//| '.' IDENTIFIER  postfix_expression_ex
			//| PTR_OP IDENTIFIER   postfix_expression_ex
			pop_token();
			item->op = token;
			item->right = val;

			token = pre_get_token_val(val);
			if (IDENTIFIER == token)
			{
				pop_token();
				auto item3 = NewItem<item_identifier>();
				if (item3)
				{
					item3->op = token;
					item3->right = val;

					item->right3 = item3;

					auto item2 = postfix_expression_ex();
					if (item2)
						item->right2 = item2;

					return item;
				}
			}
		}

		else if ('[' == token)
		{
			//: '[' expression ']'   postfix_expression_ex
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = expression();
			if (item1)
			{
				item->right1 = item1;
				token = pre_get_token_val(val);
				if (']' == token)
				{
					pop_token();
					item->right += val;
					auto item2 = postfix_expression_ex();
					if (item2)
						item->right2 = item2;

					return item;
				}
			}
		}
		else if ('(' == token)
		{
			//| '(' ')'  postfix_expression_ex
			//| '(' argument_expression_list ')'   postfix_expression_ex
			pop_token();
			item->op = token;
			token = pre_get_token_val(val);
			if (')' == token)
			{
				pop_token();
				item->right += val;
				auto item2 = postfix_expression_ex();
				if (item2)
					item->right2 = item2;
				return item;
			}

			auto item4 = argument_expression_list();
			if (item4)
			{
				item->right4 = item4;
				token = pre_get_token_val(val);
				if (')' == token)
				{
					pop_token();
					item->right += val;
					auto item2 = postfix_expression_ex();
					if (item2)
						item->right2 = item2;
					return item;
				}
			}
		}
		else if (INC_OP == token
			|| DEC_OP == token
			)
		{//|  INC_OP    postfix_expression_ex
			//| DEC_OP    postfix_expression_ex

			pop_token();
			item->op = token;
			item->right = val;
			auto item2 = postfix_expression_ex();
			if (item2)
				item->right2 = item2;
			return item;
		}

		return ReleaseItem<item_postfix_expression_ex>(item);
	}
	item_postfix_expression* postfix_expression()
	{

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
		auto item = NewItem<item_postfix_expression>();
		if (!item)
			return NULL;
		auto item1 = primary_expression();
		if (item1)
		{
			item->right1 = item1;
			auto item2 = postfix_expression_ex();
			if (item2)
				item->right2 = item2;

			return item;
		}
		return ReleaseItem<item_postfix_expression>(item);
	}

	//unary_expression
	item_unary_expression * unary_expression()
	{

		/*unary_expression
		: postfix_expression
		| INC_OP unary_expression
		| DEC_OP unary_expression
		| unary_operator cast_expression
		| SIZEOF unary_expression
		| SIZEOF '(' type_name ')'*/

		auto item = NewItem<item_unary_expression>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (INC_OP == token
			|| DEC_OP == token
			)
		{//| INC_OP unary_expression
			//| DEC_OP unary_expression
			pop_token();
			item->op = token;
			item->right = val;
			auto item2 = unary_expression();
			if (item2)
			{
				item->right2 = item2;
				return item;
			}
		}
		if (SIZEOF == token)
		{//| SIZEOF unary_expression
			//| SIZEOF '(' type_name ')'
			pop_token();
			item->op = token;
			item->right = val;

			token = pre_get_token_val(val);
			if ('(' == token)
			{
				auto item4 = type_name();
				if (item4)
				{
					item->right4 = item4;
					token = pre_get_token_val(val);
					if (')' == token)
					{
						pop_token();
						return item;
					}
				}
			}
		}

		auto item_op = unary_operator();
		if (item_op)
		{
			item->op = item_op->op;
			auto item3 = cast_expression();
			if (item3)
			{
				item->right3 = item3;
				return item;
			}
		}

		auto item1 = postfix_expression();
		if (item1)
		{
			item->right1 = item1;
			return item;
		}
		return ReleaseItem<item_unary_expression>(item);
	};



	//assignment_expression
	item_assignment_expression* assignment_expression()
	{

		/*assignment_expression
		: conditional_expression
		| unary_expression assignment_operator assignment_expression
		;*/
		auto item = NewItem<item_assignment_expression>();
		if (!item)
			return NULL;

		auto item1 = conditional_expression();
		if (item1)
		{//conditional_expression
			item->right1 = item1;
			return item;
		}

		auto item2 = unary_expression();
		if (item2)
		{
			// unary_expression assignment_operator assignment_expression
			item->gen_index = 1;
			item->right2 = item2;
			auto item3 = assignment_operator();
			if (item3)
			{
				item->right3 = item3;
				auto item4 = assignment_expression();
				if (item4)
				{
					item->right4 = item4;
					return item;
				}
			}
		}
		return ReleaseItem<item_assignment_expression>(item);
	};
	item_expression_ex* expression_ex()
	{
		/*expression_ex
		: ',' assignment_expression expression_ex
		| EMPTY*/
		auto item = NewItem<item_expression_ex>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (token == ',')
		{
			pop_token();
			item->op = token;
			item->right = val;

			auto item1 = assignment_expression();
			if (item1)
			{
				item->right1 = item1;

				auto item2 = expression_ex();
				if (item2)
					item->right2 = item2;
				return item;
			}
		}
		return ReleaseItem<item_expression_ex>(item);
	}
	item_expression* expression()
	{
		/*expression
		: assignment_expression
		| expression ',' assignment_expression
		;

		//消除左递归。
		expression
		:   assignment_expression expression_ex

		expression_ex
		: ',' assignment_expression expression_ex
		| EMPTY
		*/
		auto item = NewItem<item_expression>();
		if (!item)
			return NULL;

		auto item1 = assignment_expression();
		if (item1)
		{
			item->right1 = item1;

			auto item2 = expression_ex();
			if (item2)
				item->right2 = item2;

			return item;
		}
		return ReleaseItem<item_expression>(item);
	};

	item_primary_expression* primary_expression()
	{
		///*primary_expression
		//	: IDENTIFIER
		//	| CONSTANT
		//|F_CONSTANT
		//|I_CONSTANT
		//	| STRING_LITERAL
		//	| '(' expression ')'
		//	;*/

		auto item = NewItem<item_primary_expression>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);

		if (IDENTIFIER == token
			|| CONSTANT == token
			|| F_CONSTANT == token
			|| I_CONSTANT == token
			|| STRING_LITERAL == token
			)
		{
			pop_token();
			item->op = token;
			item->right = val;
			return item;
		}
		else if ('(' == token)
		{
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = expression();
			if (item1)
			{
				item->right1 = item1;

				token = pre_get_token_val(val);
				if (')' == token)
				{
					pop_token();
					item->right += val;
					return item;
				}
			}
		}
		return ReleaseItem<item_primary_expression>(item);
	}

	/*constant_expression
		: conditional_expression
		;*/

	item_constant_expression* constant_expression()
	{
		/*constant_expression
		: conditional_expression
		;*/
		auto item = NewItem<item_constant_expression>();
		if (!item)
			return NULL;

		auto item1 = conditional_expression();
		if (item1)
		{
			item->right1 = item1;
			return item;
		}
		return ReleaseItem<item_constant_expression>(item);
	}



	//----------------------------------------------

	item_expression* g_root = NULL;
	bool main_parse()
	{
		auto item = expression();
		g_root = item;

		return true;
	};



}
