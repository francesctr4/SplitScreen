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

### TODO 2 → [Player.cpp]
### “Manage players movement and camera”

### TODO 3 → [Scene.cpp]
### “Instantiate the players in the scene”

### TODO 4 → [Render.cpp]
### “Get the viewport of each active camera”

### TODO 5 → [Render.cpp]
### “Center each active camera to a player”

### TODO 6 → [Scene.cpp]
### “Create all the necessary cameras”

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

