Note._image = nil
Note.targetY = 0
Note.timeToGetThere = 0
Note.elapsedTime = 0
Note._channel = 0
local timeDestruction = -1

function Note:awake()
    self._image = self.gameObject:getUIImage()
end

function Note:update(dt)
    local pressOk = math.abs(self.elapsedTime - self.timeToGetThere) < 100
    
    if(self._channel == 0 and Input.Instance:getKeyDown("A") and pressOk) then
        self._image:setImage("ArrowLefthiteMat")
        timeDestruction = self.elapsedTime
    end
    if(self._channel == 1 and Input.Instance:getKeyDown("S") and pressOk) then
        self._image:setImage("ArrowDownhiteMat")
        timeDestruction = self.elapsedTime
    end
    if(self._channel == 2 and Input.Instance:getKeyDown("W") and pressOk) then
        self._image:setImage("ArrowUpWhiteMat")
        timeDestruction = self.elapsedTime
    end
    if(self._channel == 3 and Input.Instance:getKeyDown("D") and pressOk) then
        self._image:setImage("ArrowRightWhiteMat")
        timeDestruction = self.elapsedTime
    end
    
    self.elapsedTime = self.elapsedTime + dt
    
    if(timeDestruction < 0) then
        self:updatePosition()
    end


    if(timeDestruction > 0 and math.abs(self.elapsedTime - timeDestruction) > 100) then
        SceneManager.Instance.activeScene:removeGameObject(self.gameObject.name)
    end
end

function Note:setTargetPlace(y)
    self._image = self.gameObject:getUIImage()
    self.targetY = y * 2
end

function Note:setNoteChannel(y)
    self._channel = y
end

function Note:setTimeToGetThere(tInMiliseconds, elapsed)
    self.timeToGetThere = tInMiliseconds
    self.elapsedTime = elapsed
    self:updatePosition()
end

function Note:updatePosition()
    local po = self._image:getAnchorPoint()
    po.y = Math.Lerp(0, self.targetY, self.elapsedTime / (self.timeToGetThere*2))
    self._image:setAnchorPoint(po)
    if (po.y > 1.2) then
        SceneManager.Instance.activeScene:removeGameObject(self.gameObject.name)
    end
end