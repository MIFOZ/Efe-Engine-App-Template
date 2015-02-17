//--------------------------------------------------------------------------------
// FinalPS.hlsl
//
// This pixel shader samples the ambient occlusion buffer and uses its value to 
// modify the ambient term of a standard lighting equation.
//
// Copyright (C) 2009 Jason Zink.  All rights reserved.
//--------------------------------------------------------------------------------

Texture2D  diffuseMap : register(t0);
SamplerState diffuseSampler : register(s0);

struct VsOut
{
	float4 position : SV_Position;
	float2 tex		: TEXCOORDS;
};

float4 main(in VsOut In) : SV_Target
{
	return diffuseMap.Sample(diffuseSampler, In.tex);
}

