// Defaults for number of lights.
//方向光源数量
#ifndef NUM_DIR_LIGHTS
#define NUM_DIR_LIGHTS 3
#endif
//点光源数量
#ifndef NUM_POINT_LIGHTS
#define NUM_POINT_LIGHTS 0
#endif
//聚光灯光源数量
#ifndef NUM_SPOT_LIGHTS
#define NUM_SPOT_LIGHTS 0
#endif



// Include structures and functions for lighting.
#include "LightingUtil.hlsl"



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



struct DomainOut
{
	float4 PosH : SV_POSITION;
	float3 PosW : POSITION;
	float3 NormalW : NORMAL;
};



float4 PS(DomainOut pin) : SV_Target
{
		//对法线插值后，进行归一化
	// 该点的单位法向量
	// Interpolating normal can unnormalize it, so renormalize it.
		pin.NormalW = normalize(pin.NormalW);

		// Vector from point being lit to eye.
		//光线经表面上一点反射到观察点这一方向上的向量
		//从该点到观察点的单位向量
		float3 toEyeW = normalize(gEyePosW - pin.PosW);

		// Indirect lighting.
		//散射光强为散射光强*散射系数
		float4 ambient = gAmbientLight * gDiffuseAlbedo;

		const float shininess = 1.0f - gRoughness;
		//Material为LightUtils.hlsl中定义的材料数据，第三个参数改为了shininess
		Material mat = { gDiffuseAlbedo, gFresnelR0, shininess };
		float3 shadowFactor = 1.0f;

		//根据输入的光照数组计算所有光源形成的直接光照总和
		float4 directLight = ComputeLighting(gLights, mat, pin.PosW,
			pin.NormalW, toEyeW, shadowFactor);

		float4 litColor = ambient + directLight;

		// Common convention to take alpha from diffuse material.
		//从漫反射材料中获取alpha值
		litColor.a = gDiffuseAlbedo.a;
		return litColor;
}