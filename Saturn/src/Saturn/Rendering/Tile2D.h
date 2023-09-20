#pragma once
#include <glm/glm.hpp>
#include "Saturn/Rendering/SubTexture2D.h"

namespace Saturn
{
    class Tile2D
    {
    public:
        glm::vec3 Offset = glm::vec3(0.0f);
        glm::vec3 Scale = glm::vec3(1.0f);
        glm::vec4 Color = glm::vec4(1.0f);

        Tile2D(const Ref<SubTexture2D>& subTexture);

        inline Ref<SubTexture2D> GetSubTexture() const
        {
            return m_SubTexture;
        }
    private:
        Ref<SubTexture2D> m_SubTexture;
    };
}