EntryScene = {
    MainCamera = {
        Camera = {
            background = "0.80392 0.82745 0.83529"
        },
        Movement ={},
        InputController = {},
        AudioListener = {},
        Transform = {
            position = "0 1.5 -5",
            size = "1 1 1",
            rotation = "0 0 0"
        }

    },
    
    --AUDIO
    Audio1 = {
        EventEmitter = {
            Volume = 1
        }
    },
    Audio2 = {
        EventEmitter = {
            Volume = 1
        }
    },
    Audio3 = {
        EventEmitter = {
            Volume = 1
        }
    },
    Audio4 = {
        EventEmitter = {
            Volume = 1
        }
    },
    
    
    --NIVEL
    MetroMesh = {
        Transform = {
            position = "0 0 0",
            size = "1, 1, 1",
            rotation = "0 0 0"
        },
        MeshRenderer = {
            mesh = "MetroMesh.mesh",
            material = "m_Main"
        },
    },
    MetroFloor = {
        Transform = {
            position = "0 0 0",
            size = "1, 1, 1",
            rotation = "0 0 0"
        },
        MeshRenderer = {
            mesh = "FloorMesh.mesh",
            material = "m_MetroFloor"
        },
    },
    MetroLCD = {
        Transform = {
            position = "0 0 0",
            size = "1, 1, 1",
            rotation = "0 0 0"
        },
        MeshRenderer = {
            mesh = "LCDMesh.mesh",
            material = "m_LCD"
        },
    },
    NPC00 = {
        Transform = {
            position = "-1.3 0.5 2.1",
            size = "1 1 1",
            rotation = "0 -20 0"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_00.mesh",
            material = "m_NPC"
        },
    },
}