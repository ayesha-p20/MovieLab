/*********************************************************************/
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

/* Create a new image entry */
IENTRY *CreateImageEntry(void)
{
 IENTRY *ientry = malloc(sizeof(IENTRY));
 ientry -> List = NULL;
 ientry -> Next = NULL;
 ientry -> Prev = NULL;
 ientry -> RGBImage = NULL;   
 ientry -> YUVImage = NULL;
 return (ientry); 
}

/* Delete image entry (and image objects)*/
void DeleteImageEntry(IENTRY *entry)
{
 assert(entry != NULL);
 /* deleting image pointers */
 if(entry -> RGBImage != NULL)
    DeleteImage(entry -> RGBImage);
 if(entry -> YUVImage != NULL)
    DeleteYUVImage(entry -> YUVImage);
 free(entry);
// entry = NULL;  
}

/* Create a new image list */
ILIST *CreateImageList(void)
{
 ILIST *list = malloc(sizeof(ILIST));   /* create entry ?*/
 list -> length = 0;
 list -> First = NULL;
 list -> Last = NULL;
 return(list);
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
 assert(list != NULL);
 IENTRY *ientry,*ptr;
 ientry = list -> First;
 while(ientry != NULL)
 {
   ptr = ientry -> Next;
   DeleteImageEntry(ientry);
   ientry = ptr;
 }
 list -> length = 0;
 free(list);
 
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
 assert(RGBimage != NULL);
 IENTRY *ientry, *new_entry;
 /* new_entry contains the new RGBImage */
 new_entry = CreateImageEntry(); 
 new_entry -> RGBImage = RGBimage;
 if(list -> length > 0)
 {
     /* ientry is the current last image entry in list */
     ientry = list -> Last; 
     /* linking current last entry(ientry) and new entry (new_entry) that contains RGBImage */
     ientry -> Next = new_entry;
     new_entry -> Prev = ientry;
     new_entry -> List = list;
 }
 /* if the list is empty */
 else if(list -> length == 0)
 {
     /* the new_entry is the first and last entry in the list */
     list -> First = new_entry;
     new_entry -> Prev = NULL;
     new_entry -> List = list;
 }
 /* new_entry is now the last image entry */
 new_entry -> Next = NULL;
 list -> Last = new_entry;
 list -> length += 1; 
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage)
{
 assert(YUVimage != NULL);
 IENTRY *ientry, *new_entry;
 /* new_entry contains the new YUVImage */
 new_entry = CreateImageEntry(); 
 new_entry -> YUVImage = YUVimage;
 if(list -> length > 0)
 {
     /* ientry is the current last image entry in list */
     ientry = list -> Last; 
     /* linking current last entry(ientry) and new entry (new_entry) that contains RGBImage */
     assert(ientry != NULL);
     ientry -> Next = new_entry;
     new_entry -> Prev = ientry;
 }
 /* if the list is empty */
 else if(list -> length == 0)
 {
     /* the new_entry is the first and last entry in the list */
     list -> First = new_entry;
     new_entry -> Prev = NULL;
 }
 /* new_entry is now the last image entry */
 new_entry -> Next = NULL;
 list -> Last = new_entry;
 new_entry -> List = list;
 list->length += 1;
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
 assert(list != NULL);
 IENTRY *curr_entry, *ptr;
 ptr = list -> First;
 while(ptr)
 {
 /* swapping next and prev pointers */
  curr_entry = ptr -> Next;
  ptr -> Next = ptr -> Prev;
  ptr -> Prev = curr_entry;
  ptr = curr_entry;
 }
 /* swapping first andlast pointers */
 curr_entry = list -> First;
 list -> First = list -> Last;
 list -> Last = curr_entry;
}
/* EOF */
