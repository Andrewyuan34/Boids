# Contributing to Boids Simulation

## 1. Code Management
- **Main branch:** Always stable and buildable.
- **Feature branches:** Develop new features or fixes in separate branches (e.g., `feature/skybox`).
- **Pull Requests:** Submit PRs for review before merging to main.

## 2. Task Assignment
- **Issues:** Use GitHub Issues to track bugs, features, and tasks.
- **Project Board:** Use GitHub Projects for workflow management (To Do / In Progress / Done).

## 3. Code Style & Quality
- **Formatting:** Use `.clang-format` (Google style). Format code before committing.
- **Static Analysis:** Use `clang-tidy` (checked in CI).

## 4. Automation
- **CI/CD:** All PRs must pass GitHub Actions (build, test, format).
- **Testing:** Use GoogleTest for unit tests. Tests must pass before merging.

## 5. Documentation & Communication
- **Docs:** Plan to add Doxygen 
- **Discussion:** Use GitHub Discussions or discord chat for questions and ideas.
