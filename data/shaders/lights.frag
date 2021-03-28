uniform vec4 lightColor; 
uniform vec3 falloff;
uniform float intensity;
uniform vec2 iResolution;
uniform float radius;
uniform vec2 lightPos;

void main() 
{ 
	vec2 uv = gl_FragCoord.xy / iResolution.xy;

	lightPos.xy = lightPos.xy / iResolution.xy;
	
	// Calculate the delta position of the light
	vec3 delta = vec3(lightPos.xy - uv.xy, 0);
    
    // Ensure a fixed light radius
	delta.x /= radius / iResolution.x;
	delta.y /= radius / iResolution.y;
    
    // Calculate the distance from the fragment to the light
    float dist = length(delta);

	//float dist = distance(uv, lightPos.xy);

	vec3 d = lightColor.rgb * lightColor.a;

	float attenuation = intensity / (falloff.x + (falloff.y * dist) + (falloff.z * dist * dist));

	vec3 light = d * attenuation;

	light = pow(light, vec3(1.0 / 2.2));

	vec4 result = vec4(light, attenuation);

	gl_FragColor = result;
};