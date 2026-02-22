local spawnTime = 0
local awakeCalled = false
local springScaleY = DampedSpringResult()

function Puntos:awake()
    springScaleY.position = 0
    self.targetScale = 1
    spawnTime = SceneManager.Instance.activeScene.elapsedTime
end

function Puntos:update(dt)
    if(math.abs( SceneManager.Instance.activeScene.elapsedTime - spawnTime) > 600) then
        SceneManager.Instance.activeScene:removeGameObject(self.gameObject.name)
    end
    --springScaleY = Math.CalculateDampedSpring(springScaleY, self.targetScale, dt / 1000, 25, 0.4)
    --local scale = self.gameObject.transform.size
    --scale.y = springScaleY.position
    --self.gameObject.transform.size = scale
end