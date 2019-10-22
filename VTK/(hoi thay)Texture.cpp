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
#include <vtkCylinderSource.h>
#include <vtkMapper.h>
#include <vtkBMPReader.h>
#include <vtkTexture.h>
#include <vtkPlaneSource.h>

int main()
{
	vtkBMPReader *bmpReader = vtkBMPReader::New();
	bmpReader->SetFileName("masonry.bmp");

	vtkTexture *atext = vtkTexture::New();
	atext->SetInputConnection(bmpReader->GetOutputPort());
	atext->InterpolateOn();

	// Create a plane and source
	vtkPlaneSource *plane = vtkPlaneSource::New();
	vtkPolyDataMapper *planeMapper = vtkPolyDataMapper::New();
	planeMapper->SetInputConnection(plane->GetOutputPort());
	vtkActor *planeActor = vtkActor::New();
	planeActor->SetMapper(planeMapper);
	planeActor->SetTexture(atext);

	vtkRenderer *ren1 = vtkRenderer::New();
	vtkRenderWindow *renWin = vtkRenderWindow::New();
	renWin->AddRenderer(ren1);
	vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
	iren->SetRenderWindow(renWin);

	ren1->SetBackground(0.1, 0.2, 0.3);
	ren1->AddActor(planeActor);
	renWin->SetWindowName("Render");
	renWin->SetSize(1000, 1000);
	renWin->Render();
	iren->Start();

	return EXIT_SUCCESS;
}