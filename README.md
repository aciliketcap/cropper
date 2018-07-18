This small application let's you select and crop rectangular portions of image files.

I wrote a similar application using Winforms in C# in my previous job. I thought it would be a good example to show that I can code Qt apps in C++.

This application is put together by following examples in Qt Documentation.
 * Image Viewer
 * Scribble
 * Basic Drawing

I also read how event system and layout calculations work in detail.

The next feature I want to add is the ability to zoom in and out on the source image. I did it using basic analytic geometry in Winforms but I want to use linear transformations this time.

Other than that I may add following abilities for selection rectangle:
 - Set minimum / maximum size 
 - Lock aspect ratio
 - Rotation
 - Stepping one pixel at a time on source image when zoomed in

I want to make the CropCanvas and ARPLabel classes separate QWidgets which you can use in other projects too. If I do that I can port the project to QML.

CropCanvas gives you a canvas in which you can select and move out rectangular regions of images. It crops exactly what you see inside the selection rectangle. It also prevents you from moving the selection rectangle outside the source image.

ARPLabel (Aspect Ratio Preserving Label) is a QLabel which shows a QPixmap image. However it preserves the aspect ratio of the image when it is scaled down and centers the image horizontally or vertically depending on the shape of the conatiner. It will center the image if the container is bigger than the image.

I want to upload a short video on YouTube highlighting the features of these widgets.
