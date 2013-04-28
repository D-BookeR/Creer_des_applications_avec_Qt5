import QtQuick 2.0

Grid {
    x: 25; y: 25
    width: 700; height: 700
    spacing: 25
    columns: 3

    MainRectangle {
        InnerRectangle {
            transformOrigin: Item.TopLeft
            xCenter: 0; yCenter: 0
            text: "TopLeft"
        }
    }

    MainRectangle {
        InnerRectangle {
            transformOrigin: Item.Top
            xCenter: 1; yCenter: 0
            text: "Top"
        }
    }

    MainRectangle {
        InnerRectangle {
            transformOrigin: Item.TopRight
            xCenter: 2; yCenter: 0
            text: "TopRight"
        }
    }

    MainRectangle {
        InnerRectangle {
            transformOrigin: Item.Left
            xCenter: 0; yCenter: 1
            text: "Left"
        }
    }

    MainRectangle {
        InnerRectangle {
            transformOrigin: Item.Center
            xCenter: 1; yCenter: 1
            text: "\nCenter"
        }
    }

    MainRectangle {
        InnerRectangle {
            transformOrigin: Item.Right
            xCenter: 2; yCenter: 1
            text: "Right"
        }
    }

    MainRectangle {
        InnerRectangle {
            transformOrigin: Item.BottomLeft
            xCenter: 0; yCenter: 2
            text: "Bottom\nLeft"
        }
    }

    MainRectangle {
        InnerRectangle {
            transformOrigin: Item.Bottom
            xCenter: 1; yCenter: 2
            text: "Bottom"
        }
    }

    MainRectangle {
        InnerRectangle {
            transformOrigin: Item.BottomRight
            xCenter: 2; yCenter: 2
            text: "Bottom\nRight"
        }
    }
}

