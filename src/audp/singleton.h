#ifndef AUDP_SINGLETON_H
#define AUDP_SINGLETON_H

template <class T>
class Singleton
{
public:
	static T* getInstance() {
		static T t;
		return &t;
	}
};

#endif
