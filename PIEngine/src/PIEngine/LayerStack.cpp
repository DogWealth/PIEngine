#include "pipch.h"
#include "LayerStack.h"

namespace PIEngine {
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		//ע������û��delete��layer��layerӦ����application������layerջ���Ƴ�ȥҲ��Ӧ��ֱ�����ٵ�
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlayer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlayer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}

}