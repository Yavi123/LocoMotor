local v1 = Vector3(0, 1.5, -2)
local v2 = Vector3(0, 1.5, 8)
local speed = 1

local time = 0

function CameraMovement:update(dt)
    time = time + dt * speed * 0.001     -- accumulate time
    
    local alpha = (math.sin(time) + 1) / 2
    local result = Vector3.Lerp(v1, v2, alpha)

    self.gameObject.transform.position = result
end