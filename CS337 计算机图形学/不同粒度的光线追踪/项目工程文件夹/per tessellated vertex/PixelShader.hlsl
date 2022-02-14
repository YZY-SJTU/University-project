struct DomainOut
{
	float4 PosH : SV_POSITION;
	float3 PosW : POSITION;
	float4 Color : COLOR;
};



float4 PS(DomainOut pin) : SV_Target
{
	return pin.Color;
}