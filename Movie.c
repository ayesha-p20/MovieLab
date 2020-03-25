/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
 MOVIE *movie = malloc(sizeof(MOVIE));
 ILIST *frame_list = CreateImageList();
 movie -> Frames = frame_list;
 return(movie);
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
 assert(movie != NULL);
 assert(movie -> Frames != NULL);
 DeleteImageList(movie->Frames);
 free(movie);
}

/* function to check and set range of a pixel*/
int clip(int x)
{
 if(x >= 0 && x <= 255)
 {
   return(x);
 }
 else if(x < 0)
 {
   return (0);
 }

 return (255);
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
  int i,x,y;
  IENTRY *entry; 
  entry = movie -> Frames -> First;
  unsigned char R,G,B,C,D,E;
  for(i = 0; i < MovieLength(movie); i++)
  {
   YUVIMAGE *YUV; 
   YUV = entry -> YUVImage;
   IMAGE *RGB = CreateImage(MovieWidth(movie),MovieHeight(movie));
   for(x = 0; x < MovieWidth(movie); x++)
   {
    for(y = 0; y < MovieHeight(movie); y++)
    {
        /* converting Y,U,V to R,G,B */
        C = GetPixelY(YUV,x,y) - 16;
        D = GetPixelU(YUV,x,y) - 128;
        E = GetPixelV(YUV,x,y) - 128;
        R = clip(( 298 * C + 409 * E + 128) >> 8);
        G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
        B = clip(( 298 * C + 516 * D + 128) >> 8);
        /* setting R,G,B pixels */
        SetPixelR(entry -> RGBImage,x,y,R);
        SetPixelG(entry -> RGBImage,x,y,G); 
        SetPixelB(entry -> RGBImage,x,y,B);
    }
   }
   /* moving on to the next entry */
   entry -> RGBImage = RGB;
   entry = entry -> Next;
  }
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
  int i,x,y;
  IENTRY *entry;
  entry = movie -> Frames -> First;
  unsigned char R,G,B,Y,U,V;
  for(i = 0; i < MovieLength(movie); i++)
  {
   YUVIMAGE *YUV = CreateYUVImage(MovieWidth(movie),MovieHeight(movie));
   IMAGE *RGB;
   RGB = entry -> RGBImage;
   for(x = 0; x < MovieWidth(movie); x++)
   {
    for(y = 0; y < MovieHeight(movie); y++)
    {
        R = GetPixelR(RGB,x,y);
        G = GetPixelG(RGB,x,y);
        B = GetPixelB(RGB,x,y);    
       /* converting R,G,B to Y,U,V */
        Y = clip((( 66*R+129*G+ 25*B+128)>>8)+ 16);
        U = clip(((-38*R- 74*G+112*B+128)>>8)+128);
        V = clip(((112*R- 94*G- 18*B+128)>>8)+128); 
        /* setting Y,U,V pixels */
        SetPixelY(YUV,x,y,Y);
        SetPixelU(YUV,x,y,U);
        SetPixelV(YUV,x,y,V);
    }
   }
   /* moving on to the next entry */
   entry -> YUVImage = YUV;
   entry = entry -> Next;
  }

}

int MovieLength(const MOVIE *movie)
{
    return movie->Frames->length;
}

int MovieHeight(const MOVIE *movie)
{
    if(movie->Frames->First->RGBImage)
    {
        return movie->Frames->First->RGBImage->H;
    }//fi

    else if(movie->Frames->First->YUVImage)
    {
        return movie->Frames->First->YUVImage->H;
    }//fi esle

    else
    return 0;
}

int MovieWidth(const MOVIE *movie)
{
    if(movie->Frames->First->RGBImage)
        {
                return movie->Frames->First->RGBImage->W;
        }//fi

    else if(movie->Frames->First->YUVImage)
        {
                return movie->Frames->First->YUVImage->W;
        }//fi esle

    else
        return 0;
}

/* EOF */
