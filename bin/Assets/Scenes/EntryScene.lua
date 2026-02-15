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
        },
        InputController = {

        },
        Movement = {
            
        }
    },
    img = {
        Transform = {
            position = "0 0 -10",
            size = "1, 1, 1",
            rotation = "0 0 0"
        },
        UIImage = {
            minAnchor = "0.8 0.1",
            maxAnchor = "0.9 0.2",
            upLeft = "60 80",
            downRight = "10 0",
            image = "CrossMaterial",
            sortingLayer = 1
        }
    },
    img2 = {
        Transform = {
            position = "0 0 -10",
            size = "1, 1, 1",
            rotation = "0 0 0"
        },
        UIImage = {
            minAnchor = "0.8 0.1",
            maxAnchor = "0.9 0.2",
            upLeft = "0 0",
            downRight = "0 0",
            image = "CrossMaterial",
            sortingLayer = 1
        }
    }
}