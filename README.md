# miniRT

## Introduction

Welcome to miniRT, a C-based raytracer designed as part of the 42 curriculum, offering an introduction to the fascinating world of raytracing. Through miniRT, you'll not only explore how light interacts with objects in a virtual scene but also dive into the challenge of translating physical laws into code.
To develop this project, We follow TTD (Test-driven development) approach, using Criterion for the unit testing. An amazing source on raytracing that helped us a lot is [The Ray Tracer Challenge: a test-driven guide to your first 3D Renderer](http://raytracerchallenge.com/)

### About minTR

miniRT brings to life essential principles of raytracing, allowing users to create compelling scenes with simple geometric forms and adjustable lighting. From ambient to specular lighting, reflections, and refractions, miniRT’s core features lay the groundwork for generating images that capture realistic optical effect.

## How to use it

Only supported and tested on macOS and Linux.

For `Linux` it is necessary to install the GLFW library first:

```
sudo apt-get update && \
sudo apt-get install libglfw3 && \
sudo apt-get install libglfw3-dev
```

<b>Compile and run miniRT in 3 simple steps:</b>

1. `git clone --depth 1 https://github.com/SebasNadu/42_miniRT miniRT`
2. `cd miniRT && make`
3. `./miniRT scenes/bonus/04_skybox2.rt`

#### How to configure your own scenes

Your can read the scene [readme](./scenes/readme.rt) and use the [template](./scenes/template.rt) scene as reference. Have fun!.

### Controls

| **Action**                | **Keys / Controls**                | **Description**                                                                                                                                                |
| ------------------------- | ---------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Exit Application**      | `ESC` or `Q`                       | Exits the application, freeing resources and closing the window.                                                                                               |
| **Move Camera Right**     | `RIGHT` or `D`                     | Moves the camera to the right.                                                                                                                                 |
| **Move Camera Left**      | `LEFT` or `A`                      | Moves the camera to the left.                                                                                                                                  |
| **Move Camera Forward**   | `UP` or `W`                        | Moves the camera forward.                                                                                                                                      |
| **Move Camera Backward**  | `DOWN` or `S`                      | Moves the camera backward.                                                                                                                                     |
| **Rotate Right**          | `SHIFT` + `RIGHT` or `SHIFT` + `D` | Rotates the camera along the Z-axis to the right.                                                                                                              |
| **Rotate Left**           | `SHIFT` + `LEFT` or `SHIFT` + `A`  | Rotates the camera along the Z-axis to the left.                                                                                                               |
| **Move Camera Up**        | `SHIFT` + `UP` or `SHIFT` + `W`    | Moves the camera upward.                                                                                                                                       |
| **Move Camera Down**      | `SHIFT` + `DOWN` or `SHIFT` + `S`  | Moves the camera downward.                                                                                                                                     |
| **Rotate Camera (Mouse)** | Left Mouse Button (hold and drag)  | Rotates the camera in 3D space by dragging the mouse while holding the left button, the scene is render only on the realese. Cursor is hidden during rotation. |
| **Zoom In / Out**         | Mouse Scroll                       | Adjusts the camera’s focal length to zoom in or out.                                                                                                           |
| **Redraw Scene**          | `R` or `SPACE`                     | Refreshes and redraws the scene.                                                                                                                               |

## Samples

## Features Checklist

- [x] **Ray Casting Basics**

  - [x] Implement basic ray casting for rendering objects in a scene
  - [x] Calculate intersections of rays with basic shapes (spheres, planes)

- [x] **Light and Shadow**

  - [x] Implement a basic light source (point light)
  - [x] Calculate shadows (shadow rays to detect if an object is in shadow)
  - [x] Support multiple light sources

- [x] **Materials and Shading**

  - [x] Diffuse shading (Lambertian reflection)
  - [x] Specular highlights (Phong reflection model)
  - [x] Ambient light support
  - [x] Reflective materials

- [x] **Camera and Viewing**

  - [x] Define a camera with adjustable position and field of view
  - [x] Implement view transformations (translation, rotation)
  - [x] Perspective projection for 3D rendering

- [x] **Complex Shapes and Transformations**

  - [x] Support transformation matrices for objects (scaling, rotation, translation)
  - [x] Support for more complex shapes (cylinders, cones, cubes)
  - [x] Nested transformations for complex object positioning

- [x] **Reflections and Transparency**

  - [x] Reflective surfaces (mirror-like reflections)
  - [x] Refractive materials (Snell’s law for transparency and refraction)
  - [x] Fresnel effect for realistic blending of reflection and refraction
  - [x] Total internal reflection

- [x] **Anti-Aliasing**

  - [x] Implement super-sampling or jittered sampling for smoother edges
  - [x] Option to enable or disable anti-aliasing

- [x] **Texturing and Patterns**

  - [x] Apply textures or patterns (checkerboard, stripes, etc.) to surfaces
  - [x] Support UV mapping for complex object texturing
  - [x] Bump mapping for surface texture detail

- [x] **Depth of Field**

  - [x] Implement camera effects to simulate depth of field
  - [x] Use focal length and aperture size for realistic focus effects

- [ ] **Advanced Lighting Techniques**

  - [x] Implement soft shadows for realistic penumbra effects
  - [ ] Global illumination techniques (like ambient occlusion)
  - [x] Area lights for more natural light spread
  - [ ] Caustics for light-focused effects through transparent materials

- [ ] **Multi-Threading and Optimization**

  - [ ] Optimize rendering time with multi-threading
  - [x] BVH (Bounding Volume Hierarchy) or other acceleration structures
  - [x] Implement adaptive sampling for performance improvements

- [ ] **Post-Processing Effects**

  - [ ] Add support for bloom effects (light glow)
  - [ ] Motion blur for moving objects
  - [ ] Color grading and tone mapping
  - [ ] Gamma correction for realistic lighting

- [x] **Scene Composition**
  - [x] Support for importing complex scene files (OBJ, STL, etc.)
  - [x] Grouping and hierarchies of objects for scene management

---

## Authors

- [Sebastion Navarro](https://github.com/SebasNadu/) ([johnavar](https://profile.intra.42.fr/users/johnavar))
- [Piranaut](https://github.com/Piranaut) ([ppour-ba](https://profile.intra.42.fr/users/ppour-ba))
