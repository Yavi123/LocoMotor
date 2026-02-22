GamePlay = {
    MainCamera = {
        Camera = {
            background = "0.80392 0.82745 0.83529"
        },
        CameraMovement ={},
        AudioListener = {},
        Transform = {
            position = "0 1.5 -5",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        ChangeScene = {
            scene = "MainMenu"
        },
        Selectable = {
            first = ""
        }

    },
    
    --AUDIO
    Audio1 = {
        EventEmitter = {
            Volume = 1
        }
    },
    BeatCounter = {
        BeatCounter = { },
        NoteSpawner = { },
        SongDistorter = { }
    },

    ---------------------------------MESHES - METRO -----------------------------------------
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
    ---------------------------------NPCS-----------------------------------------
    NPC_00 = {
        Transform = {
            position = "-0.6 0 -5",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        NPC = {},
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_00.mesh",
            material = "m_NPC"
        },
    },
    NPC_01 = {
        Transform = {
            position = "-1.1 0 -3.17",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        NPC = 
        {
            cool = "ola"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_01.mesh",
            material = "m_NPC"
        },
    },
    NPC_02 = {
        Transform = {
            position = "-1.45 0 -2.62",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        NPC = {},
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_02.mesh",
            material = "m_NPC"
        },
    },
    NPC_03 = {
        Transform = {
            position = "0.15 0 -2.2",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        NPC = 
        {
            cool = "ola"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_03.mesh",
            material = "m_NPC"
        },
    },
    NPC_04 = {
        Transform = {
            position = "1.11 0 -2.85",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        NPC = {},
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_04.mesh",
            material = "m_NPC"
        },
    },
    NPC_05 = {
        Transform = {
            position = "1.33 0 -1.83",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        NPC = 
        {
            cool = "ola"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_05.mesh",
            material = "m_NPC"
        },
    },
    NPC_06 = {
        Transform = {
            position = "-1.1 0 0.05",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        NPC = {},
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_06.mesh",
            material = "m_NPC"
        },
    },
    NPC_07 = {
        Transform = {
            position = "-1.4 0.06 -0.5",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        NPC = 
        {
            cool = "ola"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_07.mesh",
            material = "m_NPC"
        },
    },
    NPC_08 = {
        Transform = {
            position = "1.2 0 0.44",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        NPC = {},
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_08.mesh",
            material = "m_NPC"
        },
    },
    NPC_09 = {
        Transform = {
            position = "1.2 0 1.37",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        NPC = 
        {
            cool = "ola"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_09.mesh",
            material = "m_NPC"
        },
    },
    NPC_10 = {
        Transform = {
            position = "-1 0 2.1",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        NPC = {},
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_10.mesh",
            material = "m_NPC"
        },
    },
    NPC_11 = {
        Transform = {
            position = "-1.35 0 4.2",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        NPC = 
        {
            cool = "ola"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_11.mesh",
            material = "m_NPC"
        },
    },
    NPC_12 = {
        Transform = {
            position = "-1.1 0 3.4",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        NPC = {},
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_12.mesh",
            material = "m_NPC"
        },
    },
    NPC_13 = {
        Transform = {
            position = "1.11 0 6",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        NPC = 
        {
            cool = "ola"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_12.mesh",
            material = "m_NPC"
        },
    },
    NPC_14 = {
        Transform = {
            position = "-1.10 0 5.6",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        NPC = {},
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_14.mesh",
            material = "m_NPC"
        },
    },
    NPC_15 = {
        Transform = {
            position = "1.11 0 4.2",
            size = "1 1 1",
            rotation = "0 0 0"
        },
        NPC = 
        {
            cool = "ola"
        },
        Billboard = {},
        MeshRenderer = {
            mesh = "NPC_15.mesh",
            material = "m_NPC"
        },
    },

    --REGION
    BackPanel = {
        UIImage = {
            rect_minAnchor = "0.3 -0.3",
            rect_maxAnchor = "0.7 1.3",
            rect_upLeft = "0 0",
            rect_downRight = "0 0",
            image = "BackPanelMat",
            sortingLayer = 0
        },
        ImageSpringOnBeat = {
            velocityOnBeat = 250,
            frequency = 20,
            damping = 0.3
        }
    },
    --EMPTY AROWS
    EmptyArrow0 = {
        UIImage = {
            rect_minAnchor = "0.35 0.9",
            rect_maxAnchor = "0.35 0.9",
            rect_upLeft = "50 50",
            rect_downRight = "50 50",
            image = "EmptyArrowMatLeft",
            sortingLayer = 3
        },
        ImageSpringOnBeat = {
            velocityOnBeat = 200,
            frequency = 20,
            damping = 0.3
        }
    },
    EmptyArrow1 = {
        UIImage = {
            rect_minAnchor = "0.45 0.9",
            rect_maxAnchor = "0.45 0.9",
            rect_upLeft = "50 50",
            rect_downRight = "50 50",
            image = "EmptyArrowMatDown",
            sortingLayer = 3
        },
        ImageSpringOnBeat = {
            velocityOnBeat = 200,
            frequency = 20,
            damping = 0.3
        }
    },
    EmptyArrow2 = {
        UIImage = {
            rect_minAnchor = "0.55 0.9",
            rect_maxAnchor = "0.55 0.9",
            rect_upLeft = "50 50",
            rect_downRight = "50 50",
            image = "EmptyArrowMatUp",
            sortingLayer = 3
        },
        ImageSpringOnBeat = {
            velocityOnBeat = 200,
            frequency = 20,
            damping = 0.3
        }
    },
    EmptyArrow3 = {
        UIImage = {
            rect_minAnchor = "0.65 0.9",
            rect_maxAnchor = "0.65 0.9",
            rect_upLeft = "50 50",
            rect_downRight = "50 50",
            image = "EmptyArrowMatRight",
            sortingLayer = 3
        },
        ImageSpringOnBeat = {
            velocityOnBeat = 200,
            frequency = 20,
            damping = 0.3
        }
    },
}