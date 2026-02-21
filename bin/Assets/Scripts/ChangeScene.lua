ChangeScene._sceneToGoTo = ""
ChangeScene._selectable = nil

function ChangeScene:awake()
    self._selectable = self.gameObject:getSelectable()
end

function ChangeScene:update(dt)
    
    if (self._selectable.submitTriggered) then
        SceneManager.Instance:loadScene("Assets/Scenes/" .. self._sceneToGoTo .. ".lua", self._sceneToGoTo)
        SceneManager.Instance:changeScene(self._sceneToGoTo)
    end

end

function ChangeScene:setParameters(params) 
    for name, param in pairs(params) do
        if (name == "scene") then
            self._sceneToGoTo = param
        end
    end 
end