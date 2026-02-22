Note._image = nil
Note.targetY = 0
Note.timeToGetThere = 0
Note.elapsedTime = 0

function Note:awake()
    self._image = self.gameObject:getUIImage()
end

function Note:update(dt)
    self.elapsedTime = self.elapsedTime + dt
    self:updatePosition()
end

function Note:setTargetPlace(y)
    self._image = self.gameObject:getUIImage()
    self.targetY = y * 2
end
function Note:setTimeToGetThere(tInMiliseconds, elapsed)
    self.timeToGetThere = tInMiliseconds * 2
    self.elapsedTime = elapsed
    self:updatePosition()
end

function Note:updatePosition()
    local po = self._image:getAnchorPoint()
    po.y = Math.Lerp(0, self.targetY, self.elapsedTime / self.timeToGetThere)
    self._image:setAnchorPoint(po)
end