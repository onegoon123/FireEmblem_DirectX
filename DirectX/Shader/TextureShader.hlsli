struct Input
{
    // 시멘틱 
    float4 Pos : POSITION0;
    float4 Color : COLOR;
};

struct OutPut
{
    // w나눈 다음  뷰포트 곱하고 픽셀 건져낼때 쓸 포지션 정보
    float4 Pos : SV_Position;
    float4 Color : COLOR;
};

OutPut Texture_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
	
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.Color = _Value.Color;
	
	// 다음단계에서 사용할 정보들.
    // _Value.Pos *= 월드뷰프로젝션;

    return OutPutValue;
}