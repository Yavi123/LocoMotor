ImageSpringOnBeat.spring = DampedSpringResult()
ImageSpringOnBeat._image = nil
ImageSpringOnBeat.targetScale = 0

ImageSpringOnBeat.velocityOnBeat = 0
ImageSpringOnBeat.frequency = 0
ImageSpringOnBeat.damping = 0

function ImageSpringOnBeat:set(initsize, vel, freq, dap)
    self.velocityOnBeat = vel
    self.frequency = freq
    self.damping = dap
    self._image = self.gameObject:getUIImage()
    self._image:setDimensions(Vector2(initsize, initsize))
    self.targetScale = self._image:getDimensions().y
end

function ImageSpringOnBeat:awake()
    self._image = self.gameObject:getUIImage()
    self.targetScale = self._image:getDimensions().y
end

function ImageSpringOnBeat:update(dt)
    self.spring = Math.CalculateDampedSpring(self.spring, self.targetScale, dt / 1000, self.frequency, self.damping)
    
    self._image:setDimensions(Vector2(self.spring.position, self.spring.position))
end

function ImageSpringOnBeat:onBeat()
    self.spring.velocity = self.velocityOnBeat
end

function ImageSpringOnBeat:setParameters(params) 
    for name, param in pairs(params) do
        if (name == "velocityOnBeat") then
            self.velocityOnBeat = tonumber(param)
        elseif (name == "frequency") then
            self.frequency = tonumber(param)
        elseif (name == "damping") then
            self.damping = tonumber(param)
        end
    end
    return true
end