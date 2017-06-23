#ifndef LEX_H
#define LEX_H

#include <string>






namespace lex
{



	bool  init_lex(std::string& strfilename);
	bool  error_report();
	int pre_get_token_val(std::string& strVal);
	int pre_get_token();
	void  pop_token();

}
#endif