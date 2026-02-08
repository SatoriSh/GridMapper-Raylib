<p align="center">
  <img src="https://github.com/user-attachments/assets/b0b93380-f1f2-482f-88f6-59d467246d90" width="400" alt="2D Grid Map Editor Logo">
</p>

# 2D Grid Map Editor

A high-performance, lightweight grid-based level editor built with **C++** and **Raylib**. This tool allows developers to prototype maps using a layered system and export the results into a clean, parseable `.txt` format.

## 📽️ Video-Presentation
https://github.com/user-attachments/assets/caade3fb-9806-4a09-8381-0df0c521440f

## 📸 Visualization vs. Data
To showcase your work, I recommend using a side-by-side comparison in this section. It clearly demonstrates how the visual layers translate into raw data.

| **Editor View** | **Exported Data (`Grid.txt`)** |
| :--- | :--- |
| ![Editor Screenshot](https://github.com/user-attachments/assets/f70a6eb8-13f4-4f8f-b26e-4ca271d62472) | ![Text Screenshot](https://github.com/user-attachments/assets/1cd1e1e6-57d2-44e4-9eff-ed0fb03ec305) |
| ![Editor Screenshot](https://github.com/user-attachments/assets/7487815a-5c55-4669-9bbf-523016ae4340) | ![Text Screenshot](https://github.com/user-attachments/assets/775ec0af-79fc-42a5-ae1c-437c97279a82) |
| ![Editor Screenshot](https://github.com/user-attachments/assets/289f66fa-7ef6-4e9e-9d50-e8340e46d43b) | ![Text Screenshot](https://github.com/user-attachments/assets/a3c25b4d-48c4-42f1-8d2e-da5d4dec9b28) |
---

## ✨ Features
* **Customizable Grid:** Supports map sizes from **4x4 up to 64x64**.
* **Layered Workflow:** 10 distinct layers (0-9) with unique color signatures for better visualization.
* **Advanced Camera:** 2D camera with smooth zoom and a "turbo" mode using Left Shift.
* **Efficient UI:** Built-in GUI for real-time layer switching, save confirmation, and coordinate hints.
* **Quick Export:** Instantly saves your layout to a `.txt` file with a structured width/height header.

---

## ⌨️ Controls

### Navigation
* **W / A / S / D**: Move Camera.
* **Left Shift**: Boost movement speed.
* **Mouse Wheel**: Zoom In / Out.

### Editing
* **Left Click / Space**: Paint current layer.
* **Right Click**: Erase cell (Reset to Layer 0).
* **0 - 9 Keys**: Select active layer.
* **R**: Reset entire grid.
* **N**: Toggle layer number visibility.

### File Management
* **Ctrl + S** (or Save Button): Export grid to `Grid.txt`.
* **H** (Hold): Show keyboard shortcuts.

---

## 🛠️ Technical Overview

### Export Format
The `GridExportManager` generates a space-delimited file that is easy to parse in any engine:
```text
[Width] [Height]
[Row 0: Cell 0] [Row 0: Cell 1] ...
[Row 1: Cell 0] [Row 1: Cell 1] ...
```

### Dependencies
* **Language**: C++17.
* **Graphics**: Raylib.
* **UI**: Raygui.

---

## 🚀 Building and Running
1.  Ensure **Raylib** is installed and correctly linked in your environment.
2.  Include all source files from the `src` directory.
3.  Compile using your preferred C++ compiler:
    ```bash
    g++ main.cpp src/*.cpp -lraylib -o GridEditor
    ```
4.  Run the executable and set your map dimensions in the initial GUI.

---

## 📜 License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

---

*Developed as a tool for efficient 2D game level design.*
