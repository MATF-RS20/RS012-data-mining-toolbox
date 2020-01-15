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
    FilterNode.cpp \
    KMeansNode.cpp \
    LinearRegressionNode.cpp \
    LinearSVMNode.cpp \
    Node.cpp \
    NormalizationNode.cpp \
    PerceptronNode.cpp \
    PartitionNode.cpp \
    SamplingNode.cpp \
    SceneNode.cpp \
    StatisticsNode.cpp \
    Stream.cpp \
    main.cpp \
    SourceNode.cpp \
    csvreader.cpp \
    TableWindow.cpp \
    MainWindow.cpp

HEADERS += \
    ClassificationNode.hpp \
    ClusteringNode.hpp \
    DBSCANNode.hpp \
    ConnectionLine.hpp \
    DataTable.hpp \
    DecisionTreeNode.hpp \
    FilterNode.hpp \
    KMeansNode.hpp \
    LinearRegressionNode.hpp \
    LinearSVMNode.hpp \
    Node.hpp \
    NormalizationNode.hpp \
    PartitionNode.hpp \
    PerceptronNode.hpp \
    SamplingNode.hpp \
    SceneNode.hpp \
    SourceNode.hpp \
    StatisticsNode.hpp \
    Stream.hpp \ \
    csvreader.hpp \
    TableWindow.hpp \
    MainWindow.hpp


FORMS += \
    MainWindow.ui

LIBS += -lmlpack -larmadillo -llapack -lblas

RESOURCES += \
    Resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


