const float SharpenEdge = 0.2;
const float Sharpen_val0 = 1.2;
const float sharpen = 0.9;		// Controls additional sharpening applied after previous processing. Strength should be max 0.25!
const float Average = 0.4;		// Set values to calculate the amount of  AA produced blur to consider for the sharpening pass
const float CoefBlur = 2;
#define CoefOri (1 + CoefBlur)
#define Sharpen_val1 ((Sharpen_val0-1) / 8.0)


float4 main
(	float2 uv : TEXCOORD0,
    uniform sampler2D sceneTex : s0,
	uniform float px,
	uniform float py
): COLOR0
{
	float dx = Average * px;
	float dy = Average * py;

	// Recover the original pixels
	float4 ori = tex2D(sceneTex, uv);
	// Gaussian filter
	//   [ 1, 2 , 1 ]
	//   [ 2, 4 , 2 ]
	//   [ 1, 2 , 1 ]
	float4 c1 = tex2D(sceneTex, uv + float2(-dx,-dy));
	float4 c2 = tex2D(sceneTex, uv + float2(0,-dy));
	float4 c3 = tex2D(sceneTex, uv + float2(dx,-dy));
	float4 c4 = tex2D(sceneTex, uv + float2(-dx,0));
	float4 c5 = tex2D(sceneTex, uv + float2(dx,0));
	float4 c6 = tex2D(sceneTex, uv + float2(-dx,dy));
	float4 c7 = tex2D(sceneTex, uv + float2(0,dy));
	float4 c8 = tex2D(sceneTex, uv + float2(dx,dy));
	//Normalize the values. Formula: 1 / (1+2+1+2+4+2+1+2+1) = 1 / 16 = .0625
	float4 blur = (c1+c3+c6+c8 + 2*(c2+c4+c5+c7)+ 4*ori)*0.0625;
	//Subtracting the blurred image from the original image
	float4 cori = CoefOri*ori - CoefBlur*blur;
	//For higher precision in the calculation of contour, requires slightly more processing power
	//   [ c1, c2 , c3 ]
	//   [ c4, ori , c5 ]
	//   [ c6, c7 , c8 ]
	/*
	c1 = tex2D(sceneTex, uv + float2(-px,-py));
	c2 = tex2D(sceneTex, uv + float2(0,-py));
	c3 = tex2D(sceneTex, uv + float2(px,-py));
	c4 = tex2D(sceneTex, uv + float2(-px,0));
	c5 = tex2D(sceneTex, uv + float2(px,0));
	c6 = tex2D(sceneTex, uv + float2(-px,py));
	c7 = tex2D(sceneTex, uv + float2(0,py));
	c8 = tex2D(sceneTex, uv + float2(px,py));
	*/
	// Horizontal gradient
	//   [ -1, 0 ,1 ]
	//   [ -2, 0, 2 ]
	//   [ -1, 0 ,1 ]
	float4 delta1 = (c3 + 2*c5 + c8)-(c1 + 2*c4 + c6);
	// Vertical gradient
	//   [ -1,- 2,-1 ]
	//   [  0,  0, 0 ]
	//   [  1,  2, 1 ]
	float4 delta2 = (c6 + 2*c7 + c8)-(c1 + 2*c2 + c3);
	// Calculate and sharpen the blurry edges
	float4 preSharpen;
	if (sqrt( mul(delta1, delta1) + mul(delta2, delta2) ) > SharpenEdge) 
		{
			// Contour sharpening
			preSharpen = ori * Sharpen_val0 - (c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8 ) * Sharpen_val1;
		}
	else 
		{
			// Return corrected image
			preSharpen = cori;
		}

	//post sharpen
	float4 color;
	color = 9.0 * preSharpen;
	color -= tex2D( sceneTex, uv + float2(px, py));
	color -= tex2D( sceneTex, uv + float2(0, py));
	color -= tex2D( sceneTex, uv + float2(-px, py));
	color -= tex2D( sceneTex, uv + float2(-px, 0));
	color -= tex2D( sceneTex, uv + float2(-px, -py));
	color -= tex2D( sceneTex, uv + float2(0, -py));
	color -= tex2D( sceneTex, uv + float2(px, -py));
	color -= tex2D( sceneTex, uv + float2(px, 0));
	color = color * 1 + (1.0 - 1) * preSharpen;
	color.a = preSharpen.a;

	return color;
}