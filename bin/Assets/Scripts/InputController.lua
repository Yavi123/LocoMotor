InputController = {behaviour = behaviour}
InputController.__index = InputController

InputController._movement = nil

function InputController:awake()
end
function InputController:fixedUpdate()

    self._movement.move(self._movement, 0.0001, 0.0001)

end

function InputController:start()

    self._movement = self.behaviour:gameObject():getBehaviour("Movement"):getScript()
end

function InputController:setParameters(params)
end

