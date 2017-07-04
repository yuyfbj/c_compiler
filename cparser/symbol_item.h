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
		ret_item* operator[](ret_item& v1)
		{

			return NULL;
		}

		ret_item* operator()(ret_item& v1)
		{

			return NULL;
		}

		ret_item* operator()()
		{

			return NULL;
		}
		ret_item* dot_op(ret_item& v1)
		{


			return NULL;
		}
		ret_item* ptr_op(ret_item& v1)
		{
			return NULL;
		}

		ret_item* sizeof_op()
		{

			return NULL;
		}

		ret_item* bit_and_op(ret_item& v1)
		{

			return NULL;
		}
		ret_item* bit_inv_op()
		{


			return NULL;
		}

		ret_item* bit_or_op(ret_item& v1)
		{


			return NULL;
		}
		ret_item* convert_type(ret_item& v1)
		{

			return NULL;
		}
		ret_item* logical_not()
		{

			return NULL;
		}

		ret_item* logic_or(ret_item& v1)
		{
			return NULL;
		}
		ret_item* logic_and(ret_item& v1)
		{
			return NULL;
		}
		ret_item* rel_eq_op(ret_item& v1)
		{
			return NULL;
		}
		ret_item* rel_ne_op(ret_item& v1)
		{

			return NULL;
		}
		ret_item* rel_low_op(ret_item& v1)
		{

			return NULL;
		}
		ret_item* rel_great_op(ret_item& v1)
		{

			return NULL;
		}

		ret_item* rel_le_op(ret_item& v1)
		{

			return NULL;
		}
		ret_item* rel_ge_op(ret_item& v1)
		{

			return NULL;
		}

		ret_item* shift_left_op(ret_item& v1)
		{

			return NULL;
		}
		ret_item* shift_right_op(ret_item& v1)
		{

			return NULL;
		}
		ret_item* add_op(ret_item& v1)
		{
			return NULL;
		}
		ret_item* sub_op(ret_item& v1)
		{
			return NULL;
		}

		ret_item* mul_op(ret_item& v1)
		{

			return NULL;
		}

		ret_item* div_op(ret_item& v1)
		{

			return NULL;
		}

		ret_item* mod_op(ret_item& v1)
		{

			return NULL;
		}



		ret_item* star_op()
		{

			return NULL;
		}
		ret_item* add_sign_op()
		{

			return NULL;
		}
		ret_item* sub_sign_op()
		{

			return NULL;
		}

		ret_item* xor_op(ret_item& v1)
		{
			return NULL;
		}
		

		ret_item& post_inc()
		{

			return *this;
		}
		ret_item& post_dec()
		{

			return *this;
		}

		ret_item& pre_inc()
		{

			return *this;
		}
		ret_item& pre_dec()
		{
			return *this;
		}
		
		ret_item& operator *=(const ret_item& v1)
		{


			return *this;
		}
		ret_item& operator +=(const ret_item& v1)
		{


			return *this;
		}
		ret_item& operator -=(const ret_item& v1)
		{


			return *this;
		}
		ret_item& operator /=(const ret_item& v1)
		{


			return *this;
		}
		ret_item& operator %=(const ret_item& v1)
		{


			return *this;
		}
		ret_item& operator <<=(const ret_item& v1)
		{


			return *this;
		}
		ret_item& operator >>=(const ret_item& v1)
		{


			return *this;
		}

		ret_item& operator &=(const ret_item& v1)
		{


			return *this;
		}
		ret_item& operator |=(const ret_item& v1)
		{


			return *this;
		}
		ret_item& operator ^=(const ret_item& v1)
		{


			return *this;
		}






		ret_item& operator = (const ret_item& v1)
		{
			this->op = v1.op;
			this->type = v1.type;
			this->item = v1.item;
			return *this;
		}
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
			,vt_char
			,vt_short
			,vt_int
			,vt_long
			,vt_float
			,vt_double
			,vt_struct
			,vt_enum
			,vt_array
		};
		enum rt
		{
			rt_address = 100
			,rt_value
		};
		int ref_type = 0;
		int var_type = 0;
		int size = 0;
		int array_item_size = 0;
		int array_item_type = 0;
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
			void*   array_ptr;
		};
		//各种运算符操作

	



	};

	//常量

	struct const_t :public var_t
	{
		const_t(float fval,const char* val)
		{
			name = val;

			type = CONST;
			var_type = vt_float;
			size = sizeof(float);
			float_ptr = new float(fval);
			
		}
		const_t(int ival,const char* val)
		{
			name = val;
		
			type = CONST;
			var_type = vt_int;
			size = sizeof(int);
			int_ptr = new int(ival);
			
		}

		const_t(const char* pstr)
		{
			name = pstr;
			type = CONST;
			var_type = vt_char;
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