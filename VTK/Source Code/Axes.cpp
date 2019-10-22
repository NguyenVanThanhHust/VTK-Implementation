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

#include <vtkAxesActor.h>
#include <vtkCamera.h>
#include <vtkCaptionActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTransform.h>
#include <vtkArrowSource.h>

#define vtkCreate(type,name) vtkSmartPointer<type> name = vtkSmartPointer<type>::New()
#define setMapper(MapperName,ObjectName)  MapperName->SetInputConnection(ObjectName->GetOutputPort())

int main()
{
	vtkCreate(vtkNamedColors, colors);

	vtkCreate(vtkArrowSource, arrow);
	arrow->Update();

	vtkCreate(vtkPolyDataMapper, arrowMapper);
	setMapper(arrowMapper, arrow);

	vtkCreate(vtkActor, actor);
	actor->SetMapper(arrowMapper);

	// Create the RenderWindow and RenderWindowInteractor
	vtkCreate(vtkRenderer, renderer);

	vtkCreate(vtkRenderWindow, renWin);
	renWin->AddRenderer(renderer);
	renWin->SetWindowName("Axes");

	vtkCreate(vtkRenderWindowInteractor, iren);
	iren->SetRenderWindow(renWin);

	// Add the actors to the renderer; set the background and size; render
	renderer->AddActor(actor);
	renderer->SetBackground(colors->GetColor3d("MidnightBlue").GetData());

	vtkCreate(vtkTransform, transform2);
	transform2->Translate(0.25, 0.25, 0.25);
	vtkCreate(vtkAxesActor, axes);
	axes->SetUserTransform(transform2);

	vtkCreate(vtkTransform, transform1);
	transform1->Scale(0.25, 0.25, 0.25);
	actor->SetUserTransform(transform1);

	renderer->AddActor(axes);
	renderer->GetActiveCamera()->Azimuth(50);
	renderer->GetActiveCamera()->Elevation(-30);

	renWin->SetSize(500, 500);
	renWin->Render();

	iren->Initialize();
	iren->Start();

	return EXIT_SUCCESS;	
}