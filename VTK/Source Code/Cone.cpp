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

#include <vtkConeSource.h>
#include <vtkAxesActor.h>
#include <vtkCamera.h>
#include <vtkCaptionActor2D.h>

#define vtkCreate(type,name) vtkSmartPointer<type> name = vtkSmartPointer<type>::New()
#define setMapper(MapperName,ObjectName)  MapperName->SetInputConnection(ObjectName->GetOutputPort())

int main()
{
	vtkCreate(vtkNamedColors, colors);

	vtkCreate(vtkConeSource, cone);
	cone->Update();

	vtkCreate(vtkPolyDataMapper, coneMapper);
	setMapper(coneMapper, cone);

	vtkCreate(vtkActor, actor);
	actor->SetMapper(coneMapper);

	// Create the RenderWindow and RenderWindowInteractor
	vtkCreate(vtkRenderer, renderer);

	vtkCreate(vtkRenderWindow, renWin);
	renWin->AddRenderer(renderer);
	renWin->SetWindowName("Cone");

	vtkCreate(vtkRenderWindowInteractor, iren);
	iren->SetRenderWindow(renWin);

	// Add the actors to the renderer; set the background and size; render
	renderer->AddActor(actor);
	renderer->SetBackground(colors->GetColor3d("MidnightBlue").GetData());

	renderer->AddActor(actor);
	renWin->SetSize(500, 500);
	renWin->Render();

	iren->Initialize();
	iren->Start();

	return EXIT_SUCCESS;	
}