# **MovieLab**
Movie Lab was an assignment that I completed for a course at college. This program accepts an image or a movie as input, applies a filter selected by the user to the input and displays the output in the form of another movie. I used doubly linked lists and structures to create this project. The program accepts input from command line in a linux terminal. Debugging was done using gdb and Valgrind. 

## Built With
This program has been created in C and runs on the linux terminal. Additionally, it requires Xming to play the output movie.

## Usage
### With Image Input:
The user needs to enter the name of the image file, its size (widthxheight), number of frames (determined by start, step, end), the filter - hue (hue) or bw (black and white) and the name of the output file. The output movie has frames from *start* value to *end* value. Each frame is the original image with a certain percent of the selected filter applied to it. This percent is *step* percent of the amount of *start*. The input arguments can be passed in any order. 

The following guide explains which arguments need to be passed if inout is an image:-

-i     : Indicates input is an image. Must be followed by a string argument.<br/>
-o     : Indicates argument following it is name of output movie

-start : Indicates percent of filter applied to first frame. Must be followed by integer 

-end   : Used to calculate number of frames in output movie. Must be followed by an integer

-step  : Used to calculate percent increase in filter application for each successive frame. Must be followed by an integer.

hue    : Inducates 'hue' filter needs to be applied to each frame. 

bw     : Indicates 'bw' filter needs to be applied to each frame.

#### Note: Either *hue* or *bw* can be selected, but not both.

Example 1:

