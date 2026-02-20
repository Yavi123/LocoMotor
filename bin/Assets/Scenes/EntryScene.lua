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
            position = "0 1 0",
            size = "1 1 1",
            rotation = "0 0 0"
        },

    },
    metro = {
        Transform = {
            position = "0 0 0",
            size = "1, 1, 1",
            rotation = "0 0 0"
        },
        MeshRenderer = {
            mesh = "Metro.mesh",
            material = "MetroMat"
        },
    },
    guitarra = {
        Transform = {
            position = "0 1 -6",
            size = "1, 1, 1",
            rotation = "0 0 0"
        },InputController= {},
        Movement = {},
        MeshRenderer = {
            mesh = "Guitarra.mesh",
            material = "GuitarraMat"
        },
    },
    metroExtra = {
        Transform = {
            position = "0 0 0",
            size = "1, 1, 1",
            rotation = "0 0 0"
        },
        MeshRenderer = {
            mesh = "MetroExtra.mesh",
            material = "MetroMat"
        },
    },
    metroFloor = {
        Transform = {
            position = "0 0 0",
            size = "1, 1, 1",
            rotation = "0 0 0"
        },
        MeshRenderer = {
            mesh = "MetroFloor.mesh",
            material = "FloorMat"
        },
    },
    npc = {
        Transform = {
            position = "0 .5 -2",
            size = "1, 1, 1",
            rotation = "0 0 0"
        },
        NPC = {},
        MeshRenderer = {
            mesh = "Man.mesh",
            material = "EnemyMat"
        }
    },
    floor = {
        Transform = {
            position = "0 -0.2 0",
            size = "1, 1, 1",
            rotation = "0 0 0"
        },
        MeshRenderer = {
            mesh = "Plane.mesh",
            material = "FloorMat"
        },
    }
}