<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>cub3D - 42 School Project</title>
</head>
<body>
    <h1>cub3D</h1>
    <p><strong>Author:</strong> BAH Mamadou</p>
    <p><strong>Status:</strong> Student in common core at 42 School</p>
    <h2>Project Overview</h2>
    <p>
        <em>cub3D</em> is a 42 school project that aims to develop a basic 3D game engine using the
        <strong>raycasting technique</strong>, inspired by classic games such as Wolfenstein 3D.
        The project is written in C and uses the <strong>MinilibX</strong> graphical library.
    </p>
    <h2>Features</h2>
    <ul>
        <li>Raycasting-based 3D rendering</li>
        <li>Keyboard input handling for movement</li>
        <li>Texture rendering for walls</li>
        <li>Sprite rendering</li>
        <li>Collision detection</li>
    </ul>
    <h2>Installation</h2>
    <p>To compile and run the project, you need:</p>
    <ul>
        <li>Linux or macOS</li>
        <li>GCC compiler</li>
        <li>MinilibX library</li>
    </ul>
    <h2>Compilation</h2>
    <p>Clone the repository and run the following commands in the terminal:</p>
    <pre>
    git clone &lt;your-repo-url&gt;
    cd cub3D
    make
    </pre>
    <h2>Usage</h2>
    <p>After compilation, run the executable with a map file as argument:</p>
    <pre>
    ./cub3D maps/example.cub
    </pre>
    <p>Controls:</p>
    <ul>
        <li><strong>W</strong> - Move forward</li>
        <li><strong>S</strong> - Move backward</li>
        <li><strong>A</strong> - Turn left</li>
        <li><strong>D</strong> - Turn right</li>
        <li><strong>ESC</strong> - Exit the game</li>
    </ul>
    <h2>Project Structure</h2>
    <ul>
        <li><code>src/</code> - Source code files</li>
        <li><code>includes/</code> - Header files</li>
        <li><code>maps/</code> - Example map files</li>
        <li><code>Makefile</code> - Build script</li>
    </ul>
    <h2>Documentation</h2>
    <p>
        All functions are documented using <strong>Doxygen</strong> style comments. You can generate
        documentation by running:
    </p>
    <pre>
    doxygen Doxyfile
    </pre>
    <h2>License</h2>
    <p>This project is open-source and free to use for educational purposes.</p>
    <h2>Contact</h2>
    <p>If you have questions or suggestions, contact me: <strong>BAH Mamadou</strong></p>
</body>
</html>
