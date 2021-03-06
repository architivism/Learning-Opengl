      #version 330 core
      layout(location=0) in vec3 aPos;
	  layout(location=1) in vec3 aNormal;
	  layout(location=2) in vec2 aTexCoord;
	  out vec3 Normal;
	  out vec3 FragPos;
	  out vec3 LightPos;
	  out vec2 TexCoord;

	  uniform mat4 model;

	  layout(std140) uniform Matrices
	  {
	    mat4 projection;
	    mat4 view;
	    
	  };
	  
	  
	  void main()
	  {
	    gl_Position=projection*view*model*vec4(aPos.x,aPos.y,aPos.z,1.0f);
		Normal=mat3(transpose(inverse(model)))*aNormal;
		FragPos=vec3(view*model*vec4(aPos.x,aPos.y,aPos.z,1.0f));
		
		TexCoord=aTexCoord;
	  }