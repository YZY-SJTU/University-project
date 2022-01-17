// Include structures and functions for lighting.
#include "LightingUtil.hlsl"



// Constant data that varies per frame.
cbuffer cbPerObject : register(b0)
{
	float4x4 gWorld;
	float4x4 gTexTransform;
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
	float3 NormalW : NORMAL;
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
	dout.NormalW = tri[0].NormalW * uv.x + tri[1].NormalW * uv.y + tri[2].NormalW * uv.z;
	// Displacement mapping
	//p.y = 0.3f*( p.z*sin(p.x) + p.x*cos(p.z) );
	//p.y = 0.0f;
	float4 PosW = mul(float4(p, 1.0f), gWorld);
	dout.PosW = PosW.xyz;
	dout.PosH = mul(PosW, gViewProj);

	return dout;
}
