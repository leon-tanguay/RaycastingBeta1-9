# RayCasting 3D Simulation

![RayCasting Demo](raycastDemo.gif)

A C++ project that utilizes raycasting to simulate a 3D-style environment from a 2D image, inspired by retro games like Wolfenstein 3d, utilizing the SFML library to handle graphics and input.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Demo](#demo)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [Contributing](#contributing)
- [License](#license)

## Introduction

Inspired by videos I watched on the math behind raycasting, I decided to try and implement the system myself from scratch using C++. I also decided to do this project to help develop my skills in CMake, GTest, and modern C++17 techniques.

## Features
- Converts image to 2d map to be rendered in 3d
- First-person player controller using WASD keys and mouse
- Hue Shifting Algorithm implemented using a simulation of a color cube rotation
- RayCasting simulation using physics, made more efficient by a grid-based system
- 3D-style environment with a simple shader system
- SFML integration
- Custom Vector template class

## Demo

Include a link to a demo video or showcase screenshots to give users a quick overview of what your project looks like in action.

![RayCasting Demo](link-to-demo-gif-or-screenshot.gif)

## Requirements

- C++17 or later.
- CMake version 3.16 or later
- SFML 2.6
- ImGui v1.89

## Installation

CMake handles

## Usage

Explain how users can use your application. Include any command-line arguments, configuration files, or other settings that users might need to customize.

## Controls

WASD to for directional movement. Mouse movement rotates player character horizontally and vertically. Press ESC to free mouse from window.
## Contributing

Explain how others can contribute to your project. Include guidelines for submitting issues, feature requests, and pull requests. Mention any coding standards or conventions you follow.

## License

Specify the license under which your project is distributed. Include a link to the full license text.
