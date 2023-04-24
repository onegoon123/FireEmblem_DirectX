struct OutPut
{
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};


cbuffer OutPixelColor : register(b0)
{
    float4 OutColor;
}
Texture2D DiffuseTex : register(t0);
SamplerState CLAMPSAMPLER : register(s0);

float4 Texture_PS(OutPut _Value) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(CLAMPSAMPLER, _Value.UV.xy);
    
    if (Color.a == 0)
    {
        clip(-1);
    }
    
    float GrayValue = 0.299f * Color.r + 0.587f * Color.g + 0.114f * Color.b;
    Color.rgb = float3(GrayValue, GrayValue, GrayValue);
    
    return Color;
}