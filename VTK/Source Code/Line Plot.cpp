#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingContextOpenGL);
VTK_MODULE_INIT(vtkRenderingFreeType);

#include <vtkVersion.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkChartXY.h>
#include <vtkTable.h>
#include <vtkPlot.h>
#include <vtkFloatArray.h>
#include <vtkContextView.h>
#include <vtkContextScene.h>
#include <vtkPen.h>

#define vtkCreate(type,name) vtkSmartPointer<type> name = vtkSmartPointer<type>::New()
#define setMapper(MapperName,ObjectName) \
vtkCreate(vtkPolyDataMapper,MapperName); MapperName->SetInputConnection(ObjectName->GetOutputPort())

int main()
{
	// Create a table with some points in it
	vtkCreate(vtkTable, table);

	vtkCreate(vtkFloatArray, arrX);
	arrX->SetName("X Axis");
	table->AddColumn(arrX);

	vtkCreate(vtkFloatArray, arrC);
	arrC->SetName("Cosine");
	table->AddColumn(arrC);

	vtkCreate(vtkFloatArray, arrS);
	arrS->SetName("Sine");
	table->AddColumn(arrS);

	// Fill in the table with some example values
	int numPoints = 69;
	float inc = 7.5 / (numPoints - 1);
	table->SetNumberOfRows(numPoints);
	for (int i = 0; i < numPoints; ++i)
	{
		table->SetValue(i, 0, i * inc);
		table->SetValue(i, 1, cos(i * inc));
		table->SetValue(i, 2, sin(i * inc));
	}

	// Set up the view
	vtkCreate(vtkContextView, view);
	view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);

	// Add multiple line plots, setting the colors etc
	vtkSmartPointer<vtkChartXY> chart =	vtkSmartPointer<vtkChartXY>::New();
	view->GetScene()->AddItem(chart);
	vtkPlot *line = chart->AddPlot(vtkChart::LINE);
	line->SetInputData(table, 0, 1);//cosine on X
	line->SetColor(0, 255, 255);
	line->SetWidth(1.0);
	line = chart->AddPlot(vtkChart::LINE);

	line->SetInputData(table, 0, 2);//sine on X
	line->SetColor(0, 255, 0);
	line->SetWidth(2.0);
	line = chart->AddPlot(vtkChart::LINE);

	view->GetInteractor()->Initialize();
	view->GetInteractor()->Start();

	return EXIT_SUCCESS;
}