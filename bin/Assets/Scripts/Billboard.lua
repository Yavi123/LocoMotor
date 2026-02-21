Billboard.Camera = nil

function Billboard:awake()
    self.Camera = SceneManager.Instance.activeScene:getObjectByName("MainCamera").transform
    self.gameObject.transform:lookAt(self.Camera.position)
end

function Billboard:fixedUpdate(dt)
    local aaa = self.Camera.position
    self.gameObject.transform:lookAt(aaa)
end
