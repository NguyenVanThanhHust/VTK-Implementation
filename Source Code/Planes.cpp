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
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkCamera.h>

#include <vtkHull.h>
#include <vtkPlanes.h>
#include <vtkSphereSource.h>
#include <vtkTextMapper.h>
#include <vtkTextProperty.h>

#include <string>
#include <string.h>
#include <vector>

#define vtkCreate(type,name) vtkSmartPointer<type> name = vtkSmartPointer<type>::New()
#define setMapper(MapperName,ObjectName)  MapperName->SetInputConnection(ObjectName->GetOutputPort())
#define vtkSP(type) vtkSmartPointer<type>

#ifdef vtkGenericDataArray_h
#define InsertNextTupleValue InsertNextTypedTuple
#endif

using namespace std;

int main()
{

	/*
	//https://lorensen.github.io/VTKExamples/site/Cxx/GeometricObjects/Planes/
	*/

	vtkCreate(vtkNamedColors, colors);

	// These are the two methods we will use.
	vector<string> titles{ "Frustum planes", "Bounds" };
	vector<vtkSP(vtkPlanes)> planes;
	for (auto i = 0; i < titles.size(); ++i)
	{
		planes.push_back(vtkSP(vtkPlanes)::New());
	}

	// Using frustum planes //mat phang non cut
	vtkCreate(vtkCamera, camera);
	double planesArray[24];
	camera->GetFrustumPlanes(1, planesArray);
	planes[0]->SetFrustumPlanes(planesArray);

	// Using bounds
	vtkCreate(vtkSphereSource, sphere);
	sphere->Update();
	double bounds[6];
	sphere->GetOutput()->GetBounds(bounds);
	planes[1]->SetBounds(bounds);

	// At this point, we have the planes created 
	// by both method above

	// For visualisation, we will produce an n-sided convex hull and visualise it

	// Create a common text property
	vtkCreate(vtkTextProperty, textProperty);
	textProperty->SetFontSize(10);
	textProperty->SetJustificationToCentered();

	// Create window renderer and interactor
	vtkCreate(vtkRenderWindow, renWin);
	//renWin->AddRenderer(renderer);
	renWin->SetWindowName("Planes");

	vtkCreate(vtkRenderWindowInteractor, interactor);
	interactor->SetRenderWindow(renWin);

	vector<vtkSP(vtkHull)> hulls;
	vector<vtkSP(vtkPolyData)> pds;
	vector<vtkSP(vtkPolyDataMapper)> mappers;
	vector<vtkSmartPointer<vtkActor>> actors;
	vector<vtkSmartPointer<vtkTextMapper>> textMappers;
	vector<vtkSmartPointer<vtkActor2D>> textActors;
	vector<vtkSmartPointer<vtkRenderer>> renderers;

	for (auto i = 0; i < titles.size(); ++i)
	{
		hulls.push_back(vtkSP(vtkHull)::New());
		hulls[i]->SetPlanes(planes[i]);

		pds.push_back(vtkSmartPointer<vtkPolyData>::New());

		// To generate the convex hull we supply a vtkPolyData object and a bounding
		// box.
		// We define the bounding box to be where we expect the resulting polyhedron
		// to lie.
		// Make it a generous fit as it is only used to create the initial
		// polygons that are eventually clipped.
		hulls[i]->GenerateHull(pds[i], -200, 200, -200, 200, -200, 200);

		mappers.push_back(vtkSmartPointer<vtkPolyDataMapper>::New());
		mappers[i]->SetInputData(pds[i]);

		actors.push_back(vtkSmartPointer<vtkActor>::New());
		actors[i]->SetMapper(mappers[i]);
		actors[i]->GetProperty()->SetColor(
			colors->GetColor3d("Moccasin").GetData());
		actors[i]->GetProperty()->SetSpecular(0.8);
		actors[i]->GetProperty()->SetSpecularPower(30);

		textMappers.push_back(vtkSmartPointer<vtkTextMapper>::New());
		textMappers[i]->SetInput(titles[i].c_str());
		textMappers[i]->SetTextProperty(textProperty);

		textActors.push_back(vtkSmartPointer<vtkActor2D>::New());
		textActors[i]->SetMapper(textMappers[i]);
		textActors[i]->SetPosition(120, 16);

		renderers.push_back(vtkSmartPointer<vtkRenderer>::New());
		renderers[i]->AddActor(actors[i]);
		renderers[i]->AddViewProp(textActors[i]);

		renWin->AddRenderer(renderers[i]);
	}

	// Setup the viewports
	auto xGridDimensions = 2;
	auto yGridDimensions = 1;
	auto rendererSize = 300;
	// Setup rendre window size
	renWin->SetSize(rendererSize*xGridDimensions, rendererSize*yGridDimensions);
	for (auto row = 0; row < yGridDimensions; ++row)
	{
		for (auto col = 0; col < xGridDimensions; ++col)
		{
			auto index = row*xGridDimensions + col;

			// (xmin, ymin, xmax, ymax)
			double viewport[4] = {
				// convert all result to double by statics_cast
				static_cast<double>(col) / xGridDimensions,
				static_cast<double>(yGridDimensions - (row + 1)) / yGridDimensions,
				static_cast<double>(col + 1) / xGridDimensions,
				static_cast<double>(yGridDimensions - row)
			};
			if (index > actors.size() - 1)
			{
				// Add a renderer even if there is nor actor
				// This makes the renderer window background all the same color
				vtkCreate(vtkRenderer, ren);
				ren->SetBackground(colors->GetColor3d("DarkSlateGray").GetData());
				ren->SetViewport(viewport);
				renWin->AddRenderer(ren);
				continue;
			}
			renderers[index]->SetViewport(viewport);
			renderers[index]->SetBackground(
				colors->GetColor3d("DarkSlateGray").GetData());
			renderers[index]->ResetCamera();
			renderers[index]->GetActiveCamera()->Azimuth(30);
			renderers[index]->GetActiveCamera()->Elevation(-30);
			renderers[index]->ResetCameraClippingRange();			
		}
	}

	interactor->Initialize();
	renWin->Render();
	interactor->Start();

	return EXIT_SUCCESS;
}