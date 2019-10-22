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
#include <vtkTextSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);

int main()
{
	

	vtkSmartPointer<vtkTextSource> text = vtkSmartPointer<vtkTextSource>::New();
	text->SetText("text");
	text->SetForegroundColor(0.3, 0.3, 0.3);
	text->BackingOff();
	
	text->Update();
	

	vtkSmartPointer<vtkPolyDataMapper> textMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	textMapper->SetInputConnection(text->GetOutputPort());

	vtkSmartPointer<vtkActor> textActor = vtkSmartPointer<vtkActor>::New();
	textActor->SetMapper(textMapper);//SetInputConnection(text->GetOutputPort());


	vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
	
	renWin->AddRenderer(ren1);

	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);

	ren1->AddActor(textActor);

	ren1->SetBackground(0.1, 0.2, 0.3);
	renWin->SetWindowName("Render");
	renWin->SetSize(1000, 1000);
	// Render and interact
	renWin->Render();
	iren->Start();
	return EXIT_SUCCESS;
}