Shape = {}
Shape.__index = Shape

function Shape:area()
    return 0
end

Circle = {}
Circle.__index = Circle
setmetatable(Circle, Shape)

function Circle:new(r)
    return setmetatable({ r = r }, self)
end

function Circle:area()
    return 3.14 * self.r * self.r
end

Rectangle = {}
Rectangle.__index = Rectangle
setmetatable(Rectangle, Shape)

function Rectangle:new(w, h)
    return setmetatable({ w = w, h = h }, self)
end

function Rectangle:area()
    return self.w * self.h
end

Square = {}
Square.__index = Square
setmetatable(Square, Rectangle)

function Square:new(s)
    return setmetatable(Rectangle:new(s, s), self)
end

c = Circle:new(10)
r = Rectangle:new(4, 5)
s = Square:new(5)

print(c:area())  -- 314
print(r:area())  -- 20
print(s:area()) -- 25