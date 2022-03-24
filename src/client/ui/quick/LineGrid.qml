import QtQuick 2.0

import QuickQNodes 2.0 as QNo

QNo.LineGrid {
    id: lineGrid
    opacity: 0.9
    anchors.fill: parent

    gridScale: 25
    property int minorLineToDrawCount: 0
    property int majorLineToDrawCount: 0

    onRedrawLines: function (minorLineToDrawCount, majorLineToDrawCount) {
        lineGrid.minorLineToDrawCount = minorLineToDrawCount
        lineGrid.majorLineToDrawCount = majorLineToDrawCount
        gridCanvas.requestPaint()
    }

    Canvas {
        id: gridCanvas
        anchors.fill: parent
        visible: lineGrid.visible
        enabled: false // Disable mouse event catching
        onPaint: {
            var ctx = gridCanvas.getContext('2d')
            ctx.reset()
            ctx.strokeStyle = lineGrid.thickColor

            // iterate over minor lines...
            if (minorLineToDrawCount <= lineGrid.minorLines.length) {
                ctx.lineWidth = 1.
                context.beginPath()
                for (var l = 0; l < minorLineToDrawCount; l++) {
                    let line = lineGrid.minorLines[l]
                    if (!line)
                        break
                    ctx.moveTo(line.p1.x, line.p1.y)
                    ctx.lineTo(line.p2.x, line.p2.y)
                }
                context.stroke()
            }

            // iterate over major lines...
            if (majorLineToDrawCount <= lineGrid.majorLines.length) {
                //ctx.lineWidth = 2.
                ctx.strokeStyle = Qt.darker(lineGrid.thickColor, 1.3)
                context.beginPath()
                for (l = 0; l < majorLineToDrawCount; l++) {
                    let line = lineGrid.majorLines[l]
                    if (!line)
                        break
                    ctx.moveTo(line.p1.x, line.p1.y)
                    ctx.lineTo(line.p2.x, line.p2.y)
                }
                context.stroke()
            }
        }
    } // Canvas gridCanvas
} // QNo.AbstractLineGrid2
