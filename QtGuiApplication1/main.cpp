#include "QtGuiApplication1.h"
# include "systemfunction.h"
#include <QtWidgets/QApplication>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>
#include<QFile>
#include <QDebug>
#include<QScatterSeries>
#include<QTCharts>
#include "dialog.h"

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	static QMutex mutex;
	mutex.lock();

	QString text;
	switch (type)
	{
	case QtDebugMsg:
		text = QString("Debug:");
		break;

	case QtWarningMsg:
		text = QString("Warning:");
		break;

	case QtCriticalMsg:
		text = QString("Critical:");
		break;

	case QtFatalMsg:
		text = QString("Fatal:");
	}

	QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
	QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
	QString current_date = QString("(%1)").arg(current_date_time);
	QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(current_date).arg(msg);

	QFile file("log.txt");
	file.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream text_stream(&file);
	text_stream << message << "\r\n";
	file.flush();
	file.close();

	mutex.unlock();
}
int main(int argc, char *argv[])
{
	qInstallMessageHandler(outputMessage);

	//string ss = "nihao";
	//int abc = 18;
	qDebug("This is a debug message");
	//qDebug() << ss.c_str() << abc << endl;
	qWarning("This is a warning message");
	qCritical("This is a critical message");
	//qFatal("This is a fatal message");




	QApplication a(argc, argv);
	/*
	Dialog dialog;
	dialog.show();
	*/
	
	/*int n, lambda;
	cout << "Enter n : " << endl;
	cin >> n;

	cout << "Enter lambda : " << endl;
	cin >> lambda;
	*/
	int n = 3;
	int lambda = 10000;
	

	//readfile	
	string filename = "testfile.txt";
	long line_count = countLine(filename);
	float* 	x = new float[line_count];
	float** 	y = new float*[line_count];
	for (int i = 0; i < line_count; i++) {
		y[i] = new float[1];
	}
	readFile(filename, line_count, x, y);

	//A
	float** Amat = new float*[line_count];
	for (int i = 0; i < line_count; i++) Amat[i] = new float[n];

	for (int i = 0; i < line_count; i++) {

		Amat[i][0] = 1;
		for (int k = 1; k < n; k++) {
			Amat[i][k] = pow(x[i], k);
		}
	}

	cout << endl << "Amat: " << endl;
	printArray(Amat);


	float** AT = transpose(Amat);


	cout << endl << "Transpose of Matrix: " << endl;
	printArray(AT);

	float** ATA = multi(AT, Amat);
	cout << endl << "ATA: " << endl;
	printArray(ATA);
	
	//(AtA*A*Y)^-1
	float** ATY = multi(AT, y);
	float** Newton = multi(inverse(ATA), ATY);

	float** newtonY = multi(Amat, Newton);

	cout << endl << "Newton: " << endl;
	printFormula(Newton, n);
	cout << "Total Error:" << totalError(Amat, Newton, y) << endl;
	
	string Newton_error = to_string(totalError(Amat, Newton, y));
	//printArray(Newton);

	cout << endl;


	//(AtA+lambda*Y)^-1  *   (A*Y)
	
	float** LSE = multi(inverse(opArray(ATA, lambdaY(lambda, n), 0)), ATY);
	float** LSEY = multi(Amat, LSE);
	cout << endl << "LSE: " << endl;
	printFormula(LSE, n);
	
	//ostringstream mytempstr;
	
	string LSE_error = to_string(totalError(Amat, LSE, y));
	qDebug("Total Error: %d", totalError(Amat, LSE, y));
	//cout << "Total Error:" << totalError(Amat, LSE, y) << endl;
	
	

	
	QLineSeries *newtonSeries = new QLineSeries();
	for (int i = 0; i < line_count; i++) {
		newtonSeries->append(x[i], newtonY[i][0]);
	}

	QLineSeries *LSESeries = new QLineSeries();
	for (int i = 0; i < line_count; i++) {
		LSESeries->append(x[i], LSEY[i][0]);
	}
	QScatterSeries *series0 = new QScatterSeries();
	series0->setName("scatter1");
	series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
	series0->setMarkerSize(15.0);
	for (int i = 0; i < line_count; i++) {
		series0->append(x[i], y[i][0]);
	}
	
	QChart *chart = new QChart();
	chart->legend()->hide();
	chart->addSeries(newtonSeries);
	chart->addSeries(series0);
	chart->createDefaultAxes();
	chart->setTitle(QString::fromStdString("lambda="+to_string(lambda)+" n="+to_string(n)+"<br>Newton :<br>" + showFormula(Newton, n) + "<br> Total error: " + Newton_error));
	


	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	QMainWindow window;
	window.setCentralWidget(chartView);
	window.resize(800, 600);
	window.show();
	
	system("Pause");
	window.close();

	QChart *chart2 = new QChart();
	chart2->legend()->hide();
	chart2->addSeries(LSESeries);
	chart2->addSeries(series0);
	chart2->createDefaultAxes();
	chart2->setTitle(QString::fromStdString("lambda = "+to_string(lambda)+" n = "+to_string(n)+"<br>LSE :<br>" + showFormula(LSE, n)+"<br> Total error: "+ LSE_error));



	QChartView *chartView2 = new QChartView(chart2);
	chartView2->setRenderHint(QPainter::Antialiasing);

	QMainWindow window2;
	window2.setCentralWidget(chartView2);
	window2.resize(800, 600);
	window2.show();
	return a.exec();
	
}
