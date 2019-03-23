# ImageViewer
Image~Viewer and Editor.....

		
![image](https://user-images.githubusercontent.com/24197201/52168580-e472ac00-2753-11e9-8429-034a688bb34e.png)



# Image Remix... a very short introduction..

![preset](https://user-images.githubusercontent.com/24197201/51024206-f6c45480-15b0-11e9-9e8f-78593c6384e4.gif)



# Filters..

<b>Tesselator</b> <i>new</i>

Apply triangular tesselation producing pixilate effect..Each kernel visits image,and breakdown into triangular implementation...

![tesselator](https://user-images.githubusercontent.com/24197201/51022875-8b2cb800-15ad-11e9-9d26-f3e61da4a12d.gif)

<b>Image Blur</b>
  
  This applies gaussian blur over image.We are using 5x5 kernel to convolve through image..
  
  ![blur](https://user-images.githubusercontent.com/24197201/50737271-2f4de200-11ef-11e9-878d-65a2934b88ac.gif)

  <b>Image Sharping</b>
  
  This filter apply edge enhancement over image,The algorithm is specially focused on <i>laplacian substraction</i> for this process...
  
  ![sharpness](https://user-images.githubusercontent.com/24197201/50737229-d1b99580-11ee-11e9-8a5f-68632df86b18.gif)
  
  <b>Retro</b>
  
This taste something like this..
![retro](https://user-images.githubusercontent.com/24197201/50737398-d1ba9500-11f0-11e9-890e-e9349453aa81.gif)

<b>Artify</b>

User is allowed to select  size of kernel which is applied over image,Size of kernel decide effect over image
Here is example showing filter artify...

![artify](https://user-images.githubusercontent.com/24197201/50737304-a84d3980-11ef-11e9-8cd9-496190b58ca0.gif)

This filter is specially for image containing face.For best result,face must be flooded with light.Poor lighting over face will ruin the effect.

# utility
<b>Image histogram and Face-Detection</b>

I also provide a saperate metric window to calculate and display histogram of R,G and B channels of image saperately..
It gets updated whenever we apply filter in real-time..User can see the change occured in saperate channels of image.
Also we have added a infobar to show number of face detected in image...right now it is not so good in performance...
![image](https://user-images.githubusercontent.com/24197201/54867836-2495f880-4dad-11e9-930c-56c545b7fbc8.png)


# gallery
<b>1.The Sherlock</b>


![image](https://user-images.githubusercontent.com/24197201/52168774-55b35e80-2756-11e9-8e3e-6e2788e153bd.png)


![image](https://user-images.githubusercontent.com/24197201/52168759-269ced00-2756-11e9-817a-64e74810b465.png)


# resource
<b>We are using opengl,opencv,and imgui for developement of this application..
  System must setup with opencv and opengl</b>

![image](https://user-images.githubusercontent.com/24197201/50045507-371cd980-00bc-11e9-9088-5da36b9717d2.png)

![image](https://user-images.githubusercontent.com/24197201/50045524-89f69100-00bc-11e9-86d9-f93be2bdce75.png)

![image](https://user-images.githubusercontent.com/24197201/50045604-c676bc80-00bd-11e9-8394-a34071ef94a7.png)
