#pragma once

#include "PIEngine/Core.h"

namespace PIEngine {
	enum class EventType //https://zhuanlan.zhihu.com/p/630946141
	{
		None = 0,
		WindowClose, WindowResize, WIndowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication		= BIT(0),
		EventCategoryInput				= BIT(1),
		EventCategoryKeyboard			= BIT(2),
		EventCategoryMouse				= BIT(3),
		EventCategoryMouseButton		= BIT(4),
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type;}\
								virtual EventType GetEventType() const override {return GetStaticType();}\
								virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlag() const override {return category;}

	class PI_API Event {
		friend class EventDispatcher; //friend https://blog.csdn.net/lwbeyond/article/details/7591415
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlag() const = 0;
		virtual std::string ToString() const { return GetName(); }

		//内联函数会将代码块嵌入到每个调用该函数的地方。内联函数减少了函数的调用，使代码执行的效力提高，但是会增加目标代码的大小，最终会使程序的代码段占有大量的内存。
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlag() & category;
		}

	//private是完全私有的，只有自己可以访问，派生类和外部都不可以访问
	//protected是受保护的，只有派生类可以访问，外部不能访问
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}