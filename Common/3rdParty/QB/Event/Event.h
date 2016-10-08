#ifndef _QB_EVENT_H
#define _QB_EVENT_H

#include <map>
#include <algorithm>
#include <memory>
#include <type_traits>
#include "../noncopyable.h"
#include "../any.h"

namespace QB
{
	template <typename Handler>
	class Event : public noncopyable
	{
	public:
		class Listener;
		using result_type = typename Handler::result_type;

		//Event <-> Listener
		class Connection : public noncopyable
		{
		public:
			Connection(Event* In_pEvent, Listener* In_pListener)
				:pEvent(In_pEvent), pListener(In_pListener)
			{}

			Event* pEvent;
			Listener* pListener;
		};

		using Connectionptr = std::shared_ptr<Connection>;
		using ConnectionMap = std::map<size_t, Connectionptr>;

		//Use The Handler to Handle Event 
		class Listener : public noncopyable
		{
		public:
			Listener(const Handler &In_Func)
				:Func(In_Func)
			{}

			virtual ~Listener()
			{
				for (auto &iter : m_mapConnection)
					iter.second->pEvent->cancel(iter.second);
			}

			operator const Handler&()
			{
				return Func;
			}

		private:
			friend class Connection;
			friend class Event;

			void listen(Connectionptr& In_Connection)
			{
				m_mapConnection[(size_t)(In_Connection->pEvent)] = In_Connection;
			}

			void close(Connectionptr& In_Connection)
			{
				m_mapConnection.erase((size_t)(In_Connection->pEvent));
			}

			Handler Func;
			ConnectionMap m_mapConnection;
		};

	public:
		Event() {}
		virtual ~Event() 
		{
			for (auto &iter : m_mapConnection)
				iter.second->pListener->close(iter.second);
		}

		bool connect(int In_priority, Listener& In_Listener)
		{
			return connect(any(In_priority), In_Listener);
		}

		bool operator += (Listener& In_Listener)
		{
			return connect(any(), In_Listener);
		}

		bool operator -= (Listener& In_Listener)
		{
			const auto& iter = m_mapConnection.find((size_t)&In_Listener);
			if (iter != m_mapConnection.end())
			{
				In_Listener.close(iter->second);
				cancel(iter->second);
				return true;
			}
			else
				return false;
		}

		template<typename T = result_type, typename ...Args>
		typename std::enable_if<!std::is_void<T>::value, T>::type Invoke(Args&& ...args)
		{
			T val;
			for (auto &iter : m_multimapDoInvoke)
				val = ((const Handler&)(*(iter.second->pListener)))(std::forward<Args>(args)...);
			return val;
		}
		
		template<typename T = result_type, typename ...Args>
		typename std::enable_if<std::is_void<T>::value, void>::type Invoke(Args&& ...args)
		{
			for (auto &iter : m_multimapDoInvoke)
				((const Handler&)(*(iter.second->pListener)))(std::forward<Args>(args)...);
		}

		/*

		template<typename ...Args>
		typename std::enable_if<!std::is_void<result_type>::value, T>::type Invoke(Args&& ...args)
		{
			T val;
			for (auto &iter : m_multimapDoInvoke)
				val = ((Handler&)(*(iter.second->pListener)))(std::forward<Args>(args)...);
			return val;
		}

		template<typename ...Args>
		typename std::enable_if<std::is_void<result_type>::value, void>::type Invoke(Args&& ...args)
		{
			for (auto &iter : m_multimapDoInvoke)
				((Handler&)(*(iter.second->pListener)))(std::forward<Args>(args)...);
		}

		*/
	private:
		friend class Connection;

		void cancel(Connectionptr& In_Connection)
		{
			auto iter = m_multimapDoInvoke.begin();
			while (iter != m_multimapDoInvoke.end())
			{
				if (iter->second->pListener == In_Connection->pListener)
				{
					m_multimapDoInvoke.erase(iter);
					m_mapConnection.erase((size_t)(In_Connection->pListener));
					break;
				}
				else
					++iter;
			}
		}

		bool connect(const any& any , Listener& In_Listener)
		{
			const auto& iter = m_mapConnection.find((size_t)&In_Listener);
			if (iter == m_mapConnection.end())
			{
				auto pConnection = std::make_shared<Connection>(this, &In_Listener);
				m_mapConnection[(size_t)&In_Listener] = pConnection;
				In_Listener.listen(pConnection);
				m_multimapDoInvoke.emplace(any, pConnection);
				return true;
			}
			else
				return false;
		}

		class any_compare 
		{
		public:
			bool operator()(const any& k1, const any& k2) 
			{
				if (k1.empty())
					return false;
				if (k2.empty())
					return true;
				if (k1.is<int>() && k2.is<int>())
					return k1.any_cast<int>() > k2.any_cast<int>();
				else
					return false;
			}
		};

		ConnectionMap m_mapConnection;
		std::multimap<any, Connectionptr, any_compare> m_multimapDoInvoke;
	};
}
#endif
