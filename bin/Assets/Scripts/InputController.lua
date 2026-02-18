InputController._movement = nil

function InputController:awake()
end
function InputController:fixedUpdate()

    self._movement.move(self._movement, 0.0001, 0.0001)

end

function InputController:start()

    self._movement = self.gameObject:getLuaComponent("Movement")
end

function InputController:setParameters(params)
end

