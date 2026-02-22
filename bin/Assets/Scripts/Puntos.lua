local spawnTime = 0
local springPosY = DampedSpringResult()
local img = nil

function Puntos:awake()
    spawnTime = SceneManager.Instance.activeScene.elapsedTime

    img = self.gameObject:getUIImage()
    springPosY.position = img:getAnchorPoint().y
    self.targetScale = img:getAnchorPoint().y - 0.4
end

function Puntos:update(dt)
    if(math.abs( SceneManager.Instance.activeScene.elapsedTime - spawnTime) > 600) then
        SceneManager.Instance.activeScene:removeGameObject(self.gameObject.name)
    end

    springPosY = Math.CalculateDampedSpring(springPosY, self.targetScale, dt / 1000, 25, 0.4)
    local pos = img:getAnchorPoint()
    pos.y = springPosY.position
    img:setAnchorPoint(pos)
end