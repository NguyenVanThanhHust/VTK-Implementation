#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);

#include <vtkCylinderSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

int main()
{
	// Create a new cylinder
	vtkCylinderSource *cylinder = vtkCylinderSource::New();
	cylinder->SetResolution(10);

	vtkPolyDataMapper *cylinderMapper = vtkPolyDataMapper::New();
	cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

	vtkActor *cylinderActor = vtkActor::New();
	cylinderActor->SetMapper(cylinderMapper);
	cylinderActor->RotateX(30);
	cylinderActor->RotateY(45);

	vtkRenderer *ren1 = vtkRenderer::New();
	vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer(ren1);
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);

	ren1->AddActor(cylinderActor);
	ren1->SetBackground(0.1, 0.2, 0.3);
	renWin->SetWindowName("Render");
	renWin->SetSize(300, 300);
	renWin->Render();
	iren->Start();

	return EXIT_SUCCESS;
}