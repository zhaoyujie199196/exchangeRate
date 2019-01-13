import QtQuick 2.0
import "EXRJs.js" as EXRJS

Rectangle {
    width : 830;
    height : 350;
    color : EXRJS.backColor;

    EXRHeader{
        id : header;
        width : parent.width;
        anchors.top: parent.top;
        anchors.topMargin: 30;

        onSigSearch: {
            EXRManager.exec(strStartTime, strEndTime, nNationCode);
        }
    }

    EXRInfo{
        id : info;
        anchors.centerIn: parent;
    }

    EXRPrompt{
        id : prompt;
    }

    Connections{
        target: EXRManager;
        onSigExecBegin:{
            info.strRate = "";
            prompt.show("正在查询，请稍侯...", false)
        }
        onSigExecFinish:{
            prompt.hide();
            var strRate = EXRManager.getMaxRate();
            info.strRate = strRate;
        }
        onSigParamError :{
            prompt.show("参数错误", true);
        }
    }
}
