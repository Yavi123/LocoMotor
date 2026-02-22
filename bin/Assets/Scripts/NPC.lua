NPC.targetScale = 0
NPC.lastScale = 0
NPC.nudge = 0.5
local offbeat = 1
local springScaleY = DampedSpringResult()

function NPC:awake()
    springScaleY.position = self.gameObject.transform.size.y
    self.targetScale = self.gameObject.transform.size.y
end

function NPC:setParameters(params) 
    for name, param in pairs(params) do
        if (name == "cool") then
            offbeat = 2
        end
    end
    return true
end

function NPC:update(dt)
    
    springScaleY = Math.CalculateDampedSpring(springScaleY, self.targetScale, dt / 1000, 20, 0.45)
    local scale = self.gameObject.transform.size
    scale.y = springScaleY.position
    self.gameObject.transform.size = scale
end

function NPC:onBeat()
    local beats = SceneManager.Instance.activeScene:getObjectByName("BeatCounter"):getLuaComponent("BeatCounter")._numBeats
    LocoMotor.Log(beats)
    if(beats%offbeat == 0) then
        springScaleY.velocity =self.targetScale + self.nudge
    end
end