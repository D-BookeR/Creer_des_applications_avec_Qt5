import QtQuick 2.0

Rectangle {
    width: 925; height: 775

    Grid {
        x: 25; y: 25
        spacing: 25
        columns: 4
        FilledImage { mode: Image.Stretch; label: "Stretch" }
        FilledImage { mode: Image.PreserveAspectFit; label: "PreserveAspectFit" }
        FilledImage { mode: Image.PreserveAspectCrop; label: "PreserveAspectCrop" }
        FilledImage { mode: Image.Pad; label: "Pad" }
        FilledImage { mode: Image.Tile; label: "Tile" }
        FilledImage { mode: Image.TileVertically; label: "TileVertically" }
        FilledImage { mode: Image.TileHorizontally; label: "TileHorizontally" }
    }
}

