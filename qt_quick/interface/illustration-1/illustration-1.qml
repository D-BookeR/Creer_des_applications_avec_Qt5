import QtQuick 2.0

Canvas {
    id: canvas
    width: 1000; height: 600
    onPaint: {
        var ctx = canvas.getContext("2d")
        ctx.reset()
        ctx.fillRect(100, 150, 50, 250)
        ctx.fillRect(200, 100, 100, 300)
    }
}
