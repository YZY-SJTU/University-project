// Defaults for number of lights.
//方向光源数量
#ifndef NUM_DIR_LIGHTS
#define NUM_DIR_LIGHTS 0
#endif
//点光源数量
#ifndef NUM_POINT_LIGHTS
#define NUM_POINT_LIGHTS 1
#endif
//聚光灯光源数量
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



struct VertexIn
{
	float3 PosL    : POSITION;
	float3 NormalL : NORMAL;
};

struct VertexOut
{
	float3 PosL    : L_POSITION;
	float4 Color : COLOR;
};



VertexOut VS(VertexIn vin)
{
	VertexOut vout;

	//假设进行的是等比缩放
	// Assumes nonuniform scaling; otherwise, need to use inverse-transpose of world matrix.
	float3 NormalW = mul(vin.NormalL, (float3x3)gWorld);
	NormalW = normalize(NormalW);
	vout.PosL = vin.PosL;
	// Transform to world space.
	//将顶点变换到世界空间
	float3 posW = mul(float4(vin.PosL, 1.0f), gWorld).xyz;


	RayQuery<RAY_FLAG_CULL_NON_OPAQUE |
		RAY_FLAG_SKIP_PROCEDURAL_PRIMITIVES |
		RAY_FLAG_ACCEPT_FIRST_HIT_AND_END_SEARCH> query;

	RayDesc ray;
	ray.Origin = gEyePosW;
	ray.Direction = normalize(posW - gEyePosW);
	// Set TMin to a non-zero small value to avoid aliasing issues due to floating - point errors.
	// TMin should be kept small to prevent missing geometry at close contact areas.
	ray.TMin = 0.0001f;
	ray.TMax = 10000.0f;

	query.TraceRayInline(MyAccelerationStructure, RAY_FLAG_ACCEPT_FIRST_HIT_AND_END_SEARCH, ~0, ray);

	query.Proceed();

	if (query.CommittedStatus() == COMMITTED_TRIANGLE_HIT)
	{

		float3 toEyeW = normalize(gEyePosW - posW);

		float4 ambient = gAmbientLight * gDiffuseAlbedo;

		const float shininess = 1.0f - gRoughness;
		//Material为LightUtils.hlsl中定义的材料数据，第三个参数改为了shininess
		Material mat = { gDiffuseAlbedo, gFresnelR0, shininess };
		float3 shadowFactor = 1.0f;
		//使用从camera发射的ray进行raytracing，使用lighting函数计算closet hit的color
		Light mLight[MaxLights];
		mLight[0].Strength = float3(0.6f, 0.6f, 0.6f);
		mLight[0].Position = gEyePosW;
		mLight[0].FalloffStart = 0.001f;
		mLight[0].FalloffEnd = 10000.0f;
		//根据输入的光照数组计算所有光源形成的直接光照总和
		//根据输入的光照数组计算所有光源形成的直接光照总和
		float4 directLight = ComputeLighting(mLight, mat, posW,
			NormalW, toEyeW, shadowFactor);

		float4 litColor = ambient + directLight;

		// Common convention to take alpha from diffuse material.
		//从漫反射材料中获取alpha值
		litColor.a = gDiffuseAlbedo.a;

		vout.Color = litColor;
	}
	else
	{
		float4 ambient = gAmbientLight * gDiffuseAlbedo;
		vout.Color = ambient;
	}
	return vout;
}