Billboard.Camera = nil

function Billboard:awake()
    self.Camera = SceneManager.Instance.activeScene:getObjectByName("MainCamera").transform
end

function Billboard:update(dt)
    self.gameObject.transform:lookAt(self.Camera.position, Vector3(0,1,0))
    self.gameObject.transform:setUpwards(Vector3(0,1,0))

end
