

#version 330



uniform vec4 pickColour;

out vec4 fragCol;



void main()
{
	fragCol = pickColour;
}
