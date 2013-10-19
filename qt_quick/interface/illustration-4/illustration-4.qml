import QtQuick 2.0

Canvas {
    id: canvas
    width: 1000; height: 600
    onPaint: {
        var ctx = canvas.getContext("2d")
        ctx.reset()

        var starGenerator = function(context) {
            return function (centerX, centerY, radius, order) {
                var branches = 2 * order + 1
                var ratio = 1 - 1/ branches
                var starX = function(n) { return centerX + radius * Math.cos(ratio * n * Math.PI)}
                var starY = function(n) { return centerY + radius * Math.sin(ratio * n * Math.PI)}

                context.beginPath()
                context.moveTo(centerX + radius, centerY)
                for (var i = 1; i < branches; i++) {
                    context.lineTo(starX(i), starY(i))
                }
                context.closePath()
                context.fill()
                context.stroke()
            }
        }

        var gradientSky = ctx.createLinearGradient(0, 0, 0, 400)
        gradientSky.addColorStop(0, "navy")
        gradientSky.addColorStop(0.2, "midnightblue")
        gradientSky.addColorStop(1, "deepskyblue")

        var gradientGrass = ctx.createRadialGradient(600, 0, 10, 600, 300, 600)
        gradientGrass.addColorStop(0, "lawngreen")
        gradientGrass.addColorStop(0.7, "forestgreen")
        gradientGrass.addColorStop(1, "darkgreen")

        ctx.lineWidth = 10
        ctx.fillStyle = gradientSky
        ctx.strokeStyle = "darkblue"
        ctx.rect( 10, 10, 980, 580)
        ctx.stroke()
        ctx.fill()

        ctx.fillStyle = gradientGrass
        ctx.fillRect(10, 400, 980, 190)

        ctx.fillStyle = "#554444"
        ctx.fillRect(100, 150, 50, 250)
        ctx.fillStyle = "hsl(23%, 20%, 20%)"
        ctx.fillRect(200, 100, 100, 300)
        ctx.fillStyle = "rgb(59, 45, 45)"
        ctx.fillRect(50, 180, 60, 220)
        ctx.fillStyle = Qt.rgba(0.2, 0.15, 0.15, 0.9)
        ctx.fillRect(130, 220, 120, 180)

        ctx.shadowBlur = 10
        ctx.shadowColor = "chocolate"
        ctx.shadowOffsetX = 2
        ctx.shadowOffsetY = 2

        var star = starGenerator(ctx)
        ctx.fillStyle = "gold"
        ctx.strokeStyle = "goldenrod"
        ctx.lineWidth = 4

        ctx.lineJoin = "round"
        ctx.fillRule = Qt.OddEvenFill
        star(500, 100, 40, 2)

        ctx.lineJoin = "miter"
        ctx.fillRule = Qt.WindingFill
        star(600, 120, -30, 3)
        star(900, 70, 15, 6)

        ctx.beginPath()
        ctx.ellipse(680, 60, 150, 150)
        ctx.closePath()
        ctx.fill()

        ctx.shadowBlur = 10
        ctx.fillStyle = gradientSky
        ctx.beginPath()
        ctx.ellipse(680, 80, 110, 110)
        ctx.closePath()
        ctx.fill()
    }
}
