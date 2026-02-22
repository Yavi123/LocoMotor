SetFullscreen._selectable = nil

function SetFullscreen:awake()
    self._selectable = self.gameObject:getSelectable()
end

function SetFullscreen:update(dt)
    
    if (self._selectable.submitTriggered) then
        Graphics.Instance.fullscreen = not Graphics.Instance.fullscreen
    end

end
