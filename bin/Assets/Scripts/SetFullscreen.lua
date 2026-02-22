SetFullscreen._selectable = nil

function SetFullscreen:awake()
    self._selectable = self.gameObject:getSelectable()
end

function SetFullscreen:update(dt)
    
    if (self._selectable.submitTriggered) then
        Graphics.Instance.fullscreen = not Graphics.Instance.fullscreen
    elseif (self._selectable.cancelTriggered) then
        local gObj = SceneManager.Instance.activeScene:addGameObject("AAAAA")
        local imag = gObj:addUIImage()
        --imag.enabled = false
        imag:setImage("BackPanelMat")
        local txt = gObj:addUIText()
        txt:setText("HOLA")
        txt:setFont("PoetsenOne")
    end

end
