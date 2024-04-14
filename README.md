# Rope
Rope is a simple string manipulation library for the C programming language. The goal with this project was to implement some version of every string manipulaiton function available in the JS standard library, and clean up some of the grabage that comes with that notion. As of right now, this project is still in its infancy, bu it is still in working condition.
# Usage
The core of this library is a simple struct:
```c
typedef struct RopeString {
    char* content;
    size_t length;
} RopeString_t;
```
All manipulation functions perform operations on this struct. All modification functions are suffixed with _n, for _new, because they create new RopeString_t instances. In the future, _i, for _in-place functions will be added, modifying the passed string instead of creating a new one. 
When creating a new RopeString_t, it's important to note that the content of the given `char*` is copied into the struct, as opposed to the pointer. For this reason, a `char*` can safely be freed after using it to create a RopeString_t.
