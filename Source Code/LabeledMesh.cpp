#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingContextOpenGL);
VTK_MODULE_INIT(vtkRenderingFreeType);

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSimple2DLayoutStrategy.h>
#include <vtkPolyDataMapper.h>
#include <vtkSphere.h>
#include <vtkSphereSource.h>
#include <vtkLODActor.h>
#include <vtkActor.h>
#include <vtkIdFilter.h>
#include <vtkSelectVisiblePoints.h>
#include <vtkRenderWindow.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkLabeledDataMapper.h>
#include <vtkActor2D.h>
#include <vtkCellCenters.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

using namespace std;

#define vtkCreate(type,name) vtkSmartPointer<type> name = vtkSmartPointer<type>::New()
#define setMapper(MapperName,ObjectName)  MapperName->SetInputConnection(ObjectName->GetOutputPort())

static int xLength;
static int yLength;

typedef struct
{
	vtkSmartPointer<vtkSelectVisiblePoints> visPts;
	vtkSmartPointer<vtkSelectVisiblePoints> visCells;
	vtkSmartPointer<vtkPoints> pts;
	vtkSmartPointer<vtkRenderWindow> renWin;
}vtkData;

// Create a function to draw the selection window at each location
// it is moved to
static void PlaceWindow(vtkData const& data, int xmin, int ymin)
{
	int xmax = xmin + xLength;
	int ymax = ymin + yLength;
	
	data.visPts->SetSelection(xmin, xmax, ymin, ymax);
	data.visCells->SetSelection(xmin, xmax, ymin, ymax);

	data.pts->InsertPoint(0, xmin, ymin, 0);
	data.pts->InsertPoint(1, xmin, ymin, 0);
	data.pts->InsertPoint(2, xmin, ymin, 0);
	data.pts->InsertPoint(3, xmin, ymin, 0);

	// Call Modified because InsertPoints does not modify vtkPoints
	// (for performance reasons)
	data.pts->Modified();
	data.renWin->Render();
}

static void MoveWindow(vtkData const& data)
{
	for (int y = 100; y < 300; y += 25)
	{
		for (int x = 100; x < 300; x += 25)
		{
			PlaceWindow(data, x, y);
		}
	}
}
int main()
{
	// Create a selection window.  We will display the point and cell ids that
	// lie within this window.
	int xmin = 200;
	xLength = 100;
	int xmax = xmin + xLength;
	int ymin = 200;
	yLength = 100;
	int ymax = ymin + yLength;

	vtkCreate(vtkPoints, pts);
	// 4 corners
	pts->InsertPoint(0, xmin, ymin, 0);
	pts->InsertPoint(1, xmax, ymin, 0);
	pts->InsertPoint(2, xmax, ymax, 0);
	pts->InsertPoint(3, xmin, ymax, 0);

	vtkCreate(vtkCellArray, rect);
	rect->InsertNextCell(5); // num points
	rect->InsertCellPoint(0); // idx of point
	rect->InsertCellPoint(1);
	rect->InsertCellPoint(2);
	rect->InsertCellPoint(3);
	rect->InsertCellPoint(0);

	vtkCreate(vtkPolyData, selectRect);
	selectRect->SetPoints(pts);
	selectRect->SetLines(rect);

	vtkCreate(vtkPolyDataMapper2D, rectMapper);
	rectMapper->SetInputData(selectRect);

	vtkCreate(vtkActor2D, rectActor);
	rectActor->SetMapper(rectMapper);

	// Create a sphere
	vtkCreate(vtkSphereSource, sphere);
	vtkCreate(vtkPolyDataMapper, sphereMapper);
	setMapper(sphereMapper, sphere);
	sphereMapper->GlobalImmediateModeRenderingOn();

	vtkCreate(vtkActor, sphereActor);
	sphereActor->SetMapper(sphereMapper);

	// Generate data array containing point and cell ids
	vtkCreate(vtkIdFilter, ids);
	ids->SetInputConnection(sphere->GetOutputPort());
	ids->PointIdsOn();
	ids->FieldDataOn();
	
	// Create renderer
	vtkCreate(vtkRenderer, ren1);

	// Create labels for points
	vtkCreate(vtkSelectVisiblePoints, visPts);
	visPts->SetInputConnection(ids->GetOutputPort());
	visPts->SetRenderer(ren1);
	visPts->SelectionWindowOn();
	visPts->SetSelection(xmin, xmin + xLength, ymin, ymin + yLength);

	// Create the mapper to display the points ids
	// Specify the format to use for the labels
	// Create the associated actor
	vtkCreate(vtkLabeledDataMapper, ldm);
	ldm->SetInputConnection(visPts->GetOutputPort());
	ldm->SetLabelModeToLabelFieldData();

	vtkCreate(vtkActor2D, pointLabels);
	pointLabels->SetMapper(ldm);

	// Create the mapper to display the cell ids.  Specify the
	// format to use for the labels.  Also create the associated actor.
	vtkCreate(vtkCellCenters, cc);
	cc->SetInputConnection(ids->GetOutputPort());

	vtkCreate(vtkSelectVisiblePoints, visCells);
	visCells->SetInputConnection(cc->GetOutputPort());
	visCells->SetRenderer(ren1);
	visCells->SelectionWindowOn();
	visCells->SetSelection(xmin, xmin + xLength, ymin, ymin + yLength);

	// Create the mapper to display the cell ids.  Specify the
	// format to use for the labels.  Also create the associated actor.
	vtkCreate(vtkLabeledDataMapper, cellMapper);
	cellMapper->SetInputConnection(visCells->GetOutputPort());
	cellMapper->SetLabelModeToLabelFieldData();

	vtkCreate(vtkActor2D, cellLabels);
	cellLabels->SetMapper(cellMapper);

	// Create the RenderWindow and RenderWindowInteractor
	vtkCreate(vtkRenderWindow, renWin);
	renWin->AddRenderer(ren1);

	vtkCreate(vtkRenderWindowInteractor, iren);
	iren->SetRenderWindow(renWin);

	// Add the actors to the renderer; set the background and size; render
	ren1->AddActor(sphereActor);
	ren1->AddActor2D(rectActor);
	ren1->AddActor2D(pointLabels);
	ren1->AddActor2D(cellLabels);

	ren1->SetBackground(1, 1, 1);
	renWin->SetSize(500, 500);
	renWin->Render();

	vtkData data = { visPts, visCells, pts, renWin };

	// Move the selection window across the data set.
	MoveWindow(data);

	// Put the selection window in the center of the render window.
	// This works because the xmin = ymin = 200, xLength = yLength = 100, and
	// the render window size is 500 x 500.
	PlaceWindow(data, xmin, ymin);

	iren->Initialize();
	iren->Start();

	return EXIT_SUCCESS;	
}