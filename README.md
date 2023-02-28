# An Entity-Component-System Example With SDL

This is an example of an entity component system implemented as prototype by using unordered maps. Find the corresponding blog post here: 

https://www.codingwiththomas.com/blog/an-entity-component-system-from-scratch

## Build

Use conan to build this example. If you haven't install conan, use `pip` to install: 
```
pip install conan==1.57.0
```
And then run the build commands. Note: I know there is already conan 2.0, but I haven't found time yet to check it out, so please stick to a version below 2.0
```
conan install . -if ./build --build missing
cmake -S . -B ./build
cmake --build ./build
```