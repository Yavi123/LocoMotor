local pos11 = Vector3(-0.2, 1.5, -2)
local pos12 = Vector3(-0.2, 1.5, 6.5)
local rot1 = Vector3(0, 0, 0)

local pos21 = Vector3(1, 2.9, -5.8)
local pos22 = Vector3(1, 2.9, 4.2)
local rot2 = Vector3(-20,160,0)

-- local pos31 = Vector3(-1.15, 0.3, -6.7)
-- local pos32 = Vector3(-1.15, 0.4, -1.2)
-- local rot2 = Vector3(15,200,0)

local speed = 0.075

local time = 0
local lastTime = 0
local camIndex = 0

function CameraMovement:awake()
    lastTime = SceneManager.Instance.activeScene.elapsedTime
end

function CameraMovement:update(dt)
    local realTime = SceneManager.Instance.activeScene.elapsedTime
    
    time = time + dt * speed * 0.001
    
    local alpha = (math.sin(time) + 1) / 2
    local result = Vector3(0,0,0)
    if(camIndex == 0) then
        self.gameObject.transform.eulerRotation = rot1
        result = Vector3.Lerp(pos11, pos12, alpha)
    end
    if(camIndex == 1) then
        self.gameObject.transform.eulerRotation = rot2
        result = Vector3.Lerp(pos21, pos22, alpha)
    end
    -- if(camIndex == 2) then
    --     self.gameObject.transform.eulerRotation = rot2
    --     result = Vector3.Lerp(pos31, pos32, alpha)
    -- end

    self.gameObject.transform.position = result

    if(math.abs(realTime - lastTime) > 8000) then

        lastTime = realTime
        camIndex =(camIndex +1)%2
        
    end
end