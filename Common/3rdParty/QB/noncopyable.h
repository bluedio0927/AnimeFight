#ifndef  _QB_NONCOPYABLE_H
#define  _QB_NONCOPYABLE_H

namespace QB
{
	class noncopyable
	{
	protected:
		noncopyable() {}
		~noncopyable() {}
	private: 
		noncopyable(const noncopyable&);
		const noncopyable& operator=(const noncopyable&) = delete;
	};
}
#endif // ! _QB_NONCOPYABLE_H
