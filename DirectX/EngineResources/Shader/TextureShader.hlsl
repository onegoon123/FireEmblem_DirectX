// 쉐이더를 짜게되면 다음의 규칙을 지켜야 한다.

// 어떤 정보가 들어올지 구조체로 만들어야 합니다.
// 어디가 포지션이고 어디가 컬이고
// 이름 마음대로
struct Input
{
	// 시맨틱      어떤역할을 가졌는지 
    // 버텍스 쉐이더에다가 순서를 어떻게 해놓건 사실 그건 상관이 없어요.
    // 중요한건 버텍스 버퍼고 
    float4 Pos : POSITION;
    float4 Color : COLOR;
};

struct OutPut
{
    // 레스터라이저야 이 포지션이
    // w나눈 다음  뷰포트 곱하고 픽셀 건져낼때 쓸포지션 정보를 내가 보낸거야.
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};


// 월드뷰프로젝션

OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    // OutPutValue.Pos = mul(_Value.Pos, WorldMatrix);
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.Color = _Value.Color;
	
	// 다음단계에서 사용할 정보들.
    // OutPutValue.Pos *= 월드뷰프로젝션;

    return OutPutValue;
}

struct OutColor
{
    // 깔아놓은 도화지중 0번째 도화지에 출력해라.
    float4 Color : SV_Target0;
};

OutColor Texture_PS(OutPut _Value)
{
    OutColor ReturnColor = (OutColor) 0;
    ReturnColor.Color = _Value.Color;
    return ReturnColor;
}