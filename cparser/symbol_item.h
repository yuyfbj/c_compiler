#ifndef  SYMBOL_ITEM_H
#define SYMBOL_ITEM_H
#include <map>
#include <string>
#include "token_def.h"
namespace symbol
{
	/*
	����ļ������⣬��Ҫ�������
	1.���嶯����ֵ�Ĵ��ݣ�
	���糡�����������ֽڵ㣬��ʵֻ�Ǵ��ݡ�
	2.��������ࣺ
	����ÿ�����ݽṹ�������������ȡ�
	3.��Ը����������ͣ����ܷ��ص�ֵ�����ǲ�ͬ�ģ���Ҫͳһ��
	���磺ÿ�����͵ı������ǣ�
	template<class t>
	struct var_t
	{
		using type = t;
		std::string name;
		std::string val;
	};

	
	��Ҫ����һϵ�����ݽṹ�������ͨ�õ����ݽṹ����������д�������ܼ�Щ��
	
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


	//������
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
	//�ⲿ����
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
	//���
	struct label_t :public item
	{
		const int type = LABEL;
		std::string name;
		std::string val;
		virtual int get_type()
		{
			return type;
		}
	};
	//����
	template<int ntype>
	struct const_t:public item
	{
		const int type = ntype;
		std::string name;
		std::string val;
		virtual int get_type()
		{
			return type;
		}
	};

	//����
	template<class T>
	struct var_t:public item
	{
		const int type = IDENTIFIER;
		using var_type = T;
		std::string name;
		std::string val;
		virtual int get_type()
		{
			return type;
		}
	};


	//�ṹ��,ö�� ����
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

	//ö��
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

	//����
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


	//����ȫ�ֲ�������������Ϊÿ�ֱ�������������������嶯��ʱ���á�
	


	

	
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