// Defaults for number of lights.
//�����Դ����
#ifndef NUM_DIR_LIGHTS
#define NUM_DIR_LIGHTS 3
#endif
//���Դ����
#ifndef NUM_POINT_LIGHTS
#define NUM_POINT_LIGHTS 0
#endif
//�۹�ƹ�Դ����
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
		//�Է��߲�ֵ�󣬽��й�һ��
	// �õ�ĵ�λ������
	// Interpolating normal can unnormalize it, so renormalize it.
		pin.NormalW = normalize(pin.NormalW);

		// Vector from point being lit to eye.
		//���߾�������һ�㷴�䵽�۲����һ�����ϵ�����
		//�Ӹõ㵽�۲��ĵ�λ����
		float3 toEyeW = normalize(gEyePosW - pin.PosW);

		// Indirect lighting.
		//ɢ���ǿΪɢ���ǿ*ɢ��ϵ��
		float4 ambient = gAmbientLight * gDiffuseAlbedo;

		const float shininess = 1.0f - gRoughness;
		//MaterialΪLightUtils.hlsl�ж���Ĳ������ݣ�������������Ϊ��shininess
		Material mat = { gDiffuseAlbedo, gFresnelR0, shininess };
		float3 shadowFactor = 1.0f;

		//��������Ĺ�������������й�Դ�γɵ�ֱ�ӹ����ܺ�
		float4 directLight = ComputeLighting(gLights, mat, pin.PosW,
			pin.NormalW, toEyeW, shadowFactor);

		float4 litColor = ambient + directLight;

		// Common convention to take alpha from diffuse material.
		//������������л�ȡalphaֵ
		litColor.a = gDiffuseAlbedo.a;
		return litColor;
}