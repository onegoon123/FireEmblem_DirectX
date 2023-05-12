
struct OutPut
{
    // 레스터라이저에게 보냄
    // w나눈 다음  뷰포트 곱하고 픽셀 건져낼때 쓸포지션 정보
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};
cbuffer EffectData : register(b0)
{
    float4 Scale;
    float4 LerpColor;
    float LerpT;
    bool IsBlur;
    float BlurLevel;
    float Hue;
    float Saturation;
    float Brightness;
    float Opacity;
    float None;
}

Texture2D DiffuseTex : register(t0);
SamplerState CLAMPSAMPLER : register(s0);

static const float Weight[13] =
{
    0.0561, 0.1353, 0.278, 0.4868, 0.7261, 0.9231, 1, 0.9231, 0.7261, 0.4868, 0.278, 0.1353, 0.0561
};
static const float Total = 6.2108;

float4 Texture_PS(OutPut _Value) : SV_Target0
{
    float4 Out = 0;
    
    if (true == IsBlur)
    {
        {
            float4 t = _Value.UV;
            float4 uv = 0;
    
            float tv = BlurLevel / Scale.y;
            for (int i = -6; i < 6; i++)
            {
                uv.xy = t.xy + float2(0, tv * i);
                
                float2 AtlasUV;
                    
                Out += Weight[6 + i] * DiffuseTex.Sample(CLAMPSAMPLER, uv.xy);;
            }
            Out /= Total;
        }
        float4 Out2 = 0;
        {
            float4 t = _Value.UV;
            float4 uv = 0;
    
            float tu = BlurLevel / Scale.x;
            for (int i = -6; i < 6; i++)
            {
                uv.xy = t.xy + float2(tu * i, 0);
                Out2 += Weight[6 + i] * DiffuseTex.Sample(CLAMPSAMPLER, uv.xy);;
            }
            Out2 /= Total;
        }
        Out += Out2;
        Out /= 2;

    }
    else
    {
        Out = DiffuseTex.Sample(CLAMPSAMPLER, _Value.UV.xy);
    }
    

    float angle = radians(Hue);
    float3 k = float3(0.57735, 0.57735, 0.57735);
    float cosAngle = cos(angle);
    Out.rgb = Out.rgb * cosAngle + cross(k, Out.rgb) * sin(angle) + k * dot(k, Out.rgb) * (1 - cosAngle);
    
    float3 intensity = dot(Out.rgb, float3(0.299, 0.587, 0.114));
    Out.rgb = lerp(intensity, Out.rgb, Saturation);
    
    Out.rgb = Out.rgb + Brightness;
    
    Out.a = lerp(0, Out.a, Opacity);
    
    if (LerpColor.a != 0)
    {
        if (0 < Out.a)
        {
            float4 ChangeColor = LerpColor;
            ChangeColor.a = Out.a;
            Out = lerp(Out, ChangeColor, LerpT);
        }
    }
    
    
    return Out;
}
