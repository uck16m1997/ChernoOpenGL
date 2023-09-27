<h1> ComputerGraphics / OpenGL Concepts </h1>

<h4> Vertex Buffer: </h4> 
An array of bytes of vertices on GPU VRAM. </br>

<h4> Draw Call: </h4> 
Read data from VRAM and draw it on the screen. </br>

<h4> Shader: </h4> 
A program/code that runs on the GPU. </br>

<h4> Vertex: </h4> 
A point on your geometry that can contain attributes such as position, texture coordinates, normals, colors ... </br>

<h4> Vertex Shader: </h4> 
Vertex Shader gets called for each vertex we try to render. Used for setting up/modifying positions of vertices and passing vertex attributes to the next stage (Fragment/Pixel Shader). </br>

<h4> Fragment/Pixel Shader: </h4> 
Fragment Shader runs once for each pixel that needs to be rasterized(drawn on screen) between the vertices and determines color for that pixel.  </br>

<h3> Vertex Shader vs Fragment Shader </h3> 
From an optimization perspective FragmentShader will likely be called more often then Vertex Shader as there will be more pixels than vertices surrounding. Programmers should be more mindful about about keeping Fragment Shader efficient and moving calculations to vertex shader if possible and pass data down the pipeline.
