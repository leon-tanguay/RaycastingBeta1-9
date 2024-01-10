# RayCasting 3D Simulation

![RayCasting Demo](raycastDemo.gif)

A C++ project that utilizes raycasting to simulate a 3D-style environment from a 2D image, inspired by retro games like Wolfenstein 3d, utilizing the SFML library to handle graphics and input.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Dependencies](#dependencies)
- [Controls](#controls)
- [Improvements](#improvements)

## Introduction

Inspired by videos I watched on the math behind raycasting, I decided to try and implement the system myself from scratch using C++. I also decided to do this project to help develop my skills in CMake, GTest, and modern C++17 techniques. The math behind raycasting can be found here: [https://www.youtube.com/watch?v=NbSee-XM7WA](https://youtu.be/NbSee-XM7WA?si=BZmvR1uzr4bWQ8FX)

## Features
- Converts image to 2d map to be rendered in 3d
- First-person player controller using WASD keys and mouse
- Hue Shifting Algorithm implemented using a simulation of a color cube rotation
- RayCasting simulation using physics, made more efficient by a grid-based system
- Player collision detection
- 3D-style environment with a simple shader system
- SFML integration
- Custom Vector template class

## Dependencies

- C++17 or later.
- CMake version 3.16 or later
- SFML 2.6
- ImGui v1.89

## Controls

WASD to for directional movement. Mouse movement rotates player character horizontally and vertically. Press ESC to free mouse from window.

## Improvements

I hope to add more player movement options such as jumping in the future to help immerse the player in the world, as well as adding support for textured terrain and a more advanced lighting system. Prior to these features, I want to ensure that the code is as clean as possible, and manage the amount of required dependencies
