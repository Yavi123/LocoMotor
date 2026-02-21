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
    NPC_00 = {
        Transform = {
            position = "-1.16 -0.05  -4.8 ",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_00.mesh",
            material = "m_NPC"
        },
    },
    NPC_01 = {
        Transform = {
            position = "1.3 -0.05  -4.6 ",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_01.mesh",
            material = "m_NPC"
        },
    },
    NPC_02 = {
        Transform = {
            position = "-1.31 -0.1  -2.85 ",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_02.mesh",
            material = "m_NPC"
        },
    },
    NPC_03 = {
        Transform = {
            position = "-1.53 -0.1  -1.93 ",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_03.mesh",
            material = "m_NPC"
        },
    },
    NPC_04 = {
        Transform = {
            position = "1.45 -0.02 -0.47 ",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_04.mesh",
            material = "m_NPC"
        },
    },
    NPC_05 = {
        Transform = {
            position = "1.23 -0.05 0.92 ",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_05.mesh",
            material = "m_NPC"
        },
    },
    NPC_06 = {
        Transform = {
            position = "1.31 -0.1 -3.21 ",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_06.mesh",
            material = "m_NPC"
        },
    },
    NPC_07 = {
        Transform = {
            position = "-1.2 0.01 -0.02 ",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_07.mesh",
            material = "m_NPC"
        },
    },
}