import QtQuick 2.0

Item {
    property string strRate : "";
    EXRText{
        text : getInfo(strRate);
        anchors.centerIn: parent;
        font.pointSize: 20;
    }

    function getInfo(strRate){
        if (strRate === "")
            return "";
        return "最高中行折算汇率" + strRate + "!";
    }
}
