InputController._movement = nil

function InputController:awake()
end
function InputController:update()
    if (Input.Instance:getKeyDown("W")) then
        self._movement:moveZ(-1)
    end
    if (Input.Instance:getKeyDown("S")) then
        self._movement:moveZ(1)
    end
    if (Input.Instance:getKeyDown("A")) then
        self._movement:moveX(-1)
    end
    if (Input.Instance:getKeyDown("D")) then
        self._movement:moveX(1)
    end

end

function InputController:start()

    self._movement = self.gameObject:getLuaComponent("Movement")
end

function InputController:setParameters(params)
end

