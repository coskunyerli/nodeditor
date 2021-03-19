#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>
#include <nodes/TypeConverter>

#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMainWindow>

#include <nodes/DataModelRegistry>
#include <memory>

#include "NumberSourceDataModel.hpp"
#include "NumberDisplayDataModel.hpp"
#include "AdditionModel.hpp"
#include "SubtractionModel.hpp"
#include "MultiplicationModel.hpp"
#include "DivisionModel.hpp"
#include "ModuloModel.hpp"
#include "Converters.hpp"


using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;
using QtNodes::TypeConverter;
using QtNodes::TypeConverterId;

static std::shared_ptr<DataModelRegistry>
registerDataModels() {
    auto ret = std::make_shared<DataModelRegistry>();

    ret->registerModel<NumberSourceDataModel>("Sources");

    ret->registerModel<NumberDisplayDataModel>("Displays");

    ret->registerModel<AdditionModel>("Operators");

    ret->registerModel<SubtractionModel>("Operators");

    ret->registerModel<MultiplicationModel>("Operators");

    ret->registerModel<DivisionModel>("Operators");

    ret->registerModel<ModuloModel>("Operators");

    ret->registerTypeConverter(std::make_pair(DecimalData().type(),
                                              IntegerData().type()),
                               TypeConverter{DecimalToIntegerConverter()});


    ret->registerTypeConverter(std::make_pair(IntegerData().type(),
                                              DecimalData().type()),
                               TypeConverter{IntegerToDecimalConverter()});

    return ret;
}


static
void
setStyle() {
    ConnectionStyle::setConnectionStyle(
            R"(
  {
    "ConnectionStyle": {
      "ConstructionColor": "gray",
      "NormalColor": "black",
      "SelectedColor": "gray",
      "SelectedHaloColor": "deepskyblue",
      "HoveredColor": "deepskyblue",

      "LineWidth": 3.0,
      "ConstructionLineWidth": 2.0,
      "PointDiameter": 10.0,

      "UseDataDefinedColors": true
    }
  }
  )");
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    setStyle();
    auto mainWindow = std::make_unique<QMainWindow>();
    auto *mainWidget = new QWidget(mainWindow.get());
    auto menuBar = mainWindow->menuBar();
    auto menu = menuBar->addMenu("File");
    auto saveAction = menu->addAction("Save..");
    auto loadAction = menu->addAction("Load..");
    auto mainWidgetLayout = new QVBoxLayout(mainWidget);

    std::shared_ptr<DataModelRegistry> dataModelRegistry = registerDataModels();
    auto scene = new FlowScene(dataModelRegistry, mainWidget);
    mainWidgetLayout->addWidget(new FlowView(scene));
    mainWidgetLayout->setContentsMargins(0, 0, 0, 0);
    mainWidgetLayout->setSpacing(0);

    QObject::connect(saveAction, &QAction::triggered,
                     scene, &FlowScene::save);

    QObject::connect(loadAction, &QAction::triggered,
                     scene, &FlowScene::load);

    mainWidget->setWindowTitle("Dataflow tools: simplest calculator");

    mainWindow->setCentralWidget(mainWidget);

    mainWindow->resize(800, 600);
    mainWindow->show();

    return QApplication::exec();
}
