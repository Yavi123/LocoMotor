SelectableReader = {behaviour = behaviour}
SelectableReader.__index = SelectableReader

SelectableReader._selectable = nil
SelectableReader._image = nil

function SelectableReader:awake()
    self._selectable = self.behaviour:gameObject():getSelectable()
    self._image = self.behaviour:gameObject():getUIImage()
end

function SelectableReader:update(dt)
    
    if (self._selectable:submitTriggered()) then
        Engine:Instance():print("submitTriggered_" .. self.behaviour:gameObject():getName())
    elseif (self._selectable:cancelTriggered()) then
        Engine:Instance():print("cancelTriggered_" .. self.behaviour:gameObject():getName())
    elseif (self._selectable:onSelected()) then
        self._image:setImage("CrossMaterialBlue")
    elseif (self._selectable:onDeselected()) then
        self._image:setImage("CrossMaterialRed")
    end

end
