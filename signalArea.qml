import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2


Item {
    property string name : "Name Channel"
    property int _offset : 15
    property alias canvasId: canvas
    property alias realWidth : canvas.width
    property int beginSample : 0
    property int endSample : 1
    property real scaleSample : realWidth / (endSample - beginSample)

    property int type : 0

    property variant sampleLen: []
    property variant sampleValue: []

    width: parent.width
    height: 100
    Text {
        id: caption
        text: name
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: 80
    }
    Canvas
    {
        id: canvas
        height: _offset + 5
        anchors.left: caption.right
        anchors.right: parent.right
        anchors.verticalCenter: caption.verticalCenter

        onPaint: {
            console.log("sample " + beginSample + " " + endSample)
            // get context to draw with
            var ctx = getContext("2d")
            ctx.reset()
            // setup the stroke
            ctx.lineWidth = 2
            ctx.strokeStyle = "orange"

            // begin a new path to draw
            ctx.beginPath()

            switch(type)
            {
            case 0:
                //start point
                if(sampleValue[0] == 0)
                    ctx.moveTo(0,0)
                else
                    ctx.moveTo(0, _offset)
                var drawBegin = 0

                for(var i = 0; i < sampleLen.length && i < sampleValue.length; i++)
                {
                    var scaledValue = sampleLen[i] * scaleSample;
                    if(sampleValue[i] == 1)
                        drawOne(ctx, drawBegin + scaledValue)
                    else
                        if(sampleValue[i] == 0)
                            drawZero(ctx, drawBegin + scaledValue)
                    drawBegin += scaledValue
                }
                ctx.stroke()
                break;
            case 1:
                ctx.moveTo(0, _offset / 2)
                drawBegin = 0

                for(i = 0; i < sampleLen.length && i < sampleValue.length; i++)
                {
                    scaledValue = sampleLen[i] * scaleSample;
                    if(sampleValue[i] == 0)
                        drawMedium(ctx, drawBegin + scaledValue)
                    else
                        if(sampleValue[i] != -1)
                            drawValue(ctx, drawBegin, scaledValue, sampleValue[i])
                    drawBegin += scaledValue
                }
                ctx.stroke()
                break;
            }
        }
        //function draw cross finally
        function drawZero(ctx, end)
        {
            ctx.lineTo(end, 0)
            ctx.lineTo(end, _offset)
        }
        function drawOne(ctx, end)
        {
            ctx.lineTo(end, _offset)
            ctx.lineTo(end, 0)
        }
        function drawMedium(ctx, end)
        {
            ctx.lineTo(end, _offset / 2)
        }
        function drawValue(ctx, start, len, value)
        {
            ctx.lineTo(start + _offset / 2, 0)
            ctx.lineTo(start + len - _offset / 2, 0)
            ctx.lineTo(start + len, _offset / 2)
            ctx.lineTo(start + len - _offset / 2, _offset)
            ctx.lineTo(start + _offset / 2, _offset)
            ctx.lineTo(start, _offset / 2)
            var sizeText = ctx.measureText(value).width
            ctx.fillText(value, start + len / 2 - sizeText / 2 , _offset - 2)
            ctx.moveTo(start + len, _offset/2)
        }

    }
}
