// testC.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <iostream>


#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <future>
#include <array>  
#include <tuple>

#include <fstream>
#include <sstream>

#include <stdio.h>   


#include <time.h>   
#include <string.h>   
#include <stdlib.h> 



#include "parser_statement.h"
#include "gen.h"
//模板编译好慢，这里暂时屏掉。
//#include "rule.h"

stmt::item_translation_unit* g_root = NULL;

bool main_parse()
{
	auto item = stmt::translation_unit();
	g_root = item;

	return true;
};

bool gen_json(std::string& json_out)
{
	Json::Value json;
	g_root->gen_json(json);
	
	
	Json::FastWriter jsFastWriter;
	json_out = jsFastWriter.write(json);
	

	std::ofstream of("tree.json");
	if (of.is_open())
	{
		of << json_out;
		of.flush();
		of.close();
	}
	return true;
}



int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "hello" << std::endl;

	std::string file_name_in;
	
	if (argc >= 2)
	{
		file_name_in = argv[1];
	}

	lex::init_lex(file_name_in);
	
	main_parse();

	std::string json_out;
	gen_json(json_out);

	int a;
	std::cin >> a;

	return 0;
}

