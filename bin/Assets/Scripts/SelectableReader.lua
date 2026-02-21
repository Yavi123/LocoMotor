SelectableReader._selectable = nil
SelectableReader._image = nil
SelectableReader._normalImage = "ButtonNormal"
SelectableReader._selectedImage = "ButtonHighlight"

function SelectableReader:awake()
    self._selectable = self.gameObject:getSelectable()
    self._image = self.gameObject:getUIImage()
    self._image:setImage(self._normalImage)
end

function SelectableReader:update(dt)
    
    if (self._selectable.onSelected) then
        self._image:setImage(self._selectedImage)
    elseif (self._selectable.onDeselected) then
        self._image:setImage(self._normalImage)
    end

end
