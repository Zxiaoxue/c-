#include <iostream>
using namespace std;
//单例模式



//懒汉模式
class Csingleton
{
public:
	static Csingleton* GetIntrance()
	{
		if(NULL == _Instrance)
			_Instrance = new Csingleton();
		return _Instrance;
	}

private:
	Csingleton(){};
	static Csingleton* _Instrance;
};

//
class Csingleton1
{
public:
	Csingleton1* GetIinstrance()
	{
		if(NULL == _Instrance)
			_Instrance = new Csingleton1();
		
		return _Instrance;
	}

private:
	Csingleton1() {};
	static Csingleton1* _Instrance;
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if(Csingleton1::_Instrance)
				delete Csingleton1::_Instrance;
		}
	};
	static CGarbo _CGarbo;
};

//线程安全
pthread_mutex_t mutex PTHREAD_MUTEX_INITALIZER;
class Csingleton2
{
public:
	static Csingleton2* GetInstrance()
	{
		pthread_mutex_lock(&mutex);
		if(NULL == _Instrance)
			_Instrance = new Csingleton2();
		pthread_mutex_unlock(&mutex);

		return _Instrance;
	}
private:
	Csingleton2() {};
	static Csingleton2* _Instrance;
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if(Csingleton2::_Instrance)
				delete Csingleton2::_Instrance;
		}
	};
	static CGarbo _CGarbo;
};

//更优的解法

PTHREAD_MUTEX_T mutex = PTHREAD_MUTEX_INITALIZER;

class Csingleton3
{
public:
	static Csingleton3* GetInstrance()
	{
		if(NULL == _Instrance)
		{
			pthread_mutex_lock(&lock);
			if(NULL == _Instrance)
				_Instrance = new Csingleton3();
			pthread_mutex_unlock(&lock);
		}

		return _Instrance;
	}

private:
	Csingleton3() {};
	static Csingleton3* _Instrance;
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if(Csingleton3::_Instrance)
			{
				delete Csingleton3::_Instrance;
			}
		}
	};
	static CGarbo* _CGarbo;
};

//饿汉模式
class Csingleton4
{
	static Csingleton4* GetInstrance()
	{
		static Csingleton4 _Instrance;
		return &_Instrance;
	}

private:
	Csingleton4() {}

};

































