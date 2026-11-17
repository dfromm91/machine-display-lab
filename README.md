# Machine Display Lab

A C++17 and Qt Quick demo that displays simulated vehicle speed. A button generates the next synthetic frame, and a QML binding updates the display when C++ emits a change signal.

## Run

Requires Qt 6.5 or newer with Qt Quick, Qt Quick Controls, and Qt QML, plus CMake and a C++17 compiler.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/machine_display
```

If CMake cannot find Qt, pass its installation prefix with `-DCMAKE_PREFIX_PATH=/path/to/qt` or configure with `qt-cmake`.

## Design

A synthetic frame with identifier `0x181` carries a two-byte little-endian speed in tenths of km/h. A pure C++ decoder validates the identifier, length, and range. The Qt object publishes a read-only speed property and signals changes. The decoder test checks valid and invalid frames. The offscreen Qt test loads QML, advances the simulator, and checks that the binding updates.

The protocol definition is for this demo. Frames are generated in process, with no CAN interface, vehicle hardware, or Simulink model.
