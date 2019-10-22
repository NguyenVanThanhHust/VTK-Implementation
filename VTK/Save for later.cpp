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
#include <vtkMath.h>

#include <vtkConeSource.h>
#include <vtkCubeSource.h>
#include <vtkCylinderSource.h>
#include <vtkDiskSource.h>
#include <vtkLineSource.h>
#include <vtkCubeSource.h>
#include <vtkCylinderSource.h>
#include <vtkDiskSource.h>
#include <vtkLineSource.h>
#include <vtkSphereSource.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkTextSource.h>
#include <vtkPolyDataAlgorithm.h>

#include <vector>
#include <array>

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
	//https://lorensen.github.io/VTKExamples/site/Cxx/GeometricObjects/SourceObjectsDemo/
	*/
	/*
	This is to generatea polygonal models of geometry object.
	From upper left in reading order: sphere, cone, cylinder, cube,
	plane, text, random point cloud, disk (with or without hole), and line source.
	*/

	vtkCreate(vtkNamedColors, colors);

	// Set the background color
	array<unsigned char, 4> bkg{ { 51,77, 102, 255 } };
	colors->SetColor("Background Color", bkg.data());

	vector<vtkSP(vtkPolyDataAlgorithm)> sourceObjects;
	sourceObjects.push_back(vtkSP(vtkSphereSource)::New());
	static_cast<vtkSphereSource *>(sourceObjects.back().GetPointer())->SetPhiResolution(21);
	static_cast<vtkSphereSource *>(sourceObjects.back().GetPointer())->SetThetaResolution(21);

	sourceObjects.push_back(vtkSP(vtkConeSource)::New());
	static_cast<vtkConeSource *>(sourceObjects.back().GetPointer())->SetResolution(51);

	sourceObjects.push_back(vtkSP(vtkCylinderSource)::New());
	static_cast<vtkCylinderSource *>(sourceObjects.back().GetPointer())->SetResolution(51);



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