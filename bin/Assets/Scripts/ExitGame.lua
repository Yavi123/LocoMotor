ExitGame._selectable = nil

function ExitGame:awake()
    self._selectable = self.gameObject:getSelectable()
end

function ExitGame:update(dt)
    
    if (self._selectable.submitTriggered) then
        LocoMotor.Quit()
    end

end
