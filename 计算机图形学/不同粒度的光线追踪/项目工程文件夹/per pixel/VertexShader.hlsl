// Include structures and functions for lighting.
#include "LightingUtil.hlsl"



// Constant data that varies per frame.
cbuffer cbPerObject : register(b0)
{
	float4x4 gWorld;
	float4x4 gTexTransform;
};



struct VertexIn
{
	float3 PosL    : POSITION;
	float3 NormalL : NORMAL;
};

struct VertexOut
{
	float3 PosL    : L_POSITION;
	//float3 PosH    : H_POSITION;
	//float3 PosW    : W_POSITION;
	float3 NormalW : NORMAL;
};



VertexOut VS(VertexIn vin)
{
	VertexOut vout;

	// Transform to world space.
	//将顶点变换到世界空间
	//float4 posW = mul(float4(vin.PosL, 1.0f), gWorld);
	//vout.PosW = posW.xyz;
	//vout.PosW = 0.0f
	//假设进行的是等比缩放
	// Assumes nonuniform scaling; otherwise, need to use inverse-transpose of world matrix.
	vout.NormalW = mul(vin.NormalL, (float3x3)gWorld);
	//vout.NormalW = 0.0f
	// Transform to homogeneous clip space.
	//将顶点变换到齐次裁剪空间(这个空间代表的是当前相机视角下的顶点位置)
	//vout.PosH = mul(posW, gViewProj);

	vout.PosL = vin.PosL;

	return vout;
}