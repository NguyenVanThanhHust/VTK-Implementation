#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingContextOpenGL);
VTK_MODULE_INIT(vtkRenderingFreeType);

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkLODActor.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkActor2D.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPoints.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkPolyLine.h>

#include <vtkLinearExtrusionFilter.h>


#define vtkCreate(type,name) vtkSmartPointer<type> name = vtkSmartPointer<type>::New()
#define setMapper(MapperName,ObjectName)  MapperName->SetInputConnection(ObjectName->GetOutputPort())
#define vtkSP(type) vtkSmartPointer<type>

#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif

using namespace std;

int main()
{
	/*
	//https://lorensen.github.io/VTKExamples/site/Cxx/GeometricObjects/EllipticalCylinder/
	*/
	/*
	This is to create an elliptical cross-section and stores it in a vtkPolyData.
	Use vtkLinearExtrusionFilter creates an elliptical cylinder by extruding vtkPolyLine along a vector
	Set the backface propersty of vtkActor to show the front and back face of the cylinder
	*/
	double angle = 0;
	double r1, r2;
	double centerX, centerY;
	r1 = 50;
	r2 = 30;
	centerX = 10.0;
	centerY = 5.0;

	vtkCreate(vtkPoints, points);
	int id = 0;
	while (angle <= 2.0*vtkMath::Pi() + (vtkMath::Pi() / 60.0))
	{
		points->InsertNextPoint(r1*cos(angle) + centerX, r2*sin(angle) + centerY, 0.0);
		angle += (vtkMath::Pi() / 60.0);
		++id;
	}
	
	vtkCreate(vtkPolyLine, line);
	line->GetPointIds()->SetNumberOfIds(id);

	for (unsigned int i = 0; i < static_cast<unsigned int>(id); ++i)
	{
		line->GetPointIds()->SetId(i, i);
	}

	vtkCreate(vtkCellArray, lines);
	lines->InsertNextCell(line);

	vtkCreate(vtkPolyData, polyData);
	polyData->SetPoints(points);
	polyData->SetLines(lines);

	vtkCreate(vtkLinearExtrusionFilter, extrude);
	extrude->SetInputData(polyData);
	extrude->SetExtrusionTypeToNormalExtrusion();
	extrude->SetVector(0.0, 0.0, 100.0);
	extrude->Update();

	vtkCreate(vtkNamedColors, colors);
	vtkCreate(vtkPolyDataMapper, lineMapper);
	lineMapper->SetInputData(polyData);

	vtkCreate(vtkActor, lineActor);
	lineActor->SetMapper(lineMapper);
	lineActor->GetProperty()->SetColor(colors->GetColor3d("Peacock").GetData());

	vtkCreate(vtkPolyDataMapper, mapper);
	setMapper(mapper, extrude);

	vtkCreate(vtkProperty, back);
	back->SetColor(colors->GetColor3d("Tomato").GetData());

	vtkCreate(vtkActor, actor);
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
	actor->SetBackfaceProperty(back);

	vtkCreate(vtkRenderer, renderer);
	renderer->SetBackground(colors->GetColor3d("SlateGray").GetData());
	renderer->AddActor(actor);
	renderer->AddActor(lineActor);

	vtkCreate(vtkRenderWindow, renWin);
	renWin->SetWindowName("Elliptical Cylinder");
	renWin->AddRenderer(renderer);
	renWin->SetSize(600, 600);

	vtkCreate(vtkRenderWindowInteractor, interactor);
	interactor->SetRenderWindow(renWin);

	vtkCreate(vtkInteractorStyleTrackballCamera, style);
	interactor->SetInteractorStyle(style);

	vtkCreate(vtkCamera, camera);
	camera->SetPosition(0, 1, 0);
	camera->SetFocalPoint(0, 0, 0);
	camera->SetViewUp(0, 0, 1);
	camera->Azimuth(30);
	camera->Elevation(30);

	renderer->SetActiveCamera(camera);
	renderer->ResetCamera();
	renderer->ResetCameraClippingRange();

	renWin->Render();
	interactor->Start();
	return EXIT_SUCCESS;
}