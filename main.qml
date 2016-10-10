import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

/*
import Qt.labs.controls.material 1.0
*/

ApplicationWindow {
    id: applicationWindow1
    /*
    Material.accent: Material.Orange
    Material.theme: Material.Dark
    */
    visible: true
    width: 510
    height: 480
    title: qsTr("Logical Analyzer")
    property int delta : 40
    signal getDrawingInfo(int beg, int end)
    function setPorts(list)
    {
        for (var i = 0; i < list.length; i++)
            modelPorts.append({text: list[i]})


    }
    function updateDrawingInfo(numCh, type, beginSample, endSample, lenArr, valueArr)
    {

        switch(numCh)
        {
        case 1:
            ch1.type = type
            mainLayout.begin = beginSample
            mainLayout.end = endSample
            ch1.sampleLen = lenArr
            ch1.sampleValue = valueArr
            console.log(ch1.sampleLen);
            console.log(ch1.sampleValue);
            ch1.canvasId.requestPaint()
            break;
        case 2:
            ch2.type = type
            ch2.sampleLen = lenArr
            ch2.sampleValue = valueArr
            console.log(ch2.sampleLen);
            console.log(ch2.sampleValue);
            ch2.canvasId.requestPaint()
            break;
            //case 3...n; or translate number to name
        }

    }
    function setBaudRates(list)
    {
        for (var i = 0; i < list.length; i++)
            modelBaudRates.append({text: list[i].toString()})
    }


    Item
    {
        id: topLayer
        width: parent.width
        height: 70
        ComboBox {
            id: comboBoxPorts

            x: 79
            y: 22
            width: 77
            height: 20
            model: ListModel
            {
            id: modelPorts
            ListElement { text: "Test File"}
        }
    }

    ComboBox {
        id: comboBoxBaudRates
        x: 256
        y: 22
        width: 79
        height: 20
        model: ListModel
        {
        id: modelBaudRates
        ListElement {text: "Default"}
    }
}

Button {
    id: button1
    x: 385
    y: 21
    text: qsTr("Connect")
}

Rectangle {
    id: rectangle1
    x: 505
    y: 22
    width: 32
    height: 20
    color: "#ffffff"
}

Text {
    id: text1
    x: 21
    y: 25
    text: qsTr("Device")
    font.pixelSize: 12
}

Text {
    id: text2
    x: 191
    y: 25
    text: qsTr("Baudrate")
    font.pixelSize: 12
}
}
Rectangle
{
    id: mainLayout
    color: "#ede5e5"
    anchors.right: parent.right
    anchors.rightMargin: 15
    anchors.left: parent.left
    anchors.leftMargin: 15
    anchors.top: topLayer.bottom
    height: 400

    property int begin : 0
    property int end: 1



    property real scaleLayout : ch1.realWidth / (end - begin)


    Canvas
    {
        id: gridCanvas
        property int offset_text : 25
        anchors.left: parent.left
        anchors.leftMargin: ch1.canvasId.x
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        onPaint:
        {
            console.log("w " + width + " h " + height)
            // get context to draw with
            var ctx = getContext("2d")
            ctx.reset()
            // setup the stroke
            ctx.lineWidth = 1
            ctx.strokeStyle = Qt.rgba(0, 0, 0, 0.25)

            var offset = 0;
            var count = ch1.realWidth / delta
            var captionOffset = (mainLayout.end - mainLayout.begin) / count
            console.log("cap " + count)
            var i = 0
            do
            {
                var text = Math.ceil(mainLayout.begin + i * captionOffset)
                var sizeText = ctx.measureText(text).width
                ctx.fillText(text, offset - sizeText/2, offset_text)
                ctx.beginPath()
                ctx.moveTo(offset,offset_text)
                ctx.lineTo(offset, height)
                ctx.closePath()
                ctx.stroke()
                offset += delta;
                i++
            }while(offset < width);

        }
        MouseArea
        {
            property real startX : 0
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onPressed:
            {
                startX = mouse.x
                cursorShape = Qt.ClosedHandCursor
            }
            onReleased:
            {
                cursorShape = Qt.ArrowCursor
                var offset = (mouse.x - startX) / mainLayout.scaleLayout
                if(mainLayout.begin - offset > 0)
                    getDrawingInfo(mainLayout.begin - offset, mainLayout.end - offset)
                else
                    getDrawingInfo(0, mainLayout.end - mainLayout.begin)
                gridCanvas.requestPaint()
            }
        }
    }
    SignalArea
    {
        id: ch1
        name: "Bit channel 1"
        beginSample: mainLayout.begin
        endSample: mainLayout.end
    }
    SignalArea
    {
        id: ch2
        anchors.top: ch1.bottom
        name: "Uart channel 1"
        beginSample: mainLayout.begin
        endSample: mainLayout.end
    }
}
}
