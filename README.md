![Screenshot](https://i.imgur.com/r0pdRBz.png)

![CircleCI](https://img.shields.io/circleci/build/github/hebriel/wrench-engine/master?logo=CircleCI)
![Codacy grade](https://img.shields.io/codacy/grade/d804879fda2d4836adef825b03648e8e?logo=Codacy)
![GitHub](https://img.shields.io/github/license/hebriel/wrench-engine?logo=GNU)

| OS - Compiler     | Support                 | CI Coverage        |
|-------------------|-------------------------|--------------------|
| GNU/Linux - GCC   | :white_check_mark:      | :white_check_mark: |
| GNU/Linux - Clang | :white_check_mark:      | :white_check_mark: |
| macOS - Clang     | :white_check_mark:      | :x:                |
| Windows - MSVC    | :ballot_box_with_check: | :x:                |
| Windows - MinGW   | :x:                     | :x:                |

:white_check_mark: : Yes

:x: : No

:ballot_box_with_check: : Experimental

The Wrench Engine is a game engine made with C++17 mostly present to test out my new programming skills. I hope it will be usable some day.

Wrench is currently only developed by me on macOS and GNU/Linux and only supports OpenGL. It is inspired by :

- [Hazel](https://github.com/TheCherno/Hazel)
- My old and rusty [achgabat](https://github.com/hebriel/achgabat) project (more of an ancestor of some sort)
- Part of the [SFML](https://github.com/SFML/SFML) API (it is **NOT** a dependency!)

Dependencies currently are :
- OpenGL
- [GLM](https://glm.g-truc.net/0.9.9/index.html)
- [SDL2](https://www.libsdl.org/download-2.0.php)
- [GLEW](http://glew.sourceforge.net/) ([GLAD](https://glad.dav1d.de/) will be an alternative in the future)
- A compiler that supports the C++17 features
