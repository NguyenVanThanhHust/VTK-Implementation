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

#include <vtkPlanesIntersection.h>
#include <vtkSphereSource.h>
#include <iostream>

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
	//https://lorensen.github.io/VTKExamples/site/Cxx/GeometricObjects/PlanesIntersection/
	*/
	// This is to check if 2 planes intersect or not

	// This is to compute if the arbitrary convex region
	// bounded by its planes intersects an axis aligned box
	// Play with parameter to see what changed
	vtkCreate(vtkSphereSource, sphere);
	// Default sphere is centered at orgin and have radius = 0.5
	// This paremeter can be setup
	sphere->Update();

	double bounds[6];
	sphere->GetOutput()->GetBounds(bounds);

	vtkCreate(vtkPoints, box);
	box->SetNumberOfPoints(1);

	double xMin, xMax, yMin, yMax, zMin, zMax;
	xMin = bounds[0]; xMax = bounds[1];
	yMin = bounds[2]; yMax = bounds[3];
	zMin = bounds[4]; zMax = bounds[5];

	box->SetPoint(0, 0, 10, 10);
	/*
	box->SetPoint(0, xMax, yMin, zMax);
	box->SetPoint(1, xMax, yMin, zMin);
	box->SetPoint(2, xMax, yMax, zMin);
	box->SetPoint(3, xMax, yMax, zMax);
	box->SetPoint(4, xMin, yMin, zMax);
	box->SetPoint(5, xMin, yMin, zMin);
	box->SetPoint(6, xMin, yMax, zMin);
	box->SetPoint(7, xMin, yMax, zMax);
	*/

	vtkCreate(vtkPlanesIntersection, planesIntersection);
	planesIntersection->SetBounds(bounds);

	int intersects = planesIntersection->IntersectsRegion(box);
	cout << "Intersects ? : " << intersects << endl;

	return EXIT_SUCCESS;
}