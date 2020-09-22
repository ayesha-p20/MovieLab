/*********************************************************************/
/* IterativeFilter.c: file for iterative filters                     */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include "IterativeFilter.h"
#include <assert.h>

MOVIE *doIterativeFilter(IMAGE *image, iterableFilter filter, int start, int end, int change)
{
  /* movie is the new movie that is generated from theinput image */
  MOVIE *movie;
  movie = CreateMovie();
  assert(image != NULL);
  int i;
  if(start < end)
  {
    for(i = start; i<= end; i+=change)
    {
       /* appending new image to the frame list */
       AppendRGBImage(movie->Frames,filter(CopyImage(image),i));
    }
  }
  else if(start > end)
  {
   for(i = start; i >= end; i-=change)
    {
       /* appending new image to the frame list */
       AppendRGBImage(movie->Frames,filter(CopyImage(image),i));
    }
  }
  else if(start == end) /* if the movie only has a single frame */
  {
      /* appending new image to the frame list */
      AppendRGBImage(movie->Frames,filter(CopyImage(image),1));
  }
  assert(movie != NULL);
  /* converting RGB movie to YUV movie */
  RGB2YUVMovie(movie);  
  DeleteImage(image);
  return(movie);
}
