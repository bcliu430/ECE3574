# ECE 3574 p3 README:

### Camera.cpp camera.hpp

convert a camera qjsonobject to a struct, struct contains:
```
struct Ccamera{
  int focus;             // the view point of the camera
  struct coor cen;       // a struct contains center coordinate
  double resolution[2];  // resolution array
  int size[2];           // size array 
  struct coor nor;       // a struct contains normal coordinate
};
```

### geometry.cpp geometry.hpp

This class contains all math calculations including:
1. a struct coordinate system contains x,y,z
```
struct coor{
  double x,y,z;
  bool operator==(const coor &c) const{
    return (this ->x == c.x && this ->y == c.y && this -> z == c.z);
  }

    coor operator=(const coor &c) {
    this->x = c.x;
    this->y = c.y;
    this->z = c.z;
    return *this;
  }

};
```
2. dot product two vector
3. magitude of a vector
4. unitvector of a vector
5. cross product of a vector
6. a bool funtion to determine if intersect
7. a function to get the intersect point

### getcolor.cpp getcolor.hpp

This class is used to calculate the color of each pixel and return the color to the pixel

### light.cpp light.hpp

convert the element of the qjsonarray to a light struct, the light struct contains:
```
struct Clight{
  double intensity;
  struct coor loc;
};
```

### objects.cpp objects.hpp

convert each object in the qjsonarray to an object struct, the object struct contains:
```
struct Cobject{
    struct coor cen;
    struct coor nor; // plane
    double radius; // sphere
    color Ccol;
    double lambert;
    std::string type;

    bool operator==(const Cobject & obj) const {
      return (this-> cen == obj.cen &&
      this-> nor == obj.nor &&
      this-> radius == obj.radius &&
      this-> Ccol == obj.Ccol &&
      this-> lambert == obj.lambert &&
      this-> type == obj.type);
    }
};
```

if the object type is sphere, radius will be the radius of the sphere and the

normal will be 0, and if the object typr is plane, the radius is 0 and the 

normal will be the plane's normal.

The object struct also contains a color struct:
```
struct color{
  int r,g,b;
  bool operator==(const color &c) const{
    return (this ->r == c.r && this ->g == c.g && this -> b == c.b);
  }

  color &operator= (const color &c) {
    this-> r = c.r;
    this-> g = c.g;
    this-> b = c.b;
    return *this;
  }
  color &operator+ (const color &c) {
    this-> r = this-> r + c.r;
    this-> g = this-> g + c.g;
    this-> b = this-> b + c.b;
    return *this;
  }
};
```

### parse.cpp parse.hpp

This module parses the files into a json format, ```return EXIT_SUCCESS``` if there 

is parse error, otherwise ```return EXIT_FAILURE```

### process.cpp process.hpp

This module processes the parsed json input and convert it to qimage 



### vtray.cpp

main program
