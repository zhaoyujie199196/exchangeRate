import QtQuick 2.0
import QtQuick.Controls 1.4
import "EXRJs.js" as EXRJS

Item {
    id : root;
    width : 250;
    height : 40;
    property bool bShowCalendar : false;
    property var selectedDate: new Date;
    property string strCaption : "";
    property string strSelectedTime : "";

    EXRText{
        id : textId;
        text : root.strCaption;
        anchors.left: parent.left;
        anchors.leftMargin: 10;
        anchors.verticalCenter: parent.verticalCenter;
    }
    EXRBackRect{
        id : dataId;
        text: root.strSelectedTime;
        isExpand: bShowCalendar;
        MouseArea{
            anchors.fill: parent;
            onClicked: {
                bShowCalendar = !bShowCalendar;
            }
        }
    }

    Loader{
        id : calendarLoader;
        anchors.top: dataId.bottom;
        anchors.left: dataId.left;
        sourceComponent: getComponent(dataId.isExpand);
        function getComponent(bShowCalendar){
            return bShowCalendar ? calendarComp : undefined;
        }
    }

    Component{
        id : calendarComp;
        Calendar{

            minimumDate: new Date(2018, 0, 1);
            maximumDate: new Date(2020, 0, 1);

            onSelectedDateChanged: {
                root.strSelectedTime = selectedDate.toLocaleDateString(Qt.locale("de_DE"), "yyyy-MM-dd");
            }

            onClicked: {
                root.selectedDate = date;
            }

            Component.onCompleted: {
                selectedDate = root.selectedDate;
            }
        }
    }
}
