#ifndef INTERPRET_H
#define INTERPRET_H
#include "node.h"
#include "symbol_table.h"
namespace interpret
{
	using namespace symbol;
	using namespace tree_node;
	/*
	为每个语法元素，定义解释执行的方法。
	一种方式是直接依据语法树，来执行。
	则像生成JSON那样，写函数，递归遍历树。


	或定义中间语言，再解释执行中间语言。
	则递归遍历树，生成四元式指令，参数压栈，在栈上进行计算，
	执行结果压栈，挨层进行计算。

	*/
	int evaluate(item_multiplicative_expression* item, ret_item& ret);
	int evaluate(ret_item& ret_main, item_additive_expression_ex* item, ret_item& ret);
	int evaluate(item_additive_expression* item, ret_item& ret);
	int evaluate(ret_item& ret_main, item_shift_expression_ex* item, ret_item& ret);
	int evaluate(item_shift_expression* item, ret_item& ret);
	int evaluate(ret_item& ret_main, item_relational_expression_ex* item, ret_item& ret);
	int evaluate(item_relational_expression* item, ret_item& ret);
	int evaluate(ret_item& ret_main, item_equality_expression_ex* item, ret_item& ret);
	int evaluate(item_equality_expression* item, ret_item& ret);
	int evaluate(ret_item& ret_main, item_and_expression_ex* item, ret_item& ret);
	int evaluate(item_and_expression* item, ret_item& ret);
	int evaluate(item_exclusive_or_expression* item, ret_item& ret);
	int evaluate(item_inclusive_or_expression* item, ret_item& ret);
	int evaluate(item_logical_and_expression_ex* item, ret_item& ret);
	int evaluate(item_logical_and_expression* item, ret_item& ret);
	int evaluate(item_logical_or_expression* item, ret_item& ret);
	int evaluate(item_conditional_expression* item, ret_item& ret);
	int evaluate(item_unary_expression* item, ret_item& ret);
	int evaluate(item_assignment_operator* item, ret_item& ret);

	int evaluate(item_identifier* item, ret_item& ret);
	int evaluate(item_argument_expression_list* item, ret_item& ret);
	int evaluate(item_postfix_expression_ex* item, ret_item& ret);
	int evaluate(item_postfix_expression* item, ret_item& ret);
	int evaluate(item_cast_expression* item, ret_item& ret);
	int evaluate(item_unary_expression* item, ret_item& ret);
	int evaluate(item_assignment_expression* item, ret_item& ret);
	int evaluate(item_expression_ex* item, ret_item& ret);
	int evaluate(item_expression* item, ret_item& ret);
	int evaluate(item_primary_expression* item, ret_item& ret);

	
	
	int evaluate(item_struct_declarator* item, type_struct_or_union* struct_or_union_p);
	int evaluate(item_struct_declarator_list_ex* item, type_struct_or_union* struct_or_union_p);
	int evaluate(ret_item& ret_type_item, item_struct_declarator_list* item, std::map<std::string, var_t*>& member_set);
	
	
	
	int evaluate(item_type_name* item, ret_item& ret);
	int evaluate(item_pointer* item, var_t* var_p);

	int evaluate(item_parameter_list* item, ret_item& ret);
	int evaluate(item_parameter_type_list* item, ret_item& ret);
	int evaluate(item_direct_abstract_declarator* item, var_t* type_p);
	

	int evaluate(item_enumerator* item, std::string& name, int& val);
	int evaluate(item_enumerator_list_ex* item, std::map<std::string, int>& member_set);
	int evaluate(item_enumerator_list* item, std::map<std::string, int>& member_set);
	int evaluate(item_enum_specifier* item, type_enum* enum_p);

	
	int evaluate(item_abstract_declarator* item, ret_item& ret);
	int evaluate(item_declarator* item, var_t* var_p);
	int evaluate(item_direct_declarator* item, var_t* var_p);
	int evaluate(item_direct_declarator_ex* item, var_t* var_p);
	
	int evaluate(item_type_qualifier_list* item, var_t* var_p);
	int evaluate(item_type_qualifier* item, var_t* var_p);
	int evaluate(item_type_specifier* item, ret_item& ret);

	

	int evaluate(item_specifier_qualifier_list* item, var_t* var_p);
	int evaluate(item_struct_declaration* item, std::map<std::string, var_t*>& member_set);
	int evaluate(item_struct_declaration_list* item, std::map<std::string, var_t*>& member_set);
	int evaluate(item_struct_or_union_specifier* item, type_struct_or_union* struct_or_union_p);
	

	


	template<class TP>
	void evaluate_tree(TP* item)
	{
		//直接执行语法树。



	}
	template<class TP>
	void gen_code(TP* item)
	{
		//生成中间代码。



	}




}


#endif