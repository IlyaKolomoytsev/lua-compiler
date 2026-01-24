function area(shape)
    return shape:area()
end

circle = {
    r = 10,
    area = function(self)
        return 3.14 * self.r * self.r
    end
}

rect = {
    w = 4,
    h = 5,
    area = function(self)
        return self.w * self.h
    end
}

print(area(circle)) -- 314.15
print(area(rect))   -- 20