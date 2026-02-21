local pos11 = Vector3(-0.2, 1.5, -2)
local pos12 = Vector3(-0.2, 1.5, 7.5)
local speed = 0.1

local time = 0

function CameraMovement:update(dt)
    time = time + dt * speed * 0.001
    
    local alpha = (math.sin(time) + 1) / 2
    local result = Vector3.Lerp(pos11, pos12, alpha)

    self.gameObject.transform.position = result
end