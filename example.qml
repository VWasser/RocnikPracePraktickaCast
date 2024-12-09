import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

Window {
    visible: true
    width: 640
    height: 480
    ListModel{
        id: listmodel
    }
    function changeAll(){
        for(var i=0; i< listmodel.count; ++i){
            listmodel.setProperty(i, "number", listmodel.get(i).number + 1)
        }
    }
    GridView{
        id: grid
        anchors.fill: parent
        clip: true
        model: listmodel
        cellHeight: 120
        cellWidth: 120
        delegate: Item {
            width: grid.cellWidth; height: grid.cellHeight
            Column {
                anchors.fill: parent
                Text { text: model.number; anchors.horizontalCenter: parent.horizontalCenter }
                Button{text: "change me"; onClicked: model.number +=1}
                Button{text: "change all"; onClicked: changeAll()}
            }
        }
    }
    Component.onCompleted: {
        for(var i=0; i < 10; ++i){
            listmodel.append({"number": 0});
        }
    }
}
