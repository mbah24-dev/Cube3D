*This project has been created as part of the 42 curriculum by mbah.*

# cub3D

## Description

**cub3D** is a graphical project inspired by *Wolfenstein 3D*, developed in C using the MiniLibX library.  
The goal of the project is to create a simple 3D game engine using **raycasting**, allowing the player to navigate inside a maze described in a `.cub` configuration file.

The engine renders a first-person view of the map, handles player movement and rotation, displays textured walls, and includes bonus features such as a minimap and mouse-based camera control.  
The project also focuses heavily on **robust parsing**, **error handling**, and **memory safety**.

This project was developed **entirely solo**.

---

## Features

- Raycasting-based 3D rendering
- Textured walls (N/S/E/W)
- Player movement and rotation
- Keyboard controls (W/A/S/D + arrows)
- Cross-platform support (macOS & Linux)
- Robust `.cub` file parser with detailed error handling
- Minimap displaying nearby environment
- Bonus features:
  - Minimap overlay
  - Mouse-based camera rotation
  - Platform-specific MLX handling

---

## Instructions

### Requirements

- GCC
- Make
- MiniLibX (included in the repository)
- macOS or Linux

### Compilation

Clone the repository and compile:

```bash
make
```
For bonus features:

```bash
make bonus
```
### Execution

Run the program with a valid .cub map file:

```bash
./cub3D maps/good/dungeon.cub
```

### Controls


### Action	Key
Move forward ------> W

Move backward -----> S

Strafe left -------> A

Strafe right ------> D

Rotate camera -----> ← →

Exit program ------> ESC

Mouse movement can also be used for camera rotation (bonus).

### Project Structure

```text
cub3D/
├── inc/             # Headers and type definitions
├── src/             # Source code
│   ├── parser/      # File and map parsing
│   ├── render/      # Raycasting and rendering
│   ├── player/      # Movement and controls
│   ├── initializer/ # Engine and MLX initialization
│   ├── cleanup/     # Memory and resource management
│   └── debug/       # Debug utilities
├── maps/            # Test maps (valid and invalid)
├── textures/        # Wall textures
├── Lib/             # Libft
├── minilibx-*       # MiniLibX (macOS & Linux)
└── Makefile
````
## Resources

### Raycasting & Graphics
- **Lode Vandevenne – Raycasting Tutorial**  
  https://lodev.org/cgtutor/raycasting.html

- **Wolfenstein 3D Engine Breakdown**

- **MiniLibX Documentation (42)**

---

### C & Systems Programming
- **Linux man pages**
- **GNU GCC Documentation**
- **AddressSanitizer (ASan)**

---

## AI Usage

AI tools (ChatGPT) were used **only as learning assistance**, specifically for:

- Understanding raycasting theory and mathematics
- Debugging memory errors using AddressSanitizer
- Clarifying C concepts (bitwise operations, DDA algorithm, texture mapping)
- Improving code structure and readability
- Writing this README

All code was **written, tested, and validated manually** by the author.  
AI was **never used to generate complete source files**.

---

## Notes

- The project strictly follows **42 coding standards**
- Memory leaks and invalid accesses were checked using **AddressSanitizer**
- Extensive error handling ensures invalid maps are properly rejected

---

## Author

**mbah**  
42 Network – *Cub3D Project*
