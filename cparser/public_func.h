#ifndef PUBLIC_FUNC_H
#define PUBLIC_FUNC_H

namespace pub_func
{
	template<class T>
	T* NewItem()
	{
		auto item = new T;
		if (NULL == item)
			return NULL;

		return item;
	}

	template <class T>
	T* ReleaseItem(T* p)
	{
		//error_report();
		delete p;
		return NULL;
	}


	template<class T>
	T* new_item_z()
	{
		auto item = new T;
		if (NULL == item)
			return NULL;
		memset(item, 0, sizeof(T));

		return item;
	}

	template<class T>
	T* new_item(int type)
	{
		auto item = new T;
		if (NULL == item)
			return NULL;
		

		return item;
	}

	template <class T>
	T* release_item(T* p)
	{
		//error_report();
		delete p;
		return NULL;
	}

}



#endif