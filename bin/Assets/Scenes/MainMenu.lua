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
    LogoImage =
    {
        UIImage = {
            rect_minAnchor = "0 0",
            rect_maxAnchor = "1 1",
            rect_upLeft = "0 0",
            rect_downRight = "0 10",
            image = "MaterialLogo",
            sortingLayer = -1
        },
    },
    TitleText = {
        UIText = {
            rect_minAnchor = "0.6 0.1",
            rect_maxAnchor = "0.7 0.2",
            rect_upLeft = "0 0",
            rect_downRight = "0 0",
            text = "Pulsiona para empezar ñ",
            font = "PoetsenOne",
            alignment = "c",
            colorTop = "1.0 0.3 00.0067",
            colorBot ="0.2 0.07 00.0067",
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