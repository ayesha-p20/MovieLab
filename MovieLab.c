/*********************************************************************/
/* MovieLab.c: source file for the main function                     */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include "MovieIO.h"
#include "IterativeFilter.h"

int main(int argc, char *argv[])
{
    IMAGE *input;
    int importFlag = 0;
    // allocate necessary variables
    MOVIE *movie_input;
    MOVIE *movie_output;
    iterableFilter filter_func;
    int frame_count, frame_width, frame_height;
    int start,step,end;
    /* variable to check if the movie was saved successfully */
    int code = 1;
    /* flags to keep track of the filter that needs to be applied */
    int filter_flag = 0, rev_flag = 0;
    /* flags to check if all movie parameters exist */
    int flagmoviename = 0,flagframe = 0, flagmoviesize = 0;
    char output_movie_name[100],movie_name[100], ch;
    // loop through each argument for the main function
    for(int n = 0; n < argc; n++)
    {
        // If the user wants to import an image
        if(!strcmp(argv[n], "-i"))
        {
            // If they are at the last argument
            if(n == argc - 1)
            {
                printf("\n\tPlease provide the name of the image you want to import\n");
                return 0;
            }

            input = LoadImage(argv[++n]);

            if(!input)
            {
                printf("\n\tThe image file %s could not be read\n", argv[n]);
                return 0;
            }

            // Let the program know an image has succesfully been imported
            importFlag = 1;
        }

        // If the user wants to import a movie
        /* User inputs movie_name */
        else if(!strcmp(argv[n], "-m"))
        {        
            // to be implemented
            /* if -m is the last parameter */
            if(n == argc - 1)
            {
                 printf("\n\tPlease provide the name of the movie you want to import \n");
                 return 0;
            }

            strcpy(movie_name,argv[++n]);
            flagmoviename =1;

        } 
        // other arguments to be implemented
        /*  User inputs the the size of each movie frame */
        else if(!strcmp(argv[n], "-s"))
        {
            if(n == argc - 1)
            {
                 printf("\n\tMissing argument for the resolution of the frame!\n");
                 return 0;
            }
            sscanf(argv[++n], "%d %c %d", &frame_width, &ch, &frame_height);   
            if(frame_width < 0 || frame_height < 0)
            {
                printf("\n\tPlease provide a positive integral value for movie size\n");
                return 0;
            } 
            flagmoviesize = 1;
        } 
        /* User inputs number of frames */
        else if(!strcmp(argv[n], "-f"))
        {
            if(n == argc - 1)
            {
                 printf("\n\tMissing argument for the number of frames!.\n");
                 return 0;
            }

            sscanf(argv[++n], "%d", &frame_count);

            if(frame_count < 0)
            {
                 printf("\nPlease provide a positive integral value for number of frames\n");
                 return 0;
            }
            flagframe = 1;
        } 
        
        /* User inputs output file name */
        else if(!strcmp(argv[n], "-o"))
        {
            if(n == argc - 1)
            {
                 printf("\n\tMissing argument for output file!.\n");
                 return 0;
            }
            strcpy(output_movie_name, argv[++n]);
        }
       
        /* User inputs start value */
        else if(!strcmp(argv[n], "-start"))
        {
            if(n == argc - 1)
            {
                 printf("\n\tPlease provide the start parameter\n");
                 return 0;
            }
            /* atoi() is a built in function in stdlib.h that converts string to int */
            start = atoi(argv[++n]);

            if(start < 0 || start > 100)
            {
                 printf("\n\tPlease provide the start parameter in range [0,100]\n");
                 return 0;
            }
        }
        /* User inputs end parameter */
        else if(!strcmp(argv[n], "-end"))
        {
            if(n == argc - 1)
            {
                 printf("\n\tPlease provide the end parameter\n");
                 return 0;
            }
            sscanf(argv[++n],"%d",&end);
            if(end < 0 || end > 100)
            {
                 printf("\n\tPlease provide the end parameter in range [0,100] \n");
                 return 0;
            }
        }
        /* User inputs step */
        else if(!strcmp(argv[n], "-step"))
        {
            if(n == argc - 1)
            {
                 printf("\n\tPlease provide the step parameter\n");
                 return 0;
            }

            sscanf(argv[++n],"%d",&step);

            if(step < 0 || step > 100)
            {
                 printf("\n\tPlease provide the step parameter in range [0,100] \n");
                 return 0;
            }
        }
        /* User inputs hue */
        else if(!strcmp(argv[n], "-hue"))
        {
            filter_flag = 1;
          
        }
        else if(!strcmp(argv[n], "-bw"))
        {
            filter_flag = 2;
         
        }
        /* User inputs reverse */
        else if(!strcmp(argv[n], "-reverse"))
        {
            rev_flag = 1;
        }

    } /* end of for loop */

   
    /* Load movie */
    if(importFlag != 1)
    {
        if(flagmoviename == 1 && flagmoviesize == 1 && flagframe == 1)
        {
            movie_input = LoadMovie(movie_name,frame_count, frame_width, frame_height);
        }
        //Let the program know a movie has succesfully been imported
       
        importFlag = 2;
        
    }

    // Load the default image if no argument was specified
    if(!importFlag)
    {
        printf("\nNo -i nor -m for input file to read\n");
        return 0;
    }
    else if(importFlag == 1)/* if the input is an image that was loaded correctly */
    {
        assert(input != NULL);
        if(filter_flag == 1)
        {
            filter_func = &HueRotate;
        }
        else if(filter_flag == 2)
        {
            filter_func = &BlackNWhite;
        }
        movie_output = doIterativeFilter(input,filter_func, start,end,step);
        assert(movie_output != NULL);
        code = SaveMovie(output_movie_name, movie_output);
        if(code == 1)
        {
           printf("\nError! Movie not saved");
        }
        else if(code == 0)
        {
           printf("\nMovie saved successfully!\n");
        }
    }
    else if(importFlag == 2) /* if the input is a movie that was loaded correctly */
    {    
        if(rev_flag == 1)
        {
          assert(movie_input->Frames != NULL);
          ReverseImageList(movie_input->Frames);
          printf("\nOperation Reverse is done!\n");
        }
        movie_output = movie_input;
        code = SaveMovie(output_movie_name, movie_output);
        if(code == 1)
        {
           printf("\nError! Movie not saved\n");
        }
        else if(code == 0)
        {
           printf("\nMovie saved successfully!\n");
        }

    }
    if(code == 0)  /* if a movie was saved successfully */
    {
        DeleteMovie(movie_output);
    }
    return 0;
}

/* EOF */
