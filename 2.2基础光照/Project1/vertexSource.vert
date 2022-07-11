      #version 330 core
      layout(location=0) in vec3 aPos;
	  layout(location=1) in vec3 aNormal;
	  out vec3 Normal;
	  out vec3 FragPos;
	  out vec3 LightPos;

	  uniform mat4 model;
	  uniform mat4 view;
	  uniform mat4 projection;
	  uniform vec3 lightpos;
	  void main()
	  {
	    gl_Position=projection*view*model*vec4(aPos.x,aPos.y,aPos.z,1.0f);
		Normal=mat3(transpose(inverse(model)))*aNormal;
		FragPos=vec3(view*model*vec4(aPos.x,aPos.y,aPos.z,1.0f));
		LightPos=vec3(view*vec4(lightpos,1.0f));
	  }