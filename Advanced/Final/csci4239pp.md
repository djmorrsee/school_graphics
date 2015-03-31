# 4239 Advanced Graphics Project Proposal
## Daniel Morrissey

<hr>

### Background

No other industry is pushing real time graphics programming faster than video games. Vulkan itself, the next generation of graphics API coming soon out of Khronos, has contributions from some very large names in the gaming world, including Epic Games, Valve, Oculus VR, Blizzard, EA and others. [1]

My own background has been in gaming, playing as a child and eventually using engines such as Unity3D and most recently the Unreal Engine to create and release games, prodominantly for mobile devices. The double edged sword of these engines was that it handled almost all aspects of rendering (shaders can be written in HLSL in Unity, and Unreal is just pretty as it is).

### Proposal

I plan to implement an (extremely limited) game engine, and more specifically a rendering engine to couple to a game engine. My goal is to create a limited Minecraft [2] clone. Minecraft is a game where the player is put in a limitless and procedural world made entirely of removable and placeable cubes. In early versions of the game, this was the extent of the capabilities.

The first leg of my implementation will be the rendering engine, and will be where most of the work will lay. While drawing a few cubes is simple, the impressiveness of the game lays in just how many cubes can be rendered at once (upwards of 10k individual cube objects, all textured and lit). I want to come up with an efficient method of handling and passing data back and forth from the game and rendering engines.

Once basic rendering of a cube world is done, I wish to add interactivity, which will consist of motion, as well as the ability to destroy or place cubes.


### Details

There are a few specific ideas I want to explore:

- Efficient Rendering
  - I wish to recreate the ability to display that large number of cubes. The game represents them as individual, however the rendering engine clearly cannot deal with them as such. 
  - Chunks
    - The initial implementation idea is to handle the world in chunks of cubes, loading only chunks in a radius of the viewport.

- Texturing
  - Texturing at a massive scale will likely require an indexed palette instead of a texture buffer per object.

- Interactivity
  - I don't want to spend a lot of my time creating game "features." Instead, I will implement a similar minecraft mechanic of adding and removing blocks. This will force my focus to be on the formation and passing of data from the engine to the renderer.

- Decoupling
  - In the scheme of the engine that I wish to create, I wish to decouple the different pieces. While I will only spend minimal time on each piece other than the renderer, I wish to have a physics module, a UI module, etc. 

Each of these pieces are meant to strengthen my understanding of the game engines that I plan on using in my career. I hope to use this project to explore those areas which I wouldn't otherwise see. 

### Sources:
1. https://www.khronos.org/vulkan
2. https://minecraft.net/