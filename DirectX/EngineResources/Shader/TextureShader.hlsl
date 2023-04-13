// 쉐이더를 짜게되면 다음의 규칙을 지켜야 한다.

// 어떤 정보가 들어올지 구조체로 만들어야 합니다.
// 어디가 포지션이고 어디가 컬이고
// 이름 마음대로
struct Input 
{
	// 시맨틱      어떤역할을 가졌는지 
	float4 Pos   : POSITION0;
	float4 Color : COLOR;
};

struct OutPut
{
    // 레스터라이저야 이 포지션이
    // w나눈 다음  뷰포트 곱하고 픽셀 건져낼때 쓸포지션 정보를 내가 보낸거야.
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};

OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut)0;
	
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.Color = _Value.Color;
	
	// 다음단계에서 사용할 정보들.
    // _Value.Pos *= 월드뷰프로젝션;

    return OutPutValue;
}