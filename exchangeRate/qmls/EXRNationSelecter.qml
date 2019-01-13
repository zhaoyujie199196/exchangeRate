import QtQuick 2.0
import QtQuick.Controls 1.4
import "EXRJs.js" as EXRJS

Item
{
    id : root;
    width : 200;
    height : 40;
    property bool bShowNation : false;
    property string strSelectNation : "";
    ListModel{
        id : comboModel;
    }

    Component.onCompleted: {
        comboModel.clear();
        var jsonArr = EXRManager.getNationCodes();
        comboModel.append(jsonArr);
        if (jsonArr.length !== 0){
            strSelectNation = comboModel.get(0).nation;
        }
    }

    EXRText{
        id : textId;
        text : "选择货币:"
        anchors.left: parent.left;
        anchors.leftMargin: 10;
        anchors.verticalCenter: parent.verticalCenter;
    }

    EXRBackRect{
        id : dataId;
        text: strSelectNation;
        width: root.width - textId.width;
        isExpand : root.bShowNation;
        MouseArea{
            anchors.fill: parent;
            onClicked: {
                root.bShowNation = !root.bShowNation;
            }
        }
    }

    Loader{
        id : comboLoader;
        width : root.width;
        height : 500;
        anchors.left: dataId.left;
        anchors.top: dataId.bottom;
        sourceComponent: dataId.isExpand ? comboCom : undefined;
    }
    Component{
        id : comboCom;
        ListView{
            model: comboModel;
            delegate: comboItem;
            Component{
                id : comboItem;
                Rectangle{
                    width : 90;
                    height : 30;
                    color : EXRJS.backColor;
                    EXRText{
                        anchors.left: parent.left;
                        anchors.verticalCenter: parent.verticalCenter;
                        text : nation;
                    }
                    MouseArea{
                        anchors.fill: parent;
                        onClicked: {
                            strSelectNation = nation;
                            dataId.isExpand = false;
                        }
                    }
                }
            }
        }
    }

    function getNationCode(){
        for (var i = 0; i < comboModel.count; ++i){
            var item = comboModel.get(i);
            if (item.nation === strSelectNation)
                return parseInt(item.code);
        }
        return -1;
    }
}
