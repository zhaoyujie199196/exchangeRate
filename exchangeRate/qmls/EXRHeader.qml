import QtQuick 2.0
import QtQuick.Controls 1.4
import "EXRJs.js" as EXRJS

Item {
    id : root;
    signal sigSearch(string strStartTime, string strEndTime, int nNationCode);
    EXRTimeSelecter{
        id : startTime;
        strCaption: "开始时间:"
        anchors.left: parent.left;
        anchors.leftMargin: 10;
        anchors.top: parent.top;
        anchors.topMargin: 10;
    }

    EXRTimeSelecter{
        id : endTime;
        strCaption: "结束时间:"
        anchors.left: startTime.right;
        anchors.leftMargin: 10;
        anchors.verticalCenter: startTime.verticalCenter;
    }

    EXRNationSelecter{
        id : nationSelecter;
        anchors.left: endTime.right;
        anchors.leftMargin: 10;
        anchors.verticalCenter: endTime.verticalCenter;
    }

    Rectangle{
        width : 60;
        height : 25;
        color : "white";
        anchors.left: nationSelecter.right;
        anchors.leftMargin: 20;
        anchors.verticalCenter: nationSelecter.verticalCenter;
        Rectangle{
            width : parent.width - 2;
            height : parent.height -2;
            color : EXRJS.backColor;
            anchors.centerIn: parent;
            EXRText{
                text : "查找"
                anchors.centerIn: parent;
            }
        }
        MouseArea{
            anchors.fill: parent;
            onClicked: {
                search();
            }
        }
    }

    function search(){
        startTime.bShowCalendar = false;
        endTime.bShowCalendar = false;
        nationSelecter.bShowNation = false;
        root.sigSearch(startTime.strSelectedTime, endTime.strSelectedTime, nationSelecter.getNationCode());
    }
}
