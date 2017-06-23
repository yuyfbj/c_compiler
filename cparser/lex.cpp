
#include "lex.h"

#include <regex>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <future>
#include <array>  
#include <tuple>


#include <stack>
#include <vector>
#include <sstream>
#include <iostream>
#include <queue>  
#include <fstream>

namespace lex
{
	struct CLex
	{
		std::queue < std::tuple<int, std::string> > queue_token;


		std::function<bool(const std::string&)> readfile =
			[this](const std::string& strfilename)->bool
		{
			std::string strContext;
			std::ifstream ii(strfilename);
			while (true)
			{
				char ch;
				ii.get(ch);
				strContext += ch;
				if (ii.eof())
					break;
			}

			std::istringstream is(strContext);
			while (true)
			{
				std::string strtype;
				std::getline(is, strtype, '\n');
				std::string str;
				std::getline(is, str, '\n');

				if (strtype.size() && str.size())
				{
					std::istringstream it(strtype);
					int type = 0;
					it >> type;
					//≤Â»Î∂”¡–°£
					queue_token.push(std::make_tuple(type, str));
					//std::cout << strtype << "," << str << std::endl;
				}

				if (is.eof())
					break;
			}

			return true;
		};
		std::function<std::tuple<int, std::string>()> get_token = [this]()->std::tuple<int, std::string>
		{
			if (queue_token.size() == 0)
				return std::make_tuple(0, "");
			auto tup = queue_token.front();
			queue_token.pop();

			return tup;
		};



		std::function<void()> pop_token = [this]()
		{
			queue_token.pop();
			return;
		};

		std::function<std::tuple<int, std::string>()> pre_get_token_ex = [this]()->std::tuple<int, std::string>
		{
			if (queue_token.size() == 0)
				return std::make_tuple(0, "");
			auto tup = queue_token.front();

			return tup;
		};

		std::function<int()> pre_get_token = [this]()->int
		{
			int token;
			std::string strContext;
			std::tie(token, strContext) = pre_get_token_ex();
			std::cout << token << ":" << strContext << std::endl;

			if (!token)
			{
				int a;

			}



			return token;
		};

		std::function<int(std::string&)> pre_get_token_val = [this](std::string& strVal)->int
		{
			int token;
			std::string strContext;
			std::tie(token, strContext) = pre_get_token_ex();
			strVal = strContext;
			std::cout << token << ":" << strContext << std::endl;

			if (!token)
			{
				int a;

			}



			return token;
		};

	};

	CLex g_Lex;

	std::string strfilename = "c:\\1.o";

	bool  init_lex()
	{
		bool bRet = g_Lex.readfile(strfilename);
		/*	while (true)
		{
		int token;
		std::string strContext;
		std::tie(token, strContext) = m_Lex.get_token();
		if (0 == token)
		break;

		std::cout << token << ":" << strContext << std::endl;
		}*/



		return true;
	};


	bool  error_report()
	{
		std::cout << "Error:" << std::endl;
		//DebugBreak();
		return true;
	};

	int pre_get_token_val(std::string& strVal)
	{

		int token = g_Lex.pre_get_token_val(strVal);
		if (token == 12345678)
		{//eof is reached
			return 0;
		}

		return token;
	};
	int pre_get_token ()
	{
		int token = g_Lex.pre_get_token();
		if (token == 12345678)
		{//eof is reached
			return 0;
		}

		return token;
	};
	void  pop_token ()
	{
		g_Lex.pop_token();
		return;
	};

 }




