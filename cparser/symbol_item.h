#ifndef  SYMBOL_ITEM_H
#define SYMBOL_ITEM_H
#include <map>
#include <string>
#include "token_def.h"
namespace symbol
{
	/*
	语义的几个问题，需要搞清楚：
	1.语义动作或值的传递：
	比如场景：经过多种节点，其实只是传递。
	2.语义的种类：
	比如每种数据结构的声明，操作等。
	3.针对各种数据类型，可能返回的值类型是不同的，需要统一：
	比如：每种类型的变量都是：
	template<class t>
	struct var_t
	{
		using type = t;
		std::string name;
		std::string val;
	};

	
	都要定义一系列数据结构，最好是通用的数据结构，这样代码写起来才能简单些。
	
	*/

	struct item
	{
		virtual int get_type() = 0;


	};

	template <int n>
	struct _op
	{
		using type = int;
		static const int value = n;
	};
	using null_type = _op<0>;

	

	//这个结构将成为变体的容器，一切符号计算都在这个变体里操作。
	//
	struct ret_item
	{
		int op = 0;
		int type = 0;
		template<class T>
		void set_item(T* it)
		{
			item = it;
		}
		template<class T>
		T* get_item()
		{
			return (T*)item;
		}

		void* item = NULL;
	};

	struct variant_t
	{
		template<class T>
		void set(T* it)
		{
			item = it;
		}
		template<class T>
		T* get()
		{
			return (T*)item;
		}

		void* item = NULL;
	};

	template <int n>
	struct name_t
	{
		static const int type = n;
		std::string name;
	};

	


	template <int n>
	struct value_t
	{
		static const int type = n;
		std::string val;
	};


	//声明，
	struct declare_t :public item
	{
		const int type = DECLARE;
		std::string name;
		std::string val;
		virtual int get_type()
		{
			return type;
		}
	};
	//外部引入
	struct extern_t :public item
	{
		const int type = EXTERN;
		std::string name;
		std::string val;
		virtual int get_type()
		{
			return type;
		}
	};
	//标号
	struct label_t :public item
	{
		int type = LABEL;
		std::string name;
		std::string val;
		virtual int get_type()
		{
			return type;
		}
	};
	
	//变量
	struct var_t:public item
	{
		int type = IDENTIFIER;
		virtual int get_type()
		{
			return type;
		}

		enum vt{
			vt_void_ptr = 100
			,vt_char_ptr
			,vt_short_ptr
			,vt_int_ptr
			,vt_long_ptr
			,vt_float_ptr
			,vt_double_ptr
			,vt_struct_ptr
			,vt_enum_ptr
		};
		int var_type = 0;
		int size = 0;
		std::string name;
		
		union
		{
			void*	void_ptr = NULL;
			char*	char_ptr;
			short*	short_ptr;
			int*	int_ptr;
			long*	long_ptr;
			float*  float_ptr;
			double* double_ptr;
			void*   struct_ptr;
			void*   enum_ptr;
		};
	};

	//常量

	struct const_t :public var_t
	{
		const_t(float f,const char* val)
		{
			name = val;
			float fval = atof(val);
			type = CONST;
			var_type = vt_float_ptr;
			size = sizeof(float);
			float_ptr = new float(fval);
			
		}
		const_t(int i,const char* val)
		{
			name = val;
			int ival = atoi(val);
			type = CONST;
			var_type = vt_int_ptr;
			size = sizeof(int);
			int_ptr = new int(ival);
			
		}

		const_t(const char* pstr)
		{
			name = pstr;
			type = CONST;
			var_type = vt_char_ptr;
			size = strlen(pstr) + 1;
			char_ptr = new char[size];
			if (char_ptr)
			{
				strcpy(char_ptr, pstr);
			}
		}

		
	};



	//结构体,枚举 联合
	template<
		class _fd1 = null_type
			, class _fd2 = null_type
			, class _fd3 = null_type
			, class _fd4 = null_type
			, class _fd5 = null_type
			, class _fd6 = null_type
			, class _fd7 = null_type
			, class _fd8 = null_type
			, class _fd9 = null_type
			, class _fd10 = null_type
			, class _fd11 = null_type
	>
	struct struct_t :public item
	{
		const int type = STRUCT;

		_fd1 fd1;
		_fd2 fd2;
		_fd3 fd3;
		_fd4 fd4;
		_fd5 fd5;
		_fd6 fd6;
		_fd7 fd7;
		_fd8 fd8;
		_fd9 fd9;
		_fd10 fd10;
		_fd11 fd11;

		virtual int get_type()
		{
			return type;
		}

	};

	//枚举
	template<
		class _fd1 = null_type
			, class _fd2 = null_type
			, class _fd3 = null_type
			, class _fd4 = null_type
			, class _fd5 = null_type
			, class _fd6 = null_type
			, class _fd7 = null_type
			, class _fd8 = null_type
			, class _fd9 = null_type
			, class _fd10 = null_type
			, class _fd11 = null_type
	>
	struct enum_t :public item
	{
		const int type = ENUM;

		_fd1 fd1;
		_fd2 fd2;
		_fd3 fd3;
		_fd4 fd4;
		_fd5 fd5;
		_fd6 fd6;
		_fd7 fd7;
		_fd8 fd8;
		_fd9 fd9;
		_fd10 fd10;
		_fd11 fd11;

		virtual int get_type()
		{
			return type;
		}

	};

	//联合
	template<
		class _fd1 = null_type
			, class _fd2 = null_type
			, class _fd3 = null_type
			, class _fd4 = null_type
			, class _fd5 = null_type
			, class _fd6 = null_type
			, class _fd7 = null_type
			, class _fd8 = null_type
			, class _fd9 = null_type
			, class _fd10 = null_type
			, class _fd11 = null_type
	>
	struct union_t :public item
	{
		const int type = UNION;

		_fd1 fd1;
		_fd2 fd2;
		_fd3 fd3;
		_fd4 fd4;
		_fd5 fd5;
		_fd6 fd6;
		_fd7 fd7;
		_fd8 fd8;
		_fd9 fd9;
		_fd10 fd10;
		_fd11 fd11;

		virtual int get_type()
		{
			return type;
		}

	};


	//定义全局操作符函数对象，为每种变量定义操作符。供语义动作时调用。
	


	

	
	/*
	enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;
	*/
	//struct item_enumerator_list;
	//struct item_enum_specifier :public  i_node
	//{
	//	std::string type = "item_enum_specifier";
	//	int gen_index = 0;
	//	int op = 0;
	//	int num_child = 2;
	//	std::string right;
	//	item_enumerator_list* right1 = NULL;
	//	item_identifier* right2 = NULL;
	//};

	/*struct item_enum:public item
	{
		int type ;
		std::string name;
		std::map<std::string, int>  list;

		virtual int get_type()
		{
			return type;
		}
	};*/

	//primary_expression
	//	: IDENTIFIER
	//	| CONSTANT
	//  | F_CONSTANT
	//  | I_CONSTANT
	//	| STRING_LITERAL
	//	| '(' expression ')'
	//	;

	

}
#endif