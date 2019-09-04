#include "hzpch.h"
#include "RenderCommandQueue.h"

#define HZ_CMD_BUFFER_DATA_DIM 10 * 1024 * 1024
#define TRACE(x) std::cout << x << std::endl;
#define TRACE2(x, y) std::cout << x << ", " << y << std::endl;

namespace Hazel {

	RenderCommandQueue::RenderCommandQueue()
	{
		TRACE("RenderCommandQueue");
		m_CommandBuffer = new unsigned char[HZ_CMD_BUFFER_DATA_DIM]; // 10mb buffer
		m_CommandBufferPtr = m_CommandBuffer;
		memset(m_CommandBuffer, 0, HZ_CMD_BUFFER_DATA_DIM);
	}

	RenderCommandQueue::~RenderCommandQueue()
	{
		delete[] m_CommandBuffer;
	}

	void * RenderCommandQueue::Allocate(RenderCommandFn fn, unsigned int size)
	{
		*(RenderCommandFn*)m_CommandBufferPtr = fn;
		m_CommandBufferPtr += sizeof(RenderCommandFn);

		*(int*)m_CommandBufferPtr = size;
		m_CommandBufferPtr += sizeof(unsigned int);

		void* memory = m_CommandBufferPtr;
		m_CommandBufferPtr += size;

		m_CommandCount++;
		return memory;
	}

	void RenderCommandQueue::Execute()
	{
		TRACE("RenderCommandQueue::Execute -- {0} commands, {1} bytes");
		TRACE2(m_CommandCount, (m_CommandBufferPtr - m_CommandBuffer));

		byte* buffer = m_CommandBuffer;

		for (unsigned int i = 0; i < m_CommandCount; i++)
		{
			RenderCommandFn function = *(RenderCommandFn*)buffer;
			buffer += sizeof(RenderCommandFn);

			unsigned int size = *(unsigned int*)buffer;
			buffer += sizeof(unsigned int);
			function(buffer);
			buffer += size;
		}

		m_CommandBufferPtr = m_CommandBuffer;
		m_CommandCount = 0;
	}
}
