#include "frmmain.h"
#include "gcodepreprocessorutils.h"
#include "gcodeparser.h"
#include "gcodeviewparse.h"

#include <QApplication>
#include <QDebug>
#include <QVector3D>
#include <QGLWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGLFormat glf = QGLFormat::defaultFormat();
    glf.setSampleBuffers(true);
    glf.setSamples(8);
    glf.setDoubleBuffer(true);
    QGLFormat::setDefaultFormat(glf);

    frmMain w;
    w.show();

//    qDebug() << GcodePreprocessorUtils::overrideSpeed("G0 X0 Y10 Z200 F123", 50);
//    qDebug() << GcodePreprocessorUtils::removeComment("G1 X10 ((test comment 1))");
//    qDebug() << GcodePreprocessorUtils::removeComment("G1 X10 ;;test comment 2");
//    qDebug() << GcodePreprocessorUtils::parseComment("G1 X10 ((test comment 1))");
//    qDebug() << GcodePreprocessorUtils::parseComment("G1 X10 ;;test comment 2");
//    qDebug() << GcodePreprocessorUtils::truncateDecimals(1, "G0 X123.4456 Y3.12345 Z0.5");
//    qDebug() << GcodePreprocessorUtils::removeAllWhitespace("   test spaces   ");
//    qDebug() << GcodePreprocessorUtils::parseCodes(QString("G0 X123.4456 Y3.12345 Z0.5").split(' '), 'X');
//    qDebug() << GcodePreprocessorUtils::parseGCodes("G0 G02 G12 G3 G021 M03");
//    qDebug() << GcodePreprocessorUtils::parseMCodes("G0 G02 G12 G3 G021 M03");
//    qDebug() << GcodePreprocessorUtils::splitCommand("G0 X123.4456 Y3.12345 Z0.5");
//    qDebug() << GcodePreprocessorUtils::updatePointWithCommand("G0 X10 Y20 Z30", QVector3D(10, 10, 10), false);
//    qDebug() << GcodePreprocessorUtils::updateCenterWithCommand(GcodePreprocessorUtils::splitCommand("G0 X10 Y20 I0 J20 K6"), QVector3D(10, 10, 10), QVector3D(20, 20, 20), false, true);
//    qDebug() << GcodePreprocessorUtils::generateG1FromPoints(QVector3D(10, 10, 10), QVector3D(20, 20, 20), true, 3);
//    qDebug() << GcodePreprocessorUtils::getAngle(QVector3D(0, 0, 0), QVector3D(-10, 0, 10));
//    qDebug() << GcodePreprocessorUtils::calculateSweep(M_PI / 2, 0, false);
//    qDebug() << GcodePreprocessorUtils::generatePointsAlongArcBDring(QVector3D(10, 0, 0), QVector3D(0, 10, 0), QVector3D(0, 0, 0), false, 10, 0.1, 5);

//    GcodeParser gp;

//    gp.addCommand("G1 X0 Y10");
//    gp.addCommand("G1 X10 Y0");
//    gp.addCommand("G1 X10 Y10 Z0");
//    gp.addCommand("G2 X20 Y0 R10");

//    qDebug() << "PointSegment list";

//    for (int i = 0; i < 10000; i++) {
//        GcodeParser gp1;

//        gp1.addCommand("G1 X0 Y10");
//        gp1.addCommand("G1 X10 Y0");
//        gp1.addCommand("G1 X10 Y10 Z0");
//        gp1.addCommand("G2 X20 Y0 R10");
//    }

//    foreach (PointSegment *ps, gp.getPointSegmentList()) {
//        qDebug() << *ps->point() << ps->isArc() << ps->isClockwise();
//    }

//    GcodeViewParse gvp;
//    QList<QString> commands;

//    commands.append("G1 X0 Y10");
//    commands.append("G1 X10 Y0");
//    commands.append("G1 X10 Y10 Z0");
//    commands.append("G2 X20 Y0 Z0 R10");

//    qDebug() << "LineSegment list";

//    for (int i = 0; i < 10000; i++)
//    {
//        GcodeViewParse gvp1;
//        foreach (LineSegment* ls, gvp1.toObjRedux(commands, 5)) {
//        }
//    }

//    foreach (LineSegment* ls, gvp.toObjRedux(commands, 5)) {
//        qDebug() << ls->getStart() << ls->getEnd() << ls->getLineNumber() << ls->isArc();
//    }

//    return 0;

    return a.exec();
}
