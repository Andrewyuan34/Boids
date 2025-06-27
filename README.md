# 🐦 Boids Toon Sky Project

> A visual simulation of looking up at the sky and seeing a stylized flock of birds in motion.  
> Built using the Boids algorithm and toon shading to create a dynamic, aesthetically-driven experience.  
> Tech stack: C++17 / OpenGL / ImGui (Windows & Linux)

### Features
✅ Implement Viewport/WindowInfo class  
✅ Add boundary force steering  
✅ 2D -> 3D  
✅ Integrate bgfx & ozz 
⬜ Enhance flock animation  
⬜ Dynamic skybox implementation  
⬜ Integrate clang-format in pre-commit hook and CI workflow

---

## Development Plan

### Phase 1: Core Functionality

Focus: Build a solid foundation that "flies, looks good, and is tweakable in real-time."

---

### Phase 2: Optimization & Maintainability

Focus: Improve performance, modularity, and dev comfort without overengineering.

---

### Phase 3: Polish & Showcase Ready

Focus: Final optimizations, visual quality, and debugging polish.


## Usage

```
git clone --recursive <git_repo>
cd Boids

# Windows
// Dependency: LLVM/Clang, Ninja and CMake
// Default Compiler is Clang
build.bat 
// executable is under build-clang/bin/Boids.exe

// or use msvc
// Dependency: Visual Studio and CMake
build.bat --msvc
// after running the script, open .sln file to run the program

# Linux
# Dependencies: clang, cmake and ninja
./build.sh
# Executable will be under build-clang/bin/Boids
```

---
### Script Options
- `--debug`
- `--tidy`
- `--format`
---

For contribution guidelines, see [CONTRIBUTION.md](CONTRIBUTION.md).
