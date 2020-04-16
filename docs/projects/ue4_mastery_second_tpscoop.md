---
# Page settings
layout: default
keywords:
comments: false

# Hero section
title: "UE4 Mastery: Second TPS Coop"
description: >
    The goal of this project is to create a Coop (Multiplayer with possible Splitscreen support) Third Person Shooter. 
    I plan to use this project as a base to learn Advanced UE4 C++ and Networking concepts. 
    This project should cover most key areas such as Materials, Levels, Gameplay Logic (Such as health etc.), Animations, AI and a few more key concepts.

# Author box
author:
    title: Source
    title_url: 'https://github.com/CallumCarmicheal/UE4_Learning_Projects/tree/master/ue4_mastery_second_tpscoop'
    external_url: true
    description: View on github

# Micro navigation
micro_nav: true

page_nav:
    prev:
        content: Previous project
        url: 'projects/ue4_mastery_first_fpsgame/'
---

# Summary
This project is just like the previous one [ue4_mastery_first_fpsgame](../ue4_mastery_first_fpsgame/), I am following the course (listed below) while adding my own additions here and there. 

The goal of this project is to create a Coop (Multiplayer with possible Splitscreen support) Third Person Shooter. 
I plan to use this project as a base to learn Advanced UE4 C++ and Networking concepts. 
This project should cover most key areas such as Materials, Levels, Gameplay Logic (Such as health etc.), Animations, AI and a few more key concepts.

After this project is finished it will be used as a prototype for learning advanced level design techniques and possibly implementing more mechanics such as buildable / deployable cover etc.



# Learning source(s) used
I used the following course to get a grasp on the basic features of UE4.  
- [Unreal Engine 4 Mastery: Create Multiplayer Games with C++](https://www.udemy.com/unrealengine-cpp)

## Additions
I have made a few changes / additions to from the base lessons, though not all are listed here are the main ones:
- Implemented a build counter using the [UE4 Build system, FPSGameEditor.Target.cs](../../ue4_mastery_second_tpscoop/Source/CoopGameEditor.Target.cs).
but can be changed through editing [FPSGameEditor.Target.cs](../../ue4_mastery_second_tpscoop/Source/CoopGameEditor.Target.cs).

## References / Used Materials or Tutorials

Date Viewed: April1 16, 2020 
Date Published (If avail): November 8, 2018
Link: [UE4 Tutorial: Creating a Parabolic (Curved) 2D HUD like Halo/Destiny](https://zaggoth.wordpress.com/2018/11/08/ue4-tutorial-creating-a-parabolic-curved-2d-widget-hud-like-halo-destiny/), 
Mirror: [archive.org Cached]()
I used this resource while creating the HUD to help give a more polished feel while the game is playing. 

# Screenshots

## Prototype(s) / Milestones

### [11/11/19] 
#### Created Project
Commit: [2cc262408ac6c16c21fdbe9e55f08e52a71a84cb](https://github.com/CallumCarmicheal/UE4_Learning_Projects/commit/2cc262408ac6c16c21fdbe9e55f08e52a71a84cb)

### [12/11/19] 
#### Added character
Commit: [7b7c7afb544b79fd288e9f2da6eff56f72567071](https://github.com/CallumCarmicheal/UE4_Learning_Projects/commit/7b7c7afb544b79fd288e9f2da6eff56f72567071)

Added character with movement: Crouching, Jumping and animations.

![TestLevel](../../resources/ue4_mastery_second_tpscoop/Prototype_TestLevel_With_CharAnim.PNG "TestLevel")

## Learning source used
I used the following course to get a grasp on the basic features of UE4.  
[Unreal Engine 4 Mastery: Create Multiplayer Games with C++](https://www.udemy.com/unrealengine-cpp)
