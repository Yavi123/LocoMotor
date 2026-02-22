BeatCounter._accumulatedTime = 0
BeatCounter._timeSinceBegan = 0

BeatCounter.baseBPM = 105
BeatCounter.currentBPM = 105
BeatCounter.growthRate = 0.00001 -- tweak this
BeatCounter._songTime = 0

--depende de cuanto tarda en cargar (el audio se reproduce cuando puede, pero el siguiente delta time es tan alto que pasa muy rápido)

BeatCounter._startBeatOffset = 400

BeatCounter.milisecondsInBeat = 60000 / 206

BeatCounter.eventEmitter = nil

BeatCounter._numBeats = -4
BeatCounter._rawNumBeats = 0

BeatCounter._timeWaited = 0

function BeatCounter:awake()
    
    self.eventEmitter = SceneManager.Instance.activeScene:getObjectByName("Audio1"):getEventEmitter()
    self._timeWaited = 0
end

function BeatCounter:update(dt)

    if (self._timeWaited < 500) then
        self._timeWaited = self._timeWaited + dt
        if (self._timeWaited >= 500) then
            self.eventEmitter:setEvent("event:/Song")
            self.eventEmitter:play()
        end
        return
    end
    
    if (self._timeSinceBegan < self._startBeatOffset) then
        self._timeSinceBegan = self._timeSinceBegan + dt
        if (self._timeSinceBegan >= self._startBeatOffset) then
            self._accumulatedTime = self._timeSinceBegan - self._startBeatOffset
        end
        return
    end
    self._timeSinceBegan = self._timeSinceBegan + dt

    self._accumulatedTime = self._accumulatedTime + dt

    while self._accumulatedTime > self.milisecondsInBeat do
        self._accumulatedTime = self._accumulatedTime - self.milisecondsInBeat
        self._numBeats = self._numBeats + 1
        if (self._numBeats >= 0) then
            SceneManager.Instance.activeScene:sendMessage("onBeat")
        end
        SceneManager.Instance.activeScene:sendMessage("onBeatRaw")
    end

    self._songTime = self._songTime + dt

    -- exponential growth
    self.currentBPM = self.baseBPM * math.exp(self.growthRate * self._songTime)
    self.milisecondsInBeat = 60000 / self.currentBPM
end
