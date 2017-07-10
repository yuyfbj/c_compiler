#include "interpret.h"
namespace interpret
{
	int evaluate(ret_item& ret_main, item_multiplicative_expression_ex* item, ret_item& ret)
	{
		/*
		multiplicative_expression_ex
		:  '*' cast_expression multiplicative_expression_ex
		|  '/' cast_expression multiplicative_expression_ex
		|  '%' cast_expression multiplicative_expression_ex
		|EMPTY
		;
		*/
		ret_item ret_cast_item;
		evaluate(item->right1, ret_cast_item);
		if (item->op == '*')
		{
			auto ret_p = ret_main.mul_op(ret_cast_item);
			if (item->right2)
			{
				return evaluate(*ret_p, item->right2, ret);
			}
			ret = *ret_p;
			return item->op;
		}
		else if (item->op == '/')
		{
			auto ret_p = ret_main.div_op(ret_cast_item);
			if (item->right2)
			{
				return evaluate(*ret_p, item->right2, ret);
			}
			ret = *ret_p;
			return item->op;
		}
		else if (item->op == '%')
		{
			auto ret_p = ret_main.mod_op(ret_cast_item);
			if (item->right2)
			{
				return evaluate(*ret_p, item->right2, ret);
			}
			ret = *ret_p;
			return item->op;
		}


		return 0;
	}
	int evaluate(item_multiplicative_expression* item, ret_item& ret)
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

		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		else if (item->right1 && item->right2)
		{
			ret_item ret_cast_item;
			evaluate(item->right1, ret_cast_item);
			return evaluate(ret_cast_item, item->right2, ret);
		}
		return 0;
	}
	int evaluate(ret_item& ret_main, item_additive_expression_ex* item, ret_item& ret)
	{
		/*
			additive_expression
			: '+' multiplicative_expression additive_expression_ex
			|  '-' multiplicative_expression additive_expression_ex
			|EMPTY
			;
			*/
		ret_item ret_mul_item;
		evaluate(item->right1, ret_mul_item);
		if (item->op == '+')
		{
			auto ret_p = ret_main.add_op(ret_mul_item);
			if (item->right2)
			{
				return evaluate(*ret_p, item->right2, ret);
			}
			ret = *ret_p;
			return item->op;
		}
		else if (item->op == '-')
		{
			auto ret_p = ret_main.sub_op(ret_mul_item);
			if (item->right2)
			{
				return evaluate(*ret_p, item->right2, ret);
			}
			ret = *ret_p;
			return item->op;

		}


		return 0;
	}
	int evaluate(item_additive_expression* item, ret_item& ret)
	{
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
		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		else if (item->right1 && item->right2)
		{
			ret_item ret_mul_item;
			evaluate(item->right1, ret_mul_item);
			return evaluate(ret_mul_item, item->right2, ret);
		}

		return 0;
	}

	int evaluate(ret_item& ret_main, item_shift_expression_ex* item, ret_item& ret)
	{
		/*
		shift_expression_ex
		:  LEFT_OP additive_expression shift_expression_ex
		|  RIGHT_OP additive_expression shift_expression_ex
		|EMPTY
		;
		*/
		ret_item ret_add_item;
		evaluate(item->right1, ret_add_item);
		if (item->op == LEFT_OP)
		{
			auto ret_p = ret_main.shift_left_op(ret_add_item);
			if (item->right2)
			{
				return evaluate(*ret_p, item->right2, ret);
			}
			ret = *ret_p;
			return item->op;
		}
		else if (item->op == RIGHT_OP)
		{
			auto ret_p = ret_main.shift_right_op(ret_add_item);
			if (item->right2)
			{
				return evaluate(*ret_p, item->right2, ret);
			}
			ret = *ret_p;
			return item->op;

		}

		return 0;
	}
	int evaluate(item_shift_expression* item, ret_item& ret)
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
		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		else if (item->right1 && item->right2)
		{
			ret_item ret_add_item;
			evaluate(item->right1, ret_add_item);
			return evaluate(ret_add_item, item->right2, ret);
		}



		return 0;
	}
	int evaluate(ret_item& ret_main, item_relational_expression_ex* item, ret_item& ret)
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
		ret_item ret_rel_item;
		evaluate(item->right1, ret_rel_item);
		if (item->op == '>')
		{
			auto ret_p = ret_main.rel_great_op(ret_rel_item);
			if (item->right2)
			{
				return evaluate(*ret_p, item->right2, ret);
			}
			ret = *ret_p;
			return item->op;
		}
		else if (item->op == '<')
		{
			auto ret_p = ret_main.rel_low_op(ret_rel_item);
			if (item->right2)
			{
				return evaluate(*ret_p, item->right2, ret);
			}
			ret = *ret_p;
			return item->op;
		}
		else if (item->op == LE_OP)
		{
			auto ret_p = ret_main.rel_le_op(ret_rel_item);
			if (item->right2)
			{
				return evaluate(*ret_p, item->right2, ret);
			}
			ret = *ret_p;
			return item->op;

		}
		else if (item->op == GE_OP)
		{
			auto ret_p = ret_main.rel_ge_op(ret_rel_item);
			if (item->right2)
			{
				return evaluate(*ret_p, item->right2, ret);
			}
			ret = *ret_p;
			return item->op;
		}


		return 0;
	}
	int evaluate(item_relational_expression* item, ret_item& ret)
	{
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
		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		else if (item->right1 && item->right2)
		{
			ret_item ret_shift_item;
			evaluate(item->right1, ret_shift_item);
			return evaluate(ret_shift_item, item->right2, ret);
		}
		return 0;
	}
	int evaluate(ret_item& ret_main, item_equality_expression_ex* item, ret_item& ret)
	{
		/*
		equality_expression_ex
		: EQ_OP relational_expression equality_expression_ex
		| NE_OP relational_expression equality_expression_ex
		| EMPTY
		*/
		ret_item ret_rel_item;
		evaluate(item->right1, ret_rel_item);
		if (item->op == EQ_OP)
		{
			auto ret_p = ret_main.rel_eq_op(ret_rel_item);
			if (item->right2)
			{
				return evaluate(*ret_p, item->right2, ret);
			}
			ret = *ret_p;
			return item->op;
		}
		else if (item->op == NE_OP)
		{
			auto ret_p = ret_main.rel_ne_op(ret_rel_item);
			if (item->right2)
			{
				return evaluate(*ret_p, item->right2, ret);
			}
			ret = *ret_p;
			return item->op;
		}

		return 0;
	}
	int evaluate(item_equality_expression* item, ret_item& ret)
	{
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
		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		else if (item->right1 && item->right2)
		{
			ret_item ret_rel_item;
			evaluate(item->right1, ret_rel_item);
			return evaluate(ret_rel_item, item->right2, ret);
		}
		return 0;
	}
	int evaluate(ret_item& ret_main, item_and_expression_ex* item, ret_item& ret)
	{
		/*
		and_expression_ex
		:	 '&' equality_expression and_expression_ex
		|EMPTY
		*/
		ret_item ret_equ_item;
		evaluate(item->right1, ret_equ_item);
		auto ret_p = ret_main.bit_and_op(ret_equ_item);
		if (item->right2)
		{
			return evaluate(*ret_p, item->right2, ret);
		}
		ret = *ret_p;
		return item->op;
	}

	int evaluate(item_and_expression* item, ret_item& ret)
	{
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

		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		else if (item->right1 && item->right2)
		{
			ret_item ret_equ_item;
			evaluate(item->right1, ret_equ_item);
			return evaluate(ret_equ_item, item->right2, ret);
		}
		return 0;
	}
	int evaluate(ret_item& ret_main, item_exclusive_or_expression_ex* item, ret_item& ret)
	{
		/*
			exclusive_or_expression_ex
			|  '^' and_expression exclusive_or_expression_ex
			|EMPTY
			;
			*/
		ret_item ret_and_item;
		evaluate(item->right1, ret_and_item);
		ret_item* ret_p = ret_main.xor_op(ret_and_item);
		if (item->right2)
		{
			return evaluate(*ret_p, item->right2, ret);
		}
		ret = *ret_p;
		return item->op;
	}

	int evaluate(item_exclusive_or_expression* item, ret_item& ret)
	{
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

		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		else if (item->right1 && item->right2)
		{
			ret_item ret_and_item;
			evaluate(item->right1, ret_and_item);
			return evaluate(ret_and_item, item->right2, ret);
		}
		return 0;
	}
	int evaluate(ret_item& ret_main, item_inclusive_or_expression_ex* item, ret_item& ret)
	{
		/*
			inclusive_or_expression_ex
			:  '|' exclusive_or_expression inclusive_or_expression_ex
			|EMPTY;
			*/
		ret_item ret_ioe_item;
		evaluate(item->right1, ret_ioe_item);
		auto ret_p = ret_main.bit_or_op(ret_ioe_item);
		if (item->right2)
		{
			return evaluate(*ret_p, item->right2, ret);
		}
		ret = *ret_p;
		return item->op;

	}
	int evaluate(item_inclusive_or_expression* item, ret_item& ret)
	{
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

		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		else if (item->right1 && item->right2)
		{
			ret_item ret_eoe_item;
			evaluate(item->right1, ret_eoe_item);

			return evaluate(ret_eoe_item, item->right2, ret);
		}

		return 0;
	}
	int evaluate(ret_item& ret_main, item_logical_and_expression_ex* item, ret_item& ret)
	{
		/*logical_and_expression_ex
		:  AND_OP inclusive_or_expression 	logical_and_expression_ex
		|EMPTY
		*/
		ret_item ret_ioe_item;
		evaluate(item->right1, ret_ioe_item);

		auto ret_p = ret_main.logic_and(ret_ioe_item);
		if (item->right2)
		{
			return evaluate(*ret_p, item->right2, ret);
		}
		ret = *ret_p;
		return item->op;
	}
	int evaluate(item_logical_and_expression* item, ret_item& ret)
	{
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
		;*/

		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		else if (item->right1 && item->right2)
		{
			ret_item ret_ioe_item;
			evaluate(item->right1, ret_ioe_item);
			return evaluate(ret_ioe_item, item->right2, ret);
		}
		return 0;
	}
	int evaluate(ret_item& ret_main, item_logical_or_expression_ex* item, ret_item& ret)
	{
		/*
		logical_or_expression_ex
		: OR_OP logical_and_expression logical_or_expression_ex
		|EMPTY
		*/

		if (item->right1 && item->right2 == NULL)
		{
			ret_item ret_lae_item;
			evaluate(item->right1, ret);

			auto ret_p = ret_main.logic_or(ret_lae_item);
			ret = *ret_p;
			return item->op;
		}
		else if (item->right1 && item->right2)
		{
			ret_item ret_lae_item;
			evaluate(item->right1, ret);

			auto ret_p = ret_main.logic_or(ret_lae_item);
			if (item->right2)
			{
				return evaluate(*ret_p, item->right2, ret);
			}
			ret = *ret_p;
			return item->op;
		}

		return 0;
	}
	int evaluate(item_logical_or_expression* item, ret_item& ret)
	{//ret里要放入一个bool值
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
		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		if (item->right1 && item->right2)
		{
			ret_item ret_and_item;
			evaluate(item->right1, ret_and_item);

			return evaluate(ret_and_item, item->right2, ret);
		}

		return 0;
	}
	int evaluate(item_conditional_expression* item, ret_item& ret)
	{
		//conditional_expression
		//	: logical_or_expression
		//	| logical_or_expression '?' expression ':' conditional_expression
		if (item->right1 && item->right2 == NULL && item->right3 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		if (item->right1 &&item->right2 && item->right3)
		{
			ret_item ret_condition_item;
			evaluate(item->right1, ret_condition_item);

			auto result_bool_ptr = ret_condition_item.get_item<bool>();
			if (*result_bool_ptr)
			{
				ret_item ret_result1_item;
				return evaluate(item->right2, ret_result1_item);
			}
			else
			{
				ret_item ret_result2_item;
				evaluate(item->right3, ret_result2_item);
			}

		}

		return 0;
	}
	int evaluate(item_assignment_operator* item, ret_item& ret)
	{
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
		ret.op = item->op;
		ret.type = ASSIGNMENT_OP;

		return 0;
	}
	int evaluate(item_identifier* item, ret_item& ret)
	{
		auto item_var = find_var(item->right);
		if (item_var)
			ret.set_item<var_t>((var_t*)item_var);

		return item->op;
	}

	int evaluate(item_argument_expression_list_ex* item, ret_item& ret)
	{
		/*
		argument_expression_list_ex
		: ',' assignment_expression argument_expression_list_ex
		|EMPTY
		;
		*/
		ret_item ret_aelex_item;
		int ret_val = evaluate(item->right1, ret_aelex_item);

		if (item->right2)
		{
			return evaluate(item->right2, ret);
		}
		ret = ret_aelex_item;

		return ret_val;
	}

	int evaluate(item_argument_expression_list* item, ret_item& ret)
	{
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
		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		else if (item->right1 && item->right2)
		{
			ret_item ret_aelex_item;
			evaluate(item->right1, ret_aelex_item);
			return evaluate(item->right2, ret);
		}

		return 0;
	}
	int evaluate(ret_item& ret_primary_item, item_postfix_expression_ex* item, ret_item& ret)
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
			*/


		if (item->op == '[')
		{//'[' expression ']'   postfix_expression_ex
			ret_item ret_expr_item;
			evaluate(item->right1, ret_expr_item);
			ret_item* ret_p = (ret_primary_item)[ret_expr_item];

			ret = *ret_p;
			return item->op;
		}
		else if (item->op == '(')
		{
			//这里处理的是函数调用。
			if (item->right4 == NULL)
			{//| '(' ')'  postfix_expression_ex
				ret_item* ret_p = (ret_primary_item)();
				ret = *ret_p;
				return item->op;
			}
			else
			{//| '(' argument_expression_list ')'   postfix_expression_ex
				ret_item ret_ael_item;
				evaluate(item->right4, ret_ael_item);
				ret_item* ret_p = (ret_primary_item)(ret_ael_item);
				if (item->right2)
				{
					return evaluate(*ret_p, item->right2, ret);
				}
				ret = *ret_p;
				return item->op;
			}
			return 0;
		}
		else if (item->op == '.')
		{// '.' IDENTIFIER  postfix_expression_ex
			ret_item ret_id_item;
			evaluate(item->right3, ret_id_item);
			ret_item* ret_p = ret_primary_item.dot_op(ret_id_item);
			if (item->right2)
			{
				return evaluate(*ret_p, item->right2, ret);
			}
			ret = *ret_p;
			return item->op;
		}
		else if (item->op == PTR_OP)
		{//PTR_OP IDENTIFIER   postfix_expression_ex。
			ret_item ret_id_item;
			evaluate(item->right3, ret_id_item);
			ret_item* ret_p = ret_primary_item.ptr_op(ret_id_item);
			if (item->right2)
			{
				return evaluate(*ret_p, item->right2, ret);
			}
			ret = *ret_p;
			return item->op;

		}
		else if (item->op == INC_OP)
		{// INC_OP    postfix_expression_ex
			auto ret_result = ret_primary_item.post_inc();
			if (item->right2)
			{
				return evaluate(ret_result, item->right2, ret);
			}
		}
		else if (item->op == DEC_OP)
		{//DEC_OP    postfix_expression_ex。
			auto ret_result = ret_primary_item.post_dec();
			if (item->right2)
			{
				return evaluate(ret_result, item->right2, ret);
			}
		}

		return 0;
	}
	int evaluate(item_constant_expression* item, ret_item& ret)
	{
		/*constant_expression
		: conditional_expression
		;*/
		return evaluate(item->right1, ret);
	}

	int evaluate(item_postfix_expression* item, ret_item& ret)
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

		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		else if (item->right1 && item->right2)
		{
			ret_item ret_primary_item;
			evaluate(item->right1, ret_primary_item);

			return evaluate(ret_primary_item, item->right2, ret);
		}

		return 0;
	}
	int evaluate(item_cast_expression* item, ret_item& ret)
	{
		/*	cast_expression
		: unary_expression
		| '(' type_name ')' cast_expression
		;*/
		if (item->right1)
			return evaluate(item->right1, ret);

		if (item->right2 && item->right3)
		{
			ret_item ret_type_name;
			evaluate(item->right2, ret_type_name);
			ret_item ret_cast_item;
			evaluate(item->right3, ret_cast_item);

			auto ret_p = ret_cast_item.convert_type(ret_type_name);
			ret = *ret_p;
			return item->op;
		}

		return 0;
	}

	int evaluate(item_direct_declarator_ex* item,var_t* var_p)
	{
		/*
		direct_declarator_ex
			: '[' constant_expression ']' direct_declarator_ex
			| '[' ']' direct_declarator_ex
			| '(' parameter_type_list ')' direct_declarator_ex
			| '(' identifier_list ')' direct_declarator_ex
			| '(' ')' direct_declarator_ex
			;
		*/
		//=========================================================
		if (item->op == '[')
		{
			if (item->right1 && item->right4 == NULL)
			{	//'[' constant_expression ']' 
				ret_item ret_ce_item;
				evaluate(item->right1, ret_ce_item);
				auto int_p = ret_ce_item.get_item<int>();
				if (int_p)
				{
					auto array_p = new type_array;
					if (array_p)
					{
						array_p->size = *int_p;
						var_p->array_ptr = array_p;
						var_p->var_type = ARRAY;
					}
				}
			}
			else if (item->right1 && item->right4)
			{//'[' constant_expression ']' direct_declarator_ex

			}
			else if (item->right1 == NULL && item->right4)
			{//'[' ']' direct_declarator_ex

			}
			else if (item->right1 == NULL && item->right4 == NULL)
			{	//'[' ']'

			}
		}
		else if (item->op == '(')
		{
			if (item->right2 && item->right4 == NULL)
			{	//'(' parameter_type_list ')' 

			}
			else if (item->right2 && item->right4)
			{//'(' parameter_type_list ')' direct_declarator_ex


			}
			else if (item->right3 && item->right4 == NULL)
			{//| '(' identifier_list ')'

			}
			else if (item->right3 && item->right4)
			{//| '(' identifier_list ')' direct_declarator_ex

			}
			else if (item->right3 == NULL && item->right4)
			{//'(' ')' direct_declarator_ex

			}
			else if (item->right3 == NULL && item->right4 == NULL)
			{	//'(' ')'

			}


		}
		
		return 0;
	}

	int evaluate(item_direct_declarator* item, var_t* var_p)
	{
		/*
		direct_declarator
		: IDENTIFIER direct_declarator_ex
		| '(' declarator ')' direct_declarator_ex
		;
		*/

		if (item->right1 && item->right3 == NULL)
		{
			var_p->var_name = item->right1->right;

			return item->op;
		}
		else if (item->right2 && item->right3 == NULL)
		{
			return evaluate(item->right2, var_p);

		}
		else if (item->right1 && item->right3)
		{
			var_p->var_name = item->right1->right;
			return evaluate(item->right3, var_p);

		}
		else if (item->right2 && item->right3)
		{
			evaluate(item->right2, var_p);
			return evaluate(item->right3, var_p);
		}
		return 0;
	}
	int evaluate(item_type_qualifier* item, var_t* var_p)
	{
		/*type_qualifier
		: CONST
		| VOLATILE
		;*/

		if (item->op == CONST)
			var_p->is_const = true;
		else if (item->op == VOLATILE)
			var_p->is_volatile = true;

		return item->op;
	}

	int evaluate(item_type_qualifier_list* item, var_t* var_p)
	{
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
		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, var_p);
		}
		else if (item->right1 && item->right2)
		{
			evaluate(item->right1, var_p);
			return evaluate(item->right2, var_p);
		}

		return 0;
	}

	int evaluate(item_pointer* item, var_t* var_p)
	{
		/*pointer
		: '*'
		| '*' type_qualifier_list
		| '*' pointer
		| '*' type_qualifier_list pointer
		;*/
		if (!var_p)
			return 0;
		if (item->right1 && item->right2 == NULL)
		{//'*' type_qualifier_list
			var_p->start_count++;
			return evaluate(item->right1, var_p);
		}
		else if (item->right1 == NULL && item->right2)
		{//'*' pointer
			var_p->start_count++;
			return evaluate(item->right2, var_p);
		}
		else if (item->right1 && item->right2)
		{//'*' type_qualifier_list pointer

		}
		else
		{//'*'
			var_p->start_count++;
			return item->op;
		}

		return 0;
	}
	int evaluate(item_declarator* item, var_t* var_p)
	{
		/*
		declarator
		: pointer direct_declarator
		| direct_declarator
		;
		*/
		if (item->right1 == NULL && item->right2)
		{
			return evaluate(item->right2, var_p);
		}
		else if (item->right1 && item->right2)
		{
			evaluate(item->right1, var_p);
			return evaluate(item->right2, var_p);
		}
		return 0;
	}

	int evaluate(item_specifier_qualifier_list* item, ret_item& ret)
	{
		/*得到类型和存储方式等。
		specifier_qualifier_list
		: type_specifier specifier_qualifier_list
		| type_specifier
		| type_qualifier specifier_qualifier_list
		| type_qualifier
		;
		*/

		if (item->right1 && item->right3 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		else if (item->right1 && item->right3)
		{
			ret_item ret_ts_item;
			evaluate(item->right1, ret_ts_item);

			return evaluate(item->right3, ret_ts_item);
		}
		else if (item->right2 && item->right3 == NULL)
		{
			auto var_p = ret.get_item<var_t>();
			if (var_p)
			{
				return evaluate(item->right2, var_p);
			}
		}
		else if (item->right2 && item->right3)
		{
			auto var_p = ret.get_item<var_t>();
			if (var_p)
			{
				evaluate(item->right2, var_p);
				return evaluate(item->right3, ret);
			}
		}
		return 0;
	}

	
	int evaluate(item_struct_declarator* item, var_t* var_p)
	{
		/*定义成员，及成员位宽度
		struct_declarator
		: declarator
		| ':' constant_expression
		| declarator ':' constant_expression
		;
		*/
		if (!var_p)
			return 0;
		if (item->right1 && item->right2 == NULL)
		{	
			return evaluate(item->right1, var_p);
		}
		else if (item->right1 == NULL && item->right2)
		{
			ret_item ret_ce_item;
			int nret = evaluate(item->right2, ret_ce_item);
			auto int_p = ret_ce_item.get_item<int>();
			if (int_p)
			{
				var_p->bit_widht = *int_p;
				return nret;
			}
		}
		else if (item->right1 && item->right2)
		{
			ret_item ret_ce_item;
			int nret = evaluate(item->right2, ret_ce_item);
			auto int_p = ret_ce_item.get_item<int>();
			if (int_p)
			{
				var_p->bit_widht = *int_p;
				return evaluate(item->right1, var_p);
			}
		}

		return  0;
	}

	int evaluate(ret_item& ret_main,item_struct_declarator_list_ex* item, std::map<std::string, var_t*>& member_set)
	{
		/*
		struct_declarator_list_ex
		:',' struct_declarator struct_declarator_list_ex
		;
		*/
		
		auto type_p = ret_main.get_item<var_t>();
		if (!type_p)
			return 0;
		auto var_p = new var_t;
		if (var_p)
		{
			*var_p = *type_p;
			int nret = evaluate(item->right1, var_p);
			member_set[var_p->var_name] = var_p;
		}
		if (item->right2)
		{
			return evaluate(ret_main,item->right2, member_set);
		}
		return 0;
	}


	int evaluate(ret_item& ret_type_item, item_struct_declarator_list* item, std::map<std::string, var_t*>& member_set)
	{
		/*得到变量名
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
		auto type_p = ret_type_item.get_item<var_t>();
		if (!type_p)
			return 0;
		if (item->right1 && item->right2 == NULL)
		{
			auto var_p = new var_t;
			if (var_p)
			{
				*var_p = *type_p;
				int nret =  evaluate(item->right1, var_p);
				member_set[var_p->var_name] = var_p;
				return nret;
			}
		}
		else if (item->right1 && item->right2)
		{
			auto var_p = new var_t;
			if (var_p)
			{
				*var_p = *type_p;
				int nret = evaluate(item->right1, var_p);
				member_set[var_p->var_name] = var_p;
			}
			return evaluate(ret_type_item, item->right2, member_set);
		}

		return 0;
	}

	int evaluate(item_struct_declaration* item, std::map<std::string, var_t*>& member_set)
	{
		//new struct members  and insert to list.
		//举例：int a,b,c;
		/*
		struct_declaration
			: specifier_qualifier_list struct_declarator_list ';'
			;
		*/
		ret_item ret_type_item;
		evaluate(item->right1, ret_type_item);

		return evaluate(ret_type_item, item->right2, member_set);
	}
	
	int evaluate(item_struct_declaration_list* item, std::map<std::string, var_t*>& member_set)
	{
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
		if (item->right1 && item->right2 == NULL)
		{
			int nret = evaluate(item->right1, member_set);
		}
		else if (item->right1 && item->right2)
		{
			evaluate(item->right1, member_set);
			return evaluate( item->right2, member_set);
		}
		return 0;
	}
	int evaluate(item_struct_or_union_specifier* item, type_struct_or_union* struct_or_union_p)
	{
		/*
		struct_or_union_specifier
		: struct_or_union IDENTIFIER '{' struct_declaration_list '}'
		| struct_or_union '{' struct_declaration_list '}'
		| struct_or_union IDENTIFIER
		;
		*/
		if (!struct_or_union_p)
			return  0;
		if (item->right1)
		{
			struct_or_union_p->type = item->right1->op;
		}
		if (item->right2)
		{
			struct_or_union_p->name = item->right2->right;
		}
		if (item->right3)
		{	
			return evaluate(item->right3, struct_or_union_p->member_set);
		}
		return 0;
	}
	int evaluate(item_enumerator* item, std::string& name,int& val)
	{
		/*
		enumerator
		: IDENTIFIER
		| IDENTIFIER '=' constant_expression
		;*/
		if (item->right1&& item->right2 == NULL)
		{
			name = item->right1->right;
			val = 0;
			return item->op;
		}
		else if (item->right1 && item->right2)
		{
			name = item->right1->right;
			val = 0;
			ret_item ret_ce_item;
			evaluate(item->right2, ret_ce_item);
			auto int_p = ret_ce_item.get_item<int>();
			if (int_p)
			{
				val = *int_p;
			}
			
			return item->op;
		}
		return 0;
	}

	int evaluate(item_enumerator_list_ex* item, std::map<std::string, int>& member_set)
	{
		/*enumerator_list_ex
		: ',' enumerator  enumerator_list_ex
		|empty
		;*/
		if (item->right1 && item->right2 == NULL)
		{
			std::string name;
			int val;
			int nret =  evaluate(item->right1, name,val);
			member_set[name] = val;
			return nret;
		}
		else if (item->right1 && item->right2)
		{
			std::string name;
			int val;
			evaluate(item->right1, name,val);
			member_set[name] = val;

			return evaluate(item->right2, member_set);
		}
		return 0;
	}
	int evaluate(item_enumerator_list* item, std::map<std::string, int>& member_set)
	{
		/*
		enumerator_list
		: enumerator  enumerator_list_ex
		;
		*/
		if (item->right1 && item->right2 == NULL)
		{
			std::string name;
			int val;
			int nret = evaluate(item->right1, name, val);
			member_set[name] = val;
			return nret;
		}
		else if (item->right1 && item->right2)
		{
			std::string name;
			int val;
			evaluate(item->right1, name, val);
			member_set[name] = val;

			return evaluate(item->right2, member_set);
		}

		return 0;
	}
	int evaluate(item_enum_specifier* item, type_enum* enum_p)
	{
		/*
		enum_specifier
		: ENUM '{' enumerator_list '}'
		| ENUM IDENTIFIER '{' enumerator_list '}'
		| ENUM IDENTIFIER
		;
		*/
		if (!enum_p)
			return 0;
		if (item->right2)
		{
			enum_p->name = item->right2->right;
		}
		if (item->right1)
		{
			return evaluate(item->right1, enum_p->member_set);
		}
		return item->op;
	}
	int evaluate(item_type_specifier* item, ret_item& ret)
	{
		/*用于类型的声明
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
		if (
			VOID == item->op
			|| CHAR == item->op
			|| SHORT == item->op
			|| INT == item->op
			|| LONG == item->op
			|| FLOAT == item->op
			|| DOUBLE == item->op
			|| SIGNED == item->op
			|| UNSIGNED == item->op
			|| TYPE_NAME == item->op
			)
		{	
			//这里定义一个类型，实际上是作一个实体的类型模板。
			auto var_p = new var_t(item->op);
			if (var_p)
			{
				ret.set_item<var_t>(var_p);
			}
			return item->op;
		}
		else if (item->right1)
		{//struct_or_union_specifier
			if (item->right1->op == STRUCT )
			{	
				auto var_p = new var_t(item->op);
				if (var_p)
				{
					auto struct_p = new type_struct_or_union;
					if (struct_p)
					{
						var_p->new_mem(STRUCT);
						ret.set_item<var_t>(var_p);
						return item->op;
					}
				}
				
			}
			else if (item->right1->op == UNION)
			{	
				auto var_p = new var_t(item->op);
				if (var_p)
				{
					auto struct_p = new type_struct_or_union;
					if (struct_p)
					{
						var_p->new_mem(UNION);
						ret.set_item<var_t>(var_p);
						return item->op;
					}
				}
			}
		}
		else if (item->right2)
		{//enum_specifier
			auto var_p = new var_t(item->op);
			if (var_p)
			{
				auto struct_p = new type_enum;
				if (struct_p)
				{
					var_p->new_mem(ENUM);
					ret.set_item<var_t>(var_p);
					return item->op;
				}
			}
		}
		return 0;
	}


	int evaluate(item_parameter_list* item, ret_item& ret)
	{
		/*parameter_list
		: parameter_declaration parameter_list_ex
		;*/
		//=======================================

		return 0;
	}
	int evaluate(item_parameter_type_list* item, ret_item& ret)
	{
		/*
		parameter_type_list
		: parameter_list
		| parameter_list ',' ELLIPSIS           //省略号
		;
		*/
		//=======================================
		



		return 0;
	}
	int evaluate(item_direct_abstract_declarator* item, var_t* type_p)
	{
		/*
		direct_abstract_declarator
		: '(' abstract_declarator ')' direct_abstract_declarator_ex
		| '[' ']' direct_abstract_declarator_ex
		| '[' constant_expression ']' direct_abstract_declarator_ex
		| '(' ')' direct_abstract_declarator_ex
		| '(' parameter_type_list ')' direct_abstract_declarator_ex
		;
		*/
		//=======================================
		if (item->op == '(')
		{
			if (item->right1)
			{//'(' abstract_declarator ')' direct_abstract_declarator_ex
					
			}
			else if (item->right2)
			{//'(' parameter_type_list ')' direct_abstract_declarator_ex

			}
			else
			{//'(' ')' direct_abstract_declarator_ex

			}
		}
		else if (item->op == '[')
		{
			if (item->right3)
			{//'[' constant_expression ']' direct_abstract_declarator_ex

			}
			else
			{//'[' ']' direct_abstract_declarator_ex

			}
		}

		return 0;
	}
	int evaluate(ret_item& ret_type_item,item_abstract_declarator* item, ret_item& ret)
	{
		/*	abstract_declarator
		: pointer
		| direct_abstract_declarator
		| pointer direct_abstract_declarator
		;
		*/
		auto type_p = ret_type_item.get_item<var_t>();
		if (!type_p)
			return 0;

		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, type_p);
		}
		else if (item->right1 == NULL && item->right2)
		{
			return evaluate(item->right2, type_p);
		}
		else if (item->right1 && item->right2)
		{
			ret_item ret_pt;
			evaluate(item->right1, type_p);
			return evaluate(item->right2, type_p);
		}
		return 0;
	}
	int evaluate(item_type_name* item, ret_item& ret)
	{
		/*type_name
		: type_specifier
		| specifier_qualifier_list abstract_declarator
		;
		*/
		
		if (item->right1)
		{
			return evaluate(item->right1, ret);
		}
		if (item->right2 && item->right3)
		{
			ret_item ret_type_item;
			evaluate(item->right2, ret_type_item);
			
			return evaluate(ret_type_item, item->right3, ret);
		}
		return 0;
	}

	int evaluate(item_unary_expression* item, ret_item& ret)
	{
		//unary_expression
		//	: postfix_expression
		//	| INC_OP unary_expression
		//	| DEC_OP unary_expression
		//	| unary_operator cast_expression
		//	| SIZEOF unary_expression
		//	| SIZEOF '(' type_name ')'
		//	;

		if (item->op == INC_OP)
		{
			ret_item ret_unary_item;
			evaluate(item->right2, ret_unary_item);
			auto ret_ref = ret_unary_item.pre_inc();
			ret = ret_ref;
			return item->op;
		}
		else if (item->op == DEC_OP)
		{
			ret_item ret_unary_item;
			evaluate(item->right2, ret_unary_item);
			auto ret_ref = ret_unary_item.pre_dec();
			ret = ret_ref;
			return item->op;
		}
		else if (item->op == SIZEOF)
		{
			if (item->right3)
			{
				ret_item ret_unary_item;
				evaluate(item->right2, ret_unary_item);
				auto ret_p = ret_unary_item.sizeof_op();
				ret = *ret_p;
				return item->op;
			}
			else if (item->right4)
			{
				ret_item ret_type_name_item;
				evaluate(item->right4, ret_type_name_item);
				auto ret_p = ret_type_name_item.sizeof_op();
				ret = *ret_p;
				return item->op;
			}
		}
		else if (item->op == '&')
		{
			ret_item ret_cast_item;
			evaluate(item->right4, ret_cast_item);
			
			auto ret_p = ret_cast_item.bit_and_op(ret_cast_item);
			ret = *ret_p;
			return item->op;
		}
		else if (item->op == '*')
		{
			ret_item ret_cast_item;
			evaluate(item->right4, ret_cast_item);
			auto ret_p = ret_cast_item.star_op();
			ret = *ret_p;
			return item->op;
		}
		else if (item->op == '+')
		{
			ret_item ret_cast_item;
			evaluate(item->right4, ret_cast_item);
			auto ret_p = ret_cast_item.add_sign_op();
			ret = *ret_p;
			return item->op;
		}
		else if (item->op == '-')
		{
			ret_item ret_cast_item;
			evaluate(item->right4, ret_cast_item);
			auto ret_p = ret_cast_item.sub_sign_op();
			ret = *ret_p;
			return item->op;
		}
		else if (item->op == '~')
		{
			ret_item ret_cast_item;
			evaluate(item->right4, ret_cast_item);
			auto ret_p = ret_cast_item.bit_inv_op();
			ret = *ret_p;
			return item->op;
		}
		else if (item->op == '!')
		{
			ret_item ret_cast_item;
			evaluate(item->right4, ret_cast_item);
			auto ret_p = ret_cast_item.logical_not();
			ret = *ret_p;
			return item->op;

		}
		if (item->right1)
		{
			return evaluate(item->right1, ret);
		}

		return 0;
	}


	int evaluate(item_assignment_expression* item, ret_item& ret)
	{
		/*
		assignment_expression
		: conditional_expression
		| unary_expression assignment_operator assignment_expression
		;
		*/
		if (item->right1)
		{
			return evaluate(item->right1, ret);
		}
		if (item->right1 && item->right2 && item->right3)
		{
			ret_item left_val;
			evaluate(item->right2, left_val);
			ret_item assignment_op;
			evaluate(item->right3, assignment_op);
			ret_item right_val;
			evaluate(item->right4, right_val);

			//计算赋值运算。
			if ('=' == assignment_op.op)
			{
				left_val = right_val;
			}
			else if (MUL_ASSIGN == assignment_op.op)
			{
				left_val *= right_val;
			}
			else if (DIV_ASSIGN == assignment_op.op)
			{
				left_val /= right_val;
			}
			else if (MOD_ASSIGN == assignment_op.op)
			{
				left_val %= right_val;
			}
			else if (ADD_ASSIGN == assignment_op.op)
			{
				left_val += right_val;
			}
			else if (SUB_ASSIGN == assignment_op.op)
			{
				left_val -= right_val;
			}
			else if (LEFT_ASSIGN == assignment_op.op)
			{
				left_val <<= right_val;
			}
			else if (RIGHT_ASSIGN == assignment_op.op)
			{
				left_val >>= right_val;
			}
			else if (AND_ASSIGN == assignment_op.op)
			{
				left_val &= right_val;
			}
			else if (XOR_ASSIGN == assignment_op.op)
			{
				left_val ^= right_val;
			}
			else if (OR_ASSIGN == assignment_op.op)
			{
				left_val |= right_val;
			}
			ret = left_val;
			return assignment_op.op;
			
		}

		return 0;
	}

	int evaluate(item_expression_ex* item, ret_item& ret)
	{
		/*expression_ex
		: ',' assignment_expression expression_ex
		| EMPTY
		;*/
		auto p_set = ret.get_item<std::vector<item_assignment_expression*>>();
		
		p_set->push_back(item->right1);
		if (item->right2)
			evaluate(item->right2, ret);

		return p_set->size();
	}
	int evaluate(item_expression* item, ret_item& ret)
	{
		/*expression
		: assignment_expression
		| expression ',' assignment_expression

		//消除左递归。
		expression
		:   assignment_expression expression_ex

		expression_ex
		: ',' assignment_expression expression_ex
		| EMPTY
		;

		EBNF方式：
		expression
		:   assignment_expression {',' assignment_expression}
		*/

		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		else if (item->right1 && item->right2)
		{	
			auto p_set = new std::vector<item_assignment_expression*>;
			p_set->push_back(item->right1);

			
			ret.type = TYPE_VEC_ASSIGNMENT;
			ret.set_item<std::vector<item_assignment_expression*>>(p_set);

			int count = evaluate(item->right2, ret);
			for (int i = 0; i < count; ++i)
			{
				ret_item v1;
				evaluate((*p_set)[i], v1);
			}
			return count;
		}

		return 0;
	}

	int evaluate(item_primary_expression* item, ret_item& ret)
	{
		//primary_expression
		//	: IDENTIFIER
		//	| CONSTANT
		//  | F_CONSTANT
		//  | I_CONSTANT
		//	| STRING_LITERAL
		//	| '(' expression ')'
		//	;
		ret.type = item->op;

		if (IDENTIFIER == item->op)
		{//IDENTIFIER
			//这里要根据变量名字拿到变量的地址。
			auto item_var = find_var(item->right);
			if (item_var)
				ret.set_item<var_t>((var_t*)item_var);
			
			return item->op;
		}
		else if (CONSTANT == item->op)
		{//CONSTANT
			
			//这个是"const"
			auto p = new std::string(item->right);
			if(p)
				ret.set_item<std::string>(p);
			return item->op;
		}
		else if (F_CONSTANT == item->op)
		{//F_CONSTANT
			auto item_fconst = find_const(item->right);
			if (item_fconst)
			{
				ret.set_item<const_t>((const_t*)item_fconst);
			}
			else
			{
				float f = atof(item->right.c_str());
				auto item_fconst = new const_t(f,item->right.c_str());
				if (item_fconst)
				{
					insert_const(item->right, item_fconst);
					ret.set_item<const_t>((const_t*)item_fconst);
				}
			}
			return item->op;
		}
		else if (I_CONSTANT == item->op)
		{//I_CONSTANT
			auto item_iconst = find_const(item->right);
			if (item_iconst)
			{
				ret.set_item<const_t>((const_t*)item_iconst);
			}
			else
			{
				int i = atoi(item->right.c_str());
				auto item_iconst = new const_t(i,item->right.c_str());
				if (item_iconst)
				{
					insert_const(item->right, item_iconst);
					ret.set_item<const_t>((const_t*)item_iconst);
				}
			}
			return item->op;
		}
		else if (STRING_LITERAL == item->op)
		{//STRING_LITERAL
			auto item_strconst = find_const(item->right);
			if (item_strconst)
			{
				ret.set_item<const_t>((const_t*)item_strconst);
			}
			else
			{
				auto item_strconst = new const_t(item->right.c_str());
				if (item_strconst)
				{
					insert_const(item->right, item_strconst);
					ret.set_item<const_t>((const_t*)item_strconst);
				}
			}
			return item->op;
		}
		else if ('(' == item->op)
		{//| '(' expression ')'

			return evaluate(item->right1, ret);
		}
		return 0;
	}



}