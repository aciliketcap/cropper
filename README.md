This small widget let's you select and crop rectangular portions of image files.

I wrote a similar widget using Winforms in C# in my previous job. I thought it would be a good example to show that I can code Qt apps in C++.

This application is put together by following examples in Qt Documentation.
 * Image Viewer
 * Scribble
 * Basic Drawing

I also read how event system and layout calculations work.

The next feature I want to add is the ability to zoom in and out on the source image. I did it using basic analytic geometry in Winforms but I want to use linear transformations this time.

Other than that I may add following abilities for selection rectangle:
 - Set minimum / maximum size 
 - Lock aspect ratio
 - Rotation

I want to make the CropCanvas and ARPLabel classes separate QWidgets which you can use in other projects too. If I do that I can port the project to QML.

Finally I want to upload a short video on YouTube highlighting key features.
