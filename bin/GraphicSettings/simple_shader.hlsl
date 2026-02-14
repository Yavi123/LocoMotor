float4 mainVS(float4 pos : POSITION, uniform float4x4 worldViewProj_m) : POSITION
{
	return mul(worldViewProj_m,pos);
}
 
float4 mainPS() : COLOR 
{
	return float4(0, 0, 1, 1);
}