#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingContextOpenGL);
VTK_MODULE_INIT(vtkRenderingFreeType);

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkXGMLReader.h>
#include <vtkUndirectedGraph.h>
#include <vtkGraphLayoutStrategy.h>
#include <vtkGraphLayoutView.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSimple2DLayoutStrategy.h>
#include <vtkPolyDataMapper.h>
#include <iostream>
#include <string>

using namespace std;

#define vtkCreate(type,name) vtkSmartPointer<type> name = vtkSmartPointer<type>::New()
#define setMapper(MapperName,ObjectName) \
vtkCreate(vtkPolyDataMapper,MapperName); MapperName->SetInputConnection(ObjectName->GetOutputPort())

int main()
{
	/*
	https://lorensen.github.io/VTKExamples/site/Cxx/InfoVis/XGMLReader/
	*/
	vtkCreate(vtkXGMLReader, reader);
	string fileName = "Delft_3dfier.gml";
	reader->SetFileName(fileName.c_str());
	reader->Update();

	// error from this line
	/*
	Assertion failed: tok.Type == vtkXGMLReaderToken::KEYWORD && tok.StringValue ==
"graph", file C:\Build\3rdParty\x64\VTK-8.0.0\IO\Infovis\vtkXGMLReader.cxx, line
 214
	*/

	vtkUndirectedGraph* g = reader->GetOutput();
	vtkCreate(vtkGraphLayoutView, graphLayoutView);
	graphLayoutView->AddRepresentationFromInput(g);
	graphLayoutView->SetLayoutStrategy("Simple 2D");
	graphLayoutView->ResetCamera();
	graphLayoutView->Render();

	graphLayoutView->GetInteractor()->Start();

	return EXIT_SUCCESS;
}