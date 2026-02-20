Movement.targetZ = 0
Movement.lastZ = 0
Movement.targetX = 0
Movement.lastX = 0
Movement.initPos = 0

function Movement:awake()
    --ESTO LLAMARLO DESDE UNA ESCENA DE ENTRY QUE LUEGO CARGUE EL MENU
    Audio.Instance:loadMaster("Assets/AudioBanks/Desktop")
    
    SceneManager.Instance.activeScene:getObjectByName("Audio1"):getEventEmitter():setEvent("event:/GuitarNote")
    SceneManager.Instance.activeScene:getObjectByName("Audio2"):getEventEmitter():setEvent("event:/GuitarNote")
    SceneManager.Instance.activeScene:getObjectByName("Audio3"):getEventEmitter():setEvent("event:/GuitarNote")
    SceneManager.Instance.activeScene:getObjectByName("Audio4"):getEventEmitter():setEvent("event:/GuitarNote")
    local pos = self.gameObject.transform.position
    self.initPosX = pos.x
    self.initPosZ = pos.z
end

function Movement:start()
    local file = LocoMotor.ReadFile("Assets/A.json")

    local a = Json.Parse(file)
    
    local Gamedata = a:objectAt("Game")

    LocoMotor.Log(Gamedata:objectAt("Game_name").stringValue)

    a:release()
end

function Movement:moveZ(z)
    self.targetZ = self.targetZ + tonumber(z)
end

function Movement:moveX(z)
    self.targetX = self.targetX + tonumber(z)
end

function Movement:rotateY(z)
    local rot = self.gameObject.transform.eulerRotation
    rot.y = rot.y + z;
    self.gameObject.transform.eulerRotation = Vector3(rot)
end

function Movement:update(dt)

    local currentZ = self.gameObject.transform.position.z
    local currentX = self.gameObject.transform.position.x

    local springPosZ = DampedSpringResult()
    springPosZ.position = currentZ
    springPosZ.velocity = tonumber(self.lastZ)
    local springPosX = DampedSpringResult()
    springPosX.position = self.initPos + currentX
    springPosX.velocity = tonumber(self.lastX)

    local resultZ = Math.CalculateDampedSpring(springPosZ, self.targetZ, dt / 1000, 14, 0.8)
    local resultX = Math.CalculateDampedSpring(springPosX, self.targetX, dt / 1000, 14, 0.8)

    local pos = self.gameObject.transform.position
    pos.z = resultZ.position
    pos.x = resultX.position
    self.gameObject.transform.position = pos
    self.lastZ = tonumber(resultZ.velocity)
    self.lastX = tonumber(resultX.velocity)

end

function Movement:fixedUpdate()

    local result = Physics.Instance:raycast(Vector3(-10, 0, -10), Vector3(10, 0, -10))

    if (result.hasHit) then
        LocoMotor.Log("HEMOS DADO CON EL RAYCAST!!!!: ")
    end
end
