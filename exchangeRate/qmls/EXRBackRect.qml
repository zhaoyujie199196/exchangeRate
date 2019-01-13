import QtQuick 2.0
import "EXRJs.js" as EXRJS

Rectangle{
    id : textBack
    color : "white";
    width : 140;
    height : 25;
    property string text : "";
    property bool isExpand :false;
    anchors.left: textId.right;
    anchors.verticalCenter: textId.verticalCenter;

    Rectangle{
        width : parent.width - 2;
        height : parent.height - 2;
        color : EXRJS.backColor;
        anchors.centerIn: parent;
    }

    EXRText{
        id : dataText;
        text : textBack.text;
        anchors.left: parent.left;
        anchors.leftMargin: 10;
        anchors.verticalCenter: parent.verticalCenter;
    }

    EXRText{
        id : iconText;
        text : textBack.isExpand ? "↑":"↓";
        anchors.right: parent.right;
        anchors.rightMargin: 10;
        anchors.verticalCenter: parent.verticalCenter;
    }
}
