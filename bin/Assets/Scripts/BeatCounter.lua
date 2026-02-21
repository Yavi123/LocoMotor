BeatCounter._accumulatedTime = 0

local milisecondsInBeat = 60000 / 120

BeatCounter._numBeats = 0

function BeatCounter:update(dt)
    self._accumulatedTime = self._accumulatedTime + dt

    while self._accumulatedTime > milisecondsInBeat do
        self._numBeats = self._numBeats + 1
        self._accumulatedTime = self._accumulatedTime - milisecondsInBeat
        SceneManager.Instance.activeScene:sendMessage("onBeat")
    end


end