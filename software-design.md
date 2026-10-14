---
title: Software Design and Engineering
---

# Software Design and Engineering: CS 330 3D Desk Scene

[Back to Home](./)

![CS 330 3D desk scene running](CS%20330%20code/scene.png)

## Code

### Key Change: Before and After

**Before:** RenderScene created and drew every object by hand, one block per object.

```cpp
Desk myDesk;
myDesk.Draw(this);

CoffeeMug myMug;
myMug.Draw(this);

Monitor myMonitor;
myMonitor.Draw(this);
// ...one block for every object
```

**After:** every object inherits from SceneObject, so one loop draws them all.

```cpp
for (const auto& sceneObject : m_sceneObjects) {
    sceneObject->Draw(this);
}
```

### Enhanced Files

- [SceneObject.h](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS%20330%20code/Enhanced/SceneObject.h) - Abstract base class every object inherits from
- [SceneManager.cpp](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS%20330%20code/Enhanced/SceneManager.cpp) - Creates the objects once and draws them in one loop
- [SceneManager.h](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS%20330%20code/Enhanced/SceneManager.h) - Declares the class that loads textures, sets up lights, and draws the scene
- [CoffeeMug.h](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS%20330%20code/Enhanced/CoffeeMug.h) - Declares the coffee mug object
- [Desk.h](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS%20330%20code/Enhanced/Desk.h) - Declares the desk object
- [Laptop.h](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS%20330%20code/Enhanced/Laptop.h) - Declares the laptop object
- [Monitor.h](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS%20330%20code/Enhanced/Monitor.h) - Declares the monitor object
- [Mouse.h](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS%20330%20code/Enhanced/Mouse.h) - Declares the mouse object
- [Notebook.h](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS%20330%20code/Enhanced/Notebook.h) - Declares the notebook object
- [MousePad.h](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS%20330%20code/Enhanced/MousePad.h) - Declares the mouse pad object
- [MousePad.cpp](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS%20330%20code/Enhanced/MousePad.cpp) - Draws the mouse pad under the mouse using a box mesh and a solid color

### Original Files

- [Original code folder](https://github.com/FreddyCase13/FreddyCase13.github.io/tree/main/CS%20330%20code/Original) - The CS 330 version before the enhancement

### Narrative

- [Download narrative (Word)](https://github.com/FreddyCase13/FreddyCase13.github.io/blob/main/CS%20330%20code/CS499_Freddy_Case_Software_Design_Narrative.docx)

## Artifact Description

The artifact for this category is my 3D desk scene from CS 330: Computational Graphics and Visualization course. This was built in early 2026 and submitted at the end of the February term. This is an OpenGL rendered scene made up of six objects, a coffee mug, a desk, a laptop, a monitor, a mouse, and a notebook. Each object has its own cpp class as well as its own header class. The entire codebase was built on an instructor provided shader and rendering framework which handles the lower-level graphics set up. I then added my own objects, textures, materials and created the desk scene throughout the course.

## Inclusion Justification

I chose this artifact for the software design and engineering category because the problem in it was an architectural issue. Before the enhancement, my SceneManager class was loading textures, defining materials, setting up lighting, and rendering. Each called a separate hardcoded function for each of the six objects by name. Adding a new object to the scene would mean I would have to edit SceneManager each time.

The enhancement that showcases my software development skills is the SceneObject base class that I added. This is an abstract class that has a virtual Draw() function that all six object classes inherit from. Now there is a list of SceneObjects that calls Draw() on each object within SceneManager. I also switched the list to use unique pointers instead of raw pointers so that each object will be cleaned up automatically instead of relying on manual memory management. Doing so also fixed an inefficiency where the original code kept recreating a new instance of each object every single frame instead of once at startup.

To prove the design worked, I also added a mouse pad object to the scene using the new pattern. It required writing a new cpp class, a new header file, and one new line in the object list within SceneManager. I did not have to touch the RenderScene function within SceneManager at all, which was the desired enhancement to this artifact.

## Course Outcomes

Originally in my Module One plan, I mapped outcomes three and four to this enhancement. However, for this artifact's enhancement, I feel I met outcome four, which is that I used a well-founded, industry standard object-oriented pattern design. This was done through creating a shared interface through polymorphism instead of using repeated code. I demonstrated that it delivers real value through extending the scene without modifying the existing code. For outcome three, it is more directed towards pertaining to data structures and algorithms. Therefore, I am updating my outcome-coverage plan so that I am focusing more on completing outcome three when I am completing my algorithms enhancement.

## Reflection on the Process

For this code enhancement, the most difficult part was getting the environment set back up. My original, finished project file was zipped and submitted for the class's final project. Therefore, the project file ended up missing files it depended on. I had to spend a little time making sure the file paths were correct after extracting the zip file back to its original state. Once that was completed, I went to run the project, however an important dll file was missing and the scene would not build. I had to find a copy of that dll and place it in the project's debug folder for it to work. Once I fixed that, the project compiled and the scene rendered.

The most useful thing that I learned while adding the new mouse pad object was that OpenGL’s rendering calls are stateful. In the Mousepad.cpp file, I initially drew the object’s shape before setting its texture and material. Since these functions are sequential state changes, the pad rendered with leftover state from the object drawn before it, which made the mousepad barely visible. Once the ordering of the functions was fixed, the mousepad’s color changed and was visible in the scene.

The feedback that I received from my instructor confirmed that introducing the SceneObject base class addressed a software design problem instead of only adding in new objects to the scene. The feedback pointed out that the enhanced design improved the maintainability, extensibility, and organization of the code. There were no changes requested from my instructor, which confirmed that my approach was sound. I also went back to the code before uploading the published version to add code headers to every file so that other developers could see what each file does quickly and see the added enhancements.
