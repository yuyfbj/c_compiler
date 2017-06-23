
#include "parser_declare.h"

namespace decl
{
	using namespace expr;

	item_type_qualifier_list* type_qualifier_list()
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
		auto item = NewItem<item_type_qualifier_list>();
		if (!item)
			return NULL;

		auto item1 = type_qualifier();
		if (item1)
		{
			item->right1 = item1;
			auto item2 = type_qualifier_list();
			if (item2)
				item->right2 = item2;

			return item;
		}

		//error_report();
		return ReleaseItem<item_type_qualifier_list>(item);
	}

	item_pointer* pointer()
	{
		/*pointer
		: '*'
		| '*' type_qualifier_list
		| '*' pointer
		| '*' type_qualifier_list pointer
		;*/
		auto item = NewItem<item_pointer>();
		if (!item)
			return NULL;
		std::string val;
		int token = pre_get_token_val(val);
		if (token == '*')
		{	
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = type_qualifier_list();
			if (item1)
			{
				item->right1 = item1;

				auto item2 = pointer();
				if (item2)
					item->right2 = item2;

				return item;
			}
			auto item2 = pointer();
			if (item2)
				item->right2 = item2;

			return item;
		}
		

		return ReleaseItem<item_pointer>(item);
	}

	item_direct_abstract_declarator_ex* direct_abstract_declarator_ex()
	{
		/*
		direct_abstract_declarator_ex
		:  '(' ')' direct_abstract_declarator_ex
		|  '(' parameter_type_list ')' direct_abstract_declarator_ex
		|  '[' ']' direct_abstract_declarator_ex
		|  '[' constant_expression ']' direct_abstract_declarator_ex
		*/
		auto item = NewItem<item_direct_abstract_declarator_ex>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (token == '(')
		{
			pop_token();
			item->op = token;
			item->right = val;

			token = pre_get_token_val(val);
			if (token == ')')
			{
				//'(' ')' direct_abstract_declarator_ex
				pop_token();
				item->right += val;
				auto item3 = direct_abstract_declarator_ex();
				if (item3)
				{
					item->right3 = item3;
				}
				return item;
			}
		
			auto item1 = parameter_type_list();
			if (item1)
			{
				//'(' parameter_type_list ')' direct_abstract_declarator_ex
				item->right1 = item1;
				token = pre_get_token_val(val);
				if (token == ')')
				{
					pop_token();
					item->right += val;
					auto item3 = direct_abstract_declarator_ex();
					if (item3)
					{
						item->right3 = item3;
					}
					return item;
				}
			}
		}
		else if (token == '[')
		{	
			pop_token();
			item->op = token;
			item->right = val;

			token = pre_get_token_val(val);
			if (token == ']')
			{//'[' ']' direct_abstract_declarator_ex
				pop_token();
				item->right += val;
				auto item3 = direct_abstract_declarator_ex();
				if (item3)
				{
					item->right3 = item3;
				}
				return item;
			}

			auto item2 = constant_expression();
			if (item2)
			{//'[' constant_expression ']' direct_abstract_declarator_ex
				item->right2 = item2;
				token = pre_get_token_val(val);
				if (token == ']')
				{
					pop_token();
					item->right += val;
					auto item3 = direct_abstract_declarator_ex();
					if (item3)
					{
						item->right3 = item3;
					}
					return item;
				}
			}
		}
		//error_report();
		return ReleaseItem<item_direct_abstract_declarator_ex>(item);
	}
	
	item_direct_abstract_declarator* direct_abstract_declarator()
	{
		/*
		direct_abstract_declarator
		: '(' abstract_declarator ')' direct_abstract_declarator_ex
		| '(' ')' direct_abstract_declarator_ex
		| '(' parameter_type_list ')' direct_abstract_declarator_ex
		| '[' ']' direct_abstract_declarator_ex
		| '[' constant_expression ']' direct_abstract_declarator_ex
		;
		*/

		auto item = NewItem<item_direct_abstract_declarator>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (token == '(')
		{
			pop_token();
			item->op = token;
			item->right = val;

			token = pre_get_token_val(val);
			if (token == ')')
			{
				//'(' ')' direct_abstract_declarator_ex
				pop_token();
				item->right += val;
				auto item4 = direct_abstract_declarator_ex();
				if (item4)
				{
					item->right4 = item4;
				}
				return item;
			}
			auto item1 = abstract_declarator();
			if (item1)
			{//'(' abstract_declarator ')' direct_abstract_declarator_ex
				item->right1 = item1;
				token = pre_get_token_val(val);
				if (token == ')')
				{
					pop_token();
					item->right += val;
					auto item4 = direct_abstract_declarator_ex();
					if (item4)
					{
						item->right4 = item4;
					}
					return item;
				}
			}
			auto item2 = parameter_type_list();
			if (item2)
			{
				//'(' parameter_type_list ')' direct_abstract_declarator_ex
				item->right2 = item2;
				token = pre_get_token_val(val);
				if (token == ')')
				{
					pop_token();
					item->right += val;
					auto item4 = direct_abstract_declarator_ex();
					if (item4)
					{
						item->right4 = item4;
					}
					return item;
				}
			}
			//error_report();
			return ReleaseItem<item_direct_abstract_declarator>(item);
		}
		else if (token == '[')
		{
			pop_token();
			item->op = token;
			item->right = val;

			token = pre_get_token_val(val);
			if (token == ']')
			{//'[' ']' direct_abstract_declarator_ex
				pop_token();
				item->right += val;
				auto item4 = direct_abstract_declarator_ex();
				if (item4)
				{
					item->right4 = item4;
				}
				return item;
			}
			
			auto item3 = constant_expression();
			if (item3)
			{//'[' constant_expression ']' direct_abstract_declarator_ex
				item->right3 = item3;
				token = pre_get_token_val(val);
				if (token == ']')
				{
					pop_token();
					item->right += val;
					auto item4 = direct_abstract_declarator_ex();
					if (item4)
					{
						item->right4 = item4;
					}
					return item;
				}
			}
		}
		//error_report();
		return ReleaseItem<item_direct_abstract_declarator>(item);
	}
	item_abstract_declarator* abstract_declarator()
	{
		/*	abstract_declarator
		: pointer
		| direct_abstract_declarator
		| pointer direct_abstract_declarator
		;
		*/
		auto item = NewItem<item_abstract_declarator>();
		if (!item)
			return NULL;

		auto item1 = pointer();
		if (item1)
		{//pointer
			item->right1 = item1;
			auto item2 = direct_abstract_declarator();
			if (item2)
			{//pointer direct_abstract_declarator
				item->right2 = item2;
				return item;
			}
			return item;
		}
		auto item2 = direct_abstract_declarator();
		if (item2)
		{//direct_abstract_declarator
			item->right2 = item2;
			return item;
		}
		return ReleaseItem<item_abstract_declarator>(item);
	}
	
	item_storage_class_specifier* storage_class_specifier()
	{
		/*
		storage_class_specifier
		: TYPEDEF
		| EXTERN
		| STATIC
		| AUTO
		| REGISTER
		;
		*/
		auto item = NewItem<item_storage_class_specifier>();
		if (!item)
			return NULL;
		std::string val;
		int token = pre_get_token_val(val);
		if (TYPEDEF == token
			|| EXTERN == token
			|| STATIC == token
			|| AUTO == token
			|| REGISTER == token
			)
		{
			pop_token();
			item->op = token;
			item->right = val;
			return item;
		}
		return ReleaseItem<item_storage_class_specifier>(item);
	}
	
	item_enumerator* enumerator()
	{
		/*
		enumerator
		: IDENTIFIER
		| IDENTIFIER '=' constant_expression
		;*/
		auto item = NewItem<item_enumerator>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (token == IDENTIFIER)
		{
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = NewItem<item_identifier>();
			if (item1)
			{
				item1->op = token;
				item1->right = val;
				item->right1 = item1;
			}
			
			token = pre_get_token_val(val);
			if (token == '=')
			{
				pop_token();
				item->op = token;
				item->right += val;
				auto item2 = constant_expression();
				if (item2)
				{
					item->right2 = item2;
					return item;
				}
			}
			return item;
		}
		return ReleaseItem<item_enumerator>(item);;
	}

	item_enumerator_list_ex* enumerator_list_ex()
	{
		/*	enumerator_list_ex
		: ',' enumerator  enumerator_list_ex
		|empty
		;*/
		auto item = NewItem<item_enumerator_list_ex>();
		if (!item)
			return NULL;
		std::string val;
		int token = pre_get_token_val(val);
		if (token == ',')
		{
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = enumerator();
			if (item1)
			{
				item->right1 = item1;
				auto item2 = enumerator_list_ex();
				if (item2)
					item->right2 = item2;

				return item;
			}
		}
		
		return ReleaseItem<item_enumerator_list_ex>(item);
	}
	item_enumerator_list* enumerator_list()
	{
		/*enumerator_list
		: enumerator
		| enumerator_list ',' enumerator
		;

		enumerator_list
		: enumerator  enumerator_list_ex
		;
	
		*/
		auto item = NewItem<item_enumerator_list>();
		if (!item)
			return NULL;

		auto item1 = enumerator();
		if (item1)
		{
			item->right1 = item1;

			auto item2 = enumerator_list_ex();
			if (item2)
			{
				item->right2 = item2;
			}
			
			return item;
		}
		//error_report();
		return ReleaseItem<item_enumerator_list>(item);
	}
	item_enum_specifier* enum_specifier()
	{
		/*
		enum_specifier
		: ENUM '{' enumerator_list '}'
		| ENUM IDENTIFIER '{' enumerator_list '}'
		| ENUM IDENTIFIER
		;
		*/
		auto item = NewItem<item_enum_specifier>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (token == ENUM)
		{
			pop_token();
			item->op = token;
			item->right = val;

			token = pre_get_token_val(val);
			if (token == IDENTIFIER)
			{
				pop_token();
				item->right += val;
				auto item2 = NewItem<item_identifier>();
				item2->op = token;
				item2->right = val;

				item->right2 = item2;

				//ENUM IDENTIFIER
				token = pre_get_token_val(val);
				if (token == '{')
				{	// ENUM IDENTIFIER '{' enumerator_list '}'
					pop_token();
					item->right += val;
					auto item1 = enumerator_list();
					item->right1 = item1;

					token = pre_get_token_val(val);
					if (token == '}')
					{
						pop_token();
						item->right += val;
						return item;
					}
				}
				return item;
			}
			else if (token == '{')
			{//ENUM '{' enumerator_list '}'
				pop_token();
				item->right += val;
				auto item1 = enumerator_list();
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
		return ReleaseItem<item_enum_specifier>(item);

	}
	item_struct_or_union* struct_or_union()
	{
		/*
		struct_or_union
		: STRUCT
		| UNION
		;
		*/
		auto item = NewItem<item_struct_or_union>();
		if (!item)
			return NULL;
		std::string val;
		int token = pre_get_token_val(val);
		if (token == STRUCT
			|| token == UNION
			)
		{
			pop_token();
			item->op = token;
			item->right = val;
			return item;
		}
		return ReleaseItem<item_struct_or_union>(item);
	}
	
	item_specifier_qualifier_list* specifier_qualifier_list()
	{
		/*
		specifier_qualifier_list
		: type_specifier specifier_qualifier_list
		| type_specifier
		| type_qualifier specifier_qualifier_list
		| type_qualifier
		;
		*/
		auto item = NewItem<item_specifier_qualifier_list>();
		if (!item)
			return NULL;

		auto item1 = type_specifier();
		if (item1)
		{
			item->right1 = item1;

			auto item3 = specifier_qualifier_list();
			if (item3)
				item->right3 = item3;

			return item;
		}
		auto item2 = type_qualifier();
		if (item2)
		{
			item->right2 = item2;
			auto item3 = specifier_qualifier_list();
			if (item3)
				item->right3 = item3;

			return item;
		}
		
		return ReleaseItem<item_specifier_qualifier_list>(item);
	}
	
	
	item_struct_declarator* struct_declarator()
	{
		/*
		struct_declarator
		:':' constant_expression 
		|declarator 
		| declarator ':' constant_expression
		;
		*/
		auto item = NewItem<item_struct_declarator>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (token == ':')
		{// ':' constant_expression
			pop_token();
			item->op = token;
			item->right = val;

			auto item2 = constant_expression();
			if (item2)
			{
				item->right2 = item2;
				return item;
			}
		}

		auto item1 = declarator();
		if (item1)
		{
			item->right1 = item1;
			token = pre_get_token_val(val);
			if (token == ':')
			{
				pop_token();
				item->right += val;
				auto item2 = constant_expression();
				if (item2)
				{
					item->right2 = item2;
					return item;
				}
			}
			return item;
		}
		
		//error_report();
		return ReleaseItem<item_struct_declarator>(item);
	}

	item_struct_declarator_list_ex* struct_declarator_list_ex()
	{
		/*
		struct_declarator_list_ex
		:',' struct_declarator struct_declarator_list_ex
		|empty
		;
		*/
		auto item = NewItem<item_struct_declarator_list_ex>();
		if (!item)
			return NULL;
		std::string val;
		int token = pre_get_token_val(val);
		if (token == ',')
		{
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = struct_declarator();
			if (item1)
			{
				item->right1 = item1;

				auto item2 = struct_declarator_list_ex();
				if (item2)
					item->right2 = item2;

				return item;
			}
		}
		//error_report();
		return ReleaseItem<item_struct_declarator_list_ex>(item);
	}

	item_struct_declarator_list* struct_declarator_list()
	{

		/*
		struct_declarator_list
		: struct_declarator
		| struct_declarator_list ',' struct_declarator
		;
		*/
		/*
		struct_declarator_list
		: struct_declarator struct_declarator_list_ex
		;
		*/
		auto item = NewItem<item_struct_declarator_list>();
		if (!item)
			return NULL;

		auto item1 = struct_declarator();
		if (item1)
		{
			item->right1 = item1;

			auto item2 = struct_declarator_list_ex();
			if (item2)
			{
				item->right2 = item2;
			}
			return item;
		}

		//error_report();
		return ReleaseItem<item_struct_declarator_list>(item);
	}
	item_struct_declaration* struct_declaration()
	{
		/*struct_declaration
		: specifier_qualifier_list struct_declarator_list ';'
		; */
		auto item = NewItem<item_struct_declaration>();
		if (!item)
			return NULL;

		auto item1 = specifier_qualifier_list();
		if (item1)
		{
			auto item2 = struct_declarator_list();
			if (item2)
			{
				item->right2 = item2;
				std::string val;
				int token = pre_get_token_val(val);
				if (token == ';')
				{
					return item;
				}
			}
		}

		//error_report();
		return ReleaseItem<item_struct_declaration>(item);
	}
	item_struct_declaration_list* struct_declaration_list()
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
		auto item = NewItem<item_struct_declaration_list>();
		if (!item)
			return NULL;

		auto item1 = struct_declaration();
		if (item1)
		{
			item->right1 = item1;

			auto item2 = struct_declaration_list();
			if (item2)
				item->right2 = item2;

			return item;
		}
		
		//error_report();
		return ReleaseItem<item_struct_declaration_list>(item);
	}
	item_struct_or_union_specifier* struct_or_union_specifier()
	{
		/*
		struct_or_union_specifier
		: struct_or_union IDENTIFIER '{' struct_declaration_list '}'
		| struct_or_union IDENTIFIER
		| struct_or_union '{' struct_declaration_list '}'
		;
		*/
		auto item = NewItem<item_struct_or_union_specifier>();
		if (!item)
			return NULL;

		auto item1 = struct_or_union();
		if (item1)
		{
			item->right1 = item1;
			std::string val;
			int token = pre_get_token_val(val);
			if ('{' == token)
			{//struct_or_union '{' struct_declaration_list '}'
				pop_token();
				item->op = token;
				item->right = val;
				auto item3 = struct_declaration_list();
				if (item3)
				{
					item->right3 = item3;
					token = pre_get_token_val(val);
					if ('}' == token)
					{
						pop_token();
						item->right += val;
						return item;
					}
				}
			}
			else if (IDENTIFIER == token)
			{
				//struct_or_union IDENTIFIER '{' struct_declaration_list '}'
				//	| struct_or_union IDENTIFIER
				pop_token();
				item->op = token;
				item->right = val;
				auto item2 = NewItem<item_identifier>();
				if (item2)
				{
					item2->op = token;
					item2->right = val;

					item->right2 = item2;

					token = pre_get_token_val(val);
					if ('{' == token)
					{
						pop_token();
						item->right += val;
						auto item3 = struct_declaration_list();
						if (item3)
						{
							item->right3 = item3;
							token = pre_get_token_val(val);
							if ('}' == token)
							{
								pop_token();
								item->right += val;
								return item;
							}
						}
					}
				}
				return item;
			}
		}
		
		return ReleaseItem<item_struct_or_union_specifier>(item);
	}
	item_type_specifier* type_specifier()
	{
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
		auto item = NewItem<item_type_specifier>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (
			VOID == token
			|| CHAR == token
			|| SHORT == token
			|| INT == token
			|| LONG == token
			|| FLOAT == token
			|| DOUBLE == token
			|| SIGNED == token
			|| UNSIGNED == token
			|| TYPE_NAME == token
			)
		{
			pop_token();
			item->op = token;
			item->right = val;
			return item;
		}

		auto item1 = struct_or_union_specifier();
		if (item1)
		{
			item->right1 = item1;
			return item;
		}
		auto item2 = enum_specifier();
		if (item2)
		{
			item->right2 = item2;
			return item;
		}

		return ReleaseItem<item_type_specifier>(item);
	}
	item_type_qualifier* type_qualifier()
	{
		/*type_qualifier
		: CONST
		| VOLATILE
		;*/
		auto item = NewItem<item_type_qualifier>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (CONST == token || VOLATILE == token)
		{
			pop_token();
			item->op = token;
			item->right = val;
			return item;
		}
		return ReleaseItem<item_type_qualifier>(item);

	}
	item_declaration_specifiers* declaration_specifiers()
	{
		/*declaration_specifiers
		: storage_class_specifier
		| storage_class_specifier declaration_specifiers
		| type_specifier
		| type_specifier declaration_specifiers
		| type_qualifier
		| type_qualifier declaration_specifiers
		;*/
		auto item = NewItem<item_declaration_specifiers>();
		if (!item)
			return NULL;

		auto item1 = storage_class_specifier();
		if (item1)
		{// storage_class_specifier
			// storage_class_specifier declaration_specifiers
			item->right1 = item1;
			auto item2 = declaration_specifiers();
			if (item2)
				item->right2 = item2;
			return item;
		}
		auto item3 = type_specifier();
		if (item3)
		{// type_specifier
			// type_specifier declaration_specifiers
			item->right3 = item3;
			auto item2 = declaration_specifiers();
			if (item2)
				item->right2 = item2;
			return item;
		}
		auto item4 = type_qualifier();
		if (item4)
		{//type_qualifier
			// type_qualifier declaration_specifiers
			item->right4 = item4;
			auto item2 = declaration_specifiers();
			if (item2)
				item->right2 = item2;
			return item;
		}

		return ReleaseItem<item_declaration_specifiers>(item);
	}
	item_parameter_declaration* parameter_declaration()
	{
		//parameter_declaration
		//	: declaration_specifiers declarator
		//	| declaration_specifiers abstract_declarator
		//	| declaration_specifiers
		//	;
		auto item = NewItem<item_parameter_declaration>();
		if (!item)
			return NULL;
		auto item1 = declaration_specifiers();
		if (item1)
		{
			item->right1 = item1;
			auto item2 = declarator();
			if (item2)
			{
				item->right2 = item2;
				return item;
			}
			auto item3 = abstract_declarator();
			if (item3)
			{
				item->right3 = item3;
				return item;
			}

			return item;
		}

		//error_report();
		return ReleaseItem<item_parameter_declaration>(item);
	}
	item_parameter_list_ex* parameter_list_ex()
	{
		/*
		parameter_list_ex
		: ',' parameter_declaration parameter_list_ex
		|empty
		;
		*/
		auto item = NewItem<item_parameter_list_ex>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (',' == token)
		{
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = parameter_declaration();
			if (item1)
			{
				item->right1 = item1;
				auto item2 = parameter_list_ex();
				if (item2)
				{
					item->right2 = item2;
					return item;
				}
				return item;
			}
		}
		
		//error_report();
		return ReleaseItem<item_parameter_list_ex>(item);
	}
	item_parameter_list* parameter_list()
	{
		/*parameter_list
		: parameter_declaration parameter_list_ex
		;*/
		auto item = NewItem<item_parameter_list>();
		if (!item)
			return NULL;
		auto item1 = parameter_declaration();
		if (item1)
		{
			auto item2 = parameter_list_ex();
			if (item2)
				item->right2 = item2;

			return item;
		}

		//error_report();
		return ReleaseItem<item_parameter_list>(item);
	}
	item_parameter_type_list* parameter_type_list()
	{
		/*
		parameter_type_list
		: parameter_list
		| parameter_list ',' ELLIPSIS
		;
		*/
		auto item = NewItem<item_parameter_type_list>();
		if (!item)
			return NULL;

		auto item1 = parameter_list();
		if (item1)
		{
			item->right1 = item1;
			std::string val;
			int token = pre_get_token_val(val);
			if (',' == token)
			{
				pop_token();
				item->op = token;
				item->right = val;
				token = pre_get_token_val(val);
				if (token == ELLIPSIS)
				{
					pop_token();
					item->right += val;
					return item;
				}
			}
			return item;
		}

		//error_report();
		return ReleaseItem<item_parameter_type_list>(item);
	}

	item_identifier_list_ex* identifier_list_ex()
	{
		/*
		identifier_list_ex
		: ',' IDENTIFIER identifier_list_ex
		|empty
		*/
		auto item = NewItem<item_identifier_list_ex>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);

		if (token == ',')
		{
			pop_token();
			item->op = token;
			item->right = val;
			token = pre_get_token_val(val);
			if (token == IDENTIFIER)
			{
				pop_token();
				item->right += val;
				auto item1 = NewItem<item_identifier>();
				if (item1)
				{
					item1->right = val;
					item->right1 = item1;

					auto item2 = identifier_list_ex();
					if (item2)
						item->right2 = item2;
					return item;
				}
			}
		}
		return ReleaseItem<item_identifier_list_ex>(item);
	}
	item_identifier_list* identifier_list()
	{
		
		/*
			identifier_list
		: IDENTIFIER identifier_list_ex
		*/
		auto item = NewItem<item_identifier_list>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (token == IDENTIFIER)
		{
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = NewItem<item_identifier>();
			if (item1)
			{
				item1->op = token;
				item1->right = val;
				item->right1 = item1;

				auto item2 = identifier_list_ex();
				if (item2)
					item->right2 = item2;
				return item;
			}
		}
		return ReleaseItem<item_identifier_list>(item);
	}

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

	item_direct_declarator_ex* direct_declarator_ex()
	{
		/*
		direct_declarator_ex
		: '[' constant_expression ']' direct_declarator_ex
		|  '[' ']' direct_declarator_ex
		|  '(' parameter_type_list ')' direct_declarator_ex
		|  '(' identifier_list ')' direct_declarator_ex
		|  '(' ')' direct_declarator_ex
		|empty
		;
		*/

		auto item = NewItem<item_direct_declarator_ex>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (token == '[')
		{
			pop_token();
			item->op = token;
			item->right = val;
			token = pre_get_token_val(val);
			if (token == ']')
			{
				//'[' ']' direct_declarator_ex
				pop_token();
				item->right += val;
				auto item4 = direct_declarator_ex();
				if (item4)
					item->right4 = item4;
				return item;
			}
			
			auto item1 = constant_expression();
			if (item1)
			{//'[' constant_expression ']' direct_declarator_ex
				item->right1 = item1;
				token = pre_get_token_val(val);
				if (token == ']')
				{
					pop_token();
					item->right += val;
					auto item4 = direct_declarator_ex();
					if (item4)
						item->right4 = item4;
					return item;
				}
			}
		}
		else if (token == '(')
		{
			pop_token();
			item->op = token;
			item->right = val;
			token = pre_get_token_val(val);
			if (token == ')')
			{//  '(' ')' direct_declarator_ex
				pop_token();
				item->right += val;
				auto item4 = direct_declarator_ex();
				if (item4)
					item->right4 = item4;
				return item;
			}
			
			auto item2 = parameter_type_list();
			if (item2)
			{// '(' parameter_type_list ')' direct_declarator_ex
				item->right2 = item2;
				token = pre_get_token_val(val);
				if (token == ')')
				{
					pop_token();
					item->right += val;
					auto item4 = direct_declarator_ex();
					if (item4)
						item->right4 = item4;
					return item;
				}
			}
			// '(' ')' direct_declarator_ex
			auto item3 = identifier_list();
			if (item3)
			{
				item->right3 = item3;
				token = pre_get_token_val(val);
				if (token == ')')
				{
					pop_token();
					item->right += val;
					auto item4 = direct_declarator_ex();
					if (item4)
						item->right4 = item4;
					return item;
				}
			}
		}
		return ReleaseItem<item_direct_declarator_ex>(item);
	}

	item_direct_declarator* direct_declarator()
	{
		/*
		direct_declarator
		: IDENTIFIER direct_declarator_ex
		| '(' declarator ')' direct_declarator_ex
		;
		*/
		auto item = NewItem<item_direct_declarator>();
		if (!item)
			return NULL;
			
		std::string val;
		int token = pre_get_token_val(val);
		if (IDENTIFIER == token)
		{//IDENTIFIER direct_declarator_ex
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = NewItem<item_identifier>();
			if (item1)
			{
				item1->op = token;
				item1->right = val;
				item->right1 = item1;

				auto item3 = direct_declarator_ex();
				if (item3)
				{
					item->right3 = item3;
				}
				return item;
			}
		}
		else if ('(' == token)
		{//'(' declarator ')' direct_declarator_ex
			pop_token();
			item->op = token;
			item->right = val;
			auto item2 = declarator();
			if (item2)
			{
				item->right2 = item2;
				token = pre_get_token_val(val);
				if (token == ')')
				{
					pop_token();
					item->right += val;
					auto item3 = direct_declarator_ex();
					if (item3)
					{
						item->right3 = item3;
					}

					return item;
				}
			}
		}

		return ReleaseItem<item_direct_declarator>(item);
	}

	item_declarator * declarator()
	{
		/*
		declarator
		: pointer direct_declarator
		| direct_declarator
		;
		*/
		auto item = NewItem<item_declarator>();
		if (!item)
			return NULL;

		auto item1 = pointer();
		if (item1)
		{//pointer direct_declarator
			item->right1 = item1;
			auto item2 = direct_declarator();
			if (item2)
			{
				item->right2 = item2;
				return item;
			}
		}
		else
		{//direct_declarator
			auto item2 = direct_declarator();
			if (item2)
			{
				item->right2 = item2;
				return item;
			}
		}
		
		return ReleaseItem<item_declarator>(item);
	}
	item_initializer_list_ex* initializer_list_ex()
	{
		/*
		initializer_list_ex
		: ',' initializer initializer_list_ex
		|empty
		*/
		auto item = NewItem<item_initializer_list_ex>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (',' == token)
		{
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = initializer();
			if (item1)
			{
				item->right1 = item1;

				auto item2 = initializer_list_ex();
				if (item2)
					item->right2 = item2;
				return item;
			}
		}

		return ReleaseItem<item_initializer_list_ex>(item);
	}
	item_initializer_list* initializer_list()
	{
		/*
		initializer_list
		: initializer initializer_list_ex
		;
		*/
		auto item = NewItem<item_initializer_list>();
		if (!item)
			return NULL;
		
		auto item1 = initializer();
		if (item1)
		{
			item->right1 = item1;

			auto item2 = initializer_list_ex();
			if (item2)
				item->right2 = item2;

			return item;
		}
		return ReleaseItem<item_initializer_list>(item);
	}
	item_initializer* initializer()
	{
		/*
		initializer
		: assignment_expression
		| '{' initializer_list '}'
		| '{' initializer_list ',' '}'
		;
		*/
		auto item = NewItem<item_initializer>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (token == '{')
		{// '{' initializer_list '}'
			// '{' initializer_list ',' '}'
			pop_token();
			item->op = token;
			item->right = val;
			auto item2 = initializer_list();
			if (item2)
			{
				item->right2 = item2;

				token = pre_get_token_val(val);
				if (token == '}')
				{
					pop_token();
					item->right += val;
					return item;
				}
				if (token == ',')
				{
					pop_token();
					token = pre_get_token_val(val);
					if (token != '}')
					{
						pop_token();
						item->right += val;
						return item;
					}
				}
			}
		}

		auto item1 = assignment_expression();
		if (item1)
		{
			item->right1 = item1;
			return item;
		}

		return ReleaseItem<item_initializer>(item);
		
	}
	item_init_declarator* init_declarator()
	{
		/*init_declarator
		: declarator
		| declarator '=' initializer
		;*/
		auto item = NewItem<item_init_declarator>();
		if (!item)
			return NULL;

		auto item1 = declarator();
		if (item1)
		{
			item->right1 = item1;

			std::string val;
			int token = pre_get_token_val(val);
			if ('=' == token)
			{
				pop_token();
				item->op = token;
				item->right = val;
				auto item2 = initializer();
				if (item2)
				{
					item->right2 = item2;
					return item;
				}
			}
			return item;
		}
		//error_report();
		return ReleaseItem<item_init_declarator>(item);
	}
	item_init_declarator_list_ex* init_declarator_list_ex()
	{
		/*
		init_declarator_list_ex
		:',' init_declarator init_declarator_list_ex
		|empty
		;
		*/
		auto item = NewItem<item_init_declarator_list_ex>();
		if (!item)
			return NULL;

		std::string val;
		int token = pre_get_token_val(val);
		if (token == ',')
		{
			pop_token();
			item->op = token;
			item->right = val;
			auto item1 = init_declarator();
			if (item1)
			{
				item->right1 = item1;
				auto item2 = init_declarator_list_ex();
				if (item2)
					item->right2 = item2;
				return item;
			}
		}
		return ReleaseItem<item_init_declarator_list_ex>(item);
	}
	item_init_declarator_list* init_declarator_list()
	{
		/*
		init_declarator_list
		: init_declarator init_declarator_list_ex
		;
		*/
		auto item = NewItem<item_init_declarator_list>();
		if (!item)
			return NULL;
		auto item1 = init_declarator();
		if (item1)
		{
			item->right1 = item1;
			auto item2 = init_declarator_list_ex();
			if (item2)
				item->right2 = item2;

			return item;
		}
		return ReleaseItem<item_init_declarator_list>(item);
	}


	item_declaration* declaration()
	{
		/*declaration
		: declaration_specifiers ';'
		| declaration_specifiers init_declarator_list ';'
		;*/
		auto item = NewItem<item_declaration>();
		if (!item)
			return NULL;

		auto item1 = declaration_specifiers();
		if (item1)
		{
			item->right1 = item1;

			std::string val;
			int token = pre_get_token_val(val);
			if (';' == token)
			{
				pop_token();
				return item;
			}

			auto item2 = init_declarator_list();
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
		return ReleaseItem<item_declaration>(item);
	}
}