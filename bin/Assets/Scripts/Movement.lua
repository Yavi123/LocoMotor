Movement._targetPos = 0
Movement._lastVel = 0

function Movement:move(x)
    
    self._targetPos = tonumber(x)
end

function Movement:update(dt)

    local currentX = self.gameObject.transform.position.x

    local DampedSpringData = DampedSpringResult()
    DampedSpringData.position = self.gameObject.transform.position.x
    DampedSpringData.velocity = tonumber(self._lastVel)

    local result = Math.CalculateDampedSpring(DampedSpringData, self._targetPos, dt / 1000, 10, 0.4)

    local pos = self.gameObject.transform.position
    pos.x = result.position
    self.gameObject.transform.position = pos
    self._lastVel = tonumber(result.velocity)

end

function Movement:fixedUpdate()

    local result = Physics.Instance:raycast(Vector3(-10, 0, -10), Vector3(10, 0, -10))

    if (result.hasHit) then
        LocoMotor.Log("HEMOS DADO CON EL RAYCAST!!!!: ")
    end
end
