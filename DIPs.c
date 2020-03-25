/*********************************************************************/
/* 02/27/20 Bo Tsai      updated for EECS22 assignment Winter2020    */
/* Author: Tim Schmidt Date: 11/09/2017                              */
/*                                                                   */
/* DIPs.c: source file for DIP operations                            */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "DIPs.h"
#include "Constants.h"
#include <math.h>

IMAGE *BlackNWhite(IMAGE *image, int percent)
{
    double per = (double)(percent/100.0);
    int gray_factor;
    int R_offset, G_offset, B_offset;
    unsigned char R,G,B;
    int x,y;
    for (x = 0; x < image->W; x++)
    {
      for(y = 0; y < image->H; y++)
      {
        gray_factor = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y))/3;
        R_offset = gray_factor - GetPixelR(image,x,y);
        G_offset = gray_factor - GetPixelG(image,x,y);
        B_offset = gray_factor - GetPixelB(image,x,y);
        /* calculating new R,G,B values */
        R = GetPixelR(image,x,y) + (R_offset * per);
        G = GetPixelG(image,x,y) + (G_offset * per);
        B = GetPixelB(image,x,y) + (B_offset * per);
        /* assigning new values to R,G,B */      
        SetPixelR(image, x, y, R);
        SetPixelG(image, x, y, G);
        SetPixelB(image, x, y, B);
      }
    }

    return image;
}

IMAGE *HueRotate(IMAGE *image, int percent)
{
    double per = (double)(percent/100.0);
    double degree; // modified this line to make it work
    double a, b, r;
    degree = (double)(per * 360.0);
    double d = degree * PI / 180.0;
    double tmpr, tmpg, tmpb;

    a = (2 * cos(d) + 1.0) / 3.0;
    b = (1.0 - cos(d)) / 3.0 - sin(d) / sqrt(3.0);
    r = (1.0 - cos(d)) / 3.0 + sin(d) / sqrt(3.0);

    for (int x = 0; x < image->W; x++)
    {   for (int y = 0; y < image->H; y++)
        {  
            /* calculating new R,G,B values */
            tmpr = GetPixelR(image, x, y) * a + GetPixelG(image, x, y) * b + GetPixelB(image, x, y) * r;
            tmpg = GetPixelR(image, x, y) * r + GetPixelG(image, x, y) * a + GetPixelB(image, x, y) * b;
            tmpb = GetPixelR(image, x, y) * b + GetPixelG(image, x, y) * r + GetPixelB(image, x, y) * a;
            /* assigning new values to R,G,B */
            SetPixelR(image, x, y, (tmpr > MAX_PIXEL)?MAX_PIXEL:(tmpr < 0)?0:tmpr);
            SetPixelG(image, x, y, (tmpg > MAX_PIXEL)?MAX_PIXEL:(tmpg < 0)?0:tmpg);
            SetPixelB(image, x, y, (tmpb > MAX_PIXEL)?MAX_PIXEL:(tmpb < 0)?0:tmpb);
        }
    }
    return image;
}

/* EOF */
