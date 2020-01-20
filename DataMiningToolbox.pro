QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ClassificationNode.cpp \
    ClusteringNode.cpp \
    DBSCANNode.cpp \
    ConnectionLine.cpp \
    DataTable.cpp \
    DecisionTreeNode.cpp \
    DecisionTreeParametersDialog.cpp \
    FilterNode.cpp \
    FilterParametersDialog.cpp \
    KMeansNode.cpp \
    KMeansParametersDialog.cpp \
    LinearRegressionNode.cpp \
    LinearSVMNode.cpp \
    Node.cpp \
    NormalizationNode.cpp \
    PartitionParametersDialog.cpp \
    PerceptronNode.cpp \
    PartitionNode.cpp \
    SamplingNode.cpp \
    SamplingParametersDialog.cpp \
    SceneNode.cpp \
    SourceParametersDialog.cpp \
    StatisticsNode.cpp \
    Stream.cpp \
    TableDialog.cpp \
    main.cpp \
    SourceNode.cpp \
    csvreader.cpp \
    MainWindow.cpp

HEADERS += \
    ClassificationNode.hpp \
    ClusteringNode.hpp \
    DBSCANNode.hpp \
    ConnectionLine.hpp \
    DataTable.hpp \
    DecisionTreeNode.hpp \
    DecisionTreeParametersDialog.hpp \
    FilterNode.hpp \
    FilterParametersDialog.hpp \
    KMeansNode.hpp \
    KMeansParametersDialog.hpp \
    LinearRegressionNode.hpp \
    LinearSVMNode.hpp \
    Node.hpp \
    NormalizationNode.hpp \
    PartitionNode.hpp \
    PartitionParametersDialog.hpp \
    PerceptronNode.hpp \
    SamplingNode.hpp \
    SamplingParametersDialog.hpp \
    SceneNode.hpp \
    SourceNode.hpp \
    SourceParametersDialog.hpp \
    StatisticsNode.hpp \
    Stream.hpp \ \
    TableDialog.hpp \
    csvreader.hpp \
    MainWindow.hpp


FORMS += \
    DecisionTreeParametersDialog.ui \
    FilterParametersDialog.ui \
    KMeansParametersDialog.ui \
    MainWindow.ui \
    PartitionParametersDialog.ui \
    SamplingParametersDialog.ui \
    SourceParametersDialog.ui \
    TableDialog.ui

LIBS += -lmlpack -larmadillo -llapack -lblas

RESOURCES += \
    Resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


