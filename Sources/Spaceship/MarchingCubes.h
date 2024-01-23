#pragma once
#include "Sources/KingdomEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/integer.hpp>
#include "Sources/Renderer/VertexArray.h"
#include "Sources/Renderer/Buffer.h"
#include "Sources/Renderer/RendererAPI.h"
#include "Sources/Renderer/Shader.h"
#include "Sources/Renderer/Texture.h"
#include "Sources/lib/stb/stb_image.h"

#include "Sources/Inputs/Inputs.h"
#include "Sources/Events/MouseEvent.h"
#include "Sources/Events/KeyEvent.h"

#include <bitset>
#include "MCTable.h"
#include "SDF.h"

//boundary values for Marching Cubes
#define MINX 0.0
#define MAXX 10.0
#define MINY 0.0
#define MAXY 4.0
#define MINZ 0.0
#define MAXZ 10.0




class MarchingCubes
{
public:
	MarchingCubes();
	~MarchingCubes();

	// Mouse interaction
	void OnEvent(Event& e);
	bool OnMouseClicked(MouseButtonPressedEvent& e);
	bool OnMouseReleased(MouseButtonReleasedEvent& e);
	void OnImGui();

	// Render
	void Render();
	void SetGridPointValue(const int& idx, float val);
	void SetGridAreaPointValue(const int& idx0, const int& idx1, float val);

	// Utility
	int Index(const int& x, const int& y, const int& z);
	int Index(const glm::ivec3& v);
	int getMaxTriangles() { return MAX_TRIANGLES; };
	int getCountTriangles() { return m_count_triangles; };
	int getMax_NumberOfLevel() { return (nY+1) - 2;};
	glm::ivec3 getGridDimension() { return glm::ivec3(nX, nY, nZ); };
	
	float gridval = 1.0f;
	float gridthresold = 0.0f;

	int slidershape = 0;
	float slidersize = 5.25f;
	// Data
	struct display_opts {
		bool blueprint_grid = true;
		bool marching_cubes = true;
		int floor_level = 1;
		glm::ivec3 select_cube = glm::ivec3(0);
	} mc_display_opts;

	struct select_opts {
		//glm::vec3 target = glm::vec3(0.0);
		glm::ivec3 selected_cell = glm::ivec3(0);
		bool DragStart = false;
		int DragFirstIndex;
		int DragLastIndex;
		int dX;
		int dZ;
	} mc_select_opts;

	struct edit_points_opts {
		int selected_point = 0;
		float value = 0.0f;
	} mc_edit_points_opts;

private:
	void InitBuffers();

	TRIANGLE* PropagateMarchingSquare(int ncellsX, int ncellsY, int ncellsZ, float thresold, grid* points);
	
	int GetIndexFromRaycast();
	glm::ivec3 GridCoords_FromIndex(const int& index);
	void UpdateRectangleSelection();

	void RenderShip();
	void RenderGrid();
	void RenderSelectCube();

//Signed Functions
private:
	typedef float (*func)(const float&, const glm::ivec3&, const glm::ivec3&);

private:
	int MAX_TRIANGLES = 1000;

	int nX, nY, nZ;
	glm::vec3 m_stepSize = glm::vec3(1.0);;

	grid* m_grid;

	struct shippoint {
		glm::ivec3 pos = glm::ivec3(0);
		float size;
		func shapefcn;
	};

	std::vector<shippoint> m_ship;

	TRIANGLE* m_triangles;


	bool m_stoprender = false;
	int m_count_points;
	int m_count_triangles;
	int m_vertices_per_level;
	
	int m_floor_bottom_padding = 1;
	int m_roof_bottom_padding = 1;
	

	glm::vec3 m_MAIN_POSITION = glm::vec3(0.0, 0.0, 0.0);
	// Rendering Marching Cubes
	std::shared_ptr<VertexArray>  m_VAO;
	std::shared_ptr<VertexBuffer> m_VBO;
	std::shared_ptr<IndexBuffer>  m_IBO;
	std::shared_ptr<Shader>  m_shader;
	std::shared_ptr<Texture> m_textures[2];

	// Rendering Grid
	std::shared_ptr<VertexArray>  m_VAOg;
	std::shared_ptr<VertexBuffer> m_VBOg;
	std::shared_ptr<IndexBuffer>  m_IBOg;
	std::shared_ptr<Shader>  m_shaderg;

	// Selectable cube
	std::shared_ptr<VertexArray>  m_VAOsc;
	std::shared_ptr<VertexBuffer> m_VBOsc;
	std::shared_ptr<IndexBuffer>  m_IBOsc;
	std::shared_ptr<Shader>  m_shadersc;
};