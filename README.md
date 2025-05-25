# Boids Simulation

### Features
✅ Implement Viewport/WindowInfo class  
✅ Add boundary force steering  
⬜ 2D -> 3D  
⬜ Enhance flock animation  
⬜ Dynamic skybox implementation
⬜ Integrate clang-format in pre-commit hook and CI workflow

### Usage

```
git clone --recursive <git_repo>
cd Boids

# Windows
// Dependency: Visual Studio or LLVM/Clang, Ninja and CMake
// Default Compiler is Clang
build.bat --release 
// executable is under build-clang/bin/Boids.exe

// or use msvc
build.bat --release --msvc
// after running the script, open .sln file to run the program

# Linux
# Dependencies: clang, cmake and ninja
./build.sh --release
# Executable will be under build-clang/bin/Boids
```

---
### Script Options
- `--debug`
- `--tidy`
