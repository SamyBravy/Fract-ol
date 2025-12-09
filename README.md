# ❄️ Fract-ol

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Graphics](https://img.shields.io/badge/Graphics-MinilibX-red?style=for-the-badge)

A graphical exploration project to generate and interact with various fractals using **MinilibX**, a minimal graphics library restricted to single pixel manipulation.

## 📸 Gallery

<div align="center">
  <img src="Mandelbrot.png" alt="Mandelbrot" width="300" />
  <img src="Julia.png" alt="Julia" width="300" />
</div>
<div align="center">
  <img src="Custom_tunnel.png" alt="Custom Tunnel" width="300" />
  <img src="Custom_sphere.png" alt="Custom Sphere" width="300" />
</div>

## 🚀 Usage

### Linux prerequisites
Before building on Linux (or WSL), install the MiniLibX dependencies:
```bash
sudo apt-get update
sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
```

### Compilation
```bash
make
```

### Execution
Run the program with one of the following parameter sets:

#### 1. Mandelbrot Set
The classic Mandelbrot set.
```bash
./fractol Mandelbrot
```

#### 2. Julia Set
Generates different Julia sets based on the constant `c` passed as arguments.
```bash
./fractol Julia <real> <imaginary>
# Example:
./fractol Julia -0.8 0.156
```
*(If no arguments are provided, a default Julia set is rendered)*

#### 3. Custom Fractal
Allows you to experiment with the fractal formula $Z = Z^{exp} + C$.
```bash
./fractol Custom <z_exp> <is_c_inverted>
```
*   **z_exp**: The exponent power of Z iteration (e.g., 2 for standard Mandelbrot-like).
*   **is_c_inverted**: `1` to reciprocate C ($1/C$), `0` for normal C.

**Special Presets**:
*   `./fractol Custom 1 0` -> **Tunnel Effect** (Linear Z + C)
*   `./fractol Custom 1 1` -> **Sphere Effect** (Linear Z + 1/C)


## 🎮 Controls

### Navigation
*   **Arows**: Move the view.
*   **Mouse wheel**: Zoom.
*   **Click on mouse wheel**: Reset zoom.

### Colors
*   **C**: Move colors (Shift).
*   **X**: Increase distance between colors.
*   **Z**: Decrease distance between colors.

### Fractal Adjustments
*   **Y**: Increase precision (iterations).
*   **T**: Decrease precision (iterations).

### Modifying Complex Constant (Julia/Custom)
*   **D**: Increase c's real part.
*   **A**: Decrease c's real part.
*   **W**: Increase c's imaginary part.
*   **S**: Decrease c's imaginary part.
*   **R**: Reset c's values.

### System
*   **Esc**: Exit.