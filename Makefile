#######################################################################
# Homework Assignment 5, for EECS 22, Winter 2020
#
#
# Makefile: Makefile for HW 5
#
#######################################################################

# Variables
FLAGS = -ansi -std=c99 -Wall -g

# Default target
all: MovieLab

######################### Generate object files #######################
# Target for FileIO.o
FileIO.o: FileIO.h FileIO.c Image.h
	gcc -c FileIO.c -o FileIO.o $(FLAGS)
# Target for DIPs.o
DIPs.o: DIPs.h DIPs.c Image.h Constants.h FileIO.h
	gcc -c DIPs.c -o DIPs.o $(FLAGS) -lm
# Target for Image.o
Image.o: Image.h Image.c
	gcc -c Image.c -o Image.o $(FLAGS)
	
# Target for other object files

# Target for Movie
Movie.o: Movie.h Movie.c ImageList.h Image.h FileIO.h FileIO.c
	gcc -c Movie.c -o Movie.o

# Target for ImageList.o
ImageList.o: ImageList.h ImageList.c Image.h
	gcc -c ImageList.c -o ImageList.o $(FLAGS)  

# Target for MovieIO.o
MovieIO.o: MovieIO.h MovieIO.c Movie.h Image.h FileIO.h Constants.h
	gcc -c MovieIO.c -o MovieIO.o
# Target for IterativeFilter.o
IterativeFilter.o: IterativeFilter.h IterativeFilter.c ImageList.h Movie.h Image.h 
	gcc -c IterativeFilter.c -o IterativeFilter.o

# Target for MovieLab.o
MovieLab.o: MovieLab.c FileIO.h DIPs.h Movie.h Constants.h Image.h MovieIO.h IterativeFilter.h ImageList.h
	gcc -c MovieLab.c -o MovieLab.o $(FLAGS)
         
######################### Generate the executable #####################
# Target for MovieLab
MovieLab: MovieLab.o FileIO.o DIPs.o Movie.o Image.o IterativeFilter.o MovieIO.o ImageList.o
	gcc $(FLAGS) MovieLab.o FileIO.o DIPs.o Movie.o Image.o IterativeFilter.o ImageList.o MovieIO.o -o MovieLab -lm
 

###############################  others  ##############################
# Target for clean - extend it
clean:  
	rm -f *.o *.yuv
	rm MovieLab
#	rm hue0.yuv bw.yuv
