// testC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <fstream>



#include "lex.yy.c"

int yywrap(void)        /* called at end of input */
{
	return 1;           /* terminate now */
}

int _tmain(int argc, _TCHAR* argv[])
{	
	std::ofstream of("1.o");
	while (true)
	{
		int nRet = yuyf_main();
		if (nRet == 0)
			break;
		std::cout << nRet <<":"<<yytext<< std::endl;

		if (nRet == 258 && std::string(yytext) == "eof")
		{
			nRet = 12345678;
			of << nRet << std::endl << yytext << std::endl;
			of.flush();

			break;
		}

		of << nRet <<std::endl << yytext << std::endl;
		of.flush();

		
	}
	of.close();
	
	return 0;
}

