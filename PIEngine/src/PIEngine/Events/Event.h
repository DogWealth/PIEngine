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

		//���������Ὣ�����Ƕ�뵽ÿ�����øú����ĵط����������������˺����ĵ��ã�ʹ����ִ�е�Ч����ߣ����ǻ�����Ŀ�����Ĵ�С�����ջ�ʹ����Ĵ����ռ�д������ڴ档
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlag() & category;
		}

	//private����ȫ˽�еģ�ֻ���Լ����Է��ʣ���������ⲿ�������Է���
	//protected���ܱ����ģ�ֻ����������Է��ʣ��ⲿ���ܷ���
	protected:
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