# OpenGL Circle Drawing Animation

A simple OpenGL application that animates a circle being drawn by gradually increasing the number of polygon segments—from a triangle (3 segments) up to a smooth circle (100 segments). The current segment count is displayed on screen using 7-segment style digits.

## Features

- **Animated circle**: Starts as a triangle and morphs into a circle by adding one segment every 350 ms.
- **Tangent-based circle algorithm**: Draws the circle using a tangent-length method for polygon approximation.
- **Segment counter**: Renders the current segment count (3–100) using 7-segment digit display.

## Dependencies

- **GLFW** – window and input handling
- **GLAD** – OpenGL function loader
- **C++17** – standard library (e.g. `<thread>`, `<chrono>`)

## Project Structure

```
├── src/
│   ├── main.cpp    # Application entry and rendering logic
│   └── glad.c      # GLAD OpenGL loader
├── include/
│   ├── glad/       # GLAD headers
│   ├── GLFW/       # GLFW headers
│   └── KHR/        # Khronos platform header
├── lib/            # GLFW library (libglfw3dll.a)
└── glfw3.dll       # GLFW runtime DLL (required to run the executable)
```

## Running

1. Build the project (see above).
2. Run `.exe` file.
3. A window titled **"Circle Drawing Animation"** (1560×840) opens with a black background. The circle animates from 3 to 100 segments (configurable), with the segment count shown in white 7-segment digits.

## License

This project is provided as-is for learning and experimentation.
