// Defaults for number of lights.
//�����Դ����
#ifndef NUM_DIR_LIGHTS
#define NUM_DIR_LIGHTS 0
#endif
//���Դ����
#ifndef NUM_POINT_LIGHTS
#define NUM_POINT_LIGHTS 1
#endif
//�۹�ƹ�Դ����
#ifndef NUM_SPOT_LIGHTS
#define NUM_SPOT_LIGHTS 0
#endif

// Include structures and functions for lighting.
#include "LightingUtil.hlsl"



// Constant data that varies per frame.
cbuffer cbPerObject : register(b0)
{
	float4x4 gWorld;
	float4x4 gTexTransform;
};

cbuffer cbMaterial : register(b1)
{
	float4   gDiffuseAlbedo;
	float3   gFresnelR0;
	float    gRoughness;
	float4x4 gMatTransform;
};

// Constant data that varies per material.
cbuffer cbPass : register(b2)
{
	float4x4 gView;
	float4x4 gInvView;
	float4x4 gProj;
	float4x4 gInvProj;
	float4x4 gViewProj;
	float4x4 gInvViewProj;
	float3 gEyePosW;
	float cbPerObjectPad1;
	float2 gRenderTargetSize;
	float2 gInvRenderTargetSize;
	float gNearZ;
	float gFarZ;
	float gTotalTime;
	float gDeltaTime;
	float4 gAmbientLight;

	float4 gFogColor;
	float gFogStart;
	float gFogRange;
	float2 cbPerObjectPad2;

	// Indices [0, NUM_DIR_LIGHTS) are directional lights;
	// indices [NUM_DIR_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHTS) are point lights;
	// indices [NUM_DIR_LIGHTS+NUM_POINT_LIGHTS, NUM_DIR_LIGHTS+NUM_POINT_LIGHT+NUM_SPOT_LIGHTS)
	// are spot lights for a maximum of MaxLights per object.
	Light gLights[MaxLights];
};

RaytracingAccelerationStructure MyAccelerationStructure : register(b3, space0);


struct PatchTess
{
	float EdgeTess[3]   : SV_TessFactor;
	float InsideTess[1] : SV_InsideTessFactor;
};

struct HullOut
{
	float3 PosL : L_POSITION;
	//float3 PosH : H_POSITION;
	//float3 PosW : W_POSITION;
	float3 NormalW : NORMAL;
};

struct DomainOut
{
	float4 PosH : SV_POSITION;
	float3 PosW : POSITION;
	float4 Color : COLOR;
};



// The domain shader is called for every vertex created by the tessellator.  
// It is like the vertex shader after tessellation.
[domain("tri")]
DomainOut DS(PatchTess patchTess,
	float3 uv : SV_DomainLocation,
	const OutputPatch<HullOut, 3> tri)
{
	DomainOut dout;

	// Bilinear interpolation.
	float3 p = tri[0].PosL * uv.x + tri[1].PosL * uv.y + tri[2].PosL * uv.z;
	float4 PosW = mul(float4(p, 1.0f), gWorld);
	dout.PosW = PosW.xyz;

	dout.PosH = mul(PosW, gViewProj);

	float3 NormalW = tri[0].NormalW * uv.x + tri[1].NormalW * uv.y + tri[2].NormalW * uv.z;
	NormalW = normalize(NormalW);

	RayQuery<RAY_FLAG_CULL_NON_OPAQUE |
		RAY_FLAG_SKIP_PROCEDURAL_PRIMITIVES |
		RAY_FLAG_ACCEPT_FIRST_HIT_AND_END_SEARCH> query;

	// Trace the ray.
	// Set the ray's extents.
	RayDesc ray;
	ray.Origin = gEyePosW;
	ray.Direction = normalize(dout.PosW - gEyePosW);;
	// Set TMin to a non-zero small value to avoid aliasing issues due to floating - point errors.
	// TMin should be kept small to prevent missing geometry at close contact areas.
	ray.TMin = 0.0001f;
	ray.TMax = 10000.0f;

	query.TraceRayInline(MyAccelerationStructure, RAY_FLAG_ACCEPT_FIRST_HIT_AND_END_SEARCH, ~0, ray);

	query.Proceed();

	if (query.CommittedStatus() == COMMITTED_TRIANGLE_HIT)
	{

		// Vector from point being lit to eye.
		//���߾�������һ�㷴�䵽�۲����һ�����ϵ�����
		//�Ӹõ㵽�۲��ĵ�λ����
		float3 toEyeW = normalize(gEyePosW - dout.PosW);

		// Indirect lighting.
		//ɢ���ǿΪɢ���ǿ*ɢ��ϵ��
		float4 ambient = gAmbientLight * gDiffuseAlbedo;

		const float shininess = 1.0f - gRoughness;
		//MaterialΪLightUtils.hlsl�ж���Ĳ������ݣ�������������Ϊ��shininess
		Material mat = { gDiffuseAlbedo, gFresnelR0, shininess };
		float3 shadowFactor = 1.0f;

		//ʹ�ô�camera�����ray����raytracing��ʹ��lighting��������closet hit��color
		Light mLight[MaxLights];
		mLight[0].Strength = float3(0.6f, 0.6f, 0.6f);
		mLight[0].Position = gEyePosW;
		mLight[0].FalloffStart = 0.001f;
		mLight[0].FalloffEnd = 10000.0f;
		//��������Ĺ�������������й�Դ�γɵ�ֱ�ӹ����ܺ�
		float4 directLight = ComputeLighting(mLight, mat, dout.PosW,
			NormalW, toEyeW, shadowFactor);

		float4 litColor = ambient + directLight;

		// Common convention to take alpha from diffuse material.
		//������������л�ȡalphaֵ
		litColor.a = gDiffuseAlbedo.a;

		dout.Color = litColor;
	}
	else
	{
		// Indirect lighting.
		//ɢ���ǿΪɢ���ǿ*ɢ��ϵ��
		float4 ambient = gAmbientLight * gDiffuseAlbedo;
		dout.Color = ambient;
	}

	return dout;
}
