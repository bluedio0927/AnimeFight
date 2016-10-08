#ifndef _QB_ANY_H
#define _QB_ANY_H

#include <typeinfo>
#include <type_traits>
#include <utility>

#include "named.h"

namespace QB
{
	class any
	{
		template<class T>
		using RealType = typename std::decay<T>::type;

	public:
		any() : content(nullptr)
		{}

		template<typename U>
		any(U&& value) : content(new Derived<RealType<U>>(std::forward<U>(value)))
		{}

		any(const any& that): content(that.clone())
		{}

		any(any&& that)	: content(that.content)
		{
			that.content = nullptr;
		}

		~any()
		{
			clear();
		}

		// boost queries...
		const std::type_info& type() const
		{
			return content ? content->type() : typeid(void);
		}

		bool empty() const 
		{ 
			return content == nullptr;
		}

		void clear()
		{
			delete content;
		}

		any& swap(any& rhs)
		{
			std::swap(content, rhs.content);
			return *this;
		}

		any& operator=(const any& rhs)
		{
			any(rhs).swap(*this);
			return *this;
		}


		any& operator=(any&& rhs)
		{
			rhs.swap(*this);
			any().swap(rhs);
			return *this;
		}

		// Extend...
		template<class U>
		RealType<U>& any_cast() const
		{
			typedef RealType<U> T;

			QB_RVALNAMED derived = dynamic_cast<Derived<T>*> (content);

			if (!derived)
				throw std::bad_cast();

			return derived->value;
		}

		template<class U> 
		bool is() const
		{
			typedef RealType<U> T;
			return nullptr != dynamic_cast<Derived<T>*> (content);
		}

		template<class U>
		operator U&()
		{
			return any_cast<RealType<U>>();
		}

	private:
		struct Base
		{
			virtual ~Base() {}
			virtual Base* clone() const = 0;
			virtual const std::type_info& type() const = 0;
		};

		template<typename T>
		struct Derived : Base
		{
			template<typename U>
			Derived(U&& value) : value(std::forward<U>(value)) 	
			{}

			Base* clone() const
			{ 
				return new Derived<T>(value); 
			}

			const std::type_info& type() const
			{
				return typeid(T);
			}

			T value;
		};

		Base* clone() const
		{
			if (content)
				return content->clone();
			else
				return nullptr;
		}

		Base* content;
	};

	template<typename ValueType>
	ValueType& any_cast(const any &operand)
	{
		return operand.any_cast<ValueType>();
	}
};

#endif