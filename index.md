# Introduction

aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa bbbbbbbbb

## What is a Split Screen and what is it used for?
## Why is it important to have a Split Screen?
## Context and History
## Current references

<iframe width="560" height="315" src="https://www.youtube.com/embed/sf4RgCDbM58" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

<iframe width="560" height="315" src="https://www.youtube.com/embed/GAWHzGNcTEw" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

# Current State

## Technical evolution of the Split Screen
## Current techniques in the industry
## Split Screen in other game engines

<iframe width="560" height="315" src="https://www.youtube.com/embed/rw2VKAdTdgQ" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

<iframe width="560" height="315" src="https://www.youtube.com/embed/ipU4MtV-O_8" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

<iframe width="560" height="315" src="https://www.youtube.com/embed/1XdjHIshYY4" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

# Selected Approach

## Basic concepts
## ¿Renderer vs Camera vs Viewport?
## How could we theoretically code a Split Screen?
## SDL2 is evil  →  We have to look for another way
## Then, how can we program a Split Screen in SDL2?

# Split Screen Handout & Solution

All the material provided (handout, solution and presentation) can be downloaded by clicking this link:

### [Download Provided Material](https://github.com/francesctr4/SplitScreen/archive/refs/heads/main.zip)

### TODO 1 → [Render.cpp]
### “Create cameras according to a viewport”

* First create a Camera* with the viewport defined.
* Then add the camera to the cameras list.
* Don’t forget to clear the cameras list.

![TODO 1](https://user-images.githubusercontent.com/99948892/227061306-41568d6d-1769-4885-9462-44ebd0c9ced8.png)

### TODO 2 → [Player.cpp]
### “Manage players movement and camera”

![TODO 2.1](https://user-images.githubusercontent.com/99948892/227061545-10c1719e-4356-4efd-ac43-142c79e7657d.png)

![TODO 2.2](https://user-images.githubusercontent.com/99948892/227061574-8d4a79ae-7d23-44aa-8753-0183929767e6.png)

### TODO 3 → [Scene.cpp]
### “Instantiate the players in the scene”

![TODO 3](https://user-images.githubusercontent.com/99948892/227061519-a9e45b39-7443-492d-8a9e-3645a7def82a.png)

### TODO 4 → [Render.cpp]
### “Get the viewport of each active camera”

![TODO 4](https://user-images.githubusercontent.com/99948892/227061466-5e230e87-7bd7-47ca-9a98-58328ba1c05a.png)

### TODO 5 → [Render.cpp]
### “Center each active camera to a player”

![TODO 5](https://user-images.githubusercontent.com/99948892/227061423-3f448e8e-b911-4898-a4bc-5dc2899e688c.png)

### TODO 6 → [Scene.cpp]
### “Create all the necessary cameras”

![TODO 6](https://user-images.githubusercontent.com/99948892/227061370-2e8c3613-9fbb-4680-ba4d-2297d2eadcc7.png)

## Results

### One Screen
![ONE_SCREEN](https://user-images.githubusercontent.com/99948892/227045336-ce753db3-f400-4d8f-849f-9633457ac9d4.png)

### Two Screens (Vertical)
![TWO_VERTICAL](https://user-images.githubusercontent.com/99948892/227045341-c1b03904-5ede-4d00-8ed5-b368c2c323d9.png)

### Two Screens (Horizontal)
![TWO_HORIZONTAL](https://user-images.githubusercontent.com/99948892/227045344-c21b2ccc-bf39-43e9-91e9-bf008cbc3204.png)

### Three Screens (Align Left)
![THREE_LEFT](https://user-images.githubusercontent.com/99948892/227045349-7625d11b-ce6a-4449-a9d0-61827eacf2c1.png)

### Three Screens (Align Center)
![THREE_CENTERED](https://user-images.githubusercontent.com/99948892/227045351-607e58de-3fc8-4a8a-b482-18539ba95bce.png)

### Three Screens (Align Right)
![THREE_RIGHT](https://user-images.githubusercontent.com/99948892/227045352-6396a525-127a-4e4e-9e16-8c1dc14d84b8.png)

### Four Screens
![FOUR_SCREENS](https://user-images.githubusercontent.com/99948892/227045355-35c6e569-ca34-409d-8882-1036e3aeef22.png)


# Possible Improvements

## Problems of this implementation in SDL2
## Features you could add to your Split Screen

# Conclusions

## Advantages of the Split Screen
## Disadvantages of the Split Screen

# References

This section gathers all the references used during the development of the research:

## Articles

* [Visión general de F1 2021](https://www.ea.com/es-es/games/f1/f1-2021/game-overview)
* [Wikipedia - Pantalla dividida](https://es.wikipedia.org/wiki/Pantalla_dividida) 
* [Ultimate Pop Culture Wiki - Split screen (video games)](https://ultimatepopculture.fandom.com/wiki/Split_screen_(video_games))
* [Split-Screen: Videogame History through Local Multiplayer Design](https://philarchive.org/archive/KARSV)
* [Game Developer - Shared-Multi-Split Screen Design](https://www.gamedeveloper.com/design/shared-multi-split-screen-design) 
* [Voronoi split screen: A Quick Tour](https://mattwoelk.github.io/voronoi_split_screen_notes/)

## Videos

* [Rocket League - Splitscreen Multiplayer Gameplay Trailer](https://youtu.be/sf4RgCDbM58) 
* [It Takes Two – Official Gameplay Trailer](https://youtu.be/GAWHzGNcTEw)
* [How To Create A Split Screen In Unity](https://youtu.be/rw2VKAdTdgQ) 
* [UE4 Split Screen](https://youtu.be/ipU4MtV-O_8) 
* [UE4 - Tutorial - Local Splitscreen!](https://youtu.be/68ViQFeE02o) 
* [How to Easily Add Split Screen Multiplayer in Godot](https://youtu.be/1XdjHIshYY4)
* [Voronoi Split Screen System](https://youtu.be/vsRrB0ZggE4)

## Previous years approach

* [Split Screen (2021)](https://lucaspg14.github.io/Split-Screen/) by [Lucas Pérez](https://github.com/LucasPG14)
* [Split Screen (2019)](https://jorgegh2.github.io/Split-screen/) by [Jorge Gemas](https://github.com/jorgegh2)

