InputController._movement = nil
InputController._audioIndex = 1

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
    if (Input.Instance:getKeyDown("Q")) then
        SceneManager.Instance.activeScene:getObjectByName("Audio" .. self._audioIndex):getEventEmitter():play()
        self._audioIndex = self._audioIndex % 4
        self._audioIndex = self._audioIndex + 1
    end

end

function InputController:start()

    self._movement = self.gameObject:getLuaComponent("Movement")
end

function InputController:setParameters(params)
end

