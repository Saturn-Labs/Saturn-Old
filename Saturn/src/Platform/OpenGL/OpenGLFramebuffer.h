#pragma once
#include "Saturn/Rendering/Framebuffer.h"

namespace Saturn
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& specs);
		virtual ~OpenGLFramebuffer();

		void Invalidate();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void Resize(UInt32 width, UInt32 height) override;

		virtual const FramebufferSpecification& GetSpecs() const override
		{
			return m_Specs;
		}

		virtual UInt32 GetColorAttachmentID() const override
		{
			return m_ColorAttachment;
		}
	private:
		UInt32 m_Id = 0;
		UInt32 m_ColorAttachment = 0;
		UInt32 m_DepthAttachment = 0;
		FramebufferSpecification m_Specs;
	};
}