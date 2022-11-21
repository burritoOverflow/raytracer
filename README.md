# raytracer

Test-driven development based on 'The Ray Tracer Challenge'.

Example images rendered at the end of each completed chapter can be found in the images folder, and are saved in the .ppm format. Preview on macOS can open these files, but if you're on another OS you might need to use a program such as GIMP.

## How to install

```
mkdir build
cd build
cmake ..

# On Ubuntu
make -j$(nproc)

# On macOS
make -j$(sysctl -n hw.physicalcpu)
```

However, I mostly use VSCode's CMake Tools for building the app and running the unit tests. Highly recommended!
