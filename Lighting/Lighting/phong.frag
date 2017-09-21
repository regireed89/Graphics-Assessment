#version 410



uniform vec3 direction;
uniform vec3 Id; //vec3(1,1,1);
uniform vec3 Is;  //vec3(1,1,1);
uniform vec3 Ia;  //vec3(0.25f,0.25f,0.25f);


uniform vec3 Ka;// = vec3(1,0,0);
uniform vec3 Kd;// = vec3(1,0,0);
uniform vec3 Ks;// = vec3(1,0,0);
uniform float a;
uniform vec3 camPos;

in vec4 vNormal;
in vec4 vPosition;
in vec4 vColor;
in vec2 vUV;
in vec4 vTangent;
in vec3 P;
 out vec4 FragColor;
 uniform vec3 L;

 void main()
 {	
	vec3 N = normalize(vNormal).xyz;

	vec3 Ambient = Ka * Ia;
	float Ndl = max(0.0f,dot(direction, N));
	vec3 Diffuse = Kd * Id * Ndl;

	vec3 R = reflect(direction, N);
	vec3 E = normalize(camPos - P);

	float specTerm = pow(min(0.0f, dot(R, E)), a);
	vec3 Specular = Ks * Is * specTerm;
	FragColor = vec4(Ambient + Diffuse + Specular ,1);

 }