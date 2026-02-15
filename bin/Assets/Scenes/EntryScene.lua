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
            rect_minAnchor = "0.8 0.1",
            rect_maxAnchor = "0.9 0.2",
            rect_upLeft = "60 80",
            rect_downRight = "10 0",
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
        UIText = {
            rect_minAnchor = "0.2 0.1",
            rect_maxAnchor = "0.8 0.2",
            rect_upLeft = "0 0",
            rect_downRight = "0 0",
            text = "hola",
            font = "PoetsenOne",
            alignment = "c",
            colorTop = "0.8 0.04706 0.06275",
            colorBot = "0.13333 0.04706 0.06275",
            sortingLayer = 2
        }
    }
}