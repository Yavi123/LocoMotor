SetFullscreen = {behaviour = behaviour}
SetFullscreen.__index = SetFullscreen

SetFullscreen._selectable = nil
SetFullscreen._image = nil

function SetFullscreen:awake()
    self._selectable = self.behaviour:gameObject():getSelectable()
    self._image = self.behaviour:gameObject():getUIImage()
end

function SetFullscreen:update(dt)
    
    if (self._selectable:submitTriggered()) then
        GraphicsManager:Instance():setFullscreen(not GraphicsManager:Instance():getFullscreen())
    elseif (self._selectable:cancelTriggered()) then
        Engine:Instance():print("cancelTriggered_" .. self.behaviour:gameObject():getName())
    elseif (self._selectable:onSelected()) then
        self._image:setImage("CrossMaterialBlue")
    elseif (self._selectable:onDeselected()) then
        self._image:setImage("CrossMaterialRed")
    end

end
