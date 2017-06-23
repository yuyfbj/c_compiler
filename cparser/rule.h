#ifndef RULE_H
#define RULE_H

#include <stack>
#include <vector>
#include <sstream>
#include <iostream>
#include <queue>  
#include <fstream>
#include <string>


#include <regex>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <future>
#include <array>  
#include <tuple>
#include "token_def.h"

#include "json/json.h"

namespace rule
{

	std::function<bool()> error_report = []()->bool
	{
		std::cout << "Error:"  << std::endl;
		DebugBreak();
		return true;
	};

	std::function<int(std::string&)> pre_get_token_val;
	std::function<int()> pre_get_token;
	
	std::function<void()> pop_token;





	struct _contain
	{
		//������ģ�庯����ʹ�������ⲿָ����
		
		template<class T>
		void set_context(T* context)
		{
			p_context = (long long)context;
		};

		template<class T>
		T* get_context()
		{
			return (T*)p_context;
		}

		long long p_context = NULL;


		std::string name = "_contain";
		virtual std::string get_name()
		{

			return name;
		}
		virtual std::string gen_json()
		{
			return std::string("");
		}

		


		Json::Value json_value;

		bool is_eof()
		{
			return b_eof;
		}
		bool b_eof = false;


	};


	template <int n>
	struct _t :public _contain
	{
		
		std::string val;
		using type = int;
		static const int value = n;
		static _t<n>* new_item()
		{
			return new _t<n>;
		}
		bool operator()()
		{
			std::string tempval;
			int token = pre_get_token_val(tempval);
			if (token == 0)
			{
				b_eof = true;
				return true;
			}
			if ( token != value)
			{
				//error_report();
				return false;
			}
			val = tempval;
			pop_token();
			return true;
		}
		virtual std::string get_name()
		{
			name = "_t";
			return name;
		}
		virtual std::string gen_json()
		{
			json_value["type"] = "_t";
			json_value["val_token"] = value;
			json_value["val_str"] = val;

			Json::FastWriter jsFastWriter;
			return jsFastWriter.write(json_value);
		}

	};

	/*self_rule
		�����������ָ����ǰ���Լ��������Ա�Ķ���ͷ�����Ҫ�����������Ҫ���ɣ�
		���͵ĺ�󶨡�
		������������ʵ������һ��������������һ������ʱ�������͡�
		

		*/


	//�����ʵ������һ��������������װһ��δ֪���ͣ�����ʱ������
	

	/*
	����ʽ���������˵��������ռλ��������û����Ҫ���������ˡ�
	*/
	using stop_item = _t<21000>;

	/*
	����ʽ�����������˵���Ƶ������˿գ����Բ��ü���������Ҳ���Խ����ˡ�
	*/
	using empty_rule = _t<21001>;
	/*
	����ʽ���������˵��Ҫ�ݹ��ˡ���NEWһ����ǰ�����ٴβ���set_context<T>���������Ž�����Ȼ��ݹ������
	*/
	using self_rule = _t<21002>;

	using parent_rule = _t<21003>;



	template<class r,class parent_type = stop_item>
	bool parse(r** right)
	{
		if (r::value == empty_rule::value)
		{
			//�������չ�������Բ��������ֱ�ӷ��سɹ��ˡ���������һ��ITEMΪNULL��
			return false;
		}
		if (r::value == stop_item::value)
		{
			return true;
		}

		if (r::value == parent_rule::value)
		{
			auto item = (r*)r::new_item();
			
			auto item1 = parent_type::new_item();
			item->set_context<parent_type>(item1);
			bool bRet = (*item1)();
			if (bRet)
				*right = item;
			//�ҵݹ������һ�����Ƶ������ԣ����ﲻ���жϷ���ֵ���п�ʱֻ�᷵��true,�ݹ���ϣ�������ֱ�ӷ��ء�
			return bRet;
		}

		auto item = (r*)r::new_item();
		if (item)
		{
			bool bRet = (*item)();
			if (!bRet)
			{
				//error_report();
				return false;
			}
			*right = item;
		}
		return true;
	}

	template<
		class r1,
		class r2 = stop_item, 
		class r3 = stop_item, 
		class r4 = stop_item, 
		class r5 = stop_item, 
		class r6 = stop_item, 
		class r7 = stop_item, 
		class r8 = stop_item, 
		class r9 = stop_item
	>
	struct _r :public _contain
	{
		//l:r1 r2 r3...;
		
		std::string val;
		using type = _r<r1, r2, r3, r4, r5,r6, r7, r8, r9>;
		static const int value = 1212121;


		r1* right1 = NULL; 
		r2* right2 = NULL;
		r3* right3 = NULL;
		r4* right4 = NULL;
		r5* right5 = NULL;
		r6* right6 = NULL;
		r7* right7 = NULL;
		r8* right8 = NULL;
		r9* right9 = NULL;

		static _r<r1, r2, r3,r4,r5,r6,r7,r8,r9>* new_item()
		{
			return new _r<r1, r2, r3,r4,r5,r6,r7,r8,r9>;
		}

		
		bool operator ()()
		{
			bool bRet = true;
			bRet = parse<r1>(&right1);
			if (right1 && right1->is_eof())
				return true;
			if (!bRet)
				return bRet;

			if (r2::value == stop_item::value)
				return true;
			bRet = parse<r2>(&right2);
			if (right2 && right2->is_eof())
				return true;

			if (!bRet)
				return bRet;
			
			if (r3::value == stop_item::value)
				return true;
			bRet = parse<r3>(&right3);
			if (right3 && right3->is_eof())
				return true;
			if (!bRet)
				return bRet;
			
			if (r4::value == stop_item::value)
				return true;
			bRet = parse<r4>(&right4);
			if (right4 && right4->is_eof())
				return true;
			if (!bRet)
				return bRet;
			
			if (r5::value == stop_item::value)
				return true;
			bRet = parse<r5>(&right5);
			if (right5 && right5->is_eof())
				return true;
			if (!bRet)
				return bRet;
			
			if (r6::value == stop_item::value)
				return true;
			bRet = parse<r6>(&right6);
			if (right6 && right6->is_eof())
				return true;
			if (!bRet)
				return bRet;

			if (r7::value == stop_item::value)
				return true;
			bRet = parse<r7>(&right7);
			if (right7 && right7->is_eof())
				return true;
			if (!bRet)
				return bRet;
			
			if (r8::value == stop_item::value)
				return true;
			bRet = parse<r8>(&right8);
			if (right8 && right8->is_eof())
				return true;
			if (!bRet)
				return bRet;
			
			if (r9::value == stop_item::value)
				return true;
			bRet = parse<r9>(&right9);
			if (right9 && right9->is_eof())
				return true;
			if (!bRet)
				return bRet;

			return bRet;
		}
		
		virtual std::string gen_json()
		{
			json_value["type"] = "_r";
			std::string t_name = get_name();
			json_value["name"] = t_name;
			json_value["val"] = val;

			if (right1)
			{
				right1->gen_json();
				json_value["right1"] = right1->json_value;
			}
			if (right2)
			{
				right2->gen_json();
				json_value["right2"] = right2->json_value;
			}
			if (right3)
			{
				right3->gen_json();
				json_value["right3"] = right3->json_value;
			}
			if (right4)
			{
				right4->gen_json();
				json_value["right4"] = right4->json_value;
			}
			
			if (right5)
			{
				right5->gen_json();
				json_value["right5"] = right5->json_value;
			}
			
			if (right6)
			{
				right6->gen_json();
				json_value["right6"] = right6->json_value;
			}
			if (right7)
			{
				right7->gen_json();
				json_value["right7"] = right7->json_value;
			}
			
			if (right8)
			{
				right8->gen_json();
				json_value["right8"] = right8->json_value;
			}
			
			if (right9)
			{
				right9->gen_json();
				json_value["right9"] = right9->json_value;
			}

			return std::string("");
		}
		
	};

	
	template<
		class r1,
		class r2 = stop_item,
		class r3 = stop_item,
		class r4 = stop_item,
		class r5 = stop_item,
		class r6 = stop_item,
		class r7 = stop_item,
		class r8 = stop_item,
		class r9 = stop_item,
		class r10 = stop_item,
		class r11 = stop_item
	>
	struct _rs :public _contain
	{
		/*l :
		r1
		|r2
		|r3
		...
		;

		*/
		
		std::string val;

		using type = _rs<r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11>;
		static const int value = 23232323;

		r1* right1 = NULL;
		r2* right2 = NULL;
		r3* right3 = NULL;
		r4* right4 = NULL;
		r5* right5 = NULL;
		r6* right6 = NULL;
		r7* right7 = NULL;
		r8* right8 = NULL;
		r9* right9 = NULL;
		r10* right10 = NULL;
		r11* right11 = NULL;

		static _rs<r1, r2, r3,r4,r5,r6,r7,r8,r9,r10,r11>* new_item()
		{
			return new _rs<r1, r2, r3, r4, r5, r6, r7, r8, r9,r10,r11>;
		}

		bool operator()()
		{
			bool bRet = true;
			bRet = parse<r1>(&right1);
			if (right1 && right1->is_eof())
				return true;
			if (bRet)
				return bRet;

			if (r2::value == stop_item::value)
				return true;

			bRet = parse<r2,type>(&right2);
			if (right2 && right2->is_eof())
				return true;
			if (bRet)
				return bRet;

			if (r3::value == stop_item::value)
				return true;

			bRet = parse<r3,type>(&right3);
			if (right3 && right3->is_eof())
				return true;
			if (bRet)
				return bRet;
			if (r4::value == stop_item::value)
				return true;

			bRet = parse<r4,type>(&right4);
			if (right4 && right4->is_eof())
				return true;
			if (bRet)
				return bRet;

			if (r5::value == stop_item::value)
				return true;

			bRet = parse<r5,type>(&right5);
			if (right5 && right5->is_eof())
				return true;
			if (bRet)
				return bRet;

			if (r6::value == stop_item::value)
				return true;

			bRet = parse<r6,type>(&right6);
			if (right6 && right6->is_eof())
				return true;
			if (bRet)
				return bRet;

			if (r7::value == stop_item::value)
				return true;
			bRet = parse<r7,type>(&right7);
			if (right7 && right7->is_eof())
				return true;
			if (bRet)
				return bRet;

			if (r8::value == stop_item::value)
				return true;

			bRet = parse<r8,type>(&right8);
			if (right8 && right8->is_eof())
				return true;
			if (bRet)
				return bRet;

			if (r9::value == stop_item::value)
				return true;

			bRet = parse<r9,type>(&right9);
			if (right9 && right9->is_eof())
				return true;
			if (bRet)
				return bRet;

			if (r10::value == stop_item::value)
				return true;

			bRet = parse<r10,type>(&right10);
			if (right10 && right10->is_eof())
				return true;
			if (bRet)
				return bRet;

			if (r11::value == stop_item::value)
				return true;

			bRet = parse<r11,type>(&right11);
			if (right11 && right11->is_eof())
				return true;
			if (bRet)
				return bRet;

			return true;
		}

		virtual std::string gen_json()
		{
			json_value["type"] = "_rs";
			std::string t_name = get_name();
			json_value["name"] = t_name;

			if (right1)
			{
				right1->gen_json();
				json_value["right1"] = right1->json_value;

			}
			if (right2)
			{
				right2->gen_json();
				json_value["right2"] = right2->json_value;
			}
			if (right3)
			{
				right3->gen_json();
				json_value["right3"] = right3->json_value;
			}
			if (right4)
			{
				right4->gen_json();
				json_value["right4"] = right4->json_value;
			}
			if (right5)
			{
				right5->gen_json();
				json_value["right5"] = right5->json_value;
			}
			if (right6)
			{
				right6->gen_json();
				json_value["right6"] = right6->json_value;
			}
			if (right7)
			{
				right7->gen_json();
				json_value["right7"] = right7->json_value;
			}
			if (right8)
			{
				right8->gen_json();
				json_value["right8"] = right8->json_value;
			}
			if (right9)
			{
				right9->gen_json();
				json_value["right9"] = right9->json_value;
			}
			if (right10)
			{
				right10->gen_json();
				json_value["right10"] = right10->json_value;
			}
			if (right11)
			{
				right11->gen_json();
				json_value["right11"] = right11->json_value;
			}

			return std::string("");
		}

	};

	//----------------------------------------------------------------------------------
	struct type_name;
	struct assignment_operator;
	struct primary_expression;
	struct unary_operator;
	struct unary_expression;
	
	struct expression;
	struct conditional_expression;
	struct assignment_expression;
	struct expression_ex;
	struct primary_expression;
	struct cast_expression;

	struct argument_expression_list_ex;
	struct argument_expression_list;

	struct postfix_expression_ex;
	struct postfix_expression;

	struct multiplicative_expression_ex;
	struct multiplicative_expression;

	struct additive_expression_ex;
	struct additive_expression;

	struct relational_expression_ex;
	struct relational_expression;

	struct equality_expression_ex;
	struct equality_expression;

	struct and_expression_ex;
	struct and_expression;

	struct exclusive_or_expression_ex;
	struct exclusive_or_expression;

	struct inclusive_or_expression_ex;
	struct inclusive_or_expression;

	struct logical_and_expression_ex;
	struct logical_and_expression;

	struct logical_or_expression_ex;
	struct logical_or_expression;




	//----------------------------------------------------------------------------------

	//�������ս�������ս��������ʽ������ģ��
	//���涨���������ʽ���Ա���ԡ�
	//--------------------------------------------
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
	struct type_name : public _rs<
		_t<VOID>
		, _t< CHAR>
		, _t< SHORT>
		, _t< INT>
		, _t< LONG>
		, _t< FLOAT>
		, _t< DOUBLE>
		, _t< SIGNED>
		, _t< UNSIGNED>
	>
	{
		
		type_name()
		{
			name = "type_name";
		}

	};
	//--------------------------------------------
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
	struct assignment_operator :public _rs<
		_t<'='>
		, _t<MUL_ASSIGN>
		, _t< DIV_ASSIGN>
		, _t< MOD_ASSIGN>
		, _t< ADD_ASSIGN>
		, _t< SUB_ASSIGN>
		, _t< LEFT_ASSIGN>
		, _t< RIGHT_ASSIGN>
		, _t< AND_ASSIGN>
		, _t< XOR_ASSIGN>
		, _t< OR_ASSIGN>
	>
	{
		
		assignment_operator()
		{
			name = "assignment_operator";
		}
	};
	//--------------------------------------------
	/*unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;*/
	struct  unary_operator :public _rs<
		 _t<'&'>
		, _t<'*'>
		, _t<'+'>
		, _t<'-'>
		, _t<'~'>
		, _t<'!'>
	>
	{
		
		unary_operator()
		{
			name = "unary_operator";
		}
	
	};
	
	//--------------------------------------------
	/*argument_expression_list
	: assignment_expression argument_expression_list_ex
	;

	argument_expression_list_ex
	: ',' assignment_expression argument_expression_list_ex
	| EMPTY
	;*/

	struct  argument_expression_list_ex :public _rs<
		_r<_t<','>, assignment_expression, parent_rule>
		, empty_rule
	>
	{
		
		argument_expression_list_ex()
		{
			name = "argument_expression_list_ex";
		}
	

	};


	struct argument_expression_list :public  _rs<
		_r<assignment_expression, argument_expression_list_ex>
	>
	{
		
		argument_expression_list()
		{
			name = "argument_expression_list";
		}
	
	};

	//--------------------------------------------
	/*������ݹ��
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
	
	
	struct  postfix_expression_ex :public  _rs<
		 _r<_t<'['>, expression, _t<']'>, parent_rule>
		 , _r<_t<'('>, _t<')'>, parent_rule>
		 , _r<_t<'('>, argument_expression_list, _t<')'>, parent_rule>
		 , _r<_t<','>, _t<IDENTIFIER>, parent_rule>
		 , _r<_t<PTR_OP>, _t<IDENTIFIER>, parent_rule>
		 , _r<_t<INC_OP>, parent_rule>
		 , _r<_t<DEC_OP>, parent_rule>
		, empty_rule
	>
	{
		
		postfix_expression_ex()
		{
			name = "postfix_expression_ex";
		}
		
	};

	struct  postfix_expression :public  _rs<
		_r<primary_expression, postfix_expression_ex>
	>
	{
		
		postfix_expression()
		{
			name = "postfix_expression";
		}
	
	};
	//--------------------------------------------
	//unary_expression
	//	: postfix_expression
	//	| INC_OP unary_expression
	//	| DEC_OP unary_expression
	//	| unary_operator cast_expression
	//	| SIZEOF unary_expression
	//	| SIZEOF '(' type_name ')'
	//	;
	/*����ʽ��˳����Ҫ������*/
	struct unary_expression :public  _rs<
		 postfix_expression
		, _r<_t<INC_OP>, parent_rule>
		, _r<_t<DEC_OP>, parent_rule>
		, _r<_t<SIZEOF>, _t<'('>, type_name, _t<')'>>
		, _r<_t<SIZEOF>, parent_rule>
		, _r<unary_operator, cast_expression>
	>
	{
		
		unary_expression()
		{
			name = "unary_expression";
		}
		
	};
	//--------------------------------------------
	/*cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	;*/
	//���͵��໥���á�������ṹ�ģ���ǰ������


	struct cast_expression : public  _rs<
		unary_expression
		, _r<_t<'('>, type_name, _t<')'>, parent_rule>
	>
	{
		
		cast_expression()
		{
			name = "cast_expression";
		}
		
	};
	//--------------------------------------------

	/*multiplicative_expression
	: cast_expression   multiplicative_expression_ex
	;
	multiplicative_expression_ex
	:  '*' cast_expression multiplicative_expression_ex
	| '/' cast_expression multiplicative_expression_ex
	| '%' cast_expression multiplicative_expression_ex
	| EMPTY
	;*/

	//Ϊÿ������ʽ���巵�����ͣ�������OK�ˡ�

	struct  multiplicative_expression_ex :public _rs<
		_r<_t<'*'>, cast_expression, parent_rule>
		, _r<_t<'/'>, cast_expression, parent_rule>
		, _r<_t<'%'>, cast_expression, parent_rule>
		, empty_rule
	>
	{
		
		multiplicative_expression_ex()
		{
			name = "multiplicative_expression_ex";
		}
		
	};

	struct multiplicative_expression :public _rs<
		_r<cast_expression, multiplicative_expression_ex>
	>
	{
		
		multiplicative_expression()
		{
			name = "multiplicative_expression";
		}
		
	};
	//--------------------------------------------
	/*additive_expression
	: multiplicative_expression additive_expression_ex
	;
	additive_expression_ex
	: '+' multiplicative_expression additive_expression_ex
	| '-' multiplicative_expression additive_expression_ex
	| EMPTY
	;*/

	struct additive_expression_ex :public _rs<
		_r<_t<'+'>, multiplicative_expression, parent_rule>
		, _r<_t<'-'>, multiplicative_expression, parent_rule>
		, empty_rule
	>
	{
		
		additive_expression_ex()
		{
			name = "additive_expression_ex";
		}
		
	};
	struct additive_expression : public _rs<
		_r<multiplicative_expression, additive_expression_ex>
	>
	{
		
		additive_expression()
		{
			name = "additive_expression";
		}
		
	};

	//--------------------------------------------
	/*shift_expression
	: additive_expression  shift_expression_ex
	;
	shift_expression_ex
	:  LEFT_OP additive_expression shift_expression_ex
	| RIGHT_OP additive_expression shift_expression_ex
	| EMPTY
	;*/
	struct shift_expression_ex : public  _rs<
		 _r<_t<LEFT_OP>, additive_expression, parent_rule>
		, _r<_t<RIGHT_OP>, additive_expression, parent_rule>
		, empty_rule
	>
	{
		
		shift_expression_ex()
		{
			name = "shift_expression_ex";
		}
		
	};
	struct shift_expression :public  _rs<
		_r<additive_expression, shift_expression_ex>
	>
	{
		
		shift_expression()
		{
			name = "shift_expression";
		}
	
	};
	//--------------------------------------------
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
	struct relational_expression_ex :public  _rs<
		_r<_t<'<'>, shift_expression, parent_rule>
		, _r<_t<'>'>, shift_expression, parent_rule>
		, _r<_t<LE_OP>, shift_expression, parent_rule>
		, _r<_t<GE_OP>, shift_expression, parent_rule>
		, empty_rule
	>
	{
		
		relational_expression_ex()
		{
			name = "relational_expression_ex";
		}
		
	};
	struct relational_expression : public  _rs<
		_r<shift_expression, relational_expression_ex>
	>
	{
		
		relational_expression()
		{
			name = "relational_expression";
		}
		
	};
	//--------------------------------------------
	/*equality_expression
	: relational_expression equality_expression_ex
	;
	equality_expression_ex
	: EQ_OP relational_expression equality_expression_ex
	| NE_OP relational_expression equality_expression_ex
	| EMPTY
	;
	*/
	struct equality_expression_ex :public  _rs<
		 _r<_t<EQ_OP>, relational_expression, parent_rule>
		, _r<_t<NE_OP>, relational_expression, parent_rule>
		, empty_rule
	>
	{
		
		equality_expression_ex()
		{
			name = "equality_expression_ex";
		}
		
	};

	struct equality_expression :public _rs<
		_r<relational_expression, equality_expression_ex>
	>
	{
		
		equality_expression()
		{
			name = "equality_expression";
		}
		
	};
	//--------------------------------------------
	/*and_expression
	: equality_expression and_expression_ex
	;
	and_expression_ex
	:	 '&' equality_expression and_expression_ex
	| EMPTY*/
	struct and_expression_ex :public _rs<
		_r<_t<'&'>, equality_expression, parent_rule>
		, empty_rule
	>
	{
		
		and_expression_ex()
		{
			name = "and_expression_ex";
		}
		
	};
	struct and_expression :public _rs<
		_r<equality_expression, and_expression_ex>
	>
	{
		
		and_expression()
		{
			name = "and_expression";
		}
		
	};
	//--------------------------------------------
	/*
	exclusive_or_expression
	: and_expression  exclusive_or_expression_ex
	;
	exclusive_or_expression_ex
	| '^' and_expression exclusive_or_expression_ex
	| EMPTY
	;*/
	struct exclusive_or_expression_ex :public _rs<
		 _r<_t<'^'>, and_expression, parent_rule>
		, empty_rule
	>
	{
		
		exclusive_or_expression_ex()
		{
			name = "exclusive_or_expression_ex";
		}
		
	};
	struct exclusive_or_expression :public _rs<
		_r<and_expression, exclusive_or_expression_ex>
	>
	{
		
		exclusive_or_expression()
		{
			name = "exclusive_or_expression";
		}
		
	};
	//--------------------------------------------
	/*
	inclusive_or_expression
	: exclusive_or_expression inclusive_or_expression_ex
	;
	inclusive_or_expression_ex
	:  '|' exclusive_or_expression inclusive_or_expression_ex
	|EMPTY;
	*/
	struct inclusive_or_expression_ex :public  _rs<
		_r<_t<'|'>, exclusive_or_expression, parent_rule>
		, empty_rule
	>
	{
		
		inclusive_or_expression_ex()
		{
			name = "inclusive_or_expression_ex";
		}
		
	};
	struct inclusive_or_expression :public _rs<
		_r<exclusive_or_expression, inclusive_or_expression_ex>
	>
	{
		
		inclusive_or_expression()
		{
			name = "inclusive_or_expression";
		}
		
	};
	//--------------------------------------------
	/*logical_and_expression
	: inclusive_or_expression  logical_and_expression_ex
	;
	logical_and_expression_ex
	:  AND_OP inclusive_or_expression 	logical_and_expression_ex
	| EMPTY
	;*/
	struct logical_and_expression_ex :public  _rs <
		 _r<_t<AND_OP>, inclusive_or_expression, parent_rule>
		, empty_rule
	>
	{
		
		logical_and_expression_ex()
		{
			name = "logical_and_expression_ex";
		}
		
	};
	struct logical_and_expression :public _rs<
		_r<inclusive_or_expression, logical_and_expression_ex>
	>
	{
		
		logical_and_expression()
		{
			name = "logical_and_expression";
		}
		
	};

	//--------------------------------------------
	/*
	logical_or_expression
	: logical_and_expression  logical_or_expression_ex
	;
	logical_or_expression_ex
	: OR_OP logical_and_expression logical_or_expression_ex
	|EMPTY
	;
	*/
	struct  logical_or_expression_ex : public _rs<
		_r<_t<OR_OP>, logical_and_expression, parent_rule>
		, empty_rule
	>
	{
		
		logical_or_expression_ex()
		{
			name = "logical_or_expression_ex";
		}
		
	};
	struct logical_or_expression :public _rs<
		_r<logical_and_expression, logical_or_expression_ex>
	>
	{
		
		logical_or_expression()
		{
			name = "logical_or_expression";
		}
		
	};

	//--------------------------------------------
	//conditional_expression
	//	: logical_or_expression
	//	| logical_or_expression '?' expression ':' conditional_expression
	
	struct conditional_expression : public _rs <
		 logical_or_expression
		, _r<logical_or_expression, _t<'?'>, expression, _t<':'>, parent_rule>
	>
	{
		
		conditional_expression()
		{
			name = "conditional_expression";
		}
		
	};
	//--------------------------------------------
	/*
	assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;
	*/
	struct  assignment_expression :public  _rs<
		conditional_expression
		, _r< unary_expression, assignment_operator, parent_rule>
	>
	{
		
		assignment_expression()
		{
			name = "assignment_expression";
		}
		
	};

	//--------------------------------------------
	//	expression_ex
	//	: ',' assignment_expression expression_ex
	//	| EMPTY

	////������ݹ顣
	//expression
	//	:   assignment_expression expression_ex


	struct  expression_ex :public  _rs<
		_r<_t<','>, assignment_expression, parent_rule>
		, empty_rule
	>{};
	struct expression :public _rs<
		_r<assignment_expression, expression_ex>
	>
	{
		
		expression()
		{
			name = "expression";
		}
		
	};

	//--------------------------------------------
	/*primary_expression
		: IDENTIFIER
		| CONSTANT
		|F_CONSTANT
		|I_CONSTANT
		| STRING_LITERAL
		| '(' expression ')'
		;*/

	struct  primary_expression :public _rs<
		 _t<IDENTIFIER>
		, _t<CONSTANT>
		, _t<F_CONSTANT>
		, _t<I_CONSTANT>
		, _t<STRING_LITERAL>
		, _r<_t<'('>, expression, _t<')'>>
	>
	{
		
		primary_expression()
		{
			name = "primary_expression";
		}
		
		
	};




	//-------------------------------------------------------------------
	//���ⲿ���Ľ�������
	void main_parse()
	{
		//��ʼ�������С�
	
		struct expression* p = (struct expression*)expression::new_item();
		bool bRet = (*p)();

		p->gen_json();

		Json::FastWriter writer;

		
		std::string strTree = writer.write(p->json_value);

		std::ofstream of("c:\\tree.json");
		if (of.is_open())
		{
			of << strTree;
			of.flush();
			of.close();
		}
		return;
	}


}


#endif