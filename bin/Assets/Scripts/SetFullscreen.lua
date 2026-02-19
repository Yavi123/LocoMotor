SetFullscreen._selectable = nil
SetFullscreen._image = nil

function SetFullscreen:awake()
    self._selectable = self.gameObject:getSelectable()
    self._image = self.gameObject:getUIImage()
end

function SetFullscreen:update(dt)
    
    if (self._selectable.submitTriggered) then
        Graphics.Instance.fullscreen = not Graphics.Instance.fullscreen
    elseif (self._selectable.cancelTriggered) then
        LocoMotor.Quit()
    elseif (self._selectable.onSelected) then
        self._image:setImage("CrossMaterialBlue")
    elseif (self._selectable.onDeselected) then
        self._image:setImage("CrossMaterialRed")
    end

end
