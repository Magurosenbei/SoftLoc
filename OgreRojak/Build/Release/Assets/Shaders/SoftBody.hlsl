float4x4 matWorld;
float4x4 matViewProjection;

float4 vViewPosition;
float4 LightPosition;

void Vertex_Parse(

in  float4 inPosition   : POSITION,
in  float3 inNormal     : NORMAL,
in  float2 inTexCoord   : TEXCOORD0,

out float4	outPosition :	POSITION,
out float2	outTexCoord	:	TEXCOORD0,
out float3	outNormal   :	TEXCOORD1,
out	float3	outLightDir	:	TEXCOORD2,
out	float3	outViewDir	:	TEXCOORD3,
out	float3	outLVDir	:	TEXCOORD4)
{
	outTexCoord = inTexCoord;	// No Changes
	
	outNormal = inNormal;
	outPosition = inPosition;
	
	outLightDir = normalize(LightPosition - outPosition).xyz;
	outViewDir 	= normalize(vViewPosition - outPosition).xyz;
	outLVDir	= normalize(outViewDir - outLightDir).xyz;
	
	outPosition = mul(matViewProjection, outPosition);
}

/* Pixel Shader */
sampler ColorSampler;
sampler ToneSampler;

float	SpecularPw;
float	Specular;

float3	RimMinMaxMul;

float4	SpecularColor;
float4	DiffuseColor;
float4	AmbientColor;
float4	RimColor;


void Pixel_Parse(
in	float2	inTexCoord	:	TEXCOORD0,
in	float3	inNormal	:	TEXCOORD1,
in	float3	inLightDir	:	TEXCOORD2,
in	float3	inViewDir	:	TEXCOORD3,
in	float3	inLVDir		:	TEXCOORD4,

out float4 outColor     : COLOR)
{
	outColor = tex2D(ColorSampler, inTexCoord);
	float 	LightDotNormal = dot(inNormal, inLightDir);
	LightDotNormal = max(0.0, LightDotNormal);
	
	float3	Reflect = reflect(-inLightDir, inNormal);
	
	float4	LitV = lit(LightDotNormal, dot(Reflect, inViewDir), SpecularPw);

	float3	Diffuse 	= outColor.xyz * tex1D(ToneSampler, LitV[1]) * DiffuseColor;
	float3	SpecularC 	= SpecularColor * LitV[2] * Specular;
	float3	Ambient		= AmbientColor * outColor.xyz * LitV[0];
	
	float	RimValue 	= smoothstep(RimMinMaxMul[0], RimMinMaxMul[1], 1 - dot(inNormal, inViewDir));
	float3	RimColorC	= RimColor * RimValue * RimMinMaxMul[2];
	outColor.xyz = saturate(Diffuse + SpecularC + RimColorC);
}

