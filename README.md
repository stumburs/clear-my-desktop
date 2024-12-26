# clear-my-desktop

A simple Windows tool to clear your desktop. It creates a folder in the user's `Documents` directory with today's date (e.g, "2024-12-26") using the format **YYYY-MM-DD** and **moves** all the files and folders from the desktop to that newly created folder.

# Building

- Download/clone `clear-my-desktop.cpp`
- Compile using `g++ clear-my-desktop.cpp -O3 -o clear-my-desktop`
- Run `./clear-my-desktop.exe`
