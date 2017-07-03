#include "interpret.h"
namespace interpret
{
	int evaluate(item_logical_and_expression* item, ret_item& ret)
	{


		return 0;
	}
	int evaluate(item_logical_or_expression_ex* item, ret_item& ret)
	{
		/*
		logical_or_expression_ex
		: OR_OP logical_and_expression logical_or_expression_ex
		|EMPTY
		*/

		if (item->right1 && item->right2 == NULL)
		{
			return evaluate(item->right1, ret);
		}
		else if (item->right1 && item->right2)
		{
			ret_item ret_and_item;
			evaluate(item->right1, ret_and_item);
			ret_item ret_orex_item;
			evaluate(item->right2, ret_orex_item);

			auto fn = [](ret_item& v1, ret_item& v2, ret_item& ret)->int
			{
				auto bool_ptr1 = v1.get_item<bool>();
				auto bool_ptr2 = v2.get_item<bool>();
				auto bool_ptr_result = new bool((*bool_ptr1) || (*bool_ptr2));
				ret.set_item<bool>(bool_ptr_result);

				return 0;
			};
			return fn(ret_and_item, ret_orex_item, ret);

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
			ret_item ret_orex_item;
			evaluate(item->right2, ret_orex_item);
			auto fn = [](ret_item& v1,ret_item& v2,ret_item& ret)->int
			{
				auto bool_ptr1 = v1.get_item<bool>();
				auto bool_ptr2 = v2.get_item<bool>();
				auto bool_ptr_result = new bool((*bool_ptr1) || (*bool_ptr2));
				ret.set_item<bool>(bool_ptr_result);

				return 0;
			};
			return fn( ret_and_item, ret_orex_item, ret);
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

	int evaluate(item_postfix_expression* item, ret_item& ret)
	{


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

			auto fn = [](ret_item& v1,ret_item& v2,ret_item& ret)->int
			{//==============================================

			};

			return fn(ret_type_name,ret_cast_item,ret);
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
			auto fn = [](ret_item& v1,ret_item& ret)->int
			{//=================================


			};
			return fn(ret_unary_item,ret);
		}
		else if (item->op == DEC_OP)
		{
			ret_item ret_unary_item;
			evaluate(item->right2, ret_unary_item);
			auto fn = [](ret_item& v1,ret_item& ret)->int
			{//=================================


			};
			return fn(ret_unary_item,ret);
		}
		else if (item->op == SIZEOF)
		{
			if (item->right3)
			{
				ret_item ret_unary_item;
				evaluate(item->right2, ret_unary_item);
				auto fn = [](ret_item& v1,ret_item& ret)->int
				{//=================================


				};
				return fn(ret_unary_item,ret);
			}
			else if (item->right4)
			{
				ret_item ret_type_name_item;
				evaluate(item->right4, ret_type_name_item);
				auto fn = [](ret_item& v1,ret_item& ret)->int
				{//=================================


				};
				return fn(ret_type_name_item,ret);
			}
		}
		else if (item->op == '&')
		{
			ret_item ret_cast_item;
			evaluate(item->right4, ret_cast_item);
			auto fn = [](ret_item& v1,ret_item& ret)->int
			{//========================================

			};
			return fn(ret_cast_item,ret);
		}
		else if (item->op == '*')
		{
			ret_item ret_cast_item;
			evaluate(item->right4, ret_cast_item);
			auto fn = [](ret_item& v1, ret_item& ret)->int
			{//========================================

			};
			return fn(ret_cast_item,ret);
		}
		else if (item->op == '+')
		{
			ret_item ret_cast_item;
			evaluate(item->right4, ret_cast_item);
			auto fn = [](ret_item& v1, ret_item& ret)->int
			{//========================================

			};
			return fn(ret_cast_item,ret);
		}
		else if (item->op == '-')
		{
			ret_item ret_cast_item;
			evaluate(item->right4, ret_cast_item);
			auto fn = [](ret_item& v1, ret_item& ret)->int
			{//========================================

			};
			return fn(ret_cast_item,ret);
		}
		else if (item->op == '~')
		{
			ret_item ret_cast_item;
			evaluate(item->right4, ret_cast_item);
			auto fn = [](ret_item& v1, ret_item& ret)->int
			{//========================================

			};
			return fn(ret_cast_item,ret);
		}
		else if (item->op == '!')
		{
			ret_item ret_cast_item;
			evaluate(item->right4, ret_cast_item);
			auto fn = [](ret_item& v1, ret_item& ret)->int
			{//========================================

			};
			return fn(ret_cast_item,ret);
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

			auto fn = [](ret_item& op, ret_item& left_val, ret_item& right_val, ret_item& ret)->int
			{//计算赋值运算。
				if ('=' == op.op)
				{//=================================

				}
				else if (MUL_ASSIGN == op.op)
				{//=================================

				}
				else if (DIV_ASSIGN == op.op)
				{//=================================

				}
				else if (MOD_ASSIGN == op.op)
				{//=================================

				}
				else if (ADD_ASSIGN == op.op)
				{//=================================

				}
				else if (SUB_ASSIGN == op.op)
				{//=================================

				}
				else if (LEFT_ASSIGN == op.op)
				{//=================================

				}
				else if (RIGHT_ASSIGN == op.op)
				{//=================================

				}
				else if (AND_ASSIGN == op.op)
				{//=================================

				}
				else if (XOR_ASSIGN == op.op)
				{//=================================

				}
				else if (OR_ASSIGN == op.op)
				{//=================================

				}


				return 0;
			};

			return fn(assignment_op, left_val, right_val,ret);
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
				auto item_fconst = new const_t(float(1.0),item->right.c_str());
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
				auto item_iconst = new const_t(int(100),item->right.c_str());
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