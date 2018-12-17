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
#include <vtkTextActor.h>
#include <vtkScalarBarActor.h>
#include <vtkFloatArray.h>
#include <vtkPolyData.h>

int main()
{
	// Create a sphere, cube, cone and cylinder
	vtkSphereSource *sphere = vtkSphereSource::New();
	vtkPolyDataMapper *sphereMapper = vtkPolyDataMapper::New();
	sphereMapper->SetInputConnection(sphere->GetOutputPort());
	vtkLODActor *sphereActor = vtkLODActor::New();
	sphereActor->SetMapper(sphereMapper);
	sphere->SetCenter(0.0, 0.0, 0.0);
	sphere->SetRadius(5.0);
	sphere->Update();

	// Create scalar data to associate with the vertices of the sphere
	int numPts = sphere->GetOutput()->GetPoints()->GetNumberOfPoints();
	vtkFloatArray *scalar = vtkFloatArray::New();
	scalar->SetNumberOfValues(numPts);
	for (int i = 0; i < numPts; i++)
	{
		scalar->SetValue(i, static_cast<float>(i) / numPts);
	}

	vtkPolyData *poly = vtkPolyData::New();
	poly->DeepCopy(sphere->GetOutput());
	// khong get duoc nhu example code
	polu


		vtkRenderer *ren1 = vtkRenderer::New();
	vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer(ren1);
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);

	ren1->AddActor(sphereActor);
	ren1->SetBackground(0.1, 0.2, 0.3);
	renWin->SetWindowName("Render");
	renWin->SetSize(1000, 1000);
	// Render and interact
	renWin->Render();
	iren->Start();
	return EXIT_SUCCESS;
}
