local springValues = DampedSpringResult()
SongDistorter._emitter = nil

function SongDistorter:start()
    self._emitter = self.gameObject:getLuaComponent("BeatCounter").eventEmitter
end

function SongDistorter:update(dt)

    springValues = Math.CalculateDampedSpring(springValues, 0, dt * 0.001, 25, 0.1)

    self._emitter:setParameter("Pitch", springValues.position)

    if (Input.Instance:getKeyDown("Ñ")) then
        springValues.velocity = 10
    end
end
