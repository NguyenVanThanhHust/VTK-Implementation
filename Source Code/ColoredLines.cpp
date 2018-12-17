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

#include <vtkCellArray.h>
#include <vtkPentagonalPrism.h>
#include <vtkPoints.h>
#include <vtkPolyhedron.h>
#include <vtkTetra.h>
#include <vtkUnstructuredGrid.h>
#include <vtkVoxel.h>
#include <vtkWedge.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>
#include <vtkCaptionActor2D.h>
#include <vtkTransform.h>
#include <vtkDataSetMapper.h>
#include <vtkLine.h>
#include <vtkUnsignedCharArray.h>
#include <vtkLine.h>

#define vtkCreate(type,name) vtkSmartPointer<type> name = vtkSmartPointer<type>::New()
#define setMapper(MapperName,ObjectName)  MapperName->SetInputConnection(ObjectName->GetOutputPort())

#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif

int main()
{
	
	/*
	//https://lorensen.github.io/VTKExamples/site/Cxx/GeometricObjects/ColoredLines/
	*/
	// Create the polydata where we will store all the geometric data
	vtkCreate(vtkPolyData, linesPolyData);

	// Create 3 points
	double origin[3] = { 0.0,0.0,0.0 };
	double p0[3] = { 1.0,0.0,0.0 };
	double p1[3] = { 0.0,1.0,0.0 };

	// Create a vktPoints container and store the points in it
	vtkCreate(vtkPoints, pts);
	pts->InsertNextPoint(origin);
	pts->InsertNextPoint(p0);
	pts->InsertNextPoint(p1);
	// pts contain 3 points : origin, p0, p1

	// Add the points to polydata container
	linesPolyData->SetPoints(pts);
	// linesPolyData contains 1st data : pts

	// Create the 1st line between Origin and p0
	vtkCreate(vtkLine, line1);
	line1->GetPointIds()->SetId(0, 0);// the second 0 is the index of the Origin
	line1->GetPointIds()->SetId(1, 1);// the second 1 is the index of p0 in linePolyData 
	// SetId have 2 component 
	// 1st : index in line1 
	// 2nd : index in linePolyData
	
	// Create the 2nd line between Origin and p1
	vtkCreate(vtkLine, line2);
	line2->GetPointIds()->SetId(0, 0);
	line2->GetPointIds()->SetId(1, 2);
	
	// Create a vktCellArray container and store the lines in it
	vtkCreate(vtkCellArray, lines);
	lines->InsertNextCell(line1);
	lines->InsertNextCell(line2);
	// lines contain line1 and line2

	// Add the lines to the polydata container
	linesPolyData->SetLines(lines);

	vtkCreate(vtkNamedColors, namedColors);

	// Create a vtkUnsignedCharArray container and store the colors in it
	vtkCreate(vtkUnsignedCharArray, colors);
	colors->SetNumberOfComponents(3);
	colors->InsertNextTupleValue(namedColors->GetColor3ub("Tomata").GetData());
	colors->InsertNextTupleValue(namedColors->GetColor3ub("Mint").GetData());
	// colors contains 

	// Color the lines
	// SetScalar() automatically associates the values in data array passed
	// to the elemnents in the same indices of the cell data array
	// on which it is
	// This means the first component (red) of the color array
	// is matched with the first component of the cell array(line0)
	// and the second component (green) of the colors array
	// is matched with the second component of the cell array (line 1)
	//linesPolyData->GetCellData()->SetScalars(colors);
	
	// Setup the visualization pipeline
	vtkCreate(vtkPolyDataMapper, mapper);
	mapper->SetInputData(linesPolyData);

	vtkCreate(vtkActor, actor);
	actor->SetMapper(mapper);
	actor->GetProperty()->SetLineWidth(2);

	vtkCreate(vtkRenderer, renderer);
	renderer->AddActor(actor);
	renderer->SetBackground(namedColors->GetColor3d("SlateGray").GetData());

	vtkCreate(vtkRenderWindow, renWin);
	renWin->AddRenderer(renderer);
	renWin->SetWindowName("Colored Lines");

	vtkCreate(vtkRenderWindowInteractor, interactor);
	interactor->SetRenderWindow(renWin);
	
	// Visualize
	renWin->Render();
	interactor->Start();

	return EXIT_SUCCESS;	
}