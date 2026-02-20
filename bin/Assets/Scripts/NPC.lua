NPC.targetScale = 0
NPC.lastScale = 0
NPC.nudge = 0.5

function NPC:nudge()
    self.targetScale = self.targetScale + self.nudge
end


function NPC:update(dt)
 --if (Input.Instance:getKeyDown("W")) then 
        

    local springScaleY = DampedSpringResult()
    springScaleY.position = 1
    springScaleY.velocity = tonumber(self.lastScale)


    local resultY = Math.CalculateDampedSpring(springScaleY, self.targetScale, dt / 1000, 14, 0.2)

    local scale = self.gameObject.transform.size
    scale.y = resultY.position
    self.gameObject.transform.size = scale
    self.lastScale = tonumber(resultY.velocity)
end