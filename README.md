# Zappy, the official Amber simulation.

## Introduction

We had 5 weeks to make an entire simulation based on rules set by Epitech.
In this project, we were 6 persons working on it.

- Network side
  - Léo Sautron
  - Nathan Maillot
This part of the project was restricted by without using threads and sub-process.

- Artificial Intelligence
  - Noah Lagrange Bacary
  - Cédric Roulof
Here, we were faced with algorithms, and understanding of AI actually.

- Graphical User Interface
  - Julien Ferdinand (OpenGL handling)
  - Benjamin Lauret (UI/UX)
  - Léo Sautron (OpenGL handling)
  - Nathan Maillot (UI/UX and architecture)
The main goal was to make a cosy User Interface, user-friendly, and full of informations.

Special thanks to Raphaël Turpin, who help us on OpenGL and VR implementation (thanks God).

## Context

### The Lore

- You are on a planet named **Amber**.
- The natives of this planet is the **Trantotians**.
- A **Trantorians** belongs to **teams** (as *tribes*).

### The Trantorians

- Each Trantorian have an inventory.
- They can :
  - *move* and rotate themselves.
  - *lay eggs*.
  - *take* items dropped on the floor.
  - *drop* items on the floor.
  - *see* in front of them.
  - *eject* other Trantorians from their positions.
  - *make sound* that allow them to **communicate** with other Trantorians.

### The Goal

- Trantorians have to **level up**.
- The first team with **6** Trantorians at the **8th** level win.

### Limitations

- Each action that a Trantorian can do costs time units.
- Trantorians eat 1 food each 126 time units.
  - If they can't eat, they die.

## Amber Server

We called the server Amber, because in the lore, Trantorians can take stuff from the floor, and these things are mainly stones.
So it just was logic to call the server by a stone name. (and admit that is a cool name)

This side will manages the world logic, all the actions will be executed here.
Here we manage all connections and the behaviour of the world.

## Turing AI

I think I don't have to explain why we called our AI like this...

So basically, our AI is based on multiple things, we made a strategy:

### Level 1

- We have a mother AI
  - She aims at level up.
  - If it can't level up, she will find food.
 
### Level 2

- The mother AI
  - If she is starving, she creates a child who suicides, and then collect his food.
  - If she is alone on her case, she makes a child which stay with her and try to level up.
  - If she doesn't have a child collector, she makes one and his goal is to collect items needed by the mother.

For the next levels, the logic stay the same as the second level's one.

## Onyx

As you know, we called our server Amber, and we searched a named for the GUI, and Onyx is as cool as Amber for a stone name.

So, get ready there are many things...

### 3D rendering

We used OpenGL to represent the world, it's a great stack to use in C++, and we just love the way it works.
It was not really an objective choice.

So we made many things to improve the UX:

- Animations on Trantorians.
- Camera moving.
- Optimisation.

It seems like there is not so many things, but we made many optimisations (field of view, partial rendering on 3D objects).

All the code was made from scratch.
The only library used to simplify our life during the project is *assimp*.

For the rendering, we have integrated OpenGL to our personnal Game Engine, the Etib Game Engine (EGE).

### User Interface

For the user interface, we choose an open source API *ImGUI*.

We worked on a user-friendly interface by making a tutorial which drive you through the software.
All the usefull informations of the world is displayed on differents panel.

But can also customize your experience in the app by changing the mouse sensivity for example. And you can interact with the world to see all the informations you need.

In our Game Engine, we have also integrated ImGui for a easier use for developpement. By making interfaces and simplify the use of it thanks to the GUIManager we made.

## Documentation

To see the documentation about the project and how you can integrate your own rules, or even your own GUI, you can go our website here : (WIP)

Thanks for your visit !

Nathan from Etib Corp.
