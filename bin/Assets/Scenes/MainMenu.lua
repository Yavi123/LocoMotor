MainMenu = {
    MainCamera = {
        Camera = {
            background = "0.80392 0.82745 0.83529"
        },
        Transform = {
            position = "0 0 0",
            size = "1 1 1",
            rotation = "0 0 0"
        }

    },
    TitleText = {
        UIText = {
            rect_minAnchor = "0.5 0.5",
            rect_maxAnchor = "0.5 0.55",
            rect_upLeft = "0 0",
            rect_downRight = "0 0",
            text = "Presiona para comenzar",
            font = "PoetsenOne",
            alignment = "c",
            colorTop = "0.0 0.04706 0.06275",
            colorBot = "0.13333 0.04706 0.06275",
            sortingLayer = 2
        }
    },
    NextSceneButton = {
        UIImage = {
            rect_minAnchor = "0.35 0.45",
            rect_maxAnchor = "0.65 0.525",
            rect_upLeft = "10 10",
            rect_downRight = "10 10",
            image = "ButtonNormal",
            sortingLayer = 1
        },
        SelectableReader = {
        },
        ChangeScene = {
            scene = "GamePlay"
        },
        Selectable = {
            down = "FullscreenButton",
            first = ""
        }
    },
    FullscreenButton = {
        UIImage = {
            rect_minAnchor = "0.35 0.625",
            rect_maxAnchor = "0.65 0.7",
            rect_upLeft = "10 10",
            rect_downRight = "10 10",
            image = "ButtonNormal",
            sortingLayer = 1
        },
        SelectableReader = {
        },
        SetFullscreen = {
        },
        Selectable = {
            down = "ExitButton",
            up = "NextSceneButton"
        }
    },
    ExitButton = {
        UIImage = {
            rect_minAnchor = "0.35 0.8",
            rect_maxAnchor = "0.65 0.875",
            rect_upLeft = "10 10",
            rect_downRight = "10 10",
            image = "ButtonNormal",
            sortingLayer = 1
        },
        SelectableReader = {
        },
        ExitGame = {
        },
        Selectable = {
            up = "FullscreenButton"
        }
    },
}