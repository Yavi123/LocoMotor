Movement = {behaviour = behaviour}
Movement.__index = Movement

function Movement:move(x, y)
    local pos = self.behaviour:gameObject():transform():getPosition()

    local xVal = pos.x - x
    pos.x = xVal
    local yVal = pos.y - y
    pos.y = yVal

    local result = PhysicsManager:Instance():raycast(Vector3(-10, 0, -10), Vector3(10, 0, -10))

    if (result:hasHit()) then
        Engine:Instance():print("HEMOS DADO CON EL RAYCAST!!!!: " .. result:getCollider():gameObject():getName())
    end
    
    self.behaviour:gameObject():transform():setPosition(pos)
end
