#pragma once
#include "Saturn/Common/Types.h"
#include "Saturn/Core/Core.h"

namespace Saturn
{
	struct FramebufferSpecification
	{
		UInt32 Width, Height;
		UInt32 Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;
		virtual const FramebufferSpecification& GetSpecs() const = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual UInt32 GetColorAttachmentID() const = 0;
		virtual void Resize(UInt32 width, UInt32 height) = 0;
		
		static Ref<Framebuffer> Create(const FramebufferSpecification& specs);
	};
}