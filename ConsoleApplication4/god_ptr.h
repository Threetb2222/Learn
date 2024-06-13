#pragma once

#include <functional>

template<typename T>
class Smart_Ptr
{
public:
	Smart_Ptr();//构造函数
	explicit Smart_Ptr(T*);//初始化函数，防止发生隐式转换
	~Smart_Ptr();
	Smart_Ptr(const Smart_Ptr&);
	Smart_Ptr(T*, std::function<void(T* )>);
	Smart_Ptr& operator = (const Smart_Ptr&);
	T& operator*() const;
	T* operator->() const;
	explicit operator bool() const;
	bool unique();
	void reset();
	void reset(T*);
	void reset(T*, std::function<void(T*) > );
	T* release;
	T* get()const;
private:
	static std::function<void(T*)>user_dele_ptr;
	unsigned* user_dele_ptr_count = nullptr;
	T* user_ptr = nullptr;
	std::function<void(T*)> user_dele = user_dele_ptr;
};
//设置默认删除器
template<typename T>
std::function<void(T*)> Smart_Ptr<T>::user_dele_ptr = [](T* p) {delete p; };


//初始化函数
template <typename T, typename... Other>
Smart_Ptr<T> make_smart(Other&&... other)
{
	Smart_Ptr<T> sp(new T(std::forward<Other>other...));
	return sp;
}



//template <typename T, typename... Args>
//Smart_Ptr<T> make_smart(Args&&... args)
//{
//	Smart_Ptr<T> sp(new T(std::forward<Args>(args)...));
//	return sp;
//}



//初始化函数
template<typename T>
Smart_Ptr<T>::Smart_Ptr()
{
	user_dele_ptr_count = new unsigned(1);
	user_ptr = nullptr;
}

//初始化函数
template<typename T>
Smart_Ptr<T>::Smart_Ptr(T*p)
{
	user_dele_ptr_count = new unsigned(1);
	user_ptr = p;
}


//初始化函数
template<typename T>
Smart_Ptr<T>::Smart_Ptr(T* p,std::function<void(T*)>Other)
{
	user_dele_ptr_count = new unsigned(1);
	user_ptr = p;
	user_dele = Other;
}


//初始化函数---指针
template<typename T>
inline Smart_Ptr<T>::Smart_Ptr(const Smart_Ptr&Other)
{
	user_dele_ptr_count = Other.user_dele_ptr_count;
	user_ptr = Other.user_dele;
	user_dele = Other.user_dele;
}


template<typename T>
inline T& Smart_Ptr<T>::operator*() const
{
	return *user_ptr;
}


template <typename T>
inline T* Smart_Ptr<T>::operator->() const
{
	return &this->operator*();
}



//重载等于号
template<typename T>
inline Smart_Ptr<T>& Smart_Ptr<T>::operator=(const Smart_Ptr& Other)
{
	user_dele = Other.user_dele;
	(*Other.user_dele_ptr_count)++;
	(*user_dele_ptr_count)--;
	if ((*user_dele_ptr_count) == 0)
	{
		user_dele =user_ptr;
		delete user_ptr;
	}
	user_dele_ptr_count = Other.user_dele_ptr_count;
	user_ptr = Other.user_ptr;
	return *this;

}

//重载bool
template<typename T>
inline Smart_Ptr<T>::operator bool() const
{
	if (user_ptr == nullptr) return false;
	return true;
}

template<typename T>
inline bool Smart_Ptr<T>::unique()
{
	return *user_dele_ptr_count = 1;

}

template<typename T>
inline void Smart_Ptr<T>::reset()
{
	(*user_dele_ptr_count--);
	if ((*user_dele_ptr_count) == 0)
	{
		user_dele = user_ptr;
		delete user_ptr;
	}
	user_ptr = nullptr;
	*user_dele_ptr_count = 1;
	user_dele = user_dele_ptr;
}

template<typename T>
inline void  Smart_Ptr<T>::reset(T*Other)
{
	(*user_dele_ptr_count--);
	if ((*user_dele_ptr_count) == 0)
	{
		user_dele = user_ptr;
		delete user_ptr;
	}
	user_ptr = Other;
	*user_dele_ptr_count = 1;
	user_dele = user_dele_ptr;

}



template <typename T>
void Smart_Ptr<T>::reset(T* p, std::function<void(T*)> Other)
{
	reset(Other);
	user_dele = Other;
}

template<typename T>
inline T* Smart_Ptr<T>::get() const
{
	return user_ptr;
}



template<typename T>
inline Smart_Ptr<T>::~Smart_Ptr()
{
}

