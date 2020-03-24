# K-Buffer and translucency effect

OpenGL implementation of Andreas A. Vasilakis and Ioannis Fudos paper : __K<sup>+</sup>-buffer: Fragment Synchronized k-buffer__ and translucency effect using this K-Buffer.

Link to paper : https://dl.acm.org/doi/10.1145/2556700.2556702

## Requirements

- Visual Studio 2019
- OpenGL 4.5

I used my little engine for this implementation, I hope the code is explicit enough to be easily moved to another framework.

## Build

Open the solution __KBuffer.sln__ and everything should be ready to go.

## Controls

When the viewport is focused (just click inside the viewport window) you can rotate the camera by holding the __shift__ key and draging the mouse with the __left button__ down.

You can zoom by holding the __shift__ key and draging verticaly the mouse with the __right button__ down. You can also use the __mouse wheel__ to zoom.

You can change the orbit center of the camera by selecting an object in the __Outliner__ list and pressing the __F__ key.

## Settings

You can select an object in the __Outliner__ list, when an object is selected its settings appear in the __Details__ window.

For example, you can select the *Dragon* and change the translucency parameters.

You can also select the *K-Buffer* in the __Resources__ list to change the *K* value and its other parameters.

For the drag float boxes, you can hold the __alt__ key to change the values slower, it can be useful especialy for the __Max Translucency Thickness__ parameter.

## Scene

The scene should be composed of one yellow opaque plane, a transparent purple shader ball and a translucent green dragon.

![Expected result of the sample scene.](/Data/SampleScene.png)

## Implementation details

You can find the detailed explanation [here](http://www.remimaigne.com/personal-projects/k-buffer-and-translucency).
