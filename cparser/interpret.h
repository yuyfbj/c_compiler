#ifndef INTERPRET_H
#define INTERPRET_H
#include "node.h"
#include "symbol_table.h"
namespace interpret
{
	using namespace symbol;
	using namespace tree_node;
	/*
	Ϊÿ���﷨Ԫ�أ��������ִ�еķ�����
	һ�ַ�ʽ��ֱ�������﷨������ִ�С�
	��������JSON������д�������ݹ��������


	�����м����ԣ��ٽ���ִ���м����ԡ�
	��ݹ��������������Ԫʽָ�����ѹջ����ջ�Ͻ��м��㣬
	ִ�н��ѹջ��������м��㡣

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
		//ֱ��ִ���﷨����



	}
	template<class TP>
	void gen_code(TP* item)
	{
		//�����м���롣



	}




}


#endif