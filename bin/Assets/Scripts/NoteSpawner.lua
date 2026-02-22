NoteSpawner.beatsToWaitForBeforeBegin = 0
NoteSpawner.chanceForBpmChange = 0.1
NoteSpawner.bpmChangeDuration = 8
NoteSpawner._beatCounter = nil
NoteSpawner._scene = nil
NoteSpawner._numNotes = 0
NoteSpawner._accumNotes = 0

function NoteSpawner:awake()
    self._scene = SceneManager.Instance.activeScene
    self._beatCounter = self._scene:getObjectByName("BeatCounter"):getLuaComponent("BeatCounter")
end

function NoteSpawner:update()
end

function NoteSpawner:onBeatRaw()

    if (self.beatsToWaitForBeforeBegin <= 0) then
        
        --if((self._beatCounter._numBeats % 2) == 0) then 
            self:createNote()
        --end
        if ((self._beatCounter._numBeats % self.bpmChangeDuration) == 0) then
        end

    else
        self.beatsToWaitForBeforeBegin = self.beatsToWaitForBeforeBegin - 1
    end

end

function NoteSpawner:createNote()
    
    --Ignorar nota
    if(self._accumNotes > 4) then
        local ignoreNote = math.random(1,2)
        if(ignoreNote == 1) then 
            self._accumNotes = 0
            return
        end
    end

    --Params
    local speed = 6
    local noteWidth = 40
    local randomChannel = math.random(0,3)
    
    --Crear nota
    local gObj = SceneManager.Instance.activeScene:addGameObject("Note_" .. self._numNotes)
    local imag = gObj:addUIImage()
    local arrowPos = 0.3 + 0.1 * randomChannel + 0.05
    if randomChannel == 0 then
        imag:setImage("ArrowLeftMat")
    elseif randomChannel == 1 then
        imag:setImage("ArrowDownMat")
    elseif randomChannel == 2 then
        imag:setImage("ArrowUpMat")
    elseif randomChannel == 3 then
        imag:setImage("ArrowRightMat")
    end

    imag:setSortingLayer(5)
    imag:setDimensions(Vector2(100,100))
    imag:setAnchorPoint(Vector2(arrowPos, 0))
    local note = gObj:addLuaComponent("Note")
    note:setNoteChannel(randomChannel)
    note:setTargetPlace(0.9)
    note:setTimeToGetThere(self._beatCounter.milisecondsInBeat * speed, self._beatCounter._accumulatedTime)

    self._numNotes = self._numNotes + 1
    self._accumNotes = self._accumNotes  +1
end
