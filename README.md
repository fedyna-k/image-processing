<h1 align="center">Program for Image Analysis</h1>

The `pia` CLI can be used to analyse images as seen in the course.

### Usage
```
pia [option|...parameters] <path>
```

If you need further help on the program usage, type `pia --help`.

## 💻 Compiling and executing the program 💻

### Dependencies

|Package|Minimum version|Required|
|:-:|:-:|:-:|
|`CMake`|`3.5`|`Yes`|
|`OpenCV`|`4.9`|`Yes`|

### Commands

```bash
# Create compile directory
mkdir build
cd build
# Compile the program and check for depencies issues
cmake ..
make
# Run the program on test image, you should see an Among Us character
./pia ../data/byebye.jpeg
```