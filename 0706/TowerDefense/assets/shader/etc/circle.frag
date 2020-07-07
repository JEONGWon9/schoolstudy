#version 150

#if GL_ES
precision mediump float;
#endif



uniform vec2 iResolution;  
out vec4 fragColor;



void main()
{


	vec2 uv = gl_FragCoord.xy / iResolution.xy;
    uv.x *= iResolution.y/iResolution.x;
	

	
	 

	fragColor = 


	
}

//iPoint c = iPointMake((width - 1) / 2.0f, (height - 1) / 2.0f);
//
//        for (int j = 0; j < height; j++)
//        {
//            for (int i = 0; i < width; i++)
//            {
//                float d = sqrtf((i - c.x) * (i - c.x) + (j - c.y) * (j - c.y));//whatisthis
//                if (d < 15.5)
//                {
//                    uint8* c = &rgba[potW * 4 * j + 4 * i];
//                    c[0] = 255;
//                    c[1] = 0;
//                    c[2] = 255;
//                    if (d <=15.5)
//                    {
//                        c[3] = 255;
//                    }
//                  
//                }
//            }
//        }