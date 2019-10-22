#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);

#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSTLReader.h>
#include <vtkLODActor.h>
#include <vtkInteractionStyleModule.h>
#include <vtkCamera.h>
#include <vtkCameraActor.h>

int main()
{
	// Read .stl file
	vtkSTLReader *part = vtkSTLReader::New();
	part->SetFileName("Basamento.stl");

	vtkPolyDataMapper *partMapper = vtkPolyDataMapper::New();
	partMapper->SetInputConnection(part->GetOutputPort());

	vtkLODActor *partActor = vtkLODActor::New();
	partActor->SetMapper(partMapper);
	
	partActor->RotateX(30);
	partActor->RotateY(45);


	vtkRenderer *ren1 = vtkRenderer::New();
	vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer(ren1);
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);
	
	vtkCamera *cam = vtkCamera::New();
	cam->SetClippingRange(0.0444, 2.5555);
	cam->SetFocalPoint(0.05, -0.13, -0.06);
	cam->SetPosition(0.33, -0.12, -0.26);
	cam->ComputeViewPlaneNormal();
	cam->SetViewUp(-0.02, 0.99, 0.035);
	ren1->SetActiveCamera(cam);
	
	ren1->AddActor(partActor);
	ren1->SetBackground(0.1, 0.2, 0.3);
	renWin->SetWindowName("Render");
	renWin->SetSize(300, 300);
	renWin->Render();
	iren->Start();

	return EXIT_SUCCESS;
}