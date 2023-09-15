#shader vertex
(layout = 0) vec3 VertexPosition;

int main() 
{
    glPosition * vec4(VertexPosition, 1.0f);
}
#shader endvertex

#shader fragment
out vec4 o_Color;

int main() 
{
    o_Color = vec4(1, 0, 0, 1);
}
#shader endfragment