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

}



#endif