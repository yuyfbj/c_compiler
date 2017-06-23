#ifndef Y_TAB_H
#define Y_TAB_H
#include <conio.h>


#define	IDENTIFIER	258
#define	CONSTANT	259
#define	STRING_LITERAL	260
#define	SIZEOF	261
#define	PTR_OP	262
#define	INC_OP	263
#define	DEC_OP	264
#define	LEFT_OP	265
#define	RIGHT_OP	266
#define	LE_OP	267
#define	GE_OP	268
#define	EQ_OP	269
#define	NE_OP	270
#define	AND_OP	271
#define	OR_OP	272
#define	MUL_ASSIGN	273
#define	DIV_ASSIGN	274
#define	MOD_ASSIGN	275
#define	ADD_ASSIGN	276
#define	SUB_ASSIGN	277
#define	LEFT_ASSIGN	278
#define	RIGHT_ASSIGN	279
#define	AND_ASSIGN	280
#define	XOR_ASSIGN	281
#define	OR_ASSIGN	282
#define	TYPE_NAME	283
#define	TYPEDEF	284
#define	EXTERN	285
#define	STATIC	286
#define	AUTO	287
#define	REGISTER	288
#define	CHAR	289
#define	SHORT	290
#define	INT	291
#define	LONG	292
#define	SIGNED	293
#define	UNSIGNED	294
#define	FLOAT	295
#define	DOUBLE	296
#define	CONST	297
#define	VOLATILE	298
#define	VOID	299
#define	STRUCT	300
#define	UNION	301
#define	ENUM	302
#define	ELLIPSIS	303
#define	CASE	304
#define	DEFAULT	305
#define	IF	306
#define	ELSE	307
#define	SWITCH	308
#define	WHILE	309
#define	DO	310
#define	FOR	311
#define	GOTO	312
#define	CONTINUE	313
#define	BREAK	314
#define	RETURN	315

#define	ALIGNAS 316
#define	ALIGNOF 317
#define	ATOMIC 318
#define	BOOL   319
#define	COMPLEX 320
#define	GENERIC  321
#define	IMAGINARY   322
#define	NORETURN  323
#define	STATIC_ASSERT  324
#define	THREAD_LOCAL  325
#define	FUNC_NAME   326

#define F_CONSTANT  327

#define I_CONSTANT 328

#define INLINE  329
#define RESTRICT 330

#define TYPEDEF_NAME 321

#define ENUMERATION_CONSTANT 322


//各种表达式的集合定义。
//定义的产生式的结构结点。
//=====================================================
//所表达式要用的结构都在这里。
enum  item_expression_type{
	type_assignment_operator = 100,
	type_unary_operator,
	type_primary_expression,

	type_expression,
	type_expression_ex,

	type_assignment_expression,

	type_conditional_expression,
	type_unary_expression,

	type_identifier,
	type_postfix_expression,
	type_postfix_expression_ex,

	type_cast_expression,
	type_constant_expression,

	type_argument_expression_list,
	type_argument_expression_list_ex,

	type_type_specifier,
	type_type_name,

	type_logical_or_expression,
	type_logical_or_expression_ex,
	type_logical_and_expression,
	type_logical_and_expression_ex,

	type_inclusive_or_expression,
	type_inclusive_or_expression_ex,

	type_exclusive_or_expression,
	type_exclusive_or_expression_ex,

	type_and_expression,
	type_and_expression_ex,

	type_equality_expression,
	type_equality_expression_ex,

	type_relational_expression,
	type_relational_expression_ex,


	type_shift_expression,
	type_shift_expression_ex,

	type_additive_expression,
	type_additive_expression_ex,

	type_multiplicative_expression,
	type_multiplicative_expression_ex,

	type_empty_rule,
	type_self_rule,
	type_parent_rule,

	//-------------------------------
	//声明
	type_declaration,
	type_declaration_specifiers,
	type_init_declarator_list,
	
	
	storage_class_specifier,
	
	type_type_qualifier,

	type_init_declarator,
	type_declarator,
	type_initializer,
	type_storage_class_specifier,

	type_struct_or_union_specifier,
	type_enum_specifier,

	type_struct_or_union,

	type_struct_declaration_list,
	type_struct_declaration,
	type_specifier_qualifier_list,
	

	type_enumerator_list,
	type_enumerator,

	type_pointer,
	type_direct_declarator,
	type_parameter_type_list,

	type_identifier_list,
	type_type_qualifier_list,

	
	type_parameter_list,

	type_parameter_declaration,

	
	type_abstract_declarator,
	type_direct_abstract_declarator,

	




	









};
namespace tree_node
{

	//声明
	
	struct item_init_declarator_list
	{

	};

	struct item_storage_class_specifier
	{

	};
	
	struct item_type_specifier
	{

	};
	struct item_type_qualifier
	{
		int type = type_type_qualifier;
		int gen_index;
		int op;

	};
	/*declaration_specifiers
		: storage_class_specifier
		| storage_class_specifier declaration_specifiers
		| type_specifier
		| type_specifier declaration_specifiers
		| type_qualifier
		| type_qualifier declaration_specifiers
		;*/
	struct item_declaration_specifiers
	{
		int type = type_declaration;
		int gen_index;
		int op;
		item_storage_class_specifier* right1;
		item_declaration_specifiers* right2;
		item_type_specifier* right3;
		item_type_qualifier* right4;

	};
	/*declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;*/
	struct item_declaration
	{
		int type = type_declaration;
		int gen_index;
		int op;
		item_declaration_specifiers* right1;
		item_init_declarator_list* right2;
	};



	/*	
		
		type_init_declarator_list,


		storage_class_specifier,

		type_type_qualifier,

		type_init_declarator,
		type_declarator,
		type_initializer,
		type_storage_class_specifier,

		type_struct_or_union_specifier,
		type_enum_specifier,

		type_struct_or_union,

		type_struct_declaration_list,
		type_struct_declaration,
		type_specifier_qualifier_list,


		type_enumerator_list,
		type_enumerator,

		type_pointer,
		type_direct_declarator,
		type_parameter_type_list,

		type_identifier_list,
		type_type_qualifier_list,


		type_parameter_list,

		type_parameter_declaration,


		type_abstract_declarator,
		type_direct_abstract_declarator,*/


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
	struct item_assignment_operator
	{
		int type = type_assignment_operator;
		int gen_index;
		int right;
	};

	struct item_unary_operator
	{
		int type = type_unary_operator;
		int gen_index;
		int op;
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
		

	struct item_expression;
	struct item_primary_expression
	{
		int type = type_primary_expression;
		int gen_index;
		int op;
		item_expression* right1;
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
	struct item_expression_ex
	{
		int type = type_expression_ex;
		int gen_type;
		int op;
		bool is_empty;
		item_assignment_expression* right1;
		item_expression_ex* right2;
	};
	struct item_expression
	{
		int type = type_expression;
		int gen_index;
		int op;
		item_assignment_expression* right1;
		item_expression_ex* right2;
	};


	/*
	assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;
	*/
	struct item_conditional_expression;
	struct item_unary_expression;
	struct item_assignment_expression
	{
		int type = type_assignment_expression;
		int gen_index;
		int op;
		item_conditional_expression* right1;
		item_unary_expression* right2;
		item_assignment_operator* right3;
		item_assignment_expression* right4;
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
	struct item_postfix_expression;
	struct item_cast_expression;
	struct item_type_name;//========
	struct item_unary_expression
	{
		int type = type_unary_expression;
		int gen_index;
		item_postfix_expression* right1;
		int op;
		item_unary_expression* right2;
		item_cast_expression* right3;
		item_type_name* right4;
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
	struct item_identifier
	{
		int type = type_identifier;
		int gen_index;
		int op;
	};
	struct item_argument_expression_list;
	struct item_postfix_expression_ex
	{
		int type = type_postfix_expression_ex;
		int gen_index;
		int op;
		
		item_expression* right1;
		item_postfix_expression_ex* right2;
		item_identifier * right3;
		item_argument_expression_list* right4;
		
		
	};

	struct item_postfix_expression
	{
		int type = type_postfix_expression;
		int gen_index;
		int op;
		item_primary_expression* right1;
		item_postfix_expression_ex* right2;
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

	struct item_argument_expression_list_ex
	{
		int type = type_argument_expression_list_ex;
		int gen_index;
		int op;
		item_assignment_expression* right1;
		item_argument_expression_list_ex* right2;

	};
	struct item_argument_expression_list
	{
		int type = type_argument_expression_list;
		int gen_index;
		int op;
		item_assignment_expression* right1;
		item_argument_expression_list_ex* right2;
	};
	

	//=======================================

	//conditional_expression
	//	: logical_or_expression
	//	| logical_or_expression '?' expression ':' conditional_expression

	struct item_logical_or_expression;
	struct item_conditional_expression
	{
		int type = type_conditional_expression;
		int gen_index;
		int op;
		item_logical_or_expression* right1;
		item_expression * right2;
		item_conditional_expression* right3;
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


	struct item_logical_and_expression;
	struct item_logical_or_expression_ex
	{
		int type = type_logical_or_expression_ex;
		int gen_index;
		int op;
		item_logical_and_expression* right1;
		item_logical_or_expression_ex* right2;

	};
	struct item_logical_or_expression
	{
		int type = type_logical_or_expression;
		int gen_index;
		int op;
		item_logical_and_expression* right1;
		item_logical_or_expression_ex* right2;
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
	struct item_inclusive_or_expression;

	struct item_logical_and_expression_ex
	{
		int type = type_logical_and_expression_ex;
		int gen_index;
		int op;
		item_inclusive_or_expression* right1;
		item_logical_and_expression_ex* right2;
	};

	struct item_logical_and_expression
	{
		int type = type_logical_and_expression;
		int gen_index;
		int op;
		item_inclusive_or_expression* right1;
		item_logical_and_expression_ex* right2;
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
	struct item_exclusive_or_expression;
	struct item_inclusive_or_expression_ex
	{
		int type = type_inclusive_or_expression_ex;
		int gen_index;
		int op;
		item_exclusive_or_expression* right1;
		item_inclusive_or_expression_ex* right2;
	};
	struct item_inclusive_or_expression
	{
		int type = type_inclusive_or_expression;
		int gen_index;
		int op;
		item_exclusive_or_expression* right1;
		item_inclusive_or_expression_ex* right2;
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
	struct item_and_expression;

	struct item_exclusive_or_expression_ex
	{
		int type = type_exclusive_or_expression_ex;
		int gen_index;
		int op;
		item_and_expression* right1;
		item_exclusive_or_expression_ex* right2;
	};

	struct item_exclusive_or_expression
	{
		int type = type_exclusive_or_expression;
		int gen_index;
		int op;
		item_and_expression* right1;
		item_exclusive_or_expression_ex* right2;
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
	struct item_equality_expression;

	struct item_and_expression_ex
	{
		int type = type_and_expression_ex;
		int gen_index;
		int op;
		item_equality_expression* right1;
		item_and_expression_ex* right2;
	};
	struct item_and_expression
	{
		int type = type_and_expression;
		int gen_index;
		int op;
		item_equality_expression* right1;
		item_and_expression_ex* right2;
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

	struct item_relational_expression;
	struct item_equality_expression_ex
	{
		int type = type_equality_expression_ex;
		int gen_index;
		int op;
		item_relational_expression* right1;
		item_equality_expression_ex* right2;
	};
	struct item_equality_expression
	{
		int type = type_equality_expression;
		int gen_index;
		int op;
		item_relational_expression* right1;
		item_equality_expression_ex* right2;
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
	struct item_shift_expression;

	struct item_relational_expression_ex
	{
		int type = type_relational_expression_ex;
		int gen_index;
		int op;
		item_shift_expression* right1;
		item_relational_expression_ex* right2;
	};


	struct item_relational_expression
	{
		int type = type_relational_expression;
		int gen_index;
		int op;
		item_shift_expression* right1;
		item_relational_expression_ex* right2;
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

	struct item_additive_expression;

	struct item_shift_expression_ex
	{
		int type = type_shift_expression_ex;
		int gen_index;
		int op;
		item_additive_expression* right1;
		item_shift_expression_ex* right2;

	};
	struct item_shift_expression
	{
		int type = type_shift_expression;
		int gen_index;
		int op;
		item_additive_expression* right1;
		item_shift_expression_ex* right2;

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

	struct item_additive_expression_ex
	{
		int type = type_additive_expression_ex;
		int gen_index;
		int op;
		item_multiplicative_expression* right1;
		item_additive_expression_ex* right2;
	};
	struct item_additive_expression
	{
		int type = type_additive_expression;
		int gen_index;
		int op;
		item_multiplicative_expression* right1;
		item_additive_expression_ex* right2;
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

	struct item_multiplicative_expression_ex	
	{
		int type = type_multiplicative_expression_ex;
		int gen_index;
		int op;
		item_cast_expression* right1;
		item_multiplicative_expression_ex* right2;

	};
	struct item_multiplicative_expression
	{
		int type = type_multiplicative_expression;
		int gen_index;
		int op;
		item_cast_expression* right1;
		item_multiplicative_expression_ex* right2;
	
	};

	/*cast_expression
		: unary_expression
		| '(' type_name ')' cast_expression
		;*/

	struct item_cast_expression
	{
		int type = type_cast_expression;
		int gen_index;
		int op;
		item_unary_expression* right1;
		item_type_name* right2;
		item_cast_expression* right3;

	};


	/*constant_expression
		: conditional_expression
		;*/


	struct item_constant_expression
	{
		int type = type_constant_expression;
		int gen_index;
		int op;
		item_conditional_expression* right1;
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
	//struct item_type_specifier;
	struct item_type_name
	{
		int type = type_type_name;
		int gen_index;
		int op;
		
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










	//==============================================================
	//下面定义语句相关部分。







}
#endif








