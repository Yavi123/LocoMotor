InputController = {behaviour = behaviour}
InputController.__index = InputController

InputController._movement = nil

function InputController:awake()
end
function InputController:update(dt)

    self._movement.move(self._movement, 0.001 * dt, 0.001 * dt)

end

function InputController:start()

    self._movement = self.behaviour:gameObject():getBehaviour("Movement"):getScript()
end

function InputController:setParameters(params)
end

