import QtQuick
import QtQuick.Controls

ApplicationWindow {
    required property QtObject telemetry
    readonly property real displayedSpeed: telemetry.speed
    width: 400
    height: 240
    visible: true
    title: "Machine Display Lab"

    Column {
        anchors.centerIn: parent
        spacing: 16
        Label { text: "Simulated vehicle speed" }
        Label { text: displayedSpeed.toFixed(1) + " km/h"; font.pixelSize: 36 }
        Button { text: "Generate next frame"; onClicked: telemetry.advance() }
    }
}
