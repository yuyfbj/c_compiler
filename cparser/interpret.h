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

	int evaluate(item_conditional_expression* item, ret_item& ret);
	int evaluate(item_unary_expression* item, ret_item& ret);
	int evaluate(item_assignment_operator* item, ret_item& ret);
	int evaluate(item_postfix_expression* item, ret_item& ret);
	int evaluate(item_cast_expression* item, ret_item& ret);
	int evaluate(item_type_specifier* item, ret_item& ret);
	int evaluate(item_specifier_qualifier_list* item, ret_item& ret);
	int evaluate(item_abstract_declarator* item, ret_item& ret);
	int evaluate(item_type_name* item, ret_item& ret);
	int evaluate(item_unary_expression* item, ret_item& ret);
	int evaluate(item_assignment_expression* item, ret_item& ret);
	int evaluate(item_expression_ex* item, ret_item& ret);
	int evaluate(item_expression* item, ret_item& ret);
	int evaluate(item_primary_expression* item, ret_item& ret);

	


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