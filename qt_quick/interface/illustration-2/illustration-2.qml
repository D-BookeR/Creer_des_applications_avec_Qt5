import QtQuick 2.0

Canvas {
    id: canvas
    width: 1000; height: 600
    onPaint: {
        var ctx = canvas.getContext("2d")
        ctx.reset()

        ctx.lineWidth = 10
        ctx.fillStyle = "deepskyblue"
        ctx.strokeStyle = "darkblue"
        ctx.rect( 10, 10, 980, 580)
        ctx.stroke()
        ctx.fill()

        ctx.fillStyle = "lawngreen"
        ctx.fillRect(10, 400, 980, 190)

        ctx.fillStyle = "#554444"
        ctx.fillRect(100, 150, 50, 250)
        ctx.fillStyle = "hsl(23%, 20%, 20%)"
        ctx.fillRect(200, 100, 100, 300)
        ctx.fillStyle = "rgb(59, 45, 45)"
        ctx.fillRect(50, 180, 60, 220)
        ctx.fillStyle = Qt.rgba(0.2, 0.15, 0.15, 0.9)
        ctx.fillRect(130, 220, 120, 180)
    }
}
