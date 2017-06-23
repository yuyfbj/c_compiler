#ifndef GEN_JSON_H
#define GEN_JSON_H

#include "json/json.h"


namespace gen
{
		
		template <class TP>
		void gen_json(Json::Value& json, TP* item)
		{
			json["type"] = item->type;
			json["op"] = item->op;
			json["right"] = item->right;
		}

		template <class TP, class TR1>
		void gen_json(Json::Value& json, TP* item)
		{
			json["type"] = item->type;
			json["op"] = item->op;
			json["right"] = item->right;

			if (item->right1)
			{
				Json::Value json_temp;
				((TR1*)(item->right1))->gen_json(json_temp);
				json["right1"] = json_temp;
			}
		}

		template <class TP
			, class TR1
			, class TR2
		>
		void gen_json(Json::Value& json,TP* item)
		{
			json["type"] = item->type;
			json["op"] = item->op;
			json["right"] = item->right;

			if (item->right1)
			{
				Json::Value json_temp;
				((TR1*)item->right1)->gen_json(json_temp);
				json["right1"] = json_temp;
			}
			if (item->right2)
			{
				Json::Value json_temp;
				((TR2*)item->right2)->gen_json(json_temp);
				json["right2"] = json_temp;
			}
		}

		template <class TP
			, class TR1
			, class TR2
			, class TR3>
		void gen_json(Json::Value& json,TP* item)
		{
			json["type"] = item->type;
			json["op"] = item->op;
			json["right"] = item->right;

			if (item->right1)
			{
				Json::Value json_temp;
				((TR1*)item->right1)->gen_json(json_temp);
				json["right1"] = json_temp;
			}
			if (item->right2)
			{
				Json::Value json_temp;
				((TR2*)item->right2)->gen_json(json_temp);
				json["right2"] = json_temp;
			}
			if (item->right3)
			{
				Json::Value json_temp;
				((TR3*)item->right3)->gen_json(json_temp);
				json["right3"] = json_temp;
			}
		}
		

		template <class TP
			, class TR1
			, class TR2
			, class TR3
			, class TR4
		>
		void gen_json(Json::Value& json,TP* item)
		{
			json["type"] = item->type;
			json["op"] = item->op;
			json["right"] = item->right;

			if (item->right1)
			{
				Json::Value json_temp;
				((TR1*)item->right1)->gen_json(json_temp);
				json["right1"] = json_temp;
			}
			if (item->right2)
			{
				Json::Value json_temp;
				((TR2*)item->right2)->gen_json(json_temp);
				json["right2"] = json_temp;
			}
			if (item->right3)
			{
				Json::Value json_temp;
				((TR3*)item->right3)->gen_json(json_temp);
				json["right3"] = json_temp;
			}
			if (item->right4)
			{
				Json::Value json_temp;
				((TR4*)item->right4)->gen_json(json_temp);
				json["right4"] = json_temp;
			}
		}

		template <class TP
			, class TR1
			, class TR2
			, class TR3
			, class TR4
			, class TR5
		>
		void gen_json(Json::Value& json,TP* item)
		{
			json["type"] = item->type;
			json["op"] = item->op;
			json["right"] = item->right;

			if (item->right1)
			{
				Json::Value json_temp;
				((TR1*)item->right1)->gen_json(json_temp);
				json["right1"] = json_temp;
			}
			if (item->right2)
			{
				Json::Value json_temp;
				((TR2*)item->right2)->gen_json(json_temp);
				json["right2"] = json_temp;
			}
			if (item->right3)
			{
				Json::Value json_temp;
				((TR3*)item->right3)->gen_json(json_temp);
				json["right3"] = json_temp;
			}
			if (item->right4)
			{
				Json::Value json_temp;
				((TR4*)item->right4)->gen_json(json_temp);
				json["right4"] = json_temp;
			}
			if (item->right5)
			{
				Json::Value json_temp;
				((TR5*)item->right5)->gen_json(json_temp);
				json["right5"] = json_temp;
			}
		}
	
		template <class TP
			, class TR1
			, class TR2
			, class TR3
			, class TR4
			, class TR5
			, class TR6
		>
		void gen_json(Json::Value& json,TP* item)
		{
			json["type"] = item->type;
			json["op"] = item->op;
			json["right"] = item->right;

			if (item->right1)
			{
				Json::Value json_temp;
				((TR1*)item->right1)->gen_json(json_temp);
				json["right1"] = json_temp;
			}
			if (item->right2)
			{
				Json::Value json_temp;
				((TR2*)item->right2)->gen_json(json_temp);
				json["right2"] = json_temp;
			}
			if (item->right3)
			{
				Json::Value json_temp;
				((TR3*)item->right3)->gen_json(json_temp);
				json["right3"] = json_temp;
			}
			if (item->right4)
			{
				Json::Value json_temp;
				((TR4*)item->right4)->gen_json(json_temp);
				json["right4"] = json_temp;
			}
			if (item->right5)
			{
				Json::Value json_temp;
				((TR5*)item->right5)->gen_json(json_temp);
				json["right5"] = json_temp;
			}
			if (item->right6)
			{
				Json::Value json_temp;
				((TR6*)item->right6)->gen_json(json_temp);
				json["right6"] = json_temp;
			}
		}

		template <class TP
			, class TR1
			, class TR2
			, class TR3
			, class TR4
			, class TR5
			, class TR6
			, class TR7
		>
			void gen_json(Json::Value& json,TP* item)
			{
				json["type"] = item->type;
				json["op"] = item->op;
				json["right"] = item->right;

				if (item->right1)
				{
					Json::Value json_temp;
					((TR1*)item->right1)->gen_json(json_temp);
					json["right1"] = json_temp;
				}
				if (item->right2)
				{
					Json::Value json_temp;
					((TR2*)item->right2)->gen_json(json_temp);
					json["right2"] = json_temp;
				}
				if (item->right3)
				{
					Json::Value json_temp;
					((TR3*)item->right3)->gen_json(json_temp);
					json["right3"] = json_temp;
				}
				if (item->right4)
				{
					Json::Value json_temp;
					((TR4*)item->right4)->gen_json(json_temp);
					json["right4"] = json_temp;
				}
				if (item->right5)
				{
					Json::Value json_temp;
					((TR5*)item->right5)->gen_json(json_temp);
					json["right5"] = json_temp;
				}
				if (item->right6)
				{
					Json::Value json_temp;
					((TR6*)item->right6)->gen_json(json_temp);
					json["right6"] = json_temp;
				}
				if (item->right7)
				{
					Json::Value json_temp;
					((TR7*)item->right7)->gen_json(json_temp);
					json["right7"] = json_temp;
				}
			}
		
	
	

	


	

	

	

	


}



#endif