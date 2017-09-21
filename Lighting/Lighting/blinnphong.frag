#version 410



uniform vec3 direction;
uniform vec3 Id; 
uniform vec3 Is;  
uniform vec3 Ia;  


uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks; 
uniform float a;
uniform vec3 camPos;

in vec4 vNormal;
in vec4 vPosition;
in vec4 vColor;
in vec2 vUV;
in vec4 vTangent;
 out vec4 FragColor;
 uniform vec3 L;

 void main()
 {	
	vec3 H = normalize(direction + V);
	float blin = pow(dot(N,H),a);	

	vec3 N = normalize(vNormal).xyz;
	vec3 P = vPosition.xyz;

	vec3 Ambient = Ka * Ia;
	float Ndl = max(0.0f,dot(direction, N));
	vec3 Diffuse = Kd * Id * Ndl;

	vec3 R = reflect(direction, N);
	vec3 E = normalize(camPos - P);

	float specTerm = pow(max(0.0f, dot(R, E)), a);
	vec3 Specular = Ks * Is * specTerm;
	FragColor = vec4(Ambient + Diffuse + Specular ,1);

 }



	
