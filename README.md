This small widget let's you select and crop rectangular portions of image files.

I wrote a similar widget using Winforms in C# in my previous job. I thought it would be a good example to show that I can code Qt apps in C++.

This application is put together by following examples in Qt Documentation.
 * Image Viewer
 * Scribble
 * Basic Drawing

It is lacking a few features I intend to add.

 - I want to add the ability to zoom on the source image and use scrollbars etc. I did it using basic analytic geometry in my previous widget but I want to use linear transformations this time.
 - I want to add buttons to set min / max size for selection area and locking aspect ratio of the selection area (these were possible in my previous widget).
 - I may add ability to rotate the image / selection area too. It shouldn't be hard if I base everything on transformations.
 - I won't do this one probably but I could add selecting and cropping in other shapes instead of just a rectangle (like circles or stars etc.) I used SVGs in Qt before, I can add ability to load your own simple crop shapes.
 - I won't add 3Dish transformations since I don't want to figure out UI controls for that, I'd rather use Paint3D in Windows :)
 
