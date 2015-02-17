//--------------------------------------------------------------------------------
// TextureVS.hlsl
//
// This vertex shader serves as a pass through for pre-transformed vertices.  This
// is typically used for full screen quad rendering.
//
// Copyright (C) 2010 Jason Zink.  All rights reserved.
//--------------------------------------------------------------------------------

matrix WorldViewProj;

struct VsIn
{
	float3 position : POSITION;
	float2 tex		: TEXCOORDS;
};

struct VsOut
{
	float4 position : SV_Position;
	float2 tex		: TEXCOORDS;
};

VsOut main(in VsIn In)
{
	VsOut output;

	output.position = mul(WorldViewProj, float4(In.position, 1.0f));

	output.tex = In.tex;

	return output;
}

