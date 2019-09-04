#pragma once

namespace Hazel {

	class RenderCommandQueue
	{
	public:

		typedef void(*RenderCommandFn)(void*);

		RenderCommandQueue();
		~RenderCommandQueue();

		void* Allocate(RenderCommandFn fn, unsigned int size);

		void Execute();
	private:
		unsigned char* m_CommandBuffer;
		unsigned char* m_CommandBufferPtr;
		unsigned int m_CommandCount;
	};

}
