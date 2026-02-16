Fil de Fer (Wireframe)
A 3D wireframe viewer that renders heightmaps in isometric projection. This project is part of the 42 school graphics branch curriculum.
Overview
FDF (Fil de Fer, meaning "wireframe" in French) reads a map file containing height values and renders it as a 3D wireframe model. The program uses the MiniLibX graphics library to display an isometric projection of the terrain.

Features:

Isometric Projection: Renders heightmaps in beautiful 3D isometric view
Color Gradient: Altitude-based color interpolation for visual depth
Map Parsing: Reads and validates .fdf map files
Line Drawing: Implements Bresenham's line algorithm for efficient rendering
Error Handling: Robust validation for malformed maps and invalid input
Zoom controls: in and out using the mouse

Installation
Prerequisites

GCC or Clang compiler
Make
MiniLibX library
X11 libraries (Linux) or AppKit framework (macOS)

Compilation
Clone the repository and compile:
bashgit clone <your-repo-url> fdf
cd fdf

Compile Options
make          # Compile the project
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Recompile everything

Usage
Run the program with a map file:
bash./fdf maps/42.fdf
Map File Format
Map files (.fdf) contain a grid of integers representing altitude values:

0  0  0  0  0

0 10 10 10  0

0 10 20 10  0

0 10 10 10  0

0  0  0  0  0

Optional: Add color values in hexadecimal after comma:
0  0  0  0  0

0 10,0xFF0000 10 10  0

0 10 20,0x00FF00 10  0

Controls

ESC /or q: Close the window and exit
X button: Close the window and exit

Technical Details
Algorithm Implementation
Bresenham's Line Algorithm
The core rendering uses Bresenham's line algorithm for drawing lines between points efficiently without floating-point arithmetic:

Calculate delta values (dx, dy)
Determine step direction
Initialize error accumulator
Iterate and plot pixels while adjusting error

Isometric Projection
Converts 2D map coordinates (x, y, z) to isometric view using the transformation:
iso_x = (x - y) * cos(30°)
iso_y = (x + y) * sin(30°) - z
This creates the characteristic 3D appearance with 30-degree angles.
Color Interpolation
Implements linear interpolation between vertex colors:
ccolor = start_color + (end_color - start_color) * (current_step / total_steps)
Each RGB channel is interpolated separately for smooth gradients.
Memory Management

Dynamic allocation for map grid storage
Proper cleanup on exit and error conditions
No memory leaks (verified with valgrind)

Coordinate System
    y
    ↑
    |
    |
    |———————→ x
   /
  /
 ↙
z

Error Handling
The program handles various error cases:

Invalid file format or extension
File not found or unreadable
Malformed map (inconsistent line lengths)
Invalid height or color values
Memory allocation failures
MiniLibX initialization errors

Resources

MiniLibX Documentation
Bresenham's Algorithm
Isometric Projection
