function Movement:move(x, y)
    local pos = self.gameObject.transform.position

    local xVal = pos.x - x
    pos.x = xVal
    local yVal = pos.y - y
    pos.y = yVal

    local result = Physics.Instance:raycast(Vector3(-10, 0, -10), Vector3(10, 0, -10))

    if (result.hasHit) then
        LocoMotor:Log("HEMOS DADO CON EL RAYCAST!!!!: ")
    end
    
    self.gameObject.transform.position = pos
end
