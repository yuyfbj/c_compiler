
#include "parser_statement.h"


namespace stmt
{
	//代码风格要整个整理一下，变成清晰的树结构，与产生式对应，这样的代码更清楚。
	//这里不能采用一条线的那种平风格，
	item_expression_statement* expression_statement()
	{
		/*expression_statement
		: ';'
		| expression ';'
		;
		*/
		auto item = NewItem<item_expression_statement>();
		if (!item)
			return NULL;
		std::string val;
		int token = pre_get_token_val(val);
		if (token == ';')
		{//';'
			pop_token();
			item->op = token;
			item->right = val;
			return item;
		}
		auto item1 = expression();
		if (item1)
		{//expression ';'
			item->right1 = item1;
			token = pre_get_token_val(val);
			if (token == ';')
			{
				pop_token();
				return item;
			}
		}
		return ReleaseItem<item_expression_statement>(item);
	}

	
	item_jump_statement* jump_statement()
	{
		/*
		jump_statement
		: GOTO IDENTIFIER ';'
		| CONTINUE ';'
		| BREAK ';'
		| RETURN ';'
		| RETURN expression ';'
		;
		*/
		auto item = NewItem<item_jump_statement>();
		if (!item)
			return NULL;
		std::string val;
		int token = pre_get_token_val(val);
		if (GOTO == token)
		{//GOTO IDENTIFIER ';'
			pop_token();
			item->op = token;
			token = pre_get_token_val(val);
			if (token == IDENTIFIER)
			{
				pop_token();
				auto item1 = NewItem<item_identifier>();
				if (item1)
				{
					item1->op = token;
					item1->right = val;
					token = pre_get_token_val(val);
					if (token == ';')
					{
						pop_token();
						return item;
					}
					ReleaseItem<item_identifier>(item1);
				}
			}
		}			
		else if (CONTINUE == token)
		{// CONTINUE ';'
			pop_token();
			token = pre_get_token_val(val);
			if (token == ';')
			{
				pop_token();
				return item;
			}
		}
		else if (BREAK == token)
		{//BREAK ';'
			pop_token();
			token = pre_get_token_val(val);
			if (token == ';')
			{
				pop_token();
				return item;
			}
		}
		else if (RETURN == token)
		{// RETURN ';'
			pop_token();
			token = pre_get_token_val(val);
			if (token == ';')
			{
				return item;
			}
			else
			{//RETURN expression ';'
				auto item2 = expression();
				if (item2)
				{
					item->right2 = item2;
					token = pre_get_token_val(val);
					if (token == ';')
					{
						pop_token();
						return item;
					}
				}
			}
		}
		return ReleaseItem<item_jump_statement>(item);;
	}


	item_labeled_statement* labeled_statement()
	{
		/*
		labeled_statement
		: IDENTIFIER ':' statement
		| CASE constant_expression ':' statement
		| DEFAULT ':' statement
		;
		*/
		auto item = NewItem<item_labeled_statement>();
		if (!item)
			return NULL;
		std::string val;
		int token = pre_get_token_val(val);
		if (token == IDENTIFIER)
		{//IDENTIFIER ':' statement
			std::string val1;
			int token1 = pre_get_token_val(val1);
			if (token1 == ':')
			{//这里存在一个混淆，所以多预读预判一个字符。尝试一下。
				pop_token();
				item->op = token;
				item->right = val;
				auto item1 = NewItem<item_identifier>();
				if (item1)
				{
					item1->op = token;
					item1->right = val;
					token = pre_get_token_val(val);
					if (token == ':')
					{
						pop_token();
						auto item3 = statement();
						if (item3)
						{
							item->right3 = item3;
							return item;
						}
					}
					ReleaseItem<item_identifier>(item1);
				}
			}
		}
		else if (token == CASE)
		{//CASE constant_expression ':' statement
			pop_token();
			item->op = token;
			item->right = val;
			
			auto item2 = constant_expression();
			if (item2)
			{
				item->right2 = item2;
				token = pre_get_token_val(val);
				if (token == ':')
				{
					pop_token();
					auto item3 = statement();
					if (item3)
					{
						item->right3 = item3;
						return item;
					}
				}
			}
		}
		else if (token == DEFAULT)
		{//DEFAULT ':' statement
			pop_token();
			item->op = token;
			item->right = val;

			token = pre_get_token_val(val);
			if (token == ':')
			{
				pop_token();
				auto item3 = statement();
				if (item3)
				{
					item->right3 = item3;
					return item;
				}
			}
		}
		//error_report();
		return ReleaseItem<item_labeled_statement>(item);

	}


	item_selection_statement* selection_statement()
	{
		/*
		selection_statement
		: IF '(' expression ')' statement
		| IF '(' expression ')' statement ELSE statement
		| SWITCH '(' expression ')' statement
		;
		*/
		auto item = NewItem<item_selection_statement>();
		if (!item)
			return NULL;
		std::string val;
		int token = pre_get_token_val(val);
		if (token == IF)
		{
			//IF '(' expression ')' statement
			pop_token();
			item->op = token;
			item->right = val;

			token = pre_get_token_val(val);
			if (token = '(')
			{//IF '(' expression ')' statement
				pop_token();
				auto item1 = expression();
				if (item1)
				{
					item->right1 = item1;

					token = pre_get_token_val(val);
					if (token == ')')
					{
						pop_token();
						auto item2 = statement();
						if (item2)
						{
							item->right2 = item2;
							token = pre_get_token_val(val);
							if (token == ELSE)
							{//IF '(' expression ')' statement ELSE statement
								auto item3 = statement();
								if (item3)
								{
									item->right3 = item3;
									return item;
								}
							}
							return item;
						}
					}
				}
			}
		}
		else if (token == SWITCH)
		{//SWITCH '(' expression ')' statement
			pop_token();
			item->op = token;
			item->right = val;

			token = pre_get_token_val(val);
			if (token == '(')
			{
				pop_token();
				auto item1 = expression();
				if (item1)
				{
					item->right1 = item1;
					token = pre_get_token_val(val);
					if (token == ')')
					{
						pop_token();
						auto item3 = statement();
						if (item3)
						{
							item->right3 = item3;
							return item;
						}
					}
				}
			}
		}
		//error_report();
		return ReleaseItem<item_selection_statement>(item);
	}

	item_iteration_statement* iteration_statement()
	{
		/*
		iteration_statement
		: WHILE '(' expression ')' statement
		| DO statement WHILE '(' expression ')' ';'
		| FOR '(' expression_statement expression_statement ')' statement
		| FOR '(' expression_statement expression_statement expression ')' statement
		;
		*/
		auto item = NewItem<item_iteration_statement>();
		if (!item)
			return NULL;
		std::string val;
		int token = pre_get_token_val(val);
		if (token == WHILE)
		{//WHILE '(' expression ')' statement
			pop_token();
			item->op = token;
			item->right = val;
			token = pre_get_token_val(val);
			if (token == '(')
			{
				pop_token();
				auto item1 = expression();
				if (item1)
				{
					item->right1 = item1;
					token = pre_get_token_val(val);
					if (token != ')')
					{
						pop_token();
						auto item5 = statement();
						if (item5)
						{
							item->right5 = item5;
							return item;
						}
					}
				}
			}
		}
		else if (token == DO)
		{//DO statement WHILE '(' expression ')' ';'
			pop_token();
			item->op = token;
			item->right = val;
			auto item5 = statement();
			if (item5)
			{
				item->right5 = item5;
				token = pre_get_token_val(val);
				if (token == WHILE)
				{
					pop_token();
					token = pre_get_token_val(val);
					if (token == '(')
					{
						pop_token();
						auto item1 = expression();
						if (item1)
						{
							item->right1 = item1;
							token = pre_get_token_val(val);
							if (token == ')')
							{
								pop_token();
								return item;
							}
						}
					}
				}
			}
		}
		else if (token == FOR)
		{//FOR '(' expression_statement expression_statement ')' statement
			pop_token();
			item->op = token;
			item->right = val;
			token = pre_get_token_val(val);
			if (token == '(')
			{
				pop_token();
				auto item2 = expression_statement();
				if (item2)
				{
					item->right2 = item2;
					auto item3 = expression_statement();
					if (item3)
					{
						item->right3 = item3;
						token = pre_get_token_val(val);
						if (token == ')')
						{
							pop_token();
							auto item5 = statement();
							if (item5)
							{
								item->right5 = item5;
								return item;
							}
						}
						else
						{//FOR '(' expression_statement expression_statement expression ')' statement
							auto item4 = expression();
							if (item4)
							{
								item->right4 = item4;
								if (token == ')')
								{
									pop_token();
									auto item5 = statement();
									if (item5)
									{
										item->right5 = item5;
										return item;
									}
								}
							}
						}
					}
				}
			}
		}
		//error_report();
		return ReleaseItem<item_iteration_statement>(item);
	}
	item_declaration_list* declaration_list()
	{
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
		auto  item = NewItem<item_declaration_list>();
		if (!item)
			return NULL;

		auto item1 = declaration();
		if (item1)
		{
			item->right1 = item1;
			auto item2 = declaration_list();
			if (item2)
			{
				item->right2 = item2;
			}
			return item;
		}
		return ReleaseItem<item_declaration_list>(item);
	}
	item_statement_list* statement_list()
	{
		/*statement_list
		: statement
		| statement_list statement
		改成：
		statement_list
		: statement
		| statement  statement_list

		;*/
		auto  item = NewItem<item_statement_list>();
		if (!item)
			return NULL;
		auto item1 = statement();
		if (item1)
		{
			item->right1 = item1;
			auto item2 = statement_list();
			if (item2)
			{
				item->right2 = item2;
			}
			return item;
		}
		//error_report();
		return ReleaseItem<item_statement_list>(item);
	}
	item_compound_statement* compound_statement()
	{
		/*
		compound_statement
		: '{' '}'
		| '{' statement_list '}'
		| '{' declaration_list '}'
		| '{' declaration_list statement_list '}'
		;
		*/
		auto  item = NewItem<item_compound_statement>();
		if (!item)
			return NULL;
		std::string val;
		int token = pre_get_token_val(val);
		if (token == '{')
		{
			pop_token();
			item->op = token;
			item->right = val;
			token = pre_get_token_val(val);
			if (token == '}')
			{//'{' '}'
				item->right += val;
				return item;
			}

			auto item2 = declaration_list();
			if (item2)
			{
				item->right2 = item2;
				token = pre_get_token_val(val);
				if (token == '}')
				{//'{' declaration_list '}'
					pop_token();
					item->right += val;
					return item;
				}

				auto item1 = statement_list();
				if (item1)
				{//'{' declaration_list statement_list '}'
					item->right1 = item1;
					token = pre_get_token_val(val);
					if (token == '}')
					{
						pop_token();
						item->right += val;
						return item;
					}
				}
			}
			else
			{//'{' statement_list '}'
				auto item1 = statement_list();
				if (item1)
				{
					item->right1 = item1;
					token = pre_get_token_val(val);
					if (token == '}')
					{
						pop_token();
						item->right += val;
						return item;
					}

				}
			}
		}
		//error_report();
		return ReleaseItem<item_compound_statement>(item);
	}

	item_statement* statement()
	{
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
		auto item = NewItem<item_statement>();
		if (!item)
			return NULL;
		auto item1 = jump_statement();
		if (item1)
		{
			item->right1 = item1;
			return item;
		}
		auto item2 = iteration_statement();
		if (item2)
		{
			item->right2 = item2;
			return item;
		}
		auto item3 = selection_statement();
		if (item3)
		{
			item->right3 = item3;
			return item;
		}
		auto item4 = labeled_statement();
		if (item4)
		{
			item->right4 = item4;
			return item;
		}
		auto item5 = compound_statement();
		if (item5)
		{
			item->right5 = item5;
			return item;
		}
		auto item6 = expression_statement();
		if (item6)
		{
			item->right6 = item6;
			return item;
		}
		//error_report();

		return ReleaseItem<item_statement>(item);
	}

	item_function_definition* function_definition()
	{
		/*
		function_definition
		: declaration_specifiers declarator declaration_list compound_statement
		| declaration_specifiers declarator compound_statement
		| declarator declaration_list compound_statement
		| declarator compound_statement
		;
		*/
		auto item = NewItem<item_function_definition>();
		if (!item)
			return NULL;

		auto item1 = declaration_specifiers();
		if (item1)
		{//declaration_specifiers declarator declaration_list compound_statement
			//declaration_specifiers declarator compound_statement
			item->right1 = item1;
			auto item2 = declarator();
			if (item2)
			{
				item->right2 = item2;
				auto item3 = declaration_list();
				if (item3)
				{
					item->right3 = item3;
				}

				auto item4 = compound_statement();
				if (item4)
				{
					item->right4 = item4;
					return item;
				}
			}
		}
		auto item2 = declarator();
		if (item2)
		{//declarator declaration_list compound_statement
			//declarator compound_statement
			item->right2 = item2;
			auto item3 = declaration_list();
			if (item3)
				item->right3 = item3;

			auto item4 = compound_statement();
			if (item4)
			{
				item->right4 = item4;
				return item;
			}
		}
		//error_report();
		return ReleaseItem<item_function_definition>(item);
	}
	item_external_declaration* external_declaration()
	{
		/*
		external_declaration
		: function_definition
		| declaration
		;
		*/
		auto item = NewItem<item_external_declaration>();
		if (!item)
			return NULL;

		auto item1 = function_definition();
		if (item1)
		{
			item->right1 = item1;
			return item;
		}
		auto item2 = declaration();
		if (item2)
		{
			item->right2 = item2;
			return item;
		}
		
		//error_report();
		return ReleaseItem<item_external_declaration>(item);
	}

	item_translation_unit* translation_unit()
	{
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
		auto item = NewItem<item_translation_unit>();
		if (!item)
			return NULL;

		auto item1 = external_declaration();
		if (item1)
		{
			item->right1 = item1;
			auto item2 = translation_unit();
			if (item2)
			{
				item->right2 = item2;
			}
			return item;
		}
		
		//error_report();
		return ReleaseItem<item_translation_unit>(item);
	}

	
	
}