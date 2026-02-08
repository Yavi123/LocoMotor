Movement = {behaviour = behaviour}
Movement.__index = Movement

function Movement:move(x, y)
    local pos = self.behaviour:gameObject():transform():getPosition()

    local xVal = pos.x - x
    pos.x = xVal
    local yVal = pos.y - y
    pos.y = yVal
    
    self.behaviour:gameObject():transform():setPosition(pos)
end
