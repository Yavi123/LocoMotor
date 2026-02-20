EntryScene = {
    MainCamera = {
        Camera = {
            background = "0.80392 0.82745 0.83529"
        },
        AudioListener = {},
        InputController= {},
        Movement = {
            
        },
        Transform = {
            position = "0 1.5 -5",
            size = "1 1 1",
            rotation = "0 0 0"
        },

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
    FloorMesh = {
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
    TransMesh = {
        Transform = {
            position = "0 0 0",
            size = "1, 1, 1",
            rotation = "0 0 0"
        },
        MeshRenderer = {
            mesh = "TransMesh.mesh",
            material = "m_Trans"
        },
    },
    LCDMesh = {
        Transform = {
            position = "0 0 0",
            size = "1, 1, 1",
            rotation = "0 0 0"
        },
        MeshRenderer = {
            mesh = "LCDMesh.mesh",
            material = "m_LCD"
        },
    }
}