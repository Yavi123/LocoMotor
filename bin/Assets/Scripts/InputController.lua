InputController._movement = nil

function InputController:awake()
end
function InputController:update()

    if (Input.Instance:getKeyDown("W")) then
        self._movement:move(3)
    end

end

function InputController:start()

    self._movement = self.gameObject:getLuaComponent("Movement")
end

function InputController:setParameters(params)
end

