Assignment 5: MovieLab
Ayesha Parvez
ID: 35998893

This program taken an image input, applies hiue or black and white filter to it and saves it as a
movie. It also accepts a movie as an input and apllies the reverse filter if the user selects it 
and saves the result as another movie. A movie is an object of type MOVIE that consists of Frames
which is an element of type ILIST. Each object of type ILIST connsists of length, an integral 
value that indicates the number of entries in the list. It has two elemenst of type IENTRY. These
are First and Last. They represent the first and last entries in the list respectively. Each entry
consists of 2 elements of type IENTRY, an element of type IMAGE to store RGB Image and an element
of type YUVIMAGE to store a YUV image.ImageList.c consists of definitions of functions that act on 
lists and entries, such as creating and deleteing lists and entries and appending RGB and YUV 
images to lists.The append functions accept an image (RGB or YUV) that needs to be appended to a
list which is also taken as an argument. The function creates an entry to store the image and
appends it to the end of the list. Similarly, Movie.c consists of definitions of functions that
act on MOVIE objects, such as creating and deleting movies and converting RGB movies to YUV and
vice-versa. In the conversion functions, I have used the pixels of the image that exists in the 
movie to obtain the pixels of the image in the other format. I have also defined and used a 
function called clip() to check the range of the pixels and assign 0 if the pixel is negative or
255 if the pixel exceeds 255. In the doIterativeFilter() function in IterativeFilter.c, I have
used the parameters passed to the function to apply the selected filter to the image. The address
to the functions BlackNWhite() or HueRotate() is stored in a function pointer of type 
iterableFilter. I have used start,change and end parameters to find the number of frames and the
percent application of the filter. I have then applied the filter to a copy of the original image
in a for loop. In every iteration of the loop I have passed a copy of the image and the percent
application to filter(). Percent application is the current value of the i, the iterating variable
which increments by change if start < end or decrements by change if start > end. In MovieLab.c
I read the arguments passed to main() and compare each argument with -i,-m,-o,-s,-f,-start,-step,
-end,-hue,-bw and -reverse. I store the value following each argument (except last 3, because
they don't need any values)and set flags to denote that each value has been obtained. Finally,
depending on whether a movie was loaded or an image was loaded, I create a new movie from the 
input. 
