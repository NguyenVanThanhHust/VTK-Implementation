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
#include <vtkShrinkFilter.h>
#include <vtkShrinkPolyData.h>

int main()
{
	// Read .stl file
	vtkSTLReader *part = vtkSTLReader::New();
	part->SetFileName("Basamento.stl");

	vtkShrinkPolyData *partShrink = vtkShrinkPolyData::New();
	partShrink->SetInputConnection(part->GetOutputPort());
	partShrink->SetShrinkFactor(0.3);

	vtkPolyDataMapper *partMapper = vtkPolyDataMapper::New();
	partMapper->SetInputConnection(partShrink->GetOutputPort());

	vtkLODActor *partActor = vtkLODActor::New();
	partActor->SetMapper(partMapper);
	
	partActor->RotateX(30);
	partActor->RotateY(45);


	vtkRenderer *ren1 = vtkRenderer::New();
	vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer(ren1);
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);
	

	ren1->AddActor(partActor);
	ren1->SetBackground(0.1, 0.2, 0.3);
	renWin->SetWindowName("Render");
	renWin->SetSize(300, 300);
	renWin->Render();
	iren->Start();

	return EXIT_SUCCESS;
}