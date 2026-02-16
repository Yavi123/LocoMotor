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
        RigidBody = {
            mass = "-1",
            group = "player",
            ignoreGroup = "player",
            size = "1 1 1"
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
    button = {
        UIImage = {
            rect_minAnchor = "0.7 0.1",
            rect_maxAnchor = "0.8 0.2",
            rect_upLeft = "0 0",
            rect_downRight = "0 0",
            image = "CrossMaterialRed",
            sortingLayer = 1
        },
        SelectableReader = {
        },
        Selectable = {
            left = "button2",
            first = ""
        }
    },
    button2 = {
        UIImage = {
            rect_minAnchor = "0.45 0.1",
            rect_maxAnchor = "0.55 0.2",
            rect_upLeft = "0 0",
            rect_downRight = "0 0",
            image = "CrossMaterialRed",
            sortingLayer = 1
        },
        SelectableReader = {
        },
        Selectable = {
            right = "button",
            left = "button3"
        }
    },
    button3 = {
        UIImage = {
            rect_minAnchor = "0.2 0.1",
            rect_maxAnchor = "0.3 0.2",
            rect_upLeft = "0 0",
            rect_downRight = "0 0",
            image = "CrossMaterialRed",
            sortingLayer = 1
        },
        SelectableReader = {
        },
        Selectable = {
            right = "button2",
            down = "button4"
        }
    },
    button4 = {
        UIImage = {
            rect_minAnchor = "0.2 0.3",
            rect_maxAnchor = "0.3 0.4",
            rect_upLeft = "0 0",
            rect_downRight = "0 0",
            image = "CrossMaterialRed",
            sortingLayer = 1
        },
        SelectableReader = {
        },
        SetFullscreen = {
        },
        Selectable = {
            up = "button3"
        }
    },
    text = {
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
            colorTop = "0.0 0.04706 0.06275",
            colorBot = "0.13333 0.04706 0.06275",
            sortingLayer = 2
        }
    }
}