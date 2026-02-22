NPC.targetScale = 0
NPC.lastScale = 0
NPC.nudge = 0.5
local springScaleY = DampedSpringResult()

function NPC:awake()
    springScaleY.position = self.gameObject.transform.size.y
    self.targetScale = self.gameObject.transform.size.y
end
function NPC:update(dt)
    
    springScaleY = Math.CalculateDampedSpring(springScaleY, self.targetScale, dt / 1000, 25, 0.4)
    local scale = self.gameObject.transform.size
    scale.y = springScaleY.position
    self.gameObject.transform.size = scale
end

function NPC:onBeat()
    springScaleY.velocity =self.targetScale + self.nudge
end