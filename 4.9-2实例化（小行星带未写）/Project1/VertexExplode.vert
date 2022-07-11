   #version 330 core
      layout(location=0) in vec3 aPos;
	  layout(location=1) in vec3 aNormal;
	  layout(location=2) in vec2 aTexCoord;
	  out vec3 Normal;
	 
	  uniform mat4 model;

	  out VS_OUT {
        vec2 texCoords;
        mat4 model1;
     } vs_out;

	  layout(std140) uniform Matrices
	  {
	    mat4 projection;
	    mat4 view;
	    
	  };
	  
	  
	  void main()
	  {
	    gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0f);
		Normal=mat3(transpose(inverse(model)))*aNormal;
		vs_out.model1=model;
		vs_out.texCoords=aTexCoord;
	  }