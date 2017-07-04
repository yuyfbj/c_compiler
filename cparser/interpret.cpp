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

	int evaluate(ret_item& ret_main,item_shift_expression_ex* item, ret_item& ret)
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
	int evaluate(ret_item& ret_main,item_relational_expression_ex* item, ret_item& ret)
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
	int evaluate(ret_item& ret_main,item_equality_expression_ex* item, ret_item& ret)
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
	int evaluate(ret_item& ret_main,item_exclusive_or_expression_ex* item, ret_item& ret)
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
	int evaluate(ret_item& ret_main,item_logical_and_expression_ex* item, ret_item& ret)
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
	int evaluate(ret_item& ret_main,item_logical_or_expression_ex* item, ret_item& ret)
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
			
			return evaluate(ret_and_item,item->right2, ret);
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
			return evaluate(item->right1,ret);
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
	int evaluate(item_argument_expression_list* item, ret_item& ret)
	{




		return 0;
	}
	int evaluate(ret_item& ret_primary_item,item_postfix_expression_ex* item, ret_item& ret)
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
					return evaluate(*ret_p,item->right2, ret);
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
	int evaluate(item_type_specifier* item, ret_item& ret)
	{



		return 0;
	}
	int evaluate(item_specifier_qualifier_list* item, ret_item& ret)
	{


		return 0;
	}


	int evaluate(item_pointer* item, ret_item& ret)
	{

		return 0;
	}
	int evaluate(item_constant_expression* item, ret_item& ret)
	{

		return 0;
	}

	int evaluate(item_parameter_list* item, ret_item& ret)
	{


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
		



		return 0;
	}
	int evaluate(item_direct_abstract_declarator* item, ret_item& ret)
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
	int evaluate(item_abstract_declarator* item, ret_item& ret)
	{
		/*	abstract_declarator
		: pointer
		| direct_abstract_declarator
		| pointer direct_abstract_declarator
		;
		*/
		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		else if (item->right1 == NULL && item->right2)
		{
			return evaluate(item->right2, ret);
		}
		else if (item->right1 && item->right2)
		{
			ret_item ret_pt;
			evaluate(item->right1, ret_pt);
			ret_item ret_dad_item;
			evaluate(item->right2, ret_dad_item);

			auto fn = [](ret_item& v1,ret_item&v2,ret_item& ret)->int
			{//========================================


				return 0;
			};
			return fn(ret_pt, ret_dad_item,ret);

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
			ret_item ret_sql_item;
			evaluate(item->right2, ret_sql_item);
			ret_item ret_ad_item;
			evaluate(item->right3, ret_ad_item);

			auto fn = [](ret_item& v1, ret_item& v2, ret_item& ret)->int
			{//=================================

				return 0;
			};
			return fn(ret_sql_item,ret_ad_item,ret);
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
			//====================================
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