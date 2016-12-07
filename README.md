##Head
isoChar - isolation of characters
Kevin Gentile
12/07/2016

##Description
The purpouse of this program is to read in an ASCII .pbm image file, trace items
of interest, and encapsulate them inside a bounding box. The program is given in
a sequential version and a threaded version. The sequential version loads an
image, and traces through until it finds a black seed pixel. The seed pixel is
then handed off to a boundary trace function that collects all bounding pixels
in a contour, creates a box entity to encapsulate the contour (with padding to
avoid writing on a contour). The bounding boxes are then added to the image by
drawing along the edge of the box entity. The resulting image is then written to
a file with the .new suffix. The threaded version of this program is introduced in
the trace file but does not significantly improve program execution. The threadded 
version of this program can be improved by creating a thread to check if a given 
pixel is within a bounding box as this operation encompasses the bulk of execution time.

##Before
![Screenshot: Before](alph.jpg?raw=true "Before")
##After
![Screenshot: After](alph_out.jpg?raw=true "After")
