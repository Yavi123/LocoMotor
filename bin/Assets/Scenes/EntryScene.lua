EntryScene = {
    MainCamera = {
        Camera = {
            background = "0.80392 0.82745 0.83529"
        },
        AudioListener = {},
        Transform = {
            position = "0 0 0",
            size = "1 1 1",
            rotation = "0 0 0"
        }

    },
    cube = {
        Transform = {
            position = "0 0 -10",
            size = "1, 1, 1",
            rotation = "15 -40 0"
        },
        MeshRenderer = {
            mesh = "ConemanMesh.mesh",
            material = "CustomMaterial"
        }
    },
    light = {
        Transform = {
            position = "0 1 -8",
            size = "1, 1, 1",
            rotation = "0 -0 0"
        },
        Light = {
            type = "point",
            spec = "1 1 1",
            diff = "1 1 1"
        },
        InputController = {

        },
        Movement = {
            
        }
    }
}