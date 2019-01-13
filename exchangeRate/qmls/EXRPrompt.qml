import QtQuick 2.0

Loader{
    anchors.fill: parent;
    sourceComponent: undefined;
    property string strPrompt : "";
    property bool bIsAutoHide : false;
    Component{
        id : promptCom;
        Rectangle {
            color : "black";
            opacity: 0.6;
            MouseArea{
                anchors.fill: parent;
            }

            EXRText{
                anchors.centerIn: parent;
                text : strPrompt;
            }
        }
    }

    function show(prompt, isAutoHide){
        strPrompt = prompt;
        bIsAutoHide = isAutoHide;
        if (bIsAutoHide)
            timer.running = true;
        sourceComponent = promptCom;
    }

    function hide(){
        timer.running = false;
        sourceComponent = undefined;
    }

    Timer{
        id : timer;
        interval: 2000; repeat: false; running: false;
        onTriggered: {
            hide();
        }
    }
}
