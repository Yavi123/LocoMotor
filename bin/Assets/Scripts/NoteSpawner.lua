NoteSpawner.beatsToWaitForBeforeBegin = 0
NoteSpawner.chanceForBpmChange = 0.1
NoteSpawner.bpmChangeDuration = 8
NoteSpawner._beatCounter = nil
NoteSpawner._scene = nil
NoteSpawner._numNotes = 0

function NoteSpawner:awake()
    self._scene = SceneManager.Instance.activeScene
    self._beatCounter = self._scene:getObjectByName("BeatCounter"):getLuaComponent("BeatCounter")
end

function NoteSpawner:update()
end

function NoteSpawner:onBeatRaw()

    if (self.beatsToWaitForBeforeBegin <= 0) then
        
        self:createNote()

        if ((self._beatCounter._numBeats % self.bpmChangeDuration) == 0) then
        end

    else
        self.beatsToWaitForBeforeBegin = self.beatsToWaitForBeforeBegin - 1
    end

end

function NoteSpawner:createNote()
    local gObj = SceneManager.Instance.activeScene:addGameObject("Note_" .. self._numNotes)
    local imag = gObj:addUIImage()
    imag:setImage("BackPanelMat")
    imag:setAnchorPoint(Vector2(0.42, 0))
    local note = gObj:addLuaComponent("Note")
    note:setTargetPlace(0.9)
    note:setTimeToGetThere(self._beatCounter.milisecondsInBeat * 4, self._beatCounter._accumulatedTime)

    self._numNotes = self._numNotes + 1
end
