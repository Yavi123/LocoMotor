SelectableReader._selectable = nil
SelectableReader._image = nil

function SelectableReader:awake()
    self._selectable = self.gameObject:getSelectable()
    self._image = self.gameObject:getUIImage()
end

function SelectableReader:update(dt)
    
    if (self._selectable.submitTriggered) then
        LocoMotor.Log("submitTriggered_" .. self.gameObject.name)
    elseif (self._selectable.cancelTriggered) then
        LocoMotor.Log("cancelTriggered_" .. self.gameObject.name)
    elseif (self._selectable.onSelected) then
        self._image:setImage("CrossMaterialBlue")
    elseif (self._selectable.onDeselected) then
        self._image:setImage("CrossMaterialRed")
    end

end
