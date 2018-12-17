#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSTLReader.h>
#include <vtkLODActor.h>
#include <vtkAssembly.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkConeSource.h>
#include <vtkCylinderSource.h>
#include <vtkMapper.h>

int main()
{
	// Create a sphere, cube, cone and cylinder
	vtkSphereSource *sphere = vtkSphereSource::New();
	vtkPolyDataMapper *sphereMapper = vtkPolyDataMapper::New();
	sphereMapper->SetInputConnection(sphere->GetOutputPort());
	vtkActor *sphereActor = vtkActor::New();
	sphereActor->SetMapper(sphereMapper);

	vtkCubeSource *cube = vtkCubeSource::New();
	vtkPolyDataMapper *cubeMapper = vtkPolyDataMapper::New();
	cubeMapper->SetInputConnection(cube->GetOutputPort());
	vtkActor *cubeActor = vtkActor::New();
	cubeActor->SetMapper(cubeMapper);

	vtkConeSource *cone = vtkConeSource::New();
	vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
	coneMapper->SetInputConnection(cube->GetOutputPort());
	vtkActor *coneActor = vtkActor::New();
	coneActor->SetMapper(coneMapper);

	vtkCylinderSource *cylinder = vtkCylinderSource::New();
	vtkPolyDataMapper *cylinderMapper = vtkPolyDataMapper::New();
	cylinderMapper->SetInputConnection(cylinder->GetOutputPort());
	vtkActor *cylinderActor = vtkActor::New();
	cylinderActor->SetMapper(cylinderMapper);

	vtkAssembly *assembly = vtkAssembly::New();
	assembly->AddPart(cylinderActor);
	assembly->AddPart(sphereActor);
	assembly->AddPart(cubeActor);
	assembly->AddPart(coneActor);
	assembly->SetOrigin(5, 10, 15);
	assembly->AddPosition(5, 0, 0);
	assembly->RotateX(10);
	assembly->RotateY(10);

	vtkRenderer *ren1 = vtkRenderer::New();
	vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer(ren1);
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);

	ren1->AddActor(assembly);
	ren1->AddActor(sphereActor);
	ren1->AddActor(cubeActor);
	ren1->AddActor(cylinderActor);
	ren1->AddActor(coneActor);
	ren1->SetBackground(0.1, 0.2, 0.3);
	renWin->SetWindowName("Render");
	renWin->SetSize(1000, 1000);
	renWin->Render();
	iren->Start();

	return EXIT_SUCCESS;
}