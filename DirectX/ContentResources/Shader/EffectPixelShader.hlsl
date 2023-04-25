struct OutPut
{
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

cbuffer EffectData : register(b10)
{
    float4 FlashColor;
    float t;
    bool IsGrayScale;
}

Texture2D DiffuseTex : register(t0);
SamplerState CLAMPSAMPLER : register(s0);



float4 Texture_PS(OutPut _Value) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(CLAMPSAMPLER, _Value.UV.xy);

    if (true == IsGrayScale)
    {
        float GrayValue = 0.299f * Color.r + 0.587f * Color.g + 0.114f * Color.b;
        Color.rgb = float3(GrayValue, GrayValue, GrayValue);
    }
    if (FlashColor.a != 0)
    {
        Color = lerp(Color, FlashColor, t);
    }
    
    return Color;
}
