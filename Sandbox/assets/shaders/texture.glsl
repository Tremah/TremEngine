#type vertex
#version 460 core

layout (location=0) in vec4  inPos;
layout (location=1) in vec4  inColor;
layout (location=2) in vec2  inTexCoordinates;
layout (location=3) in float inTexUnit;

uniform mat4 uMvp;

out vec2  texCoordinates;
out vec4  vColor;
out float texUnit;

void main()
{
  gl_Position  = uMvp * inPos;
  texCoordinates = inTexCoordinates;
  vColor = inColor;
  texUnit = inTexUnit;
}

#type fragment
#version 460 core

in vec2 texCoordinates;
in vec4 vColor;
in float texUnit;

uniform sampler2D uTexture;
uniform sampler2D uTextures[32];

out vec4 color;

void main()
{  
  switch(int(texUnit))
  {
    case 0:  color = texture(uTextures[0],  texCoordinates) * vColor; break;
    case 1:  color = texture(uTextures[1],  texCoordinates) * vColor; break;
    case 2:  color = texture(uTextures[2],  texCoordinates) * vColor; break;
    case 3:  color = texture(uTextures[3],  texCoordinates) * vColor; break;
    case 4:  color = texture(uTextures[4],  texCoordinates) * vColor; break;
    case 5:  color = texture(uTextures[5],  texCoordinates) * vColor; break;
    case 6:  color = texture(uTextures[6],  texCoordinates) * vColor; break;
    case 7:  color = texture(uTextures[7],  texCoordinates) * vColor; break;
    case 8:  color = texture(uTextures[8],  texCoordinates) * vColor; break;
    case 9:  color = texture(uTextures[9],  texCoordinates) * vColor; break;
    case 10: color = texture(uTextures[10], texCoordinates) * vColor; break;
    case 11: color = texture(uTextures[11], texCoordinates) * vColor; break;
    case 12: color = texture(uTextures[12], texCoordinates) * vColor; break;
    case 13: color = texture(uTextures[13], texCoordinates) * vColor; break;
    case 14: color = texture(uTextures[14], texCoordinates) * vColor; break;
    case 15: color = texture(uTextures[15], texCoordinates) * vColor; break;
    case 16: color = texture(uTextures[16], texCoordinates) * vColor; break;
    case 17: color = texture(uTextures[17], texCoordinates) * vColor; break;
    case 18: color = texture(uTextures[18], texCoordinates) * vColor; break;
    case 19: color = texture(uTextures[19], texCoordinates) * vColor; break;
    case 20: color = texture(uTextures[20], texCoordinates) * vColor; break;
    case 21: color = texture(uTextures[21], texCoordinates) * vColor; break;
    case 22: color = texture(uTextures[22], texCoordinates) * vColor; break;
    case 23: color = texture(uTextures[23], texCoordinates) * vColor; break;
    case 24: color = texture(uTextures[24], texCoordinates) * vColor; break;
    case 25: color = texture(uTextures[25], texCoordinates) * vColor; break;
    case 26: color = texture(uTextures[26], texCoordinates) * vColor; break;
    case 27: color = texture(uTextures[27], texCoordinates) * vColor; break;
    case 28: color = texture(uTextures[28], texCoordinates) * vColor; break;
    case 29: color = texture(uTextures[29], texCoordinates) * vColor; break;
    case 30: color = texture(uTextures[30], texCoordinates) * vColor; break;
    case 31: color = texture(uTextures[31], texCoordinates) * vColor; break;
  }
}