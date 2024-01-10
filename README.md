# RayCasting 3D Simulation

![RayCasting Demo](raycastDemo.gif)

A C++ project that utilizes raycasting to simulate a 3D-style environment from a 2D image, inspired by retro games like Wolfenstein 3d, utilizing the SFML library to handle graphics and input.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Dependencies](#dependencies)
- [Controls](#controls)

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

## Dependencies

- C++17 or later.
- CMake version 3.16 or later
- SFML 2.6
- ImGui v1.89

## Controls

WASD to for directional movement. Mouse movement rotates player character horizontally and vertically. Press ESC to free mouse from window.
