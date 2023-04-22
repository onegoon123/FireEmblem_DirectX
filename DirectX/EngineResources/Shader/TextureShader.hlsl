// 쉐이더를 짜게되면 다음의 규칙을 지켜야 한다.

// 0~ 16번 슬롯 
cbuffer TransformData : register(b0)
{
    float4 LocalScale;
    float4 LocalRotation;
    float4 LocalQuaternion;
    float4 LocalPosition;
    float4 WorldScale;
    float4 WorldRotation;
    float4 WorldQuaternion;
    float4 WorldPosition;
    float4x4 LocalScaleMatrix;
    float4x4 LocalRotationMatrix;
    float4x4 LocalPositionMatrix;
    float4x4 LocalWorldMatrix;
    float4x4 WorldMatrix;
    float4x4 View;
    float4x4 Projection;
    float4x4 ViewPort;
    float4x4 WorldViewProjectionMatrix;
}

// 어떤 정보가 들어올지 구조체로
// 어디가 포지션이고 어디가 컬이고
// 이름 마음대로
struct Input
{
	// 시맨틱      어떤역할을 가졌는지 
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    // 레스터라이저에게 보냄
    // w나눈 다음  뷰포트 곱하고 픽셀 건져낼때 쓸포지션 정보
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};


// 월드뷰프로젝션

OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    _Value.Pos.w = 1.0f;
    OutPutValue.Pos = mul(_Value.Pos, WorldViewProjectionMatrix);
    // OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
	
	// 다음단계에서 사용할 정보들.
    // OutPutValue.Pos *= 월드뷰프로젝션;

    return OutPutValue;
}


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
    
    return Color;
}